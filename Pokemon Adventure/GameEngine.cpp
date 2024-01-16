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
	m_pc.loadUserSettings(&m_userSettings);


	initPlayerPosition();

	//Initialization
	m_renderer.setup(m_window);
	m_encounter.setup(m_window, &m_renderer, &m_input, &m_clicked, &m_mouseX, &m_mouseY);
	m_input.setup(m_window, &m_clicked, &m_mouseX, &m_mouseY, &m_upPressed, &m_downPressed, &m_leftPressed, &m_rightPressed, &m_interactPressed, &m_escapePressed);
	m_gameMap.setup(&m_upPressed, &m_downPressed, &m_leftPressed, &m_rightPressed, &m_interactPressed, &m_renderer);
	m_cutscene.setup(&m_renderer, &m_encounter, &m_userSettings.fasterText);

	//Setting State
	m_renderer.setState(DISPLAY_MAP);
	m_renderer.setTrainer(&m_trainer);
	m_gameMap.setNptData(m_pc.getNptData());

	//Loading User Settings
	m_input.setInputValues(m_userSettings.up, m_userSettings.down, m_userSettings.left, m_userSettings.right, m_userSettings.interact);
	m_renderer.setUserSettingBooleans(m_userSettings.showFps, m_userSettings.autoSave, m_userSettings.fasterText);
	m_renderer.setUserSettingStrings(keyStrings[m_userSettings.up], keyStrings[m_userSettings.down], keyStrings[m_userSettings.left], keyStrings[m_userSettings.right], keyStrings[m_userSettings.interact]);

	return true;
}

