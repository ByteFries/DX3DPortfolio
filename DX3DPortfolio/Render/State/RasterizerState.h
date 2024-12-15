#pragma once
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState();
	void ChangeState(D3D11_FILL_MODE mod);
	void FrontCounterClockWise(bool val);

private:
	ID3D11RasterizerState* _rasterizerState;
	D3D11_RASTERIZER_DESC _dsc = {};

};

