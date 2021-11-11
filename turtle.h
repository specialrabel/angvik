#pragma once
#include "enemy.h"

class turtle : public enemy
{
private:

public:
	virtual HRESULT init(const char* imageName, POINT position, int direction);
	virtual void update();
	virtual void move();
	virtual void render();
};

