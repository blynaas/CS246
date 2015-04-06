#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "regulartile.h"
#include "viewcontroller.h"

using namespace std;

RegularTile::RegularTile(int r, int c, int room) :  Cell(r, c, "T", "RegularTile"), room(room)
{
	sym = '.';
	avail = true;
	p=0;e=0;
	contain=0;
	neighbours = new Cell *[maxNeighbours];
	for(int j=0; j<maxNeighbours; j++) neighbours[j]=0;
}

RegularTile::~RegularTile()
{
	delete e;
}

void RegularTile::notifyDisplay(ViewController &viewCtrl)
{
	viewCtrl.notify(r, c, sym);
}

bool RegularTile::available() const
{
	return avail && !p && !e;
}

void RegularTile::setDoorway()
{
	avail = false;
	sym = '\\';
	type = "D";
}

char RegularTile::getContain() const
{
	return contain;
}

int RegularTile::getRoom() const
{
	return room;
}

void RegularTile::pushPlayer(Player *p)
{
	this->p = p;
	sym = '@';
	contain = sym;
}

Player *RegularTile::getPlayer() const
{
	return p;
}

Player *RegularTile::popPlayer()
{
	Player *tmp=p;
	p=0;
	sym = '.';
	contain = ' ';
	return tmp;
}

void RegularTile::pushEnemy(Enemy *e)
{
	this->e = e;
	string tmpType = e->getType();
	if(tmpType=="vampire") sym = 'V';
	else if(tmpType=="werewolf") sym = 'W';
	else if(tmpType=="troll") sym = 'T';
	else if(tmpType=="goblin") sym = 'N';
	else if(tmpType=="merchant") sym = 'M';
	else if(tmpType=="dragon") sym = 'D';
	else if(tmpType=="phoenix") sym = 'X';
	if(sym=='M'||sym=='D') contain = sym;
	else contain = 'E';
}

Enemy *RegularTile::getEnemy() const
{
	return e;
}

Enemy *RegularTile::popEnemy()
{
	Enemy *tmp = e;
	e=0;
	sym = '.';
	contain = ' ';
	return tmp;
}

void RegularTile::pushItem(Item *i) 
{
	this->i = i;
	type = i->getType();

	if (type == "treasure")
	{
		sym = 'G';
	}
	else if (type == "potion")
	{
		sym = 'P';
	}
	contain = sym;
}

Item *RegularTile::getItem() const
{
	return i;
}

Item *RegularTile::popItem()
{
	Item *tmp = i;
	i=0;
	sym = '.';
	contain = ' ';
	type="T";
	return tmp;
}