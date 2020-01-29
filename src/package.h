#ifndef boxcar_package_h
#define boxcar_package_h

#include "dependency.h"
#include "common.h"

/**
 * A package object.
 * @author RailRunner16
 */
typedef struct sPackage {
    char* name;
    Ref version;
    Dependency* dependencies;
    bool isPrivate;
} Package;

/**
 * Initialize a package object.
 * @param package The package object to initialize.
 * @param name The name of the package.
 * @param version The version of the package.
 */
void initPackage(Package* package, const char* name, Ref version);

/**
 * Initialize a package object using a boxcar.json file.
 * @param package The package object to initialize.
 * @param fileName The path of the file to pull data from when initializing the package object.
 */
void initPackageFromFile(Package* package, const char* fileName);

#endif
