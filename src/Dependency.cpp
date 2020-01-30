#include "Dependency.hpp"

BoxCar::Packaging::Dependency::Dependency() {
    Dependency("", "latest");
}

BoxCar::Packaging::Dependency::Dependency(std::string name, std::string version) {
    this->name = name;
    this->version = version;
}

void BoxCar::Packaging::Dependency::setName(std::string newName) {
    this->name = newName;
}

void BoxCar::Packaging::Dependency::setVersion(std::string newVersion) {
    this->version = newVersion;
}

std::string BoxCar::Packaging::Dependency::getVersion() {
    return this->version;
}

std::string BoxCar::Packaging::Dependency::getName() {
    return this->name;
}

std::vector<BoxCar::Packaging::Dependency> BoxCar::Packaging::Dependency::getSubDependencies() {
    return this->subDependencies;
}

void BoxCar::Packaging::Dependency::addSubDependency(const Dependency& dependency) {
    this->subDependencies.push_back(dependency);
}

void BoxCar::Packaging::Dependency::readFromPropertyTree(const boost::property_tree::ptree& pt) {
    this->setName(pt.get<std::string>("name"));
    this->setVersion(pt.get<std::string>("version"));
}

void BoxCar::Packaging::Dependency::readFromJsonString(const std::string& json) {
    std::stringstream stream;
    stream << json;

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(stream, pt);

    this->readFromPropertyTree(pt);
}

void BoxCar::Packaging::Dependency::readFromJsonFile(const std::string& filePath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(filePath, pt);

    this->readFromPropertyTree(pt);
}