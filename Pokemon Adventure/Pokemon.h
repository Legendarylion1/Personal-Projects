#pragma once

#include <iostream>

#include "Pokemon_Species.h"
#include "Items.h"
#include "StatusChart.h"
#include "ItemChart.h"
#include "AttackChart.h"

class Pokemon
{

public:
	Pokemon(Pokemon_Species species, int level, Attack attacks[4]);
	Pokemon(Pokemon_Species species, int level);
	Pokemon();

	explicit operator bool() const { return m_level > 0; };

	void recieveAttack(Pokemon& attacker, Attack &attack);
	void gainXP(int xp);
	bool hasFainted();
	int determineAttack(Pokemon& opposingPokemon);
	bool usedItem(std::string trainerName, Item& item);
	void giveHP(int hp);
	bool takeDamage(int damage);
	void teachAttack(Attack newAttack);
	void randomizeAttacks();

	std::string getName();
	int getHealth();
	int getMaxHealth();
	int getSpeed();
	int getAttackStat();
	int getDefenseStat();
	Attack& getAttack(int attackIndex);
	int getCurrentXP();
	int getXPNeeded();
	int getLevel();
	Status getStatus();
	Pokemon_Species getSpecies();
	Item getItem() { return *m_item; }

	void setName(std::string newName);
	void setHP(unsigned int newHP);
	void setStatus(Status* status);
	void setItem(Item* item);

	void evaluateStatus();
	bool outOfMoves();
	void printMoves();
	Attack& struggle();

	void applyStatus(Status& status);
private:

	bool zeroHP();
	bool takeDamage(Pokemon& attacker, Attack& attack);
	void calculateBaseStats();

	void checkAttack();
	void checkEvolution();

	Pokemon_Species m_species;

	std::string m_name = "_";
	Attack m_attacks[4];
	Item* m_item = &id_to_item[0];
	Attack m_struggle = id_to_attack[AttackIDs::struggle];


	int m_level = 0;
	int m_currentXP = 0;
	int m_xp_Needed = 0;

	int m_currentHealth = 0;
	int m_maxHealth = 0;

	int m_attack = 0;
	int m_defense = 0;
	int m_speed = 0;

	Status* m_status = &id_to_status[statusIDs::null];
};