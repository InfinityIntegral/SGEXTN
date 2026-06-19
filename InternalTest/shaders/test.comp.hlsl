RWStructuredBuffer<float> dataBuffer : register(u0);

[numthreads(64, 1, 1)]
void main(uint3 dispatchThreadID : SV_DispatchThreadID){
    uint index = dispatchThreadID.x;
    dataBuffer[index] = dataBuffer[index] * 2.0f;
}
