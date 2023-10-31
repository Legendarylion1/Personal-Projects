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
	m_activeAIPokemon = npt.nptResources.getPokemon(0);
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
	//TODO: Refactor how encounters are handled
	m_renderer->setPokemon(m_activeTrainerPokemon, m_activeAIPokemon);
	m_renderer->setEncounter(true);

	while (!glfwWindowShouldClose(m_window))
	{
		getPlayerAction();

		if (m_activeTrainerPokemon->getHealth() == 0)
			break;
		if (m_activeAIPokemon->getHealth() == 0)
			break;
		if (m_flee)
			break;

		onUpdate();
	}

	//TODO: Add white out for player

	if (m_activeNPT != nullptr && m_activeNPT->nptResources.hasWhiteOut())
	{
		//TODO: Add visual and text for this
		std::cout << "Trainer is being given $" << m_activeNPT->nptResources.getMoneyBalance();
		m_activeTrainer->giveMoney(m_activeNPT->nptResources.getMoneyBalance());
		std::cout << "Trainer balance is now $" << m_activeTrainer->getMoneyBalance();

		m_activeNPT->removePokemon();
	}

	m_renderer->setPokemon(nullptr, nullptr);
	m_renderer->setEncounter(false);
}

void Encounter::clearEncounter()
{
	m_activeTrainer = nullptr;
	m_activeNPT = nullptr;
	m_activeTrainerPokemon = nullptr;
	m_activeAIPokemon = nullptr;

	m_flee = false;
	m_AIPokemonIndex = 0;

	m_xpRecords.clear();
	m_renderer->setState(DISPLAY_MAP);
	m_renderer->setTextBox("", "");
}

void Encounter::onUpdate()
{
	m_input->onUpdate();
	m_renderer->onUpdate();
}

void Encounter::getPlayerAction()
{
	m_renderer->setState(DEFAULT_ENCOUNTER);
	bool firstEntered = true;

	std::cout << "\n\nWhat would you like to do\n1: Fight\t2: Pokemon\n3: Items\t4: Run" << std::endl;

	m_renderer->setTextBox("What should", m_activeTrainerPokemon->getName() + " do");

	while (!glfwWindowShouldClose(m_window))
	{
		
		int option = 0;

		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 970.0f && *m_mouseX <= 1445.0f && *m_mouseY >= 150.0f && *m_mouseY <= 250.0f)
			{
				if (playerSelectedMove())
				{
					evaluateStatus(m_activeTrainerPokemon);
					handleFaint(*m_activeTrainerPokemon);
					evaluateStatus(m_activeAIPokemon);
					handleFaint(*m_activeAIPokemon);
					break;
				}
				m_renderer->setState(DEFAULT_ENCOUNTER);
				firstEntered = true;
			}
			else if (*m_mouseX >= 970.0f && *m_mouseX <= 1445.0f && *m_mouseY >= 0.0f && *m_mouseY <= 150.0f)
			{
				if (playerSelecetedPokemon(false))
				{
					evaluateStatus(m_activeTrainerPokemon);
					handleFaint(*m_activeTrainerPokemon);
					evaluateStatus(m_activeAIPokemon);
					handleFaint(*m_activeAIPokemon);
					break;
				}
				m_renderer->setState(DEFAULT_ENCOUNTER);
				firstEntered = true;
			}
			else if (*m_mouseX >= 1445.0f && *m_mouseX <= 1920.0f && *m_mouseY >= 150.0f && *m_mouseY <= 250.0f)
			{
				if (playerSelectedItem())
				{
					if (m_flee)
						break;
					evaluateStatus(m_activeTrainerPokemon);
					handleFaint(*m_activeTrainerPokemon);
					evaluateStatus(m_activeAIPokemon);
					handleFaint(*m_activeAIPokemon);
					break;
				}
				m_renderer->setState(DEFAULT_ENCOUNTER);
				firstEntered = true;
			}
			else if (*m_mouseX >= 1445.0f && *m_mouseX <= 1920.0f && *m_mouseY >= 0.0f && *m_mouseY <= 150.0f)
			{
				if (runSuccesful())
					break;
				m_renderer->setState(DEFAULT_ENCOUNTER);
				firstEntered = true;
			}
		}

		

		firstEntered = false;
		onUpdate();
	}
}

