#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned numberOfItems;
	unsigned capacity;

	//Private Functions
	void initialize();
	void nullify(const unsigned from = 0);
	void freeMemory();

public:
	//Constructor / Destructor
	Inventory(unsigned capacity);
	virtual ~Inventory();

	//Accessors
	const unsigned& size() const;
	const unsigned& maxSize() const;

	//Modifiers


	//Functions
	void Clear();
	const bool isEmpty() const;

	const bool addItem(Item* item);
	const bool removeItem(const unsigned index);

	const bool saveToFile(const std::string fileName);
	const bool loadFromFile(const std::string fileName);
};

#endif // !INVENTORY_H



