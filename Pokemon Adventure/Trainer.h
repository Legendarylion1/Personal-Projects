#pragma once

#include "Pokemon.h"

static enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Trainer
{
public:
	Trainer(std::string name);

	bool addedPokemon(Pokemon newPokemon);
	void insertPokemon(Pokemon newPokemon, unsigned int index);
	Pokemon* getPokemon(int index);
	Pokemon popPokemon(int index);
	void setRoster(Pokemon newRoster[6]);
	void swapPokemon(unsigned int index1, unsigned int index2);
	bool hasPokemon();
	bool hasWhiteOut();

	std::string getName();

	unsigned int getMoneyBalance();
	void giveMoney(int amount);
	void takeMoney(int amount);

	unsigned int getUniquePokeballCount();
	unsigned int getUniqueHealCount();
	unsigned int getUniqueMiscCount();

	unsigned int getPokeballTypeCount(unsigned int index);
	unsigned int getHealTypeCount(unsigned int index);
	unsigned int getMiscTypeCount(unsigned int index);

	unsigned int getTotalHealCount();

	Item* getPokeball(unsigned int index);
	Item* getHealItem(unsigned int index);
	Item* getMiscItem(unsigned int index);

	void addItem(Item& item);
	void removeItem(Item& item);

	void printPokemon();
	void printItems();
private:
	std::string m_name;

	unsigned int m_money = 0;

	Pokemon m_roster[6];

	std::unordered_map<Item*, unsigned int> m_pokeballStorage;
	std::unordered_map<Item*, unsigned int> m_healItemStorage;
	std::unordered_map<Item*, unsigned int> m_miscItems;
};