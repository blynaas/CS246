#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include "player.h"
#include "cell.h"
#include "nonpathabletile.h"
#include "passagetile.h"
#include "regulartile.h"
#include "viewcontroller.h"

class Floor {
  
	Cell *theFloor[MAXR][MAXC];
	ViewController *viewCtrl;
	int over; //0: not over, 1: player dead, 2: next floor, 3: win
	int pr, pc; // player's location

	void clearFloor();

public:
	Floor(int f);
	~Floor();

	void clearAction();

	void movePlayer(Cell *s, Cell *e);
	Cell* moveEnemy(Cell *e);
	void moveEnemies();
	int tryToMove(std::string d);
	void endTurn();

	int playerAttack(std::string d);
	void enemiesAttack();

	Cell* getTargetCell(std::string d);

	void usePotion(std::string d);

	int isOver() const;
	void init();

	void linkCells();
	void generateCell(int r, int c, char ch);

	Cell* getRandomEmptyCell(int* row, int* col);
	Cell* getRandomEmptyCell();
	
	friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};

#endif
