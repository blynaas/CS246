#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "floor.h"
#include "viewcontroller.h"
#include "item.h"
#include <math.h>


using namespace std;

Floor::Floor(int f) : over(0), pr(0), pc(0)
{
	viewCtrl = new ViewController(f, false);

	for(int i = 0; i < MAXR; i++)
	{
		for(int j = 0; j < MAXC; j++)
		{
			theFloor[i][j]=0;
		}
	}
}

Floor::~Floor()
{
	delete viewCtrl;

	for(int i = 0; i < MAXR; i++)
	{
		for(int j = 0; j < MAXC; j++)
		{
			delete theFloor[i][j];
		}
	}
}

int Floor::isOver() const
{
	return over;
}

void Floor::init()
{
	string fname = "map.in";
	ifstream in(fname.c_str());
	int numEnemies = 20;
	int numTreasure = 10;
	int numPotions = 10;
	int tnum=0;
	int roomnum[NUMROOM];
	for(int i=0; i<NUMROOM; i++) roomnum[i]=0;
	int tmpnum=0;
	char dec;

	for(int i = 0; i < MAXR; i++)
	{
		for(int j = 0; j < MAXC; j++)
		{
			in >> dec;
			if(dec >= '0' && dec < '5')
			{
				tnum++;
				roomnum[dec-'0']++;
			}
			generateCell(i, j, dec);
		}
	}

	linkCells();

	//player
	int row, col;

	Cell* playerCell = getRandomEmptyCell(&row, &col);
	playerCell->pushPlayer(Player::getPlayer());
	pr = row;
	pc = col;

	//doorway
	while(true)
	{
		Cell* doorCell = getRandomEmptyCell();

		if (doorCell->getRoom() != playerCell->getRoom())
		{
			doorCell->setDoorway();
			break;
		}
	}

	//potions
	for (int i = 0; i < numPotions; i++)
	{
		getRandomEmptyCell()->pushItem(new Potion(10));
	}

	//treasure
	for (int i = 0; i < numTreasure; i++)
	{
		int rnd = rand()%8;

		if (rnd <= 4)
		{
			getRandomEmptyCell()->pushItem(new Treasure(1));
		}
		else if (rnd <= 6)
		{
			getRandomEmptyCell()->pushItem(new Treasure(2));
		}
		else if (rnd == 7)
		{
			// dragon hoard
		}
	}

	//enemies
	for (int i = 0; i < numEnemies; i++)
	{
		int rnd = rand()%18;

		if (rnd <= 3)
		{
			getRandomEmptyCell()->pushEnemy(new Werewolf());
		}
		else if (rnd <= 6)
		{
			getRandomEmptyCell()->pushEnemy(new Vampire());
		}
		else if (rnd <= 11)
		{
			getRandomEmptyCell()->pushEnemy(new Goblin());
		}
		else if (rnd <= 13)
		{
			getRandomEmptyCell()->pushEnemy(new Troll());
		}
		else if (rnd <= 15)
		{
			getRandomEmptyCell()->pushEnemy(new Phoenix());
		}
		else if (rnd <= 17)
		{
			getRandomEmptyCell()->pushEnemy(new Merchant());
		}
	}

	//notify the display
	for(int i = 0; i < MAXR; i++)
	{
		for(int j = 0; j < MAXC; j++)
		{
			theFloor[i][j]->notifyDisplay(*viewCtrl);
		}
	}
}

Cell* Floor::getRandomEmptyCell(int* row, int* col)
{
	int room = rand()%NUMROOM;

	while(true)
	{
		*row = rand()%MAXR;
		*col = rand()%MAXC;
		Cell* temp = theFloor[*row][*col];

		if (temp->getSym() == '.' && temp->getRoom() == room)
		{
			return temp;
		}
	}
}

Cell* Floor::getRandomEmptyCell()
{
	int room = rand()%NUMROOM;

	while(true)
	{
		int row = rand()%MAXR;
		int col = rand()%MAXC;
		Cell* temp = theFloor[row][col];

		if (temp->getSym() == '.' && temp->getRoom() == room)
		{
			return temp;
		}
	}
}

