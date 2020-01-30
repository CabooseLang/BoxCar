//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "Connection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"
#include <utility>
#include <vector>

namespace BoxCar {
namespace Http {

Connection::Connection(boost::asio::ip::tcp::socket socket,
                       ConnectionManager& manager,
                       RequestHandler& handler)
  : socket(std::move(socket))
  , connectionManager(manager)
  , requestHandler(handler) {}

void
Connection::start() {
    this->doRead();
}

void
Connection::stop() {
    this->socket.close();
}

void
Connection::doRead() {
    auto self(shared_from_this());
    this->socket.async_read_some(
      boost::asio::buffer(this->buffer),
      [this, self](boost::system::error_code ec,
                   std::size_t bytesTransferred) {
          if (!ec) {
              RequestParser::ResultType result;
              std::tie(result, std::ignore) = this->requestParser.parse(
                this->request,
                this->buffer.data(),
                this->buffer.data() + bytesTransferred);

              if (result == RequestParser::ResultType::GOOD) {
                  this->requestHandler.handleRequest(this->request,
                                                     this->reply);
                  doWrite();
              } else if (result == RequestParser::ResultType::BAD) {
                  reply = Reply::stockReply(StatusType::BAD_REQUEST);
                  doWrite();
              } else
                  doRead();
          } else if (ec != boost::asio::error::operation_aborted)
              this->connectionManager.stop(shared_from_this());
      });
}

void
Connection::doWrite() {
    auto self(shared_from_this());
    boost::asio::async_write(
      this->socket,
      this->reply.toBuffers(),
      [this, self](boost::system::error_code ec, std::size_t) {
          if (!ec) {
              // Initiate graceful connection closure.
              boost::system::error_code ignored_ec;
              this->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                    ignored_ec);
          }

          if (ec != boost::asio::error::operation_aborted) {
              this->connectionManager.stop(shared_from_this());
          }
      });
}

}
}
