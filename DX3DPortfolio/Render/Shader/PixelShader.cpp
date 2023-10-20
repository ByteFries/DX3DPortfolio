#include "framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring key)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


    D3DCompileFromFile
    (
        key.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "ps_5_0",
        flags,
        0,
        &_blob,
        nullptr
    );

    DEVICE->CreatePixelShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_pShader);

}

PixelShader::~PixelShader()
{
    _pShader->Release();
}

void PixelShader::SetShader()
{
    DC->PSSetShader(_pShader, nullptr, 0);
}