int Floor::tryToMove(string d)
{
	Cell* ctmp = getTargetCell(d);

	int ret = 0;

	cout << ctmp->getType() << endl;

	if(!ctmp)
	{
		viewCtrl->setAction("Invalid command! ");
	}
	else if(ctmp->getType()=="E")
	{
		viewCtrl->setAction("Cannot go there! ");
	}
	else if(ctmp->getType()=="D")
	{
		over=2;
		viewCtrl->setAction("Whoa, a doorway.");
		ret = 1;
	}
	else if (ctmp->getType() == "P" || ctmp->getContain() == 'G' || (ctmp->getType() == "T" && ctmp->available()))
	{
		stringstream ss;
		ss << "";
		if (ctmp->getContain() == 'G')
		{
			int value = ctmp->getItem()->getGoldValue();
			value = Player::getPlayer()->addGold(value);
			ss << "PC obtained " << value << " gold!";
		}

		movePlayer(theFloor[pr][pc], ctmp);
		viewCtrl->setAction("PC moved to the " + d + ".");
		viewCtrl->setAction(ss.str());
		ret = 1;
	}
	else
	{
		viewCtrl->setAction("Target is occupied.");
	}

	return ret;
}

void Floor::usePotion(string d)
{
	Cell* ctmp = getTargetCell(d);

	if(!ctmp)
	{
		viewCtrl->setAction("Invalid command!");
	}
	else if (ctmp->getType() == "potion")
	{
		int healAmount = ctmp->getItem()->getPotionHeal();
		Player::getPlayer()->addHp(healAmount);
		ctmp->popItem();

		stringstream ss;
		ss << "Used a potion to the " << d << ", healed by " << healAmount << ".";
		viewCtrl->setAction(ss.str());
	}
	else
	{
		viewCtrl->setAction("That ain't no potion!");
	}
}

void Floor::enemiesAttack()
{
	
	Cell** neighbours = theFloor[pr][pc]->getNeighbours();

	for (int i = 0; i < 8; i++)
	{
		Cell* tempCell = neighbours[i];
		if (tempCell->containsEnemy())
		{
			int damage = tempCell->getEnemy()->attack(Player::getPlayer());

			stringstream ss;

			if (damage == -1) // enemy missed
			{
				ss << tempCell->getSym() << " tried to attack, but missed.";
			}
			else // enemy didn't miss
			{
				ss << "Took " << damage << " damage from " << tempCell->getSym() << ".";
			}

			viewCtrl->setAction(ss.str());

			tempCell->getEnemy()->setMoved(true);
		}
	}
}

void Floor::endTurn()
{
	moveEnemies();

	if (Player::getPlayer()->getHp() <= 0)
	{
		over = true;
	}

	for(int i=0; i<MAXR; i++)
	{
		for(int j=0; j<MAXC; j++)
		{
			theFloor[i][j]->notifyDisplay(*viewCtrl);
		}
	}
}

void Floor::moveEnemies()
{
	for(int i=0; i<MAXR; i++)
	{
		for(int j=0; j<MAXC; j++)
		{
			Cell *ctmp = theFloor[i][j];
			if (ctmp->containsEnemy() && !ctmp->getEnemy()->getMoved())
			{
				int tempr, tempc;
				ctmp->getPos(&tempr, &tempc);
				moveEnemy(ctmp)->getEnemy()->setMoved(true);
			}
		}
	}

	for(int i=0; i<MAXR; i++)
	{
		for(int j=0; j<MAXC; j++)
		{
			Cell *ctmp = theFloor[i][j];
			if (ctmp->containsEnemy())
			{
				ctmp->getEnemy()->setMoved(false);
			}
		}
	}

}

void Floor::clearAction()
{
	viewCtrl->clearAction();
}

void Floor::movePlayer(Cell *s, Cell *e)
{
	Cell **tmp = s->getNeighbours();

	e->pushPlayer(s->popPlayer());
	int m, n;
	e->getPos(&m, &n);
	pr=m;
	pc=n;
	tmp = e->getNeighbours();
}


