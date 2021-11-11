#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "menu.h"

void player::InputHandle()
{
	State* newState = _state->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}

HRESULT player::init()
{
	//플레이어 이미지 불러오기
	playerImageInit();
	//플레이어 초기화
	playerInfoInit();

	/******************************************************/
	_frag = new fragment;
	_frag->init(30, 1000);

	_pb = new Player_bullet;
	_pb->init(30, 1000, _frag);

	_spear = new Weapon;
	_spear->init(10, 10000);
	/******************************************************/

	_state = new IdleState();
	_state->enter(this);
	return S_OK;
}

void player::release()
{
	_state->exit(this);
}

void player::update()
{
	++_player.hitInterval;

	InputHandle();
	_state->update(this);

	playerEquipUpdate(); // 플레이어 무기애니메이션을 업데이트시킴.

	/******************************************************/
	bullet_test();
	_pb->update();
	_frag->update();
	_spear->update();
	/******************************************************/

	//나뭇가지 생기기전까진 냅둘것(슈퍼점프?)
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player.rc.top -= _player.speed;
		_player.rc.bottom -= _player.speed;
		_player.y -= _player.speed;

		if (_player.y <= 0)
		{
			_player.y = 0;
		}
	}

	KEYANIMANAGER->update();

	_player.rc_head = D2DMANAGER->RectMake(_player.x + _player.move_headX, _player.y + 7 + _player.move_headY, 25, 20);
	_player.rc_body = D2DMANAGER->RectMake(_player.x, _player.y + 25 + _player.move_bodyY, 25, 30);
	_player.rc_Larm = D2DMANAGER->RectMake(_player.x + _player.move_LarmX - 5, _player.y + 22 + _player.move_LarmY, 15, 25);
	_player.rc_Rarm = D2DMANAGER->RectMake(_player.x + _player.move_RarmX + 8, _player.y + 22 + _player.move_RarmY, 15, 25);
	_player.rc = D2DMANAGER->RectMake(_player.x, _player.y, 25, 55);
}

