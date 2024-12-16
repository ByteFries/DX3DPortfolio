#pragma once
//win
#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

//vec
#define UP_VECTOR Vector3(0.0f, 1.0f, 0.0f)
#define RIGHT_VECTOR Vector3(1.0f, 0.0f, 0.0f)
#define FORWARD_VECTOR Vector3(0.0f, 0.0f, 1.0f)

//device
#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

//environment
#define ENVIRONMENT Environment::Get()

//key
#define KEYBOARD Keyboard::Get()
#define KEY_PRESS(k) Keyboard::Get()->Press(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_DOWN(k) Keyboard::Get()->Down(k)

//time
#define TIME Time::Get()
#define DELTA Time::Get()->Delta()

//cam
#define CAMERA CameraManager::Get()
#define MAIN_CAM CameraManager::Get()->GetMainCamera()

//Model_Anim
#define ASSET AssetManager::Get()
#define MAX_BONE 256
#define MAX_FRAME_KEY 512

//state
#define STATE StateManager::Get()
#define RS StateManager::Get()->GetRS()

//physics
#define PHYSICS PhysicsManager::Get()
#define P_DELTA PhysicsManager::Get()->GetDelta()
#define GRAVITY PhysicsManager::Get()->GetGravity()
#define COEFFICIENT PhysicsCoefficientProvider
#define OBJECT_MAX_BIT 15
#define OBJECT_MAX_COUNT 32767

//Light
#define LIGHT LightManager::Get()

//Scene
#define SCENE SceneManager::Get()

//MODEL_IO_PATH
const string MODEL_IO_PATH = "Model_IO/ModelData/";
const string FBX_PATH = "Model_IO/ModelData/FBX/";
const string MESH_FOLDER = "/Mesh/";
const string MESH_LIST_FILE = "MeshList.list";

//instance
#define MAX_INSTANCE_COUNT 30
#define INSTANCE_BUFFER_SLOT 1