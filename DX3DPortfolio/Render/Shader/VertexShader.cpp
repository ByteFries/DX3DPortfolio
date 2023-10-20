#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring key)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile
    (
        key.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "vs_5_0",
        flags,
        0,
        &_blob,
        nullptr
    );

    DEVICE->CreateVertexShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_vShader);

    CreateInputLayout();
}

VertexShader::~VertexShader()
{
	_vShader->Release();
	_reflection->Release();
	_inputLayout->Release();
}

void VertexShader::CreateInputLayout()
{
    D3DReflect(_blob->GetBufferPointer(), _blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&_reflection);

    D3D11_SHADER_DESC shaderDesc;
    _reflection->GetDesc(&shaderDesc);

    vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        _reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        //Mask : ¿ä¼ÒÀÇ °¹¼ö
        if (paramDesc.Mask == 1)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask <= 15)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string semantic = paramDesc.SemanticName;

        if (semantic == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        inputLayouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout
    (
        inputLayouts.data(),
        inputLayouts.size(),
        _blob->GetBufferPointer(),
        _blob->GetBufferSize(),
        &_inputLayout
    );
}

void VertexShader::SetShader()
{
	DC->IASetInputLayout(_inputLayout);

	DC->VSSetShader(_vShader, nullptr, 0);
}
