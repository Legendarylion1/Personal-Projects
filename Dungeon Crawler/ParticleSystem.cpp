#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	shutdown();
}

void ParticleSystem::setup(glm::vec3 Position, float weaponAngle, unsigned int weaponType)
{
	m_weaponType = weaponType;

	if (weaponType == SWORD)
		setupSword(Position, weaponAngle);
	else if (weaponType == SPEAR)
		setupSpear(Position, weaponAngle);
	else if (weaponType == THROWABLE)
		setupThrowable(Position, weaponAngle);
	else if (weaponType == GUN)
		setupGun(Position, weaponAngle);
}

void ParticleSystem::shutdown()
{
	particleVector.clear();
}

void ParticleSystem::iterate(glm::vec3 Position, float weaponAngle)
{

	if (m_weaponType == SWORD)
		iterateSword(Position, weaponAngle);
	else if (m_weaponType == SPEAR)
		iterateSpear(Position, weaponAngle);
	else if (m_weaponType == GUN)
		iterateGun(Position, weaponAngle);
	else
		iterateThrowable(Position, weaponAngle);
}

void ParticleSystem::drawParticles(Shader& shader, Camera& camera)
{
	const unsigned int maxQuads = 1000;
	const unsigned int maxVerticeCount = maxQuads * 32;
	const unsigned int maxIndiceCount = maxQuads * 6;

	GLfloat vertices[maxVerticeCount]{};
	GLuint indices[maxIndiceCount]{};

	buildVertices(vertices, maxQuads);
	buildIndices(indices, maxIndiceCount);


	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO1.Bind();
	camera.Matrix(shader, glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, maxIndiceCount, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();

	EBO1.Delete();
	VBO1.Delete();
	VAO1.Delete();
}

void ParticleSystem::displayGunParticles(glm::vec3 Position, float weaponAngle)
{
	for (int i = 0; i < particleVector.size(); i++)
	{
		if (particleVector.at(i).position.z == -200.0f)
		{
			assignGunMetrics(particleVector.at(i), Position, weaponAngle);
		}
	}
}

void ParticleSystem::buildVertices(GLfloat* vertices, unsigned int particleCount)
{
	float scale = 1.0f;
	float particleSize = 3.0f;
	for (int i = 0; i < particleCount; i++)
	{ 
		Particle& particleStats = particleVector.at(i);

		vertices[ 24 * i] =		 (particleStats.position.x) * (scale - particleStats.scale);
		vertices[(24 * i) + 1] = (particleStats.position.y) * (scale - particleStats.scale);
		vertices[(24 * i) + 2] = particleStats.position.z;
		vertices[(24 * i) + 3] = particleStats.color.x;
		vertices[(24 * i) + 4] = particleStats.color.y;
		vertices[(24 * i) + 5] = particleStats.color.z;

		// Top Left
		vertices[(24 * i) + 6] =  (particleStats.position.x) * (scale - particleStats.scale);
		vertices[(24 * i) + 7] =  (particleStats.position.y + particleSize) * (scale - particleStats.scale);
		vertices[(24 * i) + 8] =  particleStats.position.z;
		vertices[(24 * i) + 9] =  particleStats.color.x;
		vertices[(24 * i) + 10] = particleStats.color.y;
		vertices[(24 * i) + 11] = particleStats.color.z;
		// Top Right
		vertices[(24 * i) + 12] = (particleStats.position.x + particleSize) * (scale - particleStats.scale);
		vertices[(24 * i) + 13] = (particleStats.position.y + particleSize) * (scale - particleStats.scale);
		vertices[(24 * i) + 14] = particleStats.position.z;
		vertices[(24 * i) + 15] = particleStats.color.x;
		vertices[(24 * i) + 16] = particleStats.color.y;
		vertices[(24 * i) + 17] = particleStats.color.z;

		// Bottom Right
		vertices[(24 * i) + 18] = (particleStats.position.x + particleSize) * (scale - particleStats.scale);
		vertices[(24 * i) + 19] = (particleStats.position.y) * (scale - particleStats.scale);
		vertices[(24 * i) + 20] = particleStats.position.z;
		vertices[(24 * i) + 21] = particleStats.color.x;
		vertices[(24 * i) + 22] = particleStats.color.y;
		vertices[(24 * i) + 23] = particleStats.color.z;
	}
}

void ParticleSystem::buildIndices(GLuint* indices, unsigned int particleCount)
{
	unsigned int offset = 0;
	for (int i = 0; i < particleCount; i += 6)
	{
		indices[i + 0] = offset;
		indices[i + 1] = offset + 2;
		indices[i + 2] = offset + 1;
		indices[i + 3] = offset;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 2;

		offset += 4;
	}
}

void ParticleSystem::iterateSword(glm::vec3 Position, float weaponAngle)
{
	//TODO: Maybe get rid of temp position
	//TODO: Retest sword from 1 instead of i error
	for (int i = 0; i < particleVector.size(); i++)
	{
		particleVector.at(i).position += glm::vec3(particleVector.at(i).movementVector, 0.0f);

		if (particleVector.at(i).elapsedTime > particleVector.at(i).lifeTime)
		{
			glm::vec2 movementVector = { 0.0f,0.0f };

			if (weaponAngle == 0)
				weaponAngle += 1;
			movementVector.x = cos(glm::radians(weaponAngle + 90));
			movementVector.y = sin(glm::radians(weaponAngle + 90));

			assignSwordMetrics(particleVector.at(i), Position, movementVector);
		}

		particleVector.at(i).elapsedTime += 1;
		particleVector.at(i).color.y += 0.0020f;
		particleVector.at(i).color.z += 0.0010f;
	}
}

void ParticleSystem::iterateSpear(glm::vec3 Position, float weaponAngle)
{
	//TODO: Retest spear cuz I had an error
	unsigned int respawnDelay = 500;
	for (int i = 0; i < particleVector.size(); i++)
	{
		particleVector.at(i).position += glm::vec3(particleVector.at(i).movementVector, 0.0f);

		if (particleVector.at(i).elapsedTime > particleVector.at(i).lifeTime && particleVector.at(i).elapsedTime - particleVector.at(i).lifeTime > respawnDelay)
		{
			glm::vec2 movementVector = { 0.0f,0.0f };

			if (weaponAngle == 0)
				weaponAngle += 1;
			movementVector.x = cos(glm::radians(weaponAngle + 90));
			movementVector.y = sin(glm::radians(weaponAngle + 90));

			assignSpearMetrics(particleVector.at(i), Position, movementVector, weaponAngle);
		}

		particleVector.at(i).elapsedTime += 1;
		particleVector.at(i).color.y += 0.0015f;
	}
}

void ParticleSystem::iterateThrowable(glm::vec3 Position, float weaponAngle)
{
	unsigned int respawnDelay = 500;
	for (int i = 0; i < particleVector.size(); i++)
	{
		particleVector.at(i).position += glm::vec3(particleVector.at(i).movementVector, 0.0f);

		if (particleVector.at(i).elapsedTime > particleVector.at(i).lifeTime && particleVector.at(i).elapsedTime - particleVector.at(i).lifeTime > respawnDelay)
		{
			glm::vec2 movementVector = { 0.0f,0.0f };

			if (weaponAngle == 0)
				weaponAngle += 1;

			assignThrowableMetrics(particleVector.at(i), Position, weaponAngle);
		}

		particleVector.at(i).elapsedTime += 1;
		particleVector.at(i).color.y += 0.0001f;
		particleVector.at(i).color.z += 0.0040f;
	}
}

void ParticleSystem::iterateGun(glm::vec3 Position, float weaponAngle)
{
	for (int i = 0; i < particleVector.size(); i++)
	{
		if (particleVector.at(i).elapsedTime > particleVector.at(i).lifeTime)
		{
			particleVector.at(i).position.z = -200.0f;

			continue;
		}

		particleVector.at(i).position += glm::vec3(particleVector.at(i).movementVector, 0.0f);

		particleVector.at(i).elapsedTime += 1;
		particleVector.at(i).color.z += 0.003f;
	}
}

void ParticleSystem::setupSword(glm::vec3 Position, float weaponAngle)
{
	glm::vec2 movementVector = {0.0f,0.0f};

	if (weaponAngle == 0)
		weaponAngle += 1;
	movementVector.x = cos(glm::radians(weaponAngle + 90));
	movementVector.y = sin(glm::radians(weaponAngle + 90));
	
	for (int i = 0; i < 1000; i++)
	{
		Particle newParticle{};
		newParticle.lifeTime = 1000;
		newParticle.scale = 0;

		assignSwordMetrics(newParticle, Position, movementVector);
		particleVector.push_back(newParticle);
	}
}

void ParticleSystem::setupSpear(glm::vec3 Position, float weaponAngle)
{
	glm::vec2 movementVector = { 0.0f,0.0f };

	if (weaponAngle == 0)
		weaponAngle += 1;
	movementVector.x = cos(glm::radians(weaponAngle + 90));
	movementVector.y = sin(glm::radians(weaponAngle + 90));

	for (int i = 0; i < 1000; i++)
	{
		Particle newParticle{};
		newParticle.lifeTime = 100;
		newParticle.scale = 0;

		assignSpearMetrics(newParticle, Position, movementVector, weaponAngle);
		particleVector.push_back(newParticle);
	}
}

void ParticleSystem::setupThrowable(glm::vec3 Position, float weaponAngle)
{
	glm::vec2 movementVector = { 0.0f,0.0f };

	if (weaponAngle == 0)
		weaponAngle += 1;
	movementVector.x = cos(glm::radians(weaponAngle + 90));
	movementVector.y = sin(glm::radians(weaponAngle + 90));

	for (int i = 0; i < 1000; i++)
	{
		Particle newParticle{};
		newParticle.lifeTime = 100;
		newParticle.scale = 0;

		assignThrowableMetrics(newParticle, Position, weaponAngle);
		particleVector.push_back(newParticle);
	}
}

void ParticleSystem::setupGun(glm::vec3 Position, float weaponAngle)
{
	glm::vec2 movementVector = { 0.0f,0.0f };

	if (weaponAngle == 0)
		weaponAngle += 1;

	for (int i = 0; i < 1000; i++)
	{
		Particle newParticle{};
		newParticle.lifeTime = 250;
		newParticle.scale = 0;

		assignGunMetrics(newParticle, Position, weaponAngle);
		newParticle.elapsedTime = newParticle.lifeTime;
		newParticle.position.z = -200.0f;

		particleVector.push_back(newParticle);
	}
}

void ParticleSystem::assignSwordMetrics(Particle& particle, glm::vec3 Position, glm::vec2 movementVector)
{

	int maxDistance = 100000;

	if (movementVector.x != 0)
	{
		float result = (PLAYER_SIZE / 2) / abs(movementVector.x);
		if (result < maxDistance)
			maxDistance = (int)result;
	}
	if (movementVector.y != 0)
	{
		float result = (PLAYER_SIZE / 2) / abs(movementVector.y);
		if (result < maxDistance)
			maxDistance = (int)result;
	}

	int distanceMultiplier = rand() % maxDistance;
	particle.position = glm::vec3(Position.x + (movementVector.x * distanceMultiplier), Position.y + (movementVector.y * distanceMultiplier), LAYER_SEVEN + 1.0f);

	float xMovement = (rand() % 100) / 1000.0f;
	float yMovement = (rand() % 100) / 1000.0f;


	if (movementVector.x < 0)
		xMovement *= -1;
	if (movementVector.y < 0)
		yMovement *= -1;

	particle.movementVector = glm::vec2(xMovement, yMovement);


	particle.position.z += LAYER_SEVEN;
	particle.color = glm::vec3(1.0f, 0.0f, 0.0f);
	particle.elapsedTime = rand() % particle.lifeTime;
}

void ParticleSystem::assignSpearMetrics(Particle& particle, glm::vec3 Position, glm::vec2 movementVector, float weaponAngle)
{
	int location = (rand() % 3 ) + 1;//rand() % 3;

	// 1 - Central Pillar
	// 2 - Left Pillar
	// 3 - Right Pillar
	if (location == 1)
	{
		int distanceMultiplier = (rand() % 25) - 5;
		particle.position = glm::vec3(Position.x + (movementVector.x * ((PLAYER_SIZE / 3) + distanceMultiplier)), Position.y + (movementVector.y * ((PLAYER_SIZE / 3) + distanceMultiplier)), LAYER_SEVEN + 1.0f);
	}
	else if (location == 2)
	{
		int distanceMultiplier = (rand() % 20);
		particle.position = glm::vec3(Position.x + (cos(glm::radians(weaponAngle + 100)) * ((PLAYER_SIZE / 3) + distanceMultiplier)), Position.y + (sin(glm::radians(weaponAngle + 100)) * ((PLAYER_SIZE / 3) + distanceMultiplier)), LAYER_SEVEN + 1.0f);
	}
	else if (location == 3)
	{
		int distanceMultiplier = (rand() % 20);
		particle.position = glm::vec3(Position.x + (cos(glm::radians(weaponAngle + 80)) * ((PLAYER_SIZE / 3) + distanceMultiplier)), Position.y + (sin(glm::radians(weaponAngle + 80)) * ((PLAYER_SIZE / 3) + distanceMultiplier)), LAYER_SEVEN + 1.0f);
	}

	particle.movementVector = glm::vec2(0.0f, 0.0f);


	particle.position.z += LAYER_SEVEN;
	particle.color = glm::vec3(0.0f, 0.0f, 1.0f);
	particle.elapsedTime = rand() % particle.lifeTime;
}

void ParticleSystem::assignThrowableMetrics(Particle& particle, glm::vec3 Position, float weaponAngle)
{
	int location = rand() % 100;

	if (location == 0)
	{
		int distanceMultiplier = (rand() % 40) - 20;
		int sparkleOffset = (rand() % 60) - 30;
		particle.position = glm::vec3(Position.x + (cos(glm::radians(weaponAngle + 90 + sparkleOffset)) * ((PLAYER_SIZE / 3) + distanceMultiplier)), Position.y + (sin(glm::radians(weaponAngle + 90 + sparkleOffset)) * ((PLAYER_SIZE / 3) + distanceMultiplier)), LAYER_SEVEN + 1.0f);
	}
	else if (location < 50)
	{
		//on left side of axe static
		particle.position = glm::vec3(Position.x + (cos(glm::radians(weaponAngle + 120)) * ((PLAYER_SIZE / 3))), Position.y + (sin(glm::radians(weaponAngle + 100)) * ((PLAYER_SIZE / 3))), LAYER_SEVEN + 1.0f);
	}
	else
	{
		//on right side of axe static
		particle.position = glm::vec3(Position.x + (cos(glm::radians(weaponAngle + 60)) * ((PLAYER_SIZE / 3))), Position.y + (sin(glm::radians(weaponAngle + 80)) * ((PLAYER_SIZE / 3))), LAYER_SEVEN + 1.0f);
	}

	particle.movementVector = glm::vec2(0.0f, 0.0f);

	particle.position.z += LAYER_SEVEN;
	particle.color = glm::vec3(1.0f, 0.85f, 0.0f);
	particle.elapsedTime = rand() % particle.lifeTime;
}

void ParticleSystem::assignGunMetrics(Particle& particle, glm::vec3 Position, float weaponAngle)
{
	//TODO: Change all assigns to only use weaponAngle
	float barrelPosition = (rand() % 10) - 5;
	particle.position = glm::vec3(Position.x + (cos(glm::radians(weaponAngle + 90 + barrelPosition)) * (PLAYER_SIZE / 3)), Position.y + (sin(glm::radians(weaponAngle + 90 + barrelPosition)) * (PLAYER_SIZE / 3)), LAYER_SEVEN + 1.0f);

	float testX = (rand() % 40) - 20;
	float testY = (rand() % 40) - 20;

	float xIntensity = ((rand() % 20) + 10) / 10.0f;
	float yIntensity = ((rand() % 20) + 10) / 10.0f;

	float xMovement = cos(glm::radians(weaponAngle + 90 + testX)) / 10;
	float yMovement = sin(glm::radians(weaponAngle + 90 + testY)) / 10;


	// (PI * 2) * 1000 = 6283
	//float testX = ((rand() % 3141) / 1000.0f) - 1.570796;
	//float testY = ((rand() % 3141) / 1000.0f) - 1.570796;
	//
	//float xMovement = -cos(weaponAngle + 90 + testX) / 10;
	//float yMovement = -sin(weaponAngle + 90 + testY) / 10;

	//if (cos(glm::radians(weaponAngle + 90)) < 0)
	//	xMovement *= -1;
	//if (sin(glm::radians(weaponAngle + 90)) < 0)
	//	yMovement *= -1;

	particle.movementVector = glm::vec2(xMovement * xIntensity, yMovement * yIntensity);


	particle.position.z += LAYER_SEVEN;
	particle.color = glm::vec3(1.0f,1.0f,0.0f);
	particle.elapsedTime = rand() % particle.lifeTime;
}