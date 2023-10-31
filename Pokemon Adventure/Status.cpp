#include "Status.h"

Status::Status(std::string name, bool damage, bool stun, int applicationOdds, int recoveryOdds, unsigned int id)
{
	// TODO: Display Status in battle
	m_name = name;
	m_damage = damage;
	m_stun = stun;
	m_applicationOdds = applicationOdds;
	m_recoveryOdds = recoveryOdds;
	m_id = id;
}

Status::Status(){}

int Status::getApplicationOdds()
{
	return m_applicationOdds;
}

std::string Status::getName()
{
	return m_name;
}

bool Status::takeDamage()
{
	return m_damage;
}

bool Status::notStunned()
{
	if (odds(25))
		return false;

	return true;
}

bool Status::operator==(const Status& other)
{
	return other.m_name == m_name;
}

bool Status::operator!=(const Status& other)
{
	return !(other.m_name == m_name);
}
