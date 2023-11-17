#pragma once

#include "MapSection.h"

class GameMap
{
public:
	GameMap(Shader& shader, Texture& itemAtlas);
	~GameMap();

	void generateMap(unsigned int numPlayers, unsigned int level);
	void drawMap(Shader& shader, Camera& camera, Texture& itemAtlas, Player& enemy);
	std::vector<glm::vec3> progressAI(unsigned int ID, std::vector<glm::vec3> playerPositions);

	std::vector<MapSection>& getMapSections();
private:
	struct mapTree
	{
		int x;
		int y;
		int status;
		int type = 0;
		struct mapTree* up = nullptr;
		struct mapTree* down = nullptr;
		struct mapTree* left = nullptr;
		struct mapTree* right = nullptr;

		mapTree(int xLoc, int yLoc, int sectionStatus)
		{
			this->x = xLoc;
			this->y = yLoc;
			this->status = sectionStatus;
			this->up = nullptr;
			this->down = nullptr;
			this->left = nullptr;
			this->right = nullptr;
		}
	};
	struct coordinateNode
	{
		int x;
		int y;
		struct coordinateNode* nextNode;

		coordinateNode(int xLoc, int yLoc)
		{
			this->x = xLoc;
			this->y = yLoc;
			this->nextNode = nullptr;
		}
	};

	coordinateNode* head = new coordinateNode(0, 0);
	mapTree* start = new mapTree(0, 0, 3);

	unsigned int m_longestSection = 0;
	unsigned int m_lastSectionID = 0;

	Texture textureArray[17];
	Texture m_endTexture;
	Texture m_itemTexture;
	Texture m_enemyTexture;
	std::vector<MapSection> mapSections;

	void initMap(Shader& shader, Texture& itemAtlas);
	void deleteVectors(bool deleteTextures);
	void generateTree(GameMap::mapTree* prevNode, int& curRoomCount, int& totalRooms, unsigned int prevDirection);
	void resetNodes();
	void populateTree(int& totalRooms);
	void createMapSections(GameMap::mapTree* node, int& sectionID, int prevRoomID, int direction, unsigned int branchLength);
	void linkRoom(MapSection& newSection, int prevRoomID, int direction);
	void longestBranch(unsigned int branchLength, int sectionID);
	void deconstructNodes();
	void freeMapTree(mapTree* node);
	void addCoordinateNode(GameMap::coordinateNode* newNode);
	bool searchCoordinateNodes(int x, int y);
	void implementMapInteractions(unsigned int numPlayers, unsigned int level);
	void addLoot(unsigned int ID, unsigned int playerCount, unsigned int level);
	void addEnemies(unsigned int ID, unsigned int playerCount, unsigned int level);
};