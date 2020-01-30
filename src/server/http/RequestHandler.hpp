#ifndef boxcar_requesthandler_hpp
#define boxcar_requesthandler_hpp

#include <string>

namespace BoxCar {
namespace Http {

struct Reply;
struct Request;

/// The common handler for all incoming requests.
class RequestHandler {
  public:
    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;

    /// Construct with a directory containing files to be served.
    explicit RequestHandler(const std::string& docRoot);

    /// Handle a request and produce a reply.
    void handleRequest(const Request& req, Reply& rep);

  private:
    /// The directory containing the files to be served.
    std::string docRoot;

    /// Perform URL-decoding on a string. Returns false if the encoding was
    /// invalid.
    static bool urlDecode(const std::string& in, std::string& out);
};

}
}

#endif
