#include "Projectile.h"

/// <summary>
/// Creates all of the vectors needed to draw a projectile
/// </summary>
/// <param name="itemTexture">- Reference to the game's itemAtlas</param>
Projectile::Projectile(Texture& itemTexture)
{
	m_itemTexture = itemTexture;


	GLfloat thrownItemVertices[]
	{
		(-PLAYER_SIZE / 2), (-PLAYER_SIZE / 2), LAYER_THREE,	0.0f,0.0f,0.0f,			0.0f,  0.0f,
		(-PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_THREE,		0.0f,0.0f,0.0f,			0.0f,  0.25f,
		(PLAYER_SIZE / 2), (PLAYER_SIZE / 2), LAYER_THREE,		0.0f,0.0f,0.0f,			0.25f, 0.25f,
		(PLAYER_SIZE / 2), (-PLAYER_SIZE / 2), LAYER_THREE,		0.0f,0.0f,0.0f,			0.25f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(thrownItemVertices, sizeof(thrownItemVertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	m_vaoList[0] = VAO1;


	GLfloat bulletVertices[]
	{
		(-((PLAYER_SIZE/10))/2),	 -((PLAYER_SIZE / 10)),	LAYER_THREE, 0.0f,0.0f,1.0f,
		(-((PLAYER_SIZE / 10)) / 2),  (PLAYER_SIZE / 10),	LAYER_THREE, 0.0f,0.0f,1.0f,
		( ((PLAYER_SIZE / 10)) / 2),  (PLAYER_SIZE / 10),	LAYER_THREE, 0.0f,0.0f,1.0f,
		( ((PLAYER_SIZE / 10)) / 2), -((PLAYER_SIZE / 10)),	LAYER_THREE, 0.0f,0.0f,1.0f
	};


	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(bulletVertices, sizeof(bulletVertices));
	EBO1.Bind();
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO1.Unbind();

	m_vaoList[1] = VAO2;

	GLfloat enemyBulletVertices[]
	{
		(-((PLAYER_SIZE / 10)) / 2),	 -((PLAYER_SIZE / 10)),	LAYER_THREE, 1.0f,0.0f,0.0f,
		(-((PLAYER_SIZE / 10)) / 2),  (PLAYER_SIZE / 10),	LAYER_THREE, 1.0f,0.0f,0.0f,
		(((PLAYER_SIZE / 10)) / 2),  (PLAYER_SIZE / 10),	LAYER_THREE, 1.0f,0.0f,0.0f,
		(((PLAYER_SIZE / 10)) / 2), -((PLAYER_SIZE / 10)),	LAYER_THREE, 1.0f,0.0f,0.0f
	};


	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(enemyBulletVertices, sizeof(enemyBulletVertices));
	EBO1.Bind();
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO1.Unbind();

	m_vaoList[2] = VAO3;
}

/// <summary>
/// Deletes the VAO bufferes after use
/// </summary>
Projectile::~Projectile()
{
	m_vaoList[0].Delete();
	m_vaoList[1].Delete();
	m_vaoList[2].Delete();
	//TODO: check and see if we should have kept the ebo and vbo or deleted them
}

/// <summary>
/// Draws all projectiles fired
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
void Projectile::drawProjectiles(Shader& shader, Camera& camera)
{
	for (int i = 0; i < thrownItemVector.size(); i++)
	{
		m_itemTexture.Bind();

		float xAddition = thrownItemVector.at(i).atlasCoords.x * .25;
		float yAddition = thrownItemVector.at(i).atlasCoords.y * .25;
		glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasX"), xAddition);
		glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasY"), yAddition);

		m_vaoList[0].Bind();
		camera.Matrix(shader, thrownItemVector.at(i).Position, thrownItemVector.at(i).itemAngle);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		m_vaoList[0].Unbind();
		m_itemTexture.Unbind();
		glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasX"), 0);
		glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasY"), 0);
	}

	for (int i = 0; i < bulletVector.size(); i++)
	{
		m_vaoList[1].Bind();

		camera.Matrix(shader, bulletVector.at(i).Position, bulletVector.at(i).itemAngle);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		m_vaoList[1].Unbind();
	}

	for (int i = 0; i < m_aiBullets.size(); i++)
	{
		m_vaoList[2].Bind();
		camera.Matrix(shader, m_aiBullets.at(i).Position, m_aiBullets.at(i).itemAngle);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		m_vaoList[2].Unbind();
	}
}

/// <summary>
/// Moves the projectiles along their movement vectors
/// </summary>
/// <param name="mapSections">- Reference to the games mapSections</param>
void Projectile::moveProjectiles(std::vector<MapSection>& mapSections)
{
	std::vector<unsigned int> groundedProjectiles;
	std::vector<unsigned int> usedBullets;
	std::vector<unsigned int> enemyUsedBullets;

	//	Thrown Item Movement
	for (int i = 0; i < thrownItemVector.size(); i++)
	{
		std::vector<int> result = mapSections.at(thrownItemVector.at(i).roomID).withinBounds(thrownItemVector.at(i).Position, thrownItemVector.at(i).movementVector, PLAYER_SIZE, PLAYER_SIZE, -1);

		if (thrownItemVector.at(i).roomID == result.at(0))
		{
			thrownItemVector.at(i).Position += thrownItemVector.at(i).movementVector * thrownItemVector.at(i).itemSpeed;
			if (thrownItemVector.at(i).atlasCoords.x == BASIC || thrownItemVector.at(i).atlasCoords.x == RARE)
				thrownItemVector.at(i).itemAngle += 2.0f;
		}
		else
		{
			bool grounded = true;

			for (int resultIndex = 0; resultIndex < 4; resultIndex++)
			{
				if (result.at(resultIndex) != -1)
				{
					std::vector<int> enteringResult = mapSections.at(result.at(resultIndex)).withinBounds(thrownItemVector.at(i).Position, thrownItemVector.at(i).movementVector, PLAYER_SIZE, PLAYER_SIZE, thrownItemVector.at(i).roomID);
					if (enteringResult.at(0) != -1)
					{
						thrownItemVector.at(i).roomID = enteringResult.at(0);
						thrownItemVector.at(i).Position += thrownItemVector.at(i).movementVector * thrownItemVector.at(i).itemSpeed;

						if (thrownItemVector.at(i).atlasCoords.x == BASIC)
							thrownItemVector.at(i).itemAngle += 2.0f;

						grounded = false;
						break;
					}
				}
			}

			if (grounded)
			{
				groundedProjectiles.push_back(i);
				groundedItems.push_back(thrownItemVector.at(i));
			}
		}
	}

	//	Bullet Movement
	for (int i = 0; i < bulletVector.size(); i++)
	{
		std::vector<int> result = mapSections.at(bulletVector.at(i).roomID).withinBounds(bulletVector.at(i).Position, bulletVector.at(i).movementVector, PLAYER_SIZE - (PLAYER_SIZE / 10), PLAYER_SIZE - (PLAYER_SIZE / 5), -1);

		if (bulletVector.at(i).roomID == result.at(0))
			bulletVector.at(i).Position += bulletVector.at(i).movementVector * bulletVector.at(i).itemSpeed;
		else
		{
			bool hitWall = true;

			for (int resultIndex = 0; resultIndex < 4; resultIndex++)
			{
				if (result.at(resultIndex) != -1)
				{
					std::vector<int> enteringResult = mapSections.at(result.at(resultIndex)).withinBounds(bulletVector.at(i).Position, bulletVector.at(i).movementVector, PLAYER_SIZE - (PLAYER_SIZE / 10), PLAYER_SIZE - (PLAYER_SIZE / 5), bulletVector.at(i).roomID);
					if (enteringResult.at(0) != -1)
					{
						bulletVector.at(i).roomID = enteringResult.at(0);
						bulletVector.at(i).Position += bulletVector.at(i).movementVector * bulletVector.at(i).itemSpeed;

						hitWall = false;
						break;
					}
				}
			}

			if (hitWall)
				usedBullets.push_back(i);
		}
	}

	// AI Bullet Movement
	for (int i = 0; i < m_aiBullets.size(); i++)
	{
		std::vector<int> result = mapSections.at(m_aiBullets.at(i).roomID).withinBounds(m_aiBullets.at(i).Position, m_aiBullets.at(i).movementVector, PLAYER_SIZE - (PLAYER_SIZE / 10), PLAYER_SIZE - (PLAYER_SIZE / 5), -1);

		if (m_aiBullets.at(i).roomID == result.at(0))
			m_aiBullets.at(i).Position += m_aiBullets.at(i).movementVector * m_aiBullets.at(i).itemSpeed;
		else
		{
			bool hitWall = true;

			for (int resultIndex = 0; resultIndex < 4; resultIndex++)
			{
				if (result.at(resultIndex) != -1)
				{
					std::vector<int> enteringResult = mapSections.at(result.at(resultIndex)).withinBounds(m_aiBullets.at(i).Position, m_aiBullets.at(i).movementVector, PLAYER_SIZE - (PLAYER_SIZE / 10), PLAYER_SIZE - (PLAYER_SIZE / 5), m_aiBullets.at(i).roomID);
					if (enteringResult.at(0) != -1)
					{
						m_aiBullets.at(i).roomID = enteringResult.at(0);
						m_aiBullets.at(i).Position += m_aiBullets.at(i).movementVector * m_aiBullets.at(i).itemSpeed;

						hitWall = false;
						break;
					}
				}
			}

			if (hitWall)
				enemyUsedBullets.push_back(i);
		}
	}





	//	Remove Items and bullets that hit the wall
	for (int i = groundedProjectiles.size() - 1; i >= 0; i--)
	{
		thrownItemVector.erase(thrownItemVector.begin() + groundedProjectiles.at(i));
	}

	for (int i = usedBullets.size() - 1; i >= 0; i--)
	{
		bulletVector.erase(bulletVector.begin() + usedBullets.at(i));
	}

	for (int i = enemyUsedBullets.size() - 1; i >= 0; i--)
	{
		m_aiBullets.erase(m_aiBullets.begin() + enemyUsedBullets.at(i));
	}
}

/// <summary>
/// clears the vector of grounded projectiles
/// </summary>
void Projectile::clearGroundedProjectiles()
{
	groundedItems.clear();
}

/// <summary>
/// Removes all of the [;ayer bullets that hit an AI
/// </summary>
/// <param name="bulletHitIndexes"></param>
void Projectile::playerBulletHits(std::vector<unsigned int> bulletHitIndexes)
{
	for (int i = bulletHitIndexes.size() - 1; i >= 0; i--)
	{
		bulletVector.erase(bulletVector.begin() + bulletHitIndexes.at(i));
	}
}

/// <summary>
/// Removes all of the ai bullets that hit a player
/// </summary>
/// <param name="bulletHitIndexes"></param>
void Projectile::aiBulletHits(std::vector<unsigned int> bulletHitIndexes)
{
	for (int i = bulletHitIndexes.size() - 1; i >= 0; i--)
	{
		m_aiBullets.erase(m_aiBullets.begin() + bulletHitIndexes.at(i));
	}
}

/// <summary>
/// Takes in values of the item that the player wants to throw and adds it to our vectors
/// </summary>
/// <param name="atlasCoords">- Atlas coordinates of the item being thrown</param>
/// <param name="startPosition">- Starting position of the item being thrown</param>
/// <param name="movementVector">- Vector to move the item along</param>
/// <param name="itemSpeed">- The speed of the item being thrown</param>
/// <param name="roomID">- ID of the room the item is starting in</param>
/// <param name="itemAngle">- Starting angle of the item being thrown</param>
void Projectile::throwItem(glm::vec2 atlasCoords, glm::vec3 startPosition, glm::vec3 movementVector, float itemSpeed, unsigned int roomID, float itemAngle, float itemDamage, unsigned int attackerID)
{
	thrownItemVector.push_back(thrownItem(atlasCoords, startPosition, movementVector, itemSpeed, roomID, itemAngle, itemDamage, attackerID));
}

/// <summary>
/// Takes in values of the bullet being shot by the player and adds it to our vectors
/// </summary>
/// <param name="startPosition">- Starting position of the bullet</param>
/// <param name="movementVector">- Vector to move the bullet along</param>
/// <param name="itemSpeed">- Speed of the bullet</param>
/// <param name="roomID">- ID of the room the bullet is starting in</param>
/// <param name="bulletAngle">- Starting angle of the bullet being shot</param>
void Projectile::shootBullet(glm::vec3 startPosition, glm::vec3 movementVector, float itemSpeed, unsigned int roomID, float bulletAngle, float bulletDamage, unsigned int attackerID)
{
	bulletVector.push_back(bullet(startPosition, movementVector, itemSpeed, roomID, bulletAngle, bulletDamage, attackerID));
}

/// <summary>
/// Takes in data for a bullet being shot by the AI and
/// bulletData.z is the angle of the bullet being shot
/// </summary>
/// <param name="bulletData">- Position and angle of the bullet</param>
/// <param name="roomID">- ID of the room the bullet is starting in</param>
void Projectile::addAIBullet(glm::vec4 bulletData, unsigned int roomID)
{
	float bulletAngle = bulletData.z;
	float bulletDamage = bulletData.w;
	bulletData.z = 0;
	bulletData.w = 0;

	glm::vec3 movementVector = { cos(glm::radians(bulletAngle + 90)), sin(glm::radians(bulletAngle + 90)), 0.0f };
	m_aiBullets.push_back(bullet(bulletData, movementVector, 1.0f, roomID, bulletAngle, bulletDamage, 0));
}

/// <summary>
/// Clears all projectile vectors
/// </summary>
void Projectile::clearProjectiles()
{
	bulletVector.clear();
	m_aiBullets.clear();
	thrownItemVector.clear();
	groundedItems.clear();
}

/// <summary>
/// Returns all grounded projectiles
/// </summary>
/// <returns></returns>
std::vector<Projectile::thrownItem> Projectile::getGroundedProjectiles()
{
	return groundedItems;
}

/// <summary>
/// Returns all throwable items
/// </summary>
/// <returns></returns>
std::vector<Projectile::thrownItem>& Projectile::getProjectiles()
{
	return thrownItemVector;
}

/// <summary>
/// Returns all player bullets that have been fired and arent destroyed
/// </summary>
/// <returns></returns>
std::vector<Projectile::bullet>& Projectile::getPlayerBullets()
{
	return bulletVector;
}

/// <summary>
/// Returns all AI bullets that have been fired and arent destroyed
/// </summary>
/// <returns></returns>
std::vector<Projectile::bullet>& Projectile::getAIBullets()
{
	return m_aiBullets;
}