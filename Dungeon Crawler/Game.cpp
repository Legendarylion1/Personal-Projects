#include "Game.h"

/// <summary>
/// Constructor for the dungeon Game.
/// Generates the first map
/// </summary>
/// <param name="windowWidth">- The width of the window</param>
/// <param name="windowHeight">- The height of the window</param>
Game::Game(unsigned int windowWidth, unsigned int windowHeight):
	shader("default.vert", "default.frag"),
	camera(windowWidth, windowHeight, glm::vec3((- (int)windowWidth / 2), ( -(int)windowHeight /2), 2.0f)),
	itemAtlas("Images/Items_Armor/items.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
	map(shader, itemAtlas),
	m_display(shader, camera),
	projectileHandler(itemAtlas),
	test(shader, camera)
{
	playerArray[mainPlayerID].moveToStart(camera);
	playerArray[mainPlayerID].initPlayer(mainPlayerID, shader, itemAtlas);
	playerArray[mainPlayerID].setDisplayHealthbar(false);

	
	basicEnemy.initPlayer(itemAtlas);
	basicEnemy.setPlayerTexture(shader, m_enemyTexture);

	itemAtlas.texUnit(shader, "tex0", 0);
	map.generateMap(m_playerCount, m_level);
}

/// <summary>
/// Deletes and calls the destructor of all assests currently in use
/// </summary>
Game::~Game()
{
	//Calls Player and Map Deconstructor at end of scope
	m_enemyTexture.Delete();
	itemAtlas.Delete();
	shader.Delete();
}

/// <summary>
/// Draws everything having to do with the game
/// </summary>
void Game::drawGame()
{
	shader.Activate();
	map.drawMap(shader, camera, itemAtlas, basicEnemy);
	projectileHandler.drawProjectiles(shader, camera);
	displayTabMenu();
	playerArray[mainPlayerID].drawPlayer(shader, camera, false);
}

/// <summary>
/// Recieves input from the keyboard and mouse to interact with the character and environment.
/// </summary>
/// <param name="window">- GLFW window that we are working with</param>
/// <returns>
/// stay on the same level or proceed to the next level
/// </returns>
int Game::recieveInput(GLFWwindow* window)
{
	// When we recieve a move from the user. We want to check and make sure that it is a valid move
	// Then we want to send the move to the server
	// Then we recieve the move from the server
	// Then we call the functions that the server tells us to call

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (playerCanMove(mainPlayerID, UP))
			playerArray[mainPlayerID].move(UP, camera);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (playerCanMove(mainPlayerID, LEFT))
			playerArray[mainPlayerID].move(LEFT, camera);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (playerCanMove(mainPlayerID, DOWN))
			playerArray[mainPlayerID].move(DOWN, camera);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (playerCanMove(mainPlayerID, RIGHT))
			playerArray[mainPlayerID].move(RIGHT, camera);
	}

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		m_displayTab = true;
	}
	else
	{
		m_displayTab = false;
	}

	if (playerArray[mainPlayerID].isAttacking())
	{
		attackAI(mainPlayerID);
		return 0;
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		dropItem(mainPlayerID, false);
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		playerArray[mainPlayerID].setCurItemIndex(0);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		playerArray[mainPlayerID].setCurItemIndex(1);
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		playerArray[mainPlayerID].setCurItemIndex(2);
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		//attackAI(mainPlayerID);
		//playerArray[mainPlayerID].adjustHealth(-20);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		if (evaluateInteractions(mainPlayerID) == 1)
			return 1;
	}


	if (leftMouseButtonPressed)
	{
		playerArray[mainPlayerID].clearHits();
		attackAI(mainPlayerID);
		playerArray[mainPlayerID].startAttack();
		leftMouseButtonPressed = false;
	}
	playerArray[mainPlayerID].setWeaponAngle(calculateWeaponAngle(window));

	return 0;
}

