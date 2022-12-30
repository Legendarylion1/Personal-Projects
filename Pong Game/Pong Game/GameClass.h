#pragma once
#include <Windows.h>
#include "SquareRenderer.h"
#include "ObjectRenderer.h"
#include "DataConstants.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>     // srand, rand
#include <time.h>

#define PI 3.14159265358979

class Game
{
private:

	GLFWwindow*		m_window;
	SquareRenderer	m_player1;
	SquareRenderer	m_player2;
	SquareRenderer	m_ball;
	SquareRenderer  m_divider;
	ObjectRenderer	m_scoreP1;
	ObjectRenderer	m_scoreP2;

	bool m_p1Up		= false;
	bool m_p1Down	= false;
	bool m_p2Up		= false;
	bool m_p2Down	= false;

	unsigned int m_player1Score = 0;
	unsigned int m_player2Score = 0;

	float m_playerSpeed = 0.02f;
	float m_ballXVelocity;
	float m_ballYVelocity;
	float dividerSpacing = 0.1f;
	float m_windowWidth;
	float m_windowHeight;

	unsigned int m_pauseTime;
	bool m_timerRunning = false;
	double m_curTime;
public:
	Game(const unsigned int shader, GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight);
	~Game();
	
	void initBallMovement(unsigned int direction);
	void initScalers();


	void update();
	void recieveInput();
	void drawDivider();
	void updateScore(ObjectRenderer& renderScore, unsigned int& playerScore);
	void checkEnd();
	void renderScores();
	void renderGame();


	void detectBallCollision();
	bool collided(SquareRenderer& square1, SquareRenderer& square2);
	bool hitTop(SquareRenderer& square, int pixelTop);
	bool hitBottom(SquareRenderer& square, int pixelBottom);
	bool p1Scored(SquareRenderer& ball);
	bool p2Scored(SquareRenderer& ball);
};