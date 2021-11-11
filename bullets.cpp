#include "stdafx.h"
#include "bullets.h"

HRESULT bullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();	_viBullet++)
	{
		// 렌더
		if (_viBullet->direction == 0)
		{
			_viBullet->bulletImage->Frame_scale_start(_viBullet->x, _viBullet->y, -1, 1);

			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), 0);

			_viBullet->bulletImage->scale_end();
		}
		else
		{
			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), 0);
		}

		_viBullet->count++;

		// 프레임 속도 조절용 카운트
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			_viBullet->count = 0;
		}

		//최대 프레임보다 커지면
		if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
		{
			_viBullet->bulletImage->setFrameX(0);
		}
	}
}

void bullet::fire(LPCWSTR imagename, float x, float y, float width, float height,
	float frameX, float frameY, float angle, int direction)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(imagename, width, height, frameX, frameY);
	bullet.speed = 4.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.direction = direction;

	bullet.rc = D2DMANAGER->RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);

}

void bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullet::removeBullet(int arrNum)
{
	//벡터의 값을 지울떈  erase()
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/**************************************** 갑옷이나 양이 조각날때 사용하는 불렛 *******************************************************/

HRESULT fragment::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void fragment::release()
{
}

void fragment::update()
{
	move();
}

void fragment::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		// 렌더
		_viBullet->bulletImage->render(
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->opacity);

		_viBullet->opacity -= 0.007f;

		if (_viBullet->opacity <= 0.0f)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			_viBullet++;
	}
}

void fragment::fire(LPCWSTR filename, float x, float y, float width, float height, int _direction)
{
	//최대갯수보다 더 생성되려고 하면 하지않는다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(filename, width, height);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 3.0f;
	bullet.opacity = 1.0f;
	bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;
	bullet.direction = _direction;

	bullet.type = FRAGMENT;
	bullet.jump_power = RND->getFromFloatTo(0.0f, 6.0f);
	bullet.gravity = 0.2f;

	_vBullet.push_back(bullet);
}

void fragment::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->x += _viBullet->speed * _viBullet->direction;
		_viBullet->y -= _viBullet->jump_power - _viBullet->gravity;

		_viBullet->gravity += 0.2f;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}
}

void fragment::removeMissile(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void fragment::set_rect(int num, float val)
{
	_vBullet[num].rc.bottom = val;
	_vBullet[num].rc.top = _vBullet[num].rc.bottom - _vBullet[num].height;
}

void fragment::set_gravity(int num)
{
	_vBullet[num].gravity = 0.0f;
	_vBullet[num].speed = 0.0f;
	_vBullet[num].jump_power = 0.0f;
}

void fragment::set_direction(int num)
{
	_vBullet[num].direction = _vBullet[num].direction * -1;
}

/**************************************** 플레이어 불렛 (빛기둥, 양) *******************************************************/

HRESULT Player_bullet::init(int bulletMax, float range, fragment* frag)
{
	_bulletMax = bulletMax;
	_range = range;
	_frag = frag;

	return S_OK;
}

void Player_bullet::release()
{
}

void Player_bullet::update()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].is_hit)
		{
			_vBullet[i].interval++;
		}

		if (_vBullet[i].interval > 7)
		{
			_vBullet[i].interval = 0;
			_vBullet[i].is_hit = false;
		}

		if (_vBullet[i].isGround)
		{
			_vBullet[i].interval2++;
		}

		if (_vBullet[i].interval2 > 7)
		{
			_vBullet[i].interval2 = 0;
			_vBullet[i].isFire = true;
		}
	}

	move();
	EFFECTMANAGER->update();
}

void Player_bullet::render()
{
	// 빛 기둥 전용 렌더 함수 -> 빛 기둥은 렌더 후 사라져야되기 떄문
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{	// 빛 기둥이 아니라면 패스
		if (_viBullet->type != LIGHT || !_viBullet->isFire)
		{
			_viBullet++;
			continue;
		}

		_viBullet->bulletImage->FrameRender(
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);
		
		_viBullet->count++;

		// 프레임 속도 조절용 카운트
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			_viBullet->count = 0;
		}

		//최대 프레임보다 커지면
		if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
		{
			_viBullet->bulletImage->setFrameX(0);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			_viBullet++;
	}

	// 빛 기둥 외 루프(계속 렌더)되는 함수
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{	// 빛 기둥이라면 패스
		if (_viBullet->type == LIGHT)
		{
			_viBullet++;
			continue;
		}

		// 방향전환시 이미지 반전
		if (_viBullet->direction < 0)
		{
			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), 1);
		}
		else
		{
			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), 0);
		}

		_viBullet->count++;

		// 프레임 속도 조절용 카운트
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
		}
		//최대 프레임보다 커지면
		if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
		{
			_viBullet->bulletImage->setFrameX(0);
		}

		if (_viBullet->count > 350)
		{
			EFFECTMANAGER->play("explosion", _viBullet->rc.left, _viBullet->rc.bottom);

			_frag->fire(L"bullet_img/sheep_frag1.png", _viBullet->rc.left, _viBullet->rc.top, 22, 20, -1);
			_frag->fire(L"bullet_img/sheep_frag2.png", _viBullet->rc.left, _viBullet->rc.bottom, 18, 21, -1);

			_frag->fire(L"bullet_img/sheep_frag4.png", _viBullet->rc.left + 5, _viBullet->rc.top, 20, 17, -1);
			_frag->fire(L"bullet_img/sheep_frag1.png", _viBullet->rc.left + 10, _viBullet->rc.top, 22, 20, 1);

			_frag->fire(L"bullet_img/sheep_frag3.png", _viBullet->rc.right, _viBullet->rc.top, 14, 11, 1);
			_frag->fire(L"bullet_img/sheep_frag4.png", _viBullet->rc.right, _viBullet->rc.bottom, 20, 17, 1);

			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			_viBullet++;
	}

	EFFECTMANAGER->render();
}

