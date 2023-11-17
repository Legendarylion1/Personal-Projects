#pragma once
#include "shaderClass.h"
#include "Camera.h"
#include "Texture.h"
#include "VAO.h"
#include "EBO.h"

class TextRenderer
{
public:
	TextRenderer(Shader& shader, Camera& camera);

	void renderText(const char* text, float x, float y, unsigned int fontSize, unsigned int fontSpacing);
private:
	Shader m_shader;
	Camera m_camera;
	Texture m_characterAtlas;

	unsigned int lengthOf(const char* text);
	void buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int fontSpacing, unsigned int characterCount, unsigned int maxVertices, const char* text);
	void buildIndices(GLuint *indices, unsigned int characterCount);
	glm::vec2 findCharAtlas(char character);
};