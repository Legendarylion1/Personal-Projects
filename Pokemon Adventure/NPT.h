#pragma once

#include "Trainer.h"

//TODO: These definitions probably shouldnt be here
//NON PLAYABLE TRAINERS - named by my friend watson
const static unsigned int TILE_SIZE = 16;
const static unsigned int TILE_MULTIPLIER = 9;


class NPT : public Trainer
{ 
public:
	explicit NPT(std::string name, unsigned int x, unsigned int y, unsigned int direction, unsigned int detectDistance) : Trainer(name) 
	{
		m_name = name;

		setTileX(x);
		setTileY(y);

		m_defaultXTile = x;
		m_defaultYTile = y;
		m_defaultDirection = direction;

		m_direction = direction;
		m_detectDistance = detectDistance;
	};

	int performAction(Pokemon &aiPokemon, Pokemon &playerPokemon);
	Item* getNextHeal();
	void removeHeal();
	void resetDefaultPosition();

	void setX(float x);
	void setY(float y);
	void setTileX(unsigned int x);
	void setTileY(unsigned int y);
	void setDirection(unsigned int direction);
	void setFightText(std::vector<std::string> topLines, std::vector<std::string> botLines);
	void setDefaultText(std::vector<std::string> topLines, std::vector<std::string> botLines);
	void setCutsceneText(std::vector<std::string> topLines, std::vector<std::string> botLines);
	void setSpriteState(unsigned int spriteState);
	void removePokemon();

	float getX() { return m_x; }
	float getY() { return m_y; }
	unsigned int getTileX() { return m_tileX; }
	unsigned int getTileY() { return m_tileY; }
	unsigned int getDirection() { return m_direction; }
	unsigned int getDetectDistance() { return m_detectDistance; }
	std::vector<std::string> getTopLines();
	std::vector<std::string> getBotLines();
	std::vector<std::string> getCutsceneTopLines() { return m_cutSceneTopLines; }
	std::vector<std::string> getCutsceneBotLines() { return m_cutSceneBotLines; }
	unsigned int getSpriteState() { return m_spriteState; }

	unsigned int tilesFromTrainer(unsigned int x, unsigned int y);
private:
	std::string m_name;

	float m_x = 0;
	float m_y = 0;
	unsigned int m_tileX = 0;
	unsigned int m_tileY = 0;
	unsigned int m_direction = Direction::DOWN;
	unsigned int m_detectDistance = 0;
	unsigned int m_spriteState = 1;
	
	unsigned int m_defaultXTile = 0;
	unsigned int m_defaultYTile = 0;
	unsigned int m_defaultDirection = Direction::DOWN;

	std::vector<std::string> m_fightTopLines;
	std::vector<std::string> m_fightBotLines;

	std::vector<std::string> m_defaultTopLines;
	std::vector<std::string> m_defaultBotLines;


	std::vector<std::string> m_cutSceneTopLines;
	std::vector<std::string> m_cutSceneBotLines;

	bool m_healedThisTurn = false;
	unsigned int m_excessHeals = 0;
};