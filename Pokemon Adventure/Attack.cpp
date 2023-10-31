#include "Attack.h"

Attack::Attack(std::string name, unsigned int type, int damage, int critChance, int pp, int accuracy, Status* status, unsigned int id)
{
	m_name = name;
	m_type = type;
	m_damage = damage;
	m_maxPP = pp;
	m_currentPP = pp;
	m_critChance = critChance;
	m_accuracy = accuracy;
	m_status = status;
	m_id = id;
}

Attack::Attack(){}

void Attack::usePP()
{
	m_currentPP -= 1;
}

void Attack::setPP(unsigned int pp)
{
	m_currentPP = pp;
}

int Attack::getCurrentPP()
{
	return m_currentPP;
}

int Attack::getMaxPP()
{
	return m_maxPP;
}

int Attack::getDamage()
{
	return m_damage;
}

std::string Attack::getName()
{
	return m_name;
}

Status& Attack::getStatus()
{
	return *m_status;
}

int Attack::getAccuracy()
{
	return m_accuracy;
}

int Attack::getCritChance()
{
	return m_critChance;
}

unsigned int Attack::getType()
{
	return m_type;
}
