#include "AIStats.h"

/// <summary>
/// Constructor for setting the stats of an enemy AI
/// </summary>
/// <param name="startingPosition">- Starting position of the AI</param>
AIStats::AIStats(glm::vec3 startingPosition)
{
	Position = startingPosition;
}

/// <summary>
/// Returns whether or not the AI is attacking
/// </summary>
/// <returns></returns>
bool AIStats::isAttacking()
{
	return m_attacking;
}

/// <summary>
/// Adds the players ID to it's hit IDs
/// </summary>
/// <param name="ID">- ID of the player hit</param>
void AIStats::addHit(unsigned int ID)
{
	m_hitIDS.push_back(ID);
}

void AIStats::addAttacker(unsigned int ID)
{
	for (int i = 0; i < m_kdaReport.size(); i++)
	{
		if (m_kdaReport.at(i) == ID)
		{
			m_kdaReport.erase(m_kdaReport.begin() + i);
		}
	}
	m_kdaReport.push_back(ID);
}

/// <summary>
/// Returns the ID of the AI
/// </summary>
/// <returns></returns>
unsigned int AIStats::getID()
{
	return m_ID;
}

/// <summary>
/// Returns all of the player IDs that the AI has hit
/// </summary>
/// <returns></returns>
std::vector<unsigned int> AIStats::getHitIDS()
{
	return m_hitIDS;
}

/// <summary>
/// Returns the current health of the AI
/// </summary>
/// <returns></returns>
float AIStats::getCurrentHealth()
{
	return currentHealth;
}

/// <summary>
/// Returns the maximum health of the AI
/// </summary>
/// <returns></returns>
float AIStats::getMaxHealth()
{
	return maxHealth;
}

/// <summary>
/// Returns the current position of the AI in world coordinates
/// </summary>
/// <returns></returns>
glm::vec3 AIStats::getPosition()
{
	return Position;
}

/// <summary>
/// Returns the current weapon angle of the AI
/// </summary>
/// <returns></returns>
float AIStats::getWeaponAngle()
{
	return m_weaponAngle;
}

/// <summary>
/// Returns the atlas coordinates that the AI is using
/// </summary>
/// <returns></returns>
glm::vec2 AIStats::getAtlasCoords()
{
	return m_atlasCoords;
}

/// <summary>
/// Returns the current position of the weapon
/// </summary>
/// <returns></returns>
glm::vec3 AIStats::getWeaponPosition()
{
	//TODO: Maybe remove
	return Position + m_weaponPosition;
}

/// <summary>
/// Returns the number of bullets to fire
/// </summary>
/// <returns></returns>
unsigned int AIStats::getBulletCount()
{
	return m_bulletsToFire;
}

std::vector<unsigned int> AIStats::getKDAReport()
{
	return m_kdaReport;
}

/// <summary>
/// Adjusts the AI's health by the desired value
/// </summary>
/// <param name="value">- Amount to adjust the health by</param>
void AIStats::adjustCurrentHealth(float value)
{
	currentHealth += value;
	if (currentHealth < 0)
		currentHealth = 0;
}

/// <summary>
/// Adjusts the maximum health of the AI
/// </summary>
/// <param name="value"></param>
void AIStats::adjustMaxHealth(float value)
{
	maxHealth += value;
}

/// <summary>
/// Moves the AI in the desired direction using its speed as the number of units
/// </summary>
/// <param name="direction">- Desired direction to move in</param>
void AIStats::move(unsigned int direction)
{
	if (direction == UP)
		Position.y += speed;
	else if (direction == DOWN)
		Position.y -= speed;
	else if (direction == LEFT)
		Position.x -= speed;
	else
		Position.x += speed;
}

/// <summary>
/// Sets the ID of the AI
/// </summary>
/// <param name="ID">- Desired ID for the AI</param>
void AIStats::setID(unsigned int ID)
{
	m_ID = ID;
}

/// <summary>
/// Sets the current weapon angle
/// </summary>
/// <param name="angle">- Desired weapon angle</param>
void AIStats::setWeaponAngle(float angle)
{
	m_weaponAngle = angle;
}

/// <summary>
/// Sets whether or not the AI is attacking
/// </summary>
/// <param name="status">- Whether or not the AI is attacking</param>
void AIStats::setAttacking(bool status)
{
	m_attacking = status;
}

/// <summary>
/// Sets the item Atlas coords for the AI
/// </summary>
/// <param name="atlasCoords">- Atlas coords of the weapon</param>
void AIStats::setAtlasCoords(glm::vec2 atlasCoords)
{
	m_atlasCoords = atlasCoords;
}

/// <summary>
/// Sets the number of bullets for the AI to fire
/// </summary>
/// <param name="count">- Number of bullets to fire</param>
void AIStats::setBulletCount(unsigned int count)
{
	m_bulletsToFire = count;
}

/// <summary>
/// Sets AI Attacking to true
/// </summary>
void AIStats::startAttack()
{
	//TODO: Seems redundant maybe remove
	m_attacking = true;
}

/// <summary>
/// Clears the vector of players that the AI has hit
/// </summary>
void AIStats::clearHitIDS()
{
	m_hitIDS.clear();
}