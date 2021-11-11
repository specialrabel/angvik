#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init(JOB job)
{


	_startItem.x = 800;
	_startItem.y = 300;

	switch (job)
	{
	case KING:
		generateItem(0, 6);
		_startItem.x += 50;
		generateItem(4, 2);
		_startItem.x += 40;
		generateItem(5, 2);
		_startItem.x += 40;
		generateItem(6, 2);
		break;
	case LANCER:
		generateItem(LANCER, WHITE);
		_startItem.x += 50;
		generateItem(BODY, BLUE);
		_startItem.x += 40;
		generateItem(LANCER, WHITE);
		_startItem.x += 50;
		generateItem(FOOT, BLUE);
		break;
	case SHEPHERD:
		generateItem(STAFF, PINK);
		_startItem.x += 70;
		generateItem(BODY, PINK);
		_startItem.x += 40;
		generateItem(HEAD, PINK);
		break;
	case PALADIN:
		generateItem(BOOMERANG, GOLD);
		_startItem.x += 30;
		generateItem(BODY, WHITE);
		_startItem.x += 40;
		generateItem(FOOT, WHITE);
		break;
	case BOTTLER:
		generateItem(BODY, SPECIAL);
		_startItem.x += 30;
		_startItem.y = 200;
		generateItem(OIL, WHITE);
		_startItem.x += 30;
		generateItem(OIL, GOLD);
		_startItem.x += 30;
		generateItem(OIL, PINK);
		break;
	case PEASANT:
		generateItem(EGG, NULL);
		_startItem.x += 30;
		generateItem(EGG, NULL);
		_startItem.x += 30;
		generateItem(EGG, NULL);
		_startItem.x += 30;
		generateItem(OIL, BLACK);
		break;
	case GREATGUY:
		int rNum = RND->getInt(6);
		switch (rNum)
		{

		case KING:
			generateItem(SWORD, WHITE);
			_startItem.x += 50;
			generateItem(BODY, GOLD);
			_startItem.x += 40;
			generateItem(HEAD, GOLD);
			_startItem.x += 40;
			generateItem(FOOT, GOLD);
			break;
		case LANCER:
			generateItem(LANCER, WHITE);
			_startItem.x += 50;
			generateItem(BODY, BLUE);
			_startItem.x += 40;
			generateItem(LANCER, WHITE);
			_startItem.x += 50;
			generateItem(FOOT, BLUE);
			break;
		case SHEPHERD:
			generateItem(STAFF, PINK);
			_startItem.x += 70;
			generateItem(BODY, PINK);
			_startItem.x += 40;
			generateItem(HEAD, PINK);
			break;
		case PALADIN:
			generateItem(BOOMERANG, GOLD);
			_startItem.x += 30;
			generateItem(BODY, WHITE);
			_startItem.x += 40;
			generateItem(FOOT, WHITE);
			break;
		case BOTTLER:
			generateItem(BODY, SPECIAL);
			_startItem.x += 30;
			_startItem.y = 200;
			generateItem(OIL, WHITE);
			_startItem.x += 30;
			generateItem(OIL, GOLD);
			_startItem.x += 30;
			generateItem(OIL, PINK);
			break;
		case PEASANT:
			generateItem(EGG, NULL);
			_startItem.x += 30;
			generateItem(EGG, NULL);
			_startItem.x += 30;
			generateItem(EGG, NULL);
			_startItem.x += 30;
			generateItem(OIL, BLACK);
			break;
		}
		break;
	}

	//_startItem.x = 5652;
	//_startItem.y = 906;
	//generateItem(KEY, NULL);
	_startItem.x = 5837;
	_startItem.y = 855;
	generateItem(BOX, NULL);
	_startItem.x = 6052;
	_startItem.y = 314;
	generateItem(BOX, NULL);

	return S_OK;
}

void itemManager::release()
{

}

