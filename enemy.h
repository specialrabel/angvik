#pragma once
#include "gameNode.h"

enum class enemy_state
{
	IDLE,
	RUN,
	ATTACK,
	HELP,
	JUMP,

	enum_max
};

enum class enemy_kind
{
	PLANT,
	MONKEY,
	FISH,
	TURTLE,
	NPC,
	KID,
	TREE,

	kind_num
};

class enemy : public gameNode
{
protected:
	image* enemy_img;		//에너미 이미지
	animation* enemy_body;
	enemy_state _state;
	enemy_kind _kind;
	D2D1_RECT_F _rc;

	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	int _count;				//프레임렌더링 용
	int each_interval[(int)enemy_state::enum_max];

	int _fireCount;			//발사 카운트 용
	int _Fire_interval;			//발사 주기

	int _direction;
	float _width;
	float _height;

	float _speed;
	float _angle;
	float _gravity;
	float _jumpPower;

	bool is_find;
	bool is_fire;
	bool is_set;

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, POINT position, int direction);

	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual bool bullet_Fire();

	void draw();

	// 픽셀충돌할때 에너미가 지면에 올려질 함수.
	virtual void set_top(float len);
	virtual void set_gravity(float val);
	void set_jumpPower(float val);

	inline float get_height() { return _height; }
	image* get_img() { return enemy_img; }
	inline D2D1_RECT_F getRect() { return _rc; }
	inline float get_angle() { return _angle; }

	inline int get_direction() { return _direction; }
	virtual void set_direction(int dir);
	void set_direction(int dir, float val);

	inline enemy_state get_state() { return _state; }
	inline enemy_kind get_kind() { return _kind; }

	void find_player() { is_find = true; }
	void Not_find_player() { is_find = false; }

	inline bool get_isFired() { return is_fire; }
	void off_isSet() { is_set = false; }

};

