#include "stdafx.h"
#include "collision.h"
#include "Player.h"
#include "bird.h"
#include "bullets.h"
#include "enemyManager.h"
#include "Object.h"
#include "itemManager.h"
#include "menu.h"

HRESULT collision::init(image* stage)
{
	_stage = stage;

	_effect_img = new image;
	_effect_img->D_Init(L"image/effect/effect2.png", 1200, 100, 6, 1);

	IMAGEMANAGER->addFrameImage("hit", L"image/effect/effect2.png", 1200, 100, 6, 1);
	IMAGEMANAGER->addFrameImage("plant_effect", L"image/effect/�����_�Ѿ�.png", 196, 43, 7, 1);

	EFFECTMANAGER->addEffect("explosion", "hit", 1200, 100, 200, 100, 1, 0.3, 1);
	EFFECTMANAGER->addEffect("plant_explosion", "plant_effect", 196, 43, 28, 43, 1, 0.5, 5);

	_hit = new effect;
	_hit->init(IMAGEMANAGER->findImage("hit"), 200, 100, 1, 0.3f);

	return S_OK;
}

void collision::release()
{
}

void collision::update()
{
	// �ش� �浹ó�� ������ �Ϸ���, �Ʒ��� �Լ��� Ŭ���ϰ� F12�� �̵��սô�.

	// �÷��̾�� �� �浹ó��
	pixel_collision();

	// ���ʹ̿� �� �浹ó��
	pixel_collision_enemy();

	// �÷��̾� �ҷ��� �� �浹ó��
	pixel_collision_bullet();

	// �÷��̾�� ���ʹ�
	player_AND_enemy();

	// �÷��̾�� ��������, ������� ��, ���� ȭ���浹
	player_AND_object();

	// �÷��̾� �ҷ��� ���ʹ� �浹
	player_bullet_AND_enemy();

	// ����� �ҷ��� �浹�ϴ°͵�
	Enemy_bullet_AND_anything();

	// ������ �浹ó��
	item_colision();

	//������ �ݱ�
	item_pick_up();
	item_drop();

	//���� ���ʹ� �浹
	bird_AND_enemy();

	//��Ÿ�� ����Ʈ
	_hit->update();

	EFFECTMANAGER->update();
}

void collision::render()
{
	_hit->render();

	EFFECTMANAGER->render();
}

void collision::pixel_collision()
{
	int r(0), g(0), b(0);

	for (int i = _player->getTagPlayer()->rc.bottom - 5; i < _player->getTagPlayer()->rc.bottom + 5; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), (_player->getTagPlayer()->rc.right + _player->getTagPlayer()->rc.left) / 2, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 255 && b == 0)
		{
			int height = (_player->getTagPlayer()->rc.bottom - _player->getTagPlayer()->rc.top);
			_player->getTagPlayer()->rc.top = i - height;
			_player->getTagPlayer()->rc.bottom = i;
			_player->getTagPlayer()->y = _player->getTagPlayer()->rc.top;
			_player->getTagPlayer()->isground = true;
			_player->getTagPlayer()->isJump = false;
			_player->getTagPlayer()->jumpPower = 0;
			_player->getTagPlayer()->gravity = 0.7f;
			break;
		}
	}

	for (int i = _player->getTagPlayer()->rc.left + 5; i > _player->getTagPlayer()->rc.left - 2; i--)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), i, _player->getTagPlayer()->rc.bottom - 5);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			int width = (_player->getTagPlayer()->rc.right - _player->getTagPlayer()->rc.left);
			_player->getTagPlayer()->rc.left = i;
			_player->getTagPlayer()->rc.right = i + width;
			_player->getTagPlayer()->x = _player->getTagPlayer()->rc.left;
			break;
		}
	}

	for (int i = _player->getTagPlayer()->rc.right - 5; i < _player->getTagPlayer()->rc.right + 2; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), i, _player->getTagPlayer()->rc.bottom - 5);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			int width = (_player->getTagPlayer()->rc.right - _player->getTagPlayer()->rc.left);
			_player->getTagPlayer()->rc.right = i;
			_player->getTagPlayer()->rc.left = i - width;
			_player->getTagPlayer()->x = _player->getTagPlayer()->rc.left;
			break;
		}
	}

	//õ�� �浹
	for (int i = _player->getTagPlayer()->rc.top - 5; i < _player->getTagPlayer()->rc.top + 5; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), (_player->getTagPlayer()->rc.right + _player->getTagPlayer()->rc.left) / 2, i);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_player->getTagPlayer()->jumpPower = 0;
			break;
		}
	}

	//���� �浹
	for (int i = _player->getTagPlayer()->rc.bottom - 5; i < _player->getTagPlayer()->rc.bottom + 5; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), (_player->getTagPlayer()->rc.right + _player->getTagPlayer()->rc.left) / 2, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0 && _player->getTagPlayer()->hitInterval > 120 && !_player->getTagPlayer()->isDead)
		{
			_player->getTagPlayer()->isHit = true;
			_player->getTagPlayer()->hitInterval = 0;
			break;
		}
	}

	for (int i = _player->getTagPlayer()->rc.left; i < _player->getTagPlayer()->rc.right - 5; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), i, (_player->getTagPlayer()->rc.bottom + _player->getTagPlayer()->rc.top)/2 + 7);

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_player->set_inWater(true);
		}
		else
			_player->set_inWater(false);
	}
}

