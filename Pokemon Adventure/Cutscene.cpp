#include "Cutscene.h"

Cutscene::Cutscene()
{
}

void Cutscene::setup(Renderer* renderer, Encounter* encounter, bool* fasterText)
{
	m_renderer = renderer;
	m_encounter = encounter;
	m_fasterText = fasterText;
}

void Cutscene::setCutsceneCount(unsigned int count)
{
	std::cout << "Setting cutscene count: " << count << std::endl;
	m_cutsceneCount = count;
}

unsigned int Cutscene::getCutsceneCount()
{
	return m_cutsceneCount;
}

void Cutscene::renderRouteTransition(Renderer& renderer, std::string title, bool toTown)
{
}

bool Cutscene::storyCutscene(MapSection& mapSection)
{
	//TODO: Increment Story afterwards

	std::cout << "In story Cutscene" << std::endl;
	//I - Index
	//U - Up
	//D - Down
	//L - Left
	//R - Right
	//S - Speak
	//X - Set x tile
	//Y - Set y tile
	
	//TODO: I feel like there is a better way to do the code below, that I just cant think of. Fix it please if you can :)
	//	PS it doesnt really matter the code looks clean anyways. Ur doing great so far btw. Im really proud of you. From me <3

	//TODO: A way to turn an npt

	m_mapSection = &mapSection;
	m_speakIndex.clear();

	if (!isCutScene())
	{
		m_mapSection = nullptr;
		return false;
	}


	std::string script = m_mapSection->getCutsceneScript();

	std::cout << "Script: \"" << script.c_str() << "\"\n";

	std::string currentOperation = cutsceneEvents::NONE;
	std::string currentValue = "";

	for (int i = 0; i < script.size(); i++)
	{
		std::cout << "Script Event = " << script.at(i) << std::endl;
		if (script.at(i) == 'I')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::AI_INDEX;
			currentValue = "";
		}
		else if (script.at(i) == 'U')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::MOVE_UP;
			currentValue = "";
		}
		else if (script.at(i) == 'D')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::MOVE_DOWN;
			currentValue = "";
		}
		else if (script.at(i) == 'L')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::MOVE_LEFT;
			currentValue = "";
		}
		else if (script.at(i) == 'R')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::MOVE_RIGHT;
			currentValue = "";
		}
		else if (script.at(i) == 'S')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::SPEAK;
			currentValue = "";
		}
		else if (script.at(i) == 'X')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::SET_X_TILE;
			currentValue = "";
		}
		else if (script.at(i) == 'Y')
		{
			evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
			currentOperation = cutsceneEvents::SET_Y_TILE;
			currentValue = "";
		}
		else
		{
			currentValue += script.at(i);
		}
	}
	evaluateCutscene(currentOperation, atoi(currentValue.c_str()));
	resetAIPositions();
	m_mapSection = nullptr;
	m_cutsceneCount += 1;
	return true;
}

bool Cutscene::isCutScene()
{
	if (m_mapSection->getCutsceneID() == m_cutsceneCount)
		return true;
	return false;
}

void Cutscene::spottedTrainer(NPT& npt, unsigned int trainerTileX, unsigned int trainerTileY)
{
	displayExclamation(npt.getX(), npt.getY());

	unsigned int distance = npt.tilesFromTrainer(trainerTileX, trainerTileY);

	std::cout << "Distance: " << distance << std::endl;

	for (int i = 0; i < distance; i++)
	{
		if (npt.getDirection() == Direction::UP)
			moveNPTUp(npt);
		else if (npt.getDirection() == Direction::DOWN)
			moveNPTDown(npt);
		else if (npt.getDirection() == Direction::LEFT)
			moveNPTLeft(npt);
		else
			moveNPTRight(npt);
	}
}

