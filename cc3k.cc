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
	bool gameOver = false;
	cout << "Welcome to the world of cc3k!" <<endl;
	while(!gameOver)
	{
		int floor = 1;
		Floor *f = 0;
		string s;

		cout << "Choose your race! Enter h, d, e, or o for human, dwarf, elf, or orc." << endl;

		cin >> s;

		Player::setPlayer(s);

		cout << "Game start!" << endl;

		while(floor < 6)
		{
			bool dead = false;
			f = new Floor(floor);
			f->init();
			cout << (*f);
			f->clearActions();
			cout << "Command: "<<endl;

			while(cin >> s)
			{
				if(s == "q")
				{
					gameOver = true;
					break;
				}
				else if(s == "a")
				{
					cin >> s;
					f->playerAttack(s);
				}
				else if(s == "u")
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
					cout << "You died... scrub." << endl;
					dead = true;
					break;
				}
				else if(f->isOver() == 2)
				{
					break;
				}

				cout << (*f);
				f->clearActions();
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
					gameOver = true;
					break;
				}
			}

			delete f;
			f = 0;

			if(cin.eof())
			{
				gameOver = true;
				break;
			}

			floor++;

			if(floor < 6)
			{
				cout << "You have reached Floor " << floor << "." <<endl;
			}

			if(floor == 6)
			{
				cout << "You've won! Congratulations!" << endl;
				cout << "Do you want to restart the game? (y/n)" << endl;
				cin >> s;
				if(s != "y")
				{
					gameOver = true;
				}
			}
		}

		cout << "\n(c) Jordan Verasamy and Yaro Gorban 2015" << endl;
		delete f;
	}
}

