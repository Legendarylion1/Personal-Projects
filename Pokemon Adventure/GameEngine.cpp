#include "GameEngine.h"

GameEngine::GameEngine():
	m_trainer("Trainer")
{
}

bool GameEngine::setup()
{
	//TODO: Check for shader Errors on startup
	//TODO: Make sure that the PC Save file is there


	/* Initialize the library */
	if (!glfwInit())
		return false;
	
	/* Create a windowed mode window and its OpenGL context */
	
	m_window = glfwCreateWindow(1920, 1080, "Hello World", glfwGetPrimaryMonitor(), NULL);
	//m_window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!m_window)
	{
		return false;
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW ERROR" << std::endl;
		return false;
	}

	m_pc.loadPC(m_trainer, true);
	initPlayerPosition();

	m_renderer.setup(m_window);
	m_encounter.setup(m_window, &m_renderer, &m_input, &m_clicked, &m_mouseX, &m_mouseY);
	m_input.setup(m_window, &m_clicked, &m_mouseX, &m_mouseY, &m_upPressed, &m_downPressed, &m_leftPressed, &m_rightPressed, &m_interactPressed, &m_escapePressed);
	m_gameMap.setup(&m_upPressed, &m_downPressed, &m_leftPressed, &m_rightPressed, &m_interactPressed, &m_renderer);
	m_cutscene.setup(&m_renderer, &m_encounter);



	m_renderer.setState(DISPLAY_MAP);
	m_renderer.setTrainer(&m_trainer);
	m_gameMap.setNptData(m_pc.getNptData());

	return true;
}

bool GameEngine::run()
{

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (m_escapePressed)
			handleEscape();

		handleEvents( m_gameMap.pollEvents() );

		onUpdate();
	}

	return true;
}

bool GameEngine::shutdown()
{
	m_renderer.shutdown();
	glfwTerminate();
	return true;
}

void GameEngine::onUpdate()
{
	m_input.onUpdate();
	m_renderer.onUpdate();
}

/// <summary>
/// Sets the player's position in the world.
/// Needs to be run before any setup and after loading the PC.
/// This is because we need to tell the gameMap class whether or not the player is in a building before setup.
/// Can be changed to work after, but I currently don't do it that way.
/// </summary>
void GameEngine::initPlayerPosition()
{
	m_gameMap.setCurrentMap(m_pc.getPlayerLocation().at(2));

	setPlayerPosition(m_pc.getPlayerLocation().at(0), m_pc.getPlayerLocation().at(1));

	m_playerDirection = m_pc.getPlayerLocation().at(3);

	m_gameMap.setBuildingEvent(m_pc.getPlayerLocation().at(4));

	m_renderer.setPlayerAnimation(m_playerDirection, SpriteState::IDLE);

	m_cutscene.setCutsceneCount(m_pc.getPlayerLocation().at(5));
}

void GameEngine::handleEvents(std::vector<unsigned int> events)
{
	m_inGrass = false;
	for (int i = 0; i < events.size(); i++)
	{
		if (events.at(i) == Events::inGrass)
		{
			m_inGrass = true;
		}
		else if (events.at(i) == Events::movedUp)
		{
			movePlayerUp();
		}
		else if (events.at(i) == Events::movedDown)
		{
			movePlayerDown();
		}
		else if (events.at(i) == Events::movedLeft)
		{
			movePlayerLeft();
		}
		else if (events.at(i) == Events::movedRight)
		{
			movePlayerRight();
		}
		else if (events.at(i) == Events::turnUp)
		{
			turnPlayer(Direction::UP);
		}
		else if (events.at(i) == Events::turnDown)
		{
			turnPlayer(Direction::DOWN);
		}
		else if (events.at(i) == Events::turnLeft)
		{
			turnPlayer(Direction::LEFT);
		}
		else if (events.at(i) == Events::turnRight)
		{
			turnPlayer(Direction::RIGHT);
		}
		else if (events.at(i) == Events::transferUp)
		{
			transferMaps(Direction::UP);
		}
		else if (events.at(i) == Events::transferDown)
		{
			transferMaps(Direction::DOWN);
		}
		else if (events.at(i) == Events::transferLeft)
		{
			transferMaps(Direction::LEFT);
		}
		else if (events.at(i) == Events::transferRight)
		{
			transferMaps(Direction::RIGHT);
		}
		else if (events.at(i) == Events::trainerSpotted)
		{
			attemptEncounter(false);
		}
		else if (events.at(i) == Events::pokeCenter)
		{
			transferBuilding(true);
		}
		else if (events.at(i) == Events::returnSection)
		{
			transferReturn();
		}
		else if (events.at(i) == Events::interactPC)
		{
			usePC();
		}
		else if (events.at(i) == Events::interactNurse)
		{
			nurseHeal();
		}
		else if (events.at(i) == Events::pokeShop)
		{
			transferBuilding(false);
		}
		else if (events.at(i) == Events::interactItemBuy)
		{
			buyItem();
		}
		else if (events.at(i) == Events::interactTrainer)
		{
			interactNPT();
		}
		else if (events.at(i) == Events::startCutScene)
		{
			if (m_cutscene.storyCutscene(m_gameMap.getMapSection()))
				m_pc.setCutsceneCount(m_cutscene.getCutsceneCount());
		}
	}

	if (m_inGrass)
		attemptEncounter(true);

}

