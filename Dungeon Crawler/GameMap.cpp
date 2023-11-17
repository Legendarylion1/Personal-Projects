#include "GameMap.h"

/// <summary>
/// Seeds the randomizer for the map and initializes the map
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="itemAtlas">- Reference to the game's itemAtlas</param>
GameMap::GameMap(Shader& shader, Texture& itemAtlas)
{
	srand(time(NULL));
	GameMap::initMap(shader, itemAtlas);
}

/// <summary>
/// Deletes all of the vectors needed to draw the map
/// </summary>
GameMap::~GameMap()
{
	GameMap::deleteVectors(true);
}

/// <summary>
/// Randomly generates the map
/// </summary>
/// <param name="numPlayers">- Number of players in the game</param>
/// <param name="level">- Current level of the game</param>
void GameMap::generateMap(unsigned int numPlayers, unsigned int level)
{
	int totalRooms = 2 + numPlayers + (int)(level / 3);
	int sectionIDs = 0;

	resetNodes();

	//Create and link all of the rooms
	populateTree(totalRooms);

	//Create and push back the map sections
	createMapSections(start, sectionIDs, -1, -1, m_longestSection);

	//Free the memory used to make the tree
	deconstructNodes();

	implementMapInteractions(numPlayers, level);
}

/// <summary>
/// Initializes all textures needed to draw the map
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="itemAtlas">- Reference to the game's itemAtlas</param>
void GameMap::initMap(Shader& shader, Texture& itemAtlas)
{
	//I wanted to use a map for this, but I got lazy and didnt take the time to figure out how to make a template for my texture class for the map to use
	Texture mapUpImage("Images/map-up.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP] = mapUpImage;

	Texture mapDownImage("Images/map-down.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_DOWN] = mapDownImage;

	Texture mapLeftImage("Images/map-left.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_LEFT] = mapLeftImage;

	Texture mapRightImage("Images/map-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_RIGHT] = mapRightImage;

	Texture mapUpDownImage("Images/map-up-down.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP_DOWN] = mapUpDownImage;

	Texture mapUpRight("Images/map-up-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP_RIGHT] = mapUpRight;

	Texture mapUpLeft("Images/map-up-left.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP_LEFT] = mapUpLeft;

	Texture mapDownLeft("Images/map-down-left.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_DOWN_LEFT] = mapDownLeft;

	Texture mapDownRight("Images/map-down-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_DOWN_RIGHT] = mapDownRight;

	Texture mapLeftRight("Images/map-left-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_LEFT_RIGHT] = mapLeftRight;

	Texture mapUpDownLeft("Images/map-up-down-left.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP_DOWN_LEFT] = mapUpDownLeft;

	Texture mapUpDownRight("Images/map-up-down-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP_DOWN_RIGHT] = mapUpDownRight;

	Texture mapUpLeftRight("Images/map-up-left-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_UP_LEFT_RIGHT] = mapUpLeftRight;

	Texture mapDownLeftRight("Images/map-down-left-right.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_DOWN_LEFT_RIGHT] = mapDownLeftRight;

	Texture mapOmniDirection("Images/map-omni-directional.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_OMNI_DIRECTION] = mapOmniDirection;

	Texture mapHorizontalHall("Images/map-horizontal-hall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_HORIZONTAL_HALL] = mapHorizontalHall;

	Texture mapVerticalHall("Images/map-vertical-hall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GameMap::textureArray[MAP_VERTICAL_HALL] = mapVerticalHall;

	Texture endPortal("Images/pieceOutline.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_endTexture = endPortal;

	Texture enemyTexture("Images/Characters/wPawnStandard.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_enemyTexture = enemyTexture;

	m_itemTexture = itemAtlas;

}

/// <summary>
/// Draws all of the mapSections that make up the map
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="itemAtlas">- Reference to the game's itemAtlas</param>
/// <param name="enemy">- Reference to the game's enemy player</param>
void GameMap::drawMap(Shader& shader, Camera& camera, Texture& itemAtlas, Player& enemy)
{
	for (int i = 0; i < GameMap::mapSections.size(); i++)
	{
		GameMap::mapSections.at(i).drawSection(shader, camera, itemAtlas, enemy);
	}
}

/// <summary>
/// Returns all mapSections
/// </summary>
/// <returns></returns>
std::vector<MapSection>& GameMap::getMapSections()
{
	return mapSections;
}

/// <summary>
/// Deletes all vectors used for drawing the map
/// </summary>
/// <param name="deleteTextures"></param>
void GameMap::deleteVectors(bool deleteTextures)
{
	unsigned int mapSectionSize = GameMap::mapSections.size();

	for (int i = mapSectionSize; i > 0; i--)
	{
		GameMap::mapSections.at(i - 1).deleteVectors(true);
		GameMap::mapSections.pop_back();
	}

	if (deleteTextures)
	{
		for (int i = 0; i < 17; i++)
		{
			GameMap::textureArray[i].Delete();
		}
	}
}

/// <summary>
/// Creates a linked list of nodes used to create a mapSection
/// </summary>
/// <param name="prevNode">- Pointer to the previous node in the linked list</param>
/// <param name="curRoomCount">- Reference to the count of rooms made</param>
/// <param name="totalRooms">- Referene to the total number of rooms to create</param>
/// <param name="prevDirection">- Direction that the previous room chose to make the new room</param>
void GameMap::generateTree(GameMap::mapTree* prevNode, int& curRoomCount, int& totalRooms, unsigned int prevDirection)
{
	//Four Part Function
	//Part 1	-	Links the nodes to each other as a linked list
	//Part 2	-	Checks if we have already created a room next to the room we are trying to create
	//Part 3	-	Decide how many new rooms to make and in what direction they should be
	//Part 4	-	Recursively creates the new rooms

	bool upAvailable = true;
	bool downAvailable = true;
	bool leftAvailable = true;
	bool rightAvailable = true;

	int roomCombinations = 3;

	mapTree* newNode = new mapTree(0, 0, 0);
	mapTree* newHall = new mapTree(0, 0, 1);
	newHall->type = 1;

	//	Part 1
	if (prevDirection == UP)
	{
		//Assign Coordinates
		newNode->x = prevNode->x;
		newNode->y = prevNode->y + 2;
		newHall->x = prevNode->x;
		newHall->y = prevNode->y + 1;


		//Link the Rooms
		prevNode->up = newHall;
		newHall->down = prevNode;
		newHall->up = newNode;
		newNode->down = newHall;

		downAvailable = false;
	}
	else if (prevDirection == DOWN)
	{
		//Assign Coordinates
		newNode->x = prevNode->x;
		newNode->y = prevNode->y - 2;
		newHall->x = prevNode->x;
		newHall->y = prevNode->y - 1;


		//Link the Rooms
		prevNode->down = newHall;
		newHall->up = prevNode;
		newHall->down = newNode;
		newNode->up = newHall;

		upAvailable = false;
	}
	else if (prevDirection == LEFT)
	{
		//Assign Coordinates
		newNode->x = prevNode->x - 2;
		newNode->y = prevNode->y;
		newHall->x = prevNode->x - 1;
		newHall->y = prevNode->y;


		//Link the Rooms
		prevNode->left = newHall;
		newHall->right = prevNode;
		newHall->left = newNode;
		newNode->right = newHall;

		rightAvailable = false;
	}
	else
	{
		//Assign Coordinates
		newNode->x = prevNode->x + 2;
		newNode->y = prevNode->y;
		newHall->x = prevNode->x + 1;
		newHall->y = prevNode->y;


		//Link the Rooms
		prevNode->right = newHall;
		newHall->left = prevNode;
		newHall->right = newNode;
		newNode->left = newHall;

		leftAvailable = false;
	}

	if (curRoomCount == totalRooms)
		return;
	
	//Part 2
	if (upAvailable)
	{
		upAvailable = !searchCoordinateNodes(newNode->x, newNode->y + 2);
		if (!upAvailable)
			roomCombinations--;
	}

	if (downAvailable)
	{
		downAvailable = !searchCoordinateNodes(newNode->x, newNode->y - 2);
		if (!downAvailable)
			roomCombinations--;
	}

	if (leftAvailable)
	{
		leftAvailable = !searchCoordinateNodes(newNode->x - 2, newNode->y);
		if (!leftAvailable)
			roomCombinations--;
	}

	if (rightAvailable)
	{
		rightAvailable = !searchCoordinateNodes(newNode->x + 2, newNode->y);
		if (!rightAvailable)
			roomCombinations--;
	}

	if (roomCombinations <= 0)
		return;
	

	int roomsToMake = 0;

	while ((totalRooms <= (curRoomCount + roomCombinations)) && roomCombinations > 0)
	{
		roomCombinations--;
	}

	//Part 3
	if (roomCombinations == 0)
		roomsToMake = 1;
	else
		roomsToMake = rand() % roomCombinations + 1;
	bool addUp = false;
	bool addDown = false;
	bool addLeft = false;
	bool addRight = false;

	int roomsMade = 0;
	while (roomsMade != roomsToMake)
	{
		int direction = rand() % 4 + 1;
		if (direction == UP && upAvailable)
		{
			addCoordinateNode(new coordinateNode(newNode->x, newNode->y + 2));
			upAvailable = false;
			addUp = true;
			roomsMade++;
		}
		else if (direction == DOWN && downAvailable)
		{
			addCoordinateNode(new coordinateNode(newNode->x, newNode->y - 2));
			downAvailable = false;
			addDown = true;
			roomsMade++;
		}
		else if (direction == LEFT && leftAvailable)
		{
			addCoordinateNode(new coordinateNode(newNode->x - 2, newNode->y));
			leftAvailable = false;
			addLeft = true;
			roomsMade++;
		}
		else if (direction == RIGHT && rightAvailable)
		{
			addCoordinateNode(new coordinateNode(newNode->x + 2, newNode->y));
			rightAvailable = false;
			addRight = true;
			roomsMade++;
		}
	}
	curRoomCount += roomsMade;

	//Part 4
	if (addUp)
		generateTree(newNode, curRoomCount, totalRooms, UP);
	if (addDown)
		generateTree(newNode, curRoomCount, totalRooms, DOWN);
	if (addLeft)
		generateTree(newNode, curRoomCount, totalRooms, LEFT);
	if (addRight)
		generateTree(newNode, curRoomCount, totalRooms, RIGHT);
}

/// <summary>
/// Resets all values used in the creation of a new map
/// </summary>
void GameMap::resetNodes()
{
	GameMap::m_longestSection = 0;
	GameMap::m_lastSectionID = 0;

	GameMap::head->x = 0;
	GameMap::head->y = 0;
	GameMap::head->nextNode = nullptr;

	GameMap::start->x = 0;
	GameMap::start->y = 0;
	GameMap::start->up = nullptr;
	GameMap::start->down = nullptr;
	GameMap::start->left = nullptr;
	GameMap::start->right = nullptr;
	GameMap::start->status = 3;
	GameMap::start->type = 0;

	for (int i = 0; i < mapSections.size(); i++)
	{
		GameMap::mapSections.at(i).deleteVectors(true);
	}
	GameMap::mapSections.clear();
}

/// <summary>
/// Uses our private start node and starts the process for generating a map
/// </summary>
/// <param name="totalRooms"></param>
void GameMap::populateTree(int& totalRooms)
{
	int curRoomCount = 2; //Start plus the new room created by calling generateTree

	//Between 1 and 4
	int direction = rand() % 4 + 1;

	if (direction == UP)
	{
		addCoordinateNode(new coordinateNode(start->x, start->y + 2));
	}
	else if (direction == DOWN)
	{
		addCoordinateNode(new coordinateNode(start->x, start->y - 2));
	}
	else if (direction == LEFT)
	{
		addCoordinateNode(new coordinateNode(start->x - 2, start->y));
	}
	else
	{
		addCoordinateNode(new coordinateNode(start->x + 2, start->y));
	}

	generateTree(start, curRoomCount, totalRooms, direction);
}

/// <summary>
/// Creates new map Section objects to append to our vector based on our linked mapTree nodes
/// </summary>
/// <param name="node">- Pointer to our current mapTree node</param>
/// <param name="sectionID">- Reference to the sectionID count so we can ensure unique mapSection IDs</param>
/// <param name="prevRoomID">- ID of the previous room used to link rooms</param>
/// <param name="direction">- Direction the previous mapTree node chose to make this new mapSection</param>
/// <param name="branchLength">- How far we have branched off from the start</param>
void GameMap::createMapSections(GameMap::mapTree* node, int& sectionID, int prevRoomID, int direction, unsigned int branchLength)
{
	//Three Part Function
	//Part 1	-	Assign the texture to the map section and add it to our vector
	//Part 2	-	Discover and flag new nodes to visit
	//Part 3	-	Recursively call on new nodes
	bool visitUp = false;
	bool visitDown = false;
	bool visitLeft = false;
	bool visitRight = false;


	//	Part 1
	if (node->type == 1)
	{
		if (node->up != nullptr)
		{
			MapSection newSection(GameMap::textureArray[MAP_VERTICAL_HALL], node->x, node->y, sectionID, m_enemyTexture);
			newSection.adjustBounds(MAP_VERTICAL_HALL);
			linkRoom(newSection, prevRoomID, direction);
			GameMap::mapSections.push_back(newSection);
		}
		else
		{
			MapSection newSection(GameMap::textureArray[MAP_HORIZONTAL_HALL], node->x, node->y, sectionID, m_enemyTexture);
			newSection.adjustBounds(MAP_HORIZONTAL_HALL);
			linkRoom(newSection, prevRoomID, direction);
			GameMap::mapSections.push_back(newSection);
		}
	}
	else
	{
		int textureCount = 0;
		if (node->up != nullptr)
			textureCount += 1;
		if (node->down != nullptr)
			textureCount += 2;
		if (node->left != nullptr)
			textureCount += 4;
		if (node->right != nullptr)
			textureCount += 8;

		longestBranch(branchLength, sectionID);
		MapSection newSection(GameMap::textureArray[textureCount], node->x, node->y, sectionID, m_enemyTexture);
		linkRoom(newSection, prevRoomID, direction);
		GameMap::mapSections.push_back(newSection);
	}
	sectionID += 1;


	//	Part 2
	if (node->up != nullptr && node->up->status != 3)
	{
		node->up->status = 3;
		visitUp = true;
	}
	if (node->down != nullptr && node->down->status != 3)
	{
		node->down->status = 3;
		visitDown = true;
	}
	if (node->left != nullptr && node->left->status != 3)
	{
		node->left->status = 3;
		visitLeft = true;
	}
	if (node->right != nullptr && node->right->status != 3)
	{
		node->right->status = 3;
		visitRight = true;
	}

	int nextRoomID = sectionID - 1;
	unsigned int nextBranchLength = branchLength + 1;

	//	Part 3
	if (visitUp)
		createMapSections(node->up, sectionID, nextRoomID,UP, nextBranchLength);
	if (visitDown)
		createMapSections(node->down, sectionID, nextRoomID, DOWN, nextBranchLength);
	if (visitLeft)
		createMapSections(node->left, sectionID, nextRoomID, LEFT, nextBranchLength);
	if (visitRight)
		createMapSections(node->right, sectionID, nextRoomID, RIGHT, nextBranchLength);
}

/// <summary>
/// Links the IDs of mapSections
/// </summary>
/// <param name="newSection">- Reference to the newMapSection that was created</param>
/// <param name="prevRoomID">- The ID of the room that had created the new mapSection</param>
/// <param name="direction">- Direction that the previous mapSection chose to create the new mapSection</param>
void GameMap::linkRoom(MapSection& newSection, int prevRoomID, int direction)
{
	if (prevRoomID == -1 || direction == -1)
		return;

	if (direction == UP)
	{
		newSection.down = prevRoomID;
		mapSections.at(prevRoomID).up = newSection.ID;
	}
	else if (direction == DOWN)
	{
		newSection.up = prevRoomID;
		mapSections.at(prevRoomID).down = newSection.ID;
	}
	else if (direction == LEFT)
	{
		newSection.right = prevRoomID;
		mapSections.at(prevRoomID).left = newSection.ID;
	}
	else if (direction == RIGHT)
	{
		newSection.left = prevRoomID;
		mapSections.at(prevRoomID).right = newSection.ID;
	}
}

/// <summary>
/// Checks to see if we have a furthest mapSection to make the end of the map
/// </summary>
/// <param name="branchLength">- The distance from the starting mapSection to the new one</param>
/// <param name="sectionID">- The ID if the new section</param>
void GameMap::longestBranch(unsigned int branchLength, int sectionID)
{
	if (branchLength >= m_longestSection)
	{
		m_lastSectionID = sectionID;
		m_longestSection = branchLength;
	}
}

/// <summary>
/// Frees the memory used to create the coordinate node linked list
/// </summary>
void GameMap::deconstructNodes()
{
	coordinateNode* leader = head;
	coordinateNode* follower = head;

	while (head->nextNode != nullptr)
	{
		while (leader->nextNode != nullptr)
		{
			leader = leader->nextNode;
		}
		while (follower->nextNode != leader)
		{
			follower = follower->nextNode;
		}
		delete leader;
		follower->nextNode = nullptr;
		leader = head;
		follower = head;
	}

	if (start->up != nullptr)
	{
		start->up->down = nullptr;
		freeMapTree(start->up);
	}
	else if (start->down != nullptr)
	{
		start->down->up = nullptr;
		freeMapTree(start->down);
	}
	else if (start->left != nullptr)
	{
		start->left->right = nullptr;
		freeMapTree(start->left);
	}
	else if (start->right != nullptr)
	{
		start->right->left = nullptr;
		freeMapTree(start->right);
	}
}

/// <summary>
/// recursively frees the memory used to create mapTree nodes
/// </summary>
/// <param name="node">- Pointer to the node whose memory needs to be freed</param>
void GameMap::freeMapTree(mapTree* node)
{
	if (node->up != nullptr)
	{
		node->up->down = nullptr;
		freeMapTree(node->up);
		node->up = nullptr;
	}
	if (node->down != nullptr)
	{
		node->down->up = nullptr;
		freeMapTree(node->down);
		node->down = nullptr;
	}
		
	if (node->left != nullptr)
	{
		node->left->right = nullptr;
		freeMapTree(node->left);
		node->left = nullptr;
	}
		
	if (node->right != nullptr)
	{
		node->right->left = nullptr;
		freeMapTree(node->right);
		node->right = nullptr;
	}
		
	delete node;
}

/// <summary>
/// Adds a new node to the end of the coordinate node linked list
/// </summary>
/// <param name="newNode">- Pointer to the new node</param>
void GameMap::addCoordinateNode(GameMap::coordinateNode* newNode)
{
	coordinateNode* last = head;

	while (last->nextNode != nullptr)
	{
		last = last->nextNode;
	}
	last->nextNode = newNode;
}

/// <summary>
/// Searches the coordinate nodes for the x y pair
/// </summary>
/// <param name="x">- X value we are searching for</param>
/// <param name="y">- Y value we are searching for</param>
/// <returns>Whether or not we found the pair</returns>
bool GameMap::searchCoordinateNodes(int x, int y)
{
	coordinateNode* coordinateNode = head;

	while (coordinateNode->nextNode != nullptr)
	{
		if ((coordinateNode->x == x && coordinateNode->y == y) || (x == head->x && y == head->y))
			return true;
		coordinateNode = coordinateNode->nextNode;
	}
	if ((coordinateNode->x == x && coordinateNode->y == y) || (x == head->x && y == head->y))
		return true;
	return false;
}

/// <summary>
/// Implements the loot, enemies, and portal to the next Level
/// </summary>
/// <param name="numPlayers">- Number of players in the game</param>
/// <param name="level">- Current level the players are on</param>
void GameMap::implementMapInteractions(unsigned int numPlayers, unsigned int level)
{
	// Start Room is always the start and we dont touch it
	// First room after is always enemy room
	// Then every other room is 2/3 odds of being enemy
	// With 1/3 odds of being item



	//	SETS THE END ROOM
	mapSections.at(m_lastSectionID).setEnd(true);
	mapSections.at(m_lastSectionID).setEndTexture(m_endTexture);

	// Add enemies to the first room
	addEnemies(2, numPlayers, level);

	

	//Skip first 2						  Skip Halls
	for (int i = 4; i < mapSections.size(); i += 2)
	{
		if (i == m_lastSectionID)
			continue;

		int result = rand() % 3;

		if (result == 0)
			addLoot(i, numPlayers, level);
		else
			addEnemies(i, numPlayers, level);
	}
}

/// <summary>
/// Randomly adds loot to the mapSection
/// </summary>
/// <param name="ID">- ID of the section we are adding loot to</param>
/// <param name="playerCount">- Number of players in the game</param>
/// <param name="level">- Current level the players are on</param>
void GameMap::addLoot(unsigned int ID, unsigned int playerCount, unsigned int level)
{
	if (playerCount < 3)
	{
		Item newItem = Item();

		newItem.randomize(playerCount, level, true);
		newItem.setItemPosition(glm::vec3(mapSections.at(ID).getCenter(), 0));
		mapSections.at(ID).addItem(newItem);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			Item newItem = Item();

			glm::vec2 mapCenter = mapSections.at(ID).getCenter();
			mapCenter.x += (-1 * i) + (PLAYER_SIZE / 2);
			newItem.randomize(playerCount, level, true);
			newItem.setItemPosition(glm::vec3(mapCenter, 0));
			mapSections.at(ID).addItem(newItem);
		}
	}
}

/// <summary>
/// Randomly adds enemies with weapons to the mapSection
/// </summary>
/// <param name="ID">- ID of the section we are adding enemies to</param>
/// <param name="playerCount">- Number of players in the game</param>
/// <param name="level">- Current level the players are on</param>
void GameMap::addEnemies(unsigned int ID, unsigned int playerCount, unsigned int level)
{
	unsigned int totalEnemyCount = 0;
	if (playerCount >= 3)
		totalEnemyCount += 1;

	//Every 5 levels we add another enemy to the map
	totalEnemyCount += level / 5;


	mapSections.at(ID).addEnemy(glm::vec3(mapSections.at(ID).getCenter(),0));
	
	glm::vec3 centerCoords = { mapSections.at(ID).getCenter(), 0.0f };

	for (int i = 0; i < totalEnemyCount; i++)
	{
		//MAP left bound + playerSize <= xPos <= MAP right bount - PLAYERSIZE
		int xPos = (rand() % (int)(MAP_SECTION_SIZE - (PLAYER_SIZE * 2)) + PLAYER_SIZE) - (MAP_SECTION_SIZE / 2);
		int yPos = (rand() % (int)(MAP_SECTION_SIZE - (PLAYER_SIZE * 2)) + PLAYER_SIZE) - (MAP_SECTION_SIZE / 2);


		mapSections.at(ID).addEnemy(glm::vec3(centerCoords.x + xPos, centerCoords.y + yPos, centerCoords.z));
	}
	
}

/// <summary>
/// Progresses the AI of a given mapSection
/// </summary>
/// <param name="ID">- ID of the mapSection we want to progress the AI</param>
/// <param name="playerPositions">- Positions of all of the players in the game</param>
/// <returns>All attacks the enemies launched onto the players</returns>
std::vector<glm::vec3> GameMap::progressAI(unsigned int ID, std::vector<glm::vec3> playerPositions)
{
	return mapSections.at(ID).progressAI(playerPositions);
}