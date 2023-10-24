#include "framework.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
    ZeroMemory(_keyCurState,    sizeof(_keyCurState));
    ZeroMemory(_keyOldState, sizeof(_keyOldState));
    ZeroMemory(     _keyMap,      sizeof(_keyMap));
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	memcpy(_keyOldState, _keyCurState, sizeof(_keyCurState));

	ZeroMemory(_keyCurState, sizeof(_keyCurState));
	ZeroMemory(_keyMap, sizeof(_keyMap));

	if (!GetKeyboardState(_keyCurState))
		return;

	for (int i = 0; i < MAX_KEY; i++)
	{
		unsigned char key = _keyCurState[i] & 0x80;
		_keyCurState[i] = key ? 1 : 0;

		unsigned char old = _keyOldState[i];
		unsigned char cur = _keyCurState[i];

		if (old == 0 && cur == 1)
			_keyMap[i] = DOWN;
		else if (old == 1 && cur == 0)
			_keyMap[i] = UP;
		else if (old == 1 && cur == 1)
			_keyMap[i] = PRESS;
		else
			_keyMap[i] = NONE;
	}
}

bool Keyboard::Down(char key)
{
    return _keyMap[key] == DOWN;
}

bool Keyboard::Press(char key)
{
    return _keyMap[key] == PRESS;
}

bool Keyboard::Up(char key)
{
    return _keyMap[key] == UP;
}
