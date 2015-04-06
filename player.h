#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "character.h"
#include "enemy.h"

class Enemy;

class Player : public Character {
	static Player *pc; //singleton
	static void cleanup(); //singleton
	protected:
	std::string race; //race of the player
	const int oriHp; //save the original Hp**
	int maxAcc; //used to determine when to recover Hp**
	int acc; //used to determine when to recover Hp**
	int exAtk; //actualAtk = exAtk+atk
	int exDef; //actualDef = exDef+def
	Player(int hp, int atk, int def, std::string race);
	
	public:
	static Player *getPlayer(); //singleton
	static void setPlayer(std::string race);
	static void setPlayer(Player *p); //singleton

	virtual void addGold(int i); //half for orc;;double for dwarf
	virtual void addHp(int i); //add to Hp;; ABS for elf
	int getOriHp() const; //used to determine when to recover Hp**
	std::string getRace() const; //get the race
	void clear(); //used when player go to the next floor
	int getAtk() const; //atk+exAtk
	int getDef() const; //def+exDef
	int attack(Enemy* e);
	virtual ~Player()=0;
};

class Human : public Player {
	public:
	Human(); //140HP, 20Atk, 20Def
	~Human();
};

class Dwarf : public Player {
	public:
		Dwarf(); //100HP, 20Atk 30Def
		~Dwarf();
};

class Elf : public Player {
	public:
		Elf(); // 140HP, 30Atk, 10Def
		~Elf();
};

class Orc : public Player {
	public:
		Orc();// 180HP, 30Atk, 25Def
		~Orc();
};

#endif