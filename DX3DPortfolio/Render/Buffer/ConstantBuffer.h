#pragma once
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);

	virtual ~ConstantBuffer();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

	void UpdateSubresource();


private:
	ID3D11Buffer* _buffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	void* _data;
	UINT _dataSize;
};

