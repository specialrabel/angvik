#include "stdafx.h"
#include "stage1.h"
#include "title.h"


stage1::stage1()
{
}


stage1::~stage1()
{
}

//초기화는 여기다 하세요 제발
HRESULT stage1::init()
{
	_img = IMAGEMANAGER->addImage("stage1_pixel", L"image/Stage1_pixel.png", MAPSIZEX, MAPSIZEY);
	_img->get_RGB(0, 0);

	_img2 = new image;
	_img2 = IMAGEMANAGER->addImage("stage1", L"image/Stage1-fg-original.png", MAPSIZEX, MAPSIZEY);

	_img3 = new image;
	_img3 = IMAGEMANAGER->addImage("hidden_1", L"image/hidden_place.png", 591, 286);

	_img4 = new image;
	_img4 = IMAGEMANAGER->addImage("stage1_back", L"image/Stage1-bg3.png", MAPSIZEX, MAPSIZEY);

	_img5 = new image;
	_img5 = IMAGEMANAGER->addImage("stage1_bg", L"image/Stage1-bg1.png", 1024, 1024);

	_img6 = new image;
	_img6 = IMAGEMANAGER->addImage("stage1_bg", L"image/Stage1-bg2.png", MAPSIZEX, MAPSIZEY);

	_img7 = new image;
	_img7 = IMAGEMANAGER->addImage("pause", L"image/pause.png", 466, 143);

	_img8 = new image;
	_img8 = IMAGEMANAGER->addImage("pausebg", L"image/pause_bg.png", WINSIZEX, WINSIZEY);

	textbox = new image;
	textbox = IMAGEMANAGER->addImage("texbox", L"image/Text/box.png", 200, 49);
	textbox_rc = D2DMANAGER->RectMake(5612, 780, 200, 49);

	waterfall_img = new image;
	waterfall_img->D_Init(L"image/waterfall.png", 46, 64);

	for (int i = 0; i < 2; i++)
	{
		water_img[i] = new image;
		water_img[i]->D_Init(L"image/water.png", 256, 40);
	}

	hidden_rect = D2DMANAGER->RectMake(5330, 714, 591, 286);
	background = D2DMANAGER->RectMake(0, 0, MAPSIZEX, MAPSIZEY);

	_player = new player;
	_player->init();

	_bird = new bird;
	_bird->init();
	_bird->linkPlayerClass(_player);

	_enemy = new enemyManager;
	_enemy->init();
	_enemy->Link_playerClass(_player);

	_special_enemy = new enemyManager;
	_special_enemy->init();
	_special_enemy->Link_playerClass(_player);

	_im = new itemManager;
	_im->init(_title->getJob());

	_obj = new Object;
	_obj->init();

	_menu = new menu;
	_menu->init();
	_menu->linkPlayerClass(_player);

	_player->linkMenu(_menu);

	// 충돌처리 링크설정
	_collisionManager = new collision;
	_collisionManager->init(_img);
	_collisionManager->Link_PlayerClass(_player);
	_collisionManager->Link_birdClass(_bird);
	_collisionManager->Link_enemyClass(_enemy);
	_collisionManager->Link_fish(_special_enemy);
	_collisionManager->Link_ObjectClass(_obj);
	_collisionManager->Link_Item(_im);
	_collisionManager->Link_Menu(_menu);

	// 모다피 심어놈
	_enemy->set_plant(1376, 493);
	_enemy->set_plant(1998, 329);
	_enemy->set_plant(2562, 539);
	_enemy->set_plant(2966, 558);
	_enemy->set_plant(5516, 250);
	_enemy->set_plant(5866, 232);

	// 나무
	_enemy->set_tree(3040, 739);
	_enemy->set_tree(3190, 266);

	// 원숭이
	_enemy->set_monkey(510, 247, 1);
	_enemy->set_monkey(1655, 60, 0);
	
	//꼬마
	_enemy->set_kid(3775, 290, 1);
	_enemy->set_kid(5100, 535, 1);

	// 거북이
	_enemy->set_turtle(3925, 620, 1);
	_enemy->set_turtle(4190, 909, 0);
	_enemy->set_turtle(4200, 400, 0);

	// 물고기
	_special_enemy->set_fish(5205, 980);

	// 공주
	_special_enemy->set_npc(5702, 880);
	
	// 문
	_obj->set_gate(5781, 816);

	// 함정화살
	_obj->set_arrow(5467, 842, 1, true);
	_obj->set_arrow(5467, 860, 1, true);

	_obj->set_arrow(5952, 864, -1, false);
	_obj->set_arrow(5952, 882, -1, false);

	// 나뭇가지
	_obj->set_branch(2660.5, 432.4, false);
	_obj->set_branch(2900, 475.5, false);
	_obj->set_branch(2900, 592.5, false);
	_obj->set_branch(3500.5, 552, false);
	_obj->set_branch(3500.5, 374, false);

	// 나뭇가지 reverse
	_obj->set_branch(2705.7, 410.4, true);
	_obj->set_branch(2705.7, 516.6, true);
	_obj->set_branch(2705.7, 633.5, true);
	_obj->set_branch(3325, 637.5, true);
	_obj->set_branch(3323.4, 465.8, true);

	// 물
	water[0] = D2DMANAGER->RectMake(4376, 910, 512, 35);
	water[1] = D2DMANAGER->RectMake(4906, 889, 512, 40);

	//파도
	waterfall[0] = D2DMANAGER->RectMake(4750, 559, 46, 500);
	waterfall[1] = D2DMANAGER->RectMake(4790, 559, 46, 500);
	waterfall[2] = D2DMANAGER->RectMake(4935, 609, 46, 400);

	is_drop = 1;
	text_count = 1;
	count = 0;
	pop_up = false;
	open_text = false;
	hidden_opacity = 1.5f;
	delay = 1.0f;
	curTime = 0.0f;
	is_save = 0;
	bg_opacity = 0;
	dialog = TXTDATA->txtLoad("image/Text/dialog.txt");
	current_text = dialog[0];

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void stage1::release()
{

}

void stage1::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		if (is_pause) is_pause = 0;
		else if (!is_pause) is_pause = 1;
	}
	
	if (is_pause)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player->set_isDead(true);
			is_pause = 0;
		}
	}
	if (_player->get_isDead() && !is_save)
	{
		curTime = TIMEMANAGER->getWorldTime();
		is_save = true;
	}

	if (_player->get_isDead() && delay < TIMEMANAGER->getWorldTime() - curTime)
	{
		this->init();
		SCENEMANAGER->changeScene("타이틀");
	}

	if (!is_pause) {

		_menu->update();
		_enemy->update();
		_player->update();
		_bird->update();
		_special_enemy->update();
		_obj->update();
		_im->update();
		_collisionManager->update();

		D2D1_RECT_F pRc = _player->getTagPlayer()->rc;
		if (INTERSECTION_RECT(temp, pRc, hidden_rect))
		{
			hidden_opacity -= 0.02f;
			open_hidden = true;
		}

		if (_player->getTagPlayer()->rc.right > 1731 && !pop_up)
		{
			_enemy->set_monkey(2255, 50, 0);
			pop_up = true;
		}

		if (hidden_opacity < 0)
		{
			hidden_opacity = 0.0f;
		}
		else if (hidden_opacity > 1.0f)
		{
			hidden_opacity = 1.0f;
		}

		if (_special_enemy->get_fish_num() == 0)
		{
			_special_enemy->set_fish(5205, 980);
		}

		if (_special_enemy->get_npc_num() == 0)
		{
			_obj->get_arrow()->fire();
			if (is_drop) 
			{
				_im->setDropItem(5702, 880, true);
				is_drop = 0;
			}
		}

		for (int i = 0; i < _special_enemy->getVMinion().size(); i++)
		{
			if (_special_enemy->getVMinion()[i]->get_kind() == enemy_kind::NPC) continue;
			fish_angle = _special_enemy->getVMinion()[i]->get_angle();
		}

		for (int i = 0; i < _special_enemy->getVMinion().size(); i++)
		{
			if (_special_enemy->getVMinion()[i]->get_kind() == enemy_kind::FISH) continue;
			D2D1_RECT_F Player = D2DMANAGER->RectMake(_player->getTagPlayer()->rc.left, _player->getTagPlayer()->rc.top, 100, 100);
			D2D1_RECT_F NPC = _special_enemy->getVMinion()[i]->getRect();

			if (INTERSECTION_RECT(temp, Player, NPC) && KEYMANAGER->isOnceKeyDown('F') && current_text == dialog[0])
			{
				open_text = true;
			}
		}

		in_water = _player->get_inWater();
		loop_x += 1;
		loop_y -= 1;
		bg_opacity += 0.02f;

		CAMERAMANAGER->updateScreen(_player->getTagPlayer()->x, _player->getTagPlayer()->y, 0.5, 0.4);

	}
}

