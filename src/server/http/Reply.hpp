#ifndef boxcar_reply_hpp
#define boxcar_reply_hpp

#include "Header.hpp"
#include <boost/asio.hpp>
#include <string>
#include <vector>

namespace BoxCar {
namespace Http {

typedef struct {
    std::string code;
    std::string message;
} StatusData;

extern StatusData statusDataSet[];

enum class StatusType {
    OK,
    CREATED,
    ACCEPTED,
    NO_CONTENT,
    MULTIPLE_CHOICES,
    MOVED_PERMANENTLY,
    MOVED_TEMPORARILY,
    NOT_MODIFIED,
    BAD_REQUEST,
    UNAUTHORIZED,
    FORBIDDEN,
    NOT_FOUND,
    INTERNAL_SERVER_ERROR,
    NOT_IMPLEMENTED,
    BAD_GATEWAY,
    SERVICE_UNAVAILABLE,
};

/// A Reply to be sent to a client.
struct Reply {
    /// The status of the Reply.
    StatusType status;

    /// The headers to be included in the Reply.
    std::vector<Header> headers;

    /// The content to be sent in the Reply.
    std::string content;

    /// Convert the Reply into a vector of buffers. The buffers do not own the
    /// underlying memory blocks, therefore the Reply object must remain valid
    /// and not be changed until the write operation has completed.
    std::vector<boost::asio::const_buffer> toBuffers();

    /// Get a stock Reply.
    static Reply stockReply(StatusType status);
};

}
}

#endif
