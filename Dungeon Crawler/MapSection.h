#pragma once

#include <vector>

#include "AIStats.h"

class MapSection

{
public:
	Texture sectionBackground;
	int up = -1;
	int down = -1;
	int left = -1;
	int right = -1;

	unsigned int ID;
	int x = 0;
	int y = 0;

	MapSection(Texture& backgroundTexture, int xLoc, int yLoc, unsigned int sectionID, Texture& enemyTexture);
	~MapSection();

	void setBackgroundTexture(Texture& texture);
	void setEndTexture(Texture& texture);
	void setEnd(bool isEnd);

	void drawSection(Shader& shader, Camera& camera, Texture& itemAtlas, Player& enemy);
	void drawEnemies(Shader& shader, Camera& camera, Player& enemy, Texture& itemAtlas);
	void drawItems(Shader& shader, Camera& camera, Texture& itemAtlas);
	void drawDividers(Shader& shader, Camera& camera);
	void deleteVectors(bool deleteTexture);

	void adjustBounds(unsigned int mapType);
	std::vector<int> withinBounds(glm::vec3 position, float speed, float width, float height,unsigned int direction, int enteringID);
	std::vector<int> withinBounds(glm::vec3 position, glm::vec3 movementVector, float width, float height, int enteringID);
	bool betweenBorders(float x, float y, float width, float height, unsigned int direction);

	glm::vec2 getCenter();
	int getInteractions(glm::vec3 Position, float width, float height);
	std::vector<unsigned int> getHitIDS();
	std::vector<AIStats>& getAI();
	std::vector<glm::vec4> getBullets();
	std::vector<std::vector<unsigned int>> getKillReport();
	void clearKDAReport();


	void addItem(Item newItem);
	Item popItem(unsigned int index);

	bool hasEnemies();
	void addEnemy(glm::vec3 enemyPositions);
	std::vector<unsigned int> attackEnemy(float weaponAngle, float weaponDamage, glm::vec3 weaponPosition, std::vector<unsigned int> hitIDS, unsigned int attackerID);
	bool hitAlready(AIStats& aiStats, std::vector<unsigned int> hitIDS);
	std::vector<glm::vec3> progressAI(std::vector<glm::vec3> playerPositions);

private:

	Texture m_endTexture;
	Texture m_enemyTexture;
	bool m_end = false;
	bool m_blockExits = false;

	float m_topBound = 0;
	float m_bottomBound = 0;
	float m_leftBound = 0;
	float m_rightBound = 0;

	unsigned int m_aiID = 0;

	std::vector<VAO> vaoVector;
	std::vector<VBO> vboVector;
	std::vector<EBO> eboVector;

	std::vector<Item> itemVector;
	std::vector<Item> m_enemyItems;
	std::vector<AIStats> enemyStats;
	std::vector<std::vector<unsigned int>> m_kdaVector;

	void calculateAI(AIStats& enemyStats, std::vector<glm::vec3> playerPositions, unsigned int index);
	void aiMove(AIStats& enemyStats, glm::vec3 playerPosition, unsigned int index);
	void aiAttack(AIStats& enemyStats, glm::vec3 playerPosition, float distance, unsigned int index);
};