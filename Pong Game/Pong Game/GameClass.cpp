#include "GameClass.h"

Game::Game(const unsigned int shader, GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight)
	: m_player1(0.0f, 350.0f, 20.0f, 70.0f, shader, Colors::white),
	m_player2(1180.0f, 350.0f, 20.0f, 70.0f, shader, Colors::white),
	m_ball(600.0f, 350.0f, 10.0f, 10.0f, shader, Colors::white),
	m_divider(588, 680.0f, 4.0f, 10.0f, shader, Colors::white),
	m_scoreP1(DC::zero,shader),
	m_scoreP2(DC::zero,shader)
{
	m_window = window;
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
	m_scoreP2.move(1.0f, 0.0f);
	initScalers();
	initBallMovement(Direction::OMNI);
}

Game::~Game()
{
	
}

void Game::initBallMovement(unsigned int direction)
{
	m_ball.resetPos();
	srand(time(0));
	int initialAngle;

	if (direction == Direction::OMNI)
		initialAngle = rand() % 12;
	else if (direction == Direction::RIGHT)
		initialAngle = rand() % 6;
	else
		initialAngle = rand() % 6 + 6;
	
	// Currently Have Set angles. Could do random for angles too, but I dont want bad angles for the ball. Only from 22.5 -> 67.5
	// Else too steep or not enough angle
	// After play test can see if we make random from set range
	
	// Switch wasnt working with random int :(
	// May Switch to random angle of random angle because boy is this a lot of if else
	// 0 -> 5  Sends Ball to Right Side of Screen starting with angles up to angles down
	// 6 -> 11 Sends Ball to Left Side of Screen starting with angles up to angles down
	float magnitude = 1000.0f;
	if (initialAngle == 0)
	{
		float angle = 60.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 1)
	{
		float angle = 45.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 2)
	{
		float angle = 30.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 3)
	{
		float angle = 330.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 4)
	{
		float angle = 315.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 5)
	{
		float angle = 300.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 6)
	{
		float angle = 120.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 7)
	{
		float angle = 135.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 8)
	{
		float angle = 150.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 9)
	{
		float angle = 210.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 10)
	{
		float angle = 225.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
	else if (initialAngle == 11)
	{
		float angle = 240.0f;
		m_ballXVelocity = (12 * cos(angle * (PI / 180))) / magnitude;
		m_ballYVelocity = (12 * sin(angle * (PI / 180))) / magnitude;
	}
}

void Game::initScalers()
{
	// (width/2) - ((movespeed * count) * scaler) = 0
	// (movespeed * count) * scaler = (width/2)
	// scaler = (width/2)/(movespeed * count)

	//how long it takes to get from the center of the screen to an edge
	int count = 1/m_playerSpeed;
	float xScale = (m_windowWidth / 2) / (m_playerSpeed * count);
	float yScale = (m_windowHeight / 2) / (m_playerSpeed * count);

	m_player1.setXScalar(xScale);
	m_player1.setYScalar(yScale);

	m_player2.setXScalar(xScale);
	m_player2.setYScalar(yScale);

	m_ball.setXScalar(xScale);
	m_ball.setYScalar(yScale);
}

void Game::update()
{
	m_ball.move(m_ballXVelocity, m_ballYVelocity);
	detectBallCollision();
	renderGame();
}

void Game::recieveInput()
{

	//Pressed Key
	{
		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
			m_p1Up = true;
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
			m_p1Down = true;
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
			m_p2Up = true;
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
			m_p2Down = true;
	}

	//Move Player
	{
		if (m_p1Up == true)
		{
			if (!hitTop(m_player1,m_windowHeight))
				m_player1.move(0.0f, m_playerSpeed);
		}
		if (m_p1Down == true)
		{
			if (!hitBottom(m_player1,0))
				m_player1.move(0.0f, -m_playerSpeed);
		}
		if (m_p2Up == true)
		{
			if (!hitTop(m_player2, m_windowHeight))
				m_player2.move(0.0f, m_playerSpeed);
		}
		if (m_p2Down == true)
		{
			if (!hitBottom(m_player2,0))
				m_player2.move(0.0f, -m_playerSpeed);
		}
	}

	//Release Key
	{
		if (glfwGetKey(m_window, GLFW_KEY_W) ==    GLFW_RELEASE)
			m_p1Up = false;
		if (glfwGetKey(m_window, GLFW_KEY_S) ==    GLFW_RELEASE)
			m_p1Down = false;
		if (glfwGetKey(m_window, GLFW_KEY_UP) ==   GLFW_RELEASE)
			m_p2Up = false;
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_RELEASE)
			m_p2Down = false;
	}
}

void Game::drawDivider()
{
	for (int i = 0; i < 20; i++)
	{
		m_divider.move(0.0f, -dividerSpacing * i);
		m_divider.draw();
		m_divider.move(0.0f, dividerSpacing * i);
	}
}

