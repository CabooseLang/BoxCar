#include <stdlib.h>
#include <stdio.h>

#include "libs/cJSON.h"

#include "package.h"
#include "util.h"
#include "log.h"

void initPackage(Package* package, const char* name, Ref version) {
    package->isPrivate = false;

    DependencyArray dependencies;
    initDependencyArray(&dependencies);

    package->dependencies = dependencies;
    package->name = name;
    package->version = version;
}

void initPackageFromFile(Package* package, const char* fileName) {
    char* jsonText = readFile(fileName);

    // Parse the JSON into a JSON object
    cJSON* jsonObject = cJSON_Parse(jsonText);

    // If null it had an error
    if (jsonObject == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) fprintf(stderr, "Error parsing boxcar.json before: %s\n", error_ptr);
    }
    
    // Parse name.
    cJSON* nameObject = cJSON_GetObjectItemCaseSensitive(jsonObject, "name");

    // Name must be a string.
    if (cJSON_IsString(nameObject)) package->name = nameObject->string;
    else {
        logErr("'name' field in boxcar.json must be a string.");
        exit(1);
    }


    // Parse version.
    cJSON* versionObject = cJSON_GetObjectItemCaseSensitive(jsonObject, "version");

    // Version must be a string.
    if (cJSON_IsString(nameObject)) package->version = nameObject->string;
    else {
        logErr("'version' field in boxcar.json must be a string.");
        exit(1);
    }

    DependencyArray dependencies;
    initDependencyArray(&dependencies);

    package->dependencies = dependencies;

    cJSON* dependenciesObject = cJSON_GetObjectItemCaseSensitive(jsonObject, "dependencies");
    if (cJSON_IsArray(dependenciesObject)) {
        cJSON* dependencyObject = NULL;

        cJSON_ArrayForEach(dependencyObject, dependenciesObject) {
            Dependency dependency;

            // Parse dependency name
            cJSON* dependencyNameObject = cJSON_GetObjectItemCaseSensitive(dependencyObject, "name");

            // Dependency name must be a string
            if (cJSON_IsString(dependencyNameObject)) dependency.name = dependencyNameObject->string;
            else {
                logErr("'name' field in boxcar.json dependency must be a string.");
                exit(1);
            }
            
            // Parse dependency version
            cJSON* dependencyVersionObject = cJSON_GetObjectItemCaseSensitive(dependencyObject, "version");

            // Dependency version must be a string.
            if (cJSON_IsString(dependencyVersionObject)) dependency.name = dependencyVersionObject->string;
            else {
                logErr("'version' field in boxcar.json dependency must be a string.");
                exit(1);
            }
        }
    }
}
