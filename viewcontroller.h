#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <iostream>
#include <sstream>
#include <string>

#include "player.h"

const int MAXR=25;
const int MAXC=79;
extern int roomCount;

class ViewController
{
	char theDisplay[MAXR][MAXC]; //save the display version of a floor
	std::string action; //save the information that will be shown after "action:"
	Player *p; //an pointer to player to gain information
	int f; //shows which floor this is

	public:
	ViewController(int f); //ctor
	void notify(int r, int c, char ch); //cells will call this to let the display know which char it should display
	void addAction(std::string ac); //methods in Floor will call this to let the display know what action to show
	void clearActions();
	~ViewController();
	
	friend std::ostream &operator<<(std::ostream &out, const ViewController &td);
};

#endif
