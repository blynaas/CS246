#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "character.h"
#include "enemy.h"

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
	static Player *getPlayer(std::string race);
	static void setPlayer(Player *p); //singleton

	virtual void addGold(int i); //half for orc;;double for dwarf
	virtual void addHp(int i); //add to Hp;; ABS for elf
	void returnGold(int i); //used to gain the returned gold from goblin*
	void buyAtk(int i); //used to gain permanent atk (by buying weapon from Merchants)****
	void buyDef(int i); //used to gain permanent def (by buying armor from Merchants)****
	void addAcc(); //used to determine when to recover Hp**
	int getOriHp() const; //used to determine when to recover Hp**
	int getAcc() const; //used to determine when to recover Hp**
	void clearAcc(); //used to determine when to recover Hp**
	void addMaxAcc(); //used to determine when to recover Hp**
	int getMaxAcc() const; //used to determine when to recover Hp**
	std::string getRace() const; //get the race
	void lossHp(int i); //used when be attacked
	void lossGold(int i); //used when gold is stealen by goblin*
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