void Player_bullet::fire(LPCWSTR filename, float x, float y, float width, float height, int frameX, int frameY, int direction)
{
	//최대갯수보다 더 생성되려고 하면 하지않는다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(filename, width, height, frameX, frameY);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 4.0f;

	bullet.direction = direction;

	if (filename == L"bullet_img/Light_attack2.png")
	{
		bullet.type = LIGHT;
		bullet.jump_power = 0.0f;
		bullet.gravity = 0.0f;
		bullet.interval2 = 0;
		bullet.isGround = false;
	}
	else
	{
		bullet.type = SHEEP;
		bullet.jump_power = 3.5f;
		bullet.gravity = 0.2f;
	}

	if (direction == 1)
	{
		bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y + 200, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());
	}
	else
		bullet.rc = D2DMANAGER->RectMake(bullet.x - bullet.bulletImage->getFrameWidth(), bullet.y + 200, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());
	
	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;

	_vBullet.push_back(bullet);
}

void Player_bullet::fragment_fire(LPCWSTR filename, float x, float y, float width, float height, int _direction)
{
	//최대갯수보다 더 생성되려고 하면 하지않는다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(filename, width, height);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 3.0f;

	bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;
	bullet.direction = _direction;

	bullet.type = FRAGMENT;
	bullet.jump_power = RND->getFromFloatTo(0.0f, 4.0f);
	bullet.gravity = 0.2f;

	_vBullet.push_back(bullet);
}

void Player_bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->type == LIGHT)
		{
			_viBullet++;
			continue;
		}
		_viBullet->x += _viBullet->speed * _viBullet->direction;
		_viBullet->y -= _viBullet->jump_power - _viBullet->gravity;

		_viBullet->gravity += 0.2f;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//사거리보다 더 멀리 나가면(?)
		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void Player_bullet::set_rect(int num, float val)
{
	_vBullet[num].rc.bottom = val;
	_vBullet[num].rc.top = _vBullet[num].rc.bottom - _vBullet[num].height;
	_vBullet[num].isGround = true;
}

void Player_bullet::set_gravity(int num)
{
	_vBullet[num].gravity = 0.2f;
}

void Player_bullet::set_direction(int num, float distance)
{
	if (_vBullet[num].direction > 0)
	{
		_vBullet[num].rc.right = _vBullet[num].rc.right - 5;
		_vBullet[num].rc.left = _vBullet[num].rc.left - 5;
	}
	else
	{
		_vBullet[num].rc.left = _vBullet[num].rc.left + 5;
		_vBullet[num].rc.right = _vBullet[num].rc.right + 5;
	}

	if (!_vBullet[num].is_hit)
	{
		_vBullet[num].direction = _vBullet[num].direction * -1;
		_vBullet[num].is_hit = true;
 	}
}

//현무 객체에 몇 번쨰 미사일 지워달라고 요청할 함수
void Player_bullet::removeMissile(int arrNum)
{
	_frag->fire(L"bullet_img/sheep_frag1.png", _vBullet[arrNum].rc.left, _vBullet[arrNum].rc.top, 22, 20, -1);
	_frag->fire(L"bullet_img/sheep_frag2.png", _vBullet[arrNum].rc.left, _vBullet[arrNum].rc.bottom, 18, 21, -1);

	_frag->fire(L"bullet_img/sheep_frag4.png", _vBullet[arrNum].rc.left + 5, _vBullet[arrNum].rc.top, 20, 17, -1);
	_frag->fire(L"bullet_img/sheep_frag1.png", _vBullet[arrNum].rc.left + 10,_vBullet[arrNum].rc.top, 22, 20, 1);
											   
	_frag->fire(L"bullet_img/sheep_frag3.png", _vBullet[arrNum].rc.right, _vBullet[arrNum].rc.top, 14, 11, 1);
	_frag->fire(L"bullet_img/sheep_frag4.png", _vBullet[arrNum].rc.right, _vBullet[arrNum].rc.bottom, 20, 17, 1);

	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/**************************************** 무기 던질때 사용하는 불렛 *******************************************************/

HRESULT Weapon::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	_angle = 0;

	return S_OK;
}

