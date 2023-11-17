#include "PlayerUI.h"

/// <summary>
/// Empty constructor to obtain a playerUI object
/// </summary>
PlayerUI::PlayerUI(){}

/// <summary>
/// Deletes the vectors used for our shaders
/// </summary>
PlayerUI::~PlayerUI()
{
	if (UIinitialized)
	{
		PlayerUI::vaoVector.at(0).Delete();
		PlayerUI::vboVector.at(0).Delete();
		PlayerUI::eboVector.at(0).Delete();

		PlayerUI::vaoVector.at(1).Delete();
		PlayerUI::vboVector.at(1).Delete();
		PlayerUI::eboVector.at(1).Delete();

		PlayerUI::vaoVector.at(2).Delete();
		PlayerUI::vboVector.at(2).Delete();

		PlayerUI::vaoVector.at(3).Delete();
		PlayerUI::vboVector.at(3).Delete();

		PlayerUI::vaoVector.at(4).Delete();
		PlayerUI::vboVector.at(4).Delete();

		UIinitialized = false;
	}
}

/// <summary>
/// Draws the UI for the player
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="maxHealth">- The players Maximum Health</param>
/// <param name="currentHealth">- The player's current health</param>
/// <param name="itemIndex">- The index of the current selected item</param>
/// <param name="Position">- The position of the player</param>
/// <param name="item">- An array of items that the player has</param>
/// <param name="itemTexture">- Reference to the game's item Atlas</param>
/// <param name="itemUsage">- An array of booleans saying whether or not the item at that index is in use</param>
void PlayerUI::drawUI(Shader& shader, Camera& camera, float maxHealth, float currentHealth, unsigned int itemIndex, glm::vec3 Position, Item item[3], Texture& itemTexture, bool itemUsage[3])
{
	//Health Bar
	PlayerUI::vaoVector.at(0).Bind();
	healthBarPosition(shader, maxHealth, currentHealth);
	camera.Matrix(shader, Position);
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(0).Unbind();

	//SelectedItem
	PlayerUI::vaoVector.at(3).Bind();
	camera.Matrix(shader, itemHighlightLocation(itemIndex, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(3).Unbind();

	//Item Hotbar
	drawItems(shader, camera, item, Position, itemTexture, itemUsage);
}

/// <summary>
/// Initializes all of the vectors needed to draw the UI
/// </summary>
void PlayerUI::initUI()
{
	GLuint tripleIndices[] =
	{
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6,

		8, 10, 9, 
		8, 11, 10
	};

	GLuint singleIndices[] =
	{
		0, 2, 1,
		0, 3, 2,
	};

	GLfloat healthBarVertices[]
	{
		//	Health Bar
		(- (int)WINDOWWIDTH / 2) + 50,			 ( -(int)WINDOWHEIGHT /2) + 1000,		LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(- (int)WINDOWWIDTH / 2) + 50,			 ( -(int)WINDOWHEIGHT /2) + 1000 + 50,	LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(- (int)WINDOWWIDTH / 2) + 50 + 400,	 ( -(int)WINDOWHEIGHT /2) + 1000 + 50,	LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,
		(- (int)WINDOWWIDTH / 2) + 50 + 400,	 ( -(int)WINDOWHEIGHT /2) + 1000,		LAYER_THREE,		0.0f,0.0f,0.0f,		0.0f, 0.0f,

		//	  Outline
		(-(int)WINDOWWIDTH / 2) + 47,		(-(int)WINDOWHEIGHT / 2) + 997,				LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(-(int)WINDOWWIDTH / 2) + 47,		(-(int)WINDOWHEIGHT / 2) + 997 + 56,		LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(-(int)WINDOWWIDTH / 2) + 47 + 406, (-(int)WINDOWHEIGHT / 2) + 997 + 56,		LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,
		(-(int)WINDOWWIDTH / 2) + 47 + 406, (-(int)WINDOWHEIGHT / 2) + 997,				LAYER_TWO,			1.0f,1.0f,1.0f,		0.0f, 0.0f,

		//	  Dynamic
		(-(int)WINDOWWIDTH / 2) + 50, (-(int)WINDOWHEIGHT / 2) + 1000,					LAYER_FOUR,			1.0f,0.0f,0.20f,	0.0f, 0.0f,
		(-(int)WINDOWWIDTH / 2) + 50, (-(int)WINDOWHEIGHT / 2) + 1000 + 50,				LAYER_FOUR,			1.0f,0.0f,0.20f,	0.0f, 0.0f,
		(-(int)WINDOWWIDTH / 2) + 50, (-(int)WINDOWHEIGHT / 2) + 1000 + 50,				LAYER_FOUR,			1.0f,0.0f,0.20f,	1.0f, 0.0f,
		(-(int)WINDOWWIDTH / 2) + 50, (-(int)WINDOWHEIGHT / 2) + 1000,					LAYER_FOUR,			1.0f,0.0f,0.20f,	1.0f, 0.0f
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(healthBarVertices, sizeof(healthBarVertices));
	EBO tripleEBO(tripleIndices, sizeof(tripleIndices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	tripleEBO.Unbind();

	PlayerUI::vaoVector.push_back(VAO1);
	PlayerUI::vboVector.push_back(VBO1);
	PlayerUI::eboVector.push_back(tripleEBO);

	GLfloat itemSlotVertices[]
	{
		//	Item Slot 1
		-25, -25, LAYER_FIVE,		0.0f,  0.0f,
		-25,  25, LAYER_FIVE,		0.0f,  0.25f,
		 25,  25, LAYER_FIVE,		0.25f, 0.25f,
		 25, -25, LAYER_FIVE,		0.25f, 0.0f,
	};

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(itemSlotVertices, sizeof(itemSlotVertices));
	EBO singleEBO(singleIndices, sizeof(singleIndices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	singleEBO.Unbind();

	PlayerUI::vaoVector.push_back(VAO2);
	PlayerUI::vboVector.push_back(VBO2);
	PlayerUI::eboVector.push_back(singleEBO);

	GLfloat itemSlotOutlineVertices[]
	{
		-28, -28,	LAYER_TWO,		1.0f,1.0f,1.0f,
		-28,  28,	LAYER_TWO,		1.0f,1.0f,1.0f,
		 28,  28,	LAYER_TWO,		1.0f,1.0f,1.0f,
		 28, -28,	LAYER_TWO,		1.0f,1.0f,1.0f
	};

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(itemSlotOutlineVertices, sizeof(itemSlotOutlineVertices));
	singleEBO.Bind();
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	singleEBO.Unbind();


	PlayerUI::vaoVector.push_back(VAO3);
	PlayerUI::vboVector.push_back(VBO3);

	GLfloat selectedItemVertices[]
	{
		-28, -28, LAYER_THREE,		0.0f,0.0f,1.0f,
		-28,  28, LAYER_THREE,		0.0f,0.0f,1.0f,
		 28,  28, LAYER_THREE,		0.0f,0.0f,1.0f,
		 28, -28, LAYER_THREE,		0.0f,0.0f,1.0f,
	};

	VAO VAO4;
	VAO4.Bind();

	VBO VBO4(selectedItemVertices, sizeof(selectedItemVertices));
	singleEBO.Bind();

	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.Unbind();
	VBO4.Unbind();
	singleEBO.Unbind();

	PlayerUI::vaoVector.push_back(VAO4);
	PlayerUI::vboVector.push_back(VBO4);


	GLfloat blackBackground[]
	{
		-25, -25, LAYER_FOUR, 0.4375f,0.5f,0.5625f,		0.0f, 0.0f,
		-25,  25, LAYER_FOUR, 0.4375f,0.5f,0.5625f,		0.0f, 1.0f,
		 25,  25, LAYER_FOUR, 0.4375f,0.5f,0.5625f,		1.0f, 1.0f,
		 25, -25, LAYER_FOUR, 0.4375f,0.5f,0.5625f,		1.0f, 0.0f,
	};

	VAO VAO5;
	VAO5.Bind();

	VBO VBO5(blackBackground, sizeof(blackBackground));
	singleEBO.Bind();

	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO5.Unbind();
	VBO5.Unbind();
	singleEBO.Unbind();

	PlayerUI::vaoVector.push_back(VAO5);
	PlayerUI::vboVector.push_back(VBO5);
	UIinitialized = true;

	//Where we want it - the middle of the screen where the character is going to be
	itemIndexPosition = glm::vec3(1725 - (WINDOWWIDTH / 2), 1025 - (WINDOWHEIGHT / 2), 0.0f);
}

/// <summary>
/// Finds the location to place item Hotbar elements
/// </summary>
/// <param name="location">- Index of the instance of the item Hotbar</param>
/// <param name="Position">- The position of index 0 of the item Hotbar</param>
/// <returns></returns>
glm::vec3 PlayerUI::itemHighlightLocation(unsigned int location, glm::vec3 Position)
{
	float itemGap = 70;
	return glm::vec3(Position.x + (location * itemGap), Position.y, Position.z);
}

/// <summary>
/// Sets the uniform for the health bar's position.
/// </summary>
/// <param name="shader">- The game's reference to the shader</param>
/// <param name="maxHealth">- The maximum health of the player</param>
/// <param name="currentHealth">- The current health of the player</param>
void PlayerUI::healthBarPosition(Shader& shader, float maxHealth, float currentHealth)
{
	float healthBarWidth = 400.0f;

	glUniform1f(glGetUniformLocation(shader.ID, "healthBar"), (healthBarWidth * currentHealth) / maxHealth);
}

/// <summary>
/// Draws the item hotbar and the items within the hotbar
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="camera">- Reference to the game's camera</param>
/// <param name="item">- An array of items that the player has</param>
/// <param name="Position">- The position of the player</param>
/// <param name="itemTexture">- Reference to the game's itemAtlas</param>
/// <param name="itemUsage">- An array of booleans saying whether or not the item at that index is in use</param>
void PlayerUI::drawItems(Shader& shader, Camera& camera, Item item[3], glm::vec3 Position, Texture& itemTexture, bool itemUsage[3])
{
	//TODO: Why does this for loop break everything

	//for (int i = 0; i < 3; i++)
	//{
	//	PlayerUI::vaoVector.at(4).Bind();
	//	camera.Matrix(shader, itemHighlightLocation(i, Position + itemIndexPosition));
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	PlayerUI::vaoVector.at(4).Unbind();
	//
	//	if (itemUsage[i])
	//	{
	//		item[i].bindAtlasUniforms(shader, itemTexture);
	//		PlayerUI::vaoVector.at(1).Bind();
	//		if (item[i].getItemType() == GUN)
	//			camera.Matrix(shader, itemHighlightLocation(i, Position + itemIndexPosition), -90.0f, true);
	//		else
	//			camera.Matrix(shader, itemHighlightLocation(i, Position + itemIndexPosition));
	//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//		PlayerUI::vaoVector.at(1).Unbind();
	//		itemTexture.Unbind();
	//	}
	//
	//	PlayerUI::vaoVector.at(2).Bind();
	//	camera.Matrix(shader, itemHighlightLocation(i, Position + itemIndexPosition));
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	PlayerUI::vaoVector.at(2).Unbind();
	//
	//}

	PlayerUI::vaoVector.at(4).Bind();
	camera.Matrix(shader, itemHighlightLocation(0, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(4).Unbind();
	
	PlayerUI::vaoVector.at(4).Bind();
	camera.Matrix(shader, itemHighlightLocation(1, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(4).Unbind();
	
	PlayerUI::vaoVector.at(4).Bind();
	camera.Matrix(shader, itemHighlightLocation(2, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(4).Unbind();
	
	if (itemUsage[0])
	{
		item[0].bindAtlasUniforms(shader, itemTexture);
		PlayerUI::vaoVector.at(1).Bind();
		if (item[0].getItemType() == GUN)
			camera.Matrix(shader, itemHighlightLocation(0, Position + itemIndexPosition),-90.0f, true);
		else
			camera.Matrix(shader, itemHighlightLocation(0, Position + itemIndexPosition));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		PlayerUI::vaoVector.at(1).Unbind();
		itemTexture.Unbind();
	}
	
	if (itemUsage[1])
	{
		item[1].bindAtlasUniforms(shader, itemTexture);
		PlayerUI::vaoVector.at(1).Bind();
		if (item[1].getItemType() == GUN)
			camera.Matrix(shader, itemHighlightLocation(1, Position + itemIndexPosition), -90.0f, true);
		else
			camera.Matrix(shader, itemHighlightLocation(1, Position + itemIndexPosition));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		PlayerUI::vaoVector.at(1).Unbind();
		itemTexture.Unbind();
	}
	
	if (itemUsage[2])
	{
		item[2].bindAtlasUniforms(shader, itemTexture);
		PlayerUI::vaoVector.at(1).Bind();
		if (item[2].getItemType() == GUN)
			camera.Matrix(shader, itemHighlightLocation(2, Position + itemIndexPosition), -90.0f, true);
		else
			camera.Matrix(shader, itemHighlightLocation(2, Position + itemIndexPosition));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		PlayerUI::vaoVector.at(1).Unbind();
		itemTexture.Unbind();
	}
	
	
	item[0].resetAtlasUniforms(shader);
	
	
	
	
	PlayerUI::vaoVector.at(2).Bind();
	camera.Matrix(shader, itemHighlightLocation(0, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(2).Unbind();
	
	PlayerUI::vaoVector.at(2).Bind();
	camera.Matrix(shader, itemHighlightLocation(1, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(2).Unbind();
	
	PlayerUI::vaoVector.at(2).Bind();
	camera.Matrix(shader, itemHighlightLocation(2, Position + itemIndexPosition));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	PlayerUI::vaoVector.at(2).Unbind();
}