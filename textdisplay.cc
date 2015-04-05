#include <iostream>
#include <sstream>
#include "textdisplay.h"
#include "player.h"
using namespace std;

TextDisplay::TextDisplay(int f, bool canStorePotion) : p(Player::getPlayer()), f(f),
 canStorePotion(canStorePotion){
	action = "Player character has spawned.";
	for(int i=0; i<MAXR; i++) {
		for(int j=0; j<MAXC; j++) theDisplay[i][j]=' ';
	}
}

void TextDisplay::notify(int r, int c, char ch) {
	theDisplay[r][c] = ch;
}

void TextDisplay::setAction(string ac) {action+=ac;}

void TextDisplay::clearAction() {action="";}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for(int i=0; i<MAXR; i++) {
		for(int j=0; j<MAXC; j++) out<<td.theDisplay[i][j];
		out<<"\n";
	}
	out<<"Race: "<<td.p->getRace()<<" "<<"Gold: "<<
	td.p->getGold()<<"                        "<<
	"                      "<<"floor "<<td.f<<"\n";
	if(td.p->getHp()>=0) out<<"HP: "<<td.p->getHp()<<"\n";
	else out<<"HP: "<<0<<"\n";
	out<<"Atk: "<<td.p->getAtk()<<"\n";
	out<<"Def: "<<td.p->getDef()<<"\n";
	out<<"Action: "<<td.action<<"\n";
	
	return out;
}