void player::render()
{
	//D2DMANAGER->Rectangle(_player.rc);
	//D2DMANAGER->Rectangle(_player.rc_head);
	//D2DMANAGER->Rectangle(_player.rc_body);
	//D2DMANAGER->Rectangle(_player.rc_Larm);
	//D2DMANAGER->Rectangle(_player.rc_Rarm);

	if (_player.dir == RIGHT)
	{
		_player.img_Rarm->Framerotation_start(_player.rc_Rarm.left - 12, _player.rc_Rarm.top - 20, _player.angle_Rarm);
		_player.img_Rarm->aniRender(_player.rc_Rarm.left - 12, _player.rc_Rarm.top - 10, _player.ani_Rarm, _player.hitOpacity);
		_player.img_Rarm->rotation_end();
		playerEquipRender(_player.weapon_right_type, RIGHT);
		_player.img_body->aniRender(_player.rc_body.left - 10, _player.rc_body.top - 15, _player.ani_body, _player.hitOpacity);
		playerEquipRender(BODY);
		_player.img_head->aniRender(_player.rc_head.left - 10, _player.rc_head.top - 15, _player.ani_head, _player.hitOpacity);
		playerEquipRender(HEAD);
		playerEquipRender(_player.weapon_left_type, LEFT);
		_player.img_Larm->Framerotation_start(_player.rc_Larm.left - 12, _player.rc_Larm.top - 20, _player.angle_Larm);
		_player.img_Larm->aniRender(_player.rc_Larm.left - 12, _player.rc_Larm.top - 10, _player.ani_Larm, _player.hitOpacity);
		_player.img_Larm->rotation_end();
	}
	else if (_player.dir == LEFT)
	{
		_player.img_Larm->Framerotation_start(_player.rc_Larm.left - 12, _player.rc_Larm.top - 20, _player.angle_Larm);
		_player.img_Larm->aniRender(_player.rc_Larm.left - 12, _player.rc_Larm.top - 10, _player.ani_Larm, _player.hitOpacity);
		_player.img_Larm->rotation_end();
		playerEquipRender(_player.weapon_left_type, LEFT);
		_player.img_body->aniRender(_player.rc_body.left - 10, _player.rc_body.top - 15, _player.ani_body, _player.hitOpacity);
		playerEquipRender(BODY);
		_player.img_head->aniRender(_player.rc_head.left - 10, _player.rc_head.top - 15, _player.ani_head, _player.hitOpacity);
		playerEquipRender(HEAD);
		playerEquipRender(_player.weapon_right_type, RIGHT);
		_player.img_Rarm->Framerotation_start(_player.rc_Rarm.left - 12, _player.rc_Rarm.top - 20, _player.angle_Rarm);
		_player.img_Rarm->aniRender(_player.rc_Rarm.left - 12, _player.rc_Rarm.top - 10, _player.ani_Rarm, _player.hitOpacity);
		_player.img_Rarm->rotation_end();
	}

	/******************************************************/
	_pb->render();
	_frag->render();
	_spear->render();
	/******************************************************/

	/*WCHAR str[128];
	swprintf_s(str, L"cameraX : %.1f / %.1f", _player.rc.left, (float)(MAPSIZEX));
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _player.rc.left + 80 - CAMERAMANAGER->get_camera_x(), _player.rc.top - 40 - CAMERAMANAGER->get_camera_y(),
		_player.x + WINSIZEX, _player.y + WINSIZEY);

	swprintf_s(str, L"cameraY : %.1f / %.1f", _player.rc.top, (float)(MAPSIZEY));
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _player.rc.left + 80 - CAMERAMANAGER->get_camera_x(), _player.rc.top - 20 - CAMERAMANAGER->get_camera_y(),
		_player.x + WINSIZEX, _player.y + WINSIZEY);

	swprintf_s(str, L"isground : %d", _player.isground);
	D2DMANsAGER->sDraswTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _player.rc.left + 80 - CAMERAMANAGER->get_camera_x(), _player.rc.top - CAMERAMANAGER->get_camera_y(),
		_sssplayer.x + WINSIZEX, _player.y + WINSIZEY);

	swprintf_s(str, L"isJump : %d", _player.isJump);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _player.rc.left + 80 - CAMERAMANAGER->get_camera_x(), _player.rc.top + 20 - CAMERAMANAGER->get_camera_y(),
		_player.x + WINSIZEX, _player.y + WINSIZEY);

	swprintf_s(str, L"isHit : %d", _player.isHit);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _player.rc.left + 80 - CAMERAMANAGER->get_camera_x(), _player.rc.top + 40 - CAMERAMANAGER->get_camera_y(),
		_player.x + WINSIZEX, _player.y + WINSIZEY);*/
}

void player::playerSpeed()
{
	_player.speedPower = 0.2f;

	if (_player.speed < 4)
	{
		_player.speed += _player.speedPower;
	}
}

void player::playerEquipRender(int type)
{
	if (type == HEAD)
	{
		if (_player.helmet_color == COLOREND)
		{

		}
		else
		{
			_player.img_helmet->aniRender(_player.rc_head.left - 13, _player.rc_head.top - 23, _player.ani_helmet);
		}
	}
	else if (type == BODY)
	{
		if (_player.armor_color == COLOREND)
		{

		}
		else
		{
			_player.img_armor->aniRender(_player.rc_body.left - 10, _player.rc_body.top - 18, _player.ani_armor);
		}

		if (_player.shoes_color == COLOREND)
		{

		}
		else
		{

		}
	}

}

