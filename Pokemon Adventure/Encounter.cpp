#include "Encounter.h"

Encounter::Encounter(){}

bool Encounter::setup(GLFWwindow* window, Renderer* renderer, Input* input,bool* clicked, double* mouseX, double* mouseY)
{
	m_window = window;
	m_renderer = renderer;
	m_input = input;
	m_clicked = clicked;
	m_mouseX = mouseX;
	m_mouseY = mouseY;
	return true;
}

void Encounter::setupEncounter(Trainer& trainer, NPT& npt)
{
	for (int i = 0; i < 6; i++)
	{
		if (trainer.getPokemon(i)->getHealth() != 0)
		{
			m_activeTrainerPokemon = trainer.getPokemon(i);
			m_trainerPokemonIndex = i;
			break;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		std::vector<int> pokemonRecord;
		m_xpRecords.push_back(pokemonRecord);
	}
	
	m_activeTrainer = &trainer;
	m_activeNPT = &npt;
	m_activeAIPokemon = npt.getPokemon(0);
}

void Encounter::setupEncounter(Trainer& trainer, Pokemon& pokemon, PC& pc)
{
	for (int i = 0; i < 6; i++)
	{
		if (trainer.getPokemon(i)->getHealth() != 0)
		{
			m_activeTrainerPokemon = trainer.getPokemon(i);
			m_trainerPokemonIndex = i;
			break;
		}
	}

	std::vector<int> pokemonRecord;
	m_xpRecords.push_back(pokemonRecord);

	m_pc = &pc;
	m_activeTrainer = &trainer;
	m_activeAIPokemon = &pokemon;
}

void Encounter::beginEncounter()
{
	//TODO: Add animations and graphics
	//TODO: Add move selection when leveling up

	m_renderer->setPokemon(m_activeTrainerPokemon, m_activeAIPokemon);
	m_renderer->setEncounter(true);

	while (!glfwWindowShouldClose(m_window))
	{
		getPlayerAction();
		getAIAction();

		simulateActions();

		if (battleEnded())
			break;

		onUpdate();
	}

	checkEvolutions();

	awardPlayer();
}

void Encounter::clearEncounter()
{
	m_renderer->setPokemon(nullptr, nullptr);
	m_renderer->setEncounter(false);

	m_activeTrainer = nullptr;
	m_activeNPT = nullptr;
	m_activeTrainerPokemon = nullptr;
	m_activeAIPokemon = nullptr;

	m_flee = false;
	m_AIPokemonIndex = 0;

	m_xpRecords.clear();
	m_evolutionIndexes.clear();
	m_renderer->setState(DISPLAY_MAP);
	m_renderer->setTextBox("", "");
}

void Encounter::onUpdate()
{
	m_input->onUpdate();
	m_renderer->onUpdate();
}

bool Encounter::battleEnded()
{
	if (m_flee)
		return true;
	if (!m_activeTrainer->hasPokemon())
		return true;

	replacePlayerPokemon();

	if (AIOutOfPokemon())
		return true;

	return false;
}

void Encounter::getPlayerAction()
{
	m_renderer->setState(DEFAULT_ENCOUNTER);
	bool firstEntered = true;

	m_renderer->setTextBox("What should", m_activeTrainerPokemon->getName() + " do");

	while (!glfwWindowShouldClose(m_window))
	{

		if (*m_clicked && !firstEntered)
		{
			if (mouseOverFightOption())
			{
				if (playerSelectedMove())
					break;
			}
			else if (mouseOverPokemonOption())
			{
				if (playerSelecetedPokemon(true))
					break;
			}
			else if (mouseOverItemOption())
			{
				if (playerSelectedItem())
					break;
			}
			else if (mouseOverFleeOption())
			{
				if (playerSelectedFlee())
					break;
			}

			m_renderer->setState(DEFAULT_ENCOUNTER);
		}
		
		firstEntered = false;
		onUpdate();
	}
}

bool Encounter::getAIAction()
{

	std::cout << "Getting AI Action" << std::endl;

	//TODO: Make this a void function
	if (m_activeNPT == nullptr)
	{
		m_aiAction = FIGHT;
		m_aiActionIndex = m_activeAIPokemon->determineAttack(*m_activeTrainerPokemon);
	}
	else
	{
		int action = m_activeNPT->performAction(*m_activeAIPokemon, *m_activeTrainerPokemon);

		if (action >= 0 && action < 4)
		{
			m_aiAction = FIGHT;
			m_aiActionIndex = action;
		}
		else if (action == 4)
		{
			m_aiAction = FIGHT;
			m_aiActionIndex = action;
		}
		else if (action == 5)
		{
			m_aiAction = HEAL;
		}
	}

	return true;
}

void Encounter::simulateActions()
{
	//Priority actions
	if (m_playerAction == POKEMON)
	{
		swapPlayerPokemon();
	}
	else if (m_playerAction == POKEBALL)
	{
		if (caughtPokemon())
			return;
	}
	else if (m_playerAction == HEAL || m_playerAction == MISC)
	{
		useItem(true);
	}
	else if (m_playerAction == FLEE)
	{
		if (fleeSuccessful())
			return;
	}

	if (m_aiAction == HEAL)
	{
		useItem(false);
	}
	
	//FIGHT SIMULATION
	simulateCombat();
}

void Encounter::simulateCombat()
{
	if (m_playerAction != FIGHT)
	{
		if (m_aiAction != HEAL)
			simulateAIAttack();
	}
	else if (m_aiAction == HEAL)
	{
		simulatePlayerAttack();
	}
	else
	{
		if (m_activeTrainerPokemon->getSpeed() >= m_activeAIPokemon->getSpeed())
		{
			simulatePlayerAttack();

			if (pokemonFainted(m_activeAIPokemon))
			{
				evaluateStatus(m_activeTrainerPokemon);
				pokemonFainted(m_activeTrainerPokemon);
				return;
			}
			
			simulateAIAttack();
		}
		else
		{
			simulateAIAttack();
			
			if (pokemonFainted(m_activeTrainerPokemon))
			{
				evaluateStatus(m_activeAIPokemon);
				pokemonFainted(m_activeAIPokemon);
				return;
			}

			simulatePlayerAttack();
		}


		evaluateStatus(m_activeTrainerPokemon);
		pokemonFainted(m_activeTrainerPokemon);

		evaluateStatus(m_activeAIPokemon);
		pokemonFainted(m_activeAIPokemon);
	}
}

void Encounter::simulatePlayerAttack()
{
	calculateDamageTaken( *m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->getAttack(m_playerActionIndex));
}

void Encounter::simulateAIAttack()
{
	//TODO: Make this 4 a known value for struggle
	if (m_aiActionIndex == 4)
	{
		calculateDamageTaken(*m_activeAIPokemon, *m_activeTrainerPokemon, m_activeAIPokemon->struggle());
	}
	else
	{
		calculateDamageTaken(*m_activeAIPokemon, *m_activeTrainerPokemon, m_activeAIPokemon->getAttack(m_aiActionIndex));
	}
}

bool Encounter::fleeSuccessful()
{
	if (m_activeTrainerPokemon->getSpeed() > m_activeAIPokemon->getSpeed())
	{
		m_renderer->setTextBox("You have fled", "successfully");
		onUpdate();
		Sleep(1500);
		m_flee = true;
		return true;
	}

	// 50/50 to run away. Just be lucky lol
	if (odds(50))
	{
		std::cout << " You have fled successfully" << std::endl;
		m_renderer->setTextBox("You have", "fled successfully");
		onUpdate();
		Sleep(1500);
		m_flee = true;
		return true;
	}

	std::cout << "Flee attempt was unsuccessful" << std::endl;
	m_renderer->setTextBox("Flee attempt was", "un successful");
	onUpdate();
	Sleep(1500);
	return false;
}

void Encounter::swapPlayerPokemon()
{
	std::cout << "\n" << m_activeTrainerPokemon->getName() << " withdraw for now.\n" << std::endl;
	m_activeTrainerPokemon = m_activeTrainer->getPokemon(m_playerActionIndex);
	std::cout << m_activeTrainerPokemon->getName() << " I choose you!\n" << std::endl;

	m_trainerPokemonIndex = m_playerActionIndex;
	m_renderer->setPokemon(m_activeTrainerPokemon, m_activeAIPokemon);
}

void Encounter::useItem(bool playerItem)
{
	if (playerItem)
	{
		int pokeballCount = m_activeTrainer->getUniquePokeballCount();
		int healCount = m_activeTrainer->getUniqueHealCount();

		if (m_playerAction == HEAL)
		{
			healedPokemon(pokeballCount);
		}
		else if (m_playerAction == MISC)
		{
			appliedItem(*m_activeTrainer->getMiscItem(m_playerActionIndex - pokeballCount - healCount));
		}
	}
	else
	{
		useItem(*m_activeNPT, m_activeAIPokemon, *m_activeNPT->getNextHeal());
		m_activeNPT->removeHeal();
	}
}

bool Encounter::playerSelectedMove()
{
	bool firstEntered = true;
	m_renderer->setState(SELECT_ATTACK);

	m_activeTrainerPokemon->printMoves();

	while (!glfwWindowShouldClose(m_window))
	{
		
		int move = -1;

		//Move Click
		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 505.0f && *m_mouseX <= 940.0f && *m_mouseY >= 145.0f && *m_mouseY <= 230.0f)
				move = 0;
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1415.0f && *m_mouseY >= 145.0f && *m_mouseY <= 230.0f)
				move = 1;
			else if (*m_mouseX >= 505.0f && *m_mouseX <= 940.0f && *m_mouseY >= 20.0f && *m_mouseY <= 105.0f)
				move = 2;
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1415.0f && *m_mouseY >= 20.0f && *m_mouseY <= 105.0f)
				move = 3;
			else
				return false;
		}

		
		if (move != -1)
		{
			bool struggle = false;

			if (m_activeTrainerPokemon->getAttack(move).getCurrentPP() == 0)
			{
			
				struggle = m_activeTrainerPokemon->outOfMoves();

				if (!struggle)
				{
					std::cout << " You cannot use a move with 0pp" << std::endl;
					m_renderer->setTextBox("You cannot use a", "move with 0pp ");
					m_renderer->setState(DEFAULT_ENCOUNTER);
					onUpdate();
					Sleep(1500);
					return false;
				}
			}
			else
			{
				m_playerAction = FIGHT;
				m_playerActionIndex = move;
			}

			return true;
		}

		firstEntered = false;
		onUpdate();
	}

	std::cout << "\nNo move selected\n" << std::endl;

	return false;
}

