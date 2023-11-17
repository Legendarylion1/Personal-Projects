#include "Player.h"

/// <summary>
/// Empty play initializer for a player object
/// </summary>
Player::Player(){}

/// <summary>
/// Initilizes player and player UI
/// </summary>
/// <param name="playerID">- The ID of the player being initialized</param>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="itemTexture">- Reference to the game's itemAtlas</param>
Player::Player(unsigned int playerID, Shader& shader, Texture& itemTexture)
{
	initPlayer(playerID, shader, itemTexture);
}

/// <summary>
/// Deletes all vectors containing buffer information
/// </summary>
Player::~Player()
{
	if (playerInitialized)
	{
		unsigned int vaoSize = vaoVector.size();
		unsigned int vboSize = vaoVector.size();
		unsigned int eboSize = vaoVector.size();

		for (int i = 0; i < vaoSize; i++)
		{
			Player::vaoVector.at(i).Delete();
		}
		for (int i = 0; i < vboSize; i++)
		{
			Player::vboVector.at(i).Delete();
		}
		for (int i = 0; i < vaoSize; i++)
		{
			Player::eboVector.at(i).Delete();
		}

		Player::playerTexture.Delete();
		playerInitialized = false;
	}
}

/// <summary>
/// Initializes a player sprite and a mini healthbar. Does not initialize the UI
/// </summary>
/// <param name="itemTexture"> - Reference to the game's itemTexture</param>
void Player::initPlayer(Texture& itemTexture)
{
	Player::playerID = playerID;
	Player::itemAtlas = itemTexture;
	Player::itemArray[0].setAtlasCoordinates(glm::vec2(BASIC, SPEAR));
	Player::currentHealth = Player::maxHealth;
	playerInitialized = true;

	GLfloat characterVertices[]
	{

		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2), LAYER_THREE,	0.0f,0.0f,0.0f,			0.0f, 0.0f,
		(-PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_THREE,	0.0f,0.0f,0.0f,			0.0f, 1.0f,
		(PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_THREE,	0.0f,0.0f,0.0f,			1.0f, 1.0f,
		(PLAYER_SIZE / 2), (-PLAYER_SIZE / 2), LAYER_THREE,	0.0f,0.0f,0.0f,			1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(characterVertices, sizeof(characterVertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Player::vaoVector.push_back(VAO1);
	Player::vboVector.push_back(VBO1);
	Player::eboVector.push_back(EBO1);




	GLfloat equippedItemVertices[]
	{
		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.0f,  0.0f,
		(-PLAYER_SIZE / 2), (PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.0f,  0.25f,
		(PLAYER_SIZE / 2), (PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.25f, 0.25f,
		(PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.25f, 0.0f
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(equippedItemVertices, sizeof(equippedItemVertices));
	EBO EBO2(indices, sizeof(indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	Player::vaoVector.push_back(VAO2);
	Player::vboVector.push_back(VBO2);
	Player::eboVector.push_back(EBO2);



	GLuint tripleIndices[] =
	{
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6,

		8, 10, 9,
		8, 11, 10
	};

	GLfloat healthBarVertices[]
	{
		//	Health Bar
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17,			LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2) - 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2) - 1,	(PLAYER_SIZE / 2) + 17,			LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,

		//	  Outline
		(-PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 16,				LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(-PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 18 + 10,		LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 18 + 10,		LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 16,				LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,

		//	  Dynamic
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17,			LAYER_FOUR,			1.0f,0.0f,0.20f,	0.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_FOUR,			1.0f,0.0f,0.20f,	0.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_FOUR,			1.0f,0.0f,0.20f,	1.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17,			LAYER_FOUR,			1.0f,0.0f,0.20f,	1.0f, 0.0f
	};

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(healthBarVertices, sizeof(healthBarVertices));
	EBO tripleEBO(tripleIndices, sizeof(tripleIndices));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	tripleEBO.Unbind();

	Player::vaoVector.push_back(VAO3);
	Player::vboVector.push_back(VBO3);
	Player::eboVector.push_back(tripleEBO);
}

/// <summary>
/// Initializes a player sprite and the player's UI
/// </summary>
/// <param name="playerID">- The ID of the player being initialized</param>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="itemTexture">- Reference to the game's itemAtlas</param>
void Player::initPlayer(unsigned int playerID, Shader& shader, Texture& itemTexture)
{
	ui.initUI();
	Player::playerID = playerID;
	Player::itemAtlas = itemTexture;
	Player::itemArray[0].setPlayerPosition(Position);
	Player::itemArray[0].setAtlasCoordinates(glm::vec2(LEGENDARY, SWORD));
	Player::itemArray[0].setDamage(100);
	Player::itemArray[0].setAttackSpeed(0.2f);
	Player::currentHealth = Player::maxHealth;
	playerInitialized = true;

	playerTexture = Texture("Images/Characters/Torin-Idle.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	playerTexture.texUnit(shader, "tex0", 0);

	GLfloat characterVertices[]
	{
		(-PLAYER_SIZE / 2), (-PLAYER_SIZE/2), LAYER_THREE,	0.0f,0.0f,0.0f,			0.0f, 0.0f,
		(-PLAYER_SIZE / 2), ( PLAYER_SIZE/2), LAYER_THREE,	0.0f,0.0f,0.0f,			0.0f, 1.0f,
		( PLAYER_SIZE / 2), ( PLAYER_SIZE/2), LAYER_THREE,	0.0f,0.0f,0.0f,			1.0f, 1.0f,
		( PLAYER_SIZE / 2), (-PLAYER_SIZE/2), LAYER_THREE,	0.0f,0.0f,0.0f,			1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(characterVertices, sizeof(characterVertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Player::vaoVector.push_back(VAO1);
	Player::vboVector.push_back(VBO1);
	Player::eboVector.push_back(EBO1);




	GLfloat equippedItemVertices[]
	{
		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.0f,  0.0f,
		(-PLAYER_SIZE / 2), ( PLAYER_SIZE / 2), LAYER_FOUR,				0.0f,0.0f,0.0f,			0.0f,  0.25f,
		( PLAYER_SIZE / 2), ( PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.25f, 0.25f,
		( PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.25f, 0.0f
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(equippedItemVertices, sizeof(equippedItemVertices));
	EBO EBO2(indices, sizeof(indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	Player::vaoVector.push_back(VAO2);
	Player::vboVector.push_back(VBO2);
	Player::eboVector.push_back(EBO2);



	GLuint tripleIndices[] =
	{
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6,

		8, 10, 9,
		8, 11, 10
	};

	GLfloat healthBarVertices[]
	{
		//	Health Bar
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17,			LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2) - 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2) - 1,	(PLAYER_SIZE / 2) + 17,			LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,

		//	  Outline
		(-PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 16,				LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(-PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 18 + 10,		LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 18 + 10,		LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(PLAYER_SIZE / 2),	(PLAYER_SIZE / 2) + 16,				LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,

		//	  Dynamic
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17,			LAYER_FOUR,			1.0f,0.0f,0.20f,	0.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_FOUR,			1.0f,0.0f,0.20f,	0.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17 + 10,	LAYER_FOUR,			1.0f,0.0f,0.20f,	1.0f, 0.0f,
		(-PLAYER_SIZE / 2) + 1,	(PLAYER_SIZE / 2) + 17,			LAYER_FOUR,			1.0f,0.0f,0.20f,	1.0f, 0.0f
	};

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(healthBarVertices, sizeof(healthBarVertices));
	EBO tripleEBO(tripleIndices, sizeof(tripleIndices));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	tripleEBO.Unbind();

	Player::vaoVector.push_back(VAO3);
	Player::vboVector.push_back(VBO3);
	Player::eboVector.push_back(tripleEBO);
}

/// <summary>
/// Calls the initializer for the playerUI
/// </summary>
void Player::initUI()
{
	ui.initUI();
}

/// <summary>
/// Draws the player sprite and any periferal UI elements
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="isEnemy">- Whether the player being drawn is an AI</param>
void Player::drawPlayer(Shader& shader, Camera& camera, bool isEnemy)
{
	if (!playerInitialized)
		return;
	
	if (!isEnemy)
	{
		playerTexture.Bind();
		Player::vaoVector.at(0).Bind();
		camera.Matrix(shader, Position);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		Player::vaoVector.at(0).Unbind();
		playerTexture.Unbind();

		if (m_itemUsage[curItemIndex])
		{
			if (!attacking)
			{
				itemArray[curItemIndex].bindAtlasUniforms(shader, itemAtlas);
				Player::vaoVector.at(1).Bind();
				camera.Matrix(shader, Position, weaponAngle, itemArray[curItemIndex].getFlipped());
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				Player::vaoVector.at(1).Unbind();
				itemAtlas.Unbind();
				itemArray[curItemIndex].resetAtlasUniforms(shader);
			}
			else
			{
				itemArray[curItemIndex].bindAtlasUniforms(shader, itemAtlas);
				Player::vaoVector.at(1).Bind();
				camera.Matrix(shader, itemArray[curItemIndex].getItemPosition(), itemArray[curItemIndex].getWeaponAngle(), itemArray[curItemIndex].getFlipped());
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				Player::vaoVector.at(1).Unbind();
				itemAtlas.Unbind();
				itemArray[curItemIndex].resetAtlasUniforms(shader);

				attacking = itemArray[curItemIndex].continueAttack(Position);
			}
		}
	}

	itemArray[curItemIndex].drawParticles(shader, camera);

	if (m_displayHealthbar)
	{
		Player::vaoVector.at(2).Bind();

		glUniform1f(glGetUniformLocation(shader.ID, "healthBar"), ((PLAYER_SIZE - 2) * currentHealth) / maxHealth);

		camera.Matrix(shader, Position);
		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
		Player::vaoVector.at(2).Unbind();
	}
	else
	{
		ui.drawUI(shader, camera, maxHealth, currentHealth, curItemIndex, Position, itemArray, itemAtlas, m_itemUsage);
	}
}

/// <summary>
/// Moves the player and camera to the center of the first mapSection
/// </summary>
/// <param name="camera">- Reference to the game's camera</param>
void Player::moveToStart(Camera& camera)
{
	curRoomIndex = 0;
	Position.x = 0;
	Position.y = 0;
	Position.y += (MAP_SECTION_SIZE / 2);
	Position.x += (MAP_SECTION_SIZE / 2);

	camera.move(UP, (MAP_SECTION_SIZE / 2));
	camera.move(RIGHT, (MAP_SECTION_SIZE / 2));
}

void Player::resetPlayer()
{

	weaponAngle = 0;
	curItemIndex = 0;
	curRoomIndex = 0;

	maxHealth = 100;
	speed = 1.5f;

	hitEnemyIDs.clear();
	m_kdaVector = { 0,0,0 };

	for (int i = 0; i < 3; i++)
	{
		itemArray[i] = Item();
		m_itemUsage[i] = false;
	}

	if (playerInitialized)
	{
		currentHealth = 100;

		Player::itemArray[0].setAtlasCoordinates(glm::vec2(LEGENDARY, SWORD));
		Player::itemArray[0].setDamage(100);
		Player::itemArray[0].setAttackSpeed(0.2f);
		Player::m_itemUsage[0] = true;
	}
}

/// <summary>
/// Returns whether or not the player is currently attacking
/// </summary>
/// <returns></returns>
bool Player::isAttacking()
{
	return attacking;
}

/// <summary>
/// Returns whether or not the player has been initialized
/// </summary>
/// <returns></returns>
bool Player::isInitialized()
{
	return playerInitialized;
}

/// <summary>
/// Sets the player's texture
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="texture">- Reference to the new texture the player is to use</param>
void Player::setPlayerTexture(Shader& shader, Texture& texture)
{
	playerTexture = texture;
	playerTexture.texUnit(shader, "tex0", 0);
}

/// <summary>
/// Sets whether or not to display the mini healthbar
/// </summary>
/// <param name="displayStatus"></param>
void Player::setDisplayHealthbar(bool displayStatus)
{
	m_displayHealthbar = displayStatus;
}

/// <summary>
/// Sets the position of the player
/// </summary>
/// <param name="newPosition"></param>
void Player::setPlayerPosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

/// <summary>
/// Sets the position of the currently selected item
/// </summary>
/// <param name="Position"></param>
void Player::setItemPosition(glm::vec3 Position)
{
	itemArray[curItemIndex].setItemPosition(Position);
}

/// <summary>
/// Sets the index of the currently selected item
/// </summary>
/// <param name="itemSlot"></param>
void Player::setCurItemIndex(unsigned int itemSlot)
{
	curItemIndex = itemSlot;
	itemArray[curItemIndex].setPlayerPosition(Position);
}

/// <summary>
/// Sets the angle of the currently selected weapon
/// </summary>
/// <param name="angle"></param>
void Player::setWeaponAngle(double angle)
{
	weaponAngle = angle;

	itemArray[curItemIndex].setWeaponAngle(angle);

	if (itemArray[curItemIndex].getAtlasCoordinates().y == GUN && weaponAngle <= 0)
		itemArray[curItemIndex].setFlipped(true);
	else
		itemArray[curItemIndex].setFlipped(false);
}

/// <summary>
/// Sets the index of the current mapSection the user is in
/// </summary>
/// <param name="roomIndex"></param>
void Player::setRoomIndex(unsigned int roomIndex)
{

	curRoomIndex = roomIndex;
}

/// <summary>
/// Sets player's item array at the index provided to the new Item
/// </summary>
/// <param name="index">- Player's item Array index to change</param>
/// <param name="newItem">- The Item to go into the array</param>
void Player::setItemIndex(unsigned int index, Item newItem)
{
	itemArray[index] = newItem;
}

/// <summary>
/// Sets whether or not we are using an item at the given index
/// </summary>
/// <param name="index">- Players itemUsage array index to change</param>
/// <param name="itemUsage">- The value of the position at that index</param>
void Player::setItemUsage(unsigned int index, bool itemUsage)
{
	m_itemUsage[index] = itemUsage;
}

/// <summary>
/// Sets the current health of the player
/// </summary>
/// <param name="health">- Value to set the current health</param>
void Player::setCurrentHealth(float health)
{
	currentHealth = health;
}

/// <summary>
/// Set whether or not the player is attacking
/// </summary>
/// <param name="isAttacking">- The value of whether or not we are attacking</param>
void Player::setAttacking(bool isAttacking)
{
	attacking = isAttacking;
}

/// <summary>
/// Returns the item that the player currently has selected
/// </summary>
/// <returns></returns>
Item& Player::getCurrentItem()
{
	return itemArray[curItemIndex];
}

float Player::getHealth()
{
	return currentHealth;
}

/// <summary>
/// Returns the speed of the player
/// </summary>
/// <returns></returns>
float Player::getSpeed()
{
	return speed;
}

/// <summary>
/// Return the current weapon angle
/// </summary>
/// <returns></returns>
float Player::getWeaponAngle()
{
	return weaponAngle;
}

/// <summary>
/// Returns the ID of the mapSection the player is in
/// </summary>
/// <returns></returns>
unsigned int Player::getRoomIndex()
{
	return curRoomIndex;
}

/// <summary>
/// Returns the index of the currently selected item
/// </summary>
/// <returns></returns>
unsigned int Player::getItemIndex()
{
	return curItemIndex;
}

/// <summary>
/// Returns whether or not an item is being used based on the index provided
/// </summary>
/// <param name="index">- Index to check for usage</param>
/// <returns></returns>
bool Player::getItemUsage(unsigned int index)
{
	return m_itemUsage[index];
}

/// <summary>
/// Returns the position of the player
/// </summary>
/// <returns></returns>
glm::vec3 Player::getPosition()
{
	return Position;
}

/// <summary>
/// Returns the position of the weapon in world coordinates
/// </summary>
/// <returns></returns>
glm::vec3 Player::getWeaponPosition()
{
	return itemArray[curItemIndex].getItemPosition();
}

/// <summary>
/// Returns a vector of the IDs of all the enemies already hit by an attack
/// </summary>
/// <returns></returns>
std::vector<unsigned int> Player::getHitEnemyIDs()
{
	return hitEnemyIDs;
}

std::vector<int> Player::getKDA()
{
	return m_kdaVector;
}

/// <summary>
/// Moves the player and camera in the desired direction
/// </summary>
/// <param name="direction">- Direction to move the player</param>
/// <param name="camera">- Reference to the game's camera</param>
void Player::move(unsigned int direction, Camera& camera)
{
	if (direction == UP)
	{
		Position.y += speed;
		camera.move(UP, speed);
	}
		
	if (direction == DOWN)
	{
		Position.y += -speed;
		camera.move(DOWN, speed);
	}
		
	if (direction == LEFT)
	{
		Position.x += -speed;
		camera.move(LEFT, speed);
	}
	if (direction == RIGHT)
	{
		Position.x += speed;
		camera.move(RIGHT, speed);
	}

	itemArray[curItemIndex].setPlayerPosition(Position);
}

/// <summary>
/// The player sets attacking to true and begins his animation
/// </summary>
void Player::startAttack()
{
	if (m_itemUsage[curItemIndex] == true)
	{ 
		attacking = true;
		itemArray[curItemIndex].attack(weaponAngle, Position);
	}
}

/// <summary>
/// Adjusts health by the given amount
/// </summary>
/// <param name="amount">- The value to adjust the health</param>
void Player::adjustHealth(float amount)
{
	currentHealth += amount;
	if (currentHealth < 0)
	{
		currentHealth = 0;
		addDeaths(1);
	}
}

/// <summary>
/// All of the new enemies hit get added to our vector of hits
/// </summary>
/// <param name="newHits">- Vector of the new enemies hit</param>
void Player::addHits(std::vector<unsigned int> newHits)
{
	for (int i = 0; i < newHits.size(); i++)
	{
		hitEnemyIDs.push_back(newHits.at(i));
	}
}

/// <summary>
/// Clears our vector of enemies hit
/// </summary>
void Player::clearHits()
{
	hitEnemyIDs.clear();
}

void Player::addKills(int value)
{
	m_kdaVector.at(0) += value;
}

void Player::addDeaths(int value)
{
	m_kdaVector.at(1) += value;
}

void Player::addAssists(int value)
{
	m_kdaVector.at(2) += value;
}
