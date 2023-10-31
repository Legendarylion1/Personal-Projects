#pragma once
#include "MapSection.h"
#include "SpeciesChart.h"

namespace Events
{
	static unsigned int inGrass			= 0;

	static unsigned int movedUp			= 2;
	static unsigned int movedDown		= 3;
	static unsigned int movedLeft		= 4;
	static unsigned int movedRight		= 5;

	static unsigned int turnUp			= 6;
	static unsigned int turnDown		= 7;
	static unsigned int turnLeft		= 8;
	static unsigned int turnRight		= 9;

	static unsigned int transferUp		= 10;
	static unsigned int transferDown	= 11;
	static unsigned int transferLeft	= 12;
	static unsigned int transferRight	= 13;

	static unsigned int trainerSpotted	= 14;

	static unsigned int pokeCenter		= 15;
	static unsigned int pokeShop		= 16;
	static unsigned int returnSection	= 17;

	static unsigned int interactPC		= 18;
	static unsigned int interactNurse	= 19;
	static unsigned int interactTrainer	= 20;
	static unsigned int interactItemBuy	= 21;
	static unsigned int interactMoveBuy	= 22;

	static unsigned int startCutScene	= 23;
}

class GameMap
{
public:
	GameMap();
	void setup(bool* up, bool* down, bool* left, bool* right, bool* interact, Renderer* renderer);
	std::vector<unsigned int> pollEvents();

	glm::vec2 swapMapSections(unsigned int direction, Renderer* renderer);
	glm::vec2 swapPokeCenter(Renderer* renderer);
	glm::vec2 swapPokeShop(Renderer* renderer);
	glm::vec2 returnFromBuilding(Renderer* renderer);

	glm::vec2 getPlayerPosition();

	void setCurrentMap(unsigned int mapID);
	void setBuildingEvent(unsigned int buildingEvent);
	void setPlayerPosition(unsigned int x, unsigned int y);
	void setNptData(std::vector<std::vector<bool>> nptData);
	void adjustPlayerPosition(unsigned int x, unsigned int y);
	void adjustPlayerDirection(unsigned int direction);
	 
	std::vector<std::vector<bool>> getNptData();
	std::vector<unsigned int> getMapSpecies();
	std::vector<unsigned int> getMapItems();
	unsigned int getMapLevelCap();
	unsigned int getMapID();
	MapSection& getMapSection();

	NPT& getNPT();
	NPT& getNPT(unsigned int index);
	unsigned int getNptID(NPT& npt);
private:

	void setupMapSections();
	void initBuildingEvent(Renderer* renderer);

	int nptSpottedIndex(bool evaluatingEvents = true);

private:
	Texture* m_mapTexture = nullptr;
	std::vector<MapSection> m_allSections;

	MapSection m_pokeCenter;
	MapSection m_pokeShop;
	MapSection m_currentBuilding;

	unsigned int m_currentMap = 0;
	unsigned int m_prevMap = 0;
	unsigned int m_buildingEvent = 0;

	unsigned int m_xPos = 0;
	unsigned int m_yPos = 0;
	unsigned int m_characterDirection = Direction::UP;

	bool* m_up = nullptr;
	bool* m_down = nullptr;
	bool* m_left = nullptr;
	bool* m_right = nullptr;
	bool* m_interact = nullptr;
};