void collision::pixel_collision_bullet()
{
	int r(0), g(0), b(0);

	for (int z = 0; z < _player->get_playerBullet()->get_bullet().size(); z++)
	{
		int start(0), end(0);

		D2D1_RECT_F Sheep = _player->get_playerBullet()->get_bullet()[z].rc;

		if (_player->get_playerBullet()->get_bullet()[z].type == LIGHT)
		{
			start = Sheep.bottom - 50;
			end = Sheep.bottom + 50;
		}
		else
		{
			start = Sheep.bottom - 10;
			end = Sheep.bottom + 10;
		}

		for (int i = start; i < end; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (Sheep.right + Sheep.left) / 2, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// ���� �浹
			if (r == 0 && g == 255 && b == 0)
			{
				_player->get_playerBullet()->set_rect(z, i);
				_player->get_playerBullet()->set_gravity(z);
				break;
			}
		}
		// ������� �����浹 ���ϴϱ� �����սô�
		if (_player->get_playerBullet()->get_bullet()[z].type == LIGHT) continue;

		for (int i = Sheep.left + 5; i > Sheep.left - 5; i--)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Sheep.top + Sheep.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_playerBullet()->set_direction(z, i);
				break;
			}
		}

		for (int i = Sheep.right - 5; i < Sheep.right + 5; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Sheep.top + Sheep.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_playerBullet()->set_direction(z, i);
				break;
			}
		}
	}

	/*****************************************�ν����� �浹ó��***************************************************/

	for (int z = 0; z < _player->get_fragmentBullet()->get_bullet().size(); z++)
	{
		D2D1_RECT_F Fragment = _player->get_fragmentBullet()->get_bullet()[z].rc;

		for (int i = Fragment.bottom - 20; i < Fragment.bottom + 20; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (Fragment.right + Fragment.left) / 2, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// ���� �浹
			if (r == 0 && g == 255 && b == 0)
			{
				_player->get_fragmentBullet()->set_rect(z, i);
				_player->get_fragmentBullet()->set_gravity(z);
				break;
			}
		}

		for (int i = Fragment.left + 10; i > Fragment.left - 15; i--)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, Fragment.bottom - 5);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_fragmentBullet()->set_direction(z);
				break;
			}
		}

		for (int i = Fragment.right - 10; i < Fragment.right + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, Fragment.bottom - 5);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_fragmentBullet()->set_direction(z);
				break;
			}
		}
	}

	/***************************************** ����  �浹ó��***************************************************/

	for (int z = 0; z < _player->get_WeaponBullet()->get_bullet().size(); z++)
	{
		int r_left(0), g_left(0), b_left(0);
		int r_right(0), g_right(0), b_right(0);
		float x_left(0), y_left(0), x_right(0), y_right(0);

		int direction = _player->get_WeaponBullet()->get_bullet()[z].direction;

		D2D1_RECT_F Weapon = _player->get_WeaponBullet()->get_bullet()[z].rc;

		for (int i = Weapon.bottom - 5; i < Weapon.bottom + 10; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (Weapon.right + Weapon.left) / 2, i);
			COLORREF color_left = GetPixel(_stage->getMemDC(), Weapon.left, i);
			COLORREF color_right = GetPixel(_stage->getMemDC(), Weapon.right, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			r_left = GetRValue(color_left);
			g_left = GetGValue(color_left);
			b_left = GetBValue(color_left);

			r_right = GetRValue(color_right);
			g_right = GetGValue(color_right);
			b_right = GetBValue(color_right);

			// ���� �浹
			if (r == 0 && g == 255 && b == 0)
			{
				_player->get_WeaponBullet()->set_rect(z, i);
				_player->get_WeaponBullet()->set_gravity(z);
				break;
			}

			// ���� �浹
			if (r_left == 0 && g_left == 255 && b_left == 0)
			{
				_player->get_WeaponBullet()->set_rect(z, i);
				_player->get_WeaponBullet()->set_gravity(z);

				x_left = Weapon.left;
				y_left = i;
			}

			// ���� �浹
			if (r_right == 0 && g_right == 255 && b_right == 0)
			{
				_player->get_WeaponBullet()->set_rect(z, i);
				_player->get_WeaponBullet()->set_gravity(z);

				x_right = Weapon.right;
				y_right = i;
			}
		}

		for (int i = Weapon.left + 10; i > Weapon.left - 10; i--)
		{
			if (direction == 1) continue;
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Weapon.top + Weapon.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_WeaponBullet()->set_direction(z, i);
				_player->get_WeaponBullet()->set_speed(z);
				break;
			}
		}

		for (int i = Weapon.right -50; i < Weapon.right + 10; i++)
		{
			if (direction == 0) continue;
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Weapon.top + Weapon.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_WeaponBullet()->set_direction(z, i);
				_player->get_WeaponBullet()->set_speed(z);
				break;
			}
		}
	}
}

