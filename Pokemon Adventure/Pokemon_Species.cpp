#include "Pokemon_Species.h"

Pokemon_Species::Pokemon_Species(std::string name, unsigned int id, std::unordered_map<int, Pokemon_Species> evolution, std::unordered_map<int, Attack> moveList, unsigned int type1, unsigned int type2, unsigned int xp_Yield, unsigned int baseHealth, unsigned int baseAttack, unsigned int baseDefense, unsigned int baseSpeed, unsigned int catchRate)
{
	m_name = name;
	m_id = id;
	m_evolution = evolution;
	m_moveList = moveList;
	m_type1 = type1;
	m_type2 = type2;
	m_xp_Yield = xp_Yield;
	m_catchRate = catchRate;

	m_baseHealth = baseHealth;
	m_baseAttack = baseAttack;
	m_baseDefense = baseDefense;
	m_baseSpeed = baseSpeed;
}

Pokemon_Species::Pokemon_Species(){}

std::string Pokemon_Species::getName()
{
	return m_name;
}

std::unordered_map<int, Pokemon_Species> Pokemon_Species::getEvolution()
{
	return m_evolution;
}

std::unordered_map<int, Attack> Pokemon_Species::getMovelist()
{
	return m_moveList;
}

unsigned int Pokemon_Species::getXPYield()
{
	return m_xp_Yield;
}

unsigned int Pokemon_Species::getCatchRate()
{
	return m_catchRate;
}

unsigned int Pokemon_Species::getBaseHealth()
{
	return m_baseHealth;
}

unsigned int Pokemon_Species::getBaseAttack()
{
	return m_baseAttack;
}

unsigned int Pokemon_Species::getBaseDefense()
{
	return m_baseDefense;
}

unsigned int Pokemon_Species::getBaseSpeed()
{
	return m_baseSpeed;
}

unsigned int Pokemon_Species::getType1()
{
	return m_type1;
}

unsigned int Pokemon_Species::getType2()
{
	return m_type2;
}
