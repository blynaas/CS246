#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include "player.h"
#include "enemy.h"
#include "textdisplay.h"

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
	virtual void notifyDisplay(TextDisplay &t);
	virtual bool available() const;
	virtual void setDoorway();
	virtual char getContain() const;
	virtual void pushPlayer(Player *p);
	virtual Player *getPlayer() const;
	virtual Player *popPlayer();
	virtual void pushEnemy(Enemy *e);
	virtual Enemy *getEnemy() const;
	virtual Enemy *popEnemy();
	virtual ~Cell()=0;
};

class NonPathableTile : public Cell {
	public:
	NonPathableTile(int r, int c, std::string type, std::string name);
	~NonPathableTile();

	void notifyDisplay(TextDisplay &t);
};

class PassageTile : public Cell {
	Player *p;
	public:
	PassageTile(int r, int c, std::string type, std::string name);
	~PassageTile();
	
	void notifyDisplay(TextDisplay &t);

	void pushPlayer(Player *p);
	Player *getPlayer() const;
	Player *popPlayer();
};

class RegularTile : public Cell {
	const int room;
	Player *p;
	Enemy *e;
	bool avail;
	char contain;
	public:
	RegularTile(int r, int c, int room);
	~RegularTile();

	void notifyDisplay(TextDisplay &t);

	bool available() const;
	void setDoorway();
	char getContain() const;
	int getRoom() const;
	void pushPlayer(Player *p);
	Player *getPlayer() const;
	Player *popPlayer();
	void pushEnemy(Enemy *e);
	Enemy *getEnemy() const;
	Enemy *popEnemy();
};

#endif
