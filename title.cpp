#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{
	// 배경
	{
		_foreGround.img = new image;
		_foreGround.img->D_Init(L"title/앞배경.png", 1560, 666);

		_backGround = new image;
		_backGround->D_Init(L"title/뒷배경.png", 1560, 666);
	}

	//산 구름
	{
		_mountain1.img = new image;
		_mountain1.img->D_Init(L"title/산1.png", 836, 294);
		_mountain2.img = new image;
		_mountain2.img->D_Init(L"title/산2.png", 1222, 262);
		_mountain3.img = new image;
		_mountain3.img->D_Init(L"title/산3.png", 655, 206);
		_mountain4.img = new image;
		_mountain4.img->D_Init(L"title/산4.png", 703, 146);

		_cloud1.img = new image;
		_cloud1.img->D_Init(L"title/구름1.png", 512, 512);
		_cloud2.img = new image;
		_cloud2.img->D_Init(L"title/구름2.png", 256, 256);
		_cloud3.img = new image;
		_cloud3.img->D_Init(L"title/구름3.png", 256, 256);
		_cloud4.img = new image;
		_cloud4.img->D_Init(L"title/구름4.png", 256, 256);

		_cloud4.rc = D2DMANAGER->RectMake(0, 200, 1560, 256);
		_cloud3.rc = D2DMANAGER->RectMake(0, 230, 1560, 256);
		_cloud2.rc = D2DMANAGER->RectMake(0, 270, 1560, 256);
		_cloud1.rc = D2DMANAGER->RectMake(0, 240, 1560, 512);

	}

	//메인메뉴
	{
		_logo = new image;
		_logo->D_Init(L"title/로고.png", 330, 78);

		_menu.bar = new image;
		_menu.exit = new image;
		_menu.option = new image;
		_menu.sel = new image;
		_menu.start = new image;

		_menu.bar->D_Init(L"title/메뉴바.png", 960, 36);
		_menu.exit->D_Init(L"title/exit.png", 47, 14);
		_menu.option->D_Init(L"title/options.png", 79, 18);
		_menu.start->D_Init(L"title/start.png", 64, 14);
		_menu.sel->D_Init(L"title/선택.png", 1363, 34, 8, 1);

	}

	//옵션
	{
		_op.menu = new image;
		_op.vol = new image;
		_op.music = new image;
		_op.on = new image;
		_op.off = new image;
		_op.back = new image;
		_op.ySel = new image;

		for (int i = 0; i < 5; i++) _op.num[i] = new image;

		_op.menu->D_Init(L"title/옵션메뉴.png", 579, 108);
		_op.vol->D_Init(L"title/volume.png", 70, 14);
		_op.music->D_Init(L"title/music.png", 58, 14);
		_op.on->D_Init(L"title/on.png", 24, 10);
		_op.off->D_Init(L"title/off.png", 30, 15);
		_op.back->D_Init(L"title/back.png", 50, 15);
		_op.ySel->D_Init(L"title/Y선택.png", 60, 35);

		_op.num[0]->D_Init(L"title/0.png", 9, 14);
		_op.num[1]->D_Init(L"title/25.png", 23, 14);
		_op.num[2]->D_Init(L"title/50.png", 22, 14);
		_op.num[3]->D_Init(L"title/75.png", 22, 14);
		_op.num[4]->D_Init(L"title/100.png", 34, 14);
	}

	//직업선택소
	{
		_job.king[0] = new image;
		_job.king[1] = new image;
		_job.lancer[0] = new image;
		_job.lancer[1] = new image;
		_job.shepherd[0] = new image;
		_job.shepherd[1] = new image;
		_job.paladin[0] = new image;
		_job.paladin[1] = new image;
		_job.bottler[0] = new image;
		_job.bottler[1] = new image;
		_job.peasant[0] = new image;
		_job.peasant[1] = new image;
		_job.greatguy[0] = new image;
		_job.greatguy[1] = new image;
		_job.greatguy[2] = new image;
		_job.level = new image;
		_job.yfw = new image;

		_job.king[0]->D_Init(L"title/job/king.png", 131, 184);
		_job.king[1]->D_Init(L"title/job/LKing.png", 51, 18);
		_job.lancer[0]->D_Init(L"title/job/lancer.png", 234, 174);
		_job.lancer[1]->D_Init(L"title/job/LLancer.png", 74, 14);
		_job.shepherd[0]->D_Init(L"title/job/shepherd.png", 131, 193);
		_job.shepherd[1]->D_Init(L"title/job/LShepherd.png", 100, 19);
		_job.paladin[0]->D_Init(L"title/job/paladin.png", 96, 182);
		_job.paladin[1]->D_Init(L"title/job/LPaladin.png", 88, 15);
		_job.bottler[0]->D_Init(L"title/job/bottler.png", 141, 183);
		_job.bottler[1]->D_Init(L"title/job/LBottler.png", 88, 15);
		_job.peasant[0]->D_Init(L"title/job/peasant.png", 125, 192);
		_job.peasant[1]->D_Init(L"title/job/LPeasant.png", 87, 14);
		_job.greatguy[0]->D_Init(L"title/job/greatguy.png", 680, 137, 8, 1);
		_job.greatguy[1]->D_Init(L"title/job/LGreatguy.png", 113, 17);
		_job.greatguy[2]->D_Init(L"title/job/그림자.png", 95, 27);
		_job.level->D_Init(L"title/job/레벨.png", 93, 91, 1, 5);
		_job.yfw->D_Init(L"title/yfw.png", 960, 30);
	}

	_cloud3.loopX = _cloud3.loopY = _cloud2.loopX = _cloud2.loopY = _cloud1.loopX = _cloud1.loopY = 0;

	for (int i = 0; i < 3; i++) _menu.isChoice[i] = 0;
	for (int i = 0; i < 5; i++) _op.isChoiceX[i] = 0;
	for (int i = 0; i < 3; i++) _op.isChoiceY[i] = 0;
	for (int i = 0; i < 8; i++) _job.isChoice[i] = 0;

	_menu.isChoice[0] = _op.isChoiceY[0] = _op.isChoiceX[0] = _job.isChoice[0] = 1;


	_isMain = _isOption = _isStart = 0;
	_index = _count = _jobMax = _numX = _numY = _op.musicNum = _op.volNum = _movement = _isLand = 0;

	cam.x = 1050;
	cam.y = 300;

	_foreGround.x = _foreGround.y = 0;
	_mountain2.x = _mountain3.x = 750;
	_mountain2.y = _mountain3.y = 200;
	_mountain1.x = 500;
	_mountain1.y = 240;
	_bgOpacity = _opacity = 0;

	_foreGround.speed = 0.25f;
	_foreGround.angle = PI / 2;

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	//옵션메뉴
	if (_isOption)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_numX == 0) _numX = 2;
			else _numX -= 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_numX == 2) _numX = 0;
			else _numX += 1;
		}
		for (int i = 0; i < 3; i++) _op.isChoiceY[i] = 0;
		_op.isChoiceY[_numX] = 1;

		if (_op.isChoiceY[0] == 1) //볼륨 선택됐을때
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_op.volNum == 0)  _op.volNum = 4;
				else  _op.volNum -= 1;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_op.volNum == 4)  _op.volNum = 0;
				else  _op.volNum += 1;
			}

			for (int i = 0; i < 5; i++) _op.isChoiceX[i] = 0;
			_op.isChoiceX[_op.volNum] = 1;
		}

		else if (_op.isChoiceY[1] == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_op.musicNum == 0) _op.musicNum = 1;
				else _op.musicNum -= 1;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_op.musicNum == 1) _op.musicNum = 0;
				else _op.musicNum += 1;
			}

			for (int i = 0; i < 2; i++) _op.isChoiceX[i] = 0;
			_op.isChoiceX[_op.musicNum] = 1;
		}
		if (_op.isChoiceY[2] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_isOption = 0;
			_numX = 0;
		}
	}

	//메인메뉴
	if (!_isMain && !_isOption)
	{
		if (_foreGround.x > 0 && !_isLand)
		{
			_foreGround.x -= 5;
			_mountain3.x -= 0.5;
			_mountain2.x -= 1;
			_mountain1.x -= 2;

			if (_foreGround.x < 5)
			{
				_isLand = 1;
				_opacity = 0;
			}
		}
		if (_isLand)
		{
			_opacity += 0.02f;
			_bgOpacity += 0.02f;
			if (_bgOpacity >= 1) {
				if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
				{
					if (_numX == 0) _numX = 2;
					else _numX -= 1;
				}
				if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
				{
					if (_numX == 2) _numX = 0;
					else _numX += 1;
				}
				for (int i = 0; i < 3; i++) _menu.isChoice[i] = 0;

				_menu.isChoice[_numX] = 1;

				if (_menu.isChoice[0] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
				{
					_isMain = 1;
					_isLand = 0;
					_numX = 0;
				}
				if (_menu.isChoice[1] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
				{
					_isOption = 1;
					_numX = 0;
				}
				if (_menu.isChoice[2] == 1)	if (KEYMANAGER->isOnceKeyDown('S'))	PostQuitMessage(0);
			}
		}
	}

	//직업선택소
	if (_isMain)
	{
		if (_foreGround.x < 400 && !_isLand)
		{
			_foreGround.x += 5;
			_mountain3.x += 0.5;
			_mountain2.x += 1;
			_mountain1.x += 2;

			if (_foreGround.x > 395)
			{
				_isLand = 1;
				_opacity = 0;
			}
		}

		if (_isLand && !_isStart)
		{
			_opacity += 0.02f;

			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (_numX == 0) _numX = 7;
				else _numX -= 1;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (_numX == 7) _numX = 0;
				else _numX += 1;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (_numX < 4) _numX += 4;
				else _numX -= 4;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (_numX < 4) _numX += 4;
				else _numX -= 4;
			}

			for (int i = 0; i < 8; i++) _job.isChoice[i] = 0;

			_job.isChoice[_numX] = 1;
			if (_job.isChoice[0] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = KING;
				_isStart = 1;
			}
			if (_job.isChoice[1] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = LANCER;
				_isStart = 1;
			}
			if (_job.isChoice[2] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = SHEPHERD;
				_isStart = 1;
			}
			if (_job.isChoice[3] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = PALADIN;
				_isStart = 1;
			}
			if (_job.isChoice[4] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = BOTTLER;
				_isStart = 1;
			}
			if (_job.isChoice[5] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = PEASANT;
				_isStart = 1;
			}
			if (_job.isChoice[6] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_job.jobNum = GREATGUY;
				_isStart = 1;
			}
			if (_job.isChoice[7] == 1) if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_isMain = 0;
				_isLand = 0;
				_numX = 0;
				_opacity = 0;
			}

		}

		if (_isStart)
		{
			_opacity -= 0.02f;
			_bgOpacity -= 0.02f;
			if (_bgOpacity <= 0)
			{
				SCENEMANAGER->changeScene("스테이지 1");
			}
		}
	}


	_foreGround.x += cosf(_foreGround.angle) * _foreGround.speed;
	_foreGround.y += -sinf(_foreGround.angle) * _foreGround.speed;

	_foreGround.angle -= 0.01f;

	_cloud3.loopX += 1;
	_cloud2.loopX += 1;
	_cloud1.loopX += 1;

	_movement -= 1;
	if (_movement < -10) _movement = 10;

	CAMERAMANAGER->updateScreen(cam.x, cam.y);
}

