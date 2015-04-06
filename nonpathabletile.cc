#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "nonpathabletile.h"
#include "viewcontroller.h"

using namespace std;

NonPathableTile::NonPathableTile(int r, int c, string type, string name) : Cell(r, c, type, name)
{
	neighbours = new Cell *[maxNeighbours];
	for(int i=0; i<maxNeighbours; i++) neighbours[i]=0;
	if(name=="wall1") sym = '|';
	else if(name=="wall2") sym = '-';
	else if(name=="empty") sym = ' ';
}

NonPathableTile::~NonPathableTile() {}

void NonPathableTile::notifyDisplay(ViewController &viewCtrl)
{
	viewCtrl.notify(r, c, sym);
}
