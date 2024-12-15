#pragma once

#define MAX_KEY 256

enum KeyState
{
	NONE,
	DOWN,
	UP,
	PRESS
};

class Keyboard : public Singleton<Keyboard>
{
	friend class Singleton;

	Keyboard();
	~Keyboard();

public:
	void Update();

	bool Down(char key);
	bool Press(char key);
	bool Up(char key);

private:

	unsigned char _keyCurState[MAX_KEY];
	unsigned char _keyOldState[MAX_KEY];
	unsigned char _keyMap[MAX_KEY];
};

