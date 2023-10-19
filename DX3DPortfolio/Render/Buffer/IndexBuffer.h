#pragma once
class IndexBuffer
{
public:
	IndexBuffer(vector<UINT>& indices);
	~IndexBuffer();

	void IASetBuffer();

private:
	ID3D11Buffer* _buffer;
	D3D11_MAPPED_SUBRESOURCE _subresource;
};

