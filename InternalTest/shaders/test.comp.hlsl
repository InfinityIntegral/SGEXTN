RWByteAddressBuffer dataBuffer : register(u0);

[numthreads(64, 1, 1)]
void main(uint3 dispatchThreadID : SV_DispatchThreadID){
    uint index = dispatchThreadID.x;
    dataBuffer.Store(index * 4, 0.0f);
}
