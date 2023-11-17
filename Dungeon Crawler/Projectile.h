#pragma once

#include <vector>

#include "MapSection.h"
#include "shaderClass.h"
#include "Camera.h"
#include "VAO.h"

class Projectile
{
public:
	Projectile(Texture& itemTexture);
	~Projectile();

	void drawProjectiles(Shader& shader, Camera& camera);
	void moveProjectiles(std::vector<MapSection>& mapSections);
	void clearGroundedProjectiles();
	
	
	void playerBulletHits(std::vector<unsigned int> bulletHitIndexes);
	void aiBulletHits(std::vector<unsigned int > bulletHitIndexes);

	void throwItem(glm::vec2 atlasCoords, glm::vec3 startPosition, glm::vec3 movementVector, float itemSpeed, unsigned int roomID, float itemAngle, float itemDamage, unsigned int attackerID);
	void shootBullet(glm::vec3 startPosition, glm::vec3 movementVector, float itemSpeed, unsigned int roomID, float bulletAngle, float bulletDamage, unsigned int attackerID);

	void addAIBullet(glm::vec4 bulletData, unsigned int roomID);

	void clearProjectiles();
	struct thrownItem
	{
		unsigned int roomID;
		unsigned int attackerID;

		float itemSpeed = 1.0f;
		float itemAngle = 0.0f;
		float throwableDamage = 0.0f;

		glm::vec2 atlasCoords = { 0, 0 };
		glm::vec3 Position = { 0.0f,0.0f,0.0f };
		glm::vec3 movementVector = { 0.0f,0.0f,0.0f };
		std::vector<unsigned int> hits;

		thrownItem(glm::vec2 atlasCoordinates, glm::vec3 startPosition, glm::vec3 startMovementVector, float startItemSpeed, unsigned int startingRoomID, float startingAngle, float damage, unsigned int throwerID)
		{
			thrownItem::itemSpeed = startItemSpeed;
			thrownItem::atlasCoords = atlasCoordinates;
			thrownItem::Position = startPosition;
			thrownItem::movementVector = startMovementVector;
			thrownItem::roomID = startingRoomID;
			thrownItem::itemAngle = startingAngle;
			thrownItem::throwableDamage = damage;
			thrownItem::attackerID = throwerID;
		}

		void addHits(std::vector<unsigned int> newHits)
		{
			for (int i = 0; i < newHits.size(); i++)
			{
				hits.push_back(newHits.at(i));
			}
		}
	};

	struct bullet
	{
		unsigned int roomID;
		unsigned int attackerID;

		float itemSpeed = 1.0f;
		float itemAngle = 0.0f;
		float bulletDamage = 0.0f;

		glm::vec3 Position = { 0.0f,0.0f,0.0f };
		glm::vec3 movementVector = { 0.0f,0.0f,0.0f };

		bullet(glm::vec3 startPosition, glm::vec3 startMovementVector, float startItemSpeed, unsigned int startingRoomID, float startingAngle, float damage, unsigned int shooterID)
		{
			bullet::itemSpeed = startItemSpeed;
			bullet::Position = startPosition;
			bullet::movementVector = startMovementVector;
			bullet::roomID = startingRoomID;
			bullet::itemAngle = startingAngle;
			bullet::bulletDamage = damage;
			bullet::attackerID = shooterID;
		}
	};

	std::vector<thrownItem> getGroundedProjectiles();
	std::vector<thrownItem>& getProjectiles();
	std::vector<bullet>& getPlayerBullets();
	std::vector<bullet>& getAIBullets();

private:
	Texture m_itemTexture;
	VAO m_vaoList[3];

	std::vector<bullet> bulletVector;
	std::vector<bullet> m_aiBullets;
	std::vector<thrownItem> thrownItemVector;
	std::vector<thrownItem> groundedItems;
};