/// <summary>
/// The player moves from the recieved input, so we have to move the AI and the
/// environment variables, like bullets.
/// </summary>
void Game::progressAI()
{
	if (activatedMap != -1)
	{
		if (map.getMapSections().at(activatedMap).hasEnemies())
		{
			std::vector<glm::vec3> aiAttacks = map.progressAI(activatedMap, getPlayerPositions());
			std::vector<unsigned int> aiIDS = map.getMapSections().at(activatedMap).getHitIDS();

			addAIBullets(map.getMapSections().at(activatedMap).getBullets());
			handleAIAttacks(aiAttacks, aiIDS);
			handleKDAReport(map.getMapSections().at(activatedMap).getKillReport());
		}
		else
		{
			handleKDAReport(map.getMapSections().at(activatedMap).getKillReport());
			activatedMap = -1;
		}
	}


	projectileHandler.moveProjectiles(map.getMapSections());

	std::vector<Projectile::thrownItem> groundedItems = projectileHandler.getGroundedProjectiles();
	for (int i = 0; i < groundedItems.size(); i++)
	{
		Item newItem = Item();
		newItem.setAtlasCoordinates(groundedItems.at(i).atlasCoords);
		newItem.setItemPosition(groundedItems.at(i).Position);
		newItem.setWeaponAngle(groundedItems.at(i).itemAngle);
		newItem.setDamage(groundedItems.at(i).throwableDamage);

		map.getMapSections().at(groundedItems.at(i).roomID).addItem(newItem);
	}
	projectileHandler.clearGroundedProjectiles();

	findProjectileHits();
}

/// <summary>
/// Resets the map and environment variables, rebuilds the map, and prepares for the next level.
/// </summary>
void Game::nextLevel()
{
	m_level += 1;
	map.generateMap(m_playerCount, m_level);
	camera.setPosition(glm::vec3((-(int)WINDOWWIDTH / 2), (-(int)WINDOWHEIGHT / 2), 2.0f));
	playerArray[mainPlayerID].moveToStart(camera);
	playerArray[mainPlayerID].getCurrentItem().setPlayerPosition(playerArray[mainPlayerID].getPosition());
}

bool Game::continueGame(GLFWwindow* window)
{
	for (int i = 0; i < 4; i++)
	{
		if (playerArray[i].getHealth() > 0)
			return true;
	}

	m_shouldExit = m_display.displayDeathMenu(window, playerArray);
	return false;
}

bool Game::shouldExit()
{
	return m_shouldExit;
}

void Game::resetGame()
{
	m_playerCount = 1;
	m_level = 0;
	activatedMap = -1;

	m_displayTab = false;

	for (int i = 0; i < 4; i++)
	{
		playerArray[i].resetPlayer();
	}
	nextLevel();
}

/// <summary>
/// Required function to get mouseButton feedback from GLFW
/// </summary>
/// <param name="window">- GLFW window context in use</param>
/// <param name="button">- The mouse button being pressed</param>
/// <param name="action">- What action is being performed on the button</param>
/// <param name="mods">- Not relevant</param>
void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		leftMouseButtonPressed = true;
}

/// <summary>
/// Calculates the position of the player in reference to the map. If moving between map sections
/// the player remains in his initial map section. If the player has moved into a new map section,
/// then we see if the map section needs to be activated to start enemies and we update the player's
/// map section
/// </summary>
/// <param name="ID">- Index of the player that we are testing</param>
/// <param name="direction">- Direction that the player is trying to move</param>
/// <returns>Whether or not the player can move</returns>
bool Game::playerCanMove(unsigned int ID, int direction)
{
	std::vector<int> result;
	std::vector<int> enteringResult;
	result = map.getMapSections().at(playerArray[ID].getRoomIndex()).withinBounds(playerArray[ID].getPosition(), playerArray[ID].getSpeed(), PLAYER_SIZE, PLAYER_SIZE, direction, -1);

	if (result.at(0) == playerArray[ID].getRoomIndex())
		return true;

	for (int i = 0; i < 4; i++)
	{
		if (result.at(i) != -1)
		{
			enteringResult = map.getMapSections().at(result.at(i)).withinBounds(playerArray[ID].getPosition(), playerArray[ID].getSpeed(), PLAYER_SIZE, PLAYER_SIZE, direction, playerArray[ID].getRoomIndex());
			if (enteringResult.at(0) != -1)
			{
				playerArray[ID].setRoomIndex(enteringResult.at(0));
				if (map.getMapSections().at(enteringResult.at(0)).hasEnemies())
					activatedMap = enteringResult.at(0);
				return true;
			}
		}
	}

	return false;
}

