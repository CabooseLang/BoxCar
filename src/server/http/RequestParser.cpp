#include "RequestParser.hpp"
#include "Request.hpp"

namespace BoxCar {
namespace Http {

RequestParser::RequestParser()
  : state(State::METHOD_START) {}

void
RequestParser::reset() {
    this->state = State::METHOD_START;
}

RequestParser::ResultType
RequestParser::consume(Request& req, char input) {
    switch (this->state) {
        case METHOD_START:
            if (!isChar(input) || isCtl(input) || isTspecial(input)) return ResultType::BAD;
            else {
                this->state = METHOD;
                req.method.push_back(input);
                return ResultType::INDETERMINATE;
            }
        case METHOD:
            if (input == ' ') {
                this->state = URI;
                return ResultType::INDETERMINATE;
            } else if (!isChar(input) || isCtl(input) || isTspecial(input)) return ResultType::BAD;
            else {
                req.method.push_back(input);
                return ResultType::INDETERMINATE;
            }
        case URI:
            if (input == ' ') {
                this->state = HTTP_VERSION_H;
                return ResultType::INDETERMINATE;
            } else if (isCtl(input)) return ResultType::BAD;
            else {
                req.uri.push_back(input);
                return ResultType::INDETERMINATE;
            }
        case HTTP_VERSION_H:
            if (input == 'H') {
                this->state = HTTP_VERSION_T_1;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_T_1:
            if (input == 'T') {
                this->state = HTTP_VERSION_T_2;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_T_2:
            if (input == 'T') {
                this->state = HTTP_VERSION_P;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_P:
            if (input == 'P') {
                this->state = HTTP_VERSION_SLASH;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_SLASH:
            if (input == '/') {
                req.http_version_major = 0;
                req.http_version_minor = 0;
                this->state = HTTP_VERSION_MAJOR_START;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_MAJOR_START:
            if (isDigit(input)) {
                req.http_version_major = req.http_version_major * 10 + input - '0';
                this->state = HTTP_VERSION_MAJOR;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_MAJOR:
            if (input == '.') {
                this->state = HTTP_VERSION_MINOR_START;
                return ResultType::INDETERMINATE;
            } else if (isDigit(input)) {
                req.http_version_major = req.http_version_major * 10 + input - '0';
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_MINOR_START:
            if (isDigit(input)) {
                req.http_version_minor = req.http_version_minor * 10 + input - '0';
                this->state = HTTP_VERSION_MINOR;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HTTP_VERSION_MINOR:
            if (input == '\r') {
                this->state = EXPECTING_NEWLINE_1;
                return ResultType::INDETERMINATE;
            } else if (isDigit(input)) {
                req.http_version_minor = req.http_version_minor * 10 + input - '0';
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case EXPECTING_NEWLINE_1:
            if (input == '\n') {
                this->state = HEADER_LINE_START;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HEADER_LINE_START:
            if (input == '\r') {
                this->state = EXPECTING_NEWLINE_3;
                return ResultType::INDETERMINATE;
            } else if (!req.headers.empty() && (input == ' ' || input == '\t')) {
                this->state = HEADER_LWS;
                return ResultType::INDETERMINATE;
            } else if (!isChar(input) || isCtl(input) || isTspecial(input)) return ResultType::BAD;
            else {
                req.headers.push_back(Header());
                req.headers.back().name.push_back(input);
                this->state = HEADER_NAME;
                return ResultType::INDETERMINATE;
            }
        case HEADER_LWS:
            if (input == '\r') {
                this->state = EXPECTING_NEWLINE_2;
                return ResultType::INDETERMINATE;
            } else if (input == ' ' || input == '\t') return ResultType::INDETERMINATE;
            else if (isCtl(input)) return ResultType::BAD;
            else {
                this->state = HEADER_VALUE;
                req.headers.back().value.push_back(input);
                return ResultType::INDETERMINATE;
            }
        case HEADER_NAME:
            if (input == ':') {
                this->state = SPACE_BEFORE_HEADER_VALUE;
                return ResultType::INDETERMINATE;
            } else if (!isChar(input) || isCtl(input) || isTspecial(input)) return ResultType::BAD;
            else {
                req.headers.back().name.push_back(input);
                return ResultType::INDETERMINATE;
            }
        case SPACE_BEFORE_HEADER_VALUE:
            if (input == ' ') {
                this->state = HEADER_VALUE;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case HEADER_VALUE:
            if (input == '\r') {
                this->state = EXPECTING_NEWLINE_2;
                return ResultType::INDETERMINATE;
            } else if (isCtl(input)) return ResultType::BAD;
            else {
                req.headers.back().value.push_back(input);
                return ResultType::INDETERMINATE;
            }
        case EXPECTING_NEWLINE_2:
            if (input == '\n') {
                this->state = HEADER_LINE_START;
                return ResultType::INDETERMINATE;
            } else return ResultType::BAD;
        case EXPECTING_NEWLINE_3:
            return (input == '\n') ? ResultType::GOOD : ResultType::BAD;
        default:
            return ResultType::BAD;
    }
}

bool
RequestParser::isChar(int c) {
    return c >= 0 && c <= 127;
}

bool
RequestParser::isCtl(int c) {
    return (c >= 0 && c <= 31) || (c == 127);
}

bool
RequestParser::isTspecial(int c) {
    switch (c) {
        case '(':
        case ')':
        case '<':
        case '>':
        case '@':
        case ',':
        case ';':
        case ':':
        case '\\':
        case '"':
        case '/':
        case '[':
        case ']':
        case '?':
        case '=':
        case '{':
        case '}':
        case ' ':
        case '\t':
            return true;
        default:
            return false;
    }
}

bool
RequestParser::isDigit(int c) {
    return c >= '0' && c <= '9';
}

}
}
