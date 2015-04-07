#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include "floor.h"	
#include "character.h"
#include "player.h"
#include <stdlib.h>

using namespace std;

void floodNeighbours(vector< vector<char> >  &theMap, int r, int c, char value)
{
	if (theMap[r][c] != '.')
	{
		return;
	}
	else
	{
		theMap[r][c] = value;
	}

	if(r>0)
	{
		floodNeighbours(theMap, r-1, c, value);
		if(c>0)
		{
			floodNeighbours(theMap, r-1, c-1, value);
		}
		if(c<MAXC-1)
		{
			floodNeighbours(theMap, r-1, c+1, value);
		}
	}
	if(c>0)
	{
		floodNeighbours(theMap, r, c-1, value);
	}
	if(c<MAXC-1)
	{
		floodNeighbours(theMap, r, c+1, value);
	}
	if(r<MAXR-1)
	{
		floodNeighbours(theMap, r+1, c, value);
		if(c>0)
		{
			floodNeighbours(theMap, r+1, c-1, value);
		}
		if(c<MAXC-1)
		{
			floodNeighbours(theMap, r+1, c+1, value);
		}
	}
}

void generateMapFile(string fileName)
{
	ifstream in(fileName.c_str());

	vector< vector<char> > theMap(MAXR);

	for (int r = 0; r < MAXR; r++)
	{
		theMap[r].resize(MAXC);
	}

	for (int r = 0; r < MAXR; r++)
	{
		for (int c = 0; c < MAXC; c++) // C++ WOW SO META
		{
			char ch;
			do
			{
				in.get(ch);
			} while (ch == '\n');

			theMap[r][c] = (ch == ' ') ? 'E' : ch;

			if (theMap[r][c] >= '0' && theMap[r][c] <= '9')
			{
				theMap[r][c] = '.';
			}
			if (theMap[r][c] == '@')
			{
				theMap[r][c] = '.';
			}
			if (theMap[r][c] == '\\')
			{
				theMap[r][c] = '.';
			}
		}
	}

	bool done = false;
	bool totallyDone = false;
	
	char count = '0';

	while (!totallyDone)
	{
		totallyDone = true;
		done = false;
		for (int r = 0; r < MAXR; r++)
		{
			for (int c = 0; c < MAXC; c++)
			{
				if (theMap[r][c] == '.')
				{
					totallyDone = false;
					floodNeighbours(theMap, r, c, count);
					done = true;
				}
				if (done) break;
			}
			if (done) break;
		}
		count++;
	}

	ofstream fout("mapWithChamberIDs.in");

	for (int r = 0; r < MAXR; r++)
	{
		for (int c = 0; c < MAXC; c++)
		{
			fout << theMap[r][c];
		}
		fout << endl;
	}
}


int main(int argc,char *argv[])
{
	string mapFile = "defaultMap.in";

	if (argc >= 2){
		mapFile = argv[1];
		cout << "You chose to load the non-default map called " << mapFile << endl;
	}

	generateMapFile(mapFile);

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
			f->init(mapFile);
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

