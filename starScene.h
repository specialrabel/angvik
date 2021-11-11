#pragma once
#include "gameNode.h"
#include "ship.h"
#include "action.h"

class battle;

class starScene : public gameNode
{
private:
	ship* _battle;

	action* _action;
	image* _actionImage;
	
public:
	starScene();
	~starScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

