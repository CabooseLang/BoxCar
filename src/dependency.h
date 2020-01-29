#ifndef boxcar_dependency_h
#define boxcar_dependency_h

#include "ref.h"

/**
 * A dependency object.
 * @author RailRunner16
 */
typedef struct sDependency {
    char* name;
    Ref version;
} Dependency;

/**
 * A dependency array.
 * @author RailRunner16
 */
typedef struct sDependencyArray {
    int capacity;
    int count;
    Dependency* values;
} DependencyArray;

/**
 * Install a single dependency.
 * @param dependency The dependency to install.
 */
void installDependency();

/**
 * Install all dependencies specified in the boxcar.json in the current directory.
 */
void installAllDependencies();

/**
 * Initialize a new dependency object.
 * @param dependency The dependency to initialize.
 * @param name The name of the dependency.
 * @param version The version of the dependency.
 */
void initDependency(Dependency* dependency, const char* name, Ref version);

/**
 * Initialize a new dependency array.
 * @param array The dependency array to initialize.
 */
void initDependencyArray(DependencyArray* array);

/**
 * Add a dependency to a dependency array.
 * @param array The array to add the dependency to.
 * @param dependency The dependency to add.
 */
void writeDependencyArray(DependencyArray* array, Dependency dependency);

#endif
