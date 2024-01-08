#pragma once
class BlendSpace
{
public:
	enum State
	{
		IDLE,
		WALK,
		JUMP
	};

	BlendSpace();
	~BlendSpace();

	void Update();

	void AddClip(string clipName);

private:
	State _state;

	FrameBuffer* _frameBuffer;


	ID3D11Texture2D* _animationTexture;
	ID3D11ShaderResourceView* _srv;
};