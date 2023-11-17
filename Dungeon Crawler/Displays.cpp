#include "Displays.h"

int Displays::displayMainMenu(GLFWwindow* window)
{
	return 0;
}

void Displays::displayTabMenu(Player* playerArray)
{
	// I want to make rounded edges, but that can be later
	//Displayer p1,p2,p3,p4 and then the KDA on the right


	m_textRenderer.renderText("Players", -170.0f, 200.0f, 70, 0);
	m_textRenderer.renderText("KDA", 270.0f, 200.0f, 70, 0);

	unsigned int currentSlot = 0;
	for (int i = 0; i < 4; i++)
	{
		if (playerArray[i].isInitialized())
		{
			currentSlot += 1;
			std::string name = "P";
			name.append(std::to_string(i));
			m_textRenderer.renderText(name.c_str(), -200.0f, 170.0f - (currentSlot * 100.0f), 70, 0);

			std::string KDA = std::to_string(playerArray[i].getKDA().at(0));
			KDA.append("-");
			KDA.append(std::to_string(playerArray[i].getKDA().at(1)));
			KDA.append("-");
			KDA.append(std::to_string(playerArray[i].getKDA().at(2)));
			m_textRenderer.renderText(KDA.c_str(), 200.0f, 170.0f - (currentSlot * 100.0f), 70, 0);
		}
	}

	GLfloat tabMenuVertices[]
	{
		(-WINDOWWIDTH / 2) / 2, (-WINDOWHEIGHT / 2) / 2, LAYER_SIX, 0.0f, 0.0f, 1.0f,
		(-WINDOWWIDTH / 2) / 2, ( WINDOWHEIGHT / 2) / 2, LAYER_SIX, 0.0f, 0.0f, 1.0f,
		( WINDOWWIDTH / 2) / 2, ( WINDOWHEIGHT / 2) / 2, LAYER_SIX, 0.0f, 0.0f, 1.0f,
		( WINDOWWIDTH / 2) / 2, (-WINDOWHEIGHT / 2) / 2, LAYER_SIX, 0.0f, 0.0f, 1.0f
	};
	
	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};
	
	VAO VAO1;
	VAO1.Bind();
	
	VBO VBO1(tabMenuVertices, sizeof(tabMenuVertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	
	VAO1.Bind();
	m_camera.Matrix(m_shader, glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

bool Displays::displayDeathMenu(GLFWwindow* window, Player* playerArray)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallBack2);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawDeathMenu(playerArray);
		displayTabMenu(playerArray);

		int result = evaluateDeathMenuClick(window);
		if (result == 0)
			return false;
		if (result == 1)
			return true;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return true;
}

void Displays::drawDeathMenu(Player* playerArray)
{
	m_textRenderer.renderText("Main Menu", mainMenuXPos + (buttonWidth /2), mainMenuYPos + (buttonHeight/2), 30, 0);
	m_textRenderer.renderText("Exit Game", exitButtonXPos + (buttonWidth / 2), exitButtonYPos + (buttonHeight/2), 30, 0);

	GLfloat mainMenuButtonVertices[]
	{
		mainMenuXPos, mainMenuYPos,										LAYER_SIX, 0.0f, 1.0f, 0.0f,
		mainMenuXPos, mainMenuYPos + buttonHeight,						LAYER_SIX, 0.0f, 1.0f, 0.0f,
		mainMenuXPos + buttonWidth, mainMenuYPos + buttonHeight,		LAYER_SIX, 0.0f, 1.0f, 0.0f,
		mainMenuXPos + buttonWidth, mainMenuYPos,						LAYER_SIX, 0.0f, 1.0f, 0.0f,

		exitButtonXPos, exitButtonYPos,									LAYER_SIX, 0.0f, 1.0f, 0.0f,
		exitButtonXPos, exitButtonYPos + buttonHeight,					LAYER_SIX, 0.0f, 1.0f, 0.0f,
		exitButtonXPos + buttonWidth, exitButtonYPos + buttonHeight,	LAYER_SIX, 0.0f, 1.0f, 0.0f,
		exitButtonXPos + buttonWidth, exitButtonYPos,					LAYER_SIX, 0.0f, 1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(mainMenuButtonVertices, sizeof(mainMenuButtonVertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	VAO1.Bind();
	m_camera.Matrix(m_shader, glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

int Displays::evaluateDeathMenuClick(GLFWwindow* window)
{
	if (mouseClickPosition.x == 0 || mouseClickPosition.y == 0)
		return -1;

	//Main Menu
	if (mouseClickPosition.x >= mainMenuX && mouseClickPosition.x <= mainMenuX + buttonWidth && mouseClickPosition.y >= mainMenuY && mouseClickPosition.y <= mainMenuX + buttonHeight)
	{
		return 0;
	}

	//Exit
	if (mouseClickPosition.x >= exitButtonX && mouseClickPosition.x <= exitButtonX + buttonWidth && mouseClickPosition.y >= exitButtonY && mouseClickPosition.y <= exitButtonY + buttonHeight)
	{
		return 1;
	}

	mouseClickPosition.x = 0;
	mouseClickPosition.y = 0;
	return -1;
}

Displays::Displays(Shader& shader, Camera& camera):
	m_shader(shader),
	m_camera(camera),
	m_textRenderer(shader, camera)
{
}

void mouseButtonCallBack2(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		mouseClickPosition.x = mouseX;
		mouseClickPosition.y = -mouseY + WINDOWHEIGHT;
	}
}