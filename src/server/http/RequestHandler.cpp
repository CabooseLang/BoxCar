#include "RequestHandler.hpp"
#include "MimeTypes.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

namespace BoxCar {
namespace Http {

RequestHandler::RequestHandler(std::string docRoot)
  : docRoot(std::move(docRoot)) {}

void
RequestHandler::handleRequest(const Request& req, Reply& rep) {
    // Decode url to path.
    std::string requestPath;
    if (!urlDecode(req.uri, requestPath)) {
        rep = Reply::stockReply(StatusType::BAD_REQUEST);
        return;
    }

    // Request path must be absolute and not contain "..".
    if (requestPath.empty() || requestPath[0] != '/' ||
        requestPath.find("..") != std::string::npos) {
        rep = Reply::stockReply(StatusType::BAD_REQUEST);
        return;
    }

    // If path ends in slash (i.e. is a directory) then add "index.html".
    if (requestPath[requestPath.size() - 1] == '/')
        requestPath += "index.html";

    // Determine the file extension.
    std::size_t last_slash_pos = requestPath.find_last_of('/');
    std::size_t last_dot_pos = requestPath.find_last_of('.');
    std::string extension;

    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
        extension = requestPath.substr(last_dot_pos + 1);

    // Open the file to send back.
    std::string full_path = this->docRoot + requestPath;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        rep = Reply::stockReply(StatusType::NOT_FOUND);
        return;
    }

    // Fill out the Reply to be sent to the client.
    rep.status = StatusType::OK;
    char buf[512];
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        rep.content.append(buf, is.gcount());
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = extensionToMimeType(extension);
}

bool
RequestHandler::urlDecode(const std::string& in, std::string& out) {
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else
                    return false;
            } else
                return false;
        } else if (in[i] == '+')
            out += ' ';
        else
            out += in[i];
    }
    return true;
}

}
}
