#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "pickupState.h"
#include "hitState.h"
#include "deadState.h"

State* HitState::inputHandle(player* player)
{
	if (!player->getTagPlayer()->isDead)
	{
		player->getTagPlayer()->isHit = false;
		return new IdleState();
	}
	else if (player->getTagPlayer()->isDead && player->getTagPlayer()->isground)
	{
		return new DeadState();
	}

	return nullptr;
}

void HitState::update(player* player)
{
	if (player->getTagPlayer()->isDead)
	{
		if (player->getTagPlayer()->dir == RIGHT)
		{
			player->getTagPlayer()->rc.left -= 2;
			player->getTagPlayer()->rc.right -= 2;
			player->getTagPlayer()->x -= 2;
		}
		else if (player->getTagPlayer()->dir == LEFT)
		{
			player->getTagPlayer()->rc.left += 2;
			player->getTagPlayer()->rc.right += 2;
			player->getTagPlayer()->x += 2;
		}
		
		player->getTagPlayer()->jumpPower -= player->getTagPlayer()->gravity;
		player->getTagPlayer()->rc.top -= player->getTagPlayer()->jumpPower;
		player->getTagPlayer()->rc.bottom -= player->getTagPlayer()->jumpPower;
		player->getTagPlayer()->y -= player->getTagPlayer()->jumpPower;
	}
}

void HitState::enter(player* player)
{
	player->getTagPlayer()->hitOpacity = 1.0f;
	player->getTagPlayer()->OpacityCount = 4;

	if (player->getTagPlayer()->shoes_color != COLOREND)
	{
		player->getTagPlayer()->shoes_durability -= 1;
		player->getTagPlayer()->shoes_color = COLOREND;
	}
	else if (player->getTagPlayer()->armor_color != COLOREND)
	{
		player->getTagPlayer()->armor_durability -= 1;
		player->getTagPlayer()->armor_color = COLOREND;
	}
	else if (player->getTagPlayer()->helmet_color != COLOREND)
	{
		player->getTagPlayer()->helmet_durability -= 1;
		player->getTagPlayer()->helmet_color = COLOREND;
	}
	else if (!player->getTagPlayer()->isDead)
	{
		player->getTagPlayer()->isDead = true;
	}

	if (player->getTagPlayer()->isDead)
	{
		player->getTagPlayer()->isJump = true;
		player->getTagPlayer()->isground = false;
		player->getTagPlayer()->gravity = 0.45f;
		player->getTagPlayer()->jumpPower = 5.5f;
	}

	return;
}

void HitState::exit(player* player)
{
}