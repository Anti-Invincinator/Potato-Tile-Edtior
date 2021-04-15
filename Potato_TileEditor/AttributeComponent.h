#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent
{
public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;


	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hitpoints;
	int hitpointsMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defense;
	int luck;

	//Constructor / Destructor
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void gainExp(const unsigned exp);

	void updateStats(const bool reset);
	void updateLevel();

	void Update();
};

#endif // !ATTRIBUTECOMPONENT_H