bool Encounter::playerSelecetedPokemon(bool mainAction)
{
	std::cout << "\n Select A Pokemon \n" << std::endl;

	m_activeTrainer->printPokemon();
	m_renderer->setState(SELECT_POKEMON);

	bool firstEntered = true;
	while (!glfwWindowShouldClose(m_window))
	{
		int selectedPokemon = -1;

		// Select Pokemon
		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 495.0f && *m_mouseX <= 940.0f)
			{
				if (*m_mouseY >= 627.5f && *m_mouseY <= 722.5f)
					selectedPokemon = 0;
				else if (*m_mouseY >= 492.5f && *m_mouseY <= 587.5f)
					selectedPokemon = 2;
				else if (*m_mouseY >= 357.5f && *m_mouseY <= 452.5f)
					selectedPokemon = 4;
				else
					return false;
			}
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1425.0f)
			{
				if (*m_mouseY >= 627.5f && *m_mouseY <= 722.5f)
					selectedPokemon = 1;
				else if (*m_mouseY >= 492.5f && *m_mouseY <= 587.5f)
					selectedPokemon = 3;
				else if (*m_mouseY >= 357.5f && *m_mouseY <= 452.5f)
					selectedPokemon = 5;
				else
					return false;
			}
			else
				return false;
				
		}


		if (selectedPokemon >= 0 && selectedPokemon <= 5)
		{
			if (m_activeTrainer->getPokemon(selectedPokemon)->getLevel() != 0)
			{

				if (mainAction)
				{
					if (m_activeTrainer->getPokemon(selectedPokemon) != m_activeTrainerPokemon && m_activeTrainer->getPokemon(selectedPokemon)->getHealth() != 0)
					{
						m_playerAction = POKEMON;
						m_playerActionIndex = selectedPokemon;
						return true;
					}
				}
				else
				{
					m_selectionIndex = selectedPokemon;
					return true;
				}
			}
		}

		firstEntered = false;
		onUpdate();
	}

	std::cout << "No new Pokemon Selected" << std::endl;
	return false;
}

