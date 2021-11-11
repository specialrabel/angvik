#pragma once
#include "gameNode.h"
#include "player.h"
#include "bird.h"
#include "bullets.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "collision.h"
#include "Object.h"
#include "menu.h"

class title;

class stage1 : public gameNode
{
private:
	image* _img;
	image* _img2;
	image* _img3;
	image* _img4;
	image* _img5;
	image* _img6;
	image* _img7;
	image* _img8;
	image* water_img[2];
	image* waterfall_img;
	image* textbox;
	D2D1_RECT_F textbox_rc;

	bird* _bird;
	player* _player;
	title* _title;
	enemyManager* _enemy;
	enemyManager* _special_enemy;
	itemManager* _im;
	Object* _obj;
	menu* _menu;

	collision* _collisionManager;

	D2D1_RECT_F hidden_rect, temp, background;
	D2D1_RECT_F water[2], waterfall[3];

	vector<string> dialog;
	string current_text;

	float hidden_opacity;
	float bg_opacity;
	float fish_angle;
	float loop_x, loop_y;
	float bg_loop_x;
	float delay, curTime;

	bool pop_up;
	bool in_water;
	bool open_hidden;
	bool open_text;
	bool is_pause;
	bool is_save;
	bool is_drop;

	int count;
	int text_count;

public:
	stage1();
	~stage1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Link_Player(player* player) { _player = player; }
	void Link_Title(title* title) { _title = title; }
};