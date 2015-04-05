#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "textdisplay.h"

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
	return sym == 'N';
}

Cell **Cell::getNeighbours() const {return neighbours;}

int Cell::getRoom() const {}
void Cell::notifyDisplay(TextDisplay &t) {}
bool Cell::available() const {}
void Cell::setDoorway() {}
char Cell::getContain() const {}
void Cell::pushPlayer(Player *p) {}
Player *Cell::getPlayer() const {}
Player *Cell::popPlayer() {}
void Cell::pushEnemy(Enemy *e) {}
Enemy *Cell::getEnemy() const {}
Enemy *Cell::popEnemy() {}

Cell::~Cell() {delete [] neighbours;}

ECell::ECell(int r, int c, string type, string name) : Cell(r, c, type, name){
	neighbours = new Cell *[maxNeighbours];
	for(int i=0; i<maxNeighbours; i++) neighbours[i]=0;
	if(name=="wall1") sym = '|';
	else if(name=="wall2") sym = '-';
	else if(name=="empty") sym = ' ';
	//else if(type=="doorway") sym = '\'; // ASCII code: 92
}

ECell::~ECell() {}

void ECell::notifyDisplay(TextDisplay &t) {
	t.notify(r, c, sym);
}

Passenger::Passenger(int r, int c, string type, string name) : Cell(r, c, type, name){
	neighbours = new Cell *[maxNeighbours];
	for(int i=0; i<maxNeighbours; i++) neighbours[i]=0;
	if(name=="pass1") sym = '+';
	else if(name=="pass2") sym = '#';
}

Passenger::~Passenger() {}

void Passenger::notifyDisplay(TextDisplay &t) {
	t.notify(r, c, sym);
}

void Passenger::pushPlayer(Player *p) {
	this->p = p;
	sym = '@';
}

Player *Passenger::getPlayer() const {
	return p;
}

Player *Passenger::popPlayer() {
	Player *tmp = p;
	p = 0;
	if(name=="pass1") sym = '+';
	else if(name=="pass2") sym = '#';
	return tmp;
}

Tile::Tile(int r, int c, int room) :  Cell(r, c, "T", "tile"), room(room) {
	sym = '.';
	avail = true;
	p=0;e=0;
	contain=0;
	neighbours = new Cell *[maxNeighbours];
	for(int j=0; j<maxNeighbours; j++) neighbours[j]=0;
}

Tile::~Tile() {delete e;}

void Tile::notifyDisplay(TextDisplay &t) {
	t.notify(r, c, sym);
}

bool Tile::available() const {return avail&&!(p||e);}

void Tile::setDoorway() {avail = false; sym = '\\'; type = "D";}

char Tile::getContain() const {return contain;}

int Tile::getRoom() const {return room;}

void Tile::pushPlayer(Player *p) {
	this->p = p;
	sym = '@';
	contain = sym;
}

Player *Tile::getPlayer() const {return p;}

Player *Tile::popPlayer() {
	Player *tmp=p;
	p=0;
	sym = '.';
	contain = ' ';
	return tmp;
}

void Tile::pushEnemy(Enemy *e) {
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

Enemy *Tile::getEnemy() const {return e;}

Enemy *Tile::popEnemy() {
	Enemy *tmp = e;
	e=0;
	sym = '.';
	contain = ' ';
	return tmp;
}
