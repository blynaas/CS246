#ifndef _REGULARTILE_H_
#define _REGULARTILE_H_

#include <string>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "viewcontroller.h"

class RegularTile : public Cell
{
	const int room;
	Player *p;
	Enemy *e;
	Item *i;
	bool avail;
	char contain;
	public:
	RegularTile(int r, int c, int room);
	~RegularTile();

	void notifyDisplay(ViewController &viewCtrl);

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
	void pushItem(Item *i);
	Item *getItem() const;
	Item *popItem();
};

#endif