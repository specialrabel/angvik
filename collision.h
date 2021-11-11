#pragma once
#include "gameNode.h"
#include "effect.h"

class player;
class bird;
class enemyManager;
class Object;
class menu;

class Player_bullet;
class fragment;
class Weapon;
class itemManager;


class collision
{
private:
	// 맵
	image* _stage;
	image* _effect_img;

	player* _player;
	bird* _bird;
	enemyManager* _enemy;
	enemyManager* _fish;
	Object* _obj;
	itemManager* _im;
	menu* _menu;

	D2D1_RECT_F temp;

	effect* _hit;
	
public:
	collision() {};
	~collision() {};

	// 맵 정보를 받아오기 위한 init 함수 
	virtual HRESULT init(image* stage);
	virtual void release();
	virtual void update();
	virtual void render();

	// Link 합시다
	inline void Link_PlayerClass(player* player) { _player = player;}
	inline void Link_birdClass(bird* bird) { _bird = bird; }
	inline void Link_enemyClass(enemyManager* enemyManager) { _enemy = enemyManager; }
	inline void Link_fish(enemyManager* enemyManager) { _fish = enemyManager; }
	inline void Link_ObjectClass(Object* object) { _obj = object; }
	inline void Link_Item(itemManager* itemManager) { _im = itemManager; }
	inline void Link_Menu(menu* menu) { _menu = menu; }

	// 충돌관리 함수
	void pixel_collision();
	void pixel_collision_bullet();
	void pixel_collision_enemy();
	void player_AND_enemy();
	void player_AND_object();
	void player_bullet_AND_enemy();
	void Enemy_bullet_AND_anything();
	void item_colision();
	void bird_AND_enemy();

	void item_pick_up();
	void item_drop();
};


