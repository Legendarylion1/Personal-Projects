#include "Item.h"

/// <summary>
/// Creates an item object
/// </summary>
Item::Item()
{
}

//TODO: Take a look at removing the destructor
Item::~Item()
{
}

/// <summary>
/// Randomizes the stats of the item based on the level and number of players. AI cannot use
/// throwables so we have a boolean to decide whether or not to create one.
/// </summary>
/// <param name="playerCount">- The number of players in the game</param>
/// <param name="levelCount">- The current level of the game</param>
/// <param name="includeThrowables">- Whether or not to make a throwable</param>
/// <returns>Atlas Coordinates of the item created</returns>
glm::vec2 Item::randomize(unsigned int playerCount, unsigned int levelCount, bool includeThrowables)
{

	//				~ ODDS ~
	//	50 - Basic			30	- Sword
	//	30 - Common			30	- Spear
	//	15 - RARE			20	- Throwable
	//	 5 - Legendary		20	- Gun

	unsigned int commonOdds = 30;
	unsigned int rareOdds = 15;
	unsigned int legendaryOdds = 5;

	unsigned int spearOdds = 30;
	unsigned int throwableOdds = 20;
	unsigned int gunOdds = 20;

	//float scaler = 2.0f * (level / 3);

	unsigned int rarity = BASIC;

	//	Item Rarity
	int result = rand() % 100 + 1;

	if (legendaryOdds + rareOdds + commonOdds <= result && result <= 100)
		rarity = BASIC;
	else if (legendaryOdds + rareOdds <= result && result < legendaryOdds + rareOdds + commonOdds)
		rarity = COMMON;
	else if (legendaryOdds <= result && result < legendaryOdds + rareOdds)
		rarity = RARE;
	else
		rarity = LEGENDARY;

		

	//	Item Type
	result = rand() % 100 + 1;

	if (gunOdds + throwableOdds + spearOdds <= result && result <= 100)
	{
		buildSword(rarity);
		return glm::vec2(rarity, SWORD);
	}
	else if (gunOdds + throwableOdds <= result && result < gunOdds + throwableOdds + spearOdds)
	{
		buildSpear(rarity);
		return glm::vec2(rarity, SPEAR);
	}
	else if (gunOdds <= result && result < gunOdds + throwableOdds)
	{
		if (!includeThrowables)
		{
			if (result < 33)
			{
				buildSword(rarity);
				return glm::vec2(rarity, SWORD);
			}
			else if (result < 66)
			{
				buildSpear(rarity);
				return glm::vec2(rarity, SPEAR);
			}
			else
			{
				buildGun(rarity);
				return glm::vec2(rarity, GUN);
			}

		}
		else
		{
			buildThrowable(rarity);
			return glm::vec2(rarity, THROWABLE);
		}
	}
	else
	{
		buildGun(rarity);
		return glm::vec2(rarity, GUN);
	}
}

/// <summary>
/// Binds the atlas uniforms of the texture atlas. Also binds the texture.
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="textureAtlas">- Reference to the game's itemAtlas</param>
void Item::bindAtlasUniforms(Shader& shader, Texture& textureAtlas)
{
	// (0,0) = bottom left as an array
	// (3,3) = top Right of the texture atlas
	float xAddition = atlasCoordinates.x * .25;
	float yAddition = atlasCoordinates.y * .25;

	textureAtlas.Bind();
	glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasX"), xAddition);
	glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasY"), yAddition);
}

/// <summary>
/// Sets the atlas uniforms back to 0, so it's not used by other VAOs
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
void Item::resetAtlasUniforms(Shader& shader)
{
	glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasX"), 0);
	glUniform1f(glGetUniformLocation(shader.ID, "uTexAtlasY"), 0);
}

void Item::drawParticles(Shader& shader, Camera& camera)
{
	if (atlasCoordinates.x == LEGENDARY)
	{
		particleSystem.drawParticles(shader, camera);
		particleSystem.iterate(itemPosition + playerPosition, currentAnimationAngle);
	}
}

