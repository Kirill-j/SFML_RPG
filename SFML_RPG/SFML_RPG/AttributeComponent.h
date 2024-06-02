#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent
{
public:
	// Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	// Attributes
	int vitality;
	int strenght;
	int dexterity;
	int agility;
	int intelligence;

	// Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	// Cons / Dest
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	// Functions
	std::string debugPrint() const;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

#endif