void stage1::render()
{
	 
	_img5->loopRender(background, 0, 0, bg_opacity);
	_img4->render(0, 0, bg_opacity);
	_img6->render(0, 0, bg_opacity);

	waterfall_img->loopRender(waterfall[0], 1, loop_y, bg_opacity);
	waterfall_img->loopRender(waterfall[1], 1, loop_y, bg_opacity);
	waterfall_img->loopRender(waterfall[2], 1, loop_y, bg_opacity);

	if (in_water)
	{
		_player->render();
	}


	_special_enemy->render(), bg_opacity;

	water_img[0]->rotation_start(water[0].left, water[0].top, -10.0f);
	water_img[0]->loopRender(water[0], loop_x, 1, bg_opacity);
	water_img[0]->rotation_end();

	water_img[1]->rotation_start(water[1].left, water[1].top, 19.0f);
	water_img[1]->loopRender(water[1], loop_x, 1, bg_opacity);
	water_img[1]->rotation_end();

	_obj->render();
	_img2->render(0, 0, bg_opacity);
	_img3->render(hidden_rect.left, hidden_rect.top, hidden_opacity);
	_bird->render();


	_im->render();
	
	if (!in_water)
	{
		_player->render();
	}

	_enemy->render();
	//_obj->render();
	_menu->render();
	_collisionManager->render();

	count++;

	if (open_text)
	{
		WCHAR str_previous[128];
		wstring text;

		if (count % 5 == 0)
		{
			text_count++;
			count = 0;
		}

		if (text_count >= current_text.length() && current_text == dialog[0])
		{
			current_text = dialog[0] + dialog[1];
			wstring text(current_text.begin(), current_text.end());
		}

		if (text_count >= current_text.length() && current_text != dialog[0])
		{
			text_count = current_text.length();

			if (KEYMANAGER->isOnceKeyUp('F')) 
				open_text = false;
		}

		textbox->render(textbox_rc.left, textbox_rc.top);

		if (current_text == dialog[0])
		{
			text = wstring(current_text.begin(), current_text.begin() + text_count);
		}
		else
		{
			text = wstring(current_text.begin(), current_text.begin() + text_count);
		}

		WCHAR str[128];

		lstrcpyW(str, text.c_str());

		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, textbox_rc.left + 10 - CAMERAMANAGER->get_camera_x(), textbox_rc.top - CAMERAMANAGER->get_camera_y(),
			textbox_rc.left + 100, textbox_rc.top + 100);
	}


	if (is_pause)
	{
		_img8->render(CAMERAMANAGER->get_camera_x(), CAMERAMANAGER->get_camera_y(), 0.3f);
		_img7->render(CAMERAMANAGER->get_camera_x() + WINSIZEX / 4, CAMERAMANAGER->get_camera_y() + WINSIZEY / 3);
	}
}
