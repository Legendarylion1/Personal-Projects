#pragma once

#include <string>
#include "Formulas.h"

class Status
{
public:
	Status(std::string name, bool damage, bool stun, int applicationOdds, int recoveryOdds, unsigned int id);
	Status();

	int getApplicationOdds();
	std::string getName();
	unsigned int getID() { return m_id; }
	bool takeDamage();
	bool notStunned();

	bool operator==(const Status& other);
	bool operator!=(const Status& other);

private:
	std::string m_name;
	unsigned int m_id = 0;

	bool m_damage = false;
	int m_applicationOdds = -1;
	int m_recoveryOdds = 0;

	bool m_stun = false;
};