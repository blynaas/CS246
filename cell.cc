#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "viewcontroller.h"

using namespace std;

Cell::Cell (int r, int c, std::string type, std::string name) : 
type(type), name(name), numNeighbours(0), sym(0), r(r), c(c) {neighbours=0;}

string Cell::getType() const {return type;}

char Cell::getSym() const {return sym;}

void Cell::getPos(int *a, int *b) {*a=r; *b=c;}

void Cell::addNeighbour(int po, Cell *neighbour) {
	if(!neighbours) neighbours = new Cell *[maxNeighbours];
	neighbours[po]=neighbour;
	numNeighbours++;
}

bool Cell::containsEnemy()
{
	return sym == 'N' || sym == 'T' || sym == 'W' || sym == 'V' || sym == 'M' || sym == 'X'; //TODO: make this function less stupid
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

NonPathableTile::NonPathableTile(int r, int c, string type, string name) : Cell(r, c, type, name){
	neighbours = new Cell *[maxNeighbours];
	for(int i=0; i<maxNeighbours; i++) neighbours[i]=0;
	if(name=="wall1") sym = '|';
	else if(name=="wall2") sym = '-';
	else if(name=="empty") sym = ' ';
	//else if(type=="doorway") sym = '\'; // ASCII code: 92
}

NonPathableTile::~NonPathableTile() {}

void NonPathableTile::notifyDisplay(ViewController &viewCtrl) {
	viewCtrl.notify(r, c, sym);
}

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

RegularTile::RegularTile(int r, int c, int room) :  Cell(r, c, "T", "RegularTile"), room(room) {
	sym = '.';
	avail = true;
	p=0;e=0;
	contain=0;
	neighbours = new Cell *[maxNeighbours];
	for(int j=0; j<maxNeighbours; j++) neighbours[j]=0;
}

RegularTile::~RegularTile() {delete e;}

void RegularTile::notifyDisplay(ViewController &viewCtrl) {
	viewCtrl.notify(r, c, sym);
}

bool RegularTile::available() const {return avail&&!(p||e);}

void RegularTile::setDoorway() {avail = false; sym = '\\'; type = "D";}

char RegularTile::getContain() const {return contain;}

int RegularTile::getRoom() const {return room;}

void RegularTile::pushPlayer(Player *p) {
	this->p = p;
	sym = '@';
	contain = sym;
}

Player *RegularTile::getPlayer() const {return p;}

Player *RegularTile::popPlayer() {
	Player *tmp=p;
	p=0;
	sym = '.';
	contain = ' ';
	return tmp;
}

void RegularTile::pushEnemy(Enemy *e) {
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

Enemy *RegularTile::getEnemy() const {return e;}

Enemy *RegularTile::popEnemy() {
	Enemy *tmp = e;
	e=0;
	sym = '.';
	contain = ' ';
	return tmp;
}

void RegularTile::pushItem(Item *i) {
	this->i = i;
	sym = 'G';
	contain = 'G';
	type = 'T';
}

Item *RegularTile::getItem() const {return i;}

Item *RegularTile::popItem() {
	Item *tmp = i;
	i=0;
	sym = '.';
	contain = ' ';
	return tmp;
}