void title::render()
{
	_backGround->render(0, 0, _bgOpacity); //뒷배경 렌더

	_mountain4.img->render(850, 200, _bgOpacity);
	_mountain4.img->render(400, 200, _bgOpacity);

	_cloud4.img->loopRender(_cloud4.rc, 0, 0, _bgOpacity);

	_mountain3.img->render(_mountain3.x, _mountain3.y, _bgOpacity);

	_cloud3.img->loopRender(_cloud3.rc, _cloud3.loopX, 0, _bgOpacity);

	_mountain2.img->render(_mountain2.x, _mountain2.y, _bgOpacity);

	_cloud2.img->loopRender(_cloud2.rc, _cloud2.loopX, 0, _bgOpacity);

	_mountain1.img->render(_mountain1.x, _mountain1.y, _bgOpacity);

	_cloud1.img->loopRender(_cloud1.rc, _cloud1.loopX, 0, _bgOpacity);

	_foreGround.img->render(_foreGround.x, _foreGround.y, _bgOpacity); //앞배경 렌더

	if (_isOption)
	{
		_op.menu->render(800, 250);

		if (_op.isChoiceY[0] == 1)
		{
			_menu.sel->FrameRender(805, 252, _index, 0);

			if (_op.isChoiceX[0] == 1) _op.ySel->render(1095, 250);
			else if (_op.isChoiceX[1] == 1) _op.ySel->render(1140, 250);
			else if (_op.isChoiceX[2] == 1) _op.ySel->render(1190, 250);
			else if (_op.isChoiceX[3] == 1) _op.ySel->render(1240, 250);
			else if (_op.isChoiceX[4] == 1) _op.ySel->render(1295, 250);
		}
		else if (_op.isChoiceY[1] == 1)
		{
			_menu.sel->FrameRender(805, 288, _index, 0);

			if (_op.isChoiceX[0] == 1) _op.ySel->render(1140, 285);
			else if (_op.isChoiceX[1] == 1) _op.ySel->render(1245, 285);
		}
		else if (_op.isChoiceY[2] == 1) _menu.sel->FrameRender(805, 322, _index, 0);

		_count++;
		if (_count % 5 == 0) _index++;

		if (_index > _menu.sel->getMaxFrameX()) _index = 0;

		_op.vol->render(853, 263);
		_op.music->render(860, 297);
		_op.on->render(1160, 300);
		_op.off->render(1260, 295);
		_op.num[0]->render(1120, 260);
		_op.num[1]->render(1160, 260);
		_op.num[2]->render(1210, 260);
		_op.num[3]->render(1260, 260);
		_op.num[4]->render(1310, 260);
		_op.back->render(863, 330);
	}
	else if (!_isMain)
	{
		if (_isLand) {
			_logo->render(900, 200, _opacity);
			_menu.bar->render(570, 400, _opacity);

			if (_menu.isChoice[0] == 1)		_menu.sel->FrameRender(845, 400, _index, 0, _opacity);
			else if (_menu.isChoice[1] == 1) _menu.sel->FrameRender(1000, 400, _index, 0, _opacity);
			else if (_menu.isChoice[2] == 1) _menu.sel->FrameRender(1140, 400, _index, 0, _opacity);

			_count++;
			if (_count % 5 == 0) _index++;
			if (_index > _menu.sel->getMaxFrameX()) _index = 0;

			_menu.start->render(900, 410, _opacity);
			_menu.option->render(1050, 410, _opacity);
			_menu.exit->render(1200, 410, _opacity);
		}
	}
	else if (_isMain)
	{
		if (_isLand)
		{
			_job.yfw->render(570, 80, _opacity);
			_menu.bar->render(570, 430, _opacity);
			_menu.bar->render(570, 480, _opacity);

			if (_job.isChoice[0] == 1)
			{
				_menu.sel->FrameRender(700, 430, _index, 0, _opacity);
				_job.king[0]->render(_foreGround.x + 500, _foreGround.y + 210, _opacity);
			}
			else if (_job.isChoice[1] == 1)
			{
				_menu.sel->FrameRender(870, 430, _index, 0);
				_job.lancer[0]->render(_foreGround.x + 455, _foreGround.y + 220);
			}
			else if (_job.isChoice[2] == 1)
			{
				_menu.sel->FrameRender(1040, 430, _index, 0);
				_job.shepherd[0]->render(_foreGround.x + 500, _foreGround.y + 200);
			}
			else if (_job.isChoice[3] == 1)
			{
				_menu.sel->FrameRender(1240, 430, _index, 0);
				_job.paladin[0]->render(_foreGround.x + 523, _foreGround.y + 215);
			}
			else if (_job.isChoice[4] == 1)
			{
				_menu.sel->FrameRender(700, 480, _index, 0);
				_job.bottler[0]->render(_foreGround.x + 500, _foreGround.y + 210);
			}
			else if (_job.isChoice[5] == 1)
			{
				_menu.sel->FrameRender(870, 480, _index, 0);
				_job.peasant[0]->render(_foreGround.x + 500, _foreGround.y + 205);
			}
			else if (_job.isChoice[6] == 1)
			{
				_menu.sel->FrameRender(1040, 480, _index, 0);
				_job.greatguy[0]->FrameRender(_foreGround.x + 530, _foreGround.y + 210, _job.ggindex, 0);
				_job.greatguy[2]->render(_foreGround.x + 530, _foreGround.y + 370);
			}
			else if (_job.isChoice[7] == 1) _menu.sel->FrameRender(1240, 480, _index, 0);

			_job.king[1]->render(760, 438, _opacity);
			_job.lancer[1]->render(920, 438, _opacity);
			_job.shepherd[1]->render(1080, 438, _opacity);
			_job.paladin[1]->render(1280, 438, _opacity);
			_job.bottler[1]->render(743, 488, _opacity);
			_job.peasant[1]->render(913, 488, _opacity);
			_job.greatguy[1]->render(1070, 488, _opacity);
			_op.back->render(1300, 488, _opacity);
			_job.level->FrameRender(1085, 520, 0, 0, _opacity);


			_count++;
			if (_count % 5 == 0) _index++;
			if (_index > _menu.sel->getMaxFrameX()) _index = 0;
			if (_count % 5 == 0) _job.ggindex++;
			if (_job.ggindex > _job.greatguy[0]->getMaxFrameX()) _job.ggindex = 0;
		}
	}
}
