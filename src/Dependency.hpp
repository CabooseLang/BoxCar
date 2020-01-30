#ifndef boxcar_dependency_hpp
#define boxcar_dependency_hpp

#include <string>
#include <boost/property_tree/json_parser.hpp>

namespace BoxCar {
namespace Packaging {
/**
 * A dependency object.
 * @author RailRunner16
 */
class Dependency {
  public:
    /**
     * Create a new blank dependency object.
     */
    Dependency();

    /**
     * Create a new dependency object with the given values.
     * @param name The name of the dependency.
     * @param version The dependency's version.
     */
    Dependency(std::string name, std::string version);

    /**
     * Set the name of the dependency.
     * @param newName The new name.
     */
    void setName(std::string newName);

    /**
     * Set the version of this dependency object.
     * @param newVersion The new version.
     */
    void setVersion(std::string newVersion);

    /**
     * Get this dependency's name.
     * @return This dependency's name.
     */
    std::string getName();

    /**
     * Get this dependency's name.
     * @return This dependency's name.
     */
    std::string getVersion();

    /**
     * Get all sub-dependencies of this dependency.
     * @return All of this dependency's sub-dependencies.
     */
    std::vector<Dependency> getSubDependencies();

    /**
     * Add a sub-dependency to this dependency. Do not use this in your code, it is meant for internal use only.
     * @param dependency The dependency to add.
     */
    void addSubDependency(const Dependency& dependency);

    /**
     * Load data into this dependency object from a property tree.
     * @param pt The property tree to read from.
     */
    void readFromPropertyTree(const boost::property_tree::ptree& pt);

    /**
     * Load data into this dependency object from a string of JSON data.
     * @param json The JSON data to read from.
     */
    void readFromJsonString(const std::string& json);

    /**
     * Load data into this dependency object from a JSON file.
     * @param filePath The path of the file to read from.
     */
    void readFromJsonFile(const std::string& filePath);

  private:
    std::string name, version;
    std::vector<Dependency> subDependencies;
};
}
}

#endif
