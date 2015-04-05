/* 
 * this will have a full 79*30 map
 * wall
 */

#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include "player.h"
#include "cell.h"
#include "textdisplay.h"

//const int MAXR = 25;
//const int MAXC = 79;
//const int MAXMonster = 20;

class Floor {
  
	Cell *theFloor[MAXR][MAXC];
	int moved[20][2];
	TextDisplay *td;
	int over; //0:not over, 1:player passed away, 2:next floor, 3:win
	int pr, pc; //locate the position of player

	void clearFloor();   // Frees the floor.

	public:
	Floor(int f);
	~Floor();

	void clearAction();
	void havePotion(char d1, char d2);
	void storePotion(char d1, char d2);
	void havePotion(std::string d);
	void storePotion(std::string d);
	void usePotion(int i); //use potion in the bag
	void obtainGold(Cell *p, Cell *g);
	void movePlayer(Cell *s, Cell *e);
	int playerAttack(std::string d);
	Cell* getTargetCell(std::string d);
	int isOver() const;
	void init();
	void init(int r, int c);
	void crea(int r, int c, char ch);
	int pmove(char d1, char d2); // 1 means success, 0 means fail
	Cell* emove(Cell *e); //enemy move
	int attack(char d1, char d2);
	int move(std::string d); // 1 means success, 0 means fail
	void endTurn();
	void moveEnemies();
	void print();

	
	friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};
#endif
