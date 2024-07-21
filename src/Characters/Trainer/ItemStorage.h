#pragma once
#include "../../Battle/Item/Item.h"
#include <map>
#include <vector>
#include <iostream>

class ItemStorage
{
public:
	ItemStorage();

	void addItem(ItemID item);
	void removeItem(ItemID item);


	std::map<ItemID, int>* getBattleItems();
	std::map<ItemID, int>* getAllItems();
private:
	std::map<ItemID, int> m_allItems =
	{	{ItemID::SMALL_POTION, 0},
		{ItemID::MEDIUM_POTION, 0},
		{ItemID::LARGE_POTION, 0},
		{ItemID::POKEBALL, 0},
		{ItemID::GREATBALL, 0},
		{ItemID::ULTRABALL, 0},
		{ItemID::MASTERBALL, 0},
		{ItemID::ROID_JUICE, 0}
	};

	std::map<ItemID, int> m_battleItems =
	{	{ItemID::SMALL_POTION, 0},
		{ItemID::MEDIUM_POTION, 0},
		{ItemID::POKEBALL, 0},
		{ItemID::GREATBALL, 0},
		{ItemID::ULTRABALL, 0},
		{ItemID::MASTERBALL, 0}
	};
};