/// <summary>
/// Calculates the slope of the mouse from the center of the screen for the weapons current angle
/// </summary>
/// <param name="window">- GLFW window context in use</param>
/// <returns> Angle derived by arctan to tilt weapon</returns>
double Game::calculateWeaponAngle(GLFWwindow* window)
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	double numerator = (WINDOWHEIGHT / 2.0) - (-mouseY + WINDOWHEIGHT);
	double denominator = (WINDOWWIDTH / 2.0) - mouseX;

	if (denominator == 0)
	{
		if (numerator >= 0)
			return 180.0;
		else
			return 0.0;
	}

	if (numerator < 0)
	{
		if (denominator < 0)
			return (atan(numerator / denominator) * 180 / PI) - 90;
		else
			return (atan(numerator / denominator) * 180 / PI) + 90;
	}
	else
	{
		if (denominator < 0)
			return (atan(numerator / denominator) * 180 / PI) - 90;
		else
			return (atan(numerator / denominator) * 180 / PI) + 90;
	}
}

/// <summary>
/// When player presses the interact key we evaluate what the character is trying to interact with.
/// If the player is interacting with an item we try to see if they can pick it up. Or if they are
/// trying to interact with the end portal we need to go to the next level.
/// </summary>
/// <param name="ID">- The index of the player that we are evaluating</param>
/// <returns>Whether or not to go to the next level</returns>
int Game::evaluateInteractions(unsigned int ID)
{
	//All other numbers are item indexes
	int playerInteractions = map.getMapSections().at(playerArray[ID].getRoomIndex()).getInteractions(playerArray[ID].getPosition(), PLAYER_SIZE, PLAYER_SIZE);

	//-2 is default
	if (playerInteractions == -2)
		return 0;
	//-1 is for next level
	else if (playerInteractions == -1)
		return 1;
	else
	{
		if (playerArray[ID].getItemUsage(0) != false && playerArray[ID].getItemUsage(1) != false && playerArray[ID].getItemUsage(2) != false)
			return 0;

		unsigned int indexToUse = playerArray[ID].getItemIndex();
		findOpenIndex(indexToUse, ID);
		playerArray[ID].setItemIndex(indexToUse, map.getMapSections().at(playerArray[ID].getRoomIndex()).popItem(playerInteractions));
		playerArray[ID].setItemUsage(indexToUse, true);
	}
	
	return 0;
}

/// <summary>
/// When the player presses g whe try and drop the item from their inventory
/// onto the map section.
/// </summary>
/// <param name="ID">- The index of the player that we are evaluating</param>
/// <param name="deleteItem">If we should put the item onto the map section or not</param>
void Game::dropItem(unsigned int ID, bool deleteItem)
{
	if (playerArray[ID].getItemUsage(playerArray[ID].getItemIndex()) == false)
		return;

	if (deleteItem)
	{
		playerArray[ID].setItemIndex(playerArray[ID].getItemIndex(), Item());
		playerArray[ID].setItemUsage(playerArray[ID].getItemIndex(), false);
		return;
	}

	Item itemToAdd = playerArray[ID].getCurrentItem();

	itemToAdd.setItemPosition(glm::vec3(0.0f));
	itemToAdd.setPlayerPosition(playerArray[ID].getPosition());
	itemToAdd.setWeaponAngle(playerArray[ID].getWeaponAngle());

	map.getMapSections().at(playerArray[ID].getRoomIndex()).addItem(itemToAdd);

	playerArray[ID].setItemIndex(playerArray[ID].getItemIndex(), Item());
	playerArray[ID].setItemUsage(playerArray[ID].getItemIndex(), false);
}

/// <summary>
/// Finds an open item index for the player to pick up a new item
/// </summary>
/// <param name="index">- Reference to the currentItemIndex</param>
/// <param name="ID">- Player ID that we are evaluating</param>
void Game::findOpenIndex(unsigned int& index, unsigned int ID)
{
	if (playerArray[ID].getItemUsage(index) == false)
		return;

	for (int i = 0; i < 3; i++)
	{
		if (playerArray[ID].getItemUsage(i) == false)
		{
			index = i;
			return;
		}
	}
}

/// <summary>
/// Accumulates all 4 possible player positions
/// </summary>
/// <returns>All initialized player positions</returns>
std::vector<glm::vec3> Game::getPlayerPositions()
{
	std::vector<glm::vec3> allPositions;

	for (int i = 0; i < 4; i++)
	{
		if (playerArray[i].isInitialized() && playerArray[i].getHealth() != 0)
			allPositions.push_back(playerArray[i].getPosition());
	}

	if (allPositions.size() > 0)
	{
		return allPositions;
	}
	else
		return std::vector<glm::vec3>();
}