bool Encounter::getAIAction()
{
	if (m_activeNPT == nullptr)
		calculateDamageTaken(*m_activeAIPokemon, *m_activeTrainerPokemon, m_activeAIPokemon->getAttack(m_activeAIPokemon->determineAttack(*m_activeTrainerPokemon)));
	else
	{
		int action = m_activeNPT->performAction(*m_activeAIPokemon, *m_activeTrainerPokemon, false);

		if (action >= 0 && action < 4)
		{
			//ATTACK
			calculateDamageTaken(*m_activeAIPokemon, *m_activeTrainerPokemon, m_activeAIPokemon->getAttack(action));
		}
		else if (action == 4)
		{
			//STRUGGLE
			calculateDamageTaken(*m_activeAIPokemon, *m_activeTrainerPokemon, m_activeAIPokemon->struggle());
		}
		else if (action == 5)
		{
			//HEAL
			Item* item = m_activeNPT->getNextHeal();
			useItem(m_activeNPT->nptResources, m_activeAIPokemon, *item);
			m_activeNPT->removeHeal();
		}
	}

	if (handleFaint(*m_activeTrainerPokemon))
		return true;
	else
		return false;
}

bool Encounter::playerSelectedMove()
{
	bool firstEntered = true;
	m_renderer->setState(SELECT_ATTACK);

	std::cout << "\n\nSelect Your Move\n" << std::endl;
	m_activeTrainerPokemon->printMoves();

	while (!glfwWindowShouldClose(m_window))
	{
		
		int move = 0;

		//Move Click
		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 505.0f && *m_mouseX <= 940.0f && *m_mouseY >= 145.0f && *m_mouseY <= 230.0f)
				move = 1;
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1415.0f && *m_mouseY >= 145.0f && *m_mouseY <= 230.0f)
				move = 2;
			else if (*m_mouseX >= 505.0f && *m_mouseX <= 940.0f && *m_mouseY >= 20.0f && *m_mouseY <= 105.0f)
				move = 3;
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1415.0f && *m_mouseY >= 20.0f && *m_mouseY <= 105.0f)
				move = 4;
			else
				return false;
		}

		

		if (move != 0)
		{
			bool struggle = false;

			if (m_activeTrainerPokemon->getAttack(move - 1).getCurrentPP() == 0)
			{
			
				struggle = m_activeTrainerPokemon->outOfMoves();

				if (!struggle)
				{
					std::cout << " You cannot use a move with 0pp" << std::endl;
					m_renderer->setTextBox("You cannot use a", "move with 0pp ");
					onUpdate();
					Sleep(1500);
					return false;
				}
			}


			if (m_activeTrainerPokemon->getSpeed() > m_activeAIPokemon->getSpeed())
			{
				//Heal Priority for AI
				if (m_activeNPT != nullptr)
					m_activeNPT->performAction(*m_activeAIPokemon, *m_activeTrainerPokemon, true);

				if (!struggle)
				{
					calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->getAttack(move - 1));
					recordAttack();
				}
				else
				{
					calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->struggle());
				}
			

				if (!handleFaint(*m_activeAIPokemon))
					getAIAction();
			}
			else if (m_activeAIPokemon->getSpeed() > m_activeTrainerPokemon->getSpeed())
			{
				if (!getAIAction())
				{
					if (!struggle)
					{
						calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->getAttack(move - 1));
						recordAttack();
					}
					else
					{
						calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->struggle());
					}

					handleFaint(*m_activeAIPokemon);
				}
			}
			else
			{
				if (odds(50))
				{
					if (m_activeNPT != nullptr)
						m_activeNPT->performAction(*m_activeAIPokemon, *m_activeTrainerPokemon, true);

					if (!struggle)
					{
						calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->getAttack(move - 1));
						recordAttack();
					}
					else
					{
						calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->struggle());
					}

					if (!handleFaint(*m_activeAIPokemon))
						getAIAction();
				}
				else
				{
					if (!getAIAction())
					{
						if (!struggle)
						{
							calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->getAttack(move - 1));
							recordAttack();
						}
						else
						{
							calculateDamageTaken(*m_activeTrainerPokemon, *m_activeAIPokemon, m_activeTrainerPokemon->struggle());
						}
						handleFaint(*m_activeAIPokemon);
					}
				}
			}

			return true;
		}

		firstEntered = false;
		onUpdate();
	}

	std::cout << "\nNo move selected\n" << std::endl;

	return false;
}

