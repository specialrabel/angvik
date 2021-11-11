#pragma once
#include "enemy.h"

class fish : public enemy
{
private:
	int jump_count;

public:

	virtual HRESULT init(const char* imageName, POINT position);
	virtual void update();
	virtual void move();
	virtual void render();

	virtual void set_top(float len);
	virtual void set_direction(int len);
};

