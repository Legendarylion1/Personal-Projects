#pragma once
#include <vector>
#include <string>

#include "Renderer.h"

//TODO: Find a place for this
namespace cutsceneEvents
{
	static std::string NONE = "";
	static std::string AI_INDEX = "I";
	static std::string MOVE_UP = "U";
	static std::string MOVE_DOWN = "D";
	static std::string MOVE_LEFT = "L";
	static std::string MOVE_RIGHT = "R";
	static std::string SPEAK = "S";
	static std::string SET_X_TILE = "X";
	static std::string SET_Y_TILE = "Y";
};

class MapSection
{
public:
	MapSection();
	MapSection(std::string textureName, unsigned int id, int width, int height, std::vector<std::string> layout);

	MapSection setupNextSection(Renderer* renderer, unsigned int prevLocation);

	/// <param name="pokemonIDs">- IDs of the pokemon in the section</param>
	/// <param name="levelCap">- Level Cap of the section. When the level cap is being used 3 will be added to it</param>
	void setPokemonStats(std::vector<unsigned int> pokemonIDs, unsigned int levelCap);
	void setSpawn(unsigned int direction, unsigned int x, unsigned int y);
	void setPokeCenterSpawn(unsigned int x, unsigned int y);
	void setPokeShopSpawn(unsigned int x, unsigned int y);
	void setItemsAvailable(std::vector<unsigned int> itemsAvailable);
	void setCutsceneScript(std::string script);
	void setCutsceneID(unsigned int cutsceneID);
	void setNptData(std::vector<bool> nptData);

	void addToCutScene(std::string command);
	void addToCutScene(std::string command, unsigned int value);

	std::vector<bool> getNptData();
	std::vector<unsigned int> getPokemonIDs();
	unsigned int getLevelCap();
	unsigned int getID();


	/// <summary>
	/// Sets the spawn based on where in the image we are. If we are going down in the previous image then the spawn is up as in top
	/// </summary>
	/// <param name="direction"></param>
	/// <returns></returns>
	glm::vec2 getSpawn(unsigned int direction);
	glm::vec2 getPokeCenterSpawn();
	glm::vec2 getPokeShopSpawn();
	std::vector<unsigned int> getAvailableItems();
	std::string getCutsceneScript();

	unsigned int getCutsceneID() { return m_cutsceneID; }

	MapSection getLinkedSection(unsigned int direction);

	std::vector<NPT>& getAI() { return m_assignedAI; }
	NPT& getAI(unsigned int index) { return m_assignedAI.at(index); }

	void linkSection(unsigned int direction, MapSection linkedSection);

	void setupRenderer(Renderer* renderer);
	void addAI(NPT newAI);

public:
	std::vector<std::string> sectionLayout;

	unsigned int getWidth() { return m_width; }
	unsigned int getHeight() { return m_height; }

	unsigned int getTilesWide() { return m_tilesWide; }
	unsigned int getTilesTall() { return m_tilesTall; }

private:
	unsigned int m_id = 0;
	unsigned int m_levelCap = 1;

	unsigned int m_width = 0;
	unsigned int m_height = 0;

	unsigned int m_tilesWide = 0;
	unsigned int m_tilesTall = 0;

	unsigned int m_cutsceneID = 1000; //TODO: Figure out a default

	glm::vec2 m_pokeCenterSpawn = glm::vec2(0, 0);
	glm::vec2 m_pokeShopSpawn = glm::vec2(0, 0);

	std::string m_textureName;

	std::unordered_map<unsigned int, MapSection> m_linkedSections;
	std::unordered_map<unsigned int, glm::vec2> m_spawns;
	std::vector<unsigned int> m_pokemonIDs;
	std::vector<NPT> m_assignedAI;
	std::vector<unsigned int> m_itemsAvailable;
	std::string m_cutsceneScript = "";
};