bool Encounter::playerSelectedItem()
{
	unsigned int bagIndex = 0;

	bool firstEntered = true;
	m_renderer->setState(SELECT_ITEM);
	m_renderer->setBagIndex(bagIndex);

	std::cout << "\n\t~Select An Item~\n" << std::endl;
	m_activeTrainer->printItems();
	std::cout << "\n\n";

	int pokeballCount = m_activeTrainer->getUniquePokeballCount();
	int healCount = m_activeTrainer->getUniqueHealCount();
	int miscCount = m_activeTrainer->getUniqueMiscCount();

	while (!glfwWindowShouldClose(m_window))
	{

		if (!*m_clicked || firstEntered)
		{
			firstEntered = false;
			onUpdate();
			continue;
		}

		if (!mouseOverItem(true))
			return false;

		if (mouseOverItem(false, 0))			// Up Arrow
		{
			if (bagIndex > 0)
			{
				bagIndex--;
				m_renderer->setBagIndex(bagIndex);
			}
			firstEntered = true;
			onUpdate();
		}
		else if (mouseOverItem(false, 6))		// Down Arrow
		{
			if (bagIndex + 5 < pokeballCount + healCount + miscCount)
			{
				bagIndex++;
				m_renderer->setBagIndex(bagIndex);
			}
			firstEntered = true;
			onUpdate();
		}
		else										// Item Options - Boxes between the arrows
		{

			for (int boxNumber = 0; boxNumber < 5; boxNumber++)
			{
				if (!mouseOverItem(false, boxNumber + 1))
					continue;

				if (bagIndex + boxNumber >= pokeballCount + healCount + miscCount)
					break;
				


				m_playerActionIndex = bagIndex + boxNumber;

				findItemType(pokeballCount, healCount, miscCount);

				if (m_playerAction == POKEBALL)
				{
					if (canCatchPokemon())
						return true;

					continue;
				}

				if (!playerSelecetedPokemon(false))
					return false;
				
				if (m_playerAction == HEAL)
				{
					if (canUseItem(m_activeTrainer->getPokemon(m_selectionIndex), *m_activeTrainer->getHealItem(m_playerActionIndex)))
					{
						return true;
					}
				}
				else if (m_playerAction == MISC)
				{
					if (canUseItem(m_activeTrainer->getPokemon(m_selectionIndex), *m_activeTrainer->getMiscItem(m_playerActionIndex)))
					{
						return true;
					}
				}
			}
			return false;
		}
	}
	return true;
}

