#pragma once

#include "Texture.h"
#include "TextRenderer.h"
#include "Player.h"

void mouseButtonCallBack2(GLFWwindow* window, int button, int action, int mods);
static glm::vec2 mouseClickPosition = {0.0f,0.0f};

class Displays
{
public:
	Displays(Shader& shader, Camera& camera);

	int displayMainMenu(GLFWwindow* window);
	void displayTabMenu(Player* playerArray);

	bool displayDeathMenu(GLFWwindow* window, Player* playerArray);
	void drawDeathMenu(Player* playerArray);
	int evaluateDeathMenuClick(GLFWwindow* window);



private:
	Shader m_shader;
	Camera m_camera;
	TextRenderer m_textRenderer;

	float mainMenuX = 200;
	float mainMenuY = 200;

	float mainMenuXPos = mainMenuX - (WINDOWWIDTH / 2);
	float mainMenuYPos = mainMenuY - (WINDOWHEIGHT / 2);

	float exitButtonX = 700.0f;
	float exitButtonY = 200.0f;

	float exitButtonXPos = exitButtonX - (WINDOWWIDTH / 2);
	float exitButtonYPos = exitButtonY - (WINDOWHEIGHT / 2);


	float buttonWidth = 300.0f;
	float buttonHeight = 200.0f;
};

