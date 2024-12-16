// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "_Others/targetver.h"
#define WIN32_LEAN_AND_MEAN     

#include <windows.h>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <functional>
#include <algorithm>

#include <cstdlib>
#include <ctime>  

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <Shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#include "DirectXTex\DirectXTex.h"
#include "DirectXTex\DirectXTex.inl"

#pragma comment(lib, "DirectXTex.lib")

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_win32.h"
#include "ImGui\imgui_impl_dx11.h"

#pragma comment(lib, "ImGui.lib")

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp.lib")

using namespace std;
using namespace DirectX;

#include "Defines.h"

#include "Utility\Vector2.h"
#include "Utility\Vector3.h"
#include "Utility\Vector4.h"
#include "Utility\Matrix3x3.h"
#include "Utility\Quaternion.h"
#include "Utility\Singleton.h"
#include "Utility\Observer.h"
#include "Utility\Observable.h"

#include "Utility\Utility.h"

#include "Utility\BinaryWriter.h"
#include "Utility\BinaryReader.h"

#include "Render\VertexLayout.h"

#include "System\Device.h"

#include "Render\Buffer\ConstantBuffer.h"
#include "Render\Buffer\Buffers.h"
#include "Render/Buffer/DXBuffer.h"
#include "Render\Buffer\VertexBuffer.h"
#include "Render\Buffer\IndexBuffer.h"

#include "Actor\Transform.h"

#include "Render\Shader\Shader.h"
#include "Render\Shader\VertexShader.h"
#include "Render\Shader\PixelShader.h"

#include "Render\Texture\Texture.h"

#include "Model_IO\ModelData.h"
#include "Model_IO\ModelExporter.h"
#include "Model_IO\ModelReader.h"

#include "Render\Material\Material.h"

#include "Render\Mesh\MeshBase.h"
#include "Render\Mesh\StaticMesh.h"
#include "Render\Mesh\SkeletalMesh.h"


#include "Physics\Collision\Shape\Shape.h"
#include "Physics\Collision\Shape\SphereShape.h"
#include "Physics\Collision\Shape\BoxShape.h"
#include "Physics\Collision\Shape\CapsuleShape.h"

#include "Physics\PhysicsCoefficientProvider.h"
#include "Physics\PhysicalObject\PhysicalObject.h"

#include "Physics\Collision\BroadPhase\BroadTypes.h"
#include "Physics\Collision\BroadPhase\AABBManager.h"

#include "Physics\Collision\NarrowPhase\CollisionDetection\Simplex.h"
#include "Physics\Collision\NarrowPhase\CollisionDetection\CollisionDetectionInterface.h"
#include "Physics\Collision\NarrowPhase\CollisionDetection\GJK_EPA.h"
#include "Physics\Collision\NarrowPhase\CollisionDetection\SphereSphereDetection.h"
#include "Physics\Collision\NarrowPhase\CollisionDetection\SphereConvexDetection.h"
#include "Physics\Collision\NarrowPhase\CollisionDetection\GJK_EPA2.h"

#include "Physics\Collision\NarrowPhase\ContactPoint\ContactPointFinderInterface.h"
#include "Physics\Collision\NarrowPhase\ContactPoint\ClippingContactPoint.h"
#include "Physics\Collision\NarrowPhase\ContactPoint\EdgeFaceContactPoint.h"
#include "Physics\Collision\NarrowPhase\ContactPoint\SphereSphereContactPoint.h"
#include "Physics\Collision\NarrowPhase\ContactPoint\SphereConvexContactPoint.h"

#include "Physics\Collision\NarrowPhase\CollisionManager.h"

#include "Physics\Collision\SequentialImpulseSolver.h"
#include "Physics\PhysicalCalculator\PhysicalCalculator.h"
#include "Physics\PhysicalCalculator\CalculatorStatic.h"
#include "Physics\PhysicalCalculator\CalculatorLinearBasic.h"
#include "Physics\PhysicalCalculator\CalculatorAngularBasic.h"
#include "Physics\PhysicalCalculator\CalculatorLABasic.h"

#include "System\Manager\PhysicsManager.h"

#include "Render\OpticalEffects\LightData.h"
#include "Render\OpticalEffects\Light.h"
#include "System\Manager\LightManager.h"

#include "Render\Model\ModelInterface.h"
#include "Render\Model\ModelBase.h"
#include "Render\Model\SkeletalModel.h"
#include "Render\Model\StaticModel.h"
#include "Render\Model\ModelFactory.h"

#include "Render\Renderer\InstanceDatas.h"
#include "Render/Buffer/InstanceBuffer.h"

#include "Render\Renderer\RendererUpdateComponent.h"
#include "Render\Renderer\PerObjectUpdate.h"
#include "Render\Renderer\InstancingUpdate.h"

#include "Render\Renderer\RendererInterface.h"
#include "Render\Renderer\PerObjectRenderer.h"
#include "Render\Renderer\InstancedRenderer.h"

#include "Render/RenderResource/RenderResource.h"

#include "Render\RenderableObject\RenderableObject.h"
#include "Render\RenderableObject\MeshRO.h"
#include "Render\RenderableObject\ModelRO.h"

#include "Render\Shape\ColorShape\ColorShapeRenderer.h"
#include "Render\Shape\ColorShape\ColorQuad.h"
#include "Render\Shape\ColorShape\ColorCube.h"
#include "Render\Shape\ColorShape\ColorSphere.h"

#include "Render\Shape\TextureShape\TextureShapeRenderer.h"
#include "Render\Shape\TextureShape\TextureQuad.h"
#include "Render\Shape\TextureShape\TextureCube.h"
#include "Render\Shape\TextureShape\TextureSphere.h"

#include "Actor\Actor.h"

#include "Actor\Model\MainCharactor\Bunny.h"

#include "Actor\Terrain\SkySphere.h"
#include "Actor\Terrain\TerrainQuad.h"
#include "Actor\Terrain\PlatformBase.h"
#include "Actor\Terrain\BrickPlatform.h"


#include "Render\State\BlendState.h"
#include "Render\State\SamplerState.h"
#include "Render\State\RasterizerState.h"
#include "Render\State\DepthStencilState.h"
#include "System\Manager\StateManager.h"


#include "Utility\Time.h"
#include "Utility\Keyboard.h"

#include "Scene\Scene.h"
#include "System\Manager\SceneManager.h"

#include "System\Environment.h"
#include "System\Camera.h"

#include "System\Manager\CameraManager.h"

#include "Program.h"


extern HWND hWnd;
extern Vector3 mousePos;