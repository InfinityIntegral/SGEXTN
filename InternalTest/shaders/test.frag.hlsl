struct TestInput {
    float4 position : SV_Position;
    float3 colour : COLOR;
};

float4 main(TestInput input) : SV_Target {
    return float4(input.colour, 1.0f);
}
