#include "stdafx.h"
#include "State.h"
#include "Player.h"
#include "IdleState.h"

void State::Attack(player* player, int LeftWeapon, int RightWeapon)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player->getTagPlayer()->angle_Larm = 0;
		player->getTagPlayer()->angle_Rarm = 0;

		if (LeftWeapon == TYPEEND) // 맨손일 경우
		{
			if (player->getTagPlayer()->dir == RIGHT)
			{
				player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightAttackLarm");
				player->getTagPlayer()->ani_Larm->start();
			}
			else if(player->getTagPlayer()->dir == LEFT)
			{
				player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftAttackLarm");
				player->getTagPlayer()->ani_Larm->start();
				player->getTagPlayer()->move_LarmX = 5;
				player->getTagPlayer()->move_LarmY = 3;
			}

			player->getTagPlayer()->isAttackL = true;
		}
		else if (LeftWeapon == SWORD) // 검일 경우
		{
			if (player->getTagPlayer()->dir == RIGHT)
			{
				player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightAttackWeaponLarm");
				player->getTagPlayer()->ani_Larm->start();

				player->getTagPlayer()->move_LweaponX = 0;
				player->getTagPlayer()->move_LweaponY = 0;
				player->getTagPlayer()->angle_Lweapon = -90;
			}
			else if (player->getTagPlayer()->dir == LEFT)
			{
				player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftAttackWeaponLarm");
				player->getTagPlayer()->ani_Larm->start();
				player->getTagPlayer()->move_LarmX = 5;
				player->getTagPlayer()->move_LarmY = 3;
			}

			player->getTagPlayer()->isAttackL = true;
		}
		else if (LeftWeapon == STAFF) // 스태프일 경우
		{

			player->getTagPlayer()->isAttackL = true;
		}
	}

	else if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player->getTagPlayer()->angle_Larm = 0;
		player->getTagPlayer()->angle_Rarm = 0;

		if (RightWeapon == TYPEEND) // 맨손일 경우
		{
			if (player->getTagPlayer()->dir == RIGHT)
			{
				player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightAttackRarm");
				player->getTagPlayer()->ani_Rarm->start();
				player->getTagPlayer()->move_RarmX = -5;
				player->getTagPlayer()->move_RarmY = 3;
			}
			else if (player->getTagPlayer()->dir == LEFT)
			{
				player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftAttackRarm");
				player->getTagPlayer()->ani_Rarm->start();
			}

			player->getTagPlayer()->isAttackR = true;
		}
		else if (RightWeapon == SWORD)
		{
			if (player->getTagPlayer()->dir == RIGHT)
			{
				player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightAttackWeaponRarm");
				player->getTagPlayer()->ani_Rarm->start();
				player->getTagPlayer()->move_RarmX = -5;
				player->getTagPlayer()->move_RarmY = 3;

				player->getTagPlayer()->move_RweaponX = 0;
				player->getTagPlayer()->move_RweaponY = 0;
				player->getTagPlayer()->angle_Rweapon = -90;
			}
			else if (player->getTagPlayer()->dir == LEFT)
			{
				player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftAttackWeaponRarm");
				player->getTagPlayer()->ani_Rarm->start();
			}

			player->getTagPlayer()->isAttackR = true;
		}
		else if (RightWeapon == STAFF)
		{

			player->getTagPlayer()->isAttackR = true;
		}
	}

	if (player->getTagPlayer()->isAttackL && LeftWeapon == SWORD)
	{
		if (player->getTagPlayer()->dir == RIGHT)
		{
			player->getTagPlayer()->hitBoxL = D2DMANAGER->RectMake(player->getTagPlayer()->rc.right - 20, player->getTagPlayer()->rc.top, 70, 50);

			//휘두르기
			if(player->getTagPlayer()->angle_Lweapon > -45)
			{
				player->getTagPlayer()->move_LweaponX -= 2.4f;
			}
			else
			{
				player->getTagPlayer()->move_LweaponX += 1.5f;
			}
			player->getTagPlayer()->move_LweaponY -= -2.5f;
			player->getTagPlayer()->angle_Lweapon -= -7.8f;
		}
		else if (player->getTagPlayer()->dir == LEFT)
		{
			player->getTagPlayer()->hitBoxL = D2DMANAGER->RectMake(player->getTagPlayer()->rc.left - 50, player->getTagPlayer()->rc.top, 70, 50);
		}
	}
	else if (player->getTagPlayer()->isAttackR && RightWeapon == SWORD)
	{
		if (player->getTagPlayer()->dir == RIGHT)
		{
			player->getTagPlayer()->hitBoxR = D2DMANAGER->RectMake(player->getTagPlayer()->rc.right - 20, player->getTagPlayer()->rc.top, 70, 50);
			//휘두르기
			if (player->getTagPlayer()->angle_Rweapon > -45)
			{
				player->getTagPlayer()->move_RweaponX -= 2.4f;
			}
			else
			{
				player->getTagPlayer()->move_RweaponX += 1.5f;
			}
			player->getTagPlayer()->move_RweaponY -= -2.5f;
			player->getTagPlayer()->angle_Rweapon -= -7.8f;
		}
		else if (player->getTagPlayer()->dir == LEFT)
		{
			player->getTagPlayer()->hitBoxR = D2DMANAGER->RectMake(player->getTagPlayer()->rc.left - 50, player->getTagPlayer()->rc.top, 70, 50);
		}
	}

	//공격 애니메이션이 끝났는지.
	if (player->getTagPlayer()->isAttackL && player->getTagPlayer()->ani_Larm->isCheck(1))
	{
		player->getTagPlayer()->hitBoxL = D2DMANAGER->RectMake(0, 0, 0, 0);
		player->getTagPlayer()->isAttackL = false;
	}

	if (player->getTagPlayer()->isAttackR && player->getTagPlayer()->ani_Rarm->isCheck(1))
	{
		player->getTagPlayer()->hitBoxR = D2DMANAGER->RectMake(0, 0, 0, 0);
		player->getTagPlayer()->isAttackR = false;
	}
}

void State::Hit(player* player)
{
	if (player->getTagPlayer()->OpacityCount > 0)
	{
		if (player->getTagPlayer()->hitOpacity >= 0.0f)
		{
			player->getTagPlayer()->hitOpacity -= 0.06f;
		}

		if (player->getTagPlayer()->hitOpacity <= 0.0f)
		{
			player->getTagPlayer()->hitOpacity = 1.0f;
			player->getTagPlayer()->OpacityCount -= 1;
		}
	}
}
