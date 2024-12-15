#pragma once
namespace LightData
{
	enum LightType
	{
		POINT_LIGHT = 0,
		DIRECTIONAL_LIGHT = 1,
		SPOT_LIGHT = 2,
		CAPSULE_LIGHT = 3
	};

	struct Data
	{
		LightType type = DIRECTIONAL_LIGHT;
		Vector3 direction = { 0, -1, 0 };

		XMFLOAT4 color = { 1,1,1,1 };

		Vector3 position = Vector3(0, 100, 0);
		float range = 100.0f;

		float inner = 55.0f;
		float outer = 70.0f;
		float length = 50.0f;
		int active = true;
	};

	const static int MAX_LIGHT = 10;

	struct LightBuffer : public ConstantBuffer
	{

		LightBuffer()
			:ConstantBuffer(&data, sizeof(data))
		{
			data.lights[0].direction = { 0,-1,1 };
			data.lights[0].position = Vector3(0, 10, 0);
			data.lights[0].type = POINT_LIGHT;
			data.lights[0].active = true;
			data.lightCount = 1;
		}

		~LightBuffer() {}

		struct Data
		{
			LightData::Data lights[MAX_LIGHT];
			int lightCount;
			Vector3 ambientLight = Vector3(0.1f, 0.1f, 0.1f);
			Vector3 ambientCeil = Vector3(0.1f, 0.1f, 0.1f);
			int padding;
		} data;
	};
}