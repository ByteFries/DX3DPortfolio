#pragma once

#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDC()

#define CAMERA CameraManager::Get()
#define MAIN_CAMERA CameraManager::Get()->GetMainCamera()

#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Time::Get()->Delta() 

#define MAX_BONE 256
#define MAX_FRAME_KEY 512

#define MAX_LIGHT 10

#define LERP(S, E, T) (S * (1 - T) + E * T)

#define UP_VECTOR Vector3(0.0f, +1.0f, 0.0f)

#define RIGHT_VECTOR Vector3(+1.0f, 0.0f, 0.0f)

#define FORWARD_VECTOR Vector3(0.0f, +1.0f, 0.0f)

#define MAX_INSTANCE 128