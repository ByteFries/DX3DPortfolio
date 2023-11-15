cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
    matrix invView;
}

cbuffer Projection : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 cameraDir : CAMERA_DIRECTION;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

VertexOutput main(VertexInput input)
{
    VertexOutput result;
    
    result.pos = mul(input.pos, world);
    
    float3 cameraPos= invView._41_42_43;
    result.cameraDir = normalize(result.pos.xzy - cameraPos);
    
    result.pos = mul(result.pos, view);   
    result.pos = mul(result.pos, projection);
    
    result.uv = input.uv;
    
    result.normal = normalize(mul(input.normal, (float3x3)world));
    
    result.tangent = normalize(mul(input.tangent, (float3x3) world));
    
    result.binormal = cross(result.normal, result.tangent);
    
	return result;
}