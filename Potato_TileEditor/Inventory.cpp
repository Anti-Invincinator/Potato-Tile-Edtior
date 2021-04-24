#include "stdafx.h"
#include "Inventory.h"

//Private Functions
void Inventory::initialize()
{
	this->capacity = 10;
	this->numberOfItems = 0;
	this->itemArray = new Item * [this->capacity];
	
	this->nullify();
}

void Inventory::nullify(const unsigned from)
{
	for (size_t i = from; i < this->capacity; i++)
	{
		this->itemArray[i] = nullptr;
	}
}

void Inventory::freeMemory()
{
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		delete this->itemArray[i];
	}

	delete[] itemArray;
}

//Constructor / Destructor
Inventory::Inventory(unsigned capacity)
{
	this->capacity = capacity;

	this->initialize();
}

Inventory::~Inventory()
{
	this->freeMemory();
}

//Accessors
const unsigned& Inventory::size() const
{
	return this->numberOfItems;
}

const unsigned& Inventory::maxSize() const
{
	return this->capacity;
}

//Functions
void Inventory::Clear()
{
	for (size_t i = 0; i < this->capacity; i++)
	{
		delete this->itemArray[i];
	}

	this->numberOfItems = 0;

	this->nullify();
}

const bool Inventory::isEmpty() const
{
	return this->numberOfItems == 0;
}

const bool Inventory::addItem(Item* item)
{
	if(this->numberOfItems < capacity)
	{
		this->itemArray[this->numberOfItems++] = item->clone();

		return true;
	}

	return false;
}

const bool Inventory::removeItem(const unsigned index)
{
	if (!this->isEmpty())
	{
		if (index < 0 || index >= this->capacity)
			return false;

		delete this->itemArray[index];
		this->itemArray[index] = nullptr;
		this->numberOfItems--;

		return true;
	}

	return false;
}

const bool Inventory::saveToFile(const std::string fileName)
{
	return false;
}

const bool Inventory::loadFromFile(const std::string fileName)
{
	return false;
}
