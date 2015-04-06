#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	Item();
	virtual ~Item();
	virtual int getGoldValue() = 0;
};

class Treasure : public Item {
	int value;
	public:
	Treasure(int i);
	~Treasure();
	int getGoldValue();
};

#endif
