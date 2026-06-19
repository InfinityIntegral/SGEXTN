#pragma once

namespace SGEXTN {
namespace SingEmbed {
class BuildLah_SGEXTN_SingEmbed EmbeddedFile {
public:
    EmbeddedFile(const char* data, int length);
    const char* data;
    int length;
};
}
}