void collision::pixel_collision_enemy()
{
	int r(0), g(0), b(0);

	for (int i = 0; i < _enemy->getVMinion().size(); i++)
	{
		int direction = 0;
		bool is_triggered = false;
		D2D1_RECT_F enemy_body = _enemy->getVMinion()[i]->getRect();

		for (int j = enemy_body.bottom - 10; j < enemy_body.bottom + 5; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (enemy_body.right + enemy_body.left) / 2, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_enemy->getVMinion()[i]->set_top(j);
				_enemy->getVMinion()[i]->set_gravity(0.0f);
				break;
			}
			else
			{
				is_triggered = true;
				_enemy->getVMinion()[i]->set_gravity(5.0f);
				direction = _enemy->getVMinion()[i]->get_direction();
			}
		}

		if (_enemy->getVMinion()[i]->get_kind() == enemy_kind::PLANT) continue;
	
		for (int j = enemy_body.left - 5; j < enemy_body.left + 1; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (enemy_body.top + enemy_body.bottom)/2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (is_triggered && direction == 1) continue;

			if (r == 0 && g == 255 && b == 255)
			{
				if (_enemy->getVMinion()[i]->get_direction() == 0)
				{

					_enemy->getVMinion()[i]->set_direction(1);
				}
				else
				{
					_enemy->getVMinion()[i]->set_direction(0);
				}
				break;
			}

			// ������ ����Ÿ �ȼ��� ������ ������ �Ѵ�
			if (r == 255 && g == 0 && b == 255 && _enemy->getVMinion()[i]->get_kind() == enemy_kind::KID)
			{
				_enemy->getVMinion()[i]->set_jumpPower(7.2f);
			}

			// �ź��̴� ����Ÿ �ȼ��� ������ ������ �ٲ۴�
			if (r == 255 && g == 0 && b == 255 && _enemy->getVMinion()[i]->get_kind() == enemy_kind::TURTLE || 
				r == 255 && g == 0 && b == 255 && _enemy->getVMinion()[i]->get_kind() == enemy_kind::TREE)
			{
				if (_enemy->getVMinion()[i]->get_direction() == 0)
				{
					_enemy->getVMinion()[i]->set_direction(1);
				}
				else
				{
					_enemy->getVMinion()[i]->set_direction(0);
				}
				break;
			}

		}

		for (int j = enemy_body.right - 5; j < enemy_body.right + 1; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (enemy_body.top+ enemy_body.bottom)/2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (is_triggered && direction == 0) continue;

			if (r == 0 && g == 255 && b == 255)
			{
				if (_enemy->getVMinion()[i]->get_direction() == 0)
				{
					_enemy->getVMinion()[i]->set_direction(1);
				}
				else
				{
					_enemy->getVMinion()[i]->set_direction(0);
				}
				break;
			}

			// ������ ����Ÿ �ȼ��� ������ ������ �Ѵ�
			if (r == 255 && g == 0 && b == 255 && _enemy->getVMinion()[i]->get_kind() == enemy_kind::KID)
			{
				_enemy->getVMinion()[i]->set_jumpPower(7.2f);
			}

			// �ź��̴� ����Ÿ �ȼ��� ������ ������ �ٲ۴�
			if (r == 255 && g == 0 && b == 255 && _enemy->getVMinion()[i]->get_kind() == enemy_kind::TURTLE || 
				r == 255 && g == 0 && b == 255 && _enemy->getVMinion()[i]->get_kind() == enemy_kind::TREE)
			{
				if (_enemy->getVMinion()[i]->get_direction() == 0)
				{
					_enemy->getVMinion()[i]->set_direction(1);
				}
				else
				{
					_enemy->getVMinion()[i]->set_direction(0);
				}
				break;
			}
		}
	}

	/***************************************** ����� ���� *****************************************************/

	for (int i = 0; i < _fish->getVMinion().size(); i++)
	{
		D2D1_RECT_F fish_body = _fish->getVMinion()[i]->getRect();

		for (int j = fish_body.bottom - 10; j < fish_body.bottom + 20; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (fish_body.right + fish_body.left) / 2, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_fish->getVMinion()[i]->set_top(j);
				break;
			}
		}

		for (int j = fish_body.left + 35; j > fish_body.left - 25; j--)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, fish_body.top);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_fish->getVMinion()[i]->set_direction(1);
				break;
			}
		}

		for (int j = fish_body.right - 5; j < fish_body.right + 5; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (fish_body.top + fish_body.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_fish->getVMinion()[i]->set_direction(0);
				break;
			}
		}

		if (fish_body.left < 4410)
		{
			_fish->set_fish_num(-1);
			_fish->remove_unit(i);
			break;
		}
	}
}

