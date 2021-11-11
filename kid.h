#pragma once
#include "enemy.h"

class kid : public enemy
{
private:
	bool is_jump;

public:
	virtual HRESULT init(const char* imageName, POINT position, int direction);
	virtual void update();
	virtual void move();
	virtual void render();
};

