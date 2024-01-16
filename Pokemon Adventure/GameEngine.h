#pragma once

#include "PC.h"
#include "GameMap.h"
#include "Cutscene.h"
#include "Animation.h"


class GameEngine {

public:
	GameEngine();

	bool setup();
	bool run();
	bool shutdown();

	void onUpdate();
private:
	void initPlayerPosition();
	void handleEvents(std::vector<unsigned int> events);
	void handleEscape();
	void updateGrassTiles();
	void changeSettings();


	bool attemptEncounter(bool isPokemon, int nptID = -1);
	
	void movePlayer(Direction direction, bool jump);
	void setPlayerPosition(int x, int y);
	void changeInput(INPUT_EVENT event);

	std::vector<animationControls::trainerAnimationPoint> getAnimationPoints(Direction direction, bool jump);


	void turnPlayer(unsigned int direction);
	void transferMaps(unsigned int direction);
	void transferBuilding(bool PokeCenter);
	void transferReturn();

	void nurseHeal();
	void usePC();
	void buyItem();
	void interactNPT();

	unsigned int selectPokemon(bool swapPokemon);
	void useItem();
	void swapPCPokemon(unsigned int box, unsigned int position1, unsigned int box2, unsigned int position2, unsigned int currentBox);
private:
	Input m_input;
	Renderer m_renderer;
	Encounter m_encounter;
	GameMap m_gameMap;
	Cutscene m_cutscene;

	Trainer m_trainer;
	PC m_pc;

	PC::userSettings m_userSettings;

	float m_deltaTime	= 0.0f;
	float m_lastTime	= 0.0f;

private:
	GLFWwindow* m_window = nullptr;

	bool m_clicked	= false;
	double m_mouseX	= 0;
	double m_mouseY	= 0;

	bool m_upPressed		= false;
	bool m_downPressed		= false;
	bool m_leftPressed		= false;
	bool m_rightPressed		= false;
	bool m_interactPressed	= false;
	bool m_escapePressed	= false;

	float m_playerX = 0.0f;
	float m_playerY = 0.0f;
	float m_playerSpeed = 4.0f;
	float m_turnSpeed = 8.0f;

	bool m_inGrass = false;
	bool m_rightFoot = false;
	bool m_stepped = false;
	unsigned int m_playerDirection = Direction::UP;
};