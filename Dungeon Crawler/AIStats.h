#pragma once

#include "Texture.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Item.h"
#include "Player.h"


class AIStats
{
public:
	AIStats(glm::vec3 startingPosition);

	bool isAttacking();
	void addHit(unsigned int ID);
	void addAttacker(unsigned int ID);

	unsigned int getID();
	std::vector<unsigned int> getHitIDS();
	float getCurrentHealth();
	float getMaxHealth();
	glm::vec3 getPosition();
	float getWeaponAngle();
	glm::vec2 getAtlasCoords();
	glm::vec3 getWeaponPosition();
	unsigned int getBulletCount();
	std::vector<unsigned int> getKDAReport();

	void adjustCurrentHealth(float value);
	void adjustMaxHealth(float value);
	void move(unsigned int direction);

	void setID(unsigned int ID);
	void setWeaponAngle(float angle);
	void setAttacking(bool status);
	void setAtlasCoords(glm::vec2 atlasCoords);
	void setBulletCount(unsigned int count);

	void startAttack();
	void clearHitIDS();
private:
	unsigned int m_ID = 0;
	bool m_attacking = false;

	float currentHealth = 100;
	float maxHealth = 100;
	float speed = 0.1f;
	float m_weaponAngle = 0;
	unsigned int m_bulletsToFire = 0;

	glm::vec3 m_weaponPosition = { 0.0f,0.0f,0.0f };
	glm::vec3 Position = { 0.0f,0.0f,0.0f };
	glm::vec2 m_atlasCoords = { BASIC,SWORD };

	std::vector<unsigned int> m_hitIDS;
	std::vector<unsigned int> m_kdaReport;
};