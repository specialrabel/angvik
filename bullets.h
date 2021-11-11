#pragma once
#include "gameNode.h"
#include <vector>

enum bullet_type
{
	LIGHT,
	SHEEP,
	FRAGMENT,
	SPEAR,
	ARROW,

	NOTHING
};
struct tagBullet
{
	image* bulletImage;		//�Ѿ� �̹��� 
	D2D1_RECT_F rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float interval, interval2;			//�Ѿ� ������
	float speed;			//�Ѿ� ���ǵ�
	float width;
	float height;
	float jump_power;
	float gravity;
	float opacity;
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;			//�߻�ƴ�?
	bool isGround;
	bool is_hit;
	int count;				//�Ѿ� ������ī��Ʈ��
	int direction;
	int durability;
	bullet_type type;
};

class Storm : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	Storm() {};
	~Storm() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(LPCWSTR imagename, float x, float y, float width, float height,
		float frameX, float frameY, float angle, int direction);

	void move();

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);


	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};

/******************************************* ���� ȭ�� *****************************************************/

class Arrow : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	//��Ÿ� ��(?)

public:
	Arrow() {};
	~Arrow() {};

	HRESULT init(float x, float y, int direction, bool reverse);
	void release();
	void update();
	void render();

	//�Ѿ� �߻��Լ�(������ ��ǥ)
	void fire();
	//�Ѿ� �������ݽô�
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};

/******************************************* ���ʹ� �ҷ� *****************************************************/
class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet() {};
	~bullet() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(LPCWSTR imagename, float x, float y, float width, float height,
			  float frameX, float frameY, float angle, int direction);

	void move();

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);


	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};

/**************************************** ���� ������ ����ϴ� �ҷ� *******************************************************/

class Weapon : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _angle;
	int _bulletMax;

public:
	Weapon() {};
	~Weapon() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//�Ѿ� �߻��Լ�(������ ��ǥ)
	void fire(LPCWSTR filename, float x, float y, float width, float height, int frameX, int frameY, int direction);

	//�Ѿ� �������ݽô�
	void move();
	void removeMissile(int arrNum);
	void set_speed(int num);
	void set_rect(int num, float val);
	void set_gravity(int num);
	void set_direction(int num, float val);
	void set_durability(int num, float val);

	inline void set_angle(float val) { _angle = val; }

	inline float get_angle() { return _angle; }
	vector<tagBullet> get_bullet() { return _vBullet; }
	vector<tagBullet>::iterator get_VI_bullet() { return _viBullet; }
};


/**************************************** ���̳� ���� ������ �������°͵� *******************************************************/

class fragment : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	fragment() {};
	~fragment() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//�Ѿ� �߻��Լ�(������ ��ǥ)
	void fire(LPCWSTR filename, float x, float y, float width, float height, int _direction);

	//�Ѿ� �������ݽô�
	void move();
	void removeMissile(int arrNum);
	void set_rect(int num, float val);
	void set_gravity(int num);
	void set_direction(int num);

	vector<tagBullet> get_bullet() { return _vBullet; }
	vector<tagBullet>::iterator get_VI_bullet() { return _viBullet; }
};

/**************************************** �÷��̾� �ҷ� (�� ���, ��) *******************************************************/

class Player_bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;
	fragment* _frag;

public:
	Player_bullet() {};
	~Player_bullet() {};

	HRESULT init(int bulletMax, float range, fragment* frag);
	void release();
	void update();
	void render();

	void fire(LPCWSTR filename, float x, float y, float width, float height, int frameX, int frameY, int direction);
	void fragment_fire(LPCWSTR filename, float x, float y, float width, float height, int direction);

	void move();
	void set_rect(int num, float val);
	void set_gravity(int num);
	void set_direction(int num, float distance);
	void removeMissile(int arrNum);

	vector<tagBullet> get_bullet() { return _vBullet; }
	vector<tagBullet>::iterator get_VI_bullet() { return _viBullet; }
};