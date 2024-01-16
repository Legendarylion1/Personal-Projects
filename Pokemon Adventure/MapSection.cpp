#include "MapSection.h"

MapSection::MapSection()
{
}

MapSection::MapSection(std::string textureName, unsigned int id, int width, int height, std::vector<std::string> layout)
{
	m_textureName = textureName;
	m_width = width;
	m_height = height;
	m_id = id;

	std::reverse(layout.begin(), layout.end());

	sectionLayout = layout;
	m_tilesTall = layout.size();
	m_tilesWide = layout.at(0).size();
}

MapSection MapSection::setupNextSection(Renderer* renderer, unsigned int prevLocation)
{
	return MapSection();
}

void MapSection::setPokemonStats(std::vector<unsigned int> pokemonIDs, unsigned int levelCap)
{
	m_pokemonIDs = pokemonIDs;
	m_levelCap = levelCap;
}

void MapSection::setSpawn(unsigned int direction, unsigned int x, unsigned int y)
{
	m_spawns.insert({ direction, glm::vec2(x,y) });
}

void MapSection::setPokeCenterSpawn(unsigned int x, unsigned int y)
{
	m_pokeCenterSpawn = glm::vec2(x, y);
}

void MapSection::setPokeShopSpawn(unsigned int x, unsigned int y)
{
	m_pokeShopSpawn = glm::vec2(x, y);
}

void MapSection::setItemsAvailable(std::vector<unsigned int> itemsAvailable)
{
	m_itemsAvailable = itemsAvailable;
}

void MapSection::setCutsceneScript(std::string script)
{
	m_cutsceneScript = script;
}

void MapSection::setCutsceneID(unsigned int cutsceneID)
{
	m_cutsceneID = cutsceneID;
}

void MapSection::setNptData(std::vector<bool> nptData)
{
	for (int i = 0; i < m_assignedAI.size(); i++)
	{
		if (nptData.at(i) == false)
			m_assignedAI.at(i).removePokemon();
	}
}

void MapSection::addToCutScene(std::string command)
{
	m_cutsceneScript += command;
}

void MapSection::addToCutScene(std::string command, unsigned int value)
{
	std::string newCommand = command + std::to_string(value);
	m_cutsceneScript += newCommand;
}

std::vector<bool> MapSection::getNptData()
{
	std::vector<bool> nptData;

	for (int i = 0; i < m_assignedAI.size(); i++)
	{
		nptData.push_back(m_assignedAI.at(i).hasPokemon());
	}

	return nptData;
}

std::vector<unsigned int> MapSection::getPokemonIDs()
{
	return m_pokemonIDs;
}

unsigned int MapSection::getLevelCap()
{
	return m_levelCap;
}

unsigned int MapSection::getID()
{
	return m_id;
}

glm::vec2 MapSection::getSpawn(unsigned int direction)
{
	return m_spawns[direction];
}

glm::vec2 MapSection::getPokeCenterSpawn()
{
	return m_pokeCenterSpawn;
}

glm::vec2 MapSection::getPokeShopSpawn()
{
	return m_pokeShopSpawn;
}

std::vector<unsigned int> MapSection::getAvailableItems()
{
	return m_itemsAvailable;
}

std::string MapSection::getCutsceneScript()
{
	return m_cutsceneScript;
}

MapSection MapSection::getLinkedSection(unsigned int direction)
{
	return m_linkedSections[direction];
}

void MapSection::linkSection(unsigned int direction, MapSection linkedSection)
{
	m_linkedSections.insert({ direction, linkedSection });
}

void MapSection::setupRenderer(Renderer* renderer)
{
	renderer->setMapStats(m_textureName, m_width, m_height);
	renderer->setAiPositions(&m_assignedAI);
}

void MapSection::addAI(NPT newAI)
{
	m_assignedAI.push_back(newAI);
	sectionLayout.at(newAI.getTileY()).at(newAI.getTileX()) = 'T';
}
