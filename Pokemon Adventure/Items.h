#pragma once

#include "Status.h"
#include "TypeChart.h"

class Item
{
public:
	explicit Item(std::string name, unsigned int price, float pokeballBonus, unsigned int typeBonus, unsigned int id);
	explicit Item(std::string name, unsigned int price, bool revive, int healAmount, Status* status, unsigned int id);
	Item();

	std::string getName();
	unsigned int getPrice() { return m_price; }
	unsigned int getID() { return m_id; }
	float getPokeballBonus() { return m_pokeballBonus; }

	bool isPokeball();
	bool isHeal();
	bool isRevive() { return m_revive; }

	int getHealAmount() { return m_healAmount; }
	Status& getStatus() { return *m_status; }
private:
	std::string m_name = "";
	unsigned int m_id = 0;
	unsigned int m_price = 0;

	bool m_pokeball = false;
	bool m_revive = false;

	float m_pokeballBonus = 0.0f;
	unsigned int typeBonus = NOTYPE;
	int m_healAmount = 0;

	Status* m_status = nullptr;
};



class Pokeball : public Item
{
public:
	explicit Pokeball(std::string name, unsigned int price, float pokeballBonus, unsigned int typeBonus, unsigned int id) : Item(name, price, pokeballBonus, typeBonus, id) {};
};

class Potion : public Item
{
public:
	explicit Potion(std::string name, unsigned int price, bool revive, int healAmount, Status* status, unsigned int id) : Item(name, price, revive, healAmount, status, id) {};
};