void collision::player_AND_enemy()
{
	// �÷��̾� �ٸ��� ���ʹ� ���� �浹������, ���ʹ� ����
	for (int i = 0; i < _enemy->getVMinion().size(); i++)
	{
		D2D1_RECT_F player_leg = _player->getTagPlayer()->rc;
		D2D1_RECT_F enemy_body = _enemy->getVMinion()[i]->getRect();
		// �浹�ߴٸ�
		if (INTERSECTION_RECT(temp, player_leg, enemy_body))
		{
			if (player_leg.bottom < enemy_body.top + 10)
			{
				_player->getTagPlayer()->jumpPower = 7.5f;
				_hit->startEffect(enemy_body.left, enemy_body.bottom);

				_enemy->remove_unit(i);
				_im->setDropItem(enemy_body.left, enemy_body.top, false);

				break;
			}
			else if (player_leg.right > enemy_body.left + 10 && _player->getTagPlayer()->hitInterval > 120)
			{
				_player->getTagPlayer()->isHit = true;
				_player->getTagPlayer()->hitInterval = 0;

				break;
			}
			else if (player_leg.left < enemy_body.right - 10 && _player->getTagPlayer()->hitInterval > 120)
			{
				_player->getTagPlayer()->isHit = true;
				_player->getTagPlayer()->hitInterval = 0;

				break;
			}
		}

		D2D1_RECT_F player_hitBoxL = _player->getTagPlayer()->hitBoxL;
		D2D1_RECT_F player_hitBoxR = _player->getTagPlayer()->hitBoxR;

		if (INTERSECTION_RECT(temp, player_hitBoxL, enemy_body) || INTERSECTION_RECT(temp, player_hitBoxR, enemy_body))
		{
			_hit->startEffect(enemy_body.left, enemy_body.bottom);

			_enemy->remove_unit(i);
			_im->setDropItem(enemy_body.left, enemy_body.top, false);

			break;
		}
	}

/************************************************************************************************************************/
	// �÷��̾�� ����� �浹 - ��մ� ��Ʈ���� �־���ؿ�
	for (int i = 0; i < _fish->getVMinion().size(); i++)
	{
		if (_fish->getVMinion()[i]->get_kind() == enemy_kind::FISH) continue;
		D2D1_RECT_F player_leg = _player->getTagPlayer()->rc;

		D2D1_RECT_F NPC = _fish->getVMinion()[i]->getRect();

		// �浹�ߴٸ�
		if (INTERSECTION_RECT(temp, player_leg, NPC))
		{
			if (player_leg.bottom < NPC.top + 10)
			{
				_player->getTagPlayer()->jumpPower = 7.5f;
				_fish->set_npc_num(-1);
				_fish->remove_unit(i);
				break;
			}
		}
	}

	// �÷��̾�� ����� �浹 
	for (int i = 0; i < _fish->getVMinion().size(); i++)
	{
		if (_fish->getVMinion()[i]->get_kind() == enemy_kind::NPC) continue;
		D2D1_RECT_F player_leg = _player->getTagPlayer()->rc;
		D2D1_RECT_F Fish = _fish->getVMinion()[i]->getRect();

		if (INTERSECTION_RECT(temp, player_leg, Fish) && _player->getTagPlayer()->hitInterval > 120)
		{
			_player->getTagPlayer()->isHit = true;
			_player->getTagPlayer()->hitInterval = 0;
			break;
		}
	}

/************************************************************************************************************************/
}