void itemManager::update()
{


	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		if (_viWeapon->gravity != 0) {

			float y = (_viWeapon->rc.top + _viWeapon->rc.bottom) / 2;
			y += _viWeapon->gravity;

			if (_viWeapon->img->getMaxFrameX() >= 1) _viWeapon->rc = D2DMANAGER->RectMake(_viWeapon->rc.left, y, _viWeapon->img->getFrameWidth(), _viWeapon->img->getFrameHeight());
		}
	}


	for (_viArmor = _vArmor.begin(); _viArmor != _vArmor.end(); ++_viArmor)
	{
		if (_viArmor->gravity != 0) {
			float y = (_viArmor->rc.top + _viArmor->rc.bottom) / 2;
			y += _viArmor->gravity;

			_viArmor->rc = D2DMANAGER->RectMake(_viArmor->rc.left, y, _viArmor->img->getWidth(), _viArmor->img->getHeight());
		}
	}


	for (_viOther = _vOther.begin(); _viOther != _vOther.end(); ++_viOther)
	{
		if (_viOther->gravity != 0) {
			float y = (_viOther->rc.top + _viOther->rc.bottom) / 2;
			y += _viOther->gravity;

			_viOther->rc = D2DMANAGER->RectMake(_viOther->rc.left, y, _viOther->img->getWidth(), _viOther->img->getHeight());
		}
	}

	for (int i = 0; i < _vWeapon.size(); i++)
	{
		switch (_vWeapon[i].img->getMaxFrameX())
		{
		case 4:
			if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 1 && !_vWeapon[i].second)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].second = true;
			}
			else if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 2 && !_vWeapon[i].third)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].third = true;
			}
			else if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 3 && !_vWeapon[i].fourth)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].fourth = true;
			}
			else if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 4 && !_vWeapon[i].fifth)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].fifth = true;
			}
			if (_vWeapon[i].durability == 0) removeItem(i);
			break;

		case 3:
			if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 1 && !_vWeapon[i].second)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].second = true;
			}
			else if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 3 && !_vWeapon[i].third)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].third = true;
			}
			else if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX / 3 && !_vWeapon[i].fourth)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].fourth = true;
			}
			if (_vWeapon[i].durability == 0) removeItem(i);
			break;
		case 2:
			if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 1 && !_vWeapon[i].second)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].second = true;
			}
			else if (_vWeapon[i].durability < _vWeapon[i].durabilityMAX - 3 && !_vWeapon[i].third)
			{
				_vWeapon[i].img->setFrameX(_vWeapon[i].img->getFrameX() + 1);
				_vWeapon[i].third = true;
			}
			if (_vWeapon[i].durability == 0) removeItem(i);
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		for (int i = 0; i < _vWeapon.size(); i++)
		{
			_vWeapon[i].durability--;
		}
	}
}

void itemManager::render()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		if (_viWeapon->img->getMaxFrameX() >= 1)
		{
			_viWeapon->img->FrameRender(_viWeapon->rc.left, _viWeapon->rc.top, _viWeapon->img->getFrameX(), 0);
		}
		else if (_viWeapon->img->getMaxFrameX() == 0)
		{
			_viWeapon->img->render(_viWeapon->rc.left, _viWeapon->rc.top);
		}
	}

	for (_viArmor = _vArmor.begin(); _viArmor != _vArmor.end(); ++_viArmor)
	{
		if (_viArmor->img->getMaxFrameX() >= 1)
		{
			_viArmor->img->FrameRender(_viArmor->rc.left, _viArmor->rc.top, _viArmor->img->getFrameX(), 0);
		}
		else if (_viArmor->img->getMaxFrameX() == 0)
		{
			_viArmor->img->render(_viArmor->rc.left, _viArmor->rc.top);
		}
	}

	for (_viOther = _vOther.begin(); _viOther != _vOther.end(); ++_viOther)
	{
		if (_viOther->img->getMaxFrameX() >= 1)
		{
			_viOther->img->FrameRender(_viOther->rc.left, _viOther->rc.top, _viOther->img->getFrameX(), 0);
		}
		else if (_viOther->img->getMaxFrameX() == 0)
		{
			_viOther->img->render(_viOther->rc.left, _viOther->rc.top);
		}
	}
}

