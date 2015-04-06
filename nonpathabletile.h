#ifndef _NONPATHABLETILE_H_
#define _NONPATHABLETILE_H_

#include <string>
#include "player.h"
#include "enemy.h"
#include "cell.h"
#include "viewcontroller.h"

class NonPathableTile : public Cell
{
public:
	NonPathableTile(int r, int c, std::string type, std::string name);
	~NonPathableTile();

	void notifyDisplay(ViewController &viewCtrl);
};

#endif