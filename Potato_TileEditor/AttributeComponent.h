#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent
{
public:
	//Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;


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

	void loseHP(const int hp);
	void loseEXP(const int exp);
	void gainHP(const int hp);
	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();

	void Update();
};

#endif // !ATTRIBUTECOMPONENT_H