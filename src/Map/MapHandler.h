#pragma once
#include "MapSection.h"

class MapHandler
{
public:
	MapHandler() {};
	MapHandler(Trainer* trainer, Renderer* renderer);

	void onUpdate();

	void setup() { m_mapSections[m_currentSection].loadMap(); };
	bool isValidCharacterPosition(Coordinate coords);
	char getPlayerTile() { return  m_mapSections[m_currentSection].getMapTile(m_trainer->position.coords); };
	char getTile(Coordinate coord) { return m_mapSections[m_currentSection].getMapTile(coord); };

public:
	void addMapSection(MapSection section);

	std::vector<PokemonSpawn> getPokemonSpawns() { return m_mapSections[m_currentSection].getPokemonSpawns(); };
	std::vector<ItemID> getAvailableItems() { return  m_mapSections[m_currentSection].getAvailableItems(); };
	int getPokemonMinLevel() { return m_mapSections[m_currentSection].getPokemonMinLevel(); };
	int getPokemonMaxLevel() { return m_mapSections[m_currentSection].getPokemonMaxLevel(); };

	NPT* getAI(Coordinate aiPosition) { return m_mapSections[m_currentSection].getAI(aiPosition); };
	NPT* getAI(int index) { return m_mapSections[m_currentSection].getAI(index); };
	std::vector<NPT*> getAllAI() { return m_mapSections[m_currentSection].getAllAI(); };
	std::vector<NPT*> getScriptedAI() { return m_mapSections[m_currentSection].getScriptedAI(); };

	void reserveCoordinate(Coordinate coord) { m_mapSections[m_currentSection].reserveCoordinate(coord); };
	void removeCoordinate(Coordinate coord) { m_mapSections[m_currentSection].removeCoordinate(coord); };

	CutSceneID getCutsceneID(Coordinate coord) { return m_mapSections[m_currentSection].getCutsceneID(coord); };

private:
	void swapSections();

private:
	Trainer* m_trainer = nullptr;

	SectionID m_currentSection = SectionID::MAIN_SECTION;
	std::unordered_map<SectionID, MapSection> m_mapSections;
};