bool Encounter::playerSelecetedPokemon(bool fainted)
{
	bool keepGoing = false;
	for (int i = 0; i < 6; i++)
	{
		if (m_activeTrainer->getPokemon(i)->getLevel() != 0 && m_activeTrainer->getPokemon(i)->getHealth() != 0)
			keepGoing = true;
	}

	if (!keepGoing)
		return true;

	std::cout << "\n Select A Pokemon \n" << std::endl;

	m_activeTrainer->printPokemon();
	m_renderer->setState(SELECT_POKEMON);

	bool firstEntered = true;
	while (!glfwWindowShouldClose(m_window))
	{
		int selectedPokemon = 0;

		// Select Pokemon

		//TODO: Make for loop
		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 495.0f && *m_mouseX <= 940.0f)
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
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1425.0f)
			{
				if (*m_mouseY >= 627.5f && *m_mouseY <= 722.5f)
					selectedPokemon = 2;
				else if (*m_mouseY >= 492.5f && *m_mouseY <= 587.5f)
					selectedPokemon = 4;
				else if (*m_mouseY >= 357.5f && *m_mouseY <= 452.5f)
					selectedPokemon = 6;
				else
					return false;
			}
			else
				return false;
				
		}


		if (selectedPokemon >= 1 && selectedPokemon <= 6)
		{
			if (m_activeTrainer->getPokemon(selectedPokemon - 1)->getLevel() != 0 && m_activeTrainer->getPokemon(selectedPokemon - 1)->getHealth() != 0)
			{
				if (m_activeTrainer->getPokemon(selectedPokemon - 1) != m_activeTrainerPokemon)
				{
					std::cout << "\n" << m_activeTrainerPokemon->getName() << " withdraw for now.\n" << std::endl;
					m_activeTrainerPokemon = m_activeTrainer->getPokemon(selectedPokemon - 1);
					std::cout << m_activeTrainerPokemon->getName() << " I choose you!\n" << std::endl;

					m_trainerPokemonIndex = selectedPokemon - 1;
					m_renderer->setPokemon(m_activeTrainerPokemon, m_activeAIPokemon);

					if (!fainted)
						getAIAction();

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

	while (!glfwWindowShouldClose(m_window))
	{
		int selection = 0;

		int pokeballCount = m_activeTrainer->getUniquePokeballCount();
		int healCount = m_activeTrainer->getUniqueHealCount();
		int miscCount = m_activeTrainer->getUniqueMiscCount();

		//TODO: Maybe for loop this
		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 737.5f && *m_mouseX <= 1182.5f)
			{
				
				if (*m_mouseY >= 897.5f && *m_mouseY <= 992.5f)			// Up Arrow
				{
					if (bagIndex > 0)
					{
						bagIndex--;
						m_renderer->setBagIndex(bagIndex);
					}
				}
				else if (*m_mouseY >= 762.5f && *m_mouseY <= 857.5f)	//First Box
				{
					if (bagIndex + 1 <= pokeballCount + healCount + miscCount)
						selection = 1;
				}
				else if (*m_mouseY >= 627.5f && *m_mouseY <= 722.5f)	//Second Box
				{
					if (bagIndex + 2 <= pokeballCount + healCount + miscCount)
						selection = 2;
				}
				else if (*m_mouseY >= 492.5f && *m_mouseY <= 587.5f)	//Third Box
				{
					if (bagIndex + 3 <= pokeballCount + healCount + miscCount)
						selection = 3;
				}
				else if (*m_mouseY >= 357.5f && *m_mouseY <= 452.5f)	//Fourth Box
				{
					if (bagIndex + 4 <= pokeballCount + healCount + miscCount)
						selection = 4;
				}
				else if (*m_mouseY >= 222.5f && *m_mouseY <= 317.5f)	//Fifth Box
				{
					if (bagIndex + 5 <= pokeballCount + healCount + miscCount)
						selection = 5;
				}
				else if (*m_mouseY >= 87.5f && *m_mouseY <= 182.5f)		// Down Arrow
				{
					if (bagIndex + 5 < pokeballCount + healCount + miscCount)
					{
						bagIndex++;
						m_renderer->setBagIndex(bagIndex);
					}
				}
				else
				{
					return false;
				}
			
			}
			else
			{
				return false;
			}
		}

		

		if (selection > 0 && selection <= pokeballCount + healCount + miscCount)
		{
			Item* item = nullptr;
			if (selection > 0 && selection <= pokeballCount)
			{
				item = m_activeTrainer->getPokeball(selection - 1);
				caughtPokemon(*item);
				return true;
			}
			else if (selection > pokeballCount && selection <= pokeballCount + healCount)
			{
				item = m_activeTrainer->getHealItem(selection - 1 - pokeballCount);
				if (healedPokemon(*item))
					return true;
			}
			else
			{
				item = m_activeTrainer->getMiscItem(selection - 1 - pokeballCount - healCount);
				if (appliedItem(*item))
					return true;
			}

			return false;
		}

		firstEntered = false;
		onUpdate();
	}
}

