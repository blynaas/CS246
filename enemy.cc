#include <string>
#include <iostream>
#include "enemy.h"

using namespace std;

Enemy::Enemy(int hp, int atk, int def, string type) : Character(hp, atk, def), type(type), movedThisTurn(false) {}
string Enemy::getType() const {return type;}
void Enemy::addHp(int i) {hp+=i;}
int Enemy::getAtk() const {return atk;}
int Enemy::getDef() const {return def;}
int Enemy::getHp() const {return hp;}

void Enemy::setMoved(bool val){movedThisTurn = val;}
bool Enemy::getMoved() const {return movedThisTurn;}

void Enemy::notify() {}
Enemy::~Enemy() {}

Goblin::Goblin() : Enemy(70, 5, 10, "goblin") {gold=1; pgold=0;}
Goblin::~Goblin() {}
