#include "framework.h"
#include "Cat.h"

Cat::Cat()
	:Actor("test")
{
	_mesh = new SkeletalMesh("test");

	SkeletalMesh* mesh = dynamic_cast<SkeletalMesh*>(_mesh);

	if (mesh)
	{
		_animManager = new AnimManager(mesh);
	
		_animManager->AddAnimation(_name, "test0", 0, 0);
		_animManager->AddAnimation(_name, "Running0", 0, 0);
		_animManager->CreateTexture();
		_animManager->SetTarget(this);
		_animManager->PlaySequence(State::IDLE, 1.0f, 1.0f);
	
		_wBuffer->SetAnimation(true);
	}
}

Cat::~Cat()
{
	delete _mesh;
	delete _animManager;
}

void Cat::Update()
{
	//KeyInput();

	//Physics();

	if (KEY_PRESS('Y'))
	{
		_animManager->PlaySequence(State::WALK, 0.2f, 0.2f);
	}

	Actor::Update();
}

void Cat::Render()
{
	Actor::Render();
}

void Cat::Physics()
{
	_jumpPower -= DELTA * 4.0f;

	if (_jumpMax < _jumpPower)
		_jumpPower = _jumpMax;

	_translation.y += _jumpPower;
}

void Cat::Debug()
{
	if (ImGui::TreeNode(_name.c_str()))
	{
		Transform::Debug();

		_animManager->Debug();

		ImGui::TreePop();
	}

}

void Cat::KeyInput()
{
	if (KEY_PRESS(VK_RBUTTON))
		return;

	//Move();

	_speed = 0;
	bool walk = false;
	bool keyPress[4] = { false, false, false, false };

	if (KEY_PRESS('W'))
	{
		PlayClip(WALK);
		_speed = 10.0f;
		keyPress[0] = true;
		walk = true;
		_rotation.y = MAIN_CAMERA->_rotation.y;
	}
	else if (KEY_DOWN('W'))
	{
		PlayClip(WALK);
		_speed = 10.0f;
		walk = true;
		keyPress[0] = true;
	}
	else if (KEY_UP('W'))
	{
	}

	if (KEY_PRESS('A'))
	{
		PlayClip(WALK);
		_speed = 10.0f;
		keyPress[1] = true;
		walk = true;
		_rotation.y = MAIN_CAMERA->_rotation.y + XM_PI + XM_PIDIV2;
	}
	else if (KEY_DOWN('A'))
	{
		PlayClip(WALK);
		walk = true;
		keyPress[1] = true;
	}
	else if (KEY_UP('A'))
	{
		_speed = 10.0f;
	}

	if (KEY_PRESS('S'))
	{
		_speed = 10.0f;
		PlayClip(WALK);
		keyPress[2] = true;
		walk = true;
		_rotation.y = MAIN_CAMERA->_rotation.y + XM_PI;
	}
	else if (KEY_DOWN('S'))
	{
		_speed = 10.0f;
		walk = true;
		PlayClip(WALK);
		keyPress[2] = true;
	}
	else if (KEY_UP('S'))
	{
	}

	if (KEY_PRESS('D'))
	{
		_speed = 10.0f;
		PlayClip(WALK);
		keyPress[3] = true;
		walk = true;
		Vector3 right = MAIN_CAMERA->Right();
		_rotation.y = MAIN_CAMERA->_rotation.y + XM_PIDIV2;
	}
	else if (KEY_DOWN('D'))
	{
		_speed = 10.0f;
		walk = true;
		PlayClip(WALK);
		keyPress[3] = true;
	}
	else if (KEY_UP('D'))
	{
	}

	_translation += _forward * _speed * DELTA;

	//if (KEY_DOWN(VK_SPACE))
	//{
	//	if (_state != JUMP)
	//		_jumpPower = 1.0f;
	//
	//	PlayClip(JUMP);
	//}
	//
	//if (_state != JUMP && !walk)
	//	PlayClip(IDLE);
}

void Cat::Move()
{
	_speed = 0;
	bool updateRot = false;
	bool keyPress[4] = {false, false, false, false};

	if (KEY_PRESS('W'))
	{
		PlayClip(WALK);
		_speed = 10.0f;
		keyPress[0] = true;
		_rotation.y = MAIN_CAMERA->_rotation.y;
	}
	else if (KEY_DOWN('W'))
	{
		PlayClip(WALK);
		_speed = 10.0f;
		updateRot = true;
		keyPress[0] = true;
	}
	else if (KEY_UP('W'))
	{
		updateRot = true;
	}

	if (KEY_PRESS('A'))
	{
		PlayClip(WALK);
		_speed = 10.0f;
		keyPress[1] = true;
		_rotation.y = MAIN_CAMERA->_rotation.y + XM_PI + XM_PIDIV2;
	}
	else if (KEY_DOWN('A'))
	{
		PlayClip(WALK);
		updateRot = true;
		keyPress[1] = true;
	}
	else if (KEY_UP('A'))
	{
		_speed = 10.0f;
		updateRot = true;
	}

	if (KEY_PRESS('S'))
	{
		_speed = 10.0f;
		PlayClip(WALK);
		keyPress[2] = true;
		_rotation.y = MAIN_CAMERA->_rotation.y + XM_PI;
	}
	else if (KEY_DOWN('S'))
	{
		_speed = 10.0f;
		updateRot = true;
		PlayClip(WALK);
		keyPress[2] = true;
	}
	else if (KEY_UP('S'))
	{
		updateRot = true;
	}

	if (KEY_PRESS('D'))
	{
		_speed = 10.0f;
		PlayClip(WALK);
		keyPress[3] = true;
		Vector3 right = MAIN_CAMERA->Right();
		_rotation.y = MAIN_CAMERA->_rotation.y + XM_PIDIV2;
	}
	else if (KEY_DOWN('D'))
	{
		_speed = 10.0f;
		updateRot = true;
		PlayClip(WALK);
		keyPress[3] = true;
	}
	else if (KEY_UP('D'))
	{
		updateRot = true;
	}

	_translation += _forward * _speed * DELTA;

	//////function//////
	/*if (updateRot)
	{
		float left, right, angle;

		if (keyPress[0])
		{
			if (keyPress[1])
				angle = (XM_2PI - XM_PIDIV4);
			else if (keyPress[3])
				angle = XM_PIDIV4;
			else
				angle = 0;
		}
		else if (keyPress[2])
		{
			if (keyPress[1])
				angle = XM_PI + XM_PIDIV4;
			else if (keyPress[3])
				angle = XM_PI - XM_PIDIV4;
			else
				angle = XM_PI;
		}
		else if (keyPress[1])
		{
			angle = XM_PI + XM_PIDIV2;
		}
		else if (keyPress[3])
		{
			angle = XM_PIDIV2;
		}
		else return;

		right = abs(_rotation.y - angle);
		left = abs((_rotation.y + XM_2PI) - angle);

		if (left < right)
		{
			_rotAngle = left;
			_curRotation = _rotation.y + XM_2PI;
		}
		else
		{
			_rotAngle = right;
			_curRotation = _rotation.y;
		}
	}

	if (_rotAngle != FLT_MAX)
	{
		_rotation.y = LERP(_curRotation, _rotAngle, 0.5f);
		_rotTime += DELTA;

		if (_rotation.y - _rotAngle < FLT_EPSILON)
		{
			_rotAngle = FLT_MAX;
			_rotTime = 0.0f;
		}
	}*/
}
