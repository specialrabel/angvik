#include "stdafx.h"
#include "npc.h"

HRESULT npc::init(const char * imageName, POINT position)
{
	enemy_img = IMAGEMANAGER->addFrameImage("npc_idle", L"monster/NPC_idle.png", 106, 46, 2, 1);
	IMAGEMANAGER->addFrameImage("npc_help", L"monster/NPC_help.png", 106, 46, 2, 1);

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;

	_direction = 0;
	_gravity = 0;

	_kind = enemy_kind::NPC;
	_state = enemy_state::IDLE;

	return S_OK;
}

void npc::update()
{
	_count++;
	if (_count % 10 == 0)
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

		if (_state == enemy_state::HELP)
		{
			enemy_img->setFrameX(_currentFrameX);
			_currentFrameX++;

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_state = enemy_state::IDLE;
				enemy_img = IMAGEMANAGER->findImage("npc_idle");
				_currentFrameX = 0;
			}
		}
	}

	move();
}

void npc::move()
{
	if (_state == enemy_state::IDLE && is_find)
	{
		each_interval[(int)enemy_state::IDLE]++;

		if (each_interval[(int)enemy_state::IDLE] > 100)
		{
			_state = enemy_state::HELP;
			enemy_img = IMAGEMANAGER->findImage("npc_help");
			_currentFrameX = 0;
			each_interval[(int)enemy_state::IDLE] = 0;
		}
	}

	if (_state == enemy_state::HELP && !is_find)
	{
		_state = enemy_state::HELP;
		enemy_img = IMAGEMANAGER->findImage("npc_idle");
		_currentFrameX = 0;
	}

	if (_state == enemy_state::IDLE && !is_find)
	{
		_direction = 0;
	}
}

void npc::render()
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

