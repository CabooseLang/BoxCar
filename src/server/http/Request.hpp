#ifndef boxcar_request_hpp
#define boxcar_request_hpp

#include "Header.hpp"
#include <string>
#include <vector>

namespace BoxCar {
namespace Http {

/// A Request received from a client.
struct Request {
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
};

}
}

#endif
