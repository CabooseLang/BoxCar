#include "Package.hpp"
#include "Logger.hpp"

#include <boost/foreach.hpp>

//
// Constructors & Destructors
//

BoxCar::Package::Package(std::string name) {
    this->name = name;
}

BoxCar::Package::Package() {
    Package("");
}

//
// Getters & Setters
//

void BoxCar::Package::setName(std::string newName) {
    this->name = newName;
}

void BoxCar::Package::setVersion(std::string newVersion) {
    this->version = newVersion;
}

std::string BoxCar::Package::getName() {
    return this->name;
}

std::string BoxCar::Package::getVersion() {
    return this->version;
}

std::vector<BoxCar::Dependency> BoxCar::Package::getDependencies() {
    return this->dependencies;
}

//
// Data Methods
//

void BoxCar::Package::readFromPropertyTree(const boost::property_tree::ptree& pt) {
    this->name = pt.get<std::string>("name");
    this->version = pt.get<std::string>("version");

    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, pt.get_child("dependencies")) {
        Dependency dependency;
        dependency.readFromPropertyTree(v.second);

        this->dependencies.push_back(dependency);
    }
}

void BoxCar::Package::readFromJsonString(const std::string &json) {
    std::stringstream stream;
    stream << json;

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(stream, pt);

    this->readFromPropertyTree(pt);
}

void BoxCar::Package::readFromJsonFile(const std::string& filePath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(filePath, pt);

    this->readFromPropertyTree(pt);
}

void BoxCar::Package::installAllDependencies() {
    BoxCar::Logging::Logger::inf("Installing all dependencies...");

    BOOST_FOREACH(Dependency& dependency, this->dependencies) {
        std::stringstream installMessageStream;
        installMessageStream << "Installing " << dependency.getName() << "@" << dependency.getVersion() << "...";

        BoxCar::Logging::Logger::inf(installMessageStream.str());
    }
}