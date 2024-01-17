#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#pragma comment(lib, "ImGui.lib")


#pragma comment(lib, "DirectXTex.lib")
#include "DirectXTex.h"
#include "DirectXTex.inl"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp.lib")

using namespace std;
using namespace DirectX;

#include "Utility\Utility.h"
#include "Utility\Singleton.h"
#include "System\Device.h"
#include "Math\Vector3.h"
#include "Utility\Time.h"
#include "Utility\Keyboard.h"
#include "Utility\BinaryReader.h"
#include "Utility\BinaryWriter.h"

#include "Render\State\RasterizerState.h"

#include "Defines.h"

#include "Render\Buffer\ConstantBuffer.h"
#include "Render\Buffer\GlobalBuffer.h"
#include "Render\Buffer\VertexBuffer.h"
#include "Render\Buffer\IndexBuffer.h"
#include "Render\Buffer\VertexLayout.h"
#include "Render\Buffer\StructuredBuffer.h"

#include "Render\Shader\Shader.h"
#include "Render\Shader\VertexShader.h"
#include "Render\Shader\PixelShader.h"
#include "Render\Shader\ComputeShader.h"

#include "Render\Texture\Texture.h"
#include "Render\Material.h"

#include "Render\ModelPart.h"
#include "Render\Mesh.h"
#include "Render\StaticMesh.h"
#include "Render\SkeletalMesh.h"

#include "Render\State\RasterizerState.h"
#include "Render\State\SamplerState.h"
#include "Render\State\StateManager.h"

#include "Render\View\DepthStencil.h"
#include "Render\View\RenderTarget.h"

#include "Actor\Transform.h"

#include "Collider\Collider.h"
#include "Collider\ColliderSphere.h"
#include "Collider\ColliderBox.h"

#include "Actor\Basic\Quad.h"
#include "Actor\Basic\Cube.h"
#include "Actor\Basic\TextureCube.h"
#include "Actor\Basic\Sphere.h"

#include "ModelExport\ModelType.h"
#include "ModelExport\ModelExporter.h"

#include "Actor\Model\ModelReader.h"

#include "Actor\Actor.h"
#include "Actor\ActorInstancing.h"

#include "Animation\AnimSequence.h"
#include "Animation\AnimManager.h"

#include "Actor\Model\Cat.h"
#include "Actor\Model\Enemy\Watcher.h"

#include "Actor\Terrain\Terrain.h"

#include "System\Camera.h"
#include "System\CameraManager.h"
#include "System\Environment.h"

#include "Scene\Scene.h"

#include "Program.h"

extern HWND hWnd;
extern Vector3 mousePos;
extern Vector3 mouseDir;
extern bool mouseFocus;