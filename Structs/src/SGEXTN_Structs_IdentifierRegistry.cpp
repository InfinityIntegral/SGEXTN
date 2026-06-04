#include <SGEXTN_Structs_IdentifierRegistry.h>
#include <SGEXTN_ApplicationBase_Random.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Structs_Identifier.h>

SGEXTN::Structs::Identifier SGEXTN::Structs::IdentifierRegistry::generateAndRegisterIdentifier(){
    while(true){
        const unsigned int n = SGEXTN::ApplicationBase::Random::unsignedInt32();
        if(n != 0u && private_contents.contains(n) == false){
            SGEXTN::Structs::Identifier id;
            id.private_data = n;
            private_contents.insert(n);
            return id;
        }
    }
}

SGEXTN::Structs::Identifier SGEXTN::Structs::IdentifierRegistry::parseAndRegisterIdentifier(unsigned int data, bool* isValid){
    SGEXTN::Structs::Identifier id;
    id.private_data = data;
    if(isValid != nullptr){
        if(data == 0u || private_contents.contains(data) == true){(*isValid) = false;}
        else{(*isValid) = true;}
    }
    if(data != 0u){private_contents.insert(data);}
    return id;
}

bool SGEXTN::Structs::IdentifierRegistry::unregister(SGEXTN::Structs::Identifier id){
    if(id.private_data == 0u){return false;}
    return private_contents.erase(id.private_data);
}

bool SGEXTN::Structs::IdentifierRegistry::contains(SGEXTN::Structs::Identifier id) const {
    if(id.private_data == 0u){return false;}
    return private_contents.contains(id.private_data);
}