void Cutscene::nptDialogue(NPT& npt)
{
	std::string topLine = "";
	std::string botLine = "";

	float doubleSpeed = 1.0f;
	if (*m_fasterText)
		doubleSpeed = 2.0f;

	for (int y = 0; y < npt.getTopLines().size(); y++)
	{

		for (int i = 0; i < npt.getTopLines().at(y).size(); i++)
		{
			topLine += npt.getTopLines().at(y).at(i);

			m_renderer->setTextBox(topLine, botLine);
			m_renderer->onUpdate();
			
			animationControls::animateDelay(m_playerSpeed * m_textWriteSpeed * doubleSpeed, m_renderer);
		}

		for (int i = 0; i < npt.getBotLines().at(y).size(); i++)
		{
			botLine += npt.getBotLines().at(y).at(i);

			m_renderer->setTextBox(topLine, botLine);
			m_renderer->onUpdate();

			animationControls::animateDelay(m_playerSpeed * m_textWriteSpeed * doubleSpeed, m_renderer);
		}

		m_encounter->awaitClick();

		topLine = "";
		botLine = "";
	}
	m_renderer->setTextBox("", "");
}

void Cutscene::evaluateCutscene(std::string cutsceneEvent, int value)
{
	std::cout << "Evaluating Cutscene Event: " << cutsceneEvent << "\tValue: " << value << std::endl;

	if (cutsceneEvent == cutsceneEvents::AI_INDEX)
	{
		std::cout << "AI index = " << value << std::endl;
		m_aiIndex = value;
	}
	else if (cutsceneEvent == cutsceneEvents::MOVE_UP)
	{
		for (int i = 0; i < value; i++)
		{
			moveNPTUp(m_mapSection->getAI(m_aiIndex));
		}
	}
	else if (cutsceneEvent == cutsceneEvents::MOVE_DOWN)
	{
		for (int i = 0; i < value; i++)
		{
			moveNPTDown(m_mapSection->getAI(m_aiIndex));
		}
	}
	else if (cutsceneEvent == cutsceneEvents::MOVE_LEFT)
	{
		for (int i = 0; i < value; i++)
		{
			moveNPTLeft(m_mapSection->getAI(m_aiIndex));
		}
	}
	else if (cutsceneEvent == cutsceneEvents::MOVE_RIGHT)
	{
		for (int i = 0; i < value; i++)
		{
			moveNPTRight(m_mapSection->getAI(m_aiIndex));
		}
	}
	else if (cutsceneEvent == cutsceneEvents::SPEAK)
	{
		cutsceneDialogue();
	}
	else if (cutsceneEvent == cutsceneEvents::SET_X_TILE)
	{
		m_mapSection->getAI(m_aiIndex).setTileX(value);
	}
	else if (cutsceneEvent == cutsceneEvents::SET_Y_TILE)
	{
		m_mapSection->getAI(m_aiIndex).setTileY(value);
	}

}

void Cutscene::moveNPTUp(NPT& npt)
{
	float oldY = npt.getY();
	bool firstEntered = true;
	bool stepped = false;
	bool rightFoot = true;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	npt.setDirection(Direction::UP);
	while (npt.getY() < oldY + (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		deltaTime = curTime - lastTime;
		lastTime = curTime;

		if (firstEntered)
			deltaTime = 0.0f;

		if (npt.getY() + ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime) * m_playerSpeed > oldY + (TILE_SIZE * TILE_MULTIPLIER))
			npt.setY(oldY + (TILE_SIZE * TILE_MULTIPLIER));
		else
			npt.setY(npt.getY() + ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime * m_playerSpeed));

		firstEntered = false;



		//Animation
		if (!stepped && npt.getY() >= oldY + ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (rightFoot)
			{
				npt.setSpriteState(SpriteState::STEP1);
				rightFoot = false;
				stepped = true;
			}
			else
			{
				npt.setSpriteState(SpriteState::STEP2);
				rightFoot = true;
				stepped = true;
			}
		}
		else if (npt.getY() >= oldY + ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			npt.setSpriteState(SpriteState::IDLE);
		}

		m_renderer->onUpdate();
	}
}