void itemManager::setDropItem(float x, float y, bool key)
{
	item* ITEM = new item;


	int rNum = RND->getInt(11);


	if (key)
	{
		generateItem(KEY, NULL, x, y);
	}

	if (!key)
	{
		if (rNum <= 3)
		{
			generateItem(rNum, (ITEMCOLOR)RND->getInt(COLOREND), x, y);
		}

		else if (4 <= rNum && rNum <= 6)
		{
			generateItem(rNum, (ITEMCOLOR)RND->getInt(COLOREND), x, y);

		}

		else if (7 == rNum)
		{
			generateItem(rNum, (ITEMCOLOR)RND->getInt(COLOREND), x, y);
		}

		else if (8 == rNum)
		{
			generateItem(rNum, NULL, x, y);
		}
	}
}

void itemManager::generateItem(int _typeNum, int _colorNum)
{
	tagWeapon weapon;
	ZeroMemory(&weapon, sizeof(tagWeapon));
	tagArmor armor;
	ZeroMemory(&armor, sizeof(tagArmor));
	tagOther other;
	ZeroMemory(&other, sizeof(tagOther));

	item* ITEM = new item;

	_typeNum = (ITEMTYPE)_typeNum;
	_colorNum = (ITEMTYPE)_colorNum;

	switch (_typeNum)
	{
	case SWORD:
		switch (_colorNum)
		{
		case BLACK: //12
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/°Ë.png", 352, 26, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/°Ë.png", 300, 23, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/°Ë.png", 346, 21, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/°Ë.png", 292, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/°Ë.png", 183, 16, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/°Ë.png", 352, 14, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/°Ë.png", 264, 17, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		}
		break;
	case LANCE:
		switch (_colorNum)
		{
		case BLACK: //12
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/Ã¢.png", 352, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/Ã¢.png", 368, 26, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/Ã¢.png", 388, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/Ã¢.png", 316, 14, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/Ã¢.png", 336, 16, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/Ã¢.png", 368, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/Ã¢.png", 336, 16, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		}
		break;
	case BOOMERANG:
		switch (_colorNum)
		{
		case BLACK: //7
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/ºÎ¸Þ¶û.png", 102, 26, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/ºÎ¸Þ¶û.png", 126, 32, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/ºÎ¸Þ¶û.png", 99, 23, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 3;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/ºÎ¸Þ¶û.png", 81, 25, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/ºÎ¸Þ¶û.png", 126, 48, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/ºÎ¸Þ¶û.png", 120, 23, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/ºÎ¸Þ¶û.png", 126, 34, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		}
		break;
	case STAFF:
		switch (_colorNum)
		{
		case BLACK: //7
			weapon.durability = weapon.durabilityMAX = 6;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/ÁöÆÎÀÌ.png", 440, 13, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 5;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/ÁöÆÎÀÌ.png", 340, 16, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/ÁöÆÎÀÌ.png", 440, 22, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 5;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/ÁöÆÎÀÌ.png", 435, 39, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/ÁöÆÎÀÌ.png", 500, 19, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 5;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/ÁöÆÎÀÌ.png", 275, 12, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/ÁöÆÎÀÌ.png", 445, 11, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			weapon.colorNum = _colorNum;
			break;
		}
		break;
	case HEAD:
		switch (_colorNum)
		{
		case BLACK: //2
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/black/¸ðÀÚ.png", 66, 33, 2, 1);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getFrameWidth(), armor.img->getFrameHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case BLUE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/blue/¸ðÀÚ.png", 28, 26);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case GOLD: //2(1)
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/gold/¸ðÀÚ.png", 28, 15);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case GREEN:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/green/¸ðÀÚ.png", 35, 29);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case PINK:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/pink/¸ðÀÚ.png", 35, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case RED:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/red/¸ðÀÚ.png", 29, 17);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case WHITE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/white/¸ðÀÚ.png", 26, 22);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		}
		break;
	case BODY:
		switch (_colorNum)
		{
		case BLACK: //2
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/black/°©¿Ê.png", 50, 29, 2, 1);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getFrameWidth(), armor.img->getFrameHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case BLUE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/blue/°©¿Ê.png", 23, 32);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case GOLD: //2(1)
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/gold/°©¿Ê.png", 24, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case GREEN:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/green/°©¿Ê.png", 27, 30);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case PINK:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/pink/°©¿Ê.png", 28, 27);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case RED:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/red/°©¿Ê.png", 22, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case WHITE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/white/°©¿Ê.png", 25, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case SPECIAL:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/bottler/°©¿Ê.png", 25, 27);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		}
		break;
	case FOOT:
		switch (_colorNum)
		{
		case BLACK: //2
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/black/½Å¹ß.png", 12, 14);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case BLUE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/blue/½Å¹ß.png", 13, 13);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case GOLD: //2(1)
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/gold/½Å¹ß.png", 11, 12);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case GREEN:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/green/½Å¹ß.png", 12, 13);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case PINK:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/pink/½Å¹ß.png", 14, 14);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case RED:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/red/½Å¹ß.png", 12, 12);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		case WHITE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/white/½Å¹ß.png", 12, 11);
			armor.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			armor.colorNum = _colorNum;
			break;
		}
		break;
	case OIL:
		switch (_colorNum)
		{
		case BLACK:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/°ËÀº¹°¾à.png", 21, 24);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		case BLUE:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ÆÄ¶õ¹°¾à.png", 17, 23);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		case GOLD:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/È²±Ý¹°¾à.png", 15, 22);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		case GREEN:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ÃÊ·Ï¹°¾à.png", 19, 24);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		case PINK:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ºÐÈ«¹°¾à.png", 19, 25);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		case RED:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/»¡°£¹°¾à.png", 18, 26);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		case WHITE:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ÇÏ¾á¹°¾à.png", 16, 23);
			other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			other.colorNum = _colorNum;
			break;
		}
		break;
	case EGG:
		other.gravity = 0.7f;
		other.img = new image;
		other.img->D_Init(L"image/others/¾Ë.png", 10, 12);
		other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
		other.typeNum = _typeNum;
		break;
	case KEY:
		other.gravity = 0.7f;
		other.img = new image;
		other.img->D_Init(L"image/weapon/¿­¼è.png", 23, 12);
		other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getWidth(), other.img->getHeight());
		other.typeNum = _typeNum;
		break;
	case BOX:
		other.gravity = 0.7f;
		other.img = new image;
		other.img->D_Init(L"image/others/¹Ú½º.png", 188, 31, 4, 1);
		other.rc = D2DMANAGER->RectMakeCenter(_startItem.x, _startItem.y, other.img->getFrameWidth(), other.img->getHeight());
		other.typeNum = _typeNum;
		break;
	}
	if (weapon.gravity != 0)
	{
		_vWeapon.push_back(weapon);
	}

	if (armor.gravity != 0)
	{
		_vArmor.push_back(armor);
	}

	if (other.gravity != 0)
	{
		_vOther.push_back(other);
	}

}

