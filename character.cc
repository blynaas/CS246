#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "character.h"
using namespace std;

Character::Character(int hp, int atk, int def) : hp(hp), atk(atk), def(def), gold(0) {}

double Character::getGold() const {return gold;}

int Character::getHp() const {return hp;}

Character::~Character() {}
