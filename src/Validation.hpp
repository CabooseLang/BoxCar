#ifndef boxcar_validation_hpp
#define boxcar_validation_hpp

#include <boost/regex.hpp>

namespace BoxCar {
namespace Validation {
/**
 * Validate a version.
 * @param version The version to validate
 * @return Is the version valid?
 */
bool validateVersion(const std::string& version);

/**
 * Validate a package or dependency name.
 * @param name The name to validate.
 * @return Is the name valid?
 */
bool validateName(const std::string& name);
}
}


#endif
