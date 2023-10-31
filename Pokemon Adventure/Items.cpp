#include "Items.h"
#include <iostream>

Item::Item(std::string name, unsigned int price, float pokeballBonus, unsigned int typeBonus, unsigned int id)
{
	m_name = name;
	m_id = id;
	m_price = price;
	m_pokeball = true;
	m_pokeballBonus = pokeballBonus;
}

Item::Item(std::string name, unsigned int price, bool revive, int healAmount, Status* status, unsigned int id)
{
	m_name = name;
	m_id = id;
	m_price = price;
	m_revive = revive;
	m_healAmount = healAmount;
	m_status = status;
}

Item::Item(){
}

std::string Item::getName()
{
	return m_name;
}

bool Item::isPokeball()
{
	return m_pokeball;
}

bool Item::isHeal()
{
	if (m_revive || m_healAmount > 0 || m_status != nullptr)
		return true;

	return false;
}
