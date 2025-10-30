#ifndef SGRVERTEXPROPERTY_H
#define SGRVERTEXPROPERTY_H

#include <SGRGraphicsLanguageType.h>

#include <private_api_RI/SG_Build_RI.h>

class SG_RI_DLL SGRVertexProperty
{
public:
    SGRVertexProperty(int vertexBufferObjectIndex, int offsetFromVertexStart, int shaderDeclaredLocation, SGRGraphicsLanguageType::Type propertyType, int vectorLength);
    SGRVertexProperty() = default;
    int vertexBufferObjectIndex;
    int offsetFromVertexStart;
    int shaderDeclaredLocation;
    SGRGraphicsLanguageType::Type propertyType;
    int vectorLength;
};

#endif // SGRVERTEXPROPERTY_H
