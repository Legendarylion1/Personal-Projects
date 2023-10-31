#include "Renderer.h"

void Renderer::setup(GLFWwindow* window)
{
	m_window = window;
	m_shader = Shader("default.vert", "default.frag");
	m_textRenderer = TextRenderer(&m_shader, WIDTH, HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_playerTexture = Texture("Images/Sprite.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_playerTexture.texUnit(m_shader, "tex0", 0);

	m_aiTexture = Texture("Images/aiSprite.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_aiTexture.texUnit(m_shader, "tex0", 0);

	m_grassTexture = Texture("Images/Map/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_grassTexture.texUnit(m_shader, "tex0", 0);

	m_pokeballTexture = Texture("Images/Map/Pokeball.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_pokeballTexture.texUnit(m_shader, "tex0", 0);

	m_boxTexture = Texture("Images/boxOutline.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_boxTexture.texUnit(m_shader, "tex0", 0);

	m_buyMenuTexture = Texture("Images/buyMenu.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_buyMenuTexture.texUnit(m_shader, "tex0", 0);

	m_exclamationTexture = Texture("Images/exclamation.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_exclamationTexture.texUnit(m_shader, "tex0", 0);

	setupPokemonRenderPositions();
}

void Renderer::setState(unsigned int newState)
{
	m_state = newState;
}

void Renderer::setTrainer(Trainer* trainer)
{
	m_trainer = trainer;
}

void Renderer::setPokemon(Pokemon* playerPokemon, Pokemon* opponentPokemon)
{
	m_playerPokemon = playerPokemon;
	m_opponentPokemon = opponentPokemon;
}

void Renderer::setBagIndex(unsigned int index)
{
	m_bagIndex = index;
}

void Renderer::setTextBox(std::string topLine, std::string bottomLine)
{
	m_topLine = topLine;
	m_botLine = bottomLine;
}

void Renderer::setAwaitClick(bool awaitClick)
{
	m_awaitClick = awaitClick;
}

void Renderer::setMapStats(std::string texturePath, int width, int height)
{
	m_mapTexture = Texture(texturePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_backgroundWidth = width * TILE_MULTIPLIER;
	m_backgroundHeight = height * TILE_MULTIPLIER;
}

void Renderer::setPlayerState(float playerX, float playerY, unsigned int walkDirection, unsigned int walkState)
{
	setPlayerAnimation(walkDirection, walkState);
	setPlayerCoords(playerX, playerY);
}

void Renderer::setPlayerCoords(float playerX, float playerY)
{
	m_playerX = playerX;
	m_playerY = playerY;

	float halfOfTileSize = (TILE_SIZE * TILE_MULTIPLIER) / 2.0f;

	m_camPosition = glm::vec3(m_playerX - (WIDTH / 2) + halfOfTileSize, m_playerY - (HEIGHT / 2) + halfOfTileSize, 0.0f);
}

void Renderer::setPlayerAnimation(unsigned int walkDirection, unsigned int walkState)
{
	playerWalkingDirection = walkDirection;
	playerWalkingState = walkState;
}

void Renderer::setGrassPosition(int x, int y)
{
	m_grassPositions.erase(m_grassPositions.begin());

	if (x != -1 && y != -1)
		m_grassPositions.push_back(glm::vec2(x * (TILE_SIZE * TILE_MULTIPLIER), y * (TILE_SIZE * TILE_MULTIPLIER)));
	else
		m_grassPositions.push_back(glm::vec2(-1.0f, -1.0f));
}

void Renderer::setRosterIndex(unsigned int index)
{
	m_rosterIndex = index;
}

void Renderer::setEncounter(bool inEncounter)
{
	m_inEncounter = inEncounter;
}

void Renderer::onUpdate()
{

	glClear(GL_COLOR_BUFFER_BIT);
	m_shader.Activate();

	if (m_state == DEFAULT_ENCOUNTER)
		drawDefaultEncounter();
	else if (m_state == SELECT_ATTACK)
	{
		drawAttacks();
	}
	else if (m_state == SELECT_POKEMON)
	{
		drawPokemonSelect();
	}
	else if (m_state == SELECT_ITEM)
	{
		drawItems();
	}
	else if (m_state == DISPLAY_MAP)
	{
		drawMap();
	}
	else if (m_state == DISPLAY_ESCAPE)
	{
		drawEscapeMenu();
	}
	else if (m_state == DISPLAY_PC)
	{
		drawPC();
	}
	else if (m_state == DISPLAY_BUY_ITEMS)
	{
		drawBuyItems();
	}


	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Renderer::shutdown()
{
	m_shader.Delete();
}

void Renderer::drawDefaultEncounter()
{	
	drawFightingPokemon();
	drawTextBox();

	Texture mapUpImage("Images/playerOptionSelectResized.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mapUpImage.texUnit(m_shader, "tex0", 0);

	GLfloat optionSelect[]
	{

		//Bottom Display Bar

		(WIDTH / 2) + 10,	0.0f,		0.0f, 				0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		(WIDTH / 2) + 10,	(HEIGHT / 4) - 5.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		WIDTH - 10,		(HEIGHT / 4) - 5.0f, 0.0f,			0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		WIDTH - 10,		0.0f,		0.0f,					0.0f, 0.0f, 0.0f,		1.0f, 0.0f// BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2,0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2,1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2,2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


	mapUpImage.Bind();
	VAO2.Bind();

	//positionCamera(glm::vec3(0.0f, 0.0f, 0.0f));
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(m_proj));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();

	mapUpImage.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	mapUpImage.Delete();

	drawDownArrow();
}

void Renderer::drawAttacks()
{
	//m_shader.Activate();

	drawFightingPokemon();

	Texture mapUpImage("Images/selectAttackResized.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mapUpImage.texUnit(m_shader, "tex0", 0);

	GLfloat optionSelect[]
	{

		//Bottom Display Bar

		(WIDTH / 2) - 475.0f,	10.0f,	0.0f, 		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		(WIDTH / 2) - 475.0f,	250.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		(WIDTH / 2) + 475.0f,	250.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		(WIDTH / 2) + 475.0f,	10.0f,	0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f// BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


	mapUpImage.Bind();
	VAO2.Bind();

	//positionCamera(glm::vec3(0.0f, 0.0f, 0.0f));
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(m_proj));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();

	mapUpImage.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	mapUpImage.Delete();


	float verticalDifference = 125.0f;
	float horizontalDifference = 480.0f;

	int index = 0;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if (m_playerPokemon->getAttack(index).getMaxPP() == 0)
			{
				m_textRenderer.renderText("NONE", 765.0f + (horizontalDifference * x), 175.0f - (verticalDifference * y), 40, CENTER_ALIGN, WHITE);
				index++;
				continue;
			}
			m_textRenderer.renderText(m_playerPokemon->getAttack(index).getName(), 515.0f + (horizontalDifference * x), 185.0f - (verticalDifference * y), 40, LEFT_ALIGN, WHITE);

			std::string pp = std::to_string(m_playerPokemon->getAttack(index).getCurrentPP()) + "-" + std::to_string(m_playerPokemon->getAttack(index).getMaxPP());
			m_textRenderer.renderText(pp, 1005.0f + (horizontalDifference * x), 155.0f - (verticalDifference * y), 40, RIGHT_ALIGN, WHITE);
			index++;
		}
	}
}

void Renderer::drawPokemonSelect()
{
	//m_shader.Activate();

	if (m_inEncounter)
		drawFightingPokemon();
	else
		drawMap();
	drawBackGroundBlur();

	Texture mapUpImage("Images/selectPokemonResized.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mapUpImage.texUnit(m_shader, "tex0", 0);

	float pokemonSelectWidth = 930.0f;
	float pokemonSelectHeight = 365.0f;

	GLfloat optionSelect[]
	{

		//Bottom Display Bar

		(WIDTH / 2) - (pokemonSelectWidth / 2),	(HEIGHT / 2) - (pokemonSelectHeight / 2), 0.0f, 	0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		(WIDTH / 2) - (pokemonSelectWidth / 2),	(HEIGHT / 2) + (pokemonSelectHeight / 2), 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		(WIDTH / 2) + (pokemonSelectWidth / 2),	(HEIGHT / 2) + (pokemonSelectHeight / 2), 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		(WIDTH / 2) + (pokemonSelectWidth / 2),	(HEIGHT / 2) - (pokemonSelectHeight / 2), 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f  // BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


	mapUpImage.Bind();
	VAO2.Bind();

	if (!m_inEncounter)
		positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();

	mapUpImage.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	mapUpImage.Delete();

	float horizontalDifference = 485.0f;
	float verticalDiffererence = 135.0f;

	int count = 0;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 2; x++)
		{

			if (m_trainer->getPokemon(count)->getLevel() == 0)
			{
				m_textRenderer.renderText("NONE", 525.0f + (horizontalDifference * x) + 223.0f, 650.0f - (verticalDiffererence * y), 40, CENTER_ALIGN, WHITE);
				count++;
				continue;
			}

			m_textRenderer.renderText(m_trainer->getPokemon(count)->getName(), 525.0f + (horizontalDifference * x), 670.0f - (verticalDiffererence * y), 40, LEFT_ALIGN, WHITE);


			std::string level = "Lv" + std::to_string(m_trainer->getPokemon(count)->getLevel());
			std::string health = std::to_string(m_trainer->getPokemon(count)->getHealth()) + "-" + std::to_string(m_trainer->getPokemon(count)->getMaxHealth());
			m_textRenderer.renderText(level, 525.0f + (horizontalDifference * x), 670.0f - (verticalDiffererence * y) - 35, 40, LEFT_ALIGN, WHITE);
			m_textRenderer.renderText(health, 525.0f + (horizontalDifference * x) + 475.0f, 670.0f - (verticalDiffererence * y) - 35, 40, RIGHT_ALIGN, WHITE);
			count++;
		}
	}
}

void Renderer::drawItems()
{
	//m_shader.Activate();

	if (m_inEncounter)
		drawFightingPokemon();
	else
		drawMap();
	drawBackGroundBlur();

	Texture mapUpImage("Images/selectItemResized.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mapUpImage.texUnit(m_shader, "tex0", 0);

	float itemSelectWidth = 445.0f;
	float itemSelectHeight = 905.0f;

	GLfloat optionSelect[]
	{

		//Bottom Display Bar

		(WIDTH / 2) - (itemSelectWidth / 2),	(HEIGHT / 2) - (itemSelectHeight / 2), 0.0f, 		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		(WIDTH / 2) - (itemSelectWidth / 2),	(HEIGHT / 2) + (itemSelectHeight / 2), 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		(WIDTH / 2) + (itemSelectWidth / 2),	(HEIGHT / 2) + (itemSelectHeight / 2), 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		(WIDTH / 2) + (itemSelectWidth / 2),	(HEIGHT / 2) - (itemSelectHeight / 2), 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f  // BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


	mapUpImage.Bind();
	VAO2.Bind();

	if (!m_inEncounter)
		positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();

	mapUpImage.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	mapUpImage.Delete();


	int pokeballCount = m_trainer->getUniquePokeballCount();
	int healCount = m_trainer->getUniqueHealCount();
	int miscCount = m_trainer->getUniqueMiscCount();

	int totalCount = pokeballCount + healCount + miscCount;



	float verticalDiffererence = 135.0f;

	int pCount = 0;
	int hCount = 0;
	int mCount = 0;

	for (int y = m_bagIndex; y < m_bagIndex + 5; y++)
	{

		if (y >= totalCount)
		{
			// NONE Print
			m_textRenderer.renderText("NONE", 1000.0f, 837.5f - (verticalDiffererence * y) - 35, 40, CENTER_ALIGN, WHITE);
		}
		else if (y < pokeballCount)
		{
			// Pokeball
			m_textRenderer.renderText(m_trainer->getPokeball(pCount)->getName(), 1000.0f, 837.5f - (verticalDiffererence * y) - 35, 40, CENTER_ALIGN, WHITE);

			std::string typeCount = "x" + std::to_string(m_trainer->getPokeballTypeCount(pCount));
			m_textRenderer.renderText(typeCount, 1200.0f, 837.5f - (verticalDiffererence * y) - 35, 40, RIGHT_ALIGN, WHITE);
			pCount++;
		}
		else if (y < pokeballCount + healCount)
		{
			// Heal
			m_textRenderer.renderText(m_trainer->getHealItem(hCount)->getName(), 1000.0f, 837.5f - (verticalDiffererence * y) - 35, 40, CENTER_ALIGN, WHITE);

			std::string typeCount = "x" + std::to_string(m_trainer->getHealTypeCount(hCount));
			m_textRenderer.renderText(typeCount, 1200.0f, 837.5f - (verticalDiffererence * y) - 35, 40, RIGHT_ALIGN, WHITE);
			hCount++;
		}
		else if (y < pokeballCount + healCount + miscCount)
		{
			// MISC
			m_textRenderer.renderText(m_trainer->getMiscItem(mCount)->getName(), 1000.0f, 837.5f - (verticalDiffererence * y) - 35, 40, CENTER_ALIGN, WHITE);

			std::string typeCount = "x" + std::to_string(m_trainer->getMiscTypeCount(mCount));
			m_textRenderer.renderText(typeCount, 1200.0f, 837.5f - (verticalDiffererence * y) - 35, 40, RIGHT_ALIGN, WHITE);
			mCount++;
		}
	}
}

void Renderer::drawFightingPokemon()
{
	Texture mapUpImage("Images/fightUIHPResized.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mapUpImage.texUnit(m_shader, "tex0", 0);

	GLfloat fightUI[]
	{
		//TOP Environment
		0.0f,  HEIGHT / 4, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f,  HEIGHT	 , 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		WIDTH, HEIGHT	 , 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		WIDTH, HEIGHT / 4, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,

	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	mapUpImage.Bind();
	VAO1.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	mapUpImage.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	mapUpImage.Delete();





	// P1 HealthBar

	float p1HealthWidth = (m_playerPokemon->getHealth() * 458.0f) / m_playerPokemon->getMaxHealth();
	GLfloat p1HealthBar[]
	{
		//TOP Environment
		1430.0f,					425.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		1430.0f,					475.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		1430.0f + p1HealthWidth,	475.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		1430.0f + p1HealthWidth,	425.0f, 0.0f,		0.0f, 1.0f, 0.0f,

	};

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(p1HealthBar, sizeof(p1HealthBar));
	EBO EBO3(indices1, sizeof(indices1));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	VAO3.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO3.Unbind();

	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();




	//Opponent Pokemon Healthbar

	// P1 HealthBar

	float opponentHealthWidth = (m_opponentPokemon->getHealth() * 332.0f) / m_opponentPokemon->getMaxHealth();
	GLfloat opponentHealthBar[]
	{
		//TOP Environment
		360.0f,							795.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		360.0f,							839.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		360.0f + opponentHealthWidth,	839.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		360.0f + opponentHealthWidth,	795.0f, 0.0f,		0.0f, 1.0f, 0.0f,

	};

	VAO VAO4;
	VAO4.Bind();

	VBO VBO4(opponentHealthBar, sizeof(opponentHealthBar));
	EBO EBO4(indices1, sizeof(indices1));

	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	VAO4.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO4.Unbind();

	VAO4.Delete();
	VBO4.Delete();
	EBO4.Delete();





	// Player 1 XP
	float p1XPWidth = (m_playerPokemon->getCurrentXP() * 726.0f) / m_playerPokemon->getXPNeeded();

	GLfloat p1XPBar[]
	{
		//TOP Environment
		1128.0f,				304.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		1128.0f,				331.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		1128.0f + p1XPWidth,	331.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		1128.0f + p1XPWidth,	304.0f, 0.0f,		0.0f, 0.0f, 1.0f,

	};

	VAO VAO5;
	VAO5.Bind();

	VBO VBO5(p1XPBar, sizeof(p1XPBar));
	EBO EBO5(indices1, sizeof(indices1));

	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();

	VAO5.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO5.Unbind();

	VAO5.Delete();
	VBO5.Delete();
	EBO5.Delete();




	// P1 Text
	m_textRenderer.renderText(m_playerPokemon->getName(), 1060.0f, 510.0f, 60, LEFT_ALIGN, WHITE);

	std::string playerLevel = "Lv" + std::to_string(m_playerPokemon->getLevel());
	m_textRenderer.renderText(playerLevel, 1910.0f, 510.0f, 60, RIGHT_ALIGN, WHITE);

	std::string health = std::to_string(m_playerPokemon->getHealth()) + "-" + std::to_string(m_playerPokemon->getMaxHealth());
	m_textRenderer.renderText(health, 1730.0f, 350.0f, 60, CENTER_ALIGN, WHITE);


	//Opponent Text
	m_textRenderer.renderText(m_opponentPokemon->getName(), 20.0f, 855.0f, 60, LEFT_ALIGN, WHITE);

	std::string opponentLevel = "Lv" + std::to_string(m_opponentPokemon->getLevel());
	m_textRenderer.renderText(opponentLevel, 692.0f, 860.0f, 60, RIGHT_ALIGN, WHITE);



	GLfloat characterVertices[]
	{

		//Bottom Display Bar

		0.0f,	0.0f,		0.0f, 		0.0f, 1.0f, 0.0f,	// Bottom Left
		0.0f,	HEIGHT / 4, 0.0f,		0.0f, 1.0f, 0.0f,	// TOP LEFT
		WIDTH,	HEIGHT / 4, 0.0f,		0.0f, 1.0f, 0.0f,	// TOP RIGHT
		WIDTH,	0.0f,		0.0f,		0.0f, 1.0f, 0.0f,	// BOTTOM RIGHT

	};

	GLuint indices[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO6;
	VAO6.Bind();

	VBO VBO6(characterVertices, sizeof(characterVertices));
	EBO EBO6(indices, sizeof(indices));

	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();


	VAO6.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO6.Unbind();

	VAO6.Delete();
	VBO6.Delete();
	EBO6.Delete();



	//	Player Pokemon
	{
		// TODO: Load Sheets when the battle starts to prevent constant deleting
		// 512 comes from 32 pixel size of images times 16
		// 150 may also need to be scalable
		pokemonRenderData renderData = species_render_data[m_playerPokemon->getSpecies().getID()];

		Texture playerPokemonSheet(species_Sheets_Back[renderData.sheetNumber], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		playerPokemonSheet.texUnit(m_shader, "tex0", 0);

		GLfloat fightUI[]
		{
			//TOP Environment
			150.0f,  HEIGHT / 4, 0.0f,							0.0f, 0.0f, 0.0f,		renderData.xCoord, renderData.yCoord,
			150.0f,  (HEIGHT / 4) + 512.0f , 0.0f,				0.0f, 0.0f, 0.0f,		renderData.xCoord, renderData.yCoord + POKEMON_SHEET_ROW_SIZE,
			150.0f + 512.0f, (HEIGHT / 4) + 512.0f , 0.0f,		0.0f, 0.0f, 0.0f,		renderData.xCoord + POKEMON_SHEET_COL_SIZE, renderData.yCoord + POKEMON_SHEET_ROW_SIZE,
			150.0f + 512.0f, HEIGHT / 4, 0.0f,					0.0f, 0.0f, 0.0f,		renderData.xCoord + POKEMON_SHEET_COL_SIZE, renderData.yCoord,

		};

		GLuint indices1[] =
		{
			//BOTTOM Display Bar
			0, 2, 1,
			0, 3, 2
		};

		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(fightUI, sizeof(fightUI));
		EBO EBO1(indices1, sizeof(indices1));

		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();


		playerPokemonSheet.Bind();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		VAO1.Unbind();

		playerPokemonSheet.Unbind();

		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();

		playerPokemonSheet.Delete();
	}
	


	//	Opposing Pokemon
	{
		//TODO: Hardcode the values
		//448 comes from 32 pixel size of images times 14
		pokemonRenderData renderData = species_render_data[m_opponentPokemon->getSpecies().getID()];

		Texture opponentPokemonSheet(species_Sheets_Front[renderData.sheetNumber], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		opponentPokemonSheet.texUnit(m_shader, "tex0", 0);

		GLfloat fightUI[]
		{
			//TOP Environment
			WIDTH - 300.0f - 384.0f,	HEIGHT - 76.0f - 384.0f, 0.0f,	0.0f, 0.0f, 0.0f,		renderData.xCoord, renderData.yCoord,
			WIDTH - 300.0f - 384.0f,	HEIGHT - 76.0f			, 0.0f,	0.0f, 0.0f, 0.0f,		renderData.xCoord, renderData.yCoord + POKEMON_SHEET_ROW_SIZE,
			WIDTH - 300.0f,				HEIGHT - 76.0f			, 0.0f,	0.0f, 0.0f, 0.0f,		renderData.xCoord + POKEMON_SHEET_COL_SIZE, renderData.yCoord + POKEMON_SHEET_ROW_SIZE,
			WIDTH - 300.0f,				HEIGHT - 76.0f - 384.0f, 0.0f,	0.0f, 0.0f, 0.0f,		renderData.xCoord + POKEMON_SHEET_COL_SIZE, renderData.yCoord,

		};

		GLuint indices1[] =
		{
			//BOTTOM Display Bar
			0, 2, 1,
			0, 3, 2
		};

		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(fightUI, sizeof(fightUI));
		EBO EBO1(indices1, sizeof(indices1));

		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();


		opponentPokemonSheet.Bind();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		VAO1.Unbind();

		opponentPokemonSheet.Unbind();

		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();

		opponentPokemonSheet.Delete();
	}

}

void Renderer::setupPokemonRenderPositions()
{
	//Row = y and Col = x
	// TODO: This needs to be adjusted for the Y col
	//		 Y goes from the bottom right not from the top right, I think

	for (auto& renderData : species_render_data)
	{
		unsigned int index = renderData.second.sheetIndex;

		unsigned int rowPos = floor(index / POKEMON_SHEET_ROWS);
		unsigned int colPos = index % POKEMON_SHEET_COLS;

		//Flip Coord from top left to bottom left
		rowPos = (POKEMON_SHEET_ROWS - 1) - rowPos;

		renderData.second.xCoord = colPos * POKEMON_SHEET_COL_SIZE;
		renderData.second.yCoord = rowPos * POKEMON_SHEET_ROW_SIZE; 
	}
}

void Renderer::drawDownArrow()
{
	if (!m_awaitClick)
		return;

	m_awaitClick = false;

	if (m_state == DEFAULT_ENCOUNTER)
		m_textRenderer.renderText("V", 800, 60, 50, CENTER_ALIGN, BLACK);
	else
		m_textRenderer.renderText("V", 1760, 60, 50, CENTER_ALIGN, BLACK);
}

void Renderer::drawPlayer()
{

	float playerWidth =  TILE_SIZE * TILE_MULTIPLIER;
	float playerHeight = TILE_SIZE * TILE_MULTIPLIER;

	GLfloat fightUI[]
	{
		//TOP Environment
		0.0f, 0.0f, 0.0f,					0.0f, 0.0f, 0.0f,		(playerWalkingState * 0.333f), (playerWalkingDirection * 0.25f),
		0.0f, playerHeight, 0.0f,			0.0f, 0.0f, 0.0f,		(playerWalkingState * 0.333f), (playerWalkingDirection * 0.25f) + 0.25f,
		playerWidth,playerHeight, 0.0f,		0.0f, 0.0f, 0.0f,		(playerWalkingState * 0.333f) + 0.333f, (playerWalkingDirection * 0.25f) + 0.25f,
		playerWidth, 0.0f, 0.0f,			0.0f, 0.0f, 0.0f,		(playerWalkingState * 0.333f) + 0.333f, (playerWalkingDirection * 0.25f),
	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	m_playerTexture.Bind();
	VAO1.Bind();

	positionCamera(glm::vec3(m_playerX, m_playerY, 0.0f));
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(m_proj));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();

	m_playerTexture.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::drawGrass()
{

	for (int i = 0; i < m_grassPositions.size(); i++)
	{
		if (m_grassPositions.at(i).x == -1.0f || m_grassPositions.at(i).y == -1.0f)
			continue;

		float grassWidth = TILE_SIZE * TILE_MULTIPLIER;
		float grassHeight = TILE_SIZE * TILE_MULTIPLIER;

		GLfloat fightUI[]
		{
			//TOP Environment
			m_grassPositions.at(i).x, m_grassPositions.at(i).y, 0.0f,								0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
			m_grassPositions.at(i).x, m_grassPositions.at(i).y + grassHeight, 0.0f,					0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
			m_grassPositions.at(i).x + grassWidth,m_grassPositions.at(i).y + grassHeight, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
			m_grassPositions.at(i).x + grassWidth, m_grassPositions.at(i).y, 0.0f,					0.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		};

		GLuint indices1[] =
		{
			//BOTTOM Display Bar
			0, 2, 1,
			0, 3, 2
		};

		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(fightUI, sizeof(fightUI));
		EBO EBO1(indices1, sizeof(indices1));

		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();


		m_grassTexture.Bind();
		VAO1.Bind();

		positionCamera(glm::vec3(0.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(m_proj));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		VAO1.Unbind();

		m_grassTexture.Unbind();

		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();
	}
}

void Renderer::drawAI()
{

	for (int i = 0; i < m_aiSprites->size(); i++)
	{
		float playerWidth = TILE_SIZE * TILE_MULTIPLIER;
		float playerHeight = TILE_SIZE * TILE_MULTIPLIER;

		GLfloat fightUI[]
		{
			//TOP Environment
			0.0f, 0.0f, 0.0f,					0.0f, 0.0f, 0.0f,		(m_aiSprites->at(i).getSpriteState() * 0.333f), (m_aiSprites->at(i).getDirection() * 0.25f),
			0.0f, playerHeight, 0.0f,			0.0f, 0.0f, 0.0f,		(m_aiSprites->at(i).getSpriteState() * 0.333f), (m_aiSprites->at(i).getDirection() * 0.25f) + 0.25f,
			playerWidth,playerHeight, 0.0f,		0.0f, 0.0f, 0.0f,		(m_aiSprites->at(i).getSpriteState() * 0.333f) + 0.333f, (m_aiSprites->at(i).getDirection() * 0.25f) + 0.25f,
			playerWidth, 0.0f, 0.0f,			0.0f, 0.0f, 0.0f,		(m_aiSprites->at(i).getSpriteState() * 0.333f) + 0.333f, (m_aiSprites->at(i).getDirection() * 0.25f),
		};

		GLuint indices1[] =
		{
			//BOTTOM Display Bar
			0, 2, 1,
			0, 3, 2
		};

		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(fightUI, sizeof(fightUI));
		EBO EBO1(indices1, sizeof(indices1));

		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();


		m_aiTexture.Bind();
		VAO1.Bind();

		positionCamera(glm::vec3( m_aiSprites->at(i).getX(), m_aiSprites->at(i).getY(), 0.0f));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		VAO1.Unbind();

		m_aiTexture.Unbind();

		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();
	}
}

void Renderer::drawEscapeMenu()
{
	drawMap();
	drawPlayer();
	drawBackGroundBlur();

	GLfloat fightUI[]
	{
		-200.0f, 325.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-200.0f, 475.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		200.0f, 475.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		200.0f, 325.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		-190.0f, 335.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 0.0f,
		-190.0f, 465.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 1.0f,
		190.0f, 465.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 1.0f,
		190.0f, 335.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 0.0f,





		-200.0f, 125.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-200.0f, 275.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		200.0f, 275.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		200.0f, 125.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		-190.0f, 135.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 0.0f,
		-190.0f, 265.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 1.0f,
		190.0f, 265.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 1.0f,
		190.0f, 135.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 0.0f,





		-200.0f, -75.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-200.0f, 75.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		200.0f, 75.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		200.0f, -75.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		-190.0f, -65.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 0.0f,
		-190.0f, 65.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 1.0f,
		190.0f, 65.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 1.0f,
		190.0f, -65.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 0.0f,








		-200.0f, -275.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-200.0f, -125.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		200.0f, -125.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		200.0f, -275.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		-190.0f, -265.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 0.0f,
		-190.0f, -135.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 1.0f,
		190.0f, -135.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 1.0f,
		190.0f, -265.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 0.0f,









		-200.0f, -475.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-200.0f, -325.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		200.0f, -325.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		200.0f, -475.0f, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		-190.0f, -465.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 0.0f,
		-190.0f, -335.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		0.0f, 1.0f,
		190.0f, -335.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 1.0f,
		190.0f, -465.0f, 0.0f,	0.537254902f, 0.8117647059f, 0.9411764706f,		1.0f, 0.0f,
	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6,

		8, 10, 9,
		8, 11, 10,

		12, 14, 13,
		12, 15, 14,

		16, 18, 17,
		16, 19, 18,




		20, 22, 21,
		20, 23, 22,

		24, 26, 25,
		24, 27, 26,

		28, 30, 29,
		28, 31, 30,

		32, 34, 33,
		32, 35, 34,

		36, 38, 37,
		36, 39, 38
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	VAO1.Bind();

	positionCamera(glm::vec3(m_playerX + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));

	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();


	float centerX = 75.0f;
	float centerY = 0.0f;

	m_textRenderer.renderText("Pokemon", 980.0f + centerX, 885.0f + centerY, 70, CENTER_ALIGN, WHITE);
	m_textRenderer.renderText("Bag", 940.0f + centerX, 695.0f + centerY, 70, CENTER_ALIGN, WHITE);
	m_textRenderer.renderText("Save", 950.0f + centerX, 490.0f + centerY, 70, CENTER_ALIGN, WHITE);
	m_textRenderer.renderText("Settings", 980.0f + centerX, 305.0f + centerY, 70, CENTER_ALIGN, WHITE);
	m_textRenderer.renderText("Exit", 960.0f + centerX, 100.0f + centerY, 70, CENTER_ALIGN, WHITE);
}

void Renderer::drawMap()
{
	GLfloat fightUI[]
	{
		//TOP Environment
		0.0f, 0.0f, 0.0f,								0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, m_backgroundHeight, 0.0f,					0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		m_backgroundWidth, m_backgroundHeight, 0.0f,	0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		m_backgroundWidth, 0.0f, 0.0f,					0.0f, 0.0f, 0.0f,		1.0f, 0.0f,

	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	m_mapTexture.Bind();
	VAO1.Bind();

	positionCamera(glm::vec3(0.0f, 0.0f, 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	m_mapTexture.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	drawPlayer();
	drawGrass();
	drawAI();
	drawPokeCenterPokeballs();
	drawExclamation();
	drawTrainerDialogue();
	drawDownArrow();
}

void Renderer::positionCamera(glm::vec3 translate)
{
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);

	view = glm::lookAt(m_camPosition, m_camPosition + Orientation, Up);
	proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj * view * model));


}

void Renderer::drawBackGroundBlur()
{
	Texture blurImage("Images/50_Percent_Black.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blurImage.texUnit(m_shader, "tex0", 0);

	GLfloat blurVertices[]
	{

		//Bottom Display Bar

		0, 0 , 0.0f, 			0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		0, HEIGHT, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		WIDTH, HEIGHT, 0.0f,	0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		WIDTH, 0.0f , 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f  // BOTTOM RIGHT
	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(blurVertices, sizeof(blurVertices));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	blurImage.Bind();
	VAO1.Bind();


	if (m_state == DISPLAY_ESCAPE || m_state == SELECT_POKEMON || m_state == SELECT_ITEM)
		positionCamera(glm::vec3(m_playerX - (WIDTH/2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	blurImage.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	blurImage.Delete();
}

void Renderer::setAiPositions(std::vector<NPT>* aiTrainers)
{
	m_aiSprites = aiTrainers;
}

void Renderer::setRosterSize(unsigned int rosterSize)
{
	m_rosterSize = rosterSize;
}

void Renderer::setBoxPokemon(std::vector<Pokemon> newBox)
{
	if (newBox.size() == 0)
	{
		m_boxPokemon = newBox;
	}
	else
	{
		m_boxPokemon = newBox;
	}
}

void Renderer::setBoxName(std::string boxName)
{
	m_boxName = boxName;
}

void Renderer::setAvailableItems(std::vector<std::string> availableItems)
{
	m_availableItems = availableItems;
}

void Renderer::setExclamationSize(unsigned int size)
{
	m_exclamationSize = size;
}

void Renderer::setExclamationPos(glm::vec2 pos)
{
	m_exclamationPosition = pos;
}

void Renderer::drawTextBox()
{
	Texture mapUpImage("Images/textBoxResized.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	mapUpImage.texUnit(m_shader, "tex0", 0);

	GLfloat optionSelect[]
	{
		//Bottom Display Bar

		10.0f,				10.0f,					0.0f, 		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		10.0f,				(HEIGHT / 4) - 10.0f,	0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		(WIDTH / 2) - 10,	(HEIGHT / 4) - 10.0f,	0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		(WIDTH / 2) - 10,	10.0f,					0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f// BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


	mapUpImage.Bind();
	VAO2.Bind();

	//positionCamera(glm::vec3(0.0f, 0.0f, 0.0f));
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(m_proj));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();

	mapUpImage.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	mapUpImage.Delete();




	m_textRenderer.renderText(m_topLine, 75.0f, 140.0f, 60, LEFT_ALIGN, BLACK);
	m_textRenderer.renderText(m_botLine, 75.0f,  40.0f, 60, LEFT_ALIGN, BLACK);

}

void Renderer::drawPokeCenterPokeballs()
{
	int count = 0;

	if (count == m_rosterSize)
		return;

	unsigned int pokeBallSize = (TILE_SIZE * TILE_MULTIPLIER) / 2;

	GLfloat optionSelect[]
	{
		//Bottom Display Bar

		-337.0f,		430.0f,	0.0f, 									0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		-337.0f,		430.0f + pokeBallSize,	0.0f,					0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		-337.0f + pokeBallSize,		430.0f + pokeBallSize,	0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		-337.0f + pokeBallSize,		430.0f,	0.0f,						0.0f, 0.0f, 0.0f,		1.0f, 0.0f	// BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (count == m_rosterSize)
				return;


			m_pokeballTexture.Bind();
			VAO2.Bind();

			positionCamera(glm::vec3(m_playerX + (90.0f * x), m_playerY + (-75.0f * y), 0.0f));

			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			VAO2.Unbind();

			m_pokeballTexture.Unbind();



			count++;
		}
	}

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
}

void Renderer::drawPC()
{
	// Starting with the top Left Box
	// We draw from top down and move right


	GLfloat vertices[verticeCount] = {0.0f};
	GLfloat pokemonVertices[pokemonVerticeCount] = { 0.0f };

	unsigned int boxesCreated = 0;

	for (int x = 0; x < boxesWide; x++)
	{
		for (int y = 0; y < boxesTall; y++)
		{

			// Bottom Left
			vertices[32 * boxesCreated] = boxX + (hSpacing * x);
			vertices[(32 * boxesCreated) + 1] = boxY - (vSpacing * y);
			vertices[(32 * boxesCreated) + 2] = 0.0f;
			vertices[(32 * boxesCreated) + 3] = 0.0f;
			vertices[(32 * boxesCreated) + 4] = 0.0f;
			vertices[(32 * boxesCreated) + 5] = 0.0f;
			vertices[(32 * boxesCreated) + 6] = 0.0f;
			vertices[(32 * boxesCreated) + 7] = 0.0f;

			pokemonVertices[32 * boxesCreated] = vertices[32 * boxesCreated];
			pokemonVertices[(32 * boxesCreated) + 1] = vertices[(32 * boxesCreated) + 1];

			// Top Left
			vertices[(32 * boxesCreated) + 8] = boxX + (hSpacing * x);
			vertices[(32 * boxesCreated) + 9] = boxY + boxHeight - (vSpacing * y);
			vertices[(32 * boxesCreated) + 10] = 0.0f;
			vertices[(32 * boxesCreated) + 11] = 0.0f;
			vertices[(32 * boxesCreated) + 12] = 0.0f;
			vertices[(32 * boxesCreated) + 13] = 0.0f;
			vertices[(32 * boxesCreated) + 14] = 0.0f;
			vertices[(32 * boxesCreated) + 15] = 1.0f;

			pokemonVertices[(32 * boxesCreated) + 8] = vertices[(32 * boxesCreated) + 8];
			pokemonVertices[(32 * boxesCreated) + 9] = vertices[(32 * boxesCreated) + 9];

			// Top Right
			vertices[(32 * boxesCreated) + 16] = boxX + boxWidth + (hSpacing * x);
			vertices[(32 * boxesCreated) + 17] = boxY + boxHeight - (vSpacing * y);
			vertices[(32 * boxesCreated) + 18] = 0.0f;
			vertices[(32 * boxesCreated) + 19] = 0.0f;
			vertices[(32 * boxesCreated) + 20] = 0.0f;
			vertices[(32 * boxesCreated) + 21] = 0.0f;
			vertices[(32 * boxesCreated) + 22] = 1.0f;
			vertices[(32 * boxesCreated) + 23] = 1.0f;

			pokemonVertices[(32 * boxesCreated) + 16] = vertices[(32 * boxesCreated) + 16];
			pokemonVertices[(32 * boxesCreated) + 17] = vertices[(32 * boxesCreated) + 17];

			// Bottom Right
			vertices[(32 * boxesCreated) + 24] = boxX + boxWidth + (hSpacing * x);
			vertices[(32 * boxesCreated) + 25] = boxY - (vSpacing * y);
			vertices[(32 * boxesCreated) + 26] = 0.0f;
			vertices[(32 * boxesCreated) + 27] = 0.0f;
			vertices[(32 * boxesCreated) + 28] = 0.0f;
			vertices[(32 * boxesCreated) + 29] = 0.0f;
			vertices[(32 * boxesCreated) + 30] = 1.0f;
			vertices[(32 * boxesCreated) + 31] = 0.0f;

			pokemonVertices[(32 * boxesCreated) + 24] = vertices[(32 * boxesCreated) + 24];
			pokemonVertices[(32 * boxesCreated) + 25] = vertices[(32 * boxesCreated) + 25];
			
			boxesCreated += 1;
		}
	}

	// Box Banner
	{
		//Bottom Left
		vertices[(32 * boxesCreated) + 0] = { bannerCenterX - bannerWidth };
		vertices[(32 * boxesCreated) + 1] = { bannerCenterY - bannerHeight };
		vertices[(32 * boxesCreated) + 2] = { 0.0f };

		vertices[(32 * boxesCreated) + 3] = { 0.0f };
		vertices[(32 * boxesCreated) + 4] = { 0.0f };
		vertices[(32 * boxesCreated) + 5] = { 0.0f };
		vertices[(32 * boxesCreated) + 6] = { 0.0f };
		vertices[(32 * boxesCreated) + 7] = { 0.0f };

		//Top Left
		vertices[(32 * boxesCreated) + 8] = { bannerCenterX - bannerWidth };
		vertices[(32 * boxesCreated) + 9] = { bannerCenterY + bannerHeight };
		vertices[(32 * boxesCreated) + 10] = { 0.0f };

		vertices[(32 * boxesCreated) + 11] = { 0.0f };
		vertices[(32 * boxesCreated) + 12] = { 0.0f };
		vertices[(32 * boxesCreated) + 13] = { 0.0f };
		vertices[(32 * boxesCreated) + 14] = { 0.0f };
		vertices[(32 * boxesCreated) + 15] = { 1.0f };

		//Top Right
		vertices[(32 * boxesCreated) + 16] = { bannerCenterX + bannerWidth };
		vertices[(32 * boxesCreated) + 17] = { bannerCenterY + bannerHeight };
		vertices[(32 * boxesCreated) + 18] = { 0.0f };

		vertices[(32 * boxesCreated) + 19] = { 0.0f };
		vertices[(32 * boxesCreated) + 20] = { 0.0f };
		vertices[(32 * boxesCreated) + 21] = { 0.0f };
		vertices[(32 * boxesCreated) + 22] = { 1.0f };
		vertices[(32 * boxesCreated) + 23] = { 1.0f };

		//Bottom Right
		vertices[(32 * boxesCreated) + 24] = { bannerCenterX + bannerWidth };
		vertices[(32 * boxesCreated) + 25] = { bannerCenterY - bannerHeight };
		vertices[(32 * boxesCreated) + 26] = { 0.0f };

		vertices[(32 * boxesCreated) + 27] = { 0.0f };
		vertices[(32 * boxesCreated) + 28] = { 0.0f };
		vertices[(32 * boxesCreated) + 29] = { 0.0f };
		vertices[(32 * boxesCreated) + 30] = { 1.0f };
		vertices[(32 * boxesCreated) + 31] = { 0.0f };
	}

	GLuint indices[indiceCount] = {0};
	GLuint pokemonIndices[pokemonIndiceCount] = { 0 };

	unsigned int offset = 0;

	for (int i = 0; i < indiceCount; i += 6)
	{
		indices[i + 0] = offset;
		indices[i + 1] = offset + 2;
		indices[i + 2] = offset + 1;
		indices[i + 3] = offset;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 2;

		offset += 4;
	}

	for (int i = 0; i < pokemonIndiceCount; i++)
	{
		pokemonIndices[i] = indices[i];
	}


	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(vertices, sizeof(vertices));
	EBO EBO2(indices, sizeof(indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


	m_boxTexture.Bind();
	VAO2.Bind();
	positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();
	m_boxTexture.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	for (int i = 0; i < pokemonIndiceCount; i++)
	{
		pokemonIndices[i] = indices[i];
	}

	//drawPCPokemon(pokemonVertices, pokemonIndices);

	//Drawing PC Pokemon
	{
		//TODO: Find some way in gods green earth to make this into a function
		//TODO: Need to load the correct sheets and somehow render the pokemon per sheet
		Texture playerPokemonSheet(species_Sheets_Front[1], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		playerPokemonSheet.texUnit(m_shader, "tex0", 0);

		for (int i = 0; i < m_boxPokemon.size(); i++)
		{
			if (m_boxPokemon.at(i).getLevel() == 0)
			{
				vertices[(32 * boxesCreated) + 0] = { 0.0f };
				vertices[(32 * boxesCreated) + 1] = { 0.0f };

				vertices[(32 * boxesCreated) + 8] = { 0.0f };
				vertices[(32 * boxesCreated) + 9] = { 0.0f };

				vertices[(32 * boxesCreated) + 16] = { 0.0f };
				vertices[(32 * boxesCreated) + 17] = { 0.0f };

				vertices[(32 * boxesCreated) + 24] = { 0.0f };
				vertices[(32 * boxesCreated) + 25] = { 0.0f };

				continue;
			}

			pokemonRenderData renderData = species_render_data[m_boxPokemon.at(i).getSpecies().getID()];

			// Bottom Left
			pokemonVertices[(32 * i) + 6] = renderData.xCoord;
			pokemonVertices[(32 * i) + 7] = renderData.yCoord;

			// Top Left
			pokemonVertices[(32 * i) + 14] = renderData.xCoord;
			pokemonVertices[(32 * i) + 15] = renderData.yCoord + POKEMON_SHEET_ROW_SIZE;

			// Top Right
			pokemonVertices[(32 * i) + 22] = renderData.xCoord + POKEMON_SHEET_COL_SIZE;
			pokemonVertices[(32 * i) + 23] = renderData.yCoord + POKEMON_SHEET_ROW_SIZE;

			// Bottom Right
			pokemonVertices[(32 * i) + 30] = renderData.xCoord + POKEMON_SHEET_COL_SIZE;
			pokemonVertices[(32 * i) + 31] = renderData.yCoord;
		}


		VAO VAO10;
		VAO10.Bind();

		VBO VBO10(pokemonVertices, sizeof(pokemonVertices));
		EBO EBO10(pokemonIndices, sizeof(pokemonIndices));

		VAO10.LinkAttrib(VBO10, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO10.LinkAttrib(VBO10, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO10.LinkAttrib(VBO10, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO10.Unbind();
		VBO10.Unbind();
		EBO10.Unbind();

		playerPokemonSheet.Bind();
		VAO10.Bind();
		positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));
		glDrawElements(GL_TRIANGLES, pokemonIndiceCount, GL_UNSIGNED_INT, 0);
		VAO10.Unbind();
		playerPokemonSheet.Unbind();

		VAO10.Delete();
		VBO10.Delete();
		EBO10.Delete();

		playerPokemonSheet.Delete();
	}

	//TODO: Refactor this so that all of the vertices are premade and then we can do this in one single draw call
	// Player Pokemon on the right
	GLfloat vertices2[] =
	{
		playerPokemonStartingX, playerPokemonStartingY, 0.0f, 													0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		playerPokemonStartingX, playerPokemonStartingY + playerPokemonHeight, 0.0f,								0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		playerPokemonStartingX + playerPokemonWidth, playerPokemonStartingY + playerPokemonHeight, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		playerPokemonStartingX + playerPokemonWidth, playerPokemonStartingY, 0.0f,								0.0f, 0.0f, 0.0f,		1.0f, 0.0f  // BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		0, 2, 1,
		0, 3, 2,
	};


	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(vertices2, sizeof(vertices2));
	EBO EBO3(indices2, sizeof(indices2));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	float yIncrease = 0;
	float xIncrease = 0;

	for (int x = 0; x < 2; x++)
	{
		if (x == 1)
		{
			yIncrease = ( - 1.0f * playerPokemonHeight) / 4;
		}

		for (int y = 0; y < 3; y++)
		{
			m_boxTexture.Bind();
			VAO3.Bind();

			positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f) + ((x * playerHSpacing) + xIncrease), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f) - ((y * playerVSpacing) + yIncrease), 0.0f));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAO3.Unbind();
			m_boxTexture.Unbind();
		}
	}

	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();

	m_textRenderer.renderText(m_boxName, bannerCenterX + 50, bannerCenterY - 45, 80, CENTER_ALIGN, BLACK);

	//Player Pokemon
	{
		Texture playerPokemonSheet(species_Sheets_Front[1], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		playerPokemonSheet.texUnit(m_shader, "tex0", 0);

		yIncrease = 0;
		xIncrease = 0;
		unsigned int count = 0;

		for (int x = 0; x < 2; x++)
		{
			if (x == 1)
			{
				yIncrease = (-1.0f * playerPokemonHeight) / 4;
			}

			for (int y = 0; y < 3; y++)
			{
				if (m_trainer->getPokemon(count)->getLevel() == 0)
				{
					count++;
					continue;
				}

				pokemonRenderData renderData = species_render_data[m_boxPokemon.at(count).getSpecies().getID()];

				GLfloat playerPokemonVertices[vDataPoints] =
				{
					playerPokemonStartingX, playerPokemonStartingY, 0.0f,												0.0f, 0.0f, 0.0f,	renderData.xCoord, renderData.yCoord,	// Bottom Left
					playerPokemonStartingX, playerPokemonStartingY + playerPokemonHeight, 0.0f,							0.0f, 0.0f, 0.0f,	renderData.xCoord, renderData.yCoord + POKEMON_SHEET_ROW_SIZE,	// TOP LEFT
					playerPokemonStartingX + playerPokemonWidth, playerPokemonStartingY + playerPokemonHeight, 0.0f,	0.0f, 0.0f, 0.0f,	renderData.xCoord + POKEMON_SHEET_COL_SIZE, renderData.yCoord + POKEMON_SHEET_ROW_SIZE,	// TOP RIGHT
					playerPokemonStartingX + playerPokemonWidth, playerPokemonStartingY, 0.0f,							0.0f, 0.0f, 0.0f,	renderData.xCoord + POKEMON_SHEET_COL_SIZE, renderData.yCoord  // BOTTOM RIGHT
				};


				VAO VAO3;
				VAO3.Bind();

				VBO VBO3(playerPokemonVertices, sizeof(playerPokemonVertices));
				EBO EBO3(indices2, sizeof(indices2));

				VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
				VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


				playerPokemonSheet.Bind();
				VAO3.Bind();

				positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f) + ((x * playerHSpacing) + xIncrease), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f) - ((y * playerVSpacing) + yIncrease), 0.0f));

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				VAO3.Unbind();
				playerPokemonSheet.Unbind();



				VAO3.Unbind();
				VBO3.Unbind();
				EBO3.Unbind();

				VAO3.Delete();
				VBO3.Delete();
				EBO3.Delete();

				count++;
			}
		}

		playerPokemonSheet.Delete();
	}

	//Left Right Arrows
	{
		GLfloat triangleVertices[]
		{
			//Bottom Display Bar

			bannerCenterX - bannerWidth - 100.0f, bannerCenterY + bannerHeight, 0.0f, 		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,	// Top Point
			bannerCenterX - bannerWidth - 200.0f, bannerCenterY, 0.0f,						1.0f, 1.0f, 0.0f,		0.0f, 1.0f,	// Far Point
			bannerCenterX - bannerWidth - 100.0f, bannerCenterY - bannerHeight, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,	// Bottom Point



			bannerCenterX + bannerWidth + 100.0f, bannerCenterY + bannerHeight, 0.0f, 		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,	// Top Point
			bannerCenterX + bannerWidth + 200.0f, bannerCenterY, 0.0f,						1.0f, 1.0f, 0.0f,		0.0f, 1.0f,	// Far Point
			bannerCenterX + bannerWidth + 100.0f, bannerCenterY - bannerHeight, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,	// Bottom Point
		};

		GLuint triangleIndices[] =
		{
			//BOTTOM Display Bar
			0, 2, 1,
			3, 5, 4,
		};

		VAO VAO11;
		VAO11.Bind();

		VBO VBO11(triangleVertices, sizeof(triangleVertices));
		EBO EBO11(triangleIndices, sizeof(triangleIndices));

		VAO11.LinkAttrib(VBO11, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO11.LinkAttrib(VBO11, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO11.LinkAttrib(VBO11, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO11.Unbind();
		VBO11.Unbind();
		EBO11.Unbind();

		VAO11.Bind();
		positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		VAO11.Unbind();
		

		VAO11.Delete();
		VBO11.Delete();
		EBO11.Delete();
	}

}

void Renderer::drawBuyItems()
{
	drawMap();

	GLfloat buyMenu[]
	{

		0, 0.0f, 0.0f, 			0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		0, HEIGHT, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		WIDTH, HEIGHT, 0.0f,	0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		WIDTH, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f// BOTTOM RIGHT
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO21;
	VAO21.Bind();

	VBO VBO21(buyMenu, sizeof(buyMenu));
	EBO EBO21(indices, sizeof(indices));

	VAO21.LinkAttrib(VBO21, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO21.LinkAttrib(VBO21, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO21.LinkAttrib(VBO21, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO21.Unbind();
	VBO21.Unbind();
	EBO21.Unbind();


	m_buyMenuTexture.Bind();
	VAO21.Bind();
	positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO21.Unbind();

	m_buyMenuTexture.Unbind();

	VAO21.Delete();
	VBO21.Delete();
	EBO21.Delete();


	m_textRenderer.renderText(std::to_string(m_trainer->getMoneyBalance()), 270, 800, 90, CENTER_ALIGN, BLACK);

	for (int i = 0; i < 6; i++)
	{
		if (i == m_availableItems.size())
			break;

		//TODO: fix the text renderer lol
		m_textRenderer.renderText(m_availableItems.at(i), (WIDTH) + 100, (HEIGHT - 120 - 75) - (i * 90), 50, RIGHT_ALIGN, BLACK);
	}


}

void Renderer::drawPCPokemon(GLfloat vertices[640], GLuint indices[120])
{
	const unsigned int verticeCount = 640;
	const unsigned int indiceCount = 120;

	Texture playerPokemonSheet(species_Sheets_Front[1], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	playerPokemonSheet.texUnit(m_shader, "tex0", 0);

	//TODO: Set the coordinates of the triangle to 0,0
	for (int i = 0; i < m_boxPokemon.size(); i++)
	{
		if (m_boxPokemon.at(i).getLevel() == 0)
			continue;

		pokemonRenderData renderData = species_render_data[m_boxPokemon.at(i).getSpecies().getID()];
	
		// Bottom Left
		vertices[(32 * i) + 3] = 0.0f;
		vertices[(32 * i) + 4] = 0.0f;
		vertices[(32 * i) + 5] = 0.0f;
		vertices[(32 * i) + 6] = renderData.xCoord;
		vertices[(32 * i) + 7] = renderData.yCoord;
	
		// Top Left
		vertices[(32 * i) + 11] = 0.0f;
		vertices[(32 * i) + 12] = 0.0f;
		vertices[(32 * i) + 13] = 0.0f;
		vertices[(32 * i) + 14] = renderData.xCoord;
		vertices[(32 * i) + 15] = renderData.yCoord + POKEMON_SHEET_ROW_SIZE;
	
		// Top Right
		vertices[(32 * i) + 19] = 0.0f;
		vertices[(32 * i) + 20] = 0.0f;
		vertices[(32 * i) + 21] = 0.0f;
		vertices[(32 * i) + 22] = renderData.xCoord + POKEMON_SHEET_COL_SIZE;
		vertices[(32 * i) + 23] = renderData.yCoord + POKEMON_SHEET_ROW_SIZE;
	
		// Bottom Right
		vertices[(32 * i) + 27] = 0.0f;
		vertices[(32 * i) + 28] = 0.0f;
		vertices[(32 * i) + 29] = 0.0f;
		vertices[(32 * i) + 30] = renderData.xCoord + POKEMON_SHEET_COL_SIZE;
		vertices[(32 * i) + 31] = renderData.yCoord;
	}
	
	
	VAO VAO10;
	VAO10.Bind();

	VBO VBO10(vertices, sizeof(vertices));
	EBO EBO10(indices, sizeof(indices));

	VAO10.LinkAttrib(VBO10, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO10.LinkAttrib(VBO10, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO10.LinkAttrib(VBO10, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO10.Unbind();
	VBO10.Unbind();
	EBO10.Unbind();

	//TODO: Define

	playerPokemonSheet.Bind();
	VAO10.Bind();
	positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));
	glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
	VAO10.Unbind();
	playerPokemonSheet.Unbind();

	VAO10.Delete();
	VBO10.Delete();
	EBO10.Delete();
	
	playerPokemonSheet.Delete();
}

void Renderer::drawExclamation()
{
	if (m_exclamationSize == 0)
		return;

	GLfloat optionSelect[]
	{
		//Bottom Display Bar

		m_exclamationPosition.x - m_exclamationSize, m_exclamationPosition.y - m_exclamationSize, 0.0f, 	0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		m_exclamationPosition.x - m_exclamationSize, m_exclamationPosition.y + m_exclamationSize, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		m_exclamationPosition.x + m_exclamationSize, m_exclamationPosition.y + m_exclamationSize, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		m_exclamationPosition.x + m_exclamationSize, m_exclamationPosition.y - m_exclamationSize, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f	// BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	m_exclamationTexture.Bind();
	VAO2.Bind();
	positionCamera(glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();
	m_exclamationTexture.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
}

void Renderer::drawTrainerDialogue()
{
	if (m_topLine.size() == 0)
		return;

	float borderSize = 10.0f;

	GLfloat optionSelect[]
	{
		//Bottom Display Bar

		0.0f, 0.0f, 0.0f, 			0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
		0.0f, (HEIGHT / 4), 0.0f,	0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	// TOP LEFT
		WIDTH, (HEIGHT / 4), 0.0f,	0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	// TOP RIGHT
		WIDTH, 0.0f, 0.0f,			0.0f, 0.0f, 0.0f,		1.0f, 0.0f,	// BOTTOM RIGHT


		0.0f + borderSize, 0.0f + borderSize, 0.0f, 			1.0f, 1.0f, 1.0f,		0.0f, 0.0f,	// Bottom Left
		0.0f + borderSize, (HEIGHT / 4)  - borderSize, 0.0f,	1.0f, 1.0f, 1.0f,		0.0f, 1.0f,	// TOP LEFT
		WIDTH - borderSize, (HEIGHT / 4) - borderSize, 0.0f,	1.0f, 1.0f, 1.0f,		1.0f, 1.0f,	// TOP RIGHT
		WIDTH - borderSize, 0.0f + borderSize, 0.0f,			1.0f, 1.0f, 1.0f,		1.0f, 0.0f	// BOTTOM RIGHT
	};

	GLuint indices2[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(optionSelect, sizeof(optionSelect));
	EBO EBO2(indices2, sizeof(indices2));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO2.Bind();
	positionCamera(glm::vec3(m_playerX - (WIDTH / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), m_playerY - (HEIGHT / 2) + ((TILE_SIZE * TILE_MULTIPLIER) / 2.0f), 0.0f));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO2.Unbind();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();


	m_textRenderer.renderText(m_topLine, 75.0f, 140.0f, 60, LEFT_ALIGN, BLACK);
	m_textRenderer.renderText(m_botLine, 75.0f, 40.0f, 60, LEFT_ALIGN, BLACK);
}
