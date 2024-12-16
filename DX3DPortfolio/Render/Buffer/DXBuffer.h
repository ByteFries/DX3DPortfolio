#pragma once
class DXBuffer
{
public:
	DXBuffer() {}
	virtual ~DXBuffer();

	virtual void Update(void* data, UINT size) abstract;

	virtual	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) abstract;

protected:
	ID3D11Buffer* _buffer;
	UINT _stride = 0;
	UINT _offset = 0;
	UINT _bufferSize = 0;
};

