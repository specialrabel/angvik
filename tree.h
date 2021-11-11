#pragma once
#include "enemy.h"

class tree : public enemy
{
private:

public:
	tree() {};
	~tree() {};

	virtual HRESULT init(const char* imageName, POINT position);
	virtual void update();
	virtual void move();
	virtual void render();
};