bool Encounter::playerSelectedFlee()
{
	if (m_activeNPT != nullptr)
	{
		std::cout << "You cannot run from a battle" << std::endl;
		m_renderer->setTextBox("You cannot run", "from a battle");
		onUpdate();
		Sleep(1500);
		return false;
	}

	m_playerAction = FLEE;
	return true;
}

bool Encounter::pokemonFainted(Pokemon* pokemon)
{
	//TODO: Add text for pokemon fainting
	if (!pokemon->hasFainted())
		return false;
	
	if( pokemon == m_activeAIPokemon )
	{
		m_renderer->setState(DEFAULT_ENCOUNTER);
		int xpGain = calculateXPGain(*pokemon);

		for (int i = 0; i < m_xpRecords.at(m_AIPokemonIndex).size(); i++)
		{
			animateXPGain(m_activeTrainer->getPokemon(m_xpRecords.at(m_AIPokemonIndex).at(i)), xpGain);
		}
	}
	else
	{
		std::cout << m_activeTrainerPokemon->getName() << " has fainted" << std::endl;

		removeAttackRecord();
	}
	return true;
}

int Encounter::calculateXPGain(Pokemon& pokemon)
{
	float x = (static_cast<float>(pokemon.getSpecies().getXPYield()) * pokemon.getLevel()) / 7.0f;
	float y = 1.0f / m_xpRecords.at(m_AIPokemonIndex).size();
	float z = 1.0f;

	if (m_activeNPT != nullptr)
		z = 1.5;

	if ((x * y * z) < 1)
		return 1;
	else
		return x * y * z;
}

