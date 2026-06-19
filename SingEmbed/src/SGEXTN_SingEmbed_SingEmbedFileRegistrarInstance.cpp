#include <private_api/SGEXTN_SingEmbed_SingEmbedFileRegistrarInstance.h>
#include <SGEXTN_CoreText_String.h>
#include <private_api/SGEXTN_SingEmbed_EmbeddedFile.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_UnorderedMap.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_CoreText_Character.h>

namespace {
SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance testInstance("/SGEXTN/SingEmbed/testFile.sg", 0, "");
}

constinit SGEXTN::Containers::UnorderedMap<SGEXTN::CoreText::String, SGEXTN::SingEmbed::EmbeddedFile, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>* SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry = nullptr;

SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::SingEmbedFileRegistrarInstance(const SGEXTN::CoreText::String& virtualPath, int fileSize, const char* data){
    if(SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry == nullptr){
        SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry = new SGEXTN::Containers::UnorderedMap<SGEXTN::CoreText::String, SGEXTN::SingEmbed::EmbeddedFile, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>();
    }
    const bool x = (*SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry).insert(SGEXTN::CoreText::String(SGEXTN::CoreText::Character()) + virtualPath, SGEXTN::SingEmbed::EmbeddedFile(data, fileSize));
    if(x == false){SGEXTN_IMMEDIATE_CRASH("SingEmbed initialisation crashed because 2 different files were added to the same path in the virtual file system, ensure that your assets and shader files do not have the same name");}
}
