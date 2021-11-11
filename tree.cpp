#include "stdafx.h"
#include "tree.h"

HRESULT tree::init(const char * imageName, POINT position)
{
	enemy_img = IMAGEMANAGER->addFrameImage("tree_move", L"monster/tree_move.png", 468, 86, 6, 1);
	IMAGEMANAGER->addFrameImage("tree_attack", L"monster/tree_atk.png", 444, 86, 6, 1);
	IMAGEMANAGER->addFrameImage("storm", L"bullet_img/storm.png", 475, 80, 5, 1);

	EFFECTMANAGER->addEffect("storm", "storm", 475, 80, 95, 80, 1, 0.1, 1);

	_Fire_interval = 20;

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;

	_direction = 1;
	_gravity = 0;

	_kind = enemy_kind::TREE;
	_state = enemy_state::IDLE;

	return S_OK;
}

void tree::update()
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
			each_interval[(int)enemy_state::ATTACK]++;

			if (each_interval[static_cast<int>(enemy_state::ATTACK)] > 3)
			{
				_currentFrameX++;
				each_interval[(int)enemy_state::ATTACK] = 0;
			}

			if (_currentFrameX == 3)
			{
				is_fire = true;

			}

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_state = enemy_state::IDLE;
				each_interval[(int)enemy_state::ATTACK] = 0;
				enemy_img = IMAGEMANAGER->findImage("tree_move");
				_currentFrameX = 0;
			}
		}
	}

	move();
}

void tree::move()
{

	if (each_interval[(int)enemy_state::IDLE] > 100)
	{
		is_fire = false;
		_state = enemy_state::ATTACK;
		enemy_img = IMAGEMANAGER->findImage("tree_attack");
		_currentFrameX = 0;
		each_interval[(int)enemy_state::IDLE] = 0;
	}

	if (_state == enemy_state::IDLE)
	{
		each_interval[(int)enemy_state::IDLE]++;

		if (_direction == 0)
		{
			_rc.left -= 2.0f;
			_rc.right -= 2.0f;
		}
		else
		{
			_rc.left += 2.0f;
			_rc.right += 2.0f;
		}
		is_fire = false;
	}
}

void tree::render()
{
	if (_direction == 1)
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

