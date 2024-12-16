#include "framework.h"
#include "EditorScene.h"

EditorScene::EditorScene()
{
	//ModelExporter exporter = ModelExporter("lightBulb");
	//exporter.ExportModel();

	//model = ModelFactory::CreateStaticModel("lightBulb");
	//model->SetAllShader(L"TextureLight");

	transform = new Transform();
	transform->_scale /= 50.0f;
	transform->_rotation.x = -XM_PIDIV2;
	sphere = new TextureSphere(1, 10, 10, L"_Texture/Terrain/floor_brick_tiled.png");

	brick = new BrickPlatform({5,1,5});

	sky = new SkySphere(500, 20, 20, L"_Texture/Terrain/sky_background.png");

	light = LIGHT->CreateLight();
	
	instanceDatas.resize(MAX_INSTANCE_COUNT);

	for (float x = 0; x < 5; x++)
	{
		for (float y = 0; y < 6; y++)
		{
			XMMATRIX matrix = XMMatrixTranslation(2 * x, 2 * y, 1);
			instanceDatas[x + y * 5] = new InstanceMatrixData(XMMatrixTranspose(matrix));
		}
	}
	
	render = new ColorQuad({ 1,1 }, {1,0,0,1}, new InstancedRenderer(new InstanceBuffer(instanceDatas), 30));

}

EditorScene::~EditorScene()
{
	delete render;
	delete sphere;
	delete brick;

	delete transform;
	delete model;

	delete sky;
	delete light;

	delete renderer;
}   

void EditorScene::Update()
{
	sky->Update();
	sphere->Update();
	brick->Update();
	light->Update();
	transform->Update();
	render->Update();
}

void EditorScene::PreRender()
{
}

void EditorScene::Render()
{
	brick->Render();
	sky->Render();
	render->Render();
}

void EditorScene::PostRender()
{
}

void EditorScene::Debug()
{
	sky->Debug();
	light->Debug();
}