void collision::player_AND_object()
{
	// �÷��̾�� �������� ���� �浹
	for (int i = 0; i < _obj->get_object().size(); i++)
	{
		if (_obj->get_object()[i].type != object_type::BRANCH) continue;

		D2D1_RECT_F player = _player->getTagPlayer()->rc;
		D2D1_RECT_F Object = _obj->get_object()[i].rc;

		// �浹�ߴٸ�
		if (INTERSECTION_RECT(temp, player, Object) && !_obj->get_object()[i].is_broken)
		{
			if (player.bottom < Object.top + 10)
			{
				_obj->set_is_touched(i);

				int height = (_player->getTagPlayer()->rc.bottom - _player->getTagPlayer()->rc.top);
				_player->getTagPlayer()->rc.top = Object.top - height;
				_player->getTagPlayer()->rc.bottom = Object.top;
				_player->getTagPlayer()->y = _player->getTagPlayer()->rc.top;
				_player->getTagPlayer()->isground = true;
				_player->getTagPlayer()->isJump = false;
				_player->getTagPlayer()->jumpPower = 0;
				_player->getTagPlayer()->gravity = 0.7f;

				break;
			}
		}
	}

	// �÷��̾�� ���罺������ ������ �浹
	for (int i = 0; i < _obj->get_object().size(); i++)
	{
		if (_obj->get_object()[i].type != object_type::GATE) continue;
		D2D1_RECT_F player = _player->getTagPlayer()->rc;
		D2D1_RECT_F Object = _obj->get_object()[i].rc;

		if (INTERSECTION_RECT(temp, player, Object))
		{
			int width = (_player->getTagPlayer()->rc.right - _player->getTagPlayer()->rc.left);
			_player->getTagPlayer()->rc.right = Object.left;
			_player->getTagPlayer()->rc.left = _player->getTagPlayer()->rc.right - width;
			_player->getTagPlayer()->x = _player->getTagPlayer()->rc.left;
			break;
		}
	}

/************************************************************************************************************************/
	// �÷��̾�� ���罺������ ����ȭ����� �浹 - ��մ� ��Ʈ���� �־���ؿ�
	for (int i = 0; i < _obj->get_arrow()->getVBullet().size(); i++)
	{
		D2D1_RECT_F player = _player->getTagPlayer()->rc;
		D2D1_RECT_F Object = _obj->get_arrow()->getVBullet()[i].rc;

		if (INTERSECTION_RECT(temp, player, Object) && _player->getTagPlayer()->hitInterval > 120)
		{
			_player->getTagPlayer()->isHit = true;
			_player->getTagPlayer()->hitInterval = 0;
		}
	}
/************************************************************************************************************************/
}