/// <summary>
/// Starts the attack animation of the weapon
/// </summary>
/// <param name="weaponAngleStart">- The starting weapon angle</param>
/// <param name="Position">- The starting position of the weapon</param>
void Item::attack(float weaponAngleStart, glm::vec3 Position)
{
	animationCount = 0;
	itemPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	currentAnimationAngle = weaponAngleStart;
	playerPosition = Position;

	if (atlasCoordinates.y == SWORD)
	{
		animationEnd = (int)((swordArc * 2) / animationSpeed);
		currentAnimationAngle -= swordArc;
	}
	else if (atlasCoordinates.y == SPEAR)
	{
		
		// Move it along the angle really fast, then the pull back is slow

		//May need to convert from degrees to radians. Not sure yet.
		movementVector.x = cos(glm::radians(weaponAngleStart + 90));
		movementVector.y = sin(glm::radians(weaponAngleStart + 90));

		float distance = sqrt(square(playerPosition.x - (movementVector.x)) + square(playerPosition.y - (movementVector.y)));
		
		//The higher the animation speed, the lower the animation end
		// Meaning that the animation ends sooner when the animation speed is higher

		// The problem is that when we increase the animation speed of the spear, we reduce the distance that the spear travels
		// We need to find a ratio between the animation speed and distance to send the spear

		// Constant is 100 units
		// Variables - Animation Speed, Animation End

		// 100 / animationMid
		animationEnd = 60 / animationSpeed;
		animationMid = animationEnd / 2;

		// how far we want it to stab out before retracting distance/time
		translationSpeed = PLAYER_SIZE / animationMid;
	}
	else //GUN
	{
		particleSystem.displayGunParticles(itemPosition + playerPosition, weaponAngleStart);
		animationEnd = 60 / animationSpeed;
		animationMid = animationEnd / 2;
		translationSpeed = (PLAYER_SIZE / 4) / animationMid;
		m_rotationSpeed = 15.0f / animationMid;
	}
}

/// <summary>
/// Continues the animation of our attack
/// </summary>
/// <param name="Position">- Position of the player</param>
/// <returns>Whether or not the attack has finished</returns>
bool Item::continueAttack(glm::vec3 Position)
{
	if (atlasCoordinates.y == SWORD)
		currentAnimationAngle += animationSpeed;
	else if (atlasCoordinates.y == SPEAR)
	{
		if (animationCount <= animationMid)
			itemPosition += (movementVector * (translationSpeed));
		else
			itemPosition -= (movementVector * (translationSpeed));
	}
	else
	{
		if (animationCount <= animationMid)
		{
			if (m_flipped)
				currentAnimationAngle += m_rotationSpeed;
			else
				currentAnimationAngle -= m_rotationSpeed;
		}
		else
		{
			if (m_flipped)
				currentAnimationAngle -= m_rotationSpeed;
			else
				currentAnimationAngle += m_rotationSpeed;
		}
	}

	playerPosition = Position;
	animationCount += 1;
	if (animationCount >= animationEnd)
		return false;
	else
		return true;
}

/// <summary>
/// Set the atlas coordinates of the item
/// </summary>
/// <param name="coords">- atlasCoordinates of the item</param>
void Item::setAtlasCoordinates(glm::vec2 coords)
{
    Item::atlasCoordinates = coords;
	Item::m_itemType = coords.y;

	if (atlasCoordinates.x == LEGENDARY)
	{
		particleSystem.setup(itemPosition + playerPosition, currentAnimationAngle, m_itemType);
	}
}

/// <summary>
/// Sets the position of the item
/// </summary>
/// <param name="newPosition">- Desired item position</param>
void Item::setItemPosition(glm::vec3 newPosition)
{
	itemPosition = newPosition;
}

/// <summary>
/// Sets the position of the player using the item
/// </summary>
/// <param name="newPosition">- Position of the player</param>
void Item::setPlayerPosition(glm::vec3 newPosition)
{
	playerPosition = newPosition;
}

/// <summary>
/// Sets the layer of the item in terms of being drawn
/// </summary>
/// <param name="layer"></param>
void Item::setItemLayer(float layer)
{
	//TODO: Analyze whether or not we need this item
	itemPosition.z = layer;
}

/// <summary>
/// Sets the angle of the weapon
/// </summary>
/// <param name="angle">- Desired weapon angle</param>
void Item::setWeaponAngle(float angle)
{
	currentAnimationAngle = angle;
}

/// <summary>
/// Sets the type of the weapon
/// </summary>
/// <param name="type">- Weapon type</param>
void Item::setItemType(unsigned int type)
{
	m_itemType = type;
}

/// <summary>
/// Sets whether or not to flip the drawing of the item horizontally
/// </summary>
/// <param name="flipped">- Whether or not the item should be flipped</param>
void Item::setFlipped(bool flipped)
{
	m_flipped = flipped;
}

/// <summary>
/// Sets the damage of the item
/// </summary>
/// <param name="damage">- Desired weapon damage</param>
void Item::setDamage(float damage)
{
	//TODO: LOOK AT REMOVAL
	m_damage = damage;
}

