cbuffer SkyBuffer : register(b10)
{
    float3 centerColor;
    float height;
    
    float3 apexColor;
}

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float3 originPos : POSITION;
};

float4 main(VertexOutput input) : SV_TARGET
{
    float y = saturate(input.originPos.y * height);
    
    float3 result = lerp(centerColor, apexColor, y);

    return float4(result, 1.0f);

}