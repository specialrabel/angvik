#include "stdafx.h"
#include "starScene.h"
#include "battle.h"


starScene::starScene()
{
}


starScene::~starScene()
{
}

HRESULT starScene::init()
{
	_battle = new battle;
	_battle->init("battle", WINSIZEX / 2, WINSIZEY / 2);

	_action = new action;
	_action->init();

	_actionImage = IMAGEMANAGER->findImage("º¼");
	_actionImage->setX(WINSIZEX / 2);
	_actionImage->setY(WINSIZEY / 2);

	_action->moveTo(_actionImage, 50, 50, 1.0f);

	return S_OK;
}

void starScene::release()
{
}

void starScene::update()
{
	_battle->update();
	_action->update();
}

void starScene::render()
{
	IMAGEMANAGER->findImage("¹ÙÅÁ")->render(getMemDC());

	_battle->render();

	_actionImage->render(getMemDC(), _actionImage->getX(), _actionImage->getY());
}