void itemManager::generateItem(int _typeNum, int _colorNum, float x, float y)
{
	tagWeapon weapon;
	ZeroMemory(&weapon, sizeof(tagWeapon));
	tagArmor armor;
	ZeroMemory(&armor, sizeof(tagArmor));
	tagOther other;
	ZeroMemory(&other, sizeof(tagOther));

	item* ITEM = new item;

	_typeNum = (ITEMTYPE)_typeNum;
	_colorNum = (ITEMTYPE)_colorNum;

	switch (_typeNum)
	{
	case SWORD:
		switch (_colorNum)
		{
		case BLACK: //12
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/°Ë.png", 352, 26, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/°Ë.png", 300, 23, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/°Ë.png", 346, 21, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/°Ë.png", 292, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/°Ë.png", 183, 16, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/°Ë.png", 352, 14, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/°Ë.png", 264, 17, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		}
		break;
	case LANCE:
		switch (_colorNum)
		{
		case BLACK: //12
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/Ã¢.png", 352, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/Ã¢.png", 368, 26, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/Ã¢.png", 388, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/Ã¢.png", 316, 14, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/Ã¢.png", 336, 16, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/Ã¢.png", 368, 18, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 12;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/Ã¢.png", 336, 16, 4, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		}
		break;
	case BOOMERANG:
		switch (_colorNum)
		{
		case BLACK: //7
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/ºÎ¸Þ¶û.png", 102, 26, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/ºÎ¸Þ¶û.png", 126, 32, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/ºÎ¸Þ¶û.png", 99, 23, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 3;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/ºÎ¸Þ¶û.png", 81, 25, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/ºÎ¸Þ¶û.png", 126, 48, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/ºÎ¸Þ¶û.png", 120, 23, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 4;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/ºÎ¸Þ¶û.png", 126, 34, 3, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		}
		break;
	case STAFF:
		switch (_colorNum)
		{
		case BLACK: //7
			weapon.durability = weapon.durabilityMAX = 6;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/black/ÁöÆÎÀÌ.png", 440, 13, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case BLUE: //5
			weapon.durability = weapon.durabilityMAX = 5;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/blue/ÁöÆÎÀÌ.png", 340, 16, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GOLD:
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/gold/ÁöÆÎÀÌ.png", 440, 22, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case GREEN:
			weapon.durability = weapon.durabilityMAX = 5;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/green/ÁöÆÎÀÌ.png", 435, 39, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case PINK: //5
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/pink/ÁöÆÎÀÌ.png", 500, 19, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case RED: //5
			weapon.durability = weapon.durabilityMAX = 5;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/red/ÁöÆÎÀÌ.png", 275, 12, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		case WHITE: //5
			weapon.durability = weapon.durabilityMAX = 7;
			weapon.gravity = 0.7f;
			weapon.img = new image;
			weapon.img->D_Init(L"image/weapon/white/ÁöÆÎÀÌ.png", 445, 11, 5, 1);
			weapon.rc = D2DMANAGER->RectMakeCenter(x, y, weapon.img->getFrameWidth(), weapon.img->getFrameHeight());
			weapon.typeNum = _typeNum;
			break;
		}
		break;
	case HEAD:
		switch (_colorNum)
		{
		case BLACK: //2
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/black/¸ðÀÚ.png", 66, 33, 2, 1);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getFrameWidth(), armor.img->getFrameHeight());
			armor.typeNum = _typeNum;
			break;
		case BLUE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/blue/¸ðÀÚ.png", 28, 26);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case GOLD: //2(1)
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/gold/¸ðÀÚ.png", 28, 15);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case GREEN:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/green/¸ðÀÚ.png", 35, 29);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case PINK:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/pink/¸ðÀÚ.png", 35, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case RED:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/red/¸ðÀÚ.png", 29, 17);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case WHITE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/white/¸ðÀÚ.png", 26, 22);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		}
		break;
	case BODY:
		switch (_colorNum)
		{
		case BLACK: //2
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/black/°©¿Ê.png", 50, 29, 2, 1);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getFrameWidth(), armor.img->getFrameHeight());
			armor.typeNum = _typeNum;
			break;
		case BLUE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/blue/°©¿Ê.png", 23, 32);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case GOLD: //2(1)
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/gold/°©¿Ê.png", 24, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case GREEN:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/green/°©¿Ê.png", 27, 30);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case PINK:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/pink/°©¿Ê.png", 28, 27);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case RED:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/red/°©¿Ê.png", 22, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case WHITE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/white/°©¿Ê.png", 25, 28);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case SPECIAL:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/bottler/°©¿Ê.png", 25, 27);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		}
		break;
	case FOOT:
		switch (_colorNum)
		{
		case BLACK: //2
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/black/½Å¹ß.png", 12, 14);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case BLUE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/blue/½Å¹ß.png", 13, 13);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case GOLD: //2(1)
			armor.durability = armor.durabilityMAX = 2;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/gold/½Å¹ß.png", 11, 12);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case GREEN:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/green/½Å¹ß.png", 12, 13);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case PINK:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/pink/½Å¹ß.png", 14, 14);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case RED:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/red/½Å¹ß.png", 12, 12);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		case WHITE:
			armor.durability = armor.durabilityMAX = 1;
			armor.gravity = 0.7f;
			armor.img = new image;
			armor.img->D_Init(L"image/armor/white/½Å¹ß.png", 12, 11);
			armor.rc = D2DMANAGER->RectMakeCenter(x, y, armor.img->getWidth(), armor.img->getHeight());
			armor.typeNum = _typeNum;
			break;
		}
		break;
	case OIL:
		switch (_colorNum)
		{
		case BLACK:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/°ËÀº¹°¾à.png", 21, 24);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		case BLUE:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ÆÄ¶õ¹°¾à.png", 17, 23);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		case GOLD:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/È²±Ý¹°¾à.png", 15, 22);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		case GREEN:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ÃÊ·Ï¹°¾à.png", 19, 24);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		case PINK:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ºÐÈ«¹°¾à.png", 19, 25);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		case RED:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/»¡°£¹°¾à.png", 18, 26);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		case WHITE:
			other.gravity = 0.7f;
			other.img = new image;
			other.img->D_Init(L"image/oil/ÇÏ¾á¹°¾à.png", 16, 23);
			other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
			other.typeNum = _typeNum;
			break;
		}
		break;
	case EGG:
		other.gravity = 0.7f;
		other.img = new image;
		other.img->D_Init(L"image/others/¾Ë.png", 10, 12);
		other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
		other.typeNum = _typeNum;
		break;
	case KEY:
		other.gravity = 0.7f;
		other.img = new image;
		other.img->D_Init(L"image/weapon/¿­¼è.png", 23, 12);
		other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getWidth(), other.img->getHeight());
		other.typeNum = _typeNum;
		break;
	case BOX:
		other.gravity = 0.7f;
		other.img = new image;
		other.img->D_Init(L"image/others/¹Ú½º.png", 188, 31, 4, 1);
		other.rc = D2DMANAGER->RectMakeCenter(x, y, other.img->getFrameWidth(), other.img->getHeight());
		other.typeNum = _typeNum;
		break;
	}
	if (weapon.gravity != 0)
	{
		_vWeapon.push_back(weapon);
	}

	if (armor.gravity != 0)
	{
		_vArmor.push_back(armor);
	}

	if (other.gravity != 0)
	{
		_vOther.push_back(other);
	}
}

