/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN/SingEmbed/private_api/SingEmbedFileRegistrarInstance.h>
#include <SGEXTN/CoreText/String.h>
#include <SGEXTN/SingEmbed/private_api/EmbeddedFile.h>
#include <SGEXTN/Containers/EqualTo.h>
#include <SGEXTN/Containers/Hash.h>
#include <SGEXTN/Containers/UnorderedMap.h>
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/CoreText/Character.h>

namespace {
SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance testInstance("/SGEXTN/SingEmbed/testFile.sg", 0, "");
}

SGEXTN::Containers::UnorderedMap<SGEXTN::CoreText::String, SGEXTN::SingEmbed::EmbeddedFile, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>* SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry = nullptr;

SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::SingEmbedFileRegistrarInstance(const SGEXTN::CoreText::String& virtualPath, int fileSize, const char* data){
    if(SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry == nullptr){
        SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry = new SGEXTN::Containers::UnorderedMap<SGEXTN::CoreText::String, SGEXTN::SingEmbed::EmbeddedFile, SGEXTN::Containers::EqualTo<SGEXTN::CoreText::String>, SGEXTN::Containers::Hash<SGEXTN::CoreText::String>>();
    }
    const bool x = (*SGEXTN::SingEmbed::SingEmbedFileRegistrarInstance::registry).insert(SGEXTN::CoreText::String(SGEXTN::CoreText::Character()) + virtualPath, SGEXTN::SingEmbed::EmbeddedFile(data, fileSize));
    if(x == false){SGEXTN_IMMEDIATE_CRASH("SingEmbed initialisation crashed because 2 different files were added to the same path in the virtual file system, ensure that your assets and shader files do not have the same name");}
}
