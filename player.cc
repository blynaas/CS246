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
Player *Player::getPlayer(string race)
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

//Public part
Player::Player(int hp, int atk, int def, string race) :
 Character(hp, atk, def), race(race), oriHp(hp), maxAcc(1), acc(0), exAtk(0), exDef(0) {
}

//int Player::getAtk() const {return atk+exAtk;}
//int Player::getDef() const {return def+exDef;}
int Player::getAtk() const {return atk;}
int Player::getDef() const {return def;}
void Player::addGold(int i) {gold+=i;cout << i<<" "<<gold<<endl;}
//void Player::addAtk(int i) {exAtk+=i;}
//void Player::addDef(int i) {exDef+=i;}
void Player::returnGold(int i) {gold+=i;}
void Player::buyAtk(int i) {atk+=i;}
void Player::buyDef(int i) {def+=i;}
void Player::addHp(int i) {hp = max(hp+i, 0);}
void Player::addAcc() {acc++;}
void Player::addMaxAcc() {maxAcc++;}
int Player::getMaxAcc() const {return maxAcc;}
int Player::getOriHp() const {return oriHp;}
int Player::getAcc() const {return acc;}
void Player::clearAcc() {acc=0;}
string Player::getRace() const {return race;}
void Player::lossHp(int i) {hp-=i;}
void Player::lossGold(int i) {gold-=i;}
/*void Player::clear() {
	exAtk=0;
	exDef=0;
}*/
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
