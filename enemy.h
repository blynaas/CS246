#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <string>
#include "character.h"

class Enemy : public Character {
	protected:
	std::string type;
	bool movedThisTurn;
	Enemy(int hp, int atk, int def, std::string type);
	public:
	std::string getType() const;
	void addHp(int i);
	int getAtk() const;
	int getDef() const;
	int getHp() const;
	void setMoved(bool val);
	bool getMoved() const;
	
	virtual void notify();
	virtual ~Enemy()=0;
};

class Goblin : public Enemy {
	int pgold;
	public:
	Goblin(); //70 HP, 5 Atk, 10 Def
	~Goblin();
};

#endif