#include "PC.h"

PC::PC(Trainer* trainer, Menu* menu)
{
	m_trainer = trainer;
	m_menu = menu;
}

bool PC::addPokemon(Pokemon pokemon)
{
	for (int boxCount = 0; boxCount < NUMBER_OF_BOXES; boxCount++)
	{
		for (int pokemonIndex = 0; pokemonIndex < POKEMON_IN_BOX; pokemonIndex++)
		{
			if (m_pcPokemon[boxCount][pokemonIndex].getLevel() == 0)
			{
				m_pcPokemon[boxCount][pokemonIndex] = pokemon;
				return true;
			}
		}
	}

	return false;
}

void PC::run()
{
	m_currentPokemonIndex = NONE;
	m_previousPokemonIndex = NONE;

	m_menu->setCanLeave(true);
	m_menu->setscene(MenuScene::USE_PC);
	m_menu->setRequestedData(&m_currentPokemonIndex);
	m_menu->preRun();
	
	while (true)
	{
		displayBox();

		m_menu->run();

		if (m_menu->leaveRequested())
		{
			if (m_previousPokemonIndex == NONE)
				break;

			//We cancel swap
			m_previousPokemonIndex = NONE;
			continue;
		}

		if (m_currentPokemonIndex != NONE)
		{

			if (m_currentPokemonIndex == arrowDirections::RIGHT)
			{
				moveBoxRight();
				continue;
			}
			else if (m_currentPokemonIndex == arrowDirections::LEFT)
			{
				moveBoxLeft();
				continue;
			}


			if (m_previousPokemonIndex != NONE)
				swapPokemon();
			else
			{
				if (isValidSelection())
				{
					m_previousPokemonIndex = m_currentPokemonIndex;
					m_previousBox = m_currentBox;
				}
			}

			m_currentPokemonIndex = NONE;
		}
	}

	m_menu->setCanLeave(false);
	m_menu->clearRequestedData();
	m_menu->resetScene(MenuScene::USE_PC);
	m_menu->postRun();
}

void PC::swapPokemon()
{
	//TODO: Dont allow player to move the last pokemon out of their box
	{
		Pokemon pokemon;
		
		if (m_previousPokemonIndex < 30 && m_currentPokemonIndex < 30)	//	Box to Box
		{
			pokemon = m_pcPokemon[m_previousBox][m_previousPokemonIndex];
			m_pcPokemon[m_previousBox][m_previousPokemonIndex] = m_pcPokemon[m_currentBox][m_currentPokemonIndex];
			m_pcPokemon[m_currentBox][m_currentPokemonIndex] = pokemon;
		}
		else if (m_previousPokemonIndex < 30 && m_currentPokemonIndex >= 30)	//	Box to Trainer
		{
			pokemon = m_pcPokemon[m_previousBox][m_previousPokemonIndex];
			m_pcPokemon[m_previousBox][m_previousPokemonIndex] = m_trainer->getPokemon(m_currentPokemonIndex - 30);
			m_trainer->setPokemon(m_currentPokemonIndex - 30, pokemon);
		}
		else if (m_previousPokemonIndex >= 30 && m_currentPokemonIndex < 30) //Trainer to Box
		{
			if (!playerHasEnoughPokemon())
				return;
			pokemon = m_trainer->getPokemon(m_previousPokemonIndex - 30);
			m_trainer->setPokemon(m_previousPokemonIndex - 30, m_pcPokemon[m_currentBox][m_currentPokemonIndex]);
			m_pcPokemon[m_currentBox][m_currentPokemonIndex] = pokemon;
		}
		else //Trainer to Trainer
		{
			pokemon = m_trainer->getPokemon(m_previousPokemonIndex - 30);
			m_trainer->setPokemon(m_previousPokemonIndex - 30, m_trainer->getPokemon(m_currentPokemonIndex - 30));
			m_trainer->setPokemon(m_currentPokemonIndex - 30, pokemon);
		}

	}

	m_previousPokemonIndex = NONE;
}

void PC::moveBoxRight()
{
	m_currentPokemonIndex = NONE;
	if (m_currentBox < 7)
		m_currentBox++;
	else
		m_currentBox = 0;
}

void PC::moveBoxLeft()
{
	m_currentPokemonIndex = NONE;

	if (m_currentBox > 0)
		m_currentBox--;
	else
		m_currentBox = 7;
}

void PC::displayBox()
{
	//system("CLS");
	//std::cout << "\tCurrent Box: " << m_currentBox << std::endl;

	for (int col = 0; col < 6; col++)
	{
		for (int row = 0; row < 5; row++)
		{

			if (m_pcPokemon[m_currentBox][row + (col * 5)].getLevel() == 0)
			{
				std::cout << " ,";
			}
			else
			{
				std::cout << "X,";
			}


		}

		std::cout << std::endl;
	}

	displayPokemonStats();
}

void PC::displayPokemonStats()
{
	getPokemonStatIndex();

	Pokemon displayPokemon;

	if (m_pokemonStatsIndex < 30)
		displayPokemon = m_pcPokemon[m_currentBox][m_pokemonStatsIndex];
	else
		displayPokemon = m_trainer->getPokemon(m_pokemonStatsIndex - 30);



	std::cout << "\t~ Pokemon Stats ~\n";
	if (displayPokemon.getLevel() == 0)
	{
		std::cout << "\t   ~ NONE ~";
		return;
	}

	std::cout << displayPokemon.getName() << "\tLv." << displayPokemon.getLevel() << std::endl;
	std::cout << displayPokemon.getSpecies().name << std::endl;

	std::cout << "-----------------------\n";

	std::cout << displayPokemon.getCurHealth() << "/" << displayPokemon.getStats().hp << std::endl;
	std::cout << "Attack : " << displayPokemon.getStats().attack << std::endl;
	std::cout << "Defense: " << displayPokemon.getStats().defense << std::endl;
	std::cout << "SP. ATK: " << displayPokemon.getStats().spAttack << std::endl;
	std::cout << "SP. DEF: " << displayPokemon.getStats().spDefense << std::endl;
	std::cout << "Speed  : " << displayPokemon.getStats().speed << std::endl;

	std::cout << "-----------------------\n\n";
	std::cout << "Moves Learned\n";
	std::cout << getAttackFromID(displayPokemon.getMoveset().move1)->getName() << std::endl;
	std::cout << getAttackFromID(displayPokemon.getMoveset().move2)->getName() << std::endl;
	std::cout << getAttackFromID(displayPokemon.getMoveset().move3)->getName() << std::endl;
	std::cout << getAttackFromID(displayPokemon.getMoveset().move4)->getName() << std::endl;

}

void PC::getPokemonStatIndex()
{
	int currentIndex = m_menu->getButtonIndex();

	if (currentIndex >= 36)
		return;

	m_pokemonStatsIndex = currentIndex;
}

bool PC::playerHasEnoughPokemon()
{
	//If player has > 1 pokemon we return true
	//else false
	int count = 0;

	for (int i = 0; i < 6; i++)
	{
		if (count == 2)
			return true;

		if (m_trainer->getPokemon(i).getLevel() > 0)
			count++;
	}

	if (count == 2)
		return true;

	return false;
}

bool PC::isValidSelection()
{
	if (m_currentPokemonIndex < 30)
	{
		if (m_pcPokemon[m_currentBox][m_currentPokemonIndex].getLevel() == 0)
			return false;
	}
	else
	{
		if (m_trainer->getPokemon(m_currentPokemonIndex - 30).getLevel() == 0)
			return false;
	}
	return true;
}