void collision::player_bullet_AND_enemy()
{
	// ����հ� �� �浹�� �ҷ� ����
	for (int i = 0; i < _player->get_playerBullet()->get_bullet().size(); i++)
	{
		D2D1_RECT_F bullet = _player->get_playerBullet()->get_bullet()[i].rc;

		if (_player->get_playerBullet()->get_bullet()[i].type == LIGHT)
		{
			D2D1_RECT_F temp = D2DMANAGER->RectMakeCenter((bullet.left + bullet.right) / 2, (bullet.top + bullet.bottom) / 2, 40, bullet.bottom - bullet.top);
			bullet = temp;
		}

		for (int j = 0; j < _enemy->getVMinion().size(); j++)
		{
			D2D1_RECT_F enemy_body = _enemy->getVMinion()[j]->getRect();

			if (INTERSECTION_RECT(temp, bullet, enemy_body))
			{
				_enemy->remove_unit(j);
				_im->setDropItem(enemy_body.left, enemy_body.top, false);

				if (_player->get_playerBullet()->get_bullet()[i].type == SHEEP)
				{
					_hit->startEffect(bullet.left, bullet.bottom);
					_player->get_playerBullet()->removeMissile(i);
				}
				break;
			}
		}
	}

	// ������ �浹��
	for (int i = 0; i < _player->get_WeaponBullet()->get_bullet().size(); i++)
	{
		D2D1_RECT_F Spear = _player->get_WeaponBullet()->get_bullet()[i].rc;

		for (int j = 0; j < _enemy->getVMinion().size(); j++)
		{
			D2D1_RECT_F enemy_body = _enemy->getVMinion()[j]->getRect();

			if (INTERSECTION_RECT(temp, Spear, enemy_body))
			{
				_enemy->remove_unit(j);
				_im->setDropItem(enemy_body.left, enemy_body.top, false);

				
				if (Spear.right < enemy_body.right)
				{
					_player->get_WeaponBullet()->set_direction(i, 1);
					_player->get_WeaponBullet()->set_speed(i);
				}
				else
				{
					_player->get_WeaponBullet()->set_direction(i, 0);
					_player->get_WeaponBullet()->set_speed(i);
				}

				break;
			}
		}
	}
}

