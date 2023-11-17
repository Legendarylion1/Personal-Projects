#pragma once

#include <vector>

#include "TorinDefinitions.h"
#include "shaderClass.h"
#include "Camera.h"
#include "VAO.h"
#include "EBO.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void setup(glm::vec3 Position, float weaponAngle, unsigned int weaponType);
	void shutdown();

	void iterate(glm::vec3 Position, float weaponAngle);
	void drawParticles(Shader& shader, Camera& camera);

	void displayGunParticles(glm::vec3 Position, float weaponAngle);

private:
	unsigned int m_weaponType = 0;

	struct Particle
	{
		glm::vec3 position;
		glm::vec2 movementVector;

		glm::vec3 color;

		unsigned int lifeTime;
		unsigned int elapsedTime;

		unsigned int scale;
	};

	void buildVertices(GLfloat* vertices, unsigned int particleCount);
	void buildIndices(GLuint* indices, unsigned int particleCount);

	void iterateSword(glm::vec3 Position, float weaponAngle);
	void iterateSpear(glm::vec3 Position, float weaponAngle);
	void iterateThrowable(glm::vec3 Position, float weaponAngle);
	void iterateGun(glm::vec3 Position, float weaponAngle);

	void setupSword(glm::vec3 Position, float weaponAngle);
	void setupSpear(glm::vec3 Position, float weaponAngle);
	void setupThrowable(glm::vec3 Position, float weaponAngle);
	void setupGun(glm::vec3 Position, float weaponAngle);

	void assignSwordMetrics(Particle& particle, glm::vec3 Position, glm::vec2 movementVector);
	void assignSpearMetrics(Particle& particle, glm::vec3 Position, glm::vec2 movementVector, float weaponAngle);
	void assignThrowableMetrics(Particle& particle, glm::vec3 Position, float weaponAngle);
	void assignGunMetrics(Particle& particle, glm::vec3 Position, float weaponAngle);

	std::vector<Particle> particleVector;
};