#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
protected:
	std::string type;
public:
	Item();
	Item(std::string type);
	virtual ~Item();
	std::string getType();
	virtual int getGoldValue();
	virtual int getPotionHeal();
};

class Treasure : public Item
{
	int value;
	public:
	Treasure(int i);
	~Treasure();
	int getGoldValue();
};

class Potion : public Item
{
	int value;
	public:
	Potion(int i);
	~Potion();
	int getPotionHeal();
};

#endif
