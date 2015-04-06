#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "passagetile.h"
#include "viewcontroller.h"

using namespace std;

PassageTile::PassageTile(int r, int c, string type, string name) : Cell(r, c, type, name){
	neighbours = new Cell *[maxNeighbours];
	for(int i=0; i<maxNeighbours; i++) neighbours[i]=0;
	if(name=="pass1") sym = '+';
	else if(name=="pass2") sym = '#';
}

PassageTile::~PassageTile() {}

void PassageTile::notifyDisplay(ViewController &viewCtrl) {
	viewCtrl.notify(r, c, sym);
}

void PassageTile::pushPlayer(Player *p) {
	this->p = p;
	sym = '@';
}

Player *PassageTile::getPlayer() const {
	return p;
}

Player *PassageTile::popPlayer() {
	Player *tmp = p;
	p = 0;
	if(name=="pass1") sym = '+';
	else if(name=="pass2") sym = '#';
	return tmp;
}