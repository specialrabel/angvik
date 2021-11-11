#include "stdafx.h"
#include "monkey.h"

HRESULT monkey::init(const char * imageName, POINT position, int direction)
{
	enemy_img = IMAGEMANAGER->addFrameImage("monkey", L"monster/monkey.png", 416, 46, 8, 1);

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;

	_direction = direction;
	_gravity = 0;

	_kind = enemy_kind::MONKEY;
	_state = enemy_state::RUN;

	return S_OK;
}

void monkey::update()
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
	}

	if (_gravity != 0)
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
		_gravity += 0.1f;
	}

	move();
}

void monkey::move()
{
	if (_direction == 0)
	{
		_rc.left -= 3.0f;
		_rc.right -= 3.0f;
	}
	else
	{
		_rc.left += 3.0f;
		_rc.right += 3.0f;
	}
}

void monkey::render()
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