void Encounter::animateXPGain(Pokemon* pokemon, int xpGain)
{
	if (pokemon->getLevel() == 100)
		return;

	int currentLevel = pokemon->getLevel();

	std::string nameGained = pokemon->getName() + " gained";
	std::string xpAmount = std::to_string(xpGain) + " EXP";

	m_renderer->setTextBox(nameGained, xpAmount);
	awaitClick();

	for (int i = 0; i < xpGain; i++)
	{
		pokemon->gainXP(1);

		if (pokemon->getLevel() != currentLevel)
		{
			
			recordLevelUp();
			//TODO: Ask for evolve and moves to be learned
			//Only Evolve after the battle
			currentLevel = pokemon->getLevel();

			nameGained = pokemon->getName() + " has";
			xpAmount = "leveled up";
			m_renderer->setTextBox(nameGained, xpAmount);

			awaitClick();

			nameGained = pokemon->getName() + " is now";
			xpAmount = "level " + std::to_string(currentLevel);
			m_renderer->setTextBox(nameGained, xpAmount);

			awaitClick();

		}

		onUpdate();
	}
}

void Encounter::replacePlayerPokemon()
{
	if (m_activeTrainerPokemon->getHealth() == 0)
	{
		while (true)
		{
			if (playerSelecetedPokemon(false))
				break;
		}

		m_activeTrainerPokemon = m_activeTrainer->getPokemon(m_selectionIndex);
		m_trainerPokemonIndex = m_selectionIndex;
		m_renderer->setPokemon(m_activeTrainerPokemon, m_activeAIPokemon);
	}
}

bool Encounter::AIOutOfPokemon()
{
	if (m_activeAIPokemon->getHealth() == 0)
	{
		if (m_activeNPT == nullptr)
			return true;

		if (!m_activeNPT->hasWhiteOut())
			swapAIPokemon();
		else
			return true;
	}

	return false;
}

int Encounter::calculateDamageTaken(Pokemon& attackingPokemon, Pokemon& defendingPokemon, Attack& attack)
{
	m_renderer->setState(DEFAULT_ENCOUNTER);
	m_renderer->setTextBox(attackingPokemon.getName() + " used", attack.getName());
	onUpdate();
	Sleep(1500);

	if (odds(attack.getAccuracy()))
	{
		int Power = attack.getDamage();
		int Level = attackingPokemon.getLevel();
		int A = attackingPokemon.getAttackStat();
		int D = defendingPokemon.getDefenseStat();
		int crit = 1;
		float random = 1;



		if (odds(attack.getCritChance()))
			crit = 2;

		int totalDamage = (((((2.0f * Level * crit) / 5.0f) + 2) * Power * (static_cast<float>(A) / static_cast<float>(D))) / 50.0f) + 2;



		// STAB
		if (attack.getType() == attackingPokemon.getSpecies().getType1() || attack.getType() == attackingPokemon.getSpecies().getType2())
			totalDamage *= 1.5;

		//TYPE 1 Effectiveness
		float effectiveness = TypeChart[attack.getType()][defendingPokemon.getSpecies().getType1()];

		//TYPE 2 Effectiveness
		if (defendingPokemon.getSpecies().getType2() != NOTYPE)
			effectiveness *= TypeChart[attack.getType()][defendingPokemon.getSpecies().getType2()];

		totalDamage *= effectiveness;


		//TODO: Make sure random is working correctly
		if (totalDamage != 1)
			random = static_cast<float>((rand() % 38 + 1.0f) + 217.0f) / 255.0f;

		totalDamage *= random;

		//DRIP DAMAGE
		animateDamageTaken(&defendingPokemon, totalDamage);


		if (effectiveness >= 2.0f)
		{
			std::cout << " It's super effective! " << std::endl;
			m_renderer->setTextBox("Its", "super Effective");
			onUpdate();
			Sleep(1500);
		}
		else if (effectiveness <= 1.0f)
		{
			std::cout << " It's not very effective" << std::endl;
			m_renderer->setTextBox("Its not", "very effective");
			onUpdate();
			Sleep(1500);
		}

		if (crit == 2)
		{
			m_renderer->setTextBox("Its was a", "critical hit");
			std::cout << "Its a critical Hit!" << std::endl;
			Sleep(1500);
		}

		giveStatus(defendingPokemon, attack);
		recordAttack();
	}
	else
	{
		std::cout << "It Missed" << std::endl;
		m_renderer->setTextBox(attackingPokemon.getName() + "s", "attack missed");
		onUpdate();
		Sleep(1500);
	}

	attack.usePP();
	return 0;
}

