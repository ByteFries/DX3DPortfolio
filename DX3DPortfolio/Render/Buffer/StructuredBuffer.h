#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount);
	~StructuredBuffer();

	void Copy(void* data, UINT size);
	void UpdateInput(void* data);

	ID3D11UnorderedAccessView* GetUAV() { return _uav; }
	ID3D11ShaderResourceView* GetSRV() { return _srv; }

	void SetSRV();
	void SetUAV();

private:
	void CreateInput();
	void CreateOutput();
	void CreateSRV();
	void CreateUAV();
	void CreateResult();

	ID3D11UnorderedAccessView* _uav;
	ID3D11ShaderResourceView* _srv;

	ID3D11Resource* _input;
	ID3D11Resource* _output;
	ID3D11Resource* _result;

	void* _inputData;
	UINT _inputStride;
	UINT _inputCount;

	UINT _outputStride;
	UINT _outputCount;
};

