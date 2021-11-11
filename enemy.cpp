#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_Fire_interval = RND->getFromIntTo(1, 500);

	enemy_img = IMAGEMANAGER->findImage(imageName);

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_direction = 0;
	_gravity = 0;

	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position, int direction)
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	move();
	KEYANIMANAGER->update();
}

void enemy::render()
{
	draw();
}

void enemy::move()
{
}

bool enemy::bullet_Fire()
{
	if (!is_set)
	{
		_fireCount++;
	}

	if (_fireCount % _Fire_interval == 0)
	{
		_Fire_interval = 135;
		_fireCount = 0;
		is_set = true;
	}
	
	return is_set;
}

void enemy::draw()
{

}

void enemy::set_top(float len)
{
	_rc.bottom = len;
	_rc.top = _rc.bottom - _height;
	_jumpPower = 0;
}

void enemy::set_gravity(float val)
{
	_gravity = val;
}

void enemy::set_jumpPower(float val)
{
	_jumpPower = val;
}

void enemy::set_direction(int dir)
{
	_direction = dir;
}

void enemy::set_direction(int dir, float val)
{
	if (!is_find)
	{
		_direction = dir;
	}
	else
	{
		float width = _rc.right - _rc.left;
		if (_direction == 0)
		{
			_rc.left = val;
			_rc.right = _rc.left + width;
		}
		else
		{
			_rc.right = val;
			_rc.left = _rc.right - width;
		}
	}
}
