#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	_title = new title;
	_stage1 = new stage1;
	_stage1->Link_Title(_title);
	
	SCENEMANAGER->addScene("Ÿ��Ʋ", _title);
	SCENEMANAGER->addScene("�������� 1", _stage1);

	SCENEMANAGER->changeScene("Ÿ��Ʋ");

	///////��ũ


	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
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

	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();

	//==================================================
	//���⵵ �ǵ�������

	D2DMANAGER->EndDraw();
}
