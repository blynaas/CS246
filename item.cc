#include <string>
#include "item.h"
using namespace std;

Item::Item() {}
Item::~Item() {}

Treasure::Treasure(int i) : value(i) {}
Treasure::~Treasure() {}
int Treasure::getGoldValue() {return value;}