void Encounter::animateDamageTaken(Pokemon* pokemon, int damage)
{
	for (int i = 0; i < damage; i++)
	{
		if (!pokemon->takeDamage(1))
			break;
		onUpdate();
	}
}

void Encounter::giveStatus(Pokemon& defendingPokemon, Attack& attack)
{

	if (&attack.getStatus() == nullptr)
		return;


	if (defendingPokemon.getStatus() != attack.getStatus() && odds(attack.getStatus().getApplicationOdds()))
	{
		defendingPokemon.setStatus(&attack.getStatus());
		std::cout << defendingPokemon.getName() << " has been " << attack.getStatus().getName() << std::endl;
		m_renderer->setTextBox(defendingPokemon.getName() + " has", "been " + attack.getStatus().getName());
		onUpdate();
		Sleep(1500);
	}
}

void Encounter::evaluateStatus(Pokemon* pokemon)
{
	if (pokemon->getStatus().getID() == statusIDs::null)
		return;

	if (pokemon->getStatus().takeDamage())
	{
		std::cout << pokemon->getName() << " is hurt from its " << pokemon->getStatus().getName() << std::endl;
		m_renderer->setTextBox(pokemon->getName() + " is hurt", "from its " + pokemon->getStatus().getName());
		onUpdate();
		Sleep(1500);

		int damage = (pokemon->getMaxHealth() / 16.0f);

		animateDamageTaken(pokemon, damage);
	}
}

bool Encounter::useItem(Trainer& trainer, Pokemon* pokemon, Item& item)
{
	std::cout << trainer.getName() << " has used " << item.getName() << std::endl;
	m_renderer->setTextBox(trainer.getName() + " has", "used " + item.getName());

	if (item.isRevive())
	{
		for (int i = 0; i < pokemon->getMaxHealth() / 2; i++)
		{
			pokemon->giveHP(1);
			onUpdate();
		}
	}

	for (int i = 0; i < item.getHealAmount(); i++)
	{
		if (pokemon->getHealth() == pokemon->getMaxHealth())
			break;
		pokemon->giveHP(1);
		onUpdate();
	}

	if (&item.getStatus() != NULL && pokemon->getStatus().getID() != statusIDs::null && pokemon->getStatus().getID() == item.getStatus().getID())
	{
		std::cout << pokemon->getName() << " has been healed of its" << item.getName() << std::endl;
		pokemon->setStatus(&id_to_status[statusIDs::null]);
		m_renderer->setTextBox(pokemon->getName() + " is no", "longer " + item.getName());
		onUpdate();
		Sleep(1000);
	}

	return true;
}

