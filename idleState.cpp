#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "pickupState.h"
#include "hitState.h"
#include "deadState.h"

State* IdleState::inputHandle(player* player)
{
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        player->getTagPlayer()->dir = RIGHT;
        return new RunState();
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        player->getTagPlayer()->dir = LEFT;
        return new RunState();
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        return new pickupState();
    }
    if (KEYMANAGER->isOnceKeyDown('S') && !player->getTagPlayer()->isJump)
    {
        return new JumpState();
    }
	if (player->getTagPlayer()->isHit)
	{
		return new HitState();
	}

	if (player->getTagPlayer()->isDead)
	{
		return new DeadState();
	}

	if (player->getTagPlayer()->isAttackL && player->getTagPlayer()->ani_Larm->isCheck(1))
	{
		return new IdleState();
	}

	if (player->getTagPlayer()->isAttackR && player->getTagPlayer()->ani_Rarm->isCheck(1))
	{
		return new IdleState();
	}

    return nullptr;
}

void IdleState::update(player* player)
{
	Hit(player);

	//АјАн
	Attack(player, player->getTagPlayer()->weapon_left_type, player->getTagPlayer()->weapon_right_type);

	if (player->getTagPlayer()->isAttackL == false && player->getTagPlayer()->dir == RIGHT)
	{
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightIdleLarm");
	}
	else if (player->getTagPlayer()->isAttackL == false && player->getTagPlayer()->dir == LEFT)
	{
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftIdleLarm");
		player->getTagPlayer()->move_LarmX = 0;
		player->getTagPlayer()->move_LarmY = 0;
	}
	if (player->getTagPlayer()->isAttackR == false && player->getTagPlayer()->dir == RIGHT)
	{
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightIdleRarm");
		player->getTagPlayer()->move_RarmX = 0;
		player->getTagPlayer()->move_RarmY = 0;
	}
	else if (player->getTagPlayer()->isAttackR == false && player->getTagPlayer()->dir == LEFT)
	{
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftIdleRarm");
	}

    player->getTagPlayer()->jumpPower -= player->getTagPlayer()->gravity;
    player->getTagPlayer()->rc.top -= player->getTagPlayer()->jumpPower;
    player->getTagPlayer()->rc.bottom -= player->getTagPlayer()->jumpPower;
    player->getTagPlayer()->y -= player->getTagPlayer()->jumpPower;

	if (player->getTagPlayer()->dir == RIGHT)
	{
		if (player->getTagPlayer()->angle_Larm < 10 && !player->getTagPlayer()->idleArmAngle)
		{
			player->getTagPlayer()->angle_Larm += 0.1f;
			player->getTagPlayer()->angle_Rarm -= 0.1f;
			player->getTagPlayer()->move_LweaponX -= 0.03f;
			player->getTagPlayer()->move_RweaponX += 0.03f;
			if (player->getTagPlayer()->angle_Larm > 9.5)
			{
				player->getTagPlayer()->idleArmAngle = true;
			}
		}

		else if (player->getTagPlayer()->angle_Larm > 0 && player->getTagPlayer()->idleArmAngle)
		{
			player->getTagPlayer()->angle_Larm -= 0.1f;
			player->getTagPlayer()->angle_Rarm += 0.1f;
			player->getTagPlayer()->move_LweaponX += 0.03f;
			player->getTagPlayer()->move_RweaponX -= 0.03f;
			if (player->getTagPlayer()->angle_Larm < 0.5)
			{
				player->getTagPlayer()->idleArmAngle = false;
			}
		}
	}
	if (player->getTagPlayer()->dir == LEFT)
	{
		if (player->getTagPlayer()->angle_Larm < 10 && !player->getTagPlayer()->idleArmAngle)
		{
			player->getTagPlayer()->angle_Larm += 0.1f;
			player->getTagPlayer()->angle_Rarm -= 0.1f;
			player->getTagPlayer()->move_LweaponX += 0.03f;
			if (player->getTagPlayer()->angle_Larm > 9.5)
			{
				player->getTagPlayer()->idleArmAngle = true;
			}
		}

		else if (player->getTagPlayer()->angle_Larm > 0 && player->getTagPlayer()->idleArmAngle)
		{
			player->getTagPlayer()->angle_Larm -= 0.1f;
			player->getTagPlayer()->angle_Rarm += 0.1f;
			player->getTagPlayer()->move_LweaponX -= 0.03f;
			if (player->getTagPlayer()->angle_Larm < 0.5)
			{
				player->getTagPlayer()->idleArmAngle = false;
			}
		}
	}
}

void IdleState::enter(player* player)
{
	player->getTagPlayer()->hitOpacity = 1.0f;

	player->getTagPlayer()->idleArmAngle = false;

	player->getTagPlayer()->move_headX = 0;
	player->getTagPlayer()->move_headY = 0;
	player->getTagPlayer()->move_bodyX = 0;
	player->getTagPlayer()->move_bodyY = 0;
	player->getTagPlayer()->move_LarmX = 0;
	player->getTagPlayer()->move_LarmY = 0;
	player->getTagPlayer()->move_RarmX = 0;
	player->getTagPlayer()->move_RarmY = 0;

	player->getTagPlayer()->angle_Rarm = 0;
	player->getTagPlayer()->angle_Larm = 0;

    player->getTagPlayer()->speed = 2;

    if (player->getTagPlayer()->dir == RIGHT)
    {
		player->getTagPlayer()->move_LweaponX = -5;
		player->getTagPlayer()->move_LweaponY = 40;
		player->getTagPlayer()->angle_Lweapon = -20;
		player->getTagPlayer()->move_RweaponX = -5;
		player->getTagPlayer()->move_RweaponY = 35;
		player->getTagPlayer()->angle_Rweapon = -50;
        player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerRightIdleHead");
        player->getTagPlayer()->ani_head->start();
        player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerRightIdleBody");
        player->getTagPlayer()->ani_body->start();
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightIdleLarm");
		player->getTagPlayer()->ani_Larm->start();
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightIdleRarm");
		player->getTagPlayer()->ani_Rarm->start();
    }
    else if (player->getTagPlayer()->dir == LEFT)
    {
		player->getTagPlayer()->move_LweaponX = -40;
		player->getTagPlayer()->move_LweaponY = 10;
		player->getTagPlayer()->angle_Lweapon = 50;
		player->getTagPlayer()->move_RweaponX = -50;
		player->getTagPlayer()->move_RweaponY = 29;
		player->getTagPlayer()->angle_Rweapon = 20;
        player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerLeftIdleHead");
        player->getTagPlayer()->ani_head->start();
        player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerLeftIdleBody");
        player->getTagPlayer()->ani_body->start();
		player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftIdleLarm");
		player->getTagPlayer()->ani_Larm->start();
		player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftIdleRarm");
		player->getTagPlayer()->ani_Rarm->start();
    }

    return;
}

void IdleState::exit(player* player)
{
}