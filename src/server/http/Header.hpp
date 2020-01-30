//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef boxcar_header_hpp
#define boxcar_header_hpp

#include <string>

namespace BoxCar {
namespace Http {

struct Header {
    std::string name;
    std::string value;
};

}
}

#endif