/// <summary>
/// Sets the attack speed of the weapon
/// </summary>
/// <param name="attackSpeed">- Desired weapon attack speed</param>
void Item::setAttackSpeed(float attackSpeed)
{
	//TODO: Look at removal
	animationSpeed = attackSpeed;
}

/// <summary>
/// Returns whether or not the image should be flipped horizonally
/// </summary>
/// <returns></returns>
bool Item::getFlipped()
{
	return m_flipped;
}

/// <summary>
/// Returns the type of the item
/// </summary>
/// <returns></returns>
unsigned int Item::getItemType()
{
	return m_itemType;
}

/// <summary>
/// Returns the itemAtlas coordinates of the weapon
/// </summary>
/// <returns></returns>
glm::vec2 Item::getAtlasCoordinates()
{
	return atlasCoordinates;
}

/// <summary>
/// Returns the position of the player + position of the item
/// </summary>
/// <returns></returns>
glm::vec3 Item::getItemPosition()
{
	return itemPosition + playerPosition;
}

/// <summary>
/// Returns the current angle of the weapon
/// </summary>
/// <returns></returns>
float Item::getWeaponAngle()
{
	return currentAnimationAngle;
}

/// <summary>
/// Returns the damage that the weapon does
/// </summary>
/// <returns></returns>
float Item::getDamage()
{
	return m_damage;
}

/// <summary>
/// Randomly sets the stats of a sword
/// </summary>
/// <param name="rarity">- Rarity of the sword to build</param>
void Item::buildSword(unsigned int rarity)
{
	//Currently .2 is fast attack speed on my laptop. Like really fast
	//TODO: After fps is limited and normalized test good values for the attack speed.
	//TODO: Take a look at item type for possible removal

	setAtlasCoordinates(glm::vec2(rarity, SWORD));

	animationSpeed = (rand() % 100 + 1.0f) / 1000;	//From 0.001 to 0.1
	if (rarity == COMMON)
		animationSpeed += .0025f;
	else if (rarity == RARE)
		animationSpeed += .005f;
	else if (rarity == LEGENDARY)
		animationSpeed += .015f;

	m_damage = (rand() % 100 + 1.0f) / 10; // From 0.1 to 10
	if (rarity == COMMON)
		m_damage += 5.0f;
	else if (rarity == RARE)
		m_damage += 10.0f;
	else if (rarity == LEGENDARY)
		m_damage += 20.0f;
}

/// <summary>
/// Randomly sets the stats of a spear
/// </summary>
/// <param name="rarity">- Rarity of the spear to build</param>
void Item::buildSpear(unsigned int rarity)
{
	setAtlasCoordinates(glm::vec2(rarity, SPEAR));

	animationSpeed = (rand() % 100 + 1.0f) / 1000;	//From 0.001 to 0.1
	if (rarity == COMMON)
		animationSpeed += .0025f;
	else if (rarity == RARE)
		animationSpeed += .005f;
	else if (rarity == LEGENDARY)
		animationSpeed += .015f;

	m_damage = (rand() % 100 + 1.0f) / 10; // From 0.1 to 10
	if (rarity == COMMON)
		m_damage += 2.0f;
	else if (rarity == RARE)
		m_damage += 5.0f;
	else if (rarity == LEGENDARY)
		m_damage += 10.0f;
}

/// <summary>
/// Randomly sets the stats of a throwable
/// </summary>
/// <param name="rarity">- Rarity of the throwable to build</param>
void Item::buildThrowable(unsigned int rarity)
{
	setAtlasCoordinates(glm::vec2(rarity, THROWABLE));

	m_damage = (rand() % 100 + 1.0f) / 10; // From 0.1 to 10
	if (rarity == COMMON)
		m_damage += 5.0f;
	else if (rarity == RARE)
		m_damage += 15.0f;
	else if (rarity == LEGENDARY)
		m_damage += 30.0f;
}

/// <summary>
/// Randomly sets the stats of a gun
/// </summary>
/// <param name="rarity">- Rarity of the gun to build</param>
void Item::buildGun(unsigned int rarity)
{
	setAtlasCoordinates(glm::vec2(rarity, GUN));

	animationSpeed = (rand() % 100 + 1.0f) / 1000;	//From 0.001 to 0.1

	if (rarity == RARE)
		animationSpeed += .005f;
	else if (rarity == LEGENDARY)
		animationSpeed += .045f;

	m_damage = (rand() % 100 + 1.0f) / 10; // From 0.1 to 10
	if (rarity == COMMON)
		m_damage += 20.0f;
	else if (rarity == RARE)
		m_damage += 10.0f;
	else if (rarity == LEGENDARY)
		m_damage += 5.0f;
}