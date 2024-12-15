struct VertexOutput
{
    float4 pos : SV_Position;
};

float4 main(VertexOutput input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}