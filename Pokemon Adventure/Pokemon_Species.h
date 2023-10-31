#pragma once

#include "Attack.h"
#include "Items.h"
#include <unordered_map>

class Pokemon_Species
{
public:
	Pokemon_Species(std::string name, unsigned int id, std::unordered_map<int, Pokemon_Species> evolution, std::unordered_map<int, Attack> moveList, unsigned int type1, unsigned int type2, unsigned int xp_Yield, unsigned int baseHealth, unsigned int baseAttack, unsigned int baseDefense, unsigned int baseSpeed, unsigned int catchRate);
	Pokemon_Species();

	std::string getName();
	std::unordered_map<int, Pokemon_Species> getEvolution();
	std::unordered_map<int, Attack> getMovelist();

	unsigned int getID() { return m_id; }
	unsigned int getXPYield();
	unsigned int getCatchRate();
	unsigned int getBaseHealth();
	unsigned int getBaseAttack();
	unsigned int getBaseDefense();
	unsigned int getBaseSpeed();
	unsigned int getType1();
	unsigned int getType2();


private:

	std::string m_name;
	std::unordered_map<int, Pokemon_Species> m_evolution;
	std::unordered_map<int, Attack> m_moveList;

	unsigned int m_id = 0;

	unsigned int m_type1 = NOTYPE;
	unsigned int m_type2 = NOTYPE;
	unsigned int m_xp_Yield = 0;
	unsigned int m_catchRate = 0;

	unsigned int m_baseHealth = 0;
	unsigned int m_baseAttack = 0;
	unsigned int m_baseDefense = 0;
	unsigned int m_baseSpeed = 0;
};