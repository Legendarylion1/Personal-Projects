#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "shaderClass.h"
#include "Texture.h"
#include "ParticleSystem.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Item
{
public:
	Item();
	~Item();

	glm::vec2 randomize(unsigned int playCount, unsigned int levelCount, bool includeThrowables);

	void bindAtlasUniforms(Shader& shader, Texture& textureAtlas);
	void resetAtlasUniforms(Shader& shader);

	void drawParticles(Shader& shader, Camera& camera);
	void attack(float weaponAngleStart, glm::vec3 Position);
	bool continueAttack(glm::vec3 Position);

	void setAtlasCoordinates(glm::vec2 coords);

	void setItemPosition(glm::vec3 newPosition);
	void setPlayerPosition(glm::vec3 newPosition);
	void setItemLayer(float layer);
	void setWeaponAngle(float angle);
	void setItemType(unsigned int type);
	void setFlipped(bool flipped);

	void setDamage(float damage);
	void setAttackSpeed(float attackSpeed);

	bool getFlipped();
	unsigned int getItemType();
	glm::vec2 getAtlasCoordinates();
	glm::vec3 getItemPosition();
	float getWeaponAngle();
	float getDamage();

private:
	ParticleSystem particleSystem;

	glm::vec2 atlasCoordinates = { 0,0 };

	glm::vec3 itemPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 playerPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 movementVector = glm::vec3(0.0f, 0.0f, 0.0f);
	unsigned int m_itemType = 4;
	bool m_flipped = false;

	float startingWeaponAngle = 0;
	float currentAnimationAngle = 0;
	float animationSpeed = 0.2f;
	float translationSpeed = 0.0f;
	float m_rotationSpeed = 0.0f;

	float currentWeaponAngle = 0;

	int animationCount = 0;
	int animationMid = 0;
	int animationEnd = 0;

	float m_damage = 20;

	int swordArc = 30;

	void buildSword(unsigned int rarity);
	void buildSpear(unsigned int rarity);
	void buildThrowable(unsigned int rarity);
	void buildGun(unsigned int rarity);
};