struct TestInput {
    float2 position : POSITION;
    float3 colour : COLOR;
};

struct TestOutput {
    float4 position : SV_Position;
    float3 colour : COLOR;
};

TestOutput main(TestInput input){
    TestOutput output;
    output.position = float4(input.position, 0.0f, 1.0f);
    output.colour = input.colour;
    return output;
}
