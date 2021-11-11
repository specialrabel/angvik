#pragma once

class player;

class State
{
private:
	player* _pl;

public:

	virtual State* inputHandle(player* player) = 0;
	virtual void update(player* player) = 0;
	virtual void enter(player* player) = 0;
	virtual void exit(player* player) = 0;

	void Attack(player* player, int LeftWeapon, int RightWeapon);
	void Hit(player* player);

	void setTagPlayer(player* player) { _pl = player; }
};
