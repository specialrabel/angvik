#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "runState.h"
#include "jumpState.h"
#include "hitState.h"

State* RunState::inputHandle(player* player)
{
    if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
    {
        return new IdleState();
    }
    if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
    {
        return new IdleState();
    }
    if (KEYMANAGER->isOnceKeyDown('S') && !player->getTagPlayer()->isJump)
    {
        return new JumpState();
    }
	if (player->getTagPlayer()->isHit)
	{
		return new HitState();
	}

    return nullptr;
}

void RunState::update(player* player)
{
	Hit(player);

	//공격
	Attack(player, player->getTagPlayer()->weapon_left_type, player->getTagPlayer()->weapon_right_type);


	if (player->getTagPlayer()->dir == RIGHT)
	{
		if (player->getTagPlayer()->isAttackL == false)
		{
			//이미지프레임의 끝일때를 기준으로 잡아줌.
			if (player->getTagPlayer()->ani_Larm->isCheck(1))
			{
				player->getTagPlayer()->move_LweaponX = -1;
				player->getTagPlayer()->move_LweaponY = 30;
				player->getTagPlayer()->angle_Lweapon = -70;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(2))
			{
				player->getTagPlayer()->move_LweaponX = -1;
				player->getTagPlayer()->move_LweaponY = 30;
				player->getTagPlayer()->angle_Lweapon = -70;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(3))
			{
				player->getTagPlayer()->move_LweaponX = 0;
				player->getTagPlayer()->move_LweaponY = 30;
				player->getTagPlayer()->angle_Lweapon = -70;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(4))
			{
				player->getTagPlayer()->move_LweaponX = 1;
				player->getTagPlayer()->move_LweaponY = 30;
				player->getTagPlayer()->angle_Lweapon = -71;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(5))
			{
				player->getTagPlayer()->move_LweaponX = 2;
				player->getTagPlayer()->move_LweaponY = 30;
				player->getTagPlayer()->angle_Lweapon = -72;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(6))
			{
				player->getTagPlayer()->move_LweaponX = 3;
				player->getTagPlayer()->move_LweaponY = 28;
				player->getTagPlayer()->angle_Lweapon = -73;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(7))
			{
				player->getTagPlayer()->move_LweaponX = 5;
				player->getTagPlayer()->move_LweaponY = 26;
				player->getTagPlayer()->angle_Lweapon = -74;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(8))
			{
				player->getTagPlayer()->move_LweaponX = 3;
				player->getTagPlayer()->move_LweaponY = 27;
				player->getTagPlayer()->angle_Lweapon = -72;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(9))
			{
				player->getTagPlayer()->move_LweaponX = 2;
				player->getTagPlayer()->move_LweaponY = 28;
				player->getTagPlayer()->angle_Lweapon = -71;
			}
			else if (player->getTagPlayer()->ani_Larm->isCheck(10))
			{
				player->getTagPlayer()->move_LweaponX = 1;
				player->getTagPlayer()->move_LweaponY = 29;
				player->getTagPlayer()->angle_Lweapon = -70;
			}
		}

		if (player->getTagPlayer()->isAttackR == false)
		{
			//이미지프레임의 끝일때를 기준으로 잡아줌.
			if (player->getTagPlayer()->ani_Rarm->isCheck(1))
			{
				player->getTagPlayer()->move_RweaponX = 2;
				player->getTagPlayer()->move_RweaponY = 30;
				player->getTagPlayer()->angle_Rweapon = -82;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(2))
			{
				player->getTagPlayer()->move_RweaponX = 3;
				player->getTagPlayer()->move_RweaponY = 28;
				player->getTagPlayer()->angle_Rweapon = -83;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(3))
			{
				player->getTagPlayer()->move_RweaponX = 5;
				player->getTagPlayer()->move_RweaponY = 26;
				player->getTagPlayer()->angle_Rweapon = -84;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(4))
			{
				player->getTagPlayer()->move_RweaponX = 3;
				player->getTagPlayer()->move_RweaponY = 27;
				player->getTagPlayer()->angle_Rweapon = -82;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(5))
			{
				player->getTagPlayer()->move_RweaponX = 2;
				player->getTagPlayer()->move_RweaponY = 28;
				player->getTagPlayer()->angle_Rweapon = -81;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(6))
			{
				player->getTagPlayer()->move_RweaponX = 1;
				player->getTagPlayer()->move_RweaponY = 29;
				player->getTagPlayer()->angle_Rweapon = -80;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(7))
			{
				player->getTagPlayer()->move_RweaponX = -1;
				player->getTagPlayer()->move_RweaponY = 30;
				player->getTagPlayer()->angle_Rweapon = -80;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(8))
			{
				player->getTagPlayer()->move_RweaponX = -1;
				player->getTagPlayer()->move_RweaponY = 30;
				player->getTagPlayer()->angle_Rweapon = -80;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(9))
			{
				player->getTagPlayer()->move_RweaponX = 0;
				player->getTagPlayer()->move_RweaponY = 30;
				player->getTagPlayer()->angle_Rweapon = -80;
			}
			else if (player->getTagPlayer()->ani_Rarm->isCheck(10))
			{
				player->getTagPlayer()->move_RweaponX = 1;
				player->getTagPlayer()->move_RweaponY = 30;
				player->getTagPlayer()->angle_Rweapon = -81;
			}
		}
	}
	else if (player->getTagPlayer()->dir == LEFT)
	{
		//이미지프레임의 끝일때를 기준으로 잡아줌.
		if (player->getTagPlayer()->ani_Larm->isCheck(1))
		{
			player->getTagPlayer()->move_LweaponX = -33;
			player->getTagPlayer()->move_LweaponY = -5;
			player->getTagPlayer()->angle_Lweapon = 82;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(2))
		{
			player->getTagPlayer()->move_LweaponX = -34;
			player->getTagPlayer()->move_LweaponY = -7;
			player->getTagPlayer()->angle_Lweapon = 83;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(3))
		{
			player->getTagPlayer()->move_LweaponX = -36;
			player->getTagPlayer()->move_LweaponY = -9;
			player->getTagPlayer()->angle_Lweapon = 84;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(4))
		{
			player->getTagPlayer()->move_LweaponX = -34;
			player->getTagPlayer()->move_LweaponY = -8;
			player->getTagPlayer()->angle_Lweapon = 82;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(5))
		{
			player->getTagPlayer()->move_LweaponX = -33;
			player->getTagPlayer()->move_LweaponY = -7;
			player->getTagPlayer()->angle_Lweapon = 81;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(6))
		{
			player->getTagPlayer()->move_LweaponX = -32;
			player->getTagPlayer()->move_LweaponY = -6;
			player->getTagPlayer()->angle_Lweapon = 80;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(7))
		{
			player->getTagPlayer()->move_LweaponX = -30;
			player->getTagPlayer()->move_LweaponY = -5;
			player->getTagPlayer()->angle_Lweapon = 80;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(8))
		{
			player->getTagPlayer()->move_LweaponX = -30;
			player->getTagPlayer()->move_LweaponY = -5;
			player->getTagPlayer()->angle_Lweapon = 80;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(9))
		{
			player->getTagPlayer()->move_LweaponX = -31;
			player->getTagPlayer()->move_LweaponY = -5;
			player->getTagPlayer()->angle_Lweapon = 80;
		}
		else if (player->getTagPlayer()->ani_Larm->isCheck(10))
		{
			player->getTagPlayer()->move_LweaponX = -32;
			player->getTagPlayer()->move_LweaponY = -5;
			player->getTagPlayer()->angle_Lweapon = 81;
		}

		//이미지프레임의 끝일때를 기준으로 잡아줌.
		if (player->getTagPlayer()->ani_Rarm->isCheck(1))
		{
			player->getTagPlayer()->move_RweaponX = -32;
			player->getTagPlayer()->move_RweaponY = -2;
			player->getTagPlayer()->angle_Rweapon = 70;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(2))
		{
			player->getTagPlayer()->move_RweaponX = -32;
			player->getTagPlayer()->move_RweaponY = -2;
			player->getTagPlayer()->angle_Rweapon = 70;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(3))
		{
			player->getTagPlayer()->move_RweaponX = -33;
			player->getTagPlayer()->move_RweaponY = -2;
			player->getTagPlayer()->angle_Rweapon = 70;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(4))
		{
			player->getTagPlayer()->move_RweaponX = -34;
			player->getTagPlayer()->move_RweaponY = -2;
			player->getTagPlayer()->angle_Rweapon = 71;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(5))
		{
			player->getTagPlayer()->move_RweaponX = -35;
			player->getTagPlayer()->move_RweaponY = -2;
			player->getTagPlayer()->angle_Rweapon = 72;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(6))
		{
			player->getTagPlayer()->move_RweaponX = -36;
			player->getTagPlayer()->move_RweaponY = -4;
			player->getTagPlayer()->angle_Rweapon = 73;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(7))
		{
			player->getTagPlayer()->move_RweaponX = -38;
			player->getTagPlayer()->move_RweaponY = -6;
			player->getTagPlayer()->angle_Rweapon = 74;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(8))
		{
			player->getTagPlayer()->move_RweaponX = -36;
			player->getTagPlayer()->move_RweaponY = -5;
			player->getTagPlayer()->angle_Rweapon = 72;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(9))
		{
			player->getTagPlayer()->move_RweaponX = -35;
			player->getTagPlayer()->move_RweaponY = -4;
			player->getTagPlayer()->angle_Rweapon = 71;
		}
		else if (player->getTagPlayer()->ani_Rarm->isCheck(10))
		{
			player->getTagPlayer()->move_RweaponX = -34;
			player->getTagPlayer()->move_RweaponY = -3;
			player->getTagPlayer()->angle_Rweapon = 70;
		}
	}

	if (player->getTagPlayer()->isAttackL == false && player->getTagPlayer()->dir == RIGHT)
	{
		if (player->getTagPlayer()->weapon_left_color == COLOREND) // 무기를 들고있지 않을 때
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightMoveLarm");
		}
		else // 무기를 들고 있을 때
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightMoveWeaponLarm");
		}
	}
	else if (player->getTagPlayer()->isAttackL == false && player->getTagPlayer()->dir == LEFT)
	{
		if (player->getTagPlayer()->weapon_left_color == COLOREND) // 무기를 들고있지 않을 때
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftMoveLarm");
			player->getTagPlayer()->move_LarmX = 8;
			player->getTagPlayer()->move_LarmY = 0;
		}
		else // 무기를 들고 있을 때
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftMoveWeaponLarm");
		}
	}
	if (player->getTagPlayer()->isAttackR == false && player->getTagPlayer()->dir == RIGHT)
	{
		if (player->getTagPlayer()->weapon_right_color == COLOREND) // 무기를 들고있지 않을 때
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightMoveRarm");
			player->getTagPlayer()->move_RarmX = -8;
			player->getTagPlayer()->move_RarmY = 0;
		}
		else // 무기를 들고 있을 때
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightMoveWeaponRarm");
		}
	}
	else if (player->getTagPlayer()->isAttackR == false && player->getTagPlayer()->dir == LEFT)
	{
		if (player->getTagPlayer()->weapon_right_color == COLOREND) // 무기를 들고있지 않을 때
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftMoveRarm");
		}
		else // 무기를 들고 있을 때
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftMoveWeaponRarm");
		}
	}

    player->playerSpeed();

    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        player->getTagPlayer()->dir = RIGHT;

        player->getTagPlayer()->rc.left += player->getTagPlayer()->speed;
        player->getTagPlayer()->rc.right += player->getTagPlayer()->speed;
        player->getTagPlayer()->x += player->getTagPlayer()->speed;
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

