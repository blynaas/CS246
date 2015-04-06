#include "player.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <math.h> 
using namespace std;

//Singleton Pattern
Player *Player::pc=0;
void Player::cleanup() {delete pc;}
void Player::setPlayer(Player *p) {pc=p; atexit (cleanup);}
Player *Player::getPlayer() {return pc;}
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

Player::Player(int hp, int atk, int def, string race) :
 Character(hp, atk, def), race(race), oriHp(hp), maxAcc(1), acc(0), exAtk(0), exDef(0) {
}

int Player::getAtk() const {return atk;}
int Player::getDef() const {return def;}
void Player::addGold(int i) {gold+=i;}
void Player::addHp(int i) {hp = max(hp+i, 0);}
int Player::getOriHp() const {return oriHp;}
string Player::getRace() const {return race;}

void Player::clear()
{
}

int Player::attack(Enemy* e)
{
	double defense = e->getDef();

	int damage = ceil((100/(100+defense))*atk);

	e->addHp((-1)*damage);

	return damage;
}

Player::~Player() {}

Human::Human() : Player(140, 20, 20, "Human"){}
Human::~Human(){}

Dwarf::Dwarf(): Player(100, 20, 30, "Dwarf"){}
Dwarf::~Dwarf(){}

Elf::Elf(): Player(140, 30, 10, "Elf"){}
Elf::~Elf(){}

Orc::Orc(): Player(180, 30, 25, "Orc"){}
Orc::~Orc(){}
