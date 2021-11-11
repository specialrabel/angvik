#pragma once
#include "gameNode.h"
#include "item.h"
#include "title.h"

struct tagStartItem
{
	float x, y;
};

class itemManager : public gameNode
{
private:
	vector<tagWeapon> _vWeapon;
	vector<tagWeapon>::iterator _viWeapon;
	vector<tagArmor> _vArmor;
	vector<tagArmor>::iterator _viArmor;
	vector<tagOther> _vOther;
	vector<tagOther>::iterator _viOther;

private:

	tagStartItem _startItem;
	tagWeapon _weapon;
	tagArmor _armor;
	JOB _job;
	item ITEM;
	float _y;

public:
	itemManager() {};
	~itemManager() {};

	HRESULT init(JOB job);
	void release();
	void update();
	void render();

	void setDropItem(float x, float y, bool key);
	void generateItem(int _typeNum, int _colorNum);
	void generateItem(int _typeNum, int _colorNum, float x, float y);
	void setGravity(int _typeNum, int num, float i);
	void removeItem(int arrNum);
	//规绢备客 坷老 昏力 眠啊
	void removeArmor(int arrNum);
	void removeOther(int arrNum);

	inline void setDurability(int durability) { _weapon.durability = durability; }
	inline int getDurability() { return _weapon.durability; }
	inline void setDurabilityMax() { _weapon.durability = _weapon.durabilityMAX; }

	vector<tagWeapon> getvWeapon() { return _vWeapon; }
	vector<tagWeapon>::iterator getviWeapon() { return _viWeapon; }

	vector<tagArmor> getvArmor() { return _vArmor; }
	vector<tagArmor>::iterator getviArmor() { return _viArmor; }

	vector<tagOther> getvOther() { return _vOther; }
	vector<tagOther>::iterator getviOther() { return _viOther; }

	void setDropItemMenu(float x, float y, int tpye, int color);

};

