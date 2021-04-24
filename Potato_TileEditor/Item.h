#ifndef ITEM_H
#define ITEM_H

enum ItemTypes {DEFAULT_ITEM = 0, RANGEDWEAPON, MELEEWEAPON};
enum ItemRarities {COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC};

class Item
{
private:
	void initVariables();

protected:
	//Variables
	short unsigned type;
	unsigned value;

public :
	//Constructor / Destructor
	Item(unsigned value);
	virtual ~Item();

	//Function
	virtual Item* clone() = 0;
};

#endif // !ITEM_H



