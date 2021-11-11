#pragma once
#include "gameNode.h"
#include "title.h"
#include "stage1.h"
#include "player.h"
#include "bird.h"

class playGround : public gameNode
{
private:
	title* _title;
	stage1* _stage1;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

