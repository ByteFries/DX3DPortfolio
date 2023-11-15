#pragma once

#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDC()

#define CAMERA Camera::Get()

#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Time::Get()->Delta() 

#define MAX_BONE 256
#define MAX_FRAME_KEY 512