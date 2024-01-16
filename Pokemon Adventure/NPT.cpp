#include "NPT.h"

int NPT::performAction(Pokemon& aiPokemon, Pokemon& playerPokemon)
{
	//TODO: Refactor this to fit the new way the encounters work
	//TODO: Add heal options based on the potion used

	int healCount = getTotalHealCount(); //TODO: Heal count doesnt tell how many of each item we have
	int pokemonCount = 0;

	for (int i = 0; i < 6; i++)
	{
		if (getPokemon(i)->getLevel() != 0 && getPokemon(i)->getHealth() != 0)
			pokemonCount += 1;
	}

	if (m_excessHeals == 0 && healCount > pokemonCount)
		m_excessHeals = healCount - pokemonCount;

	healCount -= m_excessHeals;



	if ((healCount == pokemonCount || pokemonCount == 1) && aiPokemon.getHealth() * 3 <= aiPokemon.getMaxHealth() && healCount >= 1)
	{
		std::cout << "[NPT][PerformAction] Returning Heal with the following stats" << std::endl;
		std::cout << "[NPT][PerformAction] HealCount: " << healCount << std::endl;
		std::cout << "[NPT][PerformAction] Pokemon Count: " << pokemonCount << std::endl;
		return 5;
	}

	if (aiPokemon.outOfMoves())
		return 4;


	return aiPokemon.determineAttack(playerPokemon);
}

Item* NPT::getNextHeal()
{
	return getHealItem(0);
}

void NPT::removeHeal()
{
	removeItem(*getHealItem(0));
}

void NPT::resetDefaultPosition()
{
	setTileX(m_defaultXTile);
	setTileY(m_defaultYTile);
	m_direction = m_defaultDirection;
}

void NPT::setX(float x)
{
	m_x = x;
}

void NPT::setY(float y)
{
	m_y = y;
}

void NPT::setTileX(unsigned int x)
{
	m_x = x * (TILE_SIZE * TILE_MULTIPLIER);
	m_tileX = x;
}

void NPT::setTileY(unsigned int y)
{
	m_y = y * (TILE_SIZE * TILE_MULTIPLIER);
	m_tileY = y;
}

void NPT::setDirection(unsigned int direction)
{
	m_direction = direction;
}

/// <summary>
/// When setting text. There must be an even number of top and bot lines even if the line is empty.
/// </summary>
void NPT::setFightText(std::vector<std::string> topLines, std::vector<std::string> botLines)
{
	m_fightTopLines = topLines;
	m_fightBotLines = botLines;
}

void NPT::setDefaultText(std::vector<std::string> topLines, std::vector<std::string> botLines)
{
	m_defaultTopLines = topLines;
	m_defaultBotLines = botLines;
}

void NPT::setCutsceneText(std::vector<std::string> topLines, std::vector<std::string> botLines)
{
	m_cutSceneTopLines = topLines;
	m_cutSceneBotLines = botLines;
}

void NPT::setSpriteState(unsigned int spriteState)
{
	m_spriteState = spriteState;
}

void NPT::removePokemon()
{
	for (int i = 0; i < 6; i++)
	{
		popPokemon(i);
	}
}

std::vector<std::string> NPT::getTopLines()
{
	if (hasPokemon())
	{
		std::cout << "[NPT] Returning Fight Top Lines\n";
		return m_fightTopLines;
	}
	else
	{
		std::cout << "[NPT] Returning Default Top Lines\n";
		return m_defaultTopLines;
	}
}

std::vector<std::string> NPT::getBotLines()
{
	if (hasPokemon())
		return m_fightBotLines;
	else
		return m_defaultBotLines;
}

unsigned int NPT::tilesFromTrainer(unsigned int x, unsigned int y)
{
	if (m_direction == Direction::UP)
		return y - m_tileY - 1;
	else if (m_direction == Direction::DOWN)
		return m_tileY - y - 1;
	else if (m_direction == Direction::LEFT)
		return m_tileX - x - 1;
	else if (m_direction == Direction::RIGHT)
		return x - m_tileX - 1;

	return 0;
}