void Weapon::release()
{
}

void Weapon::update()
{
	move();
}

void Weapon::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		if (_viBullet->direction < 0)
		{
			_viBullet->bulletImage->Frame_scale_start(_viBullet->rc.left, _viBullet->rc.top, -1.0f, 1.0f);

			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(),
				0,
				_viBullet->opacity);

			_viBullet->bulletImage->scale_end();
		}
		else
		{
			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(),
				0,
				_viBullet->opacity);
		}

		D2DMANAGER->Rectangle(_viBullet->rc);
	}
}

void Weapon::fire(LPCWSTR filename, float x, float y, float width, float height, int frameX, int frameY, int _direction)
{
	//최대갯수보다 더 생성되려고 하면 하지않는다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(filename, width, height, frameX, frameY);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 8.0f;
	bullet.opacity = 1.0f;
	bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());
	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;
	bullet.direction = _direction;

	bullet.type = SPEAR;
	bullet.jump_power = 0.0f;
	bullet.gravity = 0.0f;

	_vBullet.push_back(bullet);
}

void Weapon::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->x += _viBullet->speed * _viBullet->direction;
		_viBullet->y -= _viBullet->jump_power - _viBullet->gravity;

		if (_viBullet->gravity != 0.0f)
		{
			_viBullet->gravity += 0.2f;
		}

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());
	}
}

void Weapon::removeMissile(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void Weapon::set_speed(int num)
{
	_vBullet[num].gravity = 0.2f;
	_vBullet[num].jump_power = 0.0f;
}

void Weapon::set_rect(int num, float val)
{
	_vBullet[num].rc.bottom = val;
	_vBullet[num].rc.top = _vBullet[num].rc.bottom - _vBullet[num].height;
}

void Weapon::set_gravity(int num)
{
	if (_vBullet[num].speed < 0)
	{
		_vBullet[num].gravity = 0.0f;
		_vBullet[num].speed = 0.0f;
		_vBullet[num].jump_power = 0.0f;
	}
}

void Weapon::set_direction(int num, float val)
{
	_vBullet[num].speed = -2.0f;
}

/******************************************* 함정 화살 *****************************************************/

HRESULT Arrow::init(float x, float y, int direction, bool reverse)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(bullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(L"bullet_img/화살.png", 368, 18, 4, 1);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.type = ARROW;
	bullet.speed = 5.0f;
	bullet.isFire = false;
	bullet.direction = direction;

	if (reverse)
	{
		bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());
	}
	else
		bullet.rc = D2DMANAGER->RectMake(bullet.x - bullet.bulletImage->getFrameWidth(), bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());

	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;

	_vBullet.push_back(bullet);

	return S_OK;
}

void Arrow::release()
{
}

void Arrow::update()
{
	move();
}

void Arrow::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		if (_viBullet->direction < 0)
		{
			_viBullet->bulletImage->Frame_scale_start(_viBullet->rc.left, _viBullet->rc.top, -1.0f, 1.0f);

			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				0,
				0
			);

			_viBullet->bulletImage->scale_end();
		}
		else
		{
			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				0,
				0
			);
		}
	}
}

void Arrow::fire()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].isFire = true;
	}
}

void Arrow::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->x += _viBullet->speed * _viBullet->direction;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());
	}

	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].direction == 1 && _vBullet[i].rc.left > 5952)
		{
			_vBullet.erase(_vBullet.begin() + i);
			break;
		}
		else if(_vBullet[i].direction == -1 && _vBullet[i].rc.right < 5467)
		{
			_vBullet.erase(_vBullet.begin() + i);
			break;
		}
	}
}

void Arrow::removeBullet(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/****************************************************************************** 폭풍 ************************************************************************/

HRESULT Storm::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Storm::release()
{
}

void Storm::update()
{
	move();
}

void Storm::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->bulletImage->FrameRender(
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0, _viBullet->opacity);
		
		_viBullet->count++;
		_viBullet->opacity -= 0.01f;

		// 프레임 속도 조절용 카운트
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			_viBullet->count = 0;
		}

		//최대 프레임보다 커지면
		if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
		{
			_viBullet->bulletImage->setFrameX(0);
		}

		if (_viBullet->opacity <= 0.0f)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			_viBullet++;

	}
}

void Storm::fire(LPCWSTR imagename, float x, float y, float width, float height,
	float frameX, float frameY, float angle, int direction)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(imagename, width, height, frameX, frameY);
	bullet.speed = 4.0f;
	bullet.opacity = 1.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.direction = direction;

	if (direction == 1)
	{
		bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());
	}
	else
		bullet.rc = D2DMANAGER->RectMake(bullet.x - bullet.bulletImage->getFrameWidth(), bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);

}

void Storm::move()
{

}

void Storm::removeBullet(int arrNum)
{
	//벡터의 값을 지울떈  erase()
	_vBullet.erase(_vBullet.begin() + arrNum);
}