#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "pickupState.h"
#include "hitState.h"
#include "deadState.h"
#include "bullets.h"

State* DeadState::inputHandle(player* player)
{


	return nullptr;
}

void DeadState::update(player* player)
{
	
}

void DeadState::enter(player* player)
{
	player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerNothingHead");
	player->getTagPlayer()->ani_head->start();

	player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerNothingBody");
	player->getTagPlayer()->ani_body->start();

	player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerNothingLarm");
	player->getTagPlayer()->ani_Larm->start();

	player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerNothingRarm");
	player->getTagPlayer()->ani_Rarm->start();

	player->getTagPlayer()->weapon_left_color = COLOREND;
	player->getTagPlayer()->weapon_right_color = COLOREND;
	player->getTagPlayer()->armor_color = COLOREND;
	player->getTagPlayer()->helmet_color = COLOREND;

	player->get_fragmentBullet()->fire(L"image/player/dead_head.png", player->getTagPlayer()->rc_head.left, player->getTagPlayer()->rc_head.top, 23, 22, -1);
	player->get_fragmentBullet()->fire(L"image/player/dead_body.png", player->getTagPlayer()->rc_body.left, player->getTagPlayer()->rc_body.top, 20, 21, 1);
	player->get_fragmentBullet()->fire(L"image/player/dead_bone.png", player->getTagPlayer()->rc_Rarm.left, player->getTagPlayer()->rc_Rarm.top, 18, 12, -1);
	player->get_fragmentBullet()->fire(L"image/player/dead_bone.png", player->getTagPlayer()->rc_Larm.left, player->getTagPlayer()->rc_Larm.top, 18, 12, -1);
	player->get_fragmentBullet()->fire(L"image/player/dead_bone.png", player->getTagPlayer()->rc_Rarm.left, player->getTagPlayer()->rc_Rarm.top, 18, 12, 1);
	player->get_fragmentBullet()->fire(L"image/player/dead_bone.png", player->getTagPlayer()->rc_Larm.left, player->getTagPlayer()->rc_Larm.top, 18, 12, 1);
	player->get_fragmentBullet()->fire(L"image/player/dead_bone.png", player->getTagPlayer()->rc_Rarm.left, player->getTagPlayer()->rc_Rarm.top, 18, 12, -1);
}

void DeadState::exit(player* player)
{
}
