#include "Trainer.h"

Trainer::Trainer(std::string name)
{
	m_name = name;
}


bool Trainer::addedPokemon(Pokemon newPokemon)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_roster[i].getLevel() == 0)
		{
			m_roster[i] = newPokemon;
			return true;
		}
	}
	return false;
}

void Trainer::insertPokemon(Pokemon newPokemon, unsigned int index)
{
	m_roster[index] = newPokemon;
}


Pokemon* Trainer::getPokemon(int index)
{
	return &m_roster[index];
}

Pokemon Trainer::popPokemon(int index)
{
	std::cout << "[Debug] Popping Index: " << index << std::endl;
	Pokemon poppedPokemon = m_roster[index];
	m_roster[index] = Pokemon();

	return poppedPokemon;
}

void Trainer::setRoster(Pokemon newRoster[6])
{
	m_roster[0] = newRoster[0];
	m_roster[1] = newRoster[1];
	m_roster[2] = newRoster[2];
	m_roster[3] = newRoster[3];
	m_roster[4] = newRoster[4];
	m_roster[5] = newRoster[5];
}

void Trainer::swapPokemon(unsigned int index1, unsigned int index2)
{
	Pokemon copy = m_roster[index1];

	m_roster[index1] = m_roster[index2];
	m_roster[index2] = copy;
}

bool Trainer::hasPokemon()
{
	//std::cout << "Checking for pokemon\n";
	for (int i = 0; i < 6; i++)
	{
		if (m_roster[i].getLevel() > 0)
		{
			//std::cout << "Trainer has a level " << m_roster[i].getLevel() << " " << m_roster[i].getName() << std::endl;
			return true;
		}
	}

	//std::cout << "Trainer has no pokemon" << std::endl;
	return false;
}

bool Trainer::hasWhiteOut()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_roster[i].getHealth() > 0)
			return false;
	}
	return true;
}

std::string Trainer::getName()
{
	return m_name;
}

unsigned int Trainer::getMoneyBalance()
{
	return m_money;
}

void Trainer::giveMoney(int amount)
{
	m_money += amount;
}

void Trainer::takeMoney(int amount)
{
	m_money -= amount;
}

unsigned int Trainer::getUniquePokeballCount()
{
	if (m_pokeballStorage.size() == 0)
		return 0;

	int count = 0;

	for (auto& value : m_pokeballStorage)
		count += 1;

	return count;
}

unsigned int Trainer::getUniqueHealCount()
{
	if (m_healItemStorage.size() == 0)
		return 0;

	int count = 0;

	for (auto& value : m_healItemStorage)
		count += 1;

	return count;
}

unsigned int Trainer::getUniqueMiscCount()
{
	if (m_miscItems.size() == 0)
		return 0;

	int count = 0;

	for (auto& value : m_miscItems)
		count += 1;

	return count;
}

unsigned int Trainer::getPokeballTypeCount(unsigned int index)
{
	
	return m_pokeballStorage[getPokeball(index)];
}

unsigned int Trainer::getHealTypeCount(unsigned int index)
{
	return m_healItemStorage[getHealItem(index)];
}

unsigned int Trainer::getMiscTypeCount(unsigned int index)
{
	return m_miscItems[getMiscItem(index)];
}

unsigned int Trainer::getTotalHealCount()
{
	int count = 0;

	for (auto& value : m_healItemStorage)
		count += value.second;

	return count;
}

Item* Trainer::getPokeball(unsigned int index)
{
	int count = 0;
	for (auto& value : m_pokeballStorage)
	{
		if (count == index)
			return value.first;
		count += 1;
	}
	return nullptr;
}

Item* Trainer::getHealItem(unsigned int index)
{
	int count = 0;
	for (auto& value : m_healItemStorage)
	{
		if (count == index)
			return value.first;
		count += 1;
	}
	return nullptr;
}

Item* Trainer::getMiscItem(unsigned int index)
{
	int count = 0;
	for (auto& value : m_miscItems)
	{
		if (count == index)
			return value.first;
		count += 1;
	}
	return nullptr;
}

void Trainer::addItem(Item& item)
{
	if (item.isPokeball())
	{
		if (m_pokeballStorage.find(&item) != m_pokeballStorage.end())
			m_pokeballStorage[&item] += 1;
		else
			m_pokeballStorage[&item] = 1;
	}
	else if (item.isHeal())
	{
		if (m_healItemStorage.find(&item) != m_healItemStorage.end())
			m_healItemStorage[&item] += 1;
		else
			m_healItemStorage[&item] = 1;
	}
	else
	{
		if (m_miscItems.find(&item) != m_miscItems.end())
			m_miscItems[&item] += 1;
		else
			m_miscItems[&item] = 1;
	}
}

void Trainer::removeItem(Item& item)
{
	if (item.isPokeball())
	{
		m_pokeballStorage[&item] -= 1;
		if (m_pokeballStorage[&item] == 0)
			m_pokeballStorage.erase(&item);
	}
	else if (item.isHeal())
	{
		m_healItemStorage[&item] -= 1;
		if (m_healItemStorage[&item] == 0)
			m_healItemStorage.erase(&item);
	}
	else
	{
		m_miscItems[&item] -= 1;
		if (m_miscItems[&item] == 0)
			m_miscItems.erase(&item);
	}
}

void Trainer::printPokemon()
{
	std::cout << "\n\t~Trainer Pokemon~\n" << std::endl;
	for (int i = 0; i < 6; i++)
	{
		if (m_roster[i].getLevel() != 0)
		{
			std::cout << i + 1 << ". " << m_roster[i].getName() << " Lv" << m_roster[i].getLevel() << "   " << m_roster[i].getCurrentXP() << "/" << m_roster[i].getXPNeeded() << " XP   " << "\t" << m_roster[i].getHealth() << "/" << m_roster[i].getMaxHealth() << " HP" << std::endl;
		}
		else
		{
			std::cout << i + 1 << ". None" << std::endl;
		}
	}
}

void Trainer::printItems()
{

	std::cout << "\n\t~Items~\n" << std::endl;

	int count = 1;
	for (auto& value : m_pokeballStorage)
	{
		std::cout << count << ". " << value.first->getName() << "\tx" << value.second << std::endl;
		count += 1;
	}
	for (auto& value : m_healItemStorage)
	{
		std::cout << count << ". " << value.first->getName() << "\tx" << value.second << std::endl;
		count += 1;
	}
	for (auto& value : m_miscItems)
	{
		std::cout << count << ". " << value.first->getName() << "\tx" << value.second << std::endl;
		count += 1;
	}
}