void player::playerEquipRender(int type, int LR)
{
	if (type != TYPEEND)
	{
		if (LR == LEFT)
		{
			if (_player.weapon_left_color == GREEN)
			{
				_player.img_Lweapon->Framerotation_start(_player.rc_Larm.left - 26 + _player.move_LweaponX, _player.rc_Larm.top - 70 + _player.move_LweaponY, _player.angle_Lweapon);
				_player.img_Lweapon->aniRender(_player.rc_Larm.left - 10 + _player.move_LweaponX, _player.rc_Larm.top - 70 + _player.move_LweaponY, _player.ani_Lweapon);
				_player.img_Lweapon->rotation_end();
			}
			else if (_player.weapon_left_color == GOLD)
			{
				_player.img_Lweapon->Framerotation_start(_player.rc_Larm.left - 26 + _player.move_LweaponX, _player.rc_Larm.top - 70 + _player.move_LweaponY, _player.angle_Lweapon);
				_player.img_Lweapon->aniRender(_player.rc_Larm.left - 10 + _player.move_LweaponX, _player.rc_Larm.top - 70 + _player.move_LweaponY, _player.ani_Lweapon);
				_player.img_Lweapon->rotation_end();
			}
			else if (_player.weapon_left_color == COLOREND)
			{

			}
		}

		if (LR == RIGHT)
		{
			if (_player.weapon_right_color == GREEN)
			{
				_player.img_Rweapon->Framerotation_start(_player.rc_Rarm.left - 26 + _player.move_RweaponX, _player.rc_Larm.top - 70 + _player.move_RweaponY, _player.angle_Rweapon);
				_player.img_Rweapon->aniRender(_player.rc_Rarm.left - 10 + _player.move_RweaponX, _player.rc_Rarm.top - 70 + _player.move_RweaponY, _player.ani_Rweapon);
				_player.img_Rweapon->rotation_end();
			}
			else if (_player.weapon_left_color == GOLD)
			{
				_player.img_Rweapon->Framerotation_start(_player.rc_Rarm.left - 26 + _player.move_RweaponX, _player.rc_Larm.top - 70 + _player.move_RweaponY, _player.angle_Rweapon);
				_player.img_Rweapon->aniRender(_player.rc_Rarm.left - 10 + _player.move_RweaponX, _player.rc_Rarm.top - 70 + _player.move_RweaponY, _player.ani_Rweapon);
				_player.img_Rweapon->rotation_end();
			}
			else if (_player.weapon_left_color == COLOREND)
			{

			}
		}
	}
}

bool player::pickUpItem(int type, int color, int durability)
{
	//아이템이 무기일 경우
	if (type == SWORD || type == LANCE || type == BOOMERANG || type == STAFF)
	{
		//플레이어 왼손 오른손 확인
		if (_player.weapon_left_color == COLOREND)
		{
			_player.weapon_left_color = color;
			_player.weapon_left_type = type;
			_player.weapon_left_durability = durability;
			return true;
		}
		if (_player.weapon_right_color == COLOREND)
		{
			_player.weapon_right_color = color;
			_player.weapon_right_type = type;
			_player.weapon_right_durability = durability;
			return true;
		}

	}
	//아이템이 갑옷일 경우
	if (type == HEAD)
	{
		if (_player.helmet_color == COLOREND)
		{
			_player.helmet_color = color;
			_player.helmet_durability = durability;
			return true;

		}
	}
	if (type == BODY)
	{
		if (_player.armor_color == COLOREND)
		{
			_player.armor_color = color;
			_player.armor_durability = durability;
			return true;

		}
	}
	if (type == FOOT)
	{
		if (_player.shoes_color == COLOREND)
		{
			_player.shoes_color = color;
			_player.shoes_durability = durability;
			return true;

		}
	}

	return _menu->checkPickUp(type, color, durability);

}


