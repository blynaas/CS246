#include "player.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <math.h> 

using namespace std;

Player *Player::pc = 0;

void Player::cleanup()
{
	delete pc;
}

void Player::setPlayer(Player *p)
{
	pc=p;
	atexit (cleanup);
}

Player *Player::getPlayer()
{
	return pc;
}

void Player::setPlayer(string race)
{
	if (race == "h")
	{
		pc = new Human();
	}
	else if (race == "d")
	{	
		pc = new Dwarf();
	}
	else if (race == "e")
	{
		pc = new Elf();
	}
	else if (race == "o")
	{
		pc = new Orc();
	}
}

Player::Player(int hp, int atk, int def, string race) : Character(hp, atk, def), race(race) {}

int Player::getAtk() const
{
	return atk;
}

int Player::getDef() const
{
	return def;
}

int Player::addGold(int i)
{
	gold += i;
	return i;
}

void Player::addHp(int i)
{
	hp = max(hp+i, 0);
}

string Player::getRace() const
{
	return race;
}

int Player::attack(Enemy* e)
{
	double defense = e->getDef();

	int damage = ceil((100/(100+defense))*atk);

	e->addHp((-1)*damage);

	return damage;
}

Player::~Player() {}

Human::Human() : Player(140, 20, 20, "Human") {}
Human::~Human() {}

Dwarf::Dwarf(): Player(100, 20, 30, "Dwarf") {}
Dwarf::~Dwarf(){}
int Dwarf::addGold(int i)
{
	gold += 2*i;
	return 2*i;
}

Elf::Elf(): Player(140, 30, 10, "Elf") {}
Elf::~Elf(){}

Orc::Orc(): Player(180, 30, 25, "Orc") {}
Orc::~Orc() {}
int Orc::addGold(int i)
{
	gold += i/(double)2;
	return i/(double)2;
}

