#include <private_api_RI/SGRVertexProperty.h>
#include <SGRGraphicsLanguageType.h>

SGRVertexProperty::SGRVertexProperty(int vertexBufferObjectIndex, int offsetFromVertexStart, int shaderDeclaredLocation, SGRGraphicsLanguageType::Type propertyType, int vectorLength){
    (*this).vertexBufferObjectIndex = vertexBufferObjectIndex;
    (*this).offsetFromVertexStart = offsetFromVertexStart;
    (*this).shaderDeclaredLocation = shaderDeclaredLocation;
    (*this).propertyType = propertyType;
    (*this).vectorLength = vectorLength;
}
