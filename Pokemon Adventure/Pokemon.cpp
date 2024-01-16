#include "Pokemon.h"


Pokemon::Pokemon(Pokemon_Species species, int level, Attack attacks[4])
{
	m_name = species.getName();
	m_species = species;

	m_level = level;

	m_attacks[0] = attacks[0];
	m_attacks[1] = attacks[1];
	m_attacks[2] = attacks[2];
	m_attacks[3] = attacks[3];

	calculateBaseStats();

	m_currentHealth = m_maxHealth;
}

Pokemon::Pokemon(Pokemon_Species species, int level)
{
	m_name = species.getName();
	m_species = species;

	m_level = level;

	calculateBaseStats();
	m_currentHealth = m_maxHealth;
}

Pokemon::Pokemon(){}

std::string Pokemon::getName()
{
	return m_name;
}

int Pokemon::getHealth()
{
	return m_currentHealth;
}

int Pokemon::getMaxHealth()
{
	return m_maxHealth;
}

int Pokemon::getSpeed()
{
	return m_speed;
}

Attack& Pokemon::getAttack(int attackIndex)
{
	return m_attacks[attackIndex];
}

void Pokemon::gainXP(int xpGained)
{
	while (true)
	{
		if (m_currentXP + xpGained >= m_xp_Needed)
		{
			xpGained -= m_xp_Needed - m_currentXP;

			m_currentXP = 0;
			m_level += 1;

			std::cout << m_name << " has leveled up!" << std::endl;
			std::cout << m_name << " is level " << m_level << std::endl;

			checkAttack();
			calculateBaseStats();


		}
		else
		{
			m_currentXP += xpGained;
			break;
		}
	}
}

bool Pokemon::hasFainted()
{
		return zeroHP();
}

int Pokemon::determineAttack(Pokemon& opposingPokemon)
{
	//TODO: Right now AI only cares about strength. When I add healing moves then we need to take those into account
	int strongestAttack = 0;
	float effectiveness = 0;


	for (int i = 1; i < 4; i++)
	{
		float tempEffectiveness = 0;
		if (m_attacks[i].getMaxPP() != 0)
		{
			
			tempEffectiveness = TypeChart[m_attacks[i].getType()][opposingPokemon.getSpecies().getType1()];
			if (opposingPokemon.getSpecies().getType2() != NOTYPE)
			{
				tempEffectiveness *= TypeChart[m_attacks[i].getType()][opposingPokemon.getSpecies().getType2()];
			}

			if (m_attacks[i].getType() == opposingPokemon.getSpecies().getType1() || m_attacks[i].getType() == opposingPokemon.getSpecies().getType2())
				tempEffectiveness *= 1.5;

			tempEffectiveness *= m_attacks[i].getDamage();

			if (tempEffectiveness >= effectiveness && odds(80))
			{
				effectiveness = tempEffectiveness;
				strongestAttack = i;
			}
		}
	}
	return strongestAttack;
}

void Pokemon::giveHP(int hp)
{
	if (m_currentHealth + hp <= m_maxHealth)
		m_currentHealth += hp;
	else
		m_currentHealth = m_maxHealth;
}

bool Pokemon::takeDamage(int damage)
{
	if (m_currentHealth - damage >= 0)
	{
		m_currentHealth -= damage;
		return true;
	}
	else
	{
		m_currentHealth = 0;
		return false;
	}
}