void Game::updateScore(ObjectRenderer& renderScore, unsigned int& playerScore)
{
	playerScore += 1;
	switch (playerScore)
	{
	case 1:
		renderScore.updateAll(DC::one);
		break;
	case 2:
		renderScore.updateAll(DC::two);
		break;
	case 3:
		renderScore.updateAll(DC::three);
		break;
	case 4:
		renderScore.updateAll(DC::four);
		break;
	case 5:
		renderScore.updateAll(DC::five);
		break;
	case 6:
		renderScore.updateAll(DC::six);
		break;
	case 7:
		renderScore.updateAll(DC::seven);
		break;
	case 8:
		renderScore.updateAll(DC::eight);
		break;
	case 9:
		renderScore.updateAll(DC::nine);
		break;
	case 10:
		renderScore.updateAll(DC::zero);
		break;
	case 11:
		renderScore.updateAll(DC::one);
		break;
	};

}

void Game::checkEnd()
{
	if (m_player1Score == 11 || m_player2Score == 11)
	{
		
		int curTime = glfwGetTime();
		while (glfwGetTime() < curTime + 3) {}

		m_player1Score = 0;
		m_player2Score = 0;

		m_scoreP1.updateAll(DC::zero);
		m_scoreP2.updateAll(DC::zero);

		m_player1.resetPos();
		m_player2.resetPos();

		initBallMovement(Direction::OMNI);
		
	}
}

void Game::renderScores()
{
	//P1 Score
	{
		m_scoreP1.draw();
		
		if (m_player1Score == 10)
		{
			m_scoreP1.updateAll(DC::one);
			m_scoreP1.move(-0.1f, 0.0f);
			m_scoreP1.draw();
			m_scoreP1.updateAll(DC::zero);
			m_scoreP1.move( 0.1f, 0.0f);
		}
		else if (m_player1Score == 11)
		{
			m_scoreP1.move(-0.1f, 0.0f);
			m_scoreP1.draw();
			m_scoreP1.move(0.1f, 0.0f);
		}

	}
	
	//P2 Score
	{
		m_scoreP2.draw();

		if (m_player2Score == 10)
		{
			m_scoreP2.updateAll(DC::one);
			m_scoreP2.move(-0.1f, 0.0f);
			m_scoreP2.draw();
			m_scoreP2.updateAll(DC::zero);
			m_scoreP2.move(0.1f, 0.0f);
		}
		else if (m_player2Score == 11)
		{
			m_scoreP2.move(-0.1f, 0.0f);
			m_scoreP2.draw();
			m_scoreP2.move(0.1f, 0.0f);
		}

	}
}

void Game::renderGame()
{
	m_player1.draw();
	m_player2.draw();
	renderScores();
	drawDivider();
	m_ball.draw();
}

void Game::detectBallCollision()
{
	//Ball Hit Top or Bottom Border
	if (hitTop(m_ball, m_windowHeight) || hitBottom(m_ball, 0))
		m_ballYVelocity = -m_ballYVelocity;

	if (p1Scored(m_ball))
	{
		updateScore(m_scoreP1, m_player1Score);
	}
	else if (p2Scored(m_ball))
	{
		updateScore(m_scoreP2, m_player2Score);
	}

	//Ball Hit Paddle
	if (collided(m_ball, m_player1))
	{
		if (hitTop(m_ball, m_player1.getY() + m_player1.getHeight()))
		{
			m_ballYVelocity = -m_ballYVelocity;
		}
		else if (hitBottom(m_ball, m_player1.getY()))
		{
			m_ballYVelocity = -m_ballYVelocity;
		}
		else
		{
			m_ballXVelocity = -m_ballXVelocity;
		}
	}
	else if (collided(m_ball, m_player2))
	{

		//Hitting the bottom of the ball on the top of the paddle
		if (hitTop(m_ball, m_player2.getY() + m_player2.getHeight()))
		{
			m_ballYVelocity = -m_ballYVelocity;
		}
		else if (hitBottom(m_ball, m_player2.getY()))
		{
			m_ballYVelocity = -m_ballYVelocity;
		}
		else
		{
			m_ballXVelocity = -m_ballXVelocity;
		}
	}

	//Ball Hit End
}

bool Game::collided(SquareRenderer& square1, SquareRenderer& square2)
{
	if (square1.getX() < square2.getX() + square2.getWidth() &&
		square1.getX() + square1.getWidth() > square2.getX() &&
		square1.getY() < square2.getY() + square2.getHeight() &&
		square1.getY() + square1.getHeight() > square2.getY())
	{
		return true;
	}

	return false;
}

bool Game::hitTop(SquareRenderer& square, int pixelTop)
{
	if (square.getY() >= (pixelTop - square.getHeight()))
		return true;

	return false;
}

bool Game::hitBottom(SquareRenderer& square, int pixelBottom)
{
	if (square.getY() <= pixelBottom)
		return true;

	return false;
}

bool Game::p1Scored(SquareRenderer& ball)
{
	
	if (ball.getX() > m_windowWidth + 10)
	{
		if (m_timerRunning)
			return true;

		initBallMovement(Direction::RIGHT);
		return true;
	}
	
	return false;
}

bool Game::p2Scored(SquareRenderer& ball)
{

	if (ball.getX() + ball.getWidth() < -10)
	{
		if (m_timerRunning)
			return true;

		initBallMovement(Direction::LEFT);
		return true;
	}

	return false;
}