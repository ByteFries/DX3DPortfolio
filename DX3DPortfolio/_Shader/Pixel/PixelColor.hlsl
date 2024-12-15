struct VertexOutput
{
    float4 pos : SV_Position;
};

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

float4 main(VertexOutput input) : SV_TARGET
{
    return color;
}