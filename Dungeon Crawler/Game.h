#pragma once

#include <math.h>

#include "Camera.h"
#include "GameMap.h"
#include "Displays.h"
#include "Projectile.h"
#include "TextRenderer.h"

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
static bool leftMouseButtonPressed = false;

class Game
{
public:
	Game(unsigned int windowWidth, unsigned int windowHeight);
	~Game();

	void drawGame();

	int recieveInput(GLFWwindow* window);
	bool continueGame(GLFWwindow* window);
	bool shouldExit();

	void progressAI();
	void nextLevel();
	void resetGame();

private:
	unsigned int mainPlayerID = 0;
	unsigned int m_playerCount = 1;
	unsigned int m_level = 1;

	int activatedMap = -1;

	bool m_displayTab = false;
	bool m_shouldExit = false;

	Texture itemAtlas;
	Texture m_enemyTexture;
	Shader shader;
	Camera camera;
	GameMap map;
	Displays m_display;
	Player playerArray[4];
	Player basicEnemy;
	Projectile projectileHandler;

	TextRenderer test;

	bool playerCanMove(unsigned int ID, int direction);
	double calculateWeaponAngle(GLFWwindow* window);
	int evaluateInteractions(unsigned int ID);

	
	void dropItem(unsigned int ID, bool deleteItem);
	void findOpenIndex(unsigned int& index, unsigned int ID);
	std::vector<glm::vec3> getPlayerPositions();


	void attackAI(unsigned int ID);
	void handleAIAttacks(std::vector<glm::vec3> enemyAttacks, std::vector<unsigned int> aiIndex);
	void addAIBullets(std::vector<glm::vec4> aiBullets);
	void findProjectileHits();
	int attackHitsPlayer(glm::vec3 attackPosition, unsigned int aiIndex, float damage);
	void handleKDAReport(std::vector<std::vector<unsigned int>> kdaReport);
	void displayTabMenu();

	bool hitAlready(unsigned int playerIndex, std::vector<unsigned int> hitIndex);
};