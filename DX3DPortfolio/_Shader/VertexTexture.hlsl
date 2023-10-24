cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Projection : register(b2)
{
    matrix proj;
}

struct VertexInputput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

VertexOutput main(VertexInputput input)
{
    VertexOutput result;
    
    result.pos = mul(input.pos, world);
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, proj);
    
    result.uv = input.uv;
    
	return result;
}