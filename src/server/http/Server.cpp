#include "Server.hpp"

namespace BoxCar {
namespace Http {

Server::Server(const std::string& address,
               const std::string& port,
               const std::string& doc_root)
  : ioContext(1)
  , signals(this->ioContext)
  , acceptor(this->ioContext)
  , connectionManager()
  , requestHandler(doc_root) {
    this->signals.add(SIGINT);
    this->signals.add(SIGTERM);

#if defined(SIGQUIT)
    this->signals.add(SIGQUIT);
#endif

    do_await_stop();

    boost::asio::ip::tcp::resolver resolver(this->ioContext);
    boost::asio::ip::tcp::endpoint endpoint =
      *resolver.resolve(address, port).begin();
    this->acceptor.open(endpoint.protocol());
    this->acceptor.set_option(
      boost::asio::ip::tcp::acceptor::reuse_address(true));
    this->acceptor.bind(endpoint);
    this->acceptor.listen();

    do_accept();
}

void
Server::run() {
    this->ioContext.run();
}

void
Server::do_accept() {
    this->acceptor.async_accept([this](boost::system::error_code ec,
                                       boost::asio::ip::tcp::socket socket) {
        if (!this->acceptor.is_open())
            return;
        if (!ec)
            this->connectionManager.start(
              std::make_shared<Connection>(std::move(socket),
                                           this->connectionManager,
                                           this->requestHandler));
        do_accept();
    });
}

void
Server::do_await_stop() {
    this->signals.async_wait(
      [this](boost::system::error_code /*ec*/, int /*signo*/) {
          // The server is stopped by cancelling all outstanding asynchronous
          // operations. Once all operations have finished the io_context::run()
          // call will exit.
          this->acceptor.close();
          this->connectionManager.stopAll();
      });
}

}
}