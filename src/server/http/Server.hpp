#ifndef boxcar_server_hpp
#define boxcar_server_hpp

// Standard Library
#include <string>

// Boost Libraries
#include <boost/asio.hpp>

// Local Includes
#include "RequestHandler.hpp"
#include "ConnectionManager.hpp"

namespace BoxCar {
namespace Http {
class Server {
  public:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    /**
     * Construct the server to listen on the specified TCP address and port, and
     * serve up files from the given directory.
     */
    explicit Server(const std::string& address,
                    const std::string& port,
                    const std::string& doc_root);

    /// Run the server's io_context loop.
    void run();

  private:
    /// Perform an asynchronous accept operation.
    void do_accept();

    /// Wait for a Request to stop the server.
    void do_await_stop();

    /// The io_context used to perform asynchronous operations.
    boost::asio::io_context ioContext;

    /// The signal_set is used to register for process termination
    /// notifications.
    boost::asio::signal_set signals;

    /// Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor acceptor;

    /// The connection manager which owns all live connections.
    ConnectionManager connectionManager;

    /// The handler for all incoming requests.
    RequestHandler requestHandler;
};
}
}

#endif
