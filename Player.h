#pragma once
#include "gameNode.h"
#include "State.h"
#include "bullets.h"
#include "item.h"

#define LEFT 1
#define RIGHT 2

//������ �ݱ��
class menu;

struct PLAYER
{
	image* img;
	D2D1_RECT_F rc;				//�÷��̾� ��Ʈ
	float x, y;					//�÷��̾� ��ǥ
	int width, height;			//�÷��̾� �ʺ�, ����	
	int stage;					//�÷��̾� ��������
	int dir;					//�÷��̾� ����

	bool isAttackL;				//����Ű�� �������ִ���
	bool isAttackR;				//����Ű�� �������ִ���
	bool isground;

	float speedPower;			//�÷��̾� �ӷ�?
	float speed;				//�÷��̾� ����

	float jumpPower;
	float gravity;
	bool isJump;
	bool idleArmAngle;
	bool LweaponAngle;
	bool isHit;					//�÷��̾ �¾Ҵ���
	bool isDead;				//�÷��̾ �׾�����
	bool in_water;

	//�Ӹ�
	D2D1_RECT_F rc_head;
	image* img_head;
	animation* ani_head;
	int move_headX;
	int move_headY;

	//����, �ٸ�
	D2D1_RECT_F rc_body;
	image* img_body;
	int move_bodyX;
	int move_bodyY;
	animation* ani_body;

	//����
	D2D1_RECT_F rc_Larm;
	image* img_Larm;
	animation* ani_Larm;
	int move_LarmX;
	int move_LarmY;
	float angle_Larm;

	//������
	D2D1_RECT_F rc_Rarm;
	image* img_Rarm;
	animation* ani_Rarm;
	int move_RarmX;
	int move_RarmY;
	float angle_Rarm;

	//�÷��̾� �������
	int weapon_left_type;		//�޼չ��� Ÿ��
	int weapon_left_color;		//�޼չ��� ����
	int weapon_left_durability;
	float move_LweaponX;
	float move_LweaponY;
	float angle_Lweapon;
	image* img_Lweapon;
	animation* ani_Lweapon;

	int weapon_right_type;		//�����չ��� Ÿ��
	int weapon_right_color;		//�����չ��� ����
	int weapon_right_durability;
	float move_RweaponX;
	float move_RweaponY;
	float angle_Rweapon;
	image* img_Rweapon;
	animation* ani_Rweapon;

	int helmet_color;			//���� ����
	int helmet_durability;
	image* img_helmet;
	animation* ani_helmet;

	int armor_color;			//���� ����
	int armor_durability;
	image* img_armor;
	animation* ani_armor;

	int shoes_color;			//�Ź� ����
	int shoes_durability;
	image* img_shoes;
	animation* ani_shoes;

	int hitInterval;			//�ǰ��� �����ð�
	float hitOpacity;			//�ǰݽ� ����
	int OpacityCount;			//HitState���� ����

	D2D1_RECT_F hitBoxL;
	D2D1_RECT_F hitBoxR;
};

struct EQUIPMENT
{
	int weapon_left;
	int weapon_right;
	int helmet;
	int armour;
	int shoes;
};

class player : public gameNode
{
private:
	State* _state;
	PLAYER _player;
	EQUIPMENT _equipment;

	Player_bullet* _pb;
	fragment* _frag;
	Weapon* _spear;

	//������ �ݱ� ��
	menu* _menu;
	bool _pickUpCheck;

public:
	player() {};
	~player() {};

	void InputHandle();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void playerSpeed();
	void bullet_test();

	void playerEquipRender(int type);
	void playerEquipRender(int type, int LR);
	void playerImageInit();
	void playerInfoInit();
	void playerEquipUpdate();

	void setTagPlayer(PLAYER player) { _player = player; }

	PLAYER* getTagPlayer() { return &_player; }
	Player_bullet* get_playerBullet() { return _pb; }
	fragment* get_fragmentBullet() { return _frag; }
	Weapon* get_WeaponBullet() { return _spear; }

	float getPlayerX() { return _player.x; }
	float getPlayerY() { return _player.y; }
	int getPlayerDir() { return _player.dir; }
	bool get_inWater() { return _player.in_water; }
	void set_inWater(bool val) { _player.in_water = val; }

	bool get_isDead() { return _player.isDead; }
	void set_isDead(bool val) { _player.isDead = val; }

	//������ �ݱ�
	bool getPickUpCheck() { return _pickUpCheck; }
	void setPickUpCheckF() { _pickUpCheck = false; }
	void setPickUpCheckT() { _pickUpCheck = true; }

	void linkMenu(menu* menu) { _menu = menu; }
	bool pickUpItem(int type, int color, int durability);
};

