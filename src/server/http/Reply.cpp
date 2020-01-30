#include "Reply.hpp"
#include <string>
#include <numeric>

namespace BoxCar {
namespace Http {

StatusData statusDataSet[] = {
  { "200", "OK" },
  { "201", "Created" },
  { "202", "Accepted" },
  { "204", "No Content" },
  { "300", "Multiple Choices" },
  { "301", "Moved Permanently" },
  { "302", "Moved Temporarily" },
  { "304", "Not Modified" },
  { "400", "Bad Request" },
  { "401", "Unauthorized" },
  { "403", "Forbidden" },
  { "404", "Not Found" },
  { "500", "Internal Server Error" },
  { "501", "Not Implemented" },
  { "502", "Bad Gateway" },
  { "503", "Service Unavailable" },
};

namespace MiscStrings {

const char nameValueSeparator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

}

std::vector<boost::asio::const_buffer>
Reply::toBuffers() {
    std::vector<boost::asio::const_buffer> buffers;

    // It was worth a shot...
//    std::stringstream ss;
//    ss << "HTTP/1.0 " << std::to_string(statusDataSet[(int)this->status].code) << " "
//       << statusDataSet[(int)this->status].message;

    buffers.push_back(boost::asio::buffer("HTTP/1.1 "));
    buffers.push_back(boost::asio::buffer(statusDataSet[(int)this->status].code));
    buffers.push_back(boost::asio::buffer(" "));
    buffers.push_back(boost::asio::buffer(statusDataSet[(int)this->status].message));
    buffers.push_back(boost::asio::buffer(MiscStrings::crlf));
    for (std::size_t i = 0; i < headers.size(); ++i) {
        Header& h = headers[i];
        buffers.push_back(boost::asio::buffer(h.name));
        buffers.push_back(boost::asio::buffer(MiscStrings::nameValueSeparator));
        buffers.push_back(boost::asio::buffer(h.value));
        buffers.push_back(boost::asio::buffer(MiscStrings::crlf));
    }

    buffers.push_back(boost::asio::buffer(MiscStrings::crlf));
    buffers.push_back(boost::asio::buffer(content));
    return buffers;
}

Reply
Reply::stockReply(StatusType status) {
    Reply rep;
    rep.status = status;

    std::stringstream ss;
    ss << "<html><head><title>" << statusDataSet[(int)status].message
       << "</title></head><body><h1>" << statusDataSet[(int)status].code << " "
       << statusDataSet[(int)status].message << "</h1></body></html>";

    rep.content = ss.str();
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/html";
    return rep;
}

}
}
