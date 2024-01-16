#pragma once
#include "MapSection.h"
#include "SpeciesChart.h"

static enum Events
{
	inGrass,

	movedUp,
	movedDown,
	movedLeft,
	movedRight,

	jumpUp,
	jumpDown,
	jumpLeft,
	jumpRight,

	turnUp,
	turnDown,
	turnLeft,
	turnRight,

	transferUp,
	transferDown,
	transferLeft,
	transferRight,

	trainerSpotted,

	pokeCenter,
	pokeShop,
	returnSection,

	interactPC,
	interactNurse,
	interactTrainer,
	interactItemBuy,
	interactMoveBuy,

	startCutScene
};

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