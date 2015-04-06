#ifndef _PASSAGETILE_H_
#define _PASSAGETILE_H_

#include <string>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "viewcontroller.h"

class PassageTile : public Cell {
	Player *p;
	public:
	PassageTile(int r, int c, std::string type, std::string name);
	~PassageTile();
	
	void notifyDisplay(ViewController &viewCtrl);

	void pushPlayer(Player *p);
	Player *getPlayer() const;
	Player *popPlayer();
};

#endif