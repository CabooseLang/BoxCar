#include <stdlib.h>
#include <stdio.h>

#include "libs/cJSON.h"

#include "package.h"
#include "util.h"
#include "log.h"

void initPackage(Package* package, const char* name, Ref version) {
    package->isPrivate = false;
    package->dependencies = NULL;
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

    package->dependencies = NULL;

    cJSON* dependenciesObject = cJSON_GetObjectItemCaseSensitive(jsonObject, "dependencies");
    if (cJSON_IsArray(dependenciesObject)) {
        cJSON* dependencyObject = NULL;

        cJSON_ArrayForEach(dependencyObject, dependenciesObject) {
            Dependency dependency;

            cJSON* dependencyNameObject = cJSON_GetObjectItemCaseSensitive(dependencyObject, "name");
            
            if (cJSON_IsString(dependencyNameObject)) dependency.name = dependencyNameObject->string;
        }
    }
}
