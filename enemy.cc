#include <string>
#include <iostream>
#include <math.h>
#include "enemy.h"
#include <stdlib.h>

using namespace std;

Enemy::Enemy(int hp, int atk, int def, string type) : Character(hp, atk, def), type(type), movedThisTurn(false) {}

string Enemy::getType() const
{
	return type;
}

void Enemy::addHp(int i)
{
	hp = max(0, hp+i);
}

int Enemy::getAtk() const
{
	return atk;
}

int Enemy::getDef() const
{
	return def;
}

int Enemy::getHp() const
{
	return hp;
}

void Enemy::setMoved(bool val)
{
	movedThisTurn = val;
}

bool Enemy::getMoved() const
{
	return movedThisTurn;
}

int Enemy::attack(Player* p)
{
	
	int rnd = rand()%2;

	double defense = p->getDef();

	int damage = ceil((100/(100+defense))*atk);

	if (rnd == 0)
	{
		p->addHp((-1)*damage);
	}
	else
	{
		damage = -1;
	}

	//returns -1 to signify a miss
	return damage;
}

void Enemy::notify() {}
Enemy::~Enemy() {}

Goblin::Goblin() : Enemy(70, 5, 10, "goblin")
{
	gold = 1;
}
Goblin::~Goblin() {}

Troll::Troll() : Enemy(120, 25, 15, "troll")
{
	gold = 1;
}
Troll::~Troll() {}

Vampire::Vampire() : Enemy(50, 25, 25, "vampire")
{
	gold = 1;
}
Vampire::~Vampire() {}

Werewolf::Werewolf() : Enemy(120, 30, 5, "werewolf")
{
	gold = 1;
}
Werewolf::~Werewolf() {}

Merchant::Merchant() : Enemy(30, 70, 5, "merchant")
{
	gold=0;
}
Merchant::~Merchant() {}

Dragon::Dragon() : Enemy(150, 20, 20, "dragon")
{
	gold=0;
}
Dragon::~Dragon() {}

Phoenix::Phoenix() : Enemy(50, 35, 20, "phoenix")
{
	gold=1;
}
Phoenix::~Phoenix() {}