void RunState::enter(player* player)
{
	player->getTagPlayer()->move_headX = 0;
	player->getTagPlayer()->move_RarmX = 0;
	player->getTagPlayer()->angle_Rarm = 0;
	player->getTagPlayer()->angle_Larm = 0;

    if (player->getTagPlayer()->dir == RIGHT)
    {
		player->getTagPlayer()->angle_Lweapon = -70;
		player->getTagPlayer()->move_LweaponX = 0;
		player->getTagPlayer()->move_LweaponY = 30;

		player->getTagPlayer()->angle_Rweapon = -80;
		player->getTagPlayer()->move_RweaponX = 0;
		player->getTagPlayer()->move_RweaponY = 30;

		player->getTagPlayer()->move_LarmX = 0;
		player->getTagPlayer()->move_RarmX = -8;

        player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerRightIdleHead");
        player->getTagPlayer()->ani_head->start();
        player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerRightMoveBody");
        player->getTagPlayer()->ani_body->start();
		if (player->getTagPlayer()->weapon_left_color == COLOREND)
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightMoveLarm");
			player->getTagPlayer()->ani_Larm->start();
		}
		else
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerRightMoveWeaponLarm");
			player->getTagPlayer()->ani_Larm->start();
		}
		if (player->getTagPlayer()->weapon_right_color == COLOREND)
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightMoveRarm");
			player->getTagPlayer()->ani_Rarm->start();
		}
		else
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerRightMoveWeaponRarm");
			player->getTagPlayer()->ani_Rarm->start();
		}
    }
    else if (player->getTagPlayer()->dir == LEFT)
    {
		player->getTagPlayer()->angle_Lweapon = 80;
		player->getTagPlayer()->move_LweaponX = -30;
		player->getTagPlayer()->move_LweaponY = -5;

		player->getTagPlayer()->angle_Rweapon = 70;
		player->getTagPlayer()->move_RweaponX = -40;
		player->getTagPlayer()->move_RweaponY = -5;

		player->getTagPlayer()->move_LarmX = +8;
		player->getTagPlayer()->move_RarmX = 0;

        player->getTagPlayer()->ani_head = KEYANIMANAGER->findAnimation("playerLeftIdleHead");
        player->getTagPlayer()->ani_head->start();
        player->getTagPlayer()->ani_body = KEYANIMANAGER->findAnimation("playerLeftMoveBody");
        player->getTagPlayer()->ani_body->start();
		if (player->getTagPlayer()->weapon_left_color == COLOREND)
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftMoveLarm");
			player->getTagPlayer()->ani_Larm->start();
		}
		else
		{
			player->getTagPlayer()->ani_Larm = KEYANIMANAGER->findAnimation("playerLeftMoveWeaponLarm");
			player->getTagPlayer()->ani_Larm->start();
		}
		if (player->getTagPlayer()->weapon_right_color == COLOREND)
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftMoveRarm");
			player->getTagPlayer()->ani_Rarm->start();
		}
		else
		{
			player->getTagPlayer()->ani_Rarm = KEYANIMANAGER->findAnimation("playerLeftMoveWeaponRarm");
			player->getTagPlayer()->ani_Rarm->start();
		}
    }
}

void RunState::exit(player* player)
{
}