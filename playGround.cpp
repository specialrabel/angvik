#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	_title = new title;
	_stage1 = new stage1;
	_stage1->Link_Title(_title);
	
	SCENEMANAGER->addScene("타이틀", _title);
	SCENEMANAGER->addScene("스테이지 1", _stage1);

	SCENEMANAGER->changeScene("타이틀");

	///////링크


	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();

}

void playGround::render()
{
	D2DMANAGER->BeginDraw();

	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	SCENEMANAGER->render();

	//==================================================
	//여기도 건들지마라

	D2DMANAGER->EndDraw();
}
