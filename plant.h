#pragma once
#include "enemy.h"

class plant : public enemy
{

public:
	plant() {};
	~plant() {};

	virtual HRESULT init(const char* imageName, POINT position);
	virtual void update();
	virtual void move();
	virtual void render();
};

