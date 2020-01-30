#include "Dependency.hpp"

BoxCar::Dependency::Dependency() {
    Dependency("", "latest");
}

BoxCar::Dependency::Dependency(std::string name, std::string version) {
    this->name = name;
    this->version = version;
}

void BoxCar::Dependency::setName(std::string newName) {
    this->name = newName;
}

void BoxCar::Dependency::setVersion(std::string newVersion) {
    this->version = newVersion;
}

std::string BoxCar::Dependency::getVersion() {
    return this->version;
}

std::string BoxCar::Dependency::getName() {
    return this->name;
}

std::vector<BoxCar::Dependency> BoxCar::Dependency::getSubDependencies() {
    return this->subDependencies;
}

void BoxCar::Dependency::addSubDependency(const Dependency& dependency) {
    this->subDependencies.push_back(dependency);
}

void BoxCar::Dependency::readFromPropertyTree(const boost::property_tree::ptree& pt) {
    this->setName(pt.get<std::string>("name"));
    this->setVersion(pt.get<std::string>("version"));
}

void BoxCar::Dependency::readFromJsonString(const std::string& json) {
    std::stringstream stream;
    stream << json;

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(stream, pt);

    this->readFromPropertyTree(pt);
}

void BoxCar::Dependency::readFromJsonFile(const std::string& filePath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(filePath, pt);

    this->readFromPropertyTree(pt);
}