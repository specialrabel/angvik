#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "pickupState.h"

State* pickupState::inputHandle(player* player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN)) {
		return new IdleState();
	}

    return nullptr;
}

void pickupState::update(player* player)
{
    player->getTagPlayer()->jumpPower -= player->getTagPlayer()->gravity;
    player->getTagPlayer()->rc.top -= player->getTagPlayer()->jumpPower;
    player->getTagPlayer()->rc.bottom -= player->getTagPlayer()->jumpPower;
    player->getTagPlayer()->y -= player->getTagPlayer()->jumpPower;
}

void pickupState::enter(player* player)
{
	player->setPickUpCheckT();

	if (player->getTagPlayer()->dir == RIGHT)
	{
		player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerRightPickUpBody");
		player->getTagPlayer()->ani_body->start();
		//위치조정
		player->getTagPlayer()->move_headX = 5;
		player->getTagPlayer()->move_headY = 10;
		player->getTagPlayer()->move_bodyX = 0;
		player->getTagPlayer()->move_bodyY = 7;
		player->getTagPlayer()->angle_Larm = 30.0f;
		player->getTagPlayer()->move_LarmX = 4;
		player->getTagPlayer()->move_LarmY = 8;
		player->getTagPlayer()->angle_Rarm = -20.0f;
		player->getTagPlayer()->move_RarmX = 2;
		player->getTagPlayer()->move_RarmY = 7;
	}
	else if (player->getTagPlayer()->dir == LEFT)
	{
		player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerLeftPickUpBody");
		player->getTagPlayer()->ani_body->start();
		//위치조정
		player->getTagPlayer()->move_headX = -5;
		player->getTagPlayer()->move_headY = 10;
		player->getTagPlayer()->move_bodyX = 0;
		player->getTagPlayer()->move_bodyY = 7;
		player->getTagPlayer()->angle_Larm = 30.0f;
		player->getTagPlayer()->move_LarmX = -4;
		player->getTagPlayer()->move_LarmY = 8;
		player->getTagPlayer()->angle_Rarm = -20.0f;
		player->getTagPlayer()->move_RarmX = -2;
		player->getTagPlayer()->move_RarmY = 7;
	}

    return;
}

void pickupState::exit(player* player)
{
}