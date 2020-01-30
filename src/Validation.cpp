#include "Validation.hpp"

bool BoxCar::Validation::validateVersion(const std::string& version) {
    boost::regex versionExpr {"\\d\\.\\d(\\.\\d)?"};
    return boost::regex_match(version, versionExpr);
}

bool BoxCar::Validation::validateName(const std::string& name) {
    boost::regex nameExpr {"[\\w.-]+"};
    return boost::regex_match(name, nameExpr);
}