void itemManager::setGravity(int typeNum, int num, float i)
{
	if (typeNum <= STAFF)
	{
		int height = (_vWeapon[num].rc.bottom - _vWeapon[num].rc.top);
		_vWeapon[num].rc.top = i - height;
		_vWeapon[num].rc.bottom = i;
		_vWeapon[num].y = _vWeapon[num].rc.top;
		_vWeapon[num].gravity = 0;
	}

	if (HEAD <= typeNum && typeNum <= FOOT)
	{
		int height = (_vArmor[num].rc.bottom - _vArmor[num].rc.top);
		_vArmor[num].rc.top = i - height;
		_vArmor[num].rc.bottom = i;
		_vArmor[num].y = _vArmor[num].rc.top;
		_vArmor[num].gravity = 0;
	}

	if (OIL <= typeNum && typeNum < TYPEEND)
	{
		int height = (_vOther[num].rc.bottom - _vOther[num].rc.top);
		_vOther[num].rc.top = i - height;
		_vOther[num].rc.bottom = i;
		_vOther[num].y = _vOther[num].rc.top;
		_vOther[num].gravity = 0;
	}
}

void itemManager::removeItem(int arrNum)
{
	_vWeapon[arrNum].img->release();
	_vWeapon.erase(_vWeapon.begin() + arrNum);
}

void itemManager::removeArmor(int arrNum)
{
	_vArmor[arrNum].img->release();
	_vArmor.erase(_vArmor.begin() + arrNum);

}

void itemManager::removeOther(int arrNum)
{
	_vOther[arrNum].img->release();
	_vOther.erase(_vOther.begin() + arrNum);

}

void itemManager::setDropItemMenu(float x, float y, int tpye, int color)
{

	//»ý¼º À§Ä¡ ¼³Á¤
	_startItem.x = x;
	_startItem.y = y;
	//¾ÆÀÌÅÆ »ý¼º
	generateItem(tpye, color);

}
