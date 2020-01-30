#ifndef boxcar_requestparser_hpp
#define boxcar_requestparser_hpp

#include <tuple>

namespace BoxCar {
namespace Http {

struct Request;

/// Parser for incoming requests.
class RequestParser {
  public:
    /// Construct ready to parse the Request method.
    RequestParser();

    /// Reset to initial parser state.
    void reset();

    /// Result of parse.
    enum class ResultType {
        GOOD,
        BAD,
        INDETERMINATE,
    };

    /// Parse some data. The enum return value is good when a complete Request
    /// has been parsed, bad if the data is invalid, indeterminate when more
    /// data is required. The InputIterator return value indicates how much of
    /// the input has been consumed.
    template<typename InputIterator>
    std::tuple<ResultType, InputIterator> parse(Request& req,
                                                InputIterator begin,
                                                InputIterator end) {
        while (begin != end) {
            ResultType result = consume(req, *begin++);
            if (result == ResultType::GOOD || result == ResultType::BAD)
                return std::make_tuple(result, begin);
        }
        return std::make_tuple(ResultType::INDETERMINATE, begin);
    }

  private:
    /// Handle the next character of input.
    ResultType consume(Request& req, char input);

    /// Check if a byte is an HTTP character.
    static bool isChar(int c);

    /// Check if a byte is an HTTP control character.
    static bool isCtl(int c);

    /// Check if a byte is defined as an HTTP tspecial character.
    static bool isTspecial(int c);

    /// Check if a byte is a digit.
    static bool isDigit(int c);

    /// The current state of the parser.
    enum State {
        METHOD_START,
        METHOD,
        URI,
        HTTP_VERSION_H,
        HTTP_VERSION_T_1,
        HTTP_VERSION_T_2,
        HTTP_VERSION_P,
        HTTP_VERSION_SLASH,
        HTTP_VERSION_MAJOR_START,
        HTTP_VERSION_MAJOR,
        HTTP_VERSION_MINOR_START,
        HTTP_VERSION_MINOR,
        EXPECTING_NEWLINE_1,
        HEADER_LINE_START,
        HEADER_LWS,
        HEADER_NAME,
        SPACE_BEFORE_HEADER_VALUE,
        HEADER_VALUE,
        EXPECTING_NEWLINE_2,
        EXPECTING_NEWLINE_3
    } state;
};

}
}

#endif
