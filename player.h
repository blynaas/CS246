#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include "character.h"
#include "enemy.h"

class Enemy;

class Player : public Character {
	static Player *pc;
	static void cleanup();
protected:
	std::string race;
	Player(int hp, int atk, int def, std::string race);
	
public:

	static Player *getPlayer();

	static void setPlayer(std::string race);
	static void setPlayer(Player *p);

	virtual int addGold(int i);
	virtual void addHp(int i);

	std::string getRace() const;

	int getAtk() const;
	int getDef() const;
	int attack(Enemy* e);
	
	virtual ~Player()=0;
};

class Human : public Player {
	public:
	Human();
	~Human();
};

class Dwarf : public Player {
	public:
		Dwarf();
		~Dwarf();
		int addGold(int i);
};

class Elf : public Player {
	public:
		Elf();
		~Elf();
};

class Orc : public Player {
	public:
		Orc();
		~Orc();
		int addGold(int i);
};

#endif