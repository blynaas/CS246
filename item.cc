#include <string>
#include "item.h"
using namespace std;

Item::Item() {}
Item::Item(string type) : type(type){}
Item::~Item() {}
int Item::getGoldValue(){}
int Item::getPotionHeal(){}
string Item::getType(){return type;}

Treasure::Treasure(int i) : Item("treasure"), value(i) {}
Treasure::~Treasure() {}
int Treasure::getGoldValue() {return value;}

Potion::Potion(int i) : Item("potion"), value(i) {}
Potion::~Potion() {}
int Potion::getPotionHeal() {return value;}