int Floor::playerAttack(string d)
{
	Cell* ctmp = getTargetCell(d);
	int ret = 0;

	if(!ctmp)
	{
		viewCtrl->setAction("Invalid command! ");
	}
	else if(ctmp->containsEnemy())
	{
		int damage = Player::getPlayer()->attack(ctmp->getEnemy());

		stringstream ss;
		ss << "Hit a(n) " << ctmp->getSym() << " to the " << d << " for " << damage << " (" << ctmp->getEnemy()->getHp() << " health).";
		viewCtrl->setAction(ss.str());

		if (ctmp->getEnemy()->getHp() == 0)
		{
			Enemy* e = ctmp->popEnemy();
			Player::getPlayer()->addGold(e->getGold());
			delete e;
		}

		ret = 1;
	}
	else
	{
		viewCtrl->setAction("Nothing there to attack!");
	}

	return ret;
}

Cell* Floor::getTargetCell(string d)
{
	Cell **tmp = theFloor[pr][pc]->getNeighbours();
	Cell *ctmp = 0;

	if(d=="nw")
	{
		ctmp=tmp[0];
	}
	else if(d=="no")
	{
		ctmp=tmp[1];
	}
	else if(d=="ne")
	{
		ctmp=tmp[2];
	}
	else if(d=="we")
	{
		ctmp=tmp[3];
	}
	else if(d=="ea")
	{
		ctmp=tmp[4];
	}
	else if(d=="sw")
	{
		ctmp=tmp[5];
	}
	else if(d=="so")
	{
		ctmp=tmp[6];
	}
	else if(d=="se")
	{
		ctmp=tmp[7];
	}

	return ctmp;
}


void Floor::linkCells()
{
	for(int r=0; r<MAXR; r++)
	{
		for(int c=0; c<MAXC; c++)
		{
			if(r>0) {
				if(c>0) theFloor[r][c]->addNeighbour(0, theFloor[r-1][c-1]);
				theFloor[r][c]->addNeighbour(1, theFloor[r-1][c]);
				if(c<MAXC-1) theFloor[r][c]->addNeighbour(2, theFloor[r-1][c+1]);
			}
			if(c>0) {theFloor[r][c]->addNeighbour(3, theFloor[r][c-1]);}
			if(c<MAXC-1) {theFloor[r][c]->addNeighbour(4, theFloor[r][c+1]);}
			if(r<MAXR-1) {
				if(c>0) theFloor[r][c]->addNeighbour(5, theFloor[r+1][c-1]);
				theFloor[r][c]->addNeighbour(6, theFloor[r+1][c]);
				if(c<MAXC-1) theFloor[r][c]->addNeighbour(7, theFloor[r+1][c+1]);
			}
		}
	}
}

void Floor::generateCell(int r, int c, char ch)
{
	if(ch=='|') theFloor[r][c] = new NonPathableTile(r, c, "E", "wall1");
	else if(ch=='-') theFloor[r][c] = new NonPathableTile(r, c, "E", "wall2");
	else if(ch=='E') theFloor[r][c] = new NonPathableTile(r, c, "E", "empty");
	else if(ch=='+') theFloor[r][c] = new PassageTile(r, c, "P", "pass1");
	else if(ch=='#') theFloor[r][c] = new PassageTile(r, c, "P", "pass2");
	else if(ch=='0') theFloor[r][c] = new RegularTile(r,c,0);
	else if(ch=='1') theFloor[r][c] = new RegularTile(r,c,1);
	else if(ch=='2') theFloor[r][c] = new RegularTile(r,c,2);
	else if(ch=='3') theFloor[r][c] = new RegularTile(r,c,3);
	else if(ch=='4') theFloor[r][c] = new RegularTile(r,c,4);
}

Cell* Floor::moveEnemy(Cell *e)
{
	int m,n;
	e->getPos(&m, &n);

	Cell **tmp = e->getNeighbours();

	bool canmove=false;

	for(int i=0; i<8; i++)
	{
		if(tmp[i]->getSym()=='.')
		{
			canmove=true; break;
		}
	}

	if (!canmove)
	{
		return e;
	}

	int rnd = rand()%8;

	while(!tmp[rnd] || (tmp[rnd]->getSym()!='.'))
	{
		rnd = rand()%8;
	}

	tmp[rnd]->pushEnemy(e->popEnemy());

	return tmp[rnd];
}

ostream &operator<<(ostream &out, const Floor &f)
{
	out << (*f.viewCtrl);
	return out;
}