void player::playerImageInit()
{
	_player.img_head = IMAGEMANAGER->addFrameImage("playerHead", L"image/player/playerHead.png", 200, 200, 4, 4);

	int nothing_head[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("playerNothingHead", "playerHead", nothing_head, 1, 1, true);

	int rightIdle_head[] = { 0,	1 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdleHead", "playerHead", rightIdle_head, 2, 1, true);

	int leftIdle_head[] = { 4,	5 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdleHead", "playerHead", leftIdle_head, 2, 1, true);


	_player.img_body = IMAGEMANAGER->addFrameImage("playerBody", L"image/player/playerBody.png", 300, 300, 6, 6);

	int nothing_body[] = { 35 };
	KEYANIMANAGER->addArrayFrameAnimation("playerNothingBody", "playerBody", nothing_body, 1, 1, true);

	int rightIdle_body[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdleBody", "playerBody", rightIdle_body, 1, 1, true);

	int leftIdle_body[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdleBody", "playerBody", leftIdle_body, 1, 1, true);

	int rightPickUp_body[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightPickUpBody", "playerBody", rightPickUp_body, 1, 1, true);

	int leftPickUp_body[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftPickUpBody", "playerBody", leftPickUp_body, 1, 1, true);

	int rightMove_body[] = { 6, 7, 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveBody", "playerBody", rightMove_body, 6, 16, true);

	int leftMove_body[] = { 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveBody", "playerBody", leftMove_body, 6, 16, true);

	int rightJump_body[] = { 18, 19, 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightJumpBody", "playerBody", rightJump_body, 6, 8, false);

	int leftJump_body[] = { 24, 25, 26, 27, 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftJumpBody", "playerBody", leftJump_body, 6, 8, false);



	_player.img_Larm = IMAGEMANAGER->addFrameImage("playerLarm", L"image/player/playerArm.png", 500, 1000, 10, 20);

	int nothing_Larm[] = { 99 };
	KEYANIMANAGER->addArrayFrameAnimation("playerNothingLarm", "playerLarm", nothing_Larm, 1, 1, true);

	int rightIdle_Larm[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdleLarm", "playerLarm", rightIdle_Larm, 1, 1, true);

	int rightMove_Larm[] = { 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveLarm", "playerLarm", rightMove_Larm, 7, 11, true);

	int rightMoveWeapon_Larm[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveWeaponLarm", "playerLarm", rightMoveWeapon_Larm, 9, 16, true);

	int rightAttack_Larm[] = { 40, 41, 42, 43, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttackLarm", "playerLarm", rightAttack_Larm, 5, 30, false);

	int rightAttackWeapon_Larm[] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttackWeaponLarm", "playerLarm", rightAttackWeapon_Larm, 10, 35, false);

	int leftIdle_Larm[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdleLarm", "playerLarm", leftIdle_Larm, 1, 1, true);

	int leftMove_Larm[] = { 31, 32, 33, 34, 35, 36, 37 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveLarm", "playerLarm", leftMove_Larm, 7, 11, true);

	int leftMoveWeapon_Larm[] = { 90, 91, 92, 93, 94, 95, 96, 97, 98 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveWeaponLarm", "playerLarm", leftMoveWeapon_Larm, 9, 16, true);

	int leftAttack_Larm[] = { 50, 51, 52, 53, 54 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttackLarm", "playerLarm", leftAttack_Larm, 5, 30, false);

	int leftAttackWeapon_Larm[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttackWeaponLarm", "playerLarm", leftAttackWeapon_Larm, 10, 35, false);


	_player.img_Rarm = IMAGEMANAGER->addFrameImage("playerRarm", L"image/player/playerArm.png", 500, 1000, 10, 20);

	int nothing_Rarm[] = { 99 };
	KEYANIMANAGER->addArrayFrameAnimation("playerNothingRarm", "playerRarm", nothing_Rarm, 1, 1, true);

	int rightIdle_Rarm[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdleRarm", "playerRarm", rightIdle_Rarm, 1, 1, true);

	int rightMove_Rarm[] = { 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveRarm", "playerRarm", rightMove_Rarm, 7, 11, true);

	int rightMoveWeapon_Rarm[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveWeaponRarm", "playerRarm", rightMoveWeapon_Rarm, 9, 16, true);

	int rightAttack_Rarm[] = { 40, 41, 42, 43, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttackRarm", "playerRarm", rightAttack_Rarm, 5, 30, false);

	int rightAttackWeapon_Rarm[] = { 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttackWeaponRarm", "playerRarm", rightAttackWeapon_Rarm, 10, 35, false);

	int leftIdle_Rarm[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdleRarm", "playerRarm", leftIdle_Rarm, 1, 1, true);

	int leftMove_Rarm[] = { 21, 22, 23, 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveRarm", "playerRarm", leftMove_Rarm, 7, 11, true);

	int leftMoveWeapon_Rarm[] = { 70, 71, 72, 73, 74, 75, 76, 77, 78 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveWeaponRarm", "playerRarm", leftMoveWeapon_Rarm, 9, 16, true);

	int leftAttack_Rarm[] = { 50, 51, 52, 53, 54 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttackRarm", "playerRarm", leftAttack_Rarm, 5, 30, false);

	int leftAttackWeapon_Rarm[] = { 130, 131, 132, 133, 134, 135, 136, 137, 138, 139 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttackWeaponRarm", "playerRarm", leftAttackWeapon_Rarm, 10, 35, false);


	_player.img_Lweapon = IMAGEMANAGER->addFrameImage("Lweapon", L"image/weapon/weapon.png", 500, 500, 5, 5);

	int nothing_Lweapon[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("nothingLweapon", "Lweapon", nothing_Lweapon, 1, 1, true);

	int green_LweaponR[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("greenLweaponR", "Lweapon", green_LweaponR, 1, 1, true);

	int green_LweaponL[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("greenLweaponL", "Lweapon", green_LweaponL, 1, 1, true);

	int green_LweaponRS[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("greenLweaponRS", "Lweapon", green_LweaponRS, 1, 1, true);

	int green_LweaponLS[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("greenLweaponLS", "Lweapon", green_LweaponLS, 1, 1, true);

	int gold_LweaponR[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("goldLweaponR", "Lweapon", gold_LweaponR, 1, 1, true);

	int gold_LweaponL[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("goldLweaponL", "Lweapon", gold_LweaponL, 1, 1, true);

	int gold_LweaponRS[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("goldLweaponRS", "Lweapon", gold_LweaponRS, 1, 1, true);

	int gold_LweaponLS[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("goldLweaponLS", "Lweapon", gold_LweaponLS, 1, 1, true);




	_player.img_Rweapon = IMAGEMANAGER->addFrameImage("Rweapon", L"image/weapon/weapon.png", 500, 500, 5, 5);

	int nothing_Rweapon[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("nothingRweapon", "Rweapon", nothing_Rweapon, 1, 1, true);

	int green_RweaponR[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("greenRweaponR", "Rweapon", green_RweaponR, 1, 1, true);

	int green_RweaponL[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("greenRweaponL", "Rweapon", green_RweaponL, 1, 1, true);

	int green_RweaponRS[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("greenRweaponRS", "Rweapon", green_RweaponRS, 1, 1, true);

	int green_RweaponLS[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("greenRweaponLS", "Rweapon", green_RweaponLS, 1, 1, true);

	int gold_RweaponR[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("goldRweaponR", "Rweapon", gold_RweaponR, 1, 1, true);

	int gold_RweaponL[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("goldRweaponL", "Rweapon", gold_RweaponL, 1, 1, true);

	int gold_RweaponRS[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("goldRweaponRS", "Rweapon", gold_RweaponRS, 1, 1, true);

	int gold_RweaponLS[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("goldRweaponLS", "Rweapon", gold_RweaponLS, 1, 1, true);


	_player.img_helmet = IMAGEMANAGER->addFrameImage("helmet", L"image/weapon/helmet.png", 500, 500, 10, 10);

	int nothing_helmet[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("nothingHelmet", "helmet", nothing_helmet, 1, 1, true);

	int green_helmetR[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("greenHelmetR", "helmet", green_helmetR, 1, 1, true);

	int green_helmetL[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("greenHelmetL", "helmet", green_helmetL, 1, 1, true);

	int gold_helmetR[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("goldHelmetR", "helmet", gold_helmetR, 1, 1, true);

	int gold_helmetL[] = { 11 };
	KEYANIMANAGER->addArrayFrameAnimation("goldHelmetL", "helmet", gold_helmetL, 1, 1, true);


	_player.img_armor = IMAGEMANAGER->addFrameImage("armor", L"image/weapon/armor.png", 500, 500, 10, 10);

	int nothing_armor[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("nothingArmor", "armor", nothing_armor, 1, 1, true);

	int green_armorR[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("greenArmorR", "armor", green_armorR, 1, 1, true);

	int green_armorL[] = { 11 };
	KEYANIMANAGER->addArrayFrameAnimation("greenArmorL", "armor", green_armorL, 1, 1, true);

	int gold_armorR[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("goldArmorR", "armor", gold_armorR, 1, 1, true);

	int gold_armorL[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("goldArmorL", "armor", gold_armorL, 1, 1, true);



	_player.ani_head = KEYANIMANAGER->findAnimation("playerRightIdleHead");
	_player.ani_body = KEYANIMANAGER->findAnimation("playerRightIdleBody");
	_player.ani_Larm = KEYANIMANAGER->findAnimation("playerRightIdleLarm");
	_player.ani_Rarm = KEYANIMANAGER->findAnimation("playerRightIdleRarm");
	_player.ani_Lweapon = KEYANIMANAGER->findAnimation("nothingLweapon");
	_player.ani_Rweapon = KEYANIMANAGER->findAnimation("nothingRweapon");
	_player.ani_helmet = KEYANIMANAGER->findAnimation("nothingHelmet");
	_player.ani_armor = KEYANIMANAGER->findAnimation("nothingArmor");

	//장비타입, 색상 초기화
	_player.weapon_left_type = SWORD;
	_player.weapon_right_type = STAFF;
	_player.weapon_left_color = GOLD;
	_player.weapon_right_color = GREEN;
	_player.helmet_color = GREEN;
	_player.armor_color = GREEN;
}

void player::playerInfoInit()
{
	//_player.x = 5450;
	//_player.y = 919.0f;
	
	_player.x = 500;
	_player.y = 100;

	_player.dir = RIGHT;

	_player.rc_head = D2DMANAGER->RectMake(_player.x + _player.move_headX, _player.y + 5, 25, 20);
	_player.rc_body = D2DMANAGER->RectMake(_player.x, _player.y + 25, 25, 30);
	_player.rc_Larm = D2DMANAGER->RectMake(_player.x - 5, _player.y + 20, 15, 20);
	_player.rc_Rarm = D2DMANAGER->RectMake(_player.x + 20, _player.y + 20, 15, 20);
	_player.rc = D2DMANAGER->RectMake(_player.x, _player.y, 25, 55);
	_player.isground = false;
	_player.jumpPower = 0;
	_player.gravity = 0.7f;
	_player.speedPower = 0.2f;
}

void player::playerEquipUpdate()
{
	if (_player.weapon_left_color == GREEN)
	{
		if (_player.weapon_left_type == SWORD)
		{
			if (_player.dir == RIGHT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("greenLweaponR");
				_player.ani_Lweapon->start();
			}
			else if (_player.dir == LEFT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("greenLweaponL");
				_player.ani_Lweapon->start();
			}
		}
		if (_player.weapon_left_type == STAFF)
		{
			if (_player.dir == RIGHT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("greenLweaponRS");
				_player.ani_Lweapon->start();
			}
			else if (_player.dir == LEFT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("greenLweaponLS");
				_player.ani_Lweapon->start();
			}
		}
	}
	else if (_player.weapon_left_color == GOLD)
	{
		if (_player.weapon_left_type == SWORD)
		{
			if (_player.dir == RIGHT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("goldLweaponR");
				_player.ani_Lweapon->start();
			}
			else if (_player.dir == LEFT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("goldLweaponL");
				_player.ani_Lweapon->start();
			}
		}
		if (_player.weapon_left_type == STAFF)
		{
			if (_player.dir == RIGHT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("goldLweaponRS");
				_player.ani_Lweapon->start();
			}
			else if (_player.dir == LEFT)
			{
				_player.ani_Lweapon = KEYANIMANAGER->findAnimation("goldLweaponLS");
				_player.ani_Lweapon->start();
			}
		}

	}
	else if (_player.weapon_left_color == COLOREND)
	{

	}

	if (_player.weapon_right_color == GREEN)
	{
		if (_player.weapon_right_type == SWORD)
		{
			if (_player.dir == RIGHT)
			{
				_player.ani_Rweapon = KEYANIMANAGER->findAnimation("greenRweaponR");
				_player.ani_Rweapon->start();
			}
			else if (_player.dir == LEFT)
			{
				_player.ani_Rweapon = KEYANIMANAGER->findAnimation("greenRweaponL");
				_player.ani_Rweapon->start();
			}
		}
		if (_player.weapon_right_type == STAFF)
		{
			if (_player.dir == RIGHT)
			{
				_player.ani_Rweapon = KEYANIMANAGER->findAnimation("greenRweaponRS");
				_player.ani_Rweapon->start();
			}
			else if (_player.dir == LEFT)
			{
				_player.ani_Rweapon = KEYANIMANAGER->findAnimation("greenRweaponLS");
				_player.ani_Rweapon->start();
			}
		}
	}
	else if (_player.weapon_left_color == GOLD)
	{
		if (_player.dir == RIGHT)
		{
			_player.ani_Rweapon = KEYANIMANAGER->findAnimation("goldRweaponR");
			_player.ani_Rweapon->start();
		}
		else if (_player.dir == LEFT)
		{
			_player.ani_Rweapon = KEYANIMANAGER->findAnimation("goldRweaponL");
			_player.ani_Rweapon->start();
		}
	}
	else if (_player.weapon_left_color == COLOREND)
	{

	}

	if (_player.helmet_color == GREEN)
	{
		if (_player.dir == RIGHT)
		{
			_player.ani_helmet = KEYANIMANAGER->findAnimation("greenHelmetR");
			_player.ani_helmet->start();
		}
		else if (_player.dir == LEFT)
		{
			_player.ani_helmet = KEYANIMANAGER->findAnimation("greenHelmetL");
			_player.ani_helmet->start();
		}
	}
	else if (_player.helmet_color == GOLD)
	{
		if (_player.dir == RIGHT)
		{
			_player.ani_helmet = KEYANIMANAGER->findAnimation("goldHelmetR");
			_player.ani_helmet->start();
		}
		else if (_player.dir == LEFT)
		{
			_player.ani_helmet = KEYANIMANAGER->findAnimation("goldHelmetL");
			_player.ani_helmet->start();
		}
	}
	else if (_player.helmet_color == COLOREND)
	{

	}

	if (_player.armor_color == GREEN)
	{
		if (_player.dir == RIGHT)
		{
			_player.ani_armor = KEYANIMANAGER->findAnimation("greenArmorR");
			_player.ani_armor->start();
		}
		else if (_player.dir == LEFT)
		{
			_player.ani_armor = KEYANIMANAGER->findAnimation("greenArmorL");
			_player.ani_armor->start();
		}
	}
	else if (_player.armor_color == GOLD)
	{
		if (_player.dir == RIGHT)
		{
			_player.ani_armor = KEYANIMANAGER->findAnimation("goldArmorR");
			_player.ani_armor->start();
		}
		else if (_player.dir == LEFT)
		{
			_player.ani_armor = KEYANIMANAGER->findAnimation("goldArmorL");
			_player.ani_armor->start();
		}
	}
	else if (_player.armor_color == COLOREND)
	{

	}

	if (_player.shoes_color == GREEN)
	{
		//_player.ani_Rweapon = KEYANIMANAGER->findAnimation("greenRweapon");
		//_player.ani_Rweapon->start();
	}
	else if (_player.shoes_color == GOLD)
	{

	}
	else if (_player.shoes_color == COLOREND)
	{

	}
}


void player::bullet_test()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_player.dir == LEFT)
		{
			_pb->fire(L"bullet_img/Light_attack2.png", _player.rc_body.left - 200, -200, 6000, 1000, 30, 1, 0);
		}
		else
			_pb->fire(L"bullet_img/Light_attack2.png", _player.rc_body.right + 200, -200, 6000, 1000, 30, 1, 1);
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (_player.dir == LEFT)
		{
			_pb->fire(L"bullet_img/sheep.png", _player.rc_body.left - 10, _player.rc_body.top, 159, 76, 3, 2, -1);
		}
		else
			_pb->fire(L"bullet_img/sheep.png", _player.rc_body.right + 10, _player.rc_body.top, 159, 76, 3, 2, 1);
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_player.dir == LEFT)
		{
			_spear->fire(L"bullet_img/창.png", _player.rc_body.left - 10, _player.rc_body.top - 20, 336, 16, 4, 1, -1);
		}
		else if (_player.dir == RIGHT)
			_spear->fire(L"bullet_img/창.png", _player.rc_body.right + 10, _player.rc_body.top - 20, 336, 16, 4, 1, 1);
	}
}
