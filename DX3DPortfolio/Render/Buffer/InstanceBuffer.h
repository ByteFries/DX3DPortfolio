#pragma once
class InstanceBuffer : public DXBuffer
{
public:

	InstanceBuffer(vector<InstanceDataBase*>& datas);
	~InstanceBuffer();

	void Update(void* data, UINT size) override;
	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

private:

	D3D11_MAPPED_SUBRESOURCE _subresource;
};