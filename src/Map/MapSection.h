#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "../Characters/Trainer/NPT.h"
#include "../Characters/Pokemon/Pokemon.h"

struct PokemonSpawn
{
	Rarity rarity;
	PokemonID pokemon;
};

class MapSection
{
public:
	MapSection() {};
	MapSection(Renderer* renderer) { m_renderer = renderer; };

	void setID(SectionID id) { m_id = id; };
	SectionID getID() { return m_id; };

	void onUpdate();

	void setMap(std::vector<std::string> map);
	void setPokemonLevelCaps(int min, int max);
	void setAvailableItems(std::vector<ItemID> items) { m_availableItems = items; };
	void addPokemonSpawn(PokemonSpawn pokemonSpawn);
	void addCutscene(Coordinate coord, CutSceneID id);
	void linkSection(Coordinate coord, SectionID id, Coordinate playerSpawn);
	void resetAIPositions();
	void loadMap() { m_renderer->loadMap(m_id, m_map.at(0).size(), m_map.size()); };

	char getMapTile(Coordinate coord);
	std::vector<PokemonSpawn> getPokemonSpawns() { return m_pokemonSpawns; };
	std::vector<ItemID> getAvailableItems() { return m_availableItems; };
	int getPokemonMinLevel() { return m_pokemonMinLevel; };
	int getPokemonMaxLevel() { return m_pokemonMaxLevel; };
	Coordinate getPlayerSpawn(Coordinate coord) { return m_playerSpawn[coord]; };
	SectionID getLinkedSection(Coordinate coord) { return m_linkedSections[coord]; };
	NPT* getAI(Coordinate position);
	NPT* getAI(int index) { return m_npt.at(index); };
	std::vector<NPT*> getAllAI() { return m_npt; };
	std::vector<NPT*> getScriptedAI();

	CutSceneID getCutsceneID(Coordinate coord) { return m_cutscenes[coord]; };

public:
	void addNPT(NPT* npt) { m_npt.push_back(npt); };

	void reserveCoordinate(Coordinate coord) { m_reservedCoords.push_back(coord); };
	void removeCoordinate(Coordinate coord);
private:
	Renderer* m_renderer = nullptr;
	SectionID m_id = SectionID::MAIN_SECTION;

	int m_pokemonMinLevel = 1;
	int m_pokemonMaxLevel = 1;

	std::vector<PokemonSpawn> m_pokemonSpawns;
	std::vector<std::string> m_map;
	std::vector<Coordinate> m_reservedCoords;
	std::vector<ItemID> m_availableItems;
	std::vector<NPT*> m_npt;

	std::unordered_map<Coordinate, SectionID, CoordinateHashFunction> m_linkedSections;
	std::unordered_map<Coordinate, Coordinate, CoordinateHashFunction> m_playerSpawn;
	std::unordered_map<Coordinate, CutSceneID, CoordinateHashFunction> m_cutscenes;
};