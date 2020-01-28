#ifndef boxcar_package_h
#define boxcar_package_h

typedef struct sVersion {
    int major;
    int minor;
    int patch;
} Version;

typedef struct sDependency {
    char* name;
    Version version;
} Dependency;

typedef struct sPackage {
    char* name;
    Version version;
    Dependency* dependencies;
} Package;

#endif
