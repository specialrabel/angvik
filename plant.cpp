#include "stdafx.h"
#include "plant.h"

HRESULT plant::init(const char * imageName, POINT position)
{
	enemy_img = IMAGEMANAGER->addFrameImage("plant_left_idle", L"monster/plant_left_idle.png", 192, 54, 6, 1);
	IMAGEMANAGER->addFrameImage("plant_left_attack", L"monster/plant_left_attack.png", 272, 54, 8, 1);

	_Fire_interval = 20;

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;
		
	_direction = 0;
	_gravity = 0;

	_kind = enemy_kind::PLANT;
	_state = enemy_state::IDLE;

	return S_OK;
}

void plant::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		if (_state == enemy_state::IDLE)
		{
			enemy_img->setFrameX(_currentFrameX);
			_currentFrameX++;

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}

		if (_state == enemy_state::ATTACK)
		{
			enemy_img->setFrameX(_currentFrameX);
			_currentFrameX++;

			if (_currentFrameX == 3)
			{
				is_fire = true;
			}

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_state = enemy_state::IDLE;
				enemy_img = IMAGEMANAGER->findImage("plant_left_idle");
				_currentFrameX = 0;
			}
		}
	}

	move();
}

void plant::move()
{
	if (_state == enemy_state::IDLE && is_find)
	{
		each_interval[(int)enemy_state::IDLE]++;

		if (each_interval[(int)enemy_state::IDLE] > 100)
		{
			is_fire = false;
			_state = enemy_state::ATTACK;
			enemy_img = IMAGEMANAGER->findImage("plant_left_attack");
			_currentFrameX = 0;
			each_interval[(int)enemy_state::IDLE] = 0;
		}
	}

	if (_state == enemy_state::ATTACK && !is_find)
	{
		_state = enemy_state::IDLE;
		enemy_img = IMAGEMANAGER->findImage("plant_left_idle");
		_currentFrameX = 0;
	}

	if (_state == enemy_state::IDLE && !is_find)
	{
		_direction = 0;
		is_fire = false;
	}
}

void plant::render()
{
	if (_direction == 0)
	{
		enemy_img->FrameRender(_rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else
	{
		enemy_img->Frame_scale_start(_rc.left, _rc.top, -1.0, 1.0);
		enemy_img->FrameRender(_rc.left, _rc.top, _currentFrameX, _currentFrameY);
		enemy_img->scale_end();
	}
}

