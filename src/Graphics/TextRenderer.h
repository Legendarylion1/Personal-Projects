#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/ShaderClass.h"
#include "Texture/Texture.h"
#include "Buffers/VAO.h"
#include "Buffers/EBO.h"
#include <unordered_map>
#include "Colors.h"
#include "TextData.h"

class TextRenderer
{
public:
	TextRenderer(Shader* shader, float screenWidth, float screenHeight);	//TODO: Update Screen width and height
	TextRenderer();
	~TextRenderer();

	void setScreenSize(float screenWidth, float screenHeight)
	{
		m_width = screenWidth;
		m_height = screenHeight;
	};

	void renderText(std::string, float x, float y, unsigned int fontSize, Alignment alignment, Color color);

	float getFontSize(std::string text, float widthPercent, float heightPercent);
private:
	Shader* m_shader = nullptr;

	float m_width = 0.0f;
	float m_height = 0.0f;
	float atlasSquareSize = 0.125f;

	void buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int characterCount, unsigned int maxVertices, std::string text, float alignment);
	void buildIndices(GLuint* indices, unsigned int characterCount);
	void addSpace(GLfloat* vertices, float xPos, float yPos, unsigned int fontSize, int i);
	float findAlignment(Alignment alignment, std::string text, unsigned int fontSize);

private:

	void buildCharacter(GLfloat* vertices, int i, float* xPos, float yPos, unsigned int fontSize, float leftShift, float rightShift, glm::vec2 bottomLeftAtlas);


private:

	std::unordered_map<Color, Texture*> m_characterAtlas = { 
		{Color::WHITE , nullptr},
		{Color::BLACK , nullptr} 
	};

	std::unordered_map<char, TextPosition> m_fontMap = {
	{'1', {0.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'2', {1.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'3', {2.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'4', {3.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'5', {4.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'6', {5.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'7', {6.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'8', {7.0f,  7.0f, (3.0f / 10.0f), 0.0f}},
	{'9', {0.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'0', {1.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'A', {2.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'B', {3.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'C', {4.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'D', {5.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'E', {6.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'F', {7.0f,  6.0f, (3.0f / 10.0f), 0.0f}},
	{'G', {0.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'H', {1.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'I', {2.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'J', {3.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'K', {4.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'L', {5.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'M', {6.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'N', {7.0f,  5.0f, (3.0f / 10.0f), 0.0f}},
	{'O', {0.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'P', {1.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'Q', {2.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'R', {3.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'S', {4.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'T', {5.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'U', {6.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'V', {7.0f,  4.0f, (3.0f / 10.0f), 0.0f}},
	{'W', {0.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'X', {1.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'Y', {2.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'Z', {3.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'a', {4.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'b', {5.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'c', {6.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'d', {7.0f,  3.0f, (3.0f / 10.0f), 0.0f}},
	{'e', {0.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'f', {1.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'g', {2.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'h', {3.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'i', {4.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'j', {5.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'k', {6.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'l', {7.0f,  2.0f, (3.0f / 10.0f), 0.0f}},
	{'m', {0.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'n', {1.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'o', {2.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'p', {3.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'q', {4.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'r', {5.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'s', {6.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'t', {7.0f,  1.0f, (3.0f / 10.0f), 0.0f}},
	{'u', {0.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{'v', {1.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{'w', {2.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{'x', {3.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{'y', {4.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{'z', {5.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{':', {6.0f,  0.0f, (3.0f / 10.0f), 0.0f}},
	{'\'',{7.0f, 0.0f, (3.0f / 10.0f), 0.0f}},
	};

};