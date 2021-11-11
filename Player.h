#pragma once
#include "gameNode.h"
#include "State.h"
#include "bullets.h"
#include "item.h"

#define LEFT 1
#define RIGHT 2

//아이템 줍기용
class menu;

struct PLAYER
{
	image* img;
	D2D1_RECT_F rc;				//플레이어 렉트
	float x, y;					//플레이어 좌표
	int width, height;			//플레이어 너비, 높이	
	int stage;					//플레이어 스테이지
	int dir;					//플레이어 방향

	bool isAttackL;				//공격키를 누르고있는지
	bool isAttackR;				//공격키를 누르고있는지
	bool isground;

	float speedPower;			//플레이어 속력?
	float speed;				//플레이어 가속

	float jumpPower;
	float gravity;
	bool isJump;
	bool idleArmAngle;
	bool LweaponAngle;
	bool isHit;					//플레이어가 맞았는지
	bool isDead;				//플레이어가 죽었는지
	bool in_water;

	//머리
	D2D1_RECT_F rc_head;
	image* img_head;
	animation* ani_head;
	int move_headX;
	int move_headY;

	//몸통, 다리
	D2D1_RECT_F rc_body;
	image* img_body;
	int move_bodyX;
	int move_bodyY;
	animation* ani_body;

	//왼팔
	D2D1_RECT_F rc_Larm;
	image* img_Larm;
	animation* ani_Larm;
	int move_LarmX;
	int move_LarmY;
	float angle_Larm;

	//오른팔
	D2D1_RECT_F rc_Rarm;
	image* img_Rarm;
	animation* ani_Rarm;
	int move_RarmX;
	int move_RarmY;
	float angle_Rarm;

	//플레이어 장비정보
	int weapon_left_type;		//왼손무기 타입
	int weapon_left_color;		//왼손무기 색상
	int weapon_left_durability;
	float move_LweaponX;
	float move_LweaponY;
	float angle_Lweapon;
	image* img_Lweapon;
	animation* ani_Lweapon;

	int weapon_right_type;		//오른손무기 타입
	int weapon_right_color;		//오른손무기 색상
	int weapon_right_durability;
	float move_RweaponX;
	float move_RweaponY;
	float angle_Rweapon;
	image* img_Rweapon;
	animation* ani_Rweapon;

	int helmet_color;			//투구 색상
	int helmet_durability;
	image* img_helmet;
	animation* ani_helmet;

	int armor_color;			//갑옷 색상
	int armor_durability;
	image* img_armor;
	animation* ani_armor;

	int shoes_color;			//신발 색상
	int shoes_durability;
	image* img_shoes;
	animation* ani_shoes;

	int hitInterval;			//피격후 무적시간
	float hitOpacity;			//피격시 투명도
	int OpacityCount;			//HitState에서 쓸것

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

	//아이템 줍기 용
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

	//아이템 줍기
	bool getPickUpCheck() { return _pickUpCheck; }
	void setPickUpCheckF() { _pickUpCheck = false; }
	void setPickUpCheckT() { _pickUpCheck = true; }

	void linkMenu(menu* menu) { _menu = menu; }
	bool pickUpItem(int type, int color, int durability);
};

