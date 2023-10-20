struct VertexOutput
{
    float4 position : SV_POSITION;
};


float4 main() : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}