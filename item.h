#pragma once
#include "gameNode.h"
enum ITEMTYPE
{
	SWORD,
	LANCE,
	BOOMERANG,
	STAFF,
	HEAD,
	BODY,
	FOOT,
	OIL,
	EGG,
	BOX,
	KEY,
	TYPEEND
};

enum ITEMCOLOR
{
	BLACK,
	BLUE,
	GOLD,
	GREEN,
	PINK,
	RED,
	WHITE,
	SPECIAL,
	COLOREND
};


struct tagWeapon
{
	image* img;
	int durability, durabilityMAX; //내구도, 내구도맥스
	D2D1_RECT_F rc;
	float x, y;
	float gravity;
	int colorNum, typeNum;
	bool second, third, fourth, fifth;
};

struct tagArmor
{
	image* img;
	int durability, durabilityMAX; //내구도, 내구도맥스
	//D2D1_RECT_F handRc, tipRc; //손잡이 렉트, 끝부분 렉트 -> 불렛부분에서 구현?
	D2D1_RECT_F rc;
	float x, y;
	float gravity;
	int colorNum, typeNum;
	bool second;
};

struct tagOther
{
	image* img;
	D2D1_RECT_F rc;
	float x, y;
	float gravity;
	int colorNum, typeNum;
};

class item : public gameNode
{
private:
	tagWeapon _weapon;
	ITEMTYPE _type;
	ITEMCOLOR _color;
public:
	item() {};
	~item() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

