#pragma once
#include "gameNode.h"


enum JOB
{
	KING,
	LANCER,
	SHEPHERD,
	PALADIN,
	BOTTLER,
	PEASANT,
	GREATGUY
};

struct tagMENU
{
	image* bar;
	image* sel;
	image* option;
	image* exit;
	image* start;

	bool isChoice[3];
};

struct tagOption
{
	image* menu;
	image* vol;
	image* music;
	image* on;
	image* off;
	image* num[5];
	image* back;
	image* ySel;

	bool isChoiceX[5], isChoiceY[3];
	int volNum, musicNum;
};

struct tagJOB
{
	image* king[2];
	image* lancer[2];
	image* shepherd[2];
	image* paladin[2];
	image* bottler[2];
	image* peasant[2];
	image* greatguy[3];
	image* level;
	image* yfw;

	JOB jobNum;

	int ggindex;
	bool isChoice[8];
};

struct tagCloud
{
	D2D1_RECT_F rc;
	image* img;
	float speed;
	int loopX, loopY;
};

struct tagMountain
{
	image* img;
	float x, y;
};

struct tagCAM
{
	D2D1_RECT_F rc;
	float speed, angle;
	float x, y;
};

struct tagforeGround
{
	image* img;
	float speed, angle;
	float x, y;
};

class title : public gameNode
{
private:
	image* _backGround;
	image* _logo;

	tagMountain _mountain1;
	tagMountain _mountain2;
	tagMountain _mountain3;
	tagMountain _mountain4;

	tagCloud _cloud1;
	tagCloud _cloud2;
	tagCloud _cloud3;
	tagCloud _cloud4;

	tagforeGround _foreGround;
	tagCAM cam;
	tagMENU _menu;
	tagOption _op;
	tagJOB _job;

	bool _isMain;
	bool _isOption;
	bool _isLand;
	bool _isStart;
	int _numX, _numY;
	int _jobMax;
	int _index;
	int _count;
	int _movement;

	float _opacity;
	float _bgOpacity;

public:

	title() {};
	~title() {};

	HRESULT init();
	void release();
	void update();
	void render();

	inline JOB getJob() { return _job.jobNum; }
};

