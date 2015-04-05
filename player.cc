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
void Player::addHp(int i) {hp+=i; if(hp<=0) hp=1;}
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

Player::~Player() {}

Human::Human() : Player(140, 20, 20, "Human"){}
Human::~Human(){}
