#pragma once


#include "Armor.h"
#include "Camera.h"
#include "PlayerUI.h"

#include <vector>

class Player
{
public:
	Player();
	Player(unsigned int playerID, Shader& shader, Texture& itemTexture);
	~Player();

	void initPlayer(Texture& itemTexture);
	void initPlayer(unsigned int playerID, Shader& shader, Texture& itemTexture);
	void initUI();
	void drawPlayer(Shader& shader, Camera& camera, bool isEnemy);
	void moveToStart(Camera& camera);
	void resetPlayer();
	
	void move(unsigned int direction, Camera& camera);
	void startAttack();
	void adjustHealth(float amount);
	void addHits(std::vector<unsigned int> newHits);
	void clearHits();
	void addKills(int value);
	void addDeaths(int value);
	void addAssists(int value);
	bool isAttacking();
	bool isInitialized();

	void setPlayerTexture(Shader& shader, Texture& texture);
	void setDisplayHealthbar(bool displayStatus);
	void setPlayerPosition(glm::vec3 Pnewosition);
	void setItemPosition(glm::vec3 Position);
	void setCurItemIndex(unsigned int itemSlot);
	void setWeaponAngle(double angle);
	void setRoomIndex(unsigned int roomIndex);
	void setItemIndex(unsigned int index, Item newItem);
	void setItemUsage(unsigned int index, bool itemUsage);
	void setCurrentHealth(float health);
	void setAttacking(bool isAttacking);

	Item& getCurrentItem();
	float getHealth();
	float getSpeed();
	float getWeaponAngle();
	unsigned int getRoomIndex();
	unsigned int getItemIndex();
	bool getItemUsage(unsigned int index);
	glm::vec3 getPosition();
	glm::vec3 getWeaponPosition();
	std::vector<unsigned int> getHitEnemyIDs();
	std::vector<int> getKDA();
private:
	PlayerUI ui;
	Texture playerTexture;
	Texture itemAtlas;

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	float weaponAngle = 0;
	unsigned int playerID = 0;
	unsigned int curItemIndex = 0;
	unsigned int curRoomIndex = 0;
	bool playerInitialized = false;
	bool attacking = false;
	bool m_displayHealthbar = true;

	float maxHealth = 100;
	float currentHealth = 0;
	float speed = 1.5f;
	std::vector<unsigned int> hitEnemyIDs;
	std::vector<int> m_kdaVector = {0,0,0};

	Item itemArray[3];
	bool m_itemUsage[3] = { true, false, false };

	std::vector<VAO> vaoVector;
	std::vector<VBO> vboVector;
	std::vector<EBO> eboVector;
};