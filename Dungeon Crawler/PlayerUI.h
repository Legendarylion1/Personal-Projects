#pragma once

#include "Camera.h"
#include "Texture.h"
#include "shaderClass.h"
#include "Item.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <vector>

class PlayerUI
{
public:
	PlayerUI();
	~PlayerUI();
	void initUI();
	void drawUI(Shader& shader, Camera& camera,float maxHealth, float currentHealth, unsigned int itemIndex, glm::vec3 Position, Item item[3], Texture& itemTexture, bool itemUsage[3]);
private:
	bool UIinitialized = false;
	glm::vec3 itemIndexPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	std::vector<VAO> vaoVector;
	std::vector<VBO> vboVector;
	std::vector<EBO> eboVector;
	
	void healthBarPosition(Shader& shader, float maxHealth, float currentHealth);
	void drawItems(Shader& shader, Camera& camera, Item item[3], glm::vec3 Position, Texture& itemTexture, bool itemUsage[3]);
	glm::vec3 itemHighlightLocation(unsigned int location, glm::vec3 Position);
};