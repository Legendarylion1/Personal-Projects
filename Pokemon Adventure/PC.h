#pragma once
#include "Trainer.h"
#include "SpeciesChart.h"
#include "AttackChart.h"
#include <fstream>

class PC
{
public:

	struct userSettings
	{
		std::string resolution;
		int up, down, left, right, interact;
		bool showFps, fasterText, autoSave;
	};

public:

	bool addPokemon(Trainer& trainer, Pokemon pokemon);
	void movePokemon(unsigned int box1, unsigned int index1, unsigned int box2, unsigned int index2);
	void insertPokemon(Pokemon pokemon, unsigned int box, unsigned int index);
	Pokemon popPokemon(unsigned int box, unsigned int index);


	std::vector<unsigned int> getPlayerLocation();
	std::vector<Pokemon> getBox(unsigned int index);
	std::string getBoxName(unsigned int index);
	std::vector<std::vector<bool>> getNptData();

	void printBox(unsigned int box);
	void setPlayerPosition(unsigned int mapID, unsigned int x, unsigned int y, unsigned int direction);
	void setBuildingEvent(unsigned int buildingEvent);
	void setCutsceneCount(unsigned int cutsceneCount);
	void setNptData(std::vector<std::vector<bool>> nptData);
	void setAutoSave(bool autoSave);

	void loadPC(Trainer& trainer, bool overwriteData);
	bool savePC(Trainer& trainer);
	void autoSave(Trainer& trainer, unsigned int mapID, unsigned int x, unsigned int y, unsigned int direction, std::vector<std::vector<bool>> nptData);

	void loadUserSettings(userSettings* settings);
	void saveUserSettings(userSettings* settings);

private:

	void buildPokemon(std::string line, unsigned int loadState);


	std::string getRosterData(Trainer& trainer, unsigned int index);
	std::string getPCData(unsigned int box, unsigned int index);
	std::string getItemData(unsigned int ID);
	std::string getCoordData();
	std::string getNptData(std::vector<bool> data);
	std::string getColonData(std::string data);

	void buildBoxPokemon(std::string line);
	void buildRosterPokemon(std::string line);
	void buildItemSection(std::string line);
	void buildCoordinates(std::string line);
	void buildNptData(std::string line);

private:
	unsigned int boxSection = 0;
	unsigned int rosterSection = 1;
	unsigned int itemSection = 2;
	unsigned int coordSection = 3;
	unsigned int nptSection = 4;

	std::string m_boxSection =		"0-1101-000-0110--0001-0-11-0-00-11011-010-1101";
	std::string m_rosterSection =	"0-11-1-010-00--11-100-10011-011-110-110110-0011-";
	std::string m_itemSection =		"0-12-1-010--03-11-100-1631-011-110-15-7210-0011-";
	std::string m_coordSection =	"12-421-53---543-0-00-0000--0-0-22-7-0-1-1-2-34---";
	std::string m_nptSection =		"6-54-504-63-006--34---234--520-0-3-21-456-00-0-0";



	Pokemon m_allPokemon[8][20];
	Pokemon m_roster[6];
	std::vector<unsigned int> m_items;
	std::vector<std::vector<bool>> m_nptData;

	bool m_changesMade = false;
	bool m_autoSave = false;
	unsigned int m_boxPokemonCount[8] = {0};


	unsigned int m_playerTileX = 15;
	unsigned int m_playerTileY = 10;
	unsigned int m_playerMapID = 0;
	unsigned int m_playerDirection = 0;
	unsigned int m_buildingEvent = 0;

	unsigned int m_cutsceneCount = 0;
};