/// <summary>
/// Tries to see if our attack will hit and damage the AI. Or if our attack is
/// a projectile, then the projectile will be launched
/// </summary>
/// <param name="ID">- ID of the player that we are evaluating</param>
void Game::attackAI(unsigned int ID)
{
	unsigned int itemType = playerArray[ID].getCurrentItem().getItemType();

	if (itemType == THROWABLE)
	{
		glm::vec3 movementVector = { cos(glm::radians(playerArray[ID].getWeaponAngle() + 90)), sin(glm::radians(playerArray[ID].getWeaponAngle() + 90)), 0.0f };
		projectileHandler.throwItem(playerArray[ID].getCurrentItem().getAtlasCoordinates(), playerArray[ID].getPosition(), movementVector, 1.0f, playerArray[ID].getRoomIndex(), playerArray[ID].getWeaponAngle(), playerArray[ID].getCurrentItem().getDamage(), ID);
		dropItem(ID, true);
	}
	else if (itemType == GUN && !playerArray[mainPlayerID].isAttacking())
	{
		if (playerArray[ID].getCurrentItem().getAtlasCoordinates().x == RARE)
		{

			glm::vec3 movementVector1 = { cos(glm::radians(playerArray[ID].getWeaponAngle() + 70)), sin(glm::radians(playerArray[ID].getWeaponAngle() + 70)), 0.0f };
			projectileHandler.shootBullet(playerArray[ID].getPosition(), movementVector1, 1.0f, playerArray[ID].getRoomIndex(), playerArray[ID].getWeaponAngle(), playerArray[ID].getCurrentItem().getDamage(), ID);

			glm::vec3 movementVector2 = { cos(glm::radians(playerArray[ID].getWeaponAngle() + 90)), sin(glm::radians(playerArray[ID].getWeaponAngle() + 90)), 0.0f };
			projectileHandler.shootBullet(playerArray[ID].getPosition(), movementVector2, 1.0f, playerArray[ID].getRoomIndex(), playerArray[ID].getWeaponAngle(), playerArray[ID].getCurrentItem().getDamage(), ID);

			glm::vec3 movementVector3 = { cos(glm::radians(playerArray[ID].getWeaponAngle() + 110)), sin(glm::radians(playerArray[ID].getWeaponAngle() + 110)), 0.0f };
			projectileHandler.shootBullet(playerArray[ID].getPosition(), movementVector3, 1.0f, playerArray[ID].getRoomIndex(), playerArray[ID].getWeaponAngle(), playerArray[ID].getCurrentItem().getDamage(), ID);
		}
		else
		{
			glm::vec3 movementVector = { cos(glm::radians(playerArray[ID].getWeaponAngle() + 90)), sin(glm::radians(playerArray[ID].getWeaponAngle() + 90)), 0.0f };
			projectileHandler.shootBullet(playerArray[ID].getPosition(), movementVector, 1.0f, playerArray[ID].getRoomIndex(), playerArray[ID].getWeaponAngle(), playerArray[ID].getCurrentItem().getDamage(), ID);
		}
	}

	if (activatedMap == -1)
		return;

	if (itemType == SWORD || itemType == SPEAR)
	{
		std::vector<unsigned int> newHits = map.getMapSections().at(activatedMap).attackEnemy(playerArray[ID].getWeaponAngle(), playerArray[ID].getCurrentItem().getDamage(), playerArray[ID].getWeaponPosition(), playerArray[ID].getHitEnemyIDs(), ID);
		playerArray[ID].addHits(newHits);
	}
	
	
}

/// <summary>
/// Loops through AI attacks to see if any hit the player
/// </summary>
/// <param name="enemyAttacks">- Positions of AI attacks</param>
/// <param name="aiIndex">- Index of the AI attacking</param>
void Game::handleAIAttacks(std::vector<glm::vec3> enemyAttacks, std::vector<unsigned int> aiIndex)
{
	//TODO: Make a distance function for attack enemy and calculate AI to share
	for (int x = 0; x < enemyAttacks.size(); x++)
	{
		int result = attackHitsPlayer(enemyAttacks.at(x),aiIndex.at(x), enemyAttacks.at(x).z);
		if (result != -1)
			map.getMapSections().at(activatedMap).getAI().at(aiIndex.at(x)).addHit(result);
	}
}

