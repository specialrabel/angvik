#include "stdafx.h"
#include "fish.h"

HRESULT fish::init(const char * imageName, POINT position)
{
	enemy_img = IMAGEMANAGER->addFrameImage("fish_idle", L"monster/fish_idle.png", 138, 34, 3, 1);
	IMAGEMANAGER->addFrameImage("fish_attack", L"monster/fish_attack.png", 276, 34, 6, 1);

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;

	_direction = 0;
	_gravity = 0;
	_speed = 2.5f;
	_angle = 19;
	
	is_set = false;
	jump_count = 0;

	_kind = enemy_kind::FISH;
	_state = enemy_state::IDLE;

	return S_OK;
}

void fish::update()
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

			if (_currentFrameX > enemy_img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}
	}

	move();
}

void fish::move()
{
	if (_direction == 0)
	{
		_rc.left -= _speed;
		_rc.right -= _speed;
	}
	else
	{
		_rc.left += _speed;
		_rc.right += _speed;
	}

	if (_gravity != 0)
	{
		_rc.top -= _jumpPower - _gravity;
		_rc.bottom -= _jumpPower - _gravity;

		_gravity += 0.1f;
		_angle -= 1.0f;
	}
}

void fish::render()
{
	if (_direction == 1)
	{
		enemy_img->FrameRender(_rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else
	{
		D2D1_POINT_2F center_pos;

		center_pos.x = _rc.left - CAMERAMANAGER->get_camera_x() + enemy_img->getFrameWidth() / 2;
		center_pos.y = _rc.top - CAMERAMANAGER->get_camera_y() + enemy_img->getFrameHeight() / 2;

		D2D1::Matrix3x2F rotation_mat = D2D1::Matrix3x2F::Rotation(_angle, center_pos);
		D2D1::Matrix3x2F scale_mat = D2D1::Matrix3x2F::Scale(D2D1::SizeF(-1.0, 1.0), center_pos);

		D2DMANAGER->pRenderTarget->SetTransform(scale_mat * rotation_mat);

		enemy_img->FrameRender(_rc.left, _rc.top, _currentFrameX, _currentFrameY);

		D2DMANAGER->pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void fish::set_top(float len)
{
	_rc.bottom = len;
	_rc.top = _rc.bottom - _height;
	_jumpPower = 0.0f;
	_gravity = 0.0f;
	_speed = 2.5f;

	if (jump_count > 0)
	{
		_angle = -12.0f;
	}

	enemy_img = IMAGEMANAGER->findImage("fish_idle");
	_state = enemy_state::IDLE;
}

void fish::set_direction(int dir)
{
	jump_count += 1;
	_jumpPower = 4.5f;
	_speed = 2.0f;
	_gravity = 0.1f;
	_angle = 19;

	is_set = true;
	enemy_img = IMAGEMANAGER->findImage("fish_attack");
	_state = enemy_state::ATTACK;
	_currentFrameX = 0;
	_rc.top -= 30;
	_rc.bottom -= 30;

}
