#include "framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring key)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    ID3DBlob* errorBlob = nullptr;

    HRESULT hr = D3DCompileFromFile
    (
        key.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, //해당 플래그로는 hlsli 안에 hlsli 파일을 include 못 함
        "main",
        "ps_5_0",
        flags,
        0,
        &_blob,
        nullptr
    );
    if (FAILED(hr)) {
        OutputDebugString(L"Shader compilation failed.\n");
        if (errorBlob) {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
        }
    }
    else
    {
        DEVICE->CreatePixelShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_pShader);
    }
}

PixelShader::~PixelShader()
{
    _pShader->Release();
}

void PixelShader::SetShader()
{
    DC->PSSetShader(_pShader, nullptr, 0);
}
