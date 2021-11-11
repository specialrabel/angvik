#pragma once
#include "gameNode.h"

#include "enemy.h"
#include "plant.h"
#include "monkey.h"
#include "fish.h"
#include "npc.h"
#include "turtle.h"
#include "kid.h"
#include "bullets.h"
#include "tree.h"

#include <vector>

class player;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				Enemy_pool;
	typedef vector<enemy*>::iterator	pool_iter;

private:
	Enemy_pool _enemy_pool;
	pool_iter _pool_iter;
	bullet* _bullet;
	Storm* _bullet_storm;

	int _count;
	int fish_num;
	int npc_num;
	player* _player;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void set_plant(int destX, int destY);
	void set_tree(int destX, int destY);
	void set_monkey(int destX, int destY, int direction);
	void set_turtle(int destX, int destY, int direction);
	void set_kid(int destX, int destY, int direction);
	void set_fish(int destX, int destY);
	void set_npc(int destX, int destY);

	void set_fish_num(int val) { fish_num += val; }
	int get_fish_num() { return fish_num; }

	void set_npc_num(int val) { npc_num += val; }
	int get_npc_num() { return npc_num; }

	void minionBulletFire();
	void find_player();
	void collision_player();
	void remove_unit(int num);
	void Link_playerClass(player* player) { _player = player; }

	vector<enemy*> getVMinion() { return _enemy_pool; }
	vector<enemy*>::iterator getVIMinion() { return _pool_iter; }
	bullet* get_bullet() { return _bullet; }
	Storm* get_storm() { return _bullet_storm; }

	POINT PointMake(int x, int y);
	
};

