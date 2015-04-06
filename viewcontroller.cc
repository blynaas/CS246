#include <iostream>
#include <sstream>
#include "viewcontroller.h"
#include "player.h"
using namespace std;

ViewController::ViewController(int f) : p(Player::getPlayer()), f(f)
{
	action = "Player character has spawned.";

	for(int i = 0; i < MAXR; i++)
	{
		for(int j = 0; j < MAXC; j++)
		{
			theDisplay[i][j]=' ';
		}
	}
}

void ViewController::notify(int r, int c, char ch)
{
	theDisplay[r][c] = ch;
}

void ViewController::addAction(string ac)
{
	action += ac + " ";
}

void ViewController::clearActions()
{
	action = "";
}

ViewController::~ViewController() {}

ostream &operator<<(ostream &out, const ViewController &td)
{
	for(int i = 0; i < MAXR; i++)
	{
		for(int j = 0; j < MAXC; j++)
		{
			out<<td.theDisplay[i][j];
		}
		out<<"\n";
	}

	out << "Race: " << td.p->getRace() << " " << "Gold: " << td.p->getGold()
	<< "                                              " << "Floor " << td.f << "\n";
	out <<"HP: " << td.p->getHp() << "\n";
	out <<"Atk: " << td.p->getAtk() << "\n";
	out <<"Def: " << td.p->getDef() << "\n";
	out <<"Action: " << td.action << "\n";
	
	return out;
}
