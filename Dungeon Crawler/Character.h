#pragma once

class Character
{
public:
	unsigned int characterID;
	unsigned int curItemIndex = 0;

	Character(unsigned int characterID);
	void drawCharacter();

	void changeItem(unsigned int index);
	void move(unsigned int x,unsigned int y);
	//void replaceItem(index, Item item);
	//void replaceArmor(Armor armor);
private:
	//Item itemArray[3];
	//Armor armor;
};