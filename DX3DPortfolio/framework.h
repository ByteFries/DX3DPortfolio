#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

using namespace std;
using namespace DirectX;

#include "Utility\Singleton.h"
#include "System\Device.h"
#include "Math\Vector3.h"

#include "Defines.h"

#include "Render\Buffer\ConstantBuffer.h"
#include "Render\Buffer\GlobalBuffer.h"
#include "Render\Buffer\VertexBuffer.h"
#include "Render\Buffer\IndexBuffer.h"
#include "Render\Buffer\VertexLayout.h"

#include "Render\Mesh.h"

#include "Render\Shader\Shader.h"
#include "Render\Shader\VertexShader.h"
#include "Render\Shader\PixelShader.h"

#include "Render\Material.h"

#include "Object\Transform.h"
#include "Object\Basic\Cube.h"


#include "Scene\Scene.h"

#include "Program.h"


extern HWND hWnd;