void Cutscene::moveNPTDown(NPT& npt)
{
	float oldY = npt.getY();
	bool firstEntered = true;
	bool stepped = false;
	bool rightFoot = true;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	npt.setDirection(Direction::DOWN);
	while (npt.getY() > oldY - (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		deltaTime = curTime - lastTime;
		lastTime = curTime;

		if (firstEntered)
			deltaTime = 0.0f;

		if (npt.getY() - ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime) * m_playerSpeed < oldY - (TILE_SIZE * TILE_MULTIPLIER))
			npt.setY(oldY - (TILE_SIZE * TILE_MULTIPLIER));
		else
			npt.setY(npt.getY() - ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime * m_playerSpeed));

		firstEntered = false;



		//Animation
		if (!stepped && npt.getY() <= oldY - ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (rightFoot)
			{
				npt.setSpriteState(SpriteState::STEP1);

				rightFoot = false;
				stepped = true;
			}
			else
			{
				npt.setSpriteState(SpriteState::STEP2);
				rightFoot = true;
				stepped = true;
			}
		}
		else if (npt.getY() <= oldY - ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			npt.setSpriteState(SpriteState::IDLE);
		}

		m_renderer->onUpdate();
	}
}

void Cutscene::moveNPTLeft(NPT& npt)
{
	float oldX = npt.getX();
	bool firstEntered = true;
	bool stepped = false;
	bool rightFoot = true;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	npt.setDirection(Direction::LEFT);
	while (npt.getX() > oldX - (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		deltaTime = curTime - lastTime;
		lastTime = curTime;

		if (firstEntered)
			deltaTime = 0.0f;

		if (npt.getX() - ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime) * m_playerSpeed < oldX - (TILE_SIZE * TILE_MULTIPLIER))
			npt.setX(oldX - (TILE_SIZE * TILE_MULTIPLIER));
		else
			npt.setX(npt.getX() - ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime * m_playerSpeed));

		firstEntered = false;



		//Animation
		if (!stepped && npt.getX() <= oldX - ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (rightFoot)
			{
				npt.setSpriteState(SpriteState::STEP1);

				rightFoot = false;
				stepped = true;
			}
			else
			{
				npt.setSpriteState(SpriteState::STEP2);

				rightFoot = true;
				stepped = true;
			}
		}
		else if (npt.getX() <= oldX - ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			npt.setSpriteState(SpriteState::IDLE);
		}

		m_renderer->onUpdate();
	}
}

void Cutscene::moveNPTRight(NPT& npt)
{
	float oldX = npt.getX();
	bool firstEntered = true;
	bool stepped = false;
	bool rightFoot = true;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	//TODO: Probably create a function to turn the npt
	npt.setDirection(Direction::RIGHT);
	while (npt.getX() < oldX + (TILE_SIZE * TILE_MULTIPLIER))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		deltaTime = curTime - lastTime;
		lastTime = curTime;

		if (firstEntered)
			deltaTime = 0.0f;

		if (npt.getX() + ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime) * m_playerSpeed > oldX + (TILE_SIZE * TILE_MULTIPLIER))
			npt.setX(oldX + (TILE_SIZE * TILE_MULTIPLIER));
		else
			npt.setX(npt.getX() + ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime * m_playerSpeed));

		firstEntered = false;



		//Animation
		if (!stepped && npt.getX() >= oldX + ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f)))
		{
			if (rightFoot)
			{
				npt.setSpriteState(SpriteState::STEP1);

				rightFoot = false;
				stepped = true;
			}
			else
			{
				npt.setSpriteState(SpriteState::STEP2);

				rightFoot = true;
				stepped = true;
			}
		}
		else if (npt.getX() >= oldX + ((TILE_SIZE * TILE_MULTIPLIER) * (3.0f / 4.0f)))
		{
			npt.setSpriteState(SpriteState::IDLE);
		}

		m_renderer->onUpdate();
	}
}