bool GameEngine::run()
{

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window))
	{
		//TODO: Can Probably Remove This
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

	for (unsigned int event : events)
	{
		switch (event)
		{

			case Events::inGrass:
				m_inGrass = true;
				break;

			case Events::movedUp:
				movePlayer(Direction::UP, false);
				break;
			
			case Events::movedDown:
				movePlayer(Direction::DOWN, false);
				break;

			case Events::movedLeft:
				movePlayer(Direction::LEFT, false);
				break;

			case Events::movedRight:
				movePlayer(Direction::RIGHT, false);
				break;

			case Events::jumpUp:
				movePlayer(Direction::UP, true);
				break;

			case Events::jumpDown:
				movePlayer(Direction::DOWN, true);
				break;

			case Events::jumpLeft:
				movePlayer(Direction::LEFT, true);
				break;

			case Events::jumpRight:
				movePlayer(Direction::RIGHT, true);
				break;

			case Events::turnUp:
				turnPlayer(Direction::UP);
				break;

			case Events::turnDown:
				turnPlayer(Direction::DOWN);
				break;

			case Events::turnLeft:
				turnPlayer(Direction::LEFT);
				break;

			case Events::turnRight:
				turnPlayer(Direction::RIGHT);
				break;

			case Events::transferUp:
				transferMaps(Direction::UP);
				break;

			case Events::transferDown:
				transferMaps(Direction::DOWN);
				break;

			case Events::transferLeft:
				transferMaps(Direction::LEFT);
				break;

			case Events::transferRight:
				transferMaps(Direction::RIGHT);
				break;

			case Events::trainerSpotted:
				attemptEncounter(false);
				break;

			case Events::pokeCenter:
				transferBuilding(true);
				break;

			case Events::returnSection:
				transferReturn();
				break;

			case Events::interactPC:
				usePC();
				break;

			case Events::interactNurse:
				nurseHeal();
				break;

			case Events::pokeShop:
				transferBuilding(false);
				break;

			case Events::interactItemBuy:
				buyItem();
				break;

			case Events::interactTrainer:
				interactNPT();
				break;

			case Events::startCutScene:
				if (m_cutscene.storyCutscene(m_gameMap.getMapSection()))
				{
					m_pc.setCutsceneCount(m_cutscene.getCutsceneCount());
					m_pc.autoSave(m_trainer, m_gameMap.getMapID(), m_gameMap.getPlayerPosition().x, m_gameMap.getPlayerPosition().y, m_playerDirection, m_gameMap.getNptData());
				}
				break;
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
				changeSettings();
				m_clicked = false;
				m_renderer.setState(DISPLAY_ESCAPE);
				continue;

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

void GameEngine::changeSettings()
{
	m_renderer.setState(DISPLAY_SETTINGS);
	
	bool firstEntered = true;
	while (true)
	{
		if (m_clicked && !firstEntered)
		{
			
			// Change UP
			if (m_mouseX >= 925.0f && m_mouseX <= 995.0f && m_mouseY >= 765.0f && m_mouseY <= 835.0f )
			{
				m_renderer.setUserSettingStrings("", keyStrings[m_userSettings.down], keyStrings[m_userSettings.left], keyStrings[m_userSettings.right], keyStrings[m_userSettings.interact]);
				changeInput(INPUT_EVENT::MOVE_UP);
				firstEntered = true;
				continue;
			}

			if (m_mouseY >= 665.0f && m_mouseY <= 735.0f)
			{
				//Change LEFT
				if (m_mouseX >= 825.0f && m_mouseX <= 895.0f)
				{
					m_renderer.setUserSettingStrings(keyStrings[m_userSettings.up], keyStrings[m_userSettings.down],"", keyStrings[m_userSettings.right], keyStrings[m_userSettings.interact]);
					changeInput(INPUT_EVENT::MOVE_LEFT);
					firstEntered = true;
					continue;
				}
				//Change DOWN
				else if (m_mouseX >= 925.0f && m_mouseX <= 995.0f)
				{
					m_renderer.setUserSettingStrings(keyStrings[m_userSettings.up], "", keyStrings[m_userSettings.left], keyStrings[m_userSettings.right], keyStrings[m_userSettings.interact]);
					changeInput(INPUT_EVENT::MOVE_DOWN);
					firstEntered = true;
					continue;
				}
				// Change RIGHT
				else if (m_mouseX >= 1025.0f && m_mouseX <= 1095.0f)
				{
					m_renderer.setUserSettingStrings(keyStrings[m_userSettings.up], keyStrings[m_userSettings.down], keyStrings[m_userSettings.left], "", keyStrings[m_userSettings.interact]);
					changeInput(INPUT_EVENT::MOVE_RIGHT);
					firstEntered = true;
					continue;
				}
				else if (m_mouseX >= 1225.0f && m_mouseX <= 1295.0f)
				{
					m_renderer.setUserSettingStrings(keyStrings[m_userSettings.up], keyStrings[m_userSettings.down], keyStrings[m_userSettings.left], keyStrings[m_userSettings.right], "");
					changeInput(INPUT_EVENT::INTERACT);
					firstEntered = true;
					continue;
				}
			}

			if (m_mouseX >= 1165 && m_mouseX <= 1305)
			{
				//Show Fps
				if (m_mouseY >= 465 && m_mouseY <= 535)
				{
					m_userSettings.showFps = !m_userSettings.showFps;
				}
				//Auto Save
				else if (m_mouseY >= 315 && m_mouseY <= 385)
				{
					m_userSettings.autoSave = !m_userSettings.autoSave;
					m_pc.setAutoSave(m_userSettings.autoSave);
				}
				//Faster Text
				else if (m_mouseY >= 165 && m_mouseY <= 235)
				{
					m_userSettings.fasterText = !m_userSettings.fasterText;
				}
				m_renderer.setUserSettingBooleans(m_userSettings.showFps, m_userSettings.autoSave, m_userSettings.fasterText);
				firstEntered = true;
				continue;
			}

			break;
		}

		firstEntered = false;
		onUpdate();
	}
	m_pc.saveUserSettings(&m_userSettings);
}

bool GameEngine::attemptEncounter(bool isPokemon, int nptID)
{
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

void GameEngine::movePlayer(Direction direction, bool jump)
{
	if (m_playerDirection != direction)
	{
		turnPlayer(direction);
		return;
	}

	switch (direction)
	{
		case Direction::UP:

			animationControls::controlAnimation(&m_playerX, &m_playerY, false, true, jump, getAnimationPoints(direction, jump), m_playerSpeed, &m_renderer);
			m_gameMap.adjustPlayerPosition(0, 1);
			if (jump)
				m_gameMap.adjustPlayerPosition(0, 1);
			break;

		case Direction::DOWN:

			animationControls::controlAnimation(&m_playerX, &m_playerY, false, false, jump, getAnimationPoints(direction, jump), m_playerSpeed, &m_renderer);
			m_gameMap.adjustPlayerPosition(0, -1);
			if (jump)
				m_gameMap.adjustPlayerPosition(0, -1);
			break;

		case Direction::LEFT:

			animationControls::controlAnimation(&m_playerX, &m_playerY, true, false, jump, getAnimationPoints(direction, jump), m_playerSpeed, &m_renderer);
			m_gameMap.adjustPlayerPosition(-1, 0);
			if (jump)
				m_gameMap.adjustPlayerPosition(-1, 0);
			break;

		case Direction::RIGHT:

			animationControls::controlAnimation(&m_playerX, &m_playerY, true, true, jump, getAnimationPoints(direction, jump), m_playerSpeed, &m_renderer);
			m_gameMap.adjustPlayerPosition(1, 0);
			if (jump)
				m_gameMap.adjustPlayerPosition(1, 0);
			break;
	}

	updateGrassTiles();
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

void GameEngine::changeInput(INPUT_EVENT inputEvent)
{
	int key = m_input.getKey(inputEvent);
	
	if (key == -1)
		exit(4); //TODO: Standardize Exit Codes
	
	int newKey = -1;

	while (newKey == -1)
	{
		//TODO: Display That the key is already in use
		newKey = m_input.getNewInput(key);

		m_renderer.onUpdate();
	}

	if (newKey < 0)
	{

		m_input.swapKey(key, (int)abs(newKey));
		INPUT_EVENT swappedEvent = m_input.getEvent(key);

		switch (inputEvent)
		{
		case INPUT_EVENT::MOVE_UP:
			m_userSettings.up = (int)abs(newKey);
			break;
		case INPUT_EVENT::MOVE_DOWN:
			m_userSettings.down = (int)abs(newKey);
			break;
		case INPUT_EVENT::MOVE_LEFT:
			m_userSettings.left = (int)abs(newKey);
			break;
		case INPUT_EVENT::MOVE_RIGHT:
			m_userSettings.right = (int)abs(newKey);
			break;
		case INPUT_EVENT::INTERACT:
			m_userSettings.interact = (int)abs(newKey);
		}

		switch (swappedEvent)
		{
		case INPUT_EVENT::MOVE_UP:
			m_userSettings.up = key;
			break;
		case INPUT_EVENT::MOVE_DOWN:
			m_userSettings.down = key;
			break;
		case INPUT_EVENT::MOVE_LEFT:
			m_userSettings.left = key;
			break;
		case INPUT_EVENT::MOVE_RIGHT:
			m_userSettings.right = key;
			break;
		case INPUT_EVENT::INTERACT:
			m_userSettings.interact = key;
		}
	}
	else
	{
		m_input.updateKey(key, newKey);

		switch (inputEvent)
		{
		case INPUT_EVENT::MOVE_UP:
			m_userSettings.up = newKey;
			break;
		case INPUT_EVENT::MOVE_DOWN:
			m_userSettings.down = newKey;
			break;
		case INPUT_EVENT::MOVE_LEFT:
			m_userSettings.left = newKey;
			break;
		case INPUT_EVENT::MOVE_RIGHT:
			m_userSettings.right = newKey;
			break;
		case INPUT_EVENT::INTERACT:
			m_userSettings.interact = newKey;
		}
	}
	
	m_renderer.setUserSettingStrings(keyStrings[m_userSettings.up], keyStrings[m_userSettings.down], keyStrings[m_userSettings.left], keyStrings[m_userSettings.right], keyStrings[m_userSettings.interact]);

	//TODO: Save user Settings
}

std::vector<animationControls::trainerAnimationPoint> GameEngine::getAnimationPoints(Direction direction, bool jump)
{
	std::vector<animationControls::trainerAnimationPoint> animationPoints;

	float firstFrame = (1.0f / 4.0f);
	float lastFrame = (3.0f / 4.0f);

	if (jump)
	{
		firstFrame = (1.0f / 8.0f);
		lastFrame = (7.0f / 8.0f);
	}

	if (m_rightFoot)
	{
		animationPoints.push_back({ direction, SpriteState::STEP1, firstFrame });
		m_rightFoot = false;
	}
	else
	{
		animationPoints.push_back({ direction, SpriteState::STEP2, firstFrame });
		m_rightFoot = true;
	}

	animationPoints.push_back({ direction, SpriteState::IDLE, lastFrame });

	return animationPoints;
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

	m_pc.autoSave(m_trainer, m_gameMap.getMapID(), m_gameMap.getPlayerPosition().x, m_gameMap.getPlayerPosition().y, m_playerDirection, m_gameMap.getNptData());
}

void GameEngine::transferBuilding(bool PokeCenter)
{
	if (PokeCenter)
	{
		glm::vec2 playerPosition = m_gameMap.swapPokeCenter(&m_renderer);
		m_pc.setBuildingEvent(Events::pokeCenter);

		setPlayerPosition(playerPosition.x, playerPosition.y);
		m_pc.autoSave(m_trainer, m_gameMap.getMapID(), m_gameMap.getPlayerPosition().x, m_gameMap.getPlayerPosition().y, m_playerDirection, m_gameMap.getNptData());
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

	if (npt.hasPokemon())
		attemptEncounter(false,m_gameMap.getNptID(npt));
	else
	{
		std::cout << "[Game Engine] npt has no pokemon\n";
		m_cutscene.nptDialogue(m_gameMap.getNPT());
	}
}

unsigned int GameEngine::selectPokemon(bool swapPokemon)
{
	//TODO: Use encounters select pokemon
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
