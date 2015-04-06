#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "viewcontroller.h"

const int maxNeighbours = 8;

class Cell {
	protected:	
	std::string type; // wall1("|"), wall2("-"), PassageTile1("+"), PassageTile2("#"), doorway("\"), RegularTile(".")
	const std::string name;
	char sym;
	int numNeighbours;
	Cell **neighbours;
	int r, c;
	Cell(int r, int c, std::string type, std::string name);
	
	public:
	std::string getType() const;
	char getSym() const;
	void getPos(int *a, int *b);
	void addNeighbour(int po, Cell *neighbour);
	bool containsEnemy();
	Cell **getNeighbours() const;
	
	virtual int getRoom() const;
	virtual void notifyDisplay(ViewController &viewCtrl);
	virtual bool available() const;
	virtual void setDoorway();
	virtual char getContain() const;
	virtual void pushPlayer(Player *p);
	virtual Player *getPlayer() const;
	virtual Player *popPlayer();
	virtual void pushEnemy(Enemy *e);
	virtual Enemy *getEnemy() const;
	virtual Enemy *popEnemy();
	virtual void pushItem(Item *i);
	virtual Item *getItem() const;
	virtual Item *popItem();
	virtual ~Cell()=0;
};

#endif
