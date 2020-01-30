#ifndef boxcar_connection_hpp
#define boxcar_connection_hpp

#include "RequestHandler.hpp"
#include "reply.hpp"
#include "request.hpp"
#include "request_parser.hpp"
#include <array>
#include <boost/asio.hpp>
#include <memory>

namespace BoxCar {
namespace Http {

class ConnectionManager;

/// Represents a single connection from a client.
class connection : public std::enable_shared_from_this<connection> {
  public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    /// Construct a connection with the given socket.
    explicit connection(boost::asio::ip::tcp::socket socket,
                        ConnectionManager& manager,
                        RequestHandler& handler);

    /// Start the first asynchronous operation for the connection.
    void start();

    /// Stop all asynchronous operations associated with the connection.
    void stop();

  private:
    /// Perform an asynchronous read operation.
    void do_read();

    /// Perform an asynchronous write operation.
    void do_write();

    /**
     * Socket for the connection.
     */
    boost::asio::ip::tcp::socket socket;

    /// The manager for this connection.
    ConnectionManager& connectionManager;

    /// The handler used to process the incoming request.
    RequestHandler& requestHandler;

    /// Buffer for incoming data.
    std::array<char, 8192> buffer;

    /// The incoming request.
    Request request;

    /// The parser for the incoming request.
    RequestParser requestParser;

    /// The reply to be sent back to the client.
    Reply reply;
};

typedef std::shared_ptr<connection> connection_ptr;

}
}

#endif
