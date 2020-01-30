#ifndef boxcar_connection_hpp
#define boxcar_connection_hpp

#include "Reply.hpp"
#include "Request.hpp"
#include "RequestHandler.hpp"
#include "RequestParser.hpp"
#include <array>
#include <boost/asio.hpp>
#include <memory>

namespace BoxCar {
namespace Http {

class ConnectionManager;

/// Represents a single connection from a client.
class Connection : public std::enable_shared_from_this<Connection> {
  public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    /// Construct a connection with the given socket.
    explicit Connection(boost::asio::ip::tcp::socket socket,
                        ConnectionManager& manager,
                        RequestHandler& handler);

    /// Start the first asynchronous operation for the connection.
    void start();

    /// Stop all asynchronous operations associated with the connection.
    void stop();

  private:
    /// Perform an asynchronous read operation.
    void doRead();

    /// Perform an asynchronous write operation.
    void doWrite();

    /**
     * Socket for the connection.
     */
    boost::asio::ip::tcp::socket socket;

    /// The manager for this connection.
    ConnectionManager& connectionManager;

    /// The handler used to process the incoming Request.
    RequestHandler& requestHandler;

    /// Buffer for incoming data.
    std::array<char, 8192> buffer;

    /// The incoming Request.
    Request request;

    /// The parser for the incoming Request.
    RequestParser requestParser;

    /// The Reply to be sent back to the client.
    Reply reply;
};

typedef std::shared_ptr<Connection> connection_ptr;

}
}

#endif
