#include "MimeTypes.hpp"

Mapping mappings[] = {
    { "gif", "image/gif" },  { "htm", "text/html" }, { "html", "text/html" },
    { "jpg", "image/jpeg" }, { "png", "image/png" },
};

std::string
extensionToMimeType(const std::string& extension) {
    for (Mapping m : mappings)
        if (m.extension == extension)
            return m.mime_type;
    return "text/plain";
}