bool Encounter::runSuccesful()
{
	if (m_activeNPT != nullptr)
	{
		std::cout << "You cannot run from a battle" << std::endl;
		m_renderer->setTextBox("You cannot run", "from a battle");
		onUpdate();
		Sleep(1500);
		return false;
	}

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
	getAIAction();

	//m_activeTrainerPokemon->evaluateStatus();
	evaluateStatus(m_activeTrainerPokemon);
	handleFaint(*m_activeTrainerPokemon);
	//m_activeAIPokemon->evaluateStatus();
	evaluateStatus(m_activeAIPokemon);
	handleFaint(*m_activeAIPokemon);

	return false;
}

bool Encounter::handleFaint(Pokemon& pokemon)
{
	if (!pokemon.hasFainted())
		return false;
	
	if( &pokemon == m_activeAIPokemon )
	{
		m_renderer->setState(DEFAULT_ENCOUNTER);
		int xpGain = calculateXPGain(pokemon);

		for (int i = 0; i < m_xpRecords.at(m_AIPokemonIndex).size(); i++)
		{
			animateXPGain(m_activeTrainer->getPokemon(m_xpRecords.at(m_AIPokemonIndex).at(i)), xpGain);
		}

		if (m_activeNPT != nullptr)
			swapAIPokemon();

		return true;
	}
	else
	{
		std::cout << m_activeTrainerPokemon->getName() << " has fainted" << std::endl;

		removeAttackRecord();

		//TODO: Compress while loop here
		while (true)
		{
			if (playerSelecetedPokemon(true))
				return true;
		}
	}
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
	int currentLevel = pokemon->getLevel();

	std::string nameGained = pokemon->getName() + " gained";
	std::string xpAmount = std::to_string(xpGain) + " EXP";

	m_renderer->setTextBox(nameGained, xpAmount);

	for (int i = 0; i < xpGain; i++)
	{
		if (pokemon->getLevel() == 100)
			return;

		pokemon->gainXP(1);

		if (pokemon->getLevel() != currentLevel)
		{
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

	if ((item.isRevive() && pokemon->getHealth() != 0) || (!item.isRevive() && pokemon->getHealth() == 0))
		return false;

	if (!item.isRevive() && item.getHealAmount() == 0 && pokemon->getStatus() != item.getStatus())
		return false;

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

}

void Encounter::swapAIPokemon()
{
	if (m_activeNPT == nullptr || m_AIPokemonIndex == 6)
		return;

	if (m_activeNPT->nptResources.getPokemon(m_AIPokemonIndex + 1)->getLevel() == 0)
		return;

	m_AIPokemonIndex += 1;
	m_activeAIPokemon = m_activeNPT->nptResources.getPokemon(m_AIPokemonIndex);
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

bool Encounter::caughtPokemon(Item& item)
{
	//TODO: Implement Shake
	if (m_activeNPT != nullptr)
	{
		std::cout << " No Stealing Pokemon from Trainers!" << std::endl;
		m_renderer->setTextBox("No Stealing Pokemon", "from Trainers");
		onUpdate();
		Sleep(1500);

		return false;
	}

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

bool Encounter::healedPokemon(Item& item)
{
	std::cout << "Using " << item.getName() << std::endl;

	m_activeTrainer->printPokemon();

	bool firstEntered = true;
	int selectedPokemon = 0;

	m_renderer->setState(SELECT_POKEMON);

	while (!glfwWindowShouldClose(m_window))
	{
		int selectedPokemon = 0;

		// Select Pokemon
		if (*m_clicked && !firstEntered)
		{
			if (*m_mouseX >= 495.0f && *m_mouseX <= 940.0f)
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
			else if (*m_mouseX >= 980.0f && *m_mouseX <= 1425.0f)
			{
				if (*m_mouseY >= 627.5f && *m_mouseY <= 722.5f)
					selectedPokemon = 2;
				else if (*m_mouseY >= 492.5f && *m_mouseY <= 587.5f)
					selectedPokemon = 4;
				else if (*m_mouseY >= 357.5f && *m_mouseY <= 452.5f)
					selectedPokemon = 6;
				else
					return false;
			}
			else
				return false;

		}

		if (selectedPokemon >= 1 && selectedPokemon <= 6 && m_activeTrainer->getPokemon(selectedPokemon - 1)->getLevel() != 0)
		{
			//m_activeTrainer->getPokemon(selectedPokemon - 1)->usedItem(m_activeTrainer->getName(), item);
			if (!useItem(*m_activeTrainer, m_activeTrainer->getPokemon(selectedPokemon - 1), item))
				return false;
			m_activeTrainer->removeItem(item);
			getAIAction();
			return true;
		}

		firstEntered = false;
		onUpdate();
	}
	return false;
}

bool Encounter::appliedItem(Item& item)
{
	std::cout << "Using " << item.getName() << std::endl;
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
}