void Cutscene::cutsceneDialogue()
{
	if (m_speakIndex.find(m_aiIndex) == m_speakIndex.end())
		m_speakIndex[m_aiIndex] = 0;

	NPT& npt = m_mapSection->getAI(m_aiIndex);

	float doubleSpeed = 1.0f;
	if (*m_fasterText)
		doubleSpeed = 2.0f;

	//Dialogue
	{
		std::string topLine = "";
		std::string botLine = "";

		for (int i = 0; i < npt.getCutsceneTopLines().at(m_speakIndex[m_aiIndex]).size(); i++)
		{
			topLine += npt.getCutsceneTopLines().at(m_speakIndex[m_aiIndex]).at(i);

			m_renderer->setTextBox(topLine, botLine);
			m_renderer->onUpdate();

			animationControls::animateDelay(m_playerSpeed * m_textWriteSpeed * doubleSpeed, m_renderer);
		}
		for (int i = 0; i < npt.getCutsceneBotLines().at(m_speakIndex[m_aiIndex]).size(); i++)
		{
			botLine += npt.getCutsceneBotLines().at(m_speakIndex[m_aiIndex]).at(i);

			m_renderer->setTextBox(topLine, botLine);
			m_renderer->onUpdate();

			animationControls::animateDelay(m_playerSpeed * m_textWriteSpeed * doubleSpeed, m_renderer);
		}

		m_encounter->awaitClick();

		topLine = "";
		botLine = "";

		m_renderer->setTextBox("", "");
	}
	
	m_speakIndex[m_aiIndex] += 1;
}

void Cutscene::resetAIPositions()
{
	//TODO: Only resets position of AI that move. Idk if were moving AI without them talking but it is worth noting
	for (auto& value : m_speakIndex)
	{
		m_mapSection->getAI(value.first).resetDefaultPosition();
	}
}

void Cutscene::displayExclamation(float xPos, float yPos)
{

	m_renderer->setExclamationPos(glm::vec2(xPos + ((TILE_SIZE * TILE_MULTIPLIER) / 2), yPos + (TILE_SIZE * TILE_MULTIPLIER) + ((TILE_SIZE * TILE_MULTIPLIER) / 2)));

	unsigned int stallTime = 3;
	float oldY = 0;
	float newY = 0;
	float exclmSize = ((TILE_SIZE * TILE_MULTIPLIER) * (1.0f / 4.0f));
	bool firstEntered = true;
	bool stopSize = false;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	m_renderer->setExclamationSize(exclmSize);

	while (newY < oldY + ((TILE_SIZE * TILE_MULTIPLIER) * stallTime))
	{
		//Movement Calculations
		float curTime = (float)glfwGetTime();
		deltaTime = curTime - lastTime;
		lastTime = curTime;

		if (firstEntered)
			deltaTime = 0.0f;

		if (newY + ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime) * m_playerSpeed > oldY + ((TILE_SIZE * TILE_MULTIPLIER) * stallTime))
			newY = oldY + ((TILE_SIZE * TILE_MULTIPLIER) * stallTime);
		else
			newY += (TILE_SIZE * TILE_MULTIPLIER) * deltaTime * m_playerSpeed;

		firstEntered = false;

		//Animation Down Here
		if (!stopSize && newY >= oldY + ((TILE_SIZE * TILE_MULTIPLIER) / 4))
		{
			stopSize = true;
			m_renderer->setExclamationSize(((TILE_SIZE * TILE_MULTIPLIER) / 2));
		}
		else if (!stopSize)
		{
			exclmSize += ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime * m_playerSpeed);
			m_renderer->setExclamationSize(exclmSize);
		}
		m_renderer->onUpdate();
	}

	m_renderer->setExclamationSize(0);
}