void GameEngine::handleEscape()
{
	m_renderer.setState(DISPLAY_ESCAPE);
	m_clicked = false;
	m_escapePressed = false;

	while (true)
	{
		//if (m_escapePressed)
		//	break;

		if (m_clicked)
		{

			if (m_mouseX >= 760.0f && m_mouseX <= 1160.0f && m_mouseY >= 865.0f && m_mouseY <= 1015.0f)
			{
				selectPokemon(true);
				m_clicked = false;
				m_renderer.setState(DISPLAY_ESCAPE);
				continue;
			}
			if (m_mouseX >= 760.0f && m_mouseX <= 1160.0f && m_mouseY >= 665.0f && m_mouseY <= 815.0f)
			{
				std::cout << "Bag" << std::endl;

				useItem();
				m_clicked = false;
				m_renderer.setState(DISPLAY_ESCAPE);
				continue;

			}
			if (m_mouseX >= 760.0f && m_mouseX <= 1160.0f && m_mouseY >= 465.0f && m_mouseY <= 615.0f)
			{
				std::cout << "Save" << std::endl;

				m_pc.setPlayerPosition(m_gameMap.getMapID(), m_gameMap.getPlayerPosition().x, m_gameMap.getPlayerPosition().y, m_playerDirection);
				m_pc.setNptData(m_gameMap.getNptData());
				m_pc.savePC(m_trainer);
				break;
			}
			if (m_mouseX >= 760.0f && m_mouseX <= 1160.0f && m_mouseY >= 265.0f && m_mouseY <= 415.0f)
			{
				//TODO:: Implement
				//Auto Save as a setting
				std::cout << "Settings" << std::endl;

			}
			if (m_mouseX >= 760.0f && m_mouseX <= 1160.0f && m_mouseY >= 65.0f && m_mouseY <= 215.0f)
			{
				glfwSetWindowShouldClose(m_window, GLFW_TRUE);
				break;
			}

			break;
		}
		
		

		onUpdate();
	}

	m_renderer.setState(DISPLAY_MAP);
}

void GameEngine::updateGrassTiles()
{
	if (m_inGrass)
		m_renderer.setGrassPosition(m_gameMap.getPlayerPosition().x, m_gameMap.getPlayerPosition().y);
	else
		m_renderer.setGrassPosition(-1.0f, -1.0f);
}

bool GameEngine::attemptEncounter(bool isPokemon, int nptID)
{
	std::cout << "encounter being attempted\n";
	if (isPokemon)
	{
		if (odds(5))
		{
			int speciesIndex = rand() % m_gameMap.getMapSpecies().size();
			int pokemonLevel = rand() % m_gameMap.getMapLevelCap() + 3;

			Pokemon wildPokemon = Pokemon(id_to_species[m_gameMap.getMapSpecies().at(speciesIndex)], pokemonLevel);
			wildPokemon.randomizeAttacks();

			m_encounter.setupEncounter(m_trainer, wildPokemon, m_pc);
			m_encounter.beginEncounter();
			m_encounter.clearEncounter();
		}
	}
	else
	{

		if (nptID == -1)
		{
			m_cutscene.spottedTrainer(m_gameMap.getNPT(), m_gameMap.getPlayerPosition().x, m_gameMap.getPlayerPosition().y);
			m_encounter.setupEncounter(m_trainer, m_gameMap.getNPT());
		}
		else
		{
			m_encounter.setupEncounter(m_trainer, m_gameMap.getNPT(nptID));
		}

		m_cutscene.nptDialogue(m_gameMap.getNPT());
		m_encounter.beginEncounter();
		m_encounter.clearEncounter();
	}
	return false;
}

