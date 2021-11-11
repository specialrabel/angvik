#include "stdafx.h"
#include "kid.h"

HRESULT kid::init(const char * imageName, POINT position, int direction)
{
	enemy_img = IMAGEMANAGER->addFrameImage("kid_move", L"monster/kid_move.png", 175, 29, 7, 1);
	IMAGEMANAGER->addFrameImage("kid_jump", L"monster/kid_jump.png", 50, 27, 2, 1);

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;

	_direction = direction;
	_gravity = 0;
	is_jump = false;

	_kind = enemy_kind::KID;
	_state = enemy_state::RUN;

	return S_OK;
}

void kid::update()
{
	_count++;

	if (_count % 5 == 0)
	{
		if (_state == enemy_state::RUN)
		{
			enemy_img->setFrameX(_currentFrameX);
			_currentFrameX++;

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}

		if (_state == enemy_state::JUMP)
		{
			enemy_img->setFrameX(_currentFrameX);
			_currentFrameX++;

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}
	}

	if (_jumpPower != 0.0f)
	{
		is_jump = true;
	}
	else
		is_jump = false;

	if (is_jump)
	{
		_rc.top -=  _jumpPower - _gravity;
		_rc.bottom -= _jumpPower - _gravity;

		_jumpPower -= 0.1f;
	}

	if (_gravity != 0 && !is_jump)
	{
		if (_direction == 0)
		{
			_rc.left -= 0.5f;
			_rc.right -= 0.5f;
		}
		else
		{
			_rc.left += 0.5f;
			_rc.right += 0.5f;
		}

		_rc.top += _gravity;
		_rc.bottom += _gravity;
	}
	move();
}

void kid::move()
{
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
}

void kid::render()
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