void Encounter::findItemType(int pokeballCount, int healCount, int miscCount)
{

	if (m_playerActionIndex < pokeballCount)
	{
		m_playerAction = POKEBALL;
	}
	else if (m_playerActionIndex < pokeballCount + healCount)
	{
		m_playerActionIndex -= pokeballCount;

		m_playerAction = HEAL;
	}
	else
	{
		m_playerActionIndex -= pokeballCount + healCount;
		m_playerAction = MISC;
	}
}

void Encounter::swapAIPokemon()
{
	if (m_activeNPT == nullptr || m_AIPokemonIndex == 6)
		return;

	if (m_activeNPT->getPokemon(m_AIPokemonIndex + 1)->getLevel() == 0)
		return;

	m_AIPokemonIndex += 1;
	m_activeAIPokemon = m_activeNPT->getPokemon(m_AIPokemonIndex);
	m_renderer->setPokemon(m_activeTrainerPokemon, m_activeAIPokemon);
}

void Encounter::recordAttack()
{
	if ( std::find(m_xpRecords.at(m_AIPokemonIndex).begin(), m_xpRecords.at(m_AIPokemonIndex).end(), m_trainerPokemonIndex) == m_xpRecords.at(m_AIPokemonIndex).end())
		m_xpRecords.at(m_AIPokemonIndex).push_back(m_trainerPokemonIndex);

}

void Encounter::removeAttackRecord()
{
	if (std::find(m_xpRecords.at(m_AIPokemonIndex).begin(), m_xpRecords.at(m_AIPokemonIndex).end(), m_trainerPokemonIndex) != m_xpRecords.at(m_AIPokemonIndex).end())
	{
		for (int i = 0; i < m_xpRecords.at(m_AIPokemonIndex).size(); i++)
		{
			if (m_xpRecords.at(m_AIPokemonIndex).at(i) == m_trainerPokemonIndex)
				m_xpRecords.at(m_AIPokemonIndex).erase(m_xpRecords.at(m_AIPokemonIndex).begin() + i);
		}
	}
}

void Encounter::recordLevelUp()
{
	if (std::find(m_evolutionIndexes.begin(), m_evolutionIndexes.end(), m_trainerPokemonIndex) == m_evolutionIndexes.end())
		m_evolutionIndexes.push_back(m_trainerPokemonIndex);
}

void Encounter::checkEvolutions()
{
	for (int i = 0; i < m_evolutionIndexes.size(); i++)
	{
		m_activeTrainer->getPokemon(m_evolutionIndexes.at(i))->checkEvolution();
	}
}

void Encounter::awardPlayer()
{
	//TODO: Add white out for player
	if (m_activeNPT != nullptr && m_activeNPT->hasWhiteOut())
	{
		//TODO: Add visual and text for this
		std::cout << "Trainer is being given $" << m_activeNPT->getMoneyBalance();
		m_activeTrainer->giveMoney(m_activeNPT->getMoneyBalance());
		std::cout << "Trainer balance is now $" << m_activeTrainer->getMoneyBalance();

		m_activeNPT->removePokemon();
	}
}

bool Encounter::caughtPokemon()
{
	Item& item = *m_activeTrainer->getPokeball(m_playerActionIndex);

	//TODO: Implement Shake
	int catchRate = (((((3.0f * static_cast<float>(m_activeAIPokemon->getMaxHealth())) - (2.0f * static_cast<float>(m_activeAIPokemon->getHealth()))) / (3.0f * static_cast<float>(m_activeAIPokemon->getMaxHealth()))) * static_cast<float>(m_activeAIPokemon->getSpecies().getCatchRate()) * item.getPokeballBonus()) / 255.0f) * 100.0f;

	m_renderer->setState(DEFAULT_ENCOUNTER);
	std::cout << "Using " << item.getName() << std::endl;
	m_renderer->setTextBox("Using ", item.getName());
	onUpdate();

	if (odds(catchRate))
	{
		std::cout << "Pokemon Has Been Caught!" << std::endl;
		m_renderer->setTextBox(m_activeAIPokemon->getName(), "has been caught");
		onUpdate();
		Sleep(1500);

		if (!m_activeTrainer->addedPokemon(*m_activeAIPokemon))
			m_pc->addPokemon(*m_activeTrainer, *m_activeAIPokemon);
		m_activeTrainer->removeItem(item);
		m_flee = true;
		return true;
	}
	else
	{
		std::cout << "The Pokemon escaped" << std::endl;
		m_renderer->setTextBox("The " + m_activeAIPokemon->getName(), "has escaped");
		onUpdate();
		Sleep(1500);
		m_activeTrainer->removeItem(item);
		getAIAction();
	}

	return false;
}