void GameEngine::movePlayerUp()
{
	if (m_playerDirection != Direction::UP)
	{
		turnPlayer(Direction::UP);
		return;
	}
	m_gameMap.adjustPlayerPosition(0, 1);
	float oldY = m_playerY;
	bool firstEntered = true;
	bool stepped = false;

	m_lastTime = 0.0f;
	while (m_playerY < oldY + (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (m_playerY + ((TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime) * m_playerSpeed > oldY + (TILE_SIZE * TILE_MULTIPLIER))
			m_playerY = oldY + (TILE_SIZE * TILE_MULTIPLIER);
		else
			m_playerY += (TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime * m_playerSpeed;

		firstEntered = false;



		//Animation
		if (!stepped && m_playerY >= oldY + ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (m_rightFoot)
			{
				m_renderer.setPlayerAnimation(Direction::UP, SpriteState::STEP1);

				m_rightFoot = false;
				stepped = true;
			}
			else
			{
				m_renderer.setPlayerAnimation(Direction::UP, SpriteState::STEP2);
				m_rightFoot = true;
				stepped = true;
			}
		}
		else if (m_playerY >= oldY + ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			m_renderer.setPlayerAnimation(Direction::UP, SpriteState::IDLE);
		}

		m_renderer.setPlayerCoords(m_playerX, m_playerY);
		m_renderer.onUpdate();
	}
	updateGrassTiles();
}

void GameEngine::movePlayerDown()
{
	if (m_playerDirection != Direction::DOWN)
	{
		turnPlayer(Direction::DOWN);
		return;
	}
	m_gameMap.adjustPlayerPosition(0, -1);
	updateGrassTiles();
	float oldY = m_playerY;
	bool firstEntered = true;
	bool stepped = false;

	m_lastTime = 0.0f;
	while (m_playerY > oldY - (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (m_playerY - ((TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime) * m_playerSpeed < oldY - (TILE_SIZE * TILE_MULTIPLIER))
			m_playerY = oldY - (TILE_SIZE * TILE_MULTIPLIER);
		else
			m_playerY -= (TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime * m_playerSpeed;

		firstEntered = false;



		//Animation
		if (!stepped && m_playerY <= oldY - ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (m_rightFoot)
			{
				m_renderer.setPlayerAnimation(Direction::DOWN, SpriteState::STEP1);

				m_rightFoot = false;
				stepped = true;
			}
			else
			{
				m_renderer.setPlayerAnimation(Direction::DOWN, SpriteState::STEP2);
				m_rightFoot = true;
				stepped = true;
			}
		}
		else if (m_playerY <= oldY - ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			m_renderer.setPlayerAnimation(Direction::DOWN, SpriteState::IDLE);
		}

		m_renderer.setPlayerCoords(m_playerX, m_playerY);
		m_renderer.onUpdate();
	}
}

void GameEngine::movePlayerLeft()
{
	if (m_playerDirection != Direction::LEFT)
	{
		turnPlayer(Direction::LEFT);
		return;
	}
	m_gameMap.adjustPlayerPosition(-1, 0);
	updateGrassTiles();
	float oldX = m_playerX;
	bool firstEntered = true;
	bool stepped = false;

	m_lastTime = 0.0f;
	while (m_playerX > oldX - (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (m_playerX - ((TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime) * m_playerSpeed < oldX - (TILE_SIZE * TILE_MULTIPLIER))
			m_playerX = oldX - (TILE_SIZE * TILE_MULTIPLIER);
		else
			m_playerX -= (TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime * m_playerSpeed;

		firstEntered = false;



		//Animation
		if (!stepped && m_playerX <= oldX - ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (m_rightFoot)
			{
				m_renderer.setPlayerAnimation(Direction::LEFT, SpriteState::STEP1);

				m_rightFoot = false;
				stepped = true;
			}
			else
			{
				m_renderer.setPlayerAnimation(Direction::LEFT, SpriteState::STEP2);
				m_rightFoot = true;
				stepped = true;
			}
		}
		else if (m_playerX <= oldX - ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			m_renderer.setPlayerAnimation(Direction::LEFT, SpriteState::IDLE);
		}

		m_renderer.setPlayerCoords(m_playerX, m_playerY);
		m_renderer.onUpdate();
	}
}

void GameEngine::movePlayerRight()
{
	if (m_playerDirection != Direction::RIGHT)
	{
		turnPlayer(Direction::RIGHT);
		return;
	}
	m_gameMap.adjustPlayerPosition(1, 0);
	updateGrassTiles();
	float oldX = m_playerX;
	bool firstEntered = true;
	bool stepped = false;

	m_lastTime = 0.0f;
	while (m_playerX < oldX + (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (m_playerX + ((TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime) * m_playerSpeed > oldX + (TILE_SIZE * TILE_MULTIPLIER))
			m_playerX = oldX + (TILE_SIZE * TILE_MULTIPLIER);
		else
			m_playerX += (TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime * m_playerSpeed;

		firstEntered = false;



		//Animation
		if (!stepped && m_playerX >= oldX + ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (m_rightFoot)
			{
				m_renderer.setPlayerAnimation(Direction::RIGHT, SpriteState::STEP1);

				m_rightFoot = false;
				stepped = true;
			}
			else
			{
				m_renderer.setPlayerAnimation(Direction::RIGHT, SpriteState::STEP2);
				m_rightFoot = true;
				stepped = true;
			}
		}
		else if (m_playerX >= oldX + ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			m_renderer.setPlayerAnimation(Direction::RIGHT, SpriteState::IDLE);
		}

		m_renderer.setPlayerCoords(m_playerX, m_playerY);
		m_renderer.onUpdate();
	}
}

void GameEngine::setPlayerPosition(int x, int y)
{
	m_playerX = 0;
	m_playerY = 0;
	m_gameMap.setPlayerPosition(0, 0);

	for (int i = 0; i < x; i++)
	{
		m_playerX += (TILE_SIZE * TILE_MULTIPLIER);
		m_gameMap.adjustPlayerPosition(1, 0);
	}

	for (int i = 0; i < y; i++)
	{
		m_playerY += (TILE_SIZE * TILE_MULTIPLIER);
		m_gameMap.adjustPlayerPosition(0, 1);
	}

	m_renderer.setPlayerCoords(m_playerX, m_playerY);
}

void GameEngine::turnPlayer(unsigned int direction)
{
	if (m_playerDirection == direction)
		return;

	float oldY = m_playerY;
	float newY = m_playerY;
	bool firstEntered = true;
	bool turned = false;

	while (newY < oldY + (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (newY + ((TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime) * m_playerSpeed * m_turnSpeed > oldY + (TILE_SIZE * TILE_MULTIPLIER))
			newY = oldY + (TILE_SIZE * TILE_MULTIPLIER);
		else
			newY += (TILE_SIZE * TILE_MULTIPLIER) * m_deltaTime * m_playerSpeed * m_turnSpeed;

		firstEntered = false;

		if (!turned && newY >= oldY + ((TILE_SIZE * TILE_MULTIPLIER) * (2.0f / 4.0f)))
		{
			turned = true;
			m_renderer.setPlayerAnimation(direction, SpriteState::IDLE);
			onUpdate();
		}
	}

	m_playerDirection = direction;
	m_gameMap.adjustPlayerDirection(m_playerDirection);
	m_renderer.setPlayerAnimation(direction, SpriteState::IDLE);
	onUpdate();

}

void GameEngine::transferMaps(unsigned int direction)
{
	glm::vec2 playerPosition = m_gameMap.swapMapSections(direction, &m_renderer);

	setPlayerPosition(playerPosition.x, playerPosition.y);
}

void GameEngine::transferBuilding(bool PokeCenter)
{
	if (PokeCenter)
	{
		glm::vec2 playerPosition = m_gameMap.swapPokeCenter(&m_renderer);
		m_pc.setBuildingEvent(Events::pokeCenter);

		setPlayerPosition(playerPosition.x, playerPosition.y);
	}
	else
	{
		glm::vec2 playerPosition = m_gameMap.swapPokeShop(&m_renderer);
		m_pc.setBuildingEvent(Events::pokeShop);

		setPlayerPosition(playerPosition.x, playerPosition.y);
	}
}

void GameEngine::transferReturn()
{

	glm::vec2 playerPosition = m_gameMap.returnFromBuilding(&m_renderer);
	m_pc.setBuildingEvent(Events::inGrass);

	setPlayerPosition(playerPosition.x, playerPosition.y);

}

void GameEngine::nurseHeal()
{
	// TODO: Save after healing with nurse
	// Find the count of the pokeballs
	//		- Were gonna place pokeballs down every half step

	float oldValue= 0;
	float newValue = 0;

	
	bool firstEntered = true;

	unsigned int pokeballCount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (m_trainer.getPokemon(i)->getLevel() != 0)
			pokeballCount += 1;
	}
	pokeballCount -= 1;

	// Pokeballs placed will always be atleast one
	unsigned int pokeballsPlaced = 1;

	std::cout << "First Pokeball Placed" << std::endl;
	m_renderer.setRosterSize(pokeballsPlaced);

	// Place all of the pokeballs
	// Each pokeball is placed in half of the walk distance time


	//Place Pokeballs

	while (newValue < oldValue + (((TILE_SIZE * TILE_MULTIPLIER)/2 ) * pokeballCount) )
	{
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (newValue + ((((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount) * m_deltaTime) > oldValue + (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount))
			newValue = oldValue + (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount);
		else
			newValue += (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount) * m_deltaTime;


		if (newValue >= oldValue + (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballsPlaced))
		{
			pokeballsPlaced += 1;
			m_renderer.setRosterSize(pokeballsPlaced);
			std::cout << "Another Pokeball Placed: "<< pokeballsPlaced << std::endl;
		}

		firstEntered = false;
		onUpdate();
	}


	// Pause for animation
	pokeballCount = 30;
	newValue = 0;
	firstEntered = true;

	while (newValue < oldValue + (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount))
	{
		float curTime = (float)glfwGetTime();
		m_deltaTime = curTime - m_lastTime;
		m_lastTime = curTime;

		if (firstEntered)
			m_deltaTime = 0.0f;

		if (newValue + ((((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount) * m_deltaTime) > oldValue + (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount))
			newValue = oldValue + (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount);
		else
			newValue += (((TILE_SIZE * TILE_MULTIPLIER) / 2) * pokeballCount) * m_deltaTime;

		firstEntered = false;
		onUpdate();
	}


	//Heal
	for (int i = 0; i < 6; i++)
	{
		m_trainer.getPokemon(i)->giveHP(1000);
		m_trainer.getPokemon(i)->setStatus(&id_to_status[statusIDs::null]);
	}

	m_renderer.setRosterSize(0);
}

void GameEngine::usePC()
{
	//TODO: Hard code a value for box cap for these box swaps
	unsigned int currentBox = 0;

	unsigned int selectedBox = 0;
	unsigned int selectedPokemon = 100;


	bool firstEntered = true;
	//TODO: Determine whether or not to move this to the PC class
	m_renderer.setState(DISPLAY_PC);
	m_renderer.setBoxPokemon(m_pc.getBox(currentBox));
	m_renderer.setBoxName(m_pc.getBoxName(currentBox));

	while (true)
	{
		//TODO: Add a visual to show that a box has been selected
		bool boxLeft = false;
		bool boxRight = false;
		bool clickedPokemon = false;

		if (m_clicked && !firstEntered)
		{	

			// Swap Box Click | Triangle Click
			if (m_mouseY >= (bannerCenterY - bannerHeight) && m_mouseY <= (bannerCenterY + bannerHeight))
			{
				if (m_mouseX >= (bannerCenterX - bannerWidth - 200.0f) && m_mouseX <= (bannerCenterX - bannerWidth - 100.0f))
				{
					boxLeft = true;
				}
				else if (m_mouseX >= (bannerCenterX + bannerWidth + 100.0f) && m_mouseX <= (bannerCenterX + bannerWidth + 200.0f))
				{
					boxRight = true;
				}
				else
				{
					break;
				}
			}
			


			// Check for box click
			int boxIndex = 0;

			for (int x = 0; x < boxesWide; x++)
			{
				for (int y = 0; y < boxesTall; y++)
				{

					if (m_mouseX >= boxX + (hSpacing * x) && m_mouseX <= boxX + boxWidth + (hSpacing * x))
					{
						if (m_mouseY >= boxY - (vSpacing * y) && m_mouseY <= boxY + boxHeight - (vSpacing * y))
						{
							if (selectedPokemon != 100)
							{
								swapPCPokemon(selectedBox, selectedPokemon, currentBox, boxIndex, currentBox);
								clickedPokemon = true;
								selectedPokemon = 100;
							}
							else
							{
								selectedPokemon = boxIndex;
								selectedBox = currentBox;
								clickedPokemon = true;
							}
							//TODO: This break doesnt really solve anything
							break;
						}
					}

					boxIndex++;
				}
			}




			// Check for roster click
			float yIncrease = 0;
			unsigned int rosterIndex = 0;
			for (int x = 0; x < 2; x++)
			{
				if (x == 1)
				{
					yIncrease = (-1.0f * playerPokemonHeight) / 4;
				}

				for (int y = 0; y < 3; y++)
				{
					
					if (m_mouseX >= playerPokemonStartingX + (x * playerHSpacing) && m_mouseX <= playerPokemonStartingX + playerPokemonWidth + (x * playerHSpacing))
					{
						if (m_mouseY >= playerPokemonStartingY - ((y * playerVSpacing) + yIncrease) && m_mouseY <= playerPokemonStartingY + playerPokemonHeight - ((y * playerVSpacing) + yIncrease))
						{
							if (selectedPokemon != 100)
							{
								swapPCPokemon(selectedBox, selectedPokemon, currentBox, rosterIndex + 20, currentBox);
								clickedPokemon = true;
								selectedPokemon = 100;
							}
							else
							{
								selectedPokemon = rosterIndex + 20;
								selectedBox = currentBox;
								clickedPokemon = true;
							}
						}
					}


					rosterIndex++;
				}
			}



			// Check for exit
			if (!boxLeft && !boxRight && !clickedPokemon)
			{
				if (selectedPokemon == 100)
					break;

				selectedPokemon = 100;
			}
		}


		if (boxLeft)
		{
			if (currentBox == 0)
				currentBox = 7;
			else
				currentBox--;

			m_renderer.setBoxPokemon(m_pc.getBox(currentBox));
			m_renderer.setBoxName(m_pc.getBoxName(currentBox));

			firstEntered = true;
		}
		else if (boxRight)
		{
			if (currentBox == 7)
				currentBox = 0;
			else
				currentBox++;

			m_renderer.setBoxPokemon(m_pc.getBox(currentBox));
			m_renderer.setBoxName(m_pc.getBoxName(currentBox));
			firstEntered = true;
		}
		else if (clickedPokemon)
		{
			firstEntered = true;
		}
		else
		{
			firstEntered = false;
		}

		onUpdate();
	}

	m_renderer.setState(DISPLAY_MAP);
}

void GameEngine::buyItem()
{
	std::vector<std::string> itemNames;
	std::vector<unsigned int> itemsAvailable = m_gameMap.getMapItems();

	for (int i = 0; i < itemsAvailable.size(); i++)
	{
		itemNames.push_back(id_to_item[itemsAvailable.at(i)].getName() + "     " + std::to_string(id_to_item[itemsAvailable.at(i)].getPrice()));
	}
	m_renderer.setAvailableItems(itemNames);

	bool firstEntered = true;
	bool selectionMade = false;
	unsigned int bagIndex = 0;
	int selectedItem = -1;

	m_renderer.setState(DISPLAY_BUY_ITEMS);
	m_renderer.setBagIndex(bagIndex);

	

	while (true)
	{
		if (m_clicked && !firstEntered)
		{
			//Triangle Clicks
			if (m_mouseX >= 1425 && m_mouseX <= 1590)
			{
				if (m_mouseY >= 990 && m_mouseY <= 1035)
				{
					//Top Button
					if (bagIndex > 0)
					{
						bagIndex--;
						m_renderer.setBagIndex(bagIndex);
					}
					selectionMade = true;
				}
				else if (m_mouseY >= (HEIGHT - 675) - 45 && m_mouseY <= (HEIGHT - 675))
				{
					//Bottom Button
					if (bagIndex + 6 < itemsAvailable.size())
					{
						bagIndex++;
						m_renderer.setBagIndex(bagIndex);
					}
					selectionMade = true;
				}
			}

			//Item Clicks
			for (int i = 0; i < 6; i++)
			{
				if (m_mouseX >= WIDTH - 30 - 735  && m_mouseX <= WIDTH - 30)
				{
					if (m_mouseY >= (HEIGHT - 120 - 75) - (i * 90) && m_mouseY <= (HEIGHT - 120) - (i * 90))
					{
						selectedItem = bagIndex + i;
						selectionMade = true;
					}
				}
			}

			if (!selectionMade)
			{
				break;
			}
		}


		if (selectionMade)
		{
			if (selectedItem != -1)
			{

				if (selectedItem + bagIndex < itemsAvailable.size())
				{
					if (m_trainer.getMoneyBalance() >= id_to_item[selectedItem + bagIndex].getPrice())
					{
						m_trainer.takeMoney(id_to_item[selectedItem + bagIndex].getPrice());

						m_trainer.addItem(id_to_item[selectedItem + bagIndex]);
					}
				}

				selectedItem = -1;
			}

			selectionMade = false;
			firstEntered = true;
		}
		else
		{
			firstEntered = false;
		}
		onUpdate();
	}

	m_renderer.setState(DISPLAY_MAP);
}

void GameEngine::interactNPT()
{
	NPT& npt = m_gameMap.getNPT();

	//Turn NPT to face the trainer
	if (m_playerDirection == Direction::UP)
		npt.setDirection(Direction::DOWN);
	else if (m_playerDirection == Direction::DOWN)
		npt.setDirection(Direction::UP);
	else if (m_playerDirection == Direction::LEFT)
		npt.setDirection(Direction::RIGHT);
	else if (m_playerDirection == Direction::RIGHT)
		npt.setDirection(Direction::LEFT);

	onUpdate();

	if (npt.nptResources.hasPokemon())
		attemptEncounter(false,m_gameMap.getNptID(npt));
	else
	{
		std::cout << "[Game Engine] npt has no pokemon\n";
		m_cutscene.nptDialogue(m_gameMap.getNPT());
	}
}

unsigned int GameEngine::selectPokemon(bool swapPokemon)
{

	bool firstEntered = true;

	unsigned int selectedIndex = 7;
	unsigned int selectedPokemon = 7;

	m_renderer.setState(SELECT_POKEMON);
	m_renderer.setRosterIndex(selectedIndex);

	onUpdate();

	while (true)
	{
		if (m_clicked && !firstEntered)
		{
			if (m_mouseX >= 495.0f && m_mouseX <= 940.0f)
			{
				if (m_mouseY >= 627.5f && m_mouseY <= 722.5f)
					selectedPokemon = 0;
				else if (m_mouseY >= 492.5f && m_mouseY <= 587.5f)
					selectedPokemon = 2;
				else if (m_mouseY >= 357.5f && m_mouseY <= 452.5f)
					selectedPokemon = 4;
			}
			else if (m_mouseX >= 980.0f && m_mouseX <= 1425.0f)
			{
				if (m_mouseY >= 627.5f && m_mouseY <= 722.5f)
					selectedPokemon = 1;
				else if (m_mouseY >= 492.5f && m_mouseY <= 587.5f)
					selectedPokemon = 3;
				else if (m_mouseY >= 357.5f && m_mouseY <= 452.5f)
					selectedPokemon = 5;
			}

			if (!swapPokemon)
			{
				m_renderer.setRosterIndex(7);
				return selectedPokemon;
			}
			else if (swapPokemon && selectedPokemon == 7)
			{
				if (selectedIndex == 7)
				{
					m_renderer.setRosterIndex(7);
					return selectedPokemon;
				}
				else
					selectedIndex == 7;
			}
		}

		if (selectedPokemon != 7)
		{
			if (selectedIndex != 7)
			{
				m_trainer.swapPokemon(selectedIndex, selectedPokemon);
				selectedPokemon = 7;
				selectedIndex = 7;
				m_renderer.setRosterIndex(selectedIndex);
			}
			else
			{
				selectedIndex = selectedPokemon;

				m_renderer.setRosterIndex(selectedIndex);
				selectedPokemon = 7;
			}
		}


		firstEntered = false;
		onUpdate();
	}

	return selectedPokemon;
}

void GameEngine::useItem()
{
	bool firstEntered = true;
	unsigned int bagIndex = 0;
	unsigned int selection = 0;

	m_renderer.setState(SELECT_ITEM);
	m_renderer.setBagIndex(bagIndex);
	onUpdate();

	while (true)
	{
		int pokeballCount = m_trainer.getUniquePokeballCount();
		int healCount = m_trainer.getUniqueHealCount();
		int miscCount = m_trainer.getUniqueMiscCount();

		//TODO: Maybe for loop this
		if (m_clicked && !firstEntered)
		{
			if (m_mouseX >= 737.5f && m_mouseX <= 1182.5f)
			{

				if (m_mouseY >= 897.5f && m_mouseY <= 992.5f)			// Up Arrow
				{
					if (bagIndex > 0)
					{
						bagIndex--;
						m_renderer.setBagIndex(bagIndex);
					}
				}
				else if (m_mouseY >= 762.5f && m_mouseY <= 857.5f)	//First Box
				{
					if (bagIndex + 1 <= pokeballCount + healCount + miscCount)
						selection = 1;
				}
				else if (m_mouseY >= 627.5f && m_mouseY <= 722.5f)	//Second Box
				{
					if (bagIndex + 2 <= pokeballCount + healCount + miscCount)
						selection = 2;
				}
				else if (m_mouseY >= 492.5f && m_mouseY <= 587.5f)	//Third Box
				{
					if (bagIndex + 3 <= pokeballCount + healCount + miscCount)
						selection = 3;
				}
				else if (m_mouseY >= 357.5f && m_mouseY <= 452.5f)	//Fourth Box
				{
					if (bagIndex + 4 <= pokeballCount + healCount + miscCount)
						selection = 4;
				}
				else if (m_mouseY >= 222.5f && m_mouseY <= 317.5f)	//Fifth Box
				{
					if (bagIndex + 5 <= pokeballCount + healCount + miscCount)
						selection = 5;
				}
				else if (m_mouseY >= 87.5f && m_mouseY <= 182.5f)		// Down Arrow
				{
					if (bagIndex + 5 < pokeballCount + healCount + miscCount)
					{
						bagIndex++;
						m_renderer.setBagIndex(bagIndex);
					}
				}
				else
				{
					return;
				}

			}
			else
			{
				return;
			}
		}


		// Select Pokemon To apply to
		// TODO: Maybe allow for held items but for now we only take in heal items
		if (selection > 0 && selection <= pokeballCount + healCount + miscCount)
		{
			Item* item = nullptr;

			if (selection > pokeballCount && selection <= pokeballCount + healCount)
			{
				item = m_trainer.getHealItem(selection - 1 - pokeballCount);


				unsigned int pokemonToHeal = selectPokemon(false);

				if (pokemonToHeal != 7 && m_trainer.getPokemon(pokemonToHeal)->getLevel() != 0)
				{

					if (item->isRevive())
					{
						for (int i = 0; i < m_trainer.getPokemon(pokemonToHeal)->getMaxHealth() / 2; i++)
						{
							m_trainer.getPokemon(pokemonToHeal)->giveHP(1);
							onUpdate();
						}
					}

					for (int i = 0; i < item->getHealAmount(); i++)
					{
						if (m_trainer.getPokemon(pokemonToHeal)->getHealth() == m_trainer.getPokemon(pokemonToHeal)->getMaxHealth())
							break;
						m_trainer.getPokemon(pokemonToHeal)->giveHP(1);
						onUpdate();
					}

					if (&item->getStatus() != NULL && m_trainer.getPokemon(pokemonToHeal)->getStatus().getID() != statusIDs::null && m_trainer.getPokemon(pokemonToHeal)->getStatus().getID() == item->getStatus().getID())
					{
						std::cout << m_trainer.getPokemon(pokemonToHeal)->getName() << " has been healed of its" << item->getName() << std::endl;
						m_trainer.getPokemon(pokemonToHeal)->setStatus(&id_to_status[statusIDs::null]);
						onUpdate();
					}
				}
				else
				{
					m_renderer.setState(SELECT_ITEM);
					m_clicked = false;
					firstEntered = true;
					continue;
				}
			}
		}
		else
		{
			selection = 0;
		}





		firstEntered = false;
		onUpdate();
	}
}

void GameEngine::swapPCPokemon(unsigned int box, unsigned int position1, unsigned int box2, unsigned int position2, unsigned int currentBox)
{
	// Four Scenarios
	// 1 - We swap two box Pokemon
	// 2 - We swap a box and a roster
	// 3 - We swap a roster and a box
	// 4 - We swap two roster Pokemon

	//First is a box Pokemon
	if (position1 < 20)
	{

		//Second is a box Pokemon
		if (position2 < 20)
		{
			m_pc.movePokemon(box, position1, box2, position2);
		}
		else //Second is a roster Pokemon
		{
			Pokemon toRoster = m_pc.popPokemon(box, position1);
			m_pc.insertPokemon(m_trainer.popPokemon(position2 - 20), box, position1);


			m_trainer.insertPokemon(toRoster, position2 - 20);
		}

		m_renderer.setBoxPokemon(m_pc.getBox(currentBox));
		m_renderer.setBoxName(m_pc.getBoxName(currentBox));

	}
	else //First is a roster Pokemon
	{
		//Second is a box Pokemon
		if (position2 < 20)
		{
			Pokemon toRoster = m_pc.popPokemon(box2, position2);
			m_pc.insertPokemon(m_trainer.popPokemon(position1 - 20), box2, position2);

			m_trainer.insertPokemon(toRoster, position1 - 20);

			m_renderer.setBoxPokemon(m_pc.getBox(currentBox));
			m_renderer.setBoxName(m_pc.getBoxName(currentBox));
		}
		else //Second is a roster Pokemon
		{
			m_trainer.swapPokemon(position1 - 20, position2 - 20);
		}
	}


}
