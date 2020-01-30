//
// ConnectionManager.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef boxcar_connectionmanager_hpp
#define boxcar_connectionmanager_hpp

#include "Connection.hpp"
#include <set>

namespace BoxCar {
namespace Http {

/// Manages open connections so that they may be cleanly stopped when the server
/// needs to shut down.
class ConnectionManager {
  public:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    /// Construct a connection manager.
    ConnectionManager();

    /// Add the specified connection to the manager and start it.
    void start(connection_ptr c);

    /// Stop the specified connection.
    void stop(connection_ptr c);

    /// Stop all connections.
    void stopAll();

  private:
    /// The managed connections.
    std::set<connection_ptr> connections;
};

}
}

#endif
