#ifndef boxcar_package_hpp
#define boxcar_package_hpp

// Standard Libraries
#include <string>
#include <vector>

// Boost Libraries
#include <boost/property_tree/json_parser.hpp>

// Local Files
#include "Dependency.hpp"

namespace BoxCar {
/**
 * A package object.
 * @author RailRunner16
 */
class Package {
  public:
    //
    // Constructors & Destructors
    //

    /**
     * Create a new package object.
     */
    Package();

    /**
     * Create a new package object with a given name.
     * @param name The name of the package object.
     */
    explicit Package(std::string name);

    //
    // Getters & Setters
    //

    /**
     * Set the name of this package object.
     * @param newName The new name.
     */
    void setName(std::string newName);

    /**
     * Set the version of this package object.
     * @param newVersion The new version.
     */
    void setVersion(std::string newVersion);

    /**
     * Get the name of this package object.
     * @return The name of this package object.
     */
    std::string getName();

    /**
     * Get the version of this package object.
     * @return The version of this package object.
     */
    std::string getVersion();

    /**
     * Get all of this package's dependencies.
     * @return All of this package's dependencies.
     */
    std::vector<Dependency> getDependencies();

    //
    // Data Methods
    //

    /**
     * Load data into this package object from a property tree.
     * @param pt The property tree to read from.
     */
    void readFromPropertyTree(const boost::property_tree::ptree& pt);

    /**
     * Load data into this package object from a string of JSON data.
     * @param json The json data to read from.
     */
    void readFromJsonString(const std::string& json);

    /**
     * Load data into this package object from a JSON file.
     * @param filePath The path to the file to load.
     */
    void readFromJsonFile(const std::string& filePath);

    /**
     * Install all this package object's dependencies
     */
    void installAllDependencies();

  private:
    std::string name, version;
    std::vector<Dependency> dependencies;
};
}

#endif
