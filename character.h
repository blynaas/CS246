#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <stdlib.h>
#include <iostream>

using namespace std;

class Character {
	protected:
	int hp;
	int atk;
	int def;
	double gold;
	Character(int hp, int atk, int def);
	public:
	double getGold() const;
	int getHp() const;
	
	virtual ~Character();
};

#endif
