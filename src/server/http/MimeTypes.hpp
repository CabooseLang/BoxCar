#ifndef boxcar_mimetypes_hpp
#define boxcar_mimetypes_hpp

#include <string>

typedef struct {
    const char* extension;
    const std::string mime_type;
} Mapping;

extern Mapping mappings[];

std::string
extensionToMimeType(const std::string& extension);

#endif
