#include "MapSection.h"

/// <summary>
/// Creates all vectors needed to draw a map Section
/// </summary>
/// <param name="backgroundTexture">- Texture to be drawn as the background of the section</param>
/// <param name="xLoc">- X position of the section in grid coordinates</param>
/// <param name="yLoc">- Y position of the section in grid coordinates</param>
/// <param name="sectionID">- ID of the section</param>
/// <param name="enemyTexture">Reference to the game's AI texture</param>
MapSection::MapSection(Texture& backgroundTexture, int xLoc, int yLoc, unsigned int sectionID, Texture& enemyTexture):
	sectionBackground(backgroundTexture), ID(sectionID), m_enemyTexture(enemyTexture)
{
	GLfloat vertices[]
	{
		xLoc * MAP_SECTION_SIZE, yLoc * MAP_SECTION_SIZE, LAYER_ONE,												0.0f,0.0f,0.0f,			0.0f, 0.0f,
		xLoc * MAP_SECTION_SIZE, (yLoc * MAP_SECTION_SIZE) + MAP_SECTION_SIZE, LAYER_ONE,							0.0f,0.0f,0.0f,			0.0f, 1.0f,
		(xLoc * MAP_SECTION_SIZE) + MAP_SECTION_SIZE, (yLoc * MAP_SECTION_SIZE) + MAP_SECTION_SIZE, LAYER_ONE,		0.0f,0.0f,0.0f,			1.0f, 1.0f,
		(xLoc * MAP_SECTION_SIZE) + MAP_SECTION_SIZE, yLoc * MAP_SECTION_SIZE, LAYER_ONE,							0.0f,0.0f,0.0f,			1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	MapSection::vaoVector.push_back(VAO1);
	MapSection::vboVector.push_back(VBO1);
	MapSection::eboVector.push_back(EBO1);


	m_topBound = (yLoc * MAP_SECTION_SIZE) + MAP_SECTION_SIZE;
	m_bottomBound = (yLoc * MAP_SECTION_SIZE);
	m_leftBound = xLoc * MAP_SECTION_SIZE;
	m_rightBound = (xLoc * MAP_SECTION_SIZE) + MAP_SECTION_SIZE;

	GLfloat itemVertices[]
	{
		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_TWO,				0.0f,0.0f,0.0f,			0.0f,  0.0f,
		(-PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_TWO,				0.0f,0.0f,0.0f,			0.0f,  0.25f,
		(PLAYER_SIZE / 2), (PLAYER_SIZE / 2),	LAYER_TWO,				0.0f,0.0f,0.0f,			0.25f, 0.25f,
		(PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_TWO,				0.0f,0.0f,0.0f,			0.25f, 0.0f
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(itemVertices, sizeof(itemVertices));
	EBO EBO2(indices, sizeof(indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	MapSection::vaoVector.push_back(VAO2);
	MapSection::vboVector.push_back(VBO2);
	MapSection::eboVector.push_back(EBO2);



	// Order
	// -----
	// Bottom Left
	// Top Left
	// Top Right
	// Bottom Right
	float dividerLength = (MAP_SECTION_SIZE - (2 * MAP_CONNECTION_MARGIN_SIZE)) / 2;

	GLfloat dividerVertices[]
	{
		-dividerLength, 0,	LAYER_TWO,	0.0f,0.0f,0.0f,			0.0f, 0.0f,
		-dividerLength, 10,	LAYER_TWO,	0.0f,0.0f,0.0f,			0.0f, 1.0f,
		 dividerLength, 10,	LAYER_TWO,	0.0f,0.0f,0.0f,			1.0f, 1.0f,
		 dividerLength, 0,	LAYER_TWO,	0.0f,0.0f,0.0f,			1.0f, 0.0f
	};


	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(dividerVertices, sizeof(dividerVertices));
	EBO EBO3(indices, sizeof(indices));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	MapSection::vaoVector.push_back(VAO3);
	MapSection::vboVector.push_back(VBO3);
	MapSection::eboVector.push_back(EBO3);


	GLfloat characterVertices[]
	{

		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2), LAYER_THREE,	0.0f,0.0f,0.0f,			0.0f, 0.0f,
		(-PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_THREE,		0.0f,0.0f,0.0f,			0.0f, 1.0f,
		(PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_THREE,		0.0f,0.0f,0.0f,			1.0f, 1.0f,
		(PLAYER_SIZE / 2), (-PLAYER_SIZE / 2), LAYER_THREE,		0.0f,0.0f,0.0f,			1.0f, 0.0f
	};

	VAO VAO4;
	VAO4.Bind();

	VBO VBO4(characterVertices, sizeof(characterVertices));
	EBO EBO4(indices, sizeof(indices));

	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	MapSection::vaoVector.push_back(VAO4);
	MapSection::vboVector.push_back(VBO4);
	MapSection::eboVector.push_back(EBO4);

	GLfloat equippedItemVertices[]
	{
		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.0f,  0.0f,
		(-PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_FOUR,				0.0f,0.0f,0.0f,			0.0f,  0.25f,
		(PLAYER_SIZE / 2), (PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.25f, 0.25f,
		(PLAYER_SIZE / 2), (-PLAYER_SIZE / 2),	LAYER_FOUR,				0.0f,0.0f,0.0f,			0.25f, 0.0f
	};

	VAO VAO5;
	VAO5.Bind();

	VBO VBO5(equippedItemVertices, sizeof(equippedItemVertices));
	EBO EBO5(indices, sizeof(indices));

	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();

	MapSection::vaoVector.push_back(VAO5);
	MapSection::vboVector.push_back(VBO5);
	MapSection::eboVector.push_back(EBO5);
}

/// <summary>
/// Deletes the vectors being used by the mapSection
/// </summary>
MapSection::~MapSection()
{
	//deleteVectors(true);
}

/// <summary>
/// Sets the background texture
/// </summary>
/// <param name="texture">- Desired Texture</param>
void MapSection::setBackgroundTexture(Texture& texture)
{
	sectionBackground = texture;
}

/// <summary>
/// Creates a new VAO to draw the background
/// </summary>
/// <param name="texture">- Desired end texture</param>
void MapSection::setEndTexture(Texture& texture)
{
	GLfloat vertices[]
	{
		m_leftBound + MAP_END_MARGIN_SIZE,	m_bottomBound + MAP_END_MARGIN_SIZE,	LAYER_ONE + .05,			0.0f,0.0f,0.0f,			0.0f, 0.0f,
		m_leftBound + MAP_END_MARGIN_SIZE,	m_topBound - MAP_END_MARGIN_SIZE,		LAYER_ONE + .05,			0.0f,0.0f,0.0f,			0.0f, 1.0f,
		m_rightBound - MAP_END_MARGIN_SIZE,	m_topBound - MAP_END_MARGIN_SIZE,		LAYER_ONE + .05,			0.0f,0.0f,0.0f,			1.0f, 1.0f,
		m_rightBound - MAP_END_MARGIN_SIZE,	m_bottomBound + MAP_END_MARGIN_SIZE,	LAYER_ONE + .05,			0.0f,0.0f,0.0f,			1.0f, 0.0f
	};

	VAO VAO;
	VAO.Bind();

	VBO VBO(vertices, sizeof(vertices));
	eboVector.at(0).Bind();

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	eboVector.at(0).Unbind();

	MapSection::vaoVector.push_back(VAO);
	MapSection::vboVector.push_back(VBO);

	m_endTexture = texture;
}

/// <summary>
/// Sets whether or not this is the end of the map
/// </summary>
/// <param name="isEnd">- Whether or not this is the farthest section in the map from the start</param>
void MapSection::setEnd(bool isEnd)
{
	m_end = isEnd;
}

/// <summary>
/// Draws the map section
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="itemAtlas">- Reference to the game's itemAtlas</param>
/// <param name="enemy">- Reference to the game's enemy Player</param>
void MapSection::drawSection(Shader& shader, Camera& camera, Texture& itemAtlas, Player& enemy)
{
	sectionBackground.Bind();
	sectionBackground.texUnit(shader, "tex0", 0);
	MapSection::vaoVector.at(0).Bind();
	camera.Matrix(shader, glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	MapSection::vaoVector.at(0).Unbind();
	sectionBackground.Unbind();
	
	if (m_end)
	{
		m_endTexture.Bind();
		MapSection::vaoVector.at(5).Bind();
		camera.Matrix(shader, glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		MapSection::vaoVector.at(5).Unbind();
		m_endTexture.Unbind();
	}

	if (m_blockExits)
		drawDividers(shader, camera);
	
	drawItems(shader, camera, itemAtlas);
	drawEnemies(shader, camera, enemy, itemAtlas);
}

/// <summary>
/// Draws all AI and their weapons to the screen
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="enemy">- Reference to the game's enemy Player</param>
/// <param name="itemAtlas">- Reference to the game's itemAtlas</param>
void MapSection::drawEnemies(Shader& shader, Camera& camera, Player& enemy, Texture& itemAtlas)
{
	for (int i = 0; i < enemyStats.size(); i++)
	{
		m_enemyTexture.Bind();
		vaoVector.at(3).Bind();
		camera.Matrix(shader, enemyStats.at(i).getPosition());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		vaoVector.at(3).Unbind();
		m_enemyTexture.Unbind();

		if (!enemyStats.at(i).isAttacking())
		{
			m_enemyItems.at(i).bindAtlasUniforms(shader, itemAtlas);
			vaoVector.at(4).Bind();
			camera.Matrix(shader, m_enemyItems.at(i).getItemPosition(), enemyStats.at(i).getWeaponAngle(), m_enemyItems.at(i).getFlipped());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			vaoVector.at(4).Unbind();
			itemAtlas.Unbind();
			m_enemyItems.at(i).resetAtlasUniforms(shader);
		}
		else
		{
			m_enemyItems.at(i).bindAtlasUniforms(shader, itemAtlas);
			vaoVector.at(4).Bind();
			camera.Matrix(shader, m_enemyItems.at(i).getItemPosition(), m_enemyItems.at(i).getWeaponAngle(), m_enemyItems.at(i).getFlipped());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			vaoVector.at(4).Unbind();
			itemAtlas.Unbind();
			m_enemyItems.at(i).resetAtlasUniforms(shader);

			enemyStats.at(i).setAttacking(m_enemyItems.at(i).continueAttack(enemyStats.at(i).getPosition()));
		}
		
		m_enemyItems.at(i).drawParticles(shader, camera);

		//Just to draw the healthbar
		enemy.setPlayerPosition(enemyStats.at(i).getPosition());
		enemy.setCurrentHealth(enemyStats.at(i).getCurrentHealth());
		enemy.drawPlayer(shader, camera, true);
	}
}

/// <summary>
/// Draws all items currently on the mapSection
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="itemAtlas">- Reference to the game's itemAtlas</param>
void MapSection::drawItems(Shader& shader, Camera& camera, Texture& itemAtlas)
{
	for (int i = 0; i < itemVector.size(); i++)
	{
		itemVector.at(i).bindAtlasUniforms(shader, itemAtlas);
		MapSection::vaoVector.at(1).Bind();

		camera.Matrix(shader, itemVector.at(i).getItemPosition(), itemVector.at(i).getWeaponAngle());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		MapSection::vaoVector.at(1).Unbind();

		itemAtlas.Unbind();

		itemVector.at(i).resetAtlasUniforms(shader);

		itemVector.at(i).drawParticles(shader, camera);
	}
}

/// <summary>
/// Draws the dividers that "prevent" the users escape when in combat
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
void MapSection::drawDividers(Shader& shader, Camera& camera)
{
	if (down != -1)
	{
		MapSection::vaoVector.at(2).Bind();
		camera.Matrix(shader, glm::vec3(m_leftBound + (MAP_SECTION_SIZE / 2), m_bottomBound, 0.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		MapSection::vaoVector.at(2).Unbind();
	}

	if (up != -1)
	{
		MapSection::vaoVector.at(2).Bind();
		camera.Matrix(shader, glm::vec3(m_leftBound + (MAP_SECTION_SIZE / 2), m_topBound, 0.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		MapSection::vaoVector.at(2).Unbind();
	}

	if (left != -1)
	{
		MapSection::vaoVector.at(2).Bind();
		camera.Matrix(shader, glm::vec3(m_leftBound, m_bottomBound + (MAP_SECTION_SIZE / 2), 0.0f), 90.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		MapSection::vaoVector.at(2).Unbind();
	}
	
	if (right != -1)
	{
		MapSection::vaoVector.at(2).Bind();
		camera.Matrix(shader, glm::vec3(m_rightBound, m_bottomBound + (MAP_SECTION_SIZE / 2), 0.0f), 90.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		MapSection::vaoVector.at(2).Unbind();
	}

}

/// <summary>
/// Safely deletes all vectors that were used to draw the map and environment
/// </summary>
/// <param name="deleteTexture">Whether or not to delete the background texture</param>
void MapSection::deleteVectors(bool deleteTexture)
{
	//TODO: Remove delete Texture
	for (int i = 0; i < vaoVector.size(); i++)
	{
		MapSection::vaoVector.at(i).Delete();
	}
	for (int i = 0; i < vboVector.size(); i++)
	{
		MapSection::vboVector.at(i).Delete();
	}
	for (int i = 0; i < eboVector.size(); i++)
	{
		MapSection::eboVector.at(i).Delete();
	}

	MapSection::vaoVector.clear();
	MapSection::vboVector.clear();
	MapSection::eboVector.clear();
	MapSection::itemVector.clear();
	MapSection::enemyStats.clear();
	MapSection::m_enemyItems.clear();
}

/// <summary>
/// Checks to see if a rectangle is within the bounds of a section of the map
/// </summary>
/// <param name="position"> - Position of the rectangle in world space</param>
/// <param name="speed"> - How far the object is trying to move</param>
/// <param name="width"> - The width of the object</param>
/// <param name="height"> - The height of the object</param>
/// <param name="direction"> - The direction the object is trying to move</param>
/// <param name="enteringID"> - If the object is trying to change map sections, The ID of the section the object is coming from, otherwise enter -1</param>
/// <returns> If index 0 of the vector is the same as the ID that you were checking, then you are within bounds to move. 
/// If you are coming from a different map section, then index 0 is the ID of the map section that you are in
/// If the index 0 is -1 then the move is not within the bounds of the map</returns>
std::vector<int> MapSection::withinBounds(glm::vec3 position, float speed, float width, float height, unsigned int direction, int enteringID)
{
	float x = position.x - (width/2);
	float y = position.y - (height/2);

	if (direction == UP)
		y += speed;
	else if (direction == DOWN)
		y -= speed;
	else if (direction == LEFT)
		x -= speed;
	else if (direction == RIGHT)
		x += speed;

	std::vector<int> locations = { -1,-1,-1,-1 };

	if (enteringID == -1)
	{
		if (y + height <= m_topBound && y >= m_bottomBound && x + width <= m_rightBound && x >= m_leftBound)
		{
			locations.at(0) = ID;

			if (enemyStats.size() != 0)
				m_blockExits = true;
			else
				m_blockExits = false;

			return locations;
		}
		else
		{
			if (enemyStats.size() == 0)
				m_blockExits = false;
			
			if (up != -1 && enemyStats.size() == 0)
				locations.at(0) = up;
			if (down != -1 && enemyStats.size() == 0)
				locations.at(1) = down;
			if (left != -1 && enemyStats.size() == 0)
				locations.at(2) = left;
			if (right != -1 && enemyStats.size() == 0)
				locations.at(3) = right;
		}
	}
	else
	{
		if (y <= m_topBound && y + height >= m_bottomBound && x <= m_rightBound && x + width >= m_leftBound)
		{
			if (y + height <= m_topBound && y >= m_bottomBound && x + width <= m_rightBound && x >= m_leftBound)
				locations.at(0) = ID;
			else if (betweenBorders(x, y, width, height, direction))
				locations.at(0) = enteringID;
		}
	}

	return locations;
}

/// <summary>
/// Checks to see if a rectangle is within the bounds of a section of the map
/// </summary>
/// <param name="position">- Position of the rectangle in the world space</param>
/// <param name="movementVector">- The vector that the object is moving along</param>
/// <param name="width">- The width of the object</param>
/// <param name="height">- The height of the object</param>
/// <param name="enteringID">- If the object is trying to change map sections, The ID of the section the object is coming from, otherwise enter -1</param>
/// <returns>If index 0 of the vector is the same as the ID that you were checking, then you are within bounds to move. 
/// If you are coming from a different map section, then index 0 is the ID of the map section that you are in
/// If the index 0 is -1 then the move is not within the bounds of the map</returns>
std::vector<int> MapSection::withinBounds(glm::vec3 position, glm::vec3 movementVector, float width, float height, int enteringID)
{
	float x = position.x - (width / 2);
	float y = position.y - (height / 2);

	x += movementVector.x;
	y += movementVector.y;

	std::vector<int> locations = { -1,-1,-1,-1 };

	if (enteringID == -1)
	{
		if (y + height <= m_topBound && y >= m_bottomBound && x + width <= m_rightBound && x >= m_leftBound)
		{
			locations.at(0) = ID;

			return locations;
		}
		else
		{
			if (enemyStats.size() == 0)
				m_blockExits = false;

			if (up != -1 && enemyStats.size() == 0)
				locations.at(0) = up;
			if (down != -1 && enemyStats.size() == 0)
				locations.at(1) = down;
			if (left != -1 && enemyStats.size() == 0)
				locations.at(2) = left;
			if (right != -1 && enemyStats.size() == 0)
				locations.at(3) = right;
		}
	}
	else
	{
		if (y <= m_topBound && y + height >= m_bottomBound && x <= m_rightBound && x + width >= m_leftBound)
		{
			if (y + height <= m_topBound && y >= m_bottomBound && x + width <= m_rightBound && x >= m_leftBound)
				locations.at(0) = ID;
			else if (betweenBorders(x, y, width, height, UP) || betweenBorders(x, y, width, height, LEFT))
				locations.at(0) = enteringID;
		}
	}

	return locations;
}

/// <summary>
/// Checks to see if your movement is valid between mapSections
/// </summary>
/// <param name="x">- X coordinate in world space</param>
/// <param name="y">- Y coordinate in world space</param>
/// <param name="width">- Width of the object</param>
/// <param name="height">- Height of the object</param>
/// <param name="direction">- direction that the object is trying to move in</param>
/// <returns>Whether or the position is valid</returns>
bool MapSection::betweenBorders(float x, float y, float width, float height, unsigned int direction)
{

	if (direction == UP || direction == DOWN)
	{
		if (m_rightBound - m_leftBound != MAP_SECTION_SIZE) {	//We know were vertical
			if (m_leftBound <= x && x + width <= m_rightBound)
				return true;
		}
		else if (m_topBound - m_bottomBound != MAP_SECTION_SIZE)	// In Horizontal
		{
			if (m_bottomBound <= y && y + height <= m_topBound)
				return true;
		}
		else
			if (m_leftBound <= x && x + width <= m_rightBound)
				return true;
	}
	else
	{
		if (m_rightBound - m_leftBound != MAP_SECTION_SIZE) {	//We know were vertical
			if (m_leftBound <= x && x + width <= m_rightBound)
				return true;
		}
		else if (m_topBound - m_bottomBound != MAP_SECTION_SIZE)	// In Horizontal
		{
			if (m_bottomBound <= y && y + height <= m_topBound)
				return true;
		}
		else
			if (m_bottomBound <= y && y + height <= m_topBound)
				return true;
	}
	return false;
}

/// <summary>
/// Gets all of the interactions between the player and the map environment
/// </summary>
/// <param name="Position">- Position of the player</param>
/// <param name="width">- width of the player</param>
/// <param name="height">- height of the player</param>
/// <returns>-1 if they interacted with the end; -2 if they didnt interact with anything; Otherwise the index of the item they interacted with in the mapSection</returns>
int MapSection::getInteractions(glm::vec3 Position, float width, float height)
{
	for (int i = 0; i < itemVector.size(); i++)
	{
			//Bottom of Sword														//Top of Sword																			//Left Side of sword													//Right side of sword
		if (Position.y <= itemVector.at(i).getItemPosition().y + (PLAYER_SIZE / 2) && Position.y >= itemVector.at(i).getItemPosition().y - (PLAYER_SIZE / 2) && Position.x <= itemVector.at(i).getItemPosition().x + (PLAYER_SIZE / 2) && Position.x >= itemVector.at(i).getItemPosition().x - (PLAYER_SIZE / 2))
			return i;
	}

	if (m_end)
	{
		if (Position.y <= m_topBound - MAP_END_MARGIN_SIZE && Position.y + height >= m_bottomBound + MAP_END_MARGIN_SIZE && Position.x <= m_rightBound - MAP_END_MARGIN_SIZE && Position.x + width >= m_leftBound + MAP_END_MARGIN_SIZE)
			return -1;
	}
	return -2;
}

/// <summary>
/// Returns the IDs of all attacking AI
/// </summary>
/// <returns></returns>
std::vector<unsigned int> MapSection::getHitIDS()
{
	std::vector<unsigned int> hitIDS;

	for (int i = 0; i < enemyStats.size(); i++)
	{
		if (enemyStats.at(i).isAttacking())
		{
			hitIDS.push_back(i);
		}
	}

	if (hitIDS.size() == 0)
		return std::vector<unsigned int>();
	else
		return hitIDS;
}

/// <summary>
/// Returns the X,Y Positions of the center of the map section
/// </summary>
/// <returns></returns>
glm::vec2 MapSection::getCenter()
{
	return glm::vec2(m_leftBound + (MAP_SECTION_SIZE / 2), m_bottomBound + (MAP_SECTION_SIZE / 2));
}

/// <summary>
/// Return our vector of all AI Stats
/// </summary>
/// <returns></returns>
std::vector<AIStats>& MapSection::getAI()
{
	return enemyStats;
}

/// <summary>
/// Returns all of the bullets that have been fired by the AI. And sets the AI bullet count to 0
/// </summary>
/// <returns></returns>
std::vector<glm::vec4> MapSection::getBullets()
{
	std::vector<glm::vec4> bulletData;

	for (int i = 0; i < enemyStats.size(); i++)
	{
		if (enemyStats.at(i).getBulletCount() == 0)
			continue;

		if (enemyStats.at(i).getBulletCount() == 1)
		{
			glm::vec4 newBullet = { enemyStats.at(i).getPosition(), 0.0f };
			newBullet.z = enemyStats.at(i).getWeaponAngle();
			newBullet.w = m_enemyItems.at(i).getDamage();
			bulletData.push_back(newBullet);
		}
		else
		{
			glm::vec4 newBullet = { enemyStats.at(i).getPosition(), 0.0f };
			newBullet.z = enemyStats.at(i).getWeaponAngle();
			newBullet.w = m_enemyItems.at(i).getDamage();
			bulletData.push_back(newBullet);

			newBullet.z = enemyStats.at(i).getWeaponAngle() + 20;
			newBullet.w = m_enemyItems.at(i).getDamage();
			bulletData.push_back(newBullet);

			newBullet.z = enemyStats.at(i).getWeaponAngle() - 20;
			newBullet.w = m_enemyItems.at(i).getDamage();
			bulletData.push_back(newBullet);

		}
		enemyStats.at(i).setBulletCount(0);
	}

	if (bulletData.size() == 0)
		return std::vector<glm::vec4>();
	else
		return bulletData;
}

std::vector<std::vector<unsigned int>> MapSection::getKillReport()
{
	return m_kdaVector;
}

void MapSection::clearKDAReport()
{
	m_kdaVector.clear();
}

/// <summary>
/// Add an item to the itemVector to be drawn on the map
/// </summary>
/// <param name="newItem"></param>
void MapSection::addItem(Item newItem)
{
	MapSection::itemVector.push_back(newItem);
}

/// <summary>
/// Remove the item at the index from the itemVector and return it.
/// </summary>
/// <param name="index">- Index of the item in the itemVector</param>
/// <returns></returns>
Item MapSection::popItem(unsigned int index)
{
	Item poppedItem = itemVector.at(index);
	itemVector.erase(itemVector.begin() + index);
	return poppedItem;

}

/// <summary>
/// Returns whether or not there are enemies in the mapSection
/// </summary>
/// <returns></returns>
bool MapSection::hasEnemies()
{
	if (enemyStats.size() > 0)
		return true;
	return false;
}

/// <summary>
/// Creates a new enemy with an item to add to the mapSection
/// </summary>
/// <param name="enemyPosition">- Starting position of the enemy</param>
void MapSection::addEnemy(glm::vec3 enemyPosition)
{
	AIStats newEnemy = AIStats(enemyPosition);
	Item newItem = Item();

	newEnemy.setID(m_aiID);
	newItem.setPlayerPosition(enemyPosition);
	newEnemy.setAtlasCoords(newItem.randomize(1,1,false));
	m_aiID += 1;

	enemyStats.push_back(newEnemy);
	m_enemyItems.push_back(newItem);
}

/// <summary>
/// Player tries to attack an enemy
/// </summary>
/// <param name="weaponAngle">- Angle of the weapon</param>
/// <param name="weaponDamage">- Damage the weapon deals</param>
/// <param name="weaponPosition">- Position of the weapon</param>
/// <param name="hitIDS">- The IDs of the AI that have already been hit</param>
/// <returns>IDs of AI that were just hit</returns>
std::vector<unsigned int> MapSection::attackEnemy(float weaponAngle, float weaponDamage, glm::vec3 weaponPosition, std::vector<unsigned int> hitIDS, unsigned int attackerID)
{
	//Weapon angle was meant to be used to make sure the sword was facing the correct direction but I am lazy lol
	std::vector<unsigned int> newHits;
	std::vector<unsigned int> deadEnemies;
	//TODO: Make a distance function for attack enemy and calculate AI to share

	for (int i = enemyStats.size() - 1; i >= 0; i--)
	{
		if (hitAlready(enemyStats.at(i), hitIDS))
			continue;

		double distance = sqrt(square(enemyStats.at(i).getPosition().x - weaponPosition.x) + square(enemyStats.at(i).getPosition().y - weaponPosition.y));

		if (distance <= PLAYER_SIZE)
		{
			enemyStats.at(i).adjustCurrentHealth(-weaponDamage);
			enemyStats.at(i).addAttacker(attackerID);
			if (enemyStats.at(i).getCurrentHealth() == 0)
				deadEnemies.push_back(i);
			newHits.push_back(enemyStats.at(i).getID());
		}
	}

	for (int i = 0; i < deadEnemies.size(); i++)
	{
		m_kdaVector.push_back(enemyStats.at(deadEnemies.at(i)).getKDAReport());
		enemyStats.erase(enemyStats.begin() + deadEnemies.at(i));
		m_enemyItems.erase(m_enemyItems.begin() + deadEnemies.at(i));
	}

	return newHits;
}

/// <summary>
/// Checks to see if the AI's ID is in the provided vector
/// </summary>
/// <param name="aiStats">- Reference to the AI's stats</param>
/// <param name="hitIDS">- The IDs of AI that have already been hit</param>
/// <returns></returns>
bool MapSection::hitAlready(AIStats& aiStats, std::vector<unsigned int> hitIDS)
{
	for (int i = 0; i < hitIDS.size(); i++)
	{
		if (aiStats.getID() == hitIDS.at(i))
			return true;
	}
	return false;
}

/// <summary>
/// Moves the positions of the AI in the section and performs AI attacks
/// </summary>
/// <param name="playerPositions">- Positions of all players</param>
/// <returns>All attacks the enemies launched onto the players</returns>
std::vector<glm::vec3> MapSection::progressAI(std::vector<glm::vec3> playerPositions)
{
	std::vector<glm::vec3> attackingPositions;
	for (int i = 0; i < enemyStats.size(); i++)
	{
		calculateAI(enemyStats.at(i), playerPositions, i);
		if (enemyStats.at(i).isAttacking() && enemyStats.at(i).getAtlasCoords().y != GUN)
		{
			glm::vec3 attackStats = enemyStats.at(i).getWeaponPosition();
			attackStats.z = m_enemyItems.at(i).getDamage();
			attackingPositions.push_back(attackStats);
		}
	}

	if (attackingPositions.size() == 0)
		return std::vector<glm::vec3>();
	else
		return attackingPositions;
}

/// <summary>
/// Moves the positions of the AI based on the closest player, and attempts to attack the player
/// </summary>
/// <param name="enemyStats">- Reference to the stats of the AI</param>
/// <param name="playerPositions">- Positions of all players</param>
/// <param name="index">- Index of the AI in the section vector</param>
void MapSection::calculateAI(AIStats& enemyStats, std::vector<glm::vec3> playerPositions, unsigned int index)
{
	// Find the closest Player
	unsigned int closestPlayerIndex = 0;
	double closestDistance = MAP_SECTION_SIZE + 1;

	for (int i = 0; i < playerPositions.size(); i++)
	{
		double result = sqrt(square(enemyStats.getPosition().x - playerPositions.at(i).x) + square(enemyStats.getPosition().y - playerPositions.at(i).y));
		if (result < closestDistance)
		{
			closestDistance = result;
			closestPlayerIndex = i;
		}
	}


	if (playerPositions.size() != 0)
	{
		aiMove(enemyStats, playerPositions.at(closestPlayerIndex), index);
		aiAttack(enemyStats, playerPositions.at(closestPlayerIndex), closestDistance, index);
	}
}

/// <summary>
/// Moves the position of the AI based on the closest player
/// </summary>
/// <param name="enemyStats">- Reference to the stats of the AI</param>
/// <param name="playerPosition">- Positions of all players</param>
/// <param name="index">- Index of the AI in the section vector</param>
void MapSection::aiMove(AIStats& enemyStats, glm::vec3 playerPosition, unsigned int index)
{
	// Find what direction the player is in and move to him.
	// Also used to angle the weapon towards the player's current position
	float aiSpeed = 0.1f;

	double numerator = enemyStats.getPosition().y - playerPosition.y;
	double denominator = enemyStats.getPosition().x - playerPosition.x;

	if (denominator == 0)
	{
		if (numerator >= 0)
		{
			enemyStats.move(DOWN);
			enemyStats.setWeaponAngle(180.0f);
			
		}
		else
		{
			enemyStats.move(UP);
			enemyStats.setWeaponAngle(0.0f);
		}
	}

	if (numerator < 0)
	{
		if (denominator < 0)
		{
			enemyStats.move(UP);
			enemyStats.move(RIGHT);
			enemyStats.setWeaponAngle((atan(numerator / denominator) * 180 / PI) - 90);
		}
		else
		{
			enemyStats.move(UP);
			enemyStats.move(LEFT);
			enemyStats.setWeaponAngle((atan(numerator / denominator) * 180 / PI) + 90);
		}
	}
	else
	{
		if (denominator < 0)
		{
			enemyStats.move(DOWN);
			enemyStats.move(RIGHT);
			enemyStats.setWeaponAngle((atan(numerator / denominator) * 180 / PI) - 90);
		}
		else
		{
			enemyStats.move(DOWN);
			enemyStats.move(LEFT);
			enemyStats.setWeaponAngle((atan(numerator / denominator) * 180 / PI) + 90);
		}
	}

	m_enemyItems.at(index).setPlayerPosition(enemyStats.getPosition());
	m_enemyItems.at(index).setWeaponAngle(enemyStats.getWeaponAngle());

	if (m_enemyItems.at(index).getAtlasCoordinates().y == GUN && enemyStats.getWeaponAngle() <= 0)
		m_enemyItems.at(index).setFlipped(true);
	else
		m_enemyItems.at(index).setFlipped(false);
}

/// <summary>
/// AI attempts an attack on the players based on their position
/// </summary>
/// <param name="enemyStats">- Reference to the stats of the AI</param>
/// <param name="playerPosition">- Position of the player we are trying to attack</param>
/// <param name="distance">- Distance between us and the player</param>
/// <param name="index">- Index of the AI in the section vector</param>
void MapSection::aiAttack(AIStats& enemyStats, glm::vec3 playerPosition, float distance, unsigned int index)
{
	//TODO: remove playerPositions
	if (enemyStats.isAttacking())
		return;

	if (enemyStats.getAtlasCoords().y == SWORD)
	{
		if (distance <= PLAYER_SIZE / 2)
		{
			enemyStats.clearHitIDS();
			enemyStats.setAttacking(true);
			m_enemyItems.at(index).attack(enemyStats.getWeaponAngle(), enemyStats.getPosition());
		}
		return;
	}
	else if (enemyStats.getAtlasCoords().y == SPEAR)
	{
		if (distance <= PLAYER_SIZE + (PLAYER_SIZE * 0.5f))
		{
			enemyStats.clearHitIDS();
			enemyStats.setAttacking(true);
			m_enemyItems.at(index).attack(enemyStats.getWeaponAngle(), enemyStats.getPosition());
		}
		return;
	}
	else if (enemyStats.getAtlasCoords().y == GUN)
	{
		if (enemyStats.getAtlasCoords().x == BASIC && distance <= MAP_SECTION_SIZE / 2)
		{
			enemyStats.clearHitIDS();
			enemyStats.setBulletCount(1);
			enemyStats.setAttacking(true);
			m_enemyItems.at(index).attack(enemyStats.getWeaponAngle(), enemyStats.getPosition());
		}
		else if (enemyStats.getAtlasCoords().x == RARE && distance <= PLAYER_SIZE * 3)
		{
			enemyStats.clearHitIDS();
			enemyStats.setBulletCount(3);
			enemyStats.setAttacking(true);
			m_enemyItems.at(index).attack(enemyStats.getWeaponAngle(), enemyStats.getPosition());
		}
		else if (enemyStats.getAtlasCoords().x == COMMON || enemyStats.getAtlasCoords().x == LEGENDARY)
		{
			enemyStats.clearHitIDS();
			enemyStats.setBulletCount(1);
			enemyStats.setAttacking(true);
			m_enemyItems.at(index).attack(enemyStats.getWeaponAngle(), enemyStats.getPosition());
		}
		return;
	}
}

/// <summary>
/// Adjusts the bounds of the mapSection based on its type
/// </summary>
/// <param name="mapType"></param>
void MapSection::adjustBounds(unsigned int mapType)
{
	//Vertical Hall image is drawn 512x512
	//The sides are cropped at 133 pixels from the sides
	//	133/512	= ?/sizeOfSection
	//	(sizeOfSection * 133) / 512 = amount to adjust

	if (mapType == MAP_VERTICAL_HALL)
	{
		m_rightBound = m_rightBound - MAP_CONNECTION_MARGIN_SIZE;
		m_leftBound = m_leftBound + MAP_CONNECTION_MARGIN_SIZE;
	}
	if (mapType == MAP_HORIZONTAL_HALL)
	{
		m_topBound = m_topBound - MAP_CONNECTION_MARGIN_SIZE;
		m_bottomBound = m_bottomBound + MAP_CONNECTION_MARGIN_SIZE;
	}
}