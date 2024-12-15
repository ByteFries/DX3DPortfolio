struct VertexOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

float4 main(VertexOutput input) : SV_TARGET
{
    return input.color;
}