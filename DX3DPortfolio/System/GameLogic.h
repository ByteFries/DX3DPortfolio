#pragma once
class GameLogic : public Singleton<GameLogic>
{
	friend class Singleton;
public:
	void Update();
	
	void Debug();


private:
	UINT _coinCount = 0;
	bool _gameOver = false;

};

