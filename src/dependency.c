#include "dependency.h"
#include "log.h"
#include "common.h"
#include "memory.h"

void installAllDependencies() {
    logInf("Installing Dependencies");
}

void installDependency() {

}

void initDependency(Dependency* dependency, const char* name, Ref version) {
    dependency->name = name;
    dependency->version = version;
}

void initDependencyArray(DependencyArray* array) {
    array->capacity = 0;
    array->count = 0;
    array->values = NULL;
}

void writeDependencyArray(DependencyArray* array, Dependency dependency) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values =
          GROW_ARRAY(array->values, Dependency, oldCapacity, array->capacity);
    }

    array->values[array->count] = dependency;
    array->count++;
}