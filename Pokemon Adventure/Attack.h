#pragma once

#include "Status.h"
#include "TypeChart.h"

class Attack
{
public:
	Attack(std::string name, unsigned int type, int damage, int critChance, int pp, int accuracy, Status* status, unsigned int id);
	Attack();

	void usePP();
	void setPP(unsigned int pp);

	int getCurrentPP();
	int getMaxPP();
	int getDamage();
	std::string getName();
	unsigned int getID() { return m_id; };
	Status& getStatus();
	int getAccuracy();
	int getCritChance();
	unsigned int getType();
private:
	std::string m_name;
	unsigned int m_type = 0;
	unsigned int m_id = 0;
	int m_damage = 0;
	int m_maxPP = 0;
	int m_currentPP = 0;
	int m_critChance = 0;
	int m_accuracy = 0;
	Status* m_status = nullptr;
};