void collision::Enemy_bullet_AND_anything()
{
	int r(0), g(0), b(0);

	for (int i = 0; i < _enemy->get_bullet()->getVBullet().size(); i++)
	{
		bool is_deleted = false;
		
		if (_enemy->getVMinion()[i]->get_kind() != enemy_kind::PLANT) continue;

		// �÷��̾� ��
		D2D1_RECT_F player_body = _player->getTagPlayer()->rc;
		// �ҷ� RECT
		D2D1_RECT_F bullet = { _enemy->get_bullet()->getVBullet()[i].rc.left + 21, _enemy->get_bullet()->getVBullet()[i].rc.top,
							   _enemy->get_bullet()->getVBullet()[i].rc.right - 21, _enemy->get_bullet()->getVBullet()[i].rc.bottom };
		
		// �÷��̾�� ����� �ҷ��� �浹�� �Ѿ˻��� -> ���� ����Ʈ�� �÷��̾� �״� ��� �־����

		if (INTERSECTION_RECT(temp, player_body, bullet) && _player->getTagPlayer()->hitInterval > 120)
		{
			_player->getTagPlayer()->isHit = true;
			_player->getTagPlayer()->hitInterval = 0;
			EFFECTMANAGER->play("plant_explosion", bullet.left, bullet.bottom);
			_enemy->get_bullet()->removeBullet(i);
			is_deleted = true;
			break;
		}

		if (is_deleted)
		{
			break;
		}

		// �ҷ��� ���� �浹�� �ҷ� ����
		for (int j = bullet.bottom - 5; j < bullet.bottom + 5; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (bullet.left + bullet.right) / 2, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// ���� �浹
			if (r == 0 && g == 255 && b == 0)
			{
				EFFECTMANAGER->play("plant_explosion", bullet.left, bullet.bottom);
				_enemy->get_bullet()->removeBullet(i);
				is_deleted = true;
				break;
			}
		}
		if (is_deleted)
		{
			break;
		}

		// �ҷ��� ���� �浹�� �ҷ����� (����)
		for (int j = bullet.left - 10; j < bullet.left + 10; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (bullet.top + bullet.bottom) / 2);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// ���� �浹
			if (r == 0 && g == 255 && b == 255)
			{
				EFFECTMANAGER->play("plant_explosion", bullet.left, bullet.bottom);
				_enemy->get_bullet()->removeBullet(i);
				is_deleted = true;
				break;
			}
		}
		if (is_deleted)
		{
			break;
		}
		// �ҷ��� ���� �浹�� �ҷ����� (������)
		for (int j = bullet.right - 10; j < bullet.right + 10; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (bullet.top + bullet.bottom) / 2);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// ���� �浹
			if (r == 0 && g == 255 && b == 255)
			{
				EFFECTMANAGER->play("plant_explosion", bullet.left, bullet.bottom);
				_enemy->get_bullet()->removeBullet(i);
				is_deleted = true;
				break;
			}
		}
		if (is_deleted)
		{
			break;
		}
	}

	// ������ ��ǳ���� �浹
	for (int i = 0; i < _enemy->get_storm()->getVBullet().size(); i++)
	{
		// �÷��̾� ��
		D2D1_RECT_F player_body = _player->getTagPlayer()->rc;
		// �ҷ� RECT
		D2D1_RECT_F bullet = { _enemy->get_storm()->getVBullet()[i].rc.left, _enemy->get_storm()->getVBullet()[i].rc.top,
							   _enemy->get_storm()->getVBullet()[i].rc.right, _enemy->get_storm()->getVBullet()[i].rc.bottom };

		if (INTERSECTION_RECT(temp, player_body, bullet) && _player->getTagPlayer()->hitInterval > 120)
		{
			_player->getTagPlayer()->isHit = true;
			_player->getTagPlayer()->hitInterval = 0;
			break;
		}

	}
}

void collision::item_colision()
{
	int r(0), g(0), b(0);
	for (int j = 0; j < _im->getvWeapon().size(); j++)
	{
		D2D1_RECT_F item = _im->getvWeapon()[j].rc;
		for (int i = item.bottom - 15; i < item.bottom + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (item.right + item.left) / 2, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_im->setGravity(_im->getvWeapon()[j].typeNum, j, i);
				break;
			}
		}
	}

	for (int j = 0; j < _im->getvArmor().size(); j++)
	{
		D2D1_RECT_F item = _im->getvArmor()[j].rc;
		for (int i = item.bottom - 15; i < item.bottom + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (item.right + item.left) / 2, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_im->setGravity(_im->getvArmor()[j].typeNum, j, i);
				break;
			}
		}
	}

	for (int j = 0; j < _im->getvOther().size(); j++)
	{
		D2D1_RECT_F item = _im->getvOther()[j].rc;
		for (int i = item.bottom - 15; i < item.bottom + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (item.right + item.left) / 2, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_im->setGravity(_im->getvOther()[j].typeNum, j, i);
				break;
			}
		}
	}
	
}


