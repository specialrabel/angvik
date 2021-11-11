#pragma once
#include "enemy.h"

class npc : public enemy
{
private:

public:

	npc() {};
	~npc() {};

	virtual HRESULT init(const char* imageName, POINT position);
	virtual void update();
	virtual void move();
	virtual void render();
};