bool Encounter::healedPokemon(unsigned int pokeballCount)
{
	Item* item = m_activeTrainer->getHealItem(m_playerActionIndex);

	std::cout << "Using " << item->getName() << std::endl;

	//TODO: Can remove the if statement because these checks should be happening before this point
	
	if (m_selectionIndex >= 0 && m_selectionIndex <= 5 && m_activeTrainer->getPokemon(m_selectionIndex)->getLevel() != 0)
	{
		useItem(*m_activeTrainer, m_activeTrainer->getPokemon(m_selectionIndex), *item);
		m_activeTrainer->removeItem( *item );
		//getAIAction();
		return true;
	}

	return false;
}

bool Encounter::appliedItem(Item& item)
{
	std::cout << "Using " << item.getName() << std::endl;
	return false;
}

bool Encounter::canUseItem(Pokemon* pokemon, Item& item)
{
	if ((item.isRevive() && pokemon->getHealth() != 0) || (!item.isRevive() && pokemon->getHealth() == 0))
		return false;

	if (!item.isRevive() && item.getHealAmount() == 0 && pokemon->getStatus() != item.getStatus())
		return false;

	return true;
}

bool Encounter::canCatchPokemon()
{
	if (m_activeNPT == nullptr)
		return true;

	std::cout << " No Stealing Pokemon from Trainers!" << std::endl;
	m_renderer->setTextBox("No Stealing Pokemon", "from Trainers");
	onUpdate();
	Sleep(1500);

	return false;
}

bool Encounter::mouseOverFightOption()
{
	if (*m_mouseX >= 970.0f && *m_mouseX <= 1445.0f && *m_mouseY >= 150.0f && *m_mouseY <= 250.0f)
		return true;
	return false;
}

bool Encounter::mouseOverPokemonOption()
{
	if (*m_mouseX >= 970.0f && *m_mouseX <= 1445.0f && *m_mouseY >= 0.0f && *m_mouseY <= 150.0f)
		return true;
	return false;
}

bool Encounter::mouseOverItemOption()
{
	if (*m_mouseX >= 1445.0f && *m_mouseX <= 1920.0f && *m_mouseY >= 150.0f && *m_mouseY <= 250.0f)
		return true;
	return false;
}

bool Encounter::mouseOverFleeOption()
{
	if (*m_mouseX >= 1445.0f && *m_mouseX <= 1920.0f && *m_mouseY >= 0.0f && *m_mouseY <= 150.0f)
		return true;
	return false;
}

bool Encounter::mouseOverItem(bool isX, int boxNumber)
{
	float boxDifference = 135.0f;

	float leftX = 737.5f;
	float rightX = 1182.5f;

	float topY = 992.5f;
	float botY = 897.5f;

	if (isX)
	{
		if (*m_mouseX >= leftX && *m_mouseX <= rightX)
		{
			return true;
		}
	}
	else
	{
		if (*m_mouseY >= botY - (boxNumber * boxDifference) && *m_mouseY <= topY - (boxNumber * boxDifference))
		{
			return true;
		}
	}
	return false;
}

void Encounter::awaitClick()
{
	bool firstEntered = true;

	while (!glfwWindowShouldClose(m_window))
	{

		if (*m_clicked && !firstEntered)
			break;

		firstEntered = false;
		m_renderer->setAwaitClick(true);
		onUpdate();
	}

	//TODO: Make sure this didnt break anything
	m_renderer->setAwaitClick(false);
}