void collision::bird_AND_enemy()
{
	//�� �Ѿ� ���� 20��
	for (int m = 0; m < 20; m++)
	{
		//�� �Ѿ��� �߻�Ǿ� �ִٸ�
		if (_bird->getRcBirdShot(m))
		{
			//�������ִ� ����� �浹 Ȯ��
			for (int i = 0; i < _enemy->getVMinion().size(); i++)
			{
				D2D1_RECT_F bird = _bird->getBirdRC(m);
				D2D1_RECT_F enemy_body = _enemy->getVMinion()[i]->getRect();

				// �浹�ߴٸ�
				if (INTERSECTION_RECT(temp, bird, enemy_body))
				{
					_bird->setBirdDistory(m);
					_enemy->remove_unit(i);
					break;

				}
			}


		}
	}

}


void collision::item_pick_up()
{

	if (_player->getPickUpCheck())
	{
		//�����ϸ� ��ȣ ���ֱ�
		_player->setPickUpCheckF();

		D2D1_RECT_F player = _player->getTagPlayer()->rc;
		//���Ⱑ ������ ������
		for (int j = 0; j < _im->getvWeapon().size(); j++)
		{
			D2D1_RECT_F item = _im->getvWeapon()[j].rc;
			if (INTERSECTION_RECT(temp, player, item))
			{
				int type = _im->getvWeapon()[j].typeNum;
				int color = _im->getvWeapon()[j].colorNum;
				//int durability = _im->getvWeapon()[j].durability;
				//������ �Լ� ����
				int durability = 0;

				//�κ��丮�� Ȯ���ϰ� �ֿ� �� ������ �ݰ� ������ ���� ���ֿ�� ��ġ
				if (_player->pickUpItem(type, color, durability))
				{
					_im->removeItem(j);
				}
			}
		}
		//���� ������ ������
		for (int j = 0; j < _im->getvArmor().size(); j++)
		{
			D2D1_RECT_F item = _im->getvArmor()[j].rc;
			if (INTERSECTION_RECT(temp, player, item))
			{
				int type = _im->getvArmor()[j].typeNum;
				int color = _im->getvArmor()[j].colorNum;
				//int durability = _im->getvWeapon()[j].durability;
				//������ �Լ� ����
				int durability = 0;
				//�κ��丮�� Ȯ���ϰ� �ֿ� �� ������ �ݰ� ������ ���� ���ֿ�� ��ġ
				if (_player->pickUpItem(type, color, durability))
				{
					_im->removeArmor(j);
				}
			}
		}
		//���� �� ���� ������ ������
		for (int j = 0; j < _im->getvOther().size(); j++)
		{
			D2D1_RECT_F item = _im->getvOther()[j].rc;
			if (INTERSECTION_RECT(temp, player, item))
			{
				int type = _im->getvOther()[j].typeNum;
				int color = _im->getvOther()[j].colorNum;
				int durability = 0;
				//�κ��丮�� Ȯ���ϰ� �ֿ� �� ������ �ݰ� ������ ���� ���ֿ�� ��ġ
				if (_player->pickUpItem(type, color, durability))
				{
					_im->removeOther(j);
				}
			}
		}

	}
}

void collision::item_drop()
{

	if (_menu->getdropItem())
	{
		_menu->setdropItemF();

		float x = _player->getPlayerX();
		float y = _player->getPlayerY();

		int type = _menu->dropType();
		int color = _menu->dropColor();
		int durability = _menu->dropDurability();

		_im->setDropItemMenu(x, y, type, color);

	}

}