/// <summary>
/// If the AI shot a bullet we add it to the projectile handler
/// </summary>
/// <param name="aiBullets">- The position of the bullet(s) that the AI fired</param>
void Game::addAIBullets(std::vector<glm::vec4> aiBullets)
{
	for (int i = 0; i < aiBullets.size(); i++)
	{
		projectileHandler.addAIBullet(aiBullets.at(i), activatedMap);
	}
}

/// <summary>
/// Checks for AI and player projectile impacts. If a player or Ai is hit, they
/// will take damage. If a throwable hits a wall it will stop and be added to the
/// map section. Finally, if a bullet hits a wall it will be deleted.
/// </summary>
void Game::findProjectileHits() 
{
	if (activatedMap == -1)
		return;

	for (int i = 0; i < projectileHandler.getProjectiles().size(); i++)
	{
		projectileHandler.getProjectiles().at(i).addHits(map.getMapSections().at(activatedMap).attackEnemy(projectileHandler.getProjectiles().at(i).itemAngle, projectileHandler.getProjectiles().at(i).throwableDamage, projectileHandler.getProjectiles().at(i).Position, projectileHandler.getProjectiles().at(i).hits, projectileHandler.getProjectiles().at(i).attackerID));
	}

	std::vector<unsigned int> bulletHitIndexes;
	for (int i = 0; i < projectileHandler.getPlayerBullets().size(); i++)
	{
		if (map.getMapSections().at(activatedMap).attackEnemy( projectileHandler.getPlayerBullets().at(i).itemAngle, projectileHandler.getPlayerBullets().at(i).bulletDamage, projectileHandler.getPlayerBullets().at(i).Position, std::vector<unsigned int>(), projectileHandler.getPlayerBullets().at(i).attackerID).size() != 0 )
			bulletHitIndexes.push_back(i);
	} 
	projectileHandler.playerBulletHits(bulletHitIndexes);
	bulletHitIndexes.clear();

	for (int x = 0; x < projectileHandler.getAIBullets().size(); x++)
	{
		if (attackHitsPlayer(projectileHandler.getAIBullets().at(x).Position, 0, projectileHandler.getAIBullets().at(x).bulletDamage) != -1)
			bulletHitIndexes.push_back(x);
	}
	projectileHandler.aiBulletHits(bulletHitIndexes);
}

/// <summary>
/// Checks if the AI attack is within range of the player. If so, the player takes damage.
/// </summary>
/// <param name="attackPosition">- The position of the incoming attack</param>
/// <param name="aiIndex">- The index of the AI in the mapsection vector</param>
/// <param name="damage">- The damage that the attack will do</param>
/// <returns>The index of the player hit</returns>
int Game::attackHitsPlayer(glm::vec3 attackPosition,unsigned int aiIndex, float damage)
{
	for (int i = 3; i >= 0; i--)
	{
		if (!playerArray[i].isInitialized())
			continue;

		if (map.getMapSections().at(activatedMap).getAI().size() == 0)
			continue;

		if (hitAlready(i, map.getMapSections().at(activatedMap).getAI().at(aiIndex).getHitIDS()))
			continue;

		float distance = sqrt(square(playerArray[i].getPosition().x - attackPosition.x) + square(playerArray[i].getPosition().y - attackPosition.y));

		if (distance <= PLAYER_SIZE)
		{
			playerArray[i].adjustHealth(-damage);

			return i;
		}
	}
	
	return -1;
}

/// <summary>
/// Checks to see if the player index is already in the vector of hitIndex
/// </summary>
/// <param name="playerIndex">- The index of the player</param>
/// <param name="hitIndex">- The list of players already hit</param>
/// <returns>If the playerIndex is in the hitIndex</returns>
bool Game::hitAlready(unsigned int playerIndex, std::vector<unsigned int> hitIndex)
{
	for (int i = 0; i < hitIndex.size(); i++)
	{
		if (playerIndex == hitIndex.at(i))
			return true;
	}
	return false;
}

void Game::displayTabMenu()
{
	if (m_displayTab)
		m_display.displayTabMenu(playerArray);
}

void Game::handleKDAReport(std::vector<std::vector<unsigned int>> kdaReport)
{
	for (int i = 0; i < kdaReport.size(); i++)
	{

		for (int x = 0; x < kdaReport.at(i).size() - 1; x++)
		{
			playerArray[kdaReport.at(i).at(x)].addAssists(1);
		}
		playerArray[kdaReport.at(i).back()].addKills(1);
	}

	map.getMapSections().at(activatedMap).clearKDAReport();
}
