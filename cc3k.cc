#include <iostream>
#include <cstdlib>
#include <sstream>
#include "floor.h"	
#include "character.h"
#include "player.h"
#include <stdlib.h>

using namespace std;

int main(int argc,char *argv[])
{
	srand (time(NULL));
	bool endOfGame = false;
	cout << "cc3k!" <<endl;
	while(!endOfGame)
	{
		int floor = 1;
		Floor *f = 0;
		string s;

		cout << "enter h, d, e, or o for human, dwarf, elf, or orc" << endl;

		cin >> s;

		Player::setPlayer(s);

		cout << "game start!" << endl;

		while(floor < 6)
		{
			bool dead = false;
			f = new Floor(floor);
			f->init();
			cout << (*f);
			f->clearAction();
			cout << "Command: "<<endl;

			while(cin >> s)
			{
				string deathwords = "ur ded m8";

				if(s == "q")
				{
					endOfGame = true;
					break;
				}
				if(s == "a")
				{
					cin >> s;
					f->playerAttack(s);
				}
				if(s == "u")
				{
					cin >> s;
					f->usePotion(s);
				}
				else 
				{
					f->tryToMove(s);
				}

				f->enemiesAttack();
				f->endTurn();

				if(f->isOver() == 1) // check end conditions
				{
					cout << deathwords << endl;
					dead = true;
					break;
				}
				if(f->isOver() == 2)
				{
					break;
				}

				cout << (*f);
				f->clearAction();
				cout << "Command: " << endl;
			}

			if(s == "r" || s == "q")
			{
				break;
			}
			else if(dead)
			{
				cout << "Do you want to:\n(r) play again\n(q) or leave" << endl;
				cin >> s;

				while(s != "r" && s != "q")
				{
					cout << "Please choose again." << endl;
					cin >> s;
					if(cin.eof())
					{
						break;
					}
				}
				if(s == "r")
				{
					break;
				}
				else
				{
					endOfGame = true;
					break;
				}
			}

			delete f;
			f = 0;

			if(cin.eof())
			{
				endOfGame = true;
				break;
			}

			floor++;

			if(floor < 6)
			{
				cout << "You have reached Floor " << floor << "." <<endl;
			}

			if(floor == 6)
			{
				cout << "u win m8" << endl;
				cout << "Do you want to restart the game? (y/n)" << endl;
				cin >> s;
				if(s != "y")
				{
					endOfGame = true;
				}
			}
		}

		cout << "\npeace out boys" << endl;
		delete f;
	}
}

