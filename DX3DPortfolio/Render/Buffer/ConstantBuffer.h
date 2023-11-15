#pragma once
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT size);
	~ConstantBuffer();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);
	void SetCSBuffer(UINT slot);
	
	void UpdateSubresource();

private:
	ID3D11Buffer* _cBuffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	void* _data;
	UINT _size;
};

