cbuffer MaterialBuffer : register(b1)
{
    float4 diffuseColor;
    float4 specularColor;
    float4 ambientColor;
    
    int hasDiffuse;
    int hasSpecular;
    int hasNormal;
    int shininess;
}

struct VertexOutput
{
    float4 pos : SV_POSITION;
};

float4 main(VertexOutput input) : SV_TARGET
{
    return diffuseColor;
}