bool Pokemon::zeroHP()
{
	if (m_currentHealth == 0)
	{
		std::cout << m_name.c_str() << "Has fainted" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Pokemon::checkAttack()
{
	for (auto& value : m_species.getMovelist())
	{
		if (m_level == value.first)
			teachAttack(value.second);
	}
}

void Pokemon::teachAttack(Attack newAttack)
{
	//TODO: Implement for mouse and keyboard
	for (int i = 0; i < 4; i++)
	{
		if (m_attacks[i].getMaxPP() == 0)
		{
			m_attacks[i] = newAttack;
			std::cout << m_name << " has learned " << newAttack.getName() << "!" << std::endl;
			return;
		}
	}

	std::cout << m_name << " wants to learn " << newAttack.getName() << std::endl;
	std::cout << "Pick a move to swap with " << newAttack.getName() <<  std::endl;

	printMoves();
	int selection = 0;
	std::cin >> selection;

	if (selection >= 1 && selection <= 4)
	{
		m_attacks[selection - 1] = newAttack;
		std::cout << m_name << " has learned " << newAttack.getName() << "!" << std::endl;
	}
	else
	{
		std::cout << m_name << " did not learn " << newAttack.getName() << std::endl;
	}
}

void Pokemon::randomizeAttacks()
{
	std::vector<Attack> possibleAttacks;

	for (auto i : m_species.getMovelist())
	{
		if (i.first <= m_level)
			possibleAttacks.push_back(i.second);
	}


	for (int i = 0; i < 4; i++)
	{
		if (possibleAttacks.size() == 0)
			break;

		int attackIndex = rand() % possibleAttacks.size();
		m_attacks[i] = possibleAttacks.at(attackIndex);
		possibleAttacks.erase(possibleAttacks.begin() + attackIndex);
	}
}

bool Pokemon::outOfMoves()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_attacks[i].getCurrentPP() > 0)
			return false;
	}

	return true;
}

void Pokemon::calculateBaseStats()
{
	//TODO: XP Speed Ranges
	//Meduim Fast XP
	int prevMax = m_maxHealth;

	m_xp_Needed = ((m_level + 1) * (m_level + 1) * (m_level + 1) - (m_level * m_level * m_level));

	m_maxHealth = m_species.getBaseHealth() + (m_level * (static_cast<float>(m_species.getBaseHealth()) / 50.0f));
	m_attack = m_species.getBaseAttack() + (m_level * (static_cast<float>(m_species.getBaseAttack()) / 50.0f));
	m_defense = m_species.getBaseDefense() + (m_level * (static_cast<float>(m_species.getBaseDefense()) / 50.0f));
	m_speed = m_species.getBaseSpeed() + (m_level * (static_cast<float>(m_species.getBaseSpeed()) / 50.0f));

	giveHP(m_maxHealth - prevMax);
}

int Pokemon::getCurrentXP()
{
	return m_currentXP;
}

int Pokemon::getXPNeeded()
{
	return m_xp_Needed;
}

int Pokemon::getLevel()
{
	return m_level;
}

Pokemon_Species Pokemon::getSpecies()
{
	return m_species;
}

int Pokemon::getAttackStat()
{
	return m_attack;
}

int Pokemon::getDefenseStat()
{
	return m_defense;
}

Status Pokemon::getStatus()
{
	return *m_status;
}

void Pokemon::checkEvolution()
{
	if (m_species.getEvolution().size() == 0)
		return;

	bool changeName = false;

	if (m_level >= m_species.getEvolution().begin()->first)
	{
		std::cout << m_name << " is evolving!" << std::endl;

		if (m_name == m_species.getName())
			changeName = true;

		m_species = m_species.getEvolution().begin()->second;
		std::cout << m_name << " has evolved into a " << m_species.getName() << std::endl;

		if (changeName)
			m_name = m_species.getName();

	}
}

void Pokemon::printMoves()
{
	for (int i = 0; i < 4; i++)
	{
		if (getAttack(i).getMaxPP() > 0)
			std::cout << i + 1 << ". " << getAttack(i).getName() << ": " << getAttack(i).getCurrentPP() << "/" << getAttack(i).getMaxPP() << std::endl;
		else
			std::cout << i + 1 << ". None" << std::endl;
	}
}

void Pokemon::setName(std::string newName)
{
	m_name = newName;
}

void Pokemon::setHP(unsigned int newHP)
{
	m_currentHealth = newHP;
}

void Pokemon::setStatus(Status* status)
{
	m_status = status;
}

void Pokemon::setItem(Item* item)
{
	m_item = item;
}

Attack& Pokemon::struggle()
{
	return m_struggle;
}