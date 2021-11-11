#include "stdafx.h"
#include "enemyManager.h"
#include "Player.h"

HRESULT enemyManager::init()
{
	IMAGEMANAGER->addFrameImage("plant_bullet", L"bullet_img/plant_bullet.png", 168, 18, 6, 1);

	_bullet = new bullet;
	_bullet->init(30, 500);

	_bullet_storm = new Storm;
	_bullet_storm->init(4, 500);

	fish_num = 0;
	npc_num = 0;

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		(*_pool_iter)->update();
	}

	find_player();
	minionBulletFire();
	_bullet->update();
	_bullet_storm->update();
}

void enemyManager::render()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		(*_pool_iter)->render();
	}
	_bullet->render();
	_bullet_storm->render();
}

void enemyManager::set_plant(int destX, int destY)
{
	enemy* _plant;
	_plant = new plant;
	_plant->init("plant_left_idle", PointMake(destX, destY));

	_enemy_pool.push_back(_plant);
}

void enemyManager::set_tree(int destX, int destY)
{
	enemy* _tree;
	_tree = new tree;
	_tree->init("tree_move", PointMake(destX, destY));

	_enemy_pool.push_back(_tree);
}

void enemyManager::set_monkey(int destX, int destY, int direction)
{
	enemy* _monkey;
	_monkey = new monkey;
	_monkey->init("monkey", PointMake(destX, destY), direction);

	_enemy_pool.push_back(_monkey);
}

void enemyManager::set_turtle(int destX, int destY, int direction)
{
	enemy* _turtle;
	_turtle = new turtle;
	_turtle->init("monkey", PointMake(destX, destY), direction);

	_enemy_pool.push_back(_turtle);
}

void enemyManager::set_kid(int destX, int destY, int direction)
{
	enemy* _kid;
	_kid = new kid;
	_kid->init("kid_move", PointMake(destX, destY), direction);

	_enemy_pool.push_back(_kid);
}

void enemyManager::set_fish(int destX, int destY)
{
	enemy* _fish;
	_fish = new fish;
	_fish->init("fish_idle", PointMake(destX, destY));
	fish_num += 1;

	_enemy_pool.push_back(_fish);
}

void enemyManager::set_npc(int destX, int destY)
{
	enemy* _npc;
	_npc = new npc;
	_npc->init("npc_idle", PointMake(destX, destY));
	npc_num += 1;

	_enemy_pool.push_back(_npc);
}

void enemyManager::minionBulletFire()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{	// 모다피 전용 발사 함수. 모다피 외에는 전부 패스
		if ((*_pool_iter)->get_kind() != enemy_kind::PLANT) continue;

		// 불렛 인터벌 완료가 되었다면, 총알 생성
		if ((*_pool_iter)->bullet_Fire() && (*_pool_iter)->get_isFired())
		{
			D2D1_RECT_F rc = (*_pool_iter)->getRect();
			D2D1_RECT_F player_rect = _player->getTagPlayer()->rc;

			// 플레이어가 왼쪽에 있을시, 불렛 왼쪽 생성
			if ((*_pool_iter)->get_direction() == 0)
			{
				_bullet->fire(L"bullet_img/plant_bullet.png", rc.left - 10, (rc.top + rc.bottom)/2,
					168, 18, 6, 1,
					getAngle((rc.left + rc.right) / 2, rc.bottom,
						player_rect.left + player_rect.right - player_rect.left,
						player_rect.top + player_rect.bottom - player_rect.top),
					0);
			}
			else
			{
				_bullet->fire(L"bullet_img/plant_bullet.png", rc.right - 10, (rc.top + rc.bottom) / 2,
					168, 18, 6, 1,
					getAngle((rc.left + rc.right) / 2, rc.bottom,
						player_rect.left + player_rect.right - player_rect.left,
						player_rect.top + player_rect.bottom - player_rect.top),
					1);
			}
			(*_pool_iter)->off_isSet();
		}
	}

	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{	
		if ((*_pool_iter)->get_kind() != enemy_kind::TREE) continue;

		// 불렛 인터벌 완료가 되었다면, 총알 생성
		if ((*_pool_iter)->bullet_Fire() && (*_pool_iter)->get_isFired())
		{
			D2D1_RECT_F rc = (*_pool_iter)->getRect();
			D2D1_RECT_F player_rect = _player->getTagPlayer()->rc;

			// 플레이어가 왼쪽에 있을시, 불렛 왼쪽 생성
			if ((*_pool_iter)->get_direction() == 0)
			{
				_bullet_storm->fire(L"bullet_img/storm.png", rc.left - 25, rc.top,
					475, 80, 5, 1,
					getAngle((rc.left + rc.right) / 2, rc.bottom,
						player_rect.left + player_rect.right - player_rect.left,
						player_rect.top + player_rect.bottom - player_rect.top),
					0);
			}
			else
			{
				_bullet_storm->fire(L"bullet_img/storm.png", rc.right + 25, rc.top,
					475, 80, 5, 1,
					getAngle((rc.left + rc.right) / 2, rc.bottom,
						player_rect.left + player_rect.right - player_rect.left,
						player_rect.top + player_rect.bottom - player_rect.top),
					1);
			}
			(*_pool_iter)->off_isSet();
		}
	}
}

void enemyManager::find_player()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{	
		if ((*_pool_iter)->get_kind() != enemy_kind::PLANT && (*_pool_iter)->get_kind() != enemy_kind::NPC) continue;

		int x = (*_pool_iter)->getRect().left + ((*_pool_iter)->getRect().right - (*_pool_iter)->getRect().left) / 2;
		int y = (*_pool_iter)->getRect().top + (*_pool_iter)->get_height() / 2;

		int x2 = _player->getTagPlayer()->rc.left + (_player->getTagPlayer()->rc.right - _player->getTagPlayer()->rc.left) / 2;
		int y2 = _player->getTagPlayer()->rc.top + (_player->getTagPlayer()->rc.bottom - _player->getTagPlayer()->rc.top) / 2;

		if (getDistance(x, y, x2, y2) < 500)
		{
			// 플레이어 발견 플래그 온
			(*_pool_iter)->find_player();

			if (x > x2)
			{
				(*_pool_iter)->set_direction(0);
			}
			else
				(*_pool_iter)->set_direction(1);
		}
		else
		{
			(*_pool_iter)->Not_find_player();
		}
	}
}

void enemyManager::collision_player()
{
}

void enemyManager::remove_unit(int num)
{
	//_enemy_pool[num]->get_img()->release();
	_enemy_pool.erase(_enemy_pool.begin() + num);
}

POINT enemyManager::PointMake(int x, int y)
{
	POINT temp;

	temp.x = x;
	temp.y = y;

	return temp;
}
