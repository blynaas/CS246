#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "viewcontroller.h"

using namespace std;

Cell::Cell (int r, int c, std::string type, std::string name) : type(type), name(name), numNeighbours(0), sym(0), r(r), c(c)
{
	neighbours = 0;
}

string Cell::getType() const
{
	return type;
}

char Cell::getSym() const
{
	return sym;
}

void Cell::getPos (int *a, int *b)
{
	*a=r; *b=c;
}

void Cell::addNeighbour(int po, Cell *neighbour)
{
	if (!neighbours)
	{
		neighbours = new Cell *[maxNeighbours];
	}

	neighbours[po] = neighbour;
	numNeighbours++;
}

bool Cell::containsEnemy()
{
	return sym == 'N' || sym == 'T' || sym == 'W' || sym == 'V' || sym == 'M' || sym == 'X' || sym == 'D'; //TODO: make this function less stupid
}

Cell **Cell::getNeighbours() const {return neighbours;}

int Cell::getRoom() const {}
void Cell::notifyDisplay(ViewController &viewCtrl) {}
bool Cell::available() const {}
void Cell::setDoorway() {}
char Cell::getContain() const {}
void Cell::pushPlayer(Player *p) {}
Player *Cell::getPlayer() const {}
Player *Cell::popPlayer() {}
void Cell::pushEnemy(Enemy *e) {}
Enemy *Cell::getEnemy() const {}
Enemy *Cell::popEnemy() {}
void Cell::pushItem(Item *e) {}
Item *Cell::getItem() const {}
Item *Cell::popItem() {}

Cell::~Cell() {delete [] neighbours;}

