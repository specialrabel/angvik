#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "hitState.h"

State* JumpState::inputHandle(player* player)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && player->getTagPlayer()->isground)
	{
		player->getTagPlayer()->dir = RIGHT;
		return new RunState();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && player->getTagPlayer()->isground)
	{
		player->getTagPlayer()->dir = LEFT;
		return new RunState();
	}
	if (player->getTagPlayer()->isground)
	{
		return new IdleState();
	}
	if (player->getTagPlayer()->isHit)
	{
		return new HitState();
	}

	return nullptr;
}

void JumpState::update(player* player)
{
	//공격
	Attack(player, player->getTagPlayer()->weapon_left_type, player->getTagPlayer()->weapon_right_type);

	//각도조절
	if (player->getTagPlayer()->angle_Rweapon > -70)
	{
		player->getTagPlayer()->move_RweaponX += 0.1f;

		player->getTagPlayer()->move_RweaponY -= 0.2f;
		player->getTagPlayer()->angle_Rweapon -= 0.8f;
	}
	if (player->getTagPlayer()->angle_Lweapon < 35)
	{
		player->getTagPlayer()->move_LweaponX -= 0.5f;

		player->getTagPlayer()->move_LweaponY += 0.2f;
		player->getTagPlayer()->angle_Lweapon -= -2.8f;
	}
	if (player->getTagPlayer()->jumpPower < 0)
	{
		player->getTagPlayer()->angle_Rweapon = -75;

		player->getTagPlayer()->angle_Lweapon = 40;
	}

	if (player->getTagPlayer()->isAttackL == false && player->getTagPlayer()->dir == RIGHT)
	{
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightIdleLarm");
	}
	else if (player->getTagPlayer()->isAttackL == false && player->getTagPlayer()->dir == LEFT)
	{
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftIdleLarm");
		player->getTagPlayer()->move_LarmX = 20;
		player->getTagPlayer()->move_LarmY = 0;
	}
	if (player->getTagPlayer()->isAttackR == false && player->getTagPlayer()->dir == RIGHT)
	{
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightIdleRarm");
		player->getTagPlayer()->move_RarmX = -20;
		player->getTagPlayer()->move_RarmY = 0;
	}
	else if (player->getTagPlayer()->isAttackR == false && player->getTagPlayer()->dir == LEFT)
	{
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftIdleRarm");
	}


	player->playerSpeed();

	if (player->getTagPlayer()->dir == RIGHT)
	{
		if (player->getTagPlayer()->angle_Rarm > -12)
		{
			player->getTagPlayer()->angle_Rarm -= 0.8f;
		}

		if (player->getTagPlayer()->jumpPower > 0)
		{
			player->getTagPlayer()->move_headX = 1;
			player->getTagPlayer()->angle_Larm += 1.3f;
		}
		if (player->getTagPlayer()->jumpPower <= 0)
		{
			player->getTagPlayer()->move_headX = -2;
			player->getTagPlayer()->angle_Larm = 45.0f;
		}
		player->getTagPlayer()->move_LarmX = 0;
		player->getTagPlayer()->move_RarmX = 0;
	}
	else if (player->getTagPlayer()->dir == LEFT)
	{
		if (player->getTagPlayer()->angle_Larm < 12)
		{
			player->getTagPlayer()->angle_Larm += 1.2f;
		}

		if (player->getTagPlayer()->jumpPower > 0)
		{
			player->getTagPlayer()->move_headX = -2;
			player->getTagPlayer()->angle_Rarm -= 1.3f;
		}
		if (player->getTagPlayer()->jumpPower <= 0)
		{
			player->getTagPlayer()->move_headX = 1;
			player->getTagPlayer()->angle_Rarm = -45.0f;
		}
		player->getTagPlayer()->move_LarmX = 0;
		player->getTagPlayer()->move_RarmX = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player->getTagPlayer()->angle_Rarm = player->getTagPlayer()->angle_Larm * -1;
		player->getTagPlayer()->angle_Larm = player->getTagPlayer()->angle_Rarm * -1;
		player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerRightIdleHead");
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightIdleLarm");
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightIdleRarm");
		player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerRightJumpBody");
		player->getTagPlayer()->ani_body->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->getTagPlayer()->dir = RIGHT;

		player->getTagPlayer()->rc.left += player->getTagPlayer()->speed;
		player->getTagPlayer()->rc.right += player->getTagPlayer()->speed;
		player->getTagPlayer()->x += player->getTagPlayer()->speed;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		player->getTagPlayer()->angle_Larm = player->getTagPlayer()->angle_Rarm * -1;
		player->getTagPlayer()->angle_Rarm = player->getTagPlayer()->angle_Larm * -1;
		player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerLeftIdleHead");
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftIdleLarm");
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftIdleRarm");
		player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerLeftJumpBody");
		player->getTagPlayer()->ani_body->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->getTagPlayer()->dir = LEFT;

		player->getTagPlayer()->rc.left -= player->getTagPlayer()->speed;
		player->getTagPlayer()->rc.right -= player->getTagPlayer()->speed;
		player->getTagPlayer()->x -= player->getTagPlayer()->speed;
		if (player->getTagPlayer()->x <= 0)
		{
			player->getTagPlayer()->x = 0;
		}
	}

	player->getTagPlayer()->jumpPower -= player->getTagPlayer()->gravity;
	player->getTagPlayer()->rc.top -= player->getTagPlayer()->jumpPower;
	player->getTagPlayer()->rc.bottom -= player->getTagPlayer()->jumpPower;
	player->getTagPlayer()->y -= player->getTagPlayer()->jumpPower;
}

void JumpState::enter(player* player)
{
	player->getTagPlayer()->speed = 2;

	player->getTagPlayer()->isJump = true;
	player->getTagPlayer()->isground = false;
	player->getTagPlayer()->gravity = 0.45f;
	player->getTagPlayer()->jumpPower = 10.5f;

	if (player->getTagPlayer()->dir == RIGHT)
	{
		player->getTagPlayer()->move_LweaponX = -5;
		player->getTagPlayer()->move_LweaponY = 40;
		player->getTagPlayer()->angle_Lweapon = -20;
		player->getTagPlayer()->move_RweaponX = -5;
		player->getTagPlayer()->move_RweaponY = 35;
		player->getTagPlayer()->angle_Rweapon = -50;
		player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerRightJumpBody");
		player->getTagPlayer()->ani_body->start();
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightIdleLarm");
		player->getTagPlayer()->ani_Larm->start();
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightIdleRarm");
		player->getTagPlayer()->ani_Rarm->start();
		player->getTagPlayer()->angle_Rarm = 20;
		player->getTagPlayer()->angle_Larm = 0;
	}
	else if (player->getTagPlayer()->dir == LEFT)
	{
		player->getTagPlayer()->move_LweaponX = -40;
		player->getTagPlayer()->move_LweaponY = 10;
		player->getTagPlayer()->angle_Lweapon = 50;
		player->getTagPlayer()->move_RweaponX = -50;
		player->getTagPlayer()->move_RweaponY = 29;
		player->getTagPlayer()->angle_Rweapon = 20;
		player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerLeftJumpBody");
		player->getTagPlayer()->ani_body->start();
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftIdleLarm");
		player->getTagPlayer()->ani_Larm->start();
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftIdleRarm");
		player->getTagPlayer()->ani_Rarm->start();
		player->getTagPlayer()->angle_Rarm = 0;
		player->getTagPlayer()->angle_Larm = -20;
	}

	return;
}

void JumpState::exit(player* player)
{
}