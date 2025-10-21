#ifndef SGRVERTEXPROPERTY_H
#define SGRVERTEXPROPERTY_H

#include "sgrgraphicslanguagetype.h"

class SGRVertexProperty
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
