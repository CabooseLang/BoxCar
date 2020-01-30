#include "Package.hpp"
#include "Logger.hpp"
#include "Validation.hpp"

#include <boost/foreach.hpp>
#include <boost/regex.hpp>

//
// Constructors & Destructors
//

BoxCar::Packaging::Package::Package(std::string name) {
    this->name = name;
}

BoxCar::Packaging::Package::Package() {
    Package("");
}

//
// Getters & Setters
//

void BoxCar::Packaging::Package::setName(std::string newName) {
    this->name = newName;
}

void BoxCar::Packaging::Package::setVersion(std::string newVersion) {
    this->version = newVersion;
}

std::string BoxCar::Packaging::Package::getName() {
    return this->name;
}

std::string BoxCar::Packaging::Package::getVersion() {
    return this->version;
}

std::vector<BoxCar::Packaging::Dependency> BoxCar::Packaging::Package::getDependencies() {
    return this->dependencies;
}

//
// Data Methods
//

void BoxCar::Packaging::Package::readFromPropertyTree(const boost::property_tree::ptree& pt) {
    this->name = pt.get<std::string>("name");
    this->version = pt.get<std::string>("version");

    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, pt.get_child("dependencies")) {
        Dependency dependency;
        dependency.readFromPropertyTree(v.second);

        this->dependencies.push_back(dependency);
    }
}

void BoxCar::Packaging::Package::readFromJsonString(const std::string &json) {
    std::stringstream stream;
    stream << json;

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(stream, pt);

    this->readFromPropertyTree(pt);
}

void BoxCar::Packaging::Package::readFromJsonFile(const std::string& filePath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(filePath, pt);

    this->readFromPropertyTree(pt);
}

void BoxCar::Packaging::Package::installAllDependencies() {
    std::stringstream installingAllStream;
    installingAllStream << "Installing all dependencies of package " << this->name << "@" << this->version << "...";

    BoxCar::Logging::Logger::inf(installingAllStream.str());

    BOOST_FOREACH(Dependency& dependency, this->dependencies) {
        std::stringstream installMessageStream;
        installMessageStream << "Installing " << dependency.getName() << "@" << dependency.getVersion() << "...";

        BoxCar::Logging::Logger::inf(installMessageStream.str());
    }
}

BoxCar::Packaging::PackageValidity BoxCar::Packaging::Package::validate() {
    if (!BoxCar::Validation::validateName(this->name)) return PackageValidity {
        false,
        "'name' field must only contain alphanumeric characters, underscores, hyphens, and periods."
    };

    if (!BoxCar::Validation::validateVersion(this->version)) return PackageValidity {
        false,
        "'version' field must be a valid version (x.x.x)."
    };

    BOOST_FOREACH(Dependency& dependency, this->dependencies) {
        if (!BoxCar::Validation::validateName(dependency.getName())) return PackageValidity {
            false,
            "'name' field of dependency must only contain alphanumeric characters, underscores, hyphens, and periods."
        };

        if (!BoxCar::Validation::validateVersion(dependency.getVersion())) return PackageValidity {
            false,
            "'version' field of dependency must be a valid version (x.x.x)."
        };
    }

    return PackageValidity {
        true,
        ""
    };
}