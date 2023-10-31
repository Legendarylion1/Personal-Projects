#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "EBO.h"
#include <unordered_map>

const static unsigned int LEFT_ALIGN = 0;
const static unsigned int CENTER_ALIGN = 1;
const static unsigned int RIGHT_ALIGN = 2;

const static unsigned int WHITE = 0;
const static unsigned int BLACK = 1;


const static unsigned int TEXTXPOS = 0;
const static unsigned int TEXTYPOS = 1;
const static unsigned int HPADDING = 2;
const static unsigned int VPADDING = 3;


// {Char: {texXCoord, texYCoord, HorizontalPadding, VerticalPadding}}
static std::unordered_map<char, std::vector<float> > fontMap = {
	{'1',std::vector<float>{0.0f, 7.0f, -0.3f, 0.0f}},
	{'2',std::vector<float>{1.0f, 7.0f, -0.3f, 0.0f}},
	{'3',std::vector<float>{2.0f, 7.0f, -0.3f, 0.0f}},
	{'4',std::vector<float>{3.0f, 7.0f, -0.3f, 0.0f}},
	{'5',std::vector<float>{4.0f, 7.0f, -0.3f, 0.0f}},
	{'6',std::vector<float>{5.0f, 7.0f, -0.3f, 0.0f}},
	{'7',std::vector<float>{6.0f, 7.0f, -0.3f, 0.0f}},
	{'8',std::vector<float>{7.0f, 7.0f, -0.3f, 0.0f}},
	{'9',std::vector<float>{0.0f, 6.0f, -0.3f, 0.0f}},
	{'0',std::vector<float>{1.0f, 6.0f, -0.3f, 0.0f}},
	{'A',std::vector<float>{2.0f, 6.0f, -0.3f, 0.0f}},
	{'B',std::vector<float>{3.0f, 6.0f, -0.3f, 0.0f}},
	{'C',std::vector<float>{4.0f, 6.0f, -0.3f, 0.0f}},
	{'D',std::vector<float>{5.0f, 6.0f, -0.3f, 0.0f}},
	{'E',std::vector<float>{6.0f, 6.0f, -0.3f, 0.0f}},
	{'F',std::vector<float>{7.0f, 6.0f, -0.3f, 0.0f}},
	{'G',std::vector<float>{0.0f, 5.0f, -0.3f, 0.0f}},
	{'H',std::vector<float>{1.0f, 5.0f, -0.3f, 0.0f}},
	{'I',std::vector<float>{2.0f, 5.0f, -0.3f, 0.0f}},
	{'J',std::vector<float>{3.0f, 5.0f, -0.3f, 0.0f}},
	{'K',std::vector<float>{4.0f, 5.0f, -0.3f, 0.0f}},
	{'L',std::vector<float>{5.0f, 5.0f, -0.3f, 0.0f}},
	{'M',std::vector<float>{6.0f, 5.0f, -0.3f, 0.0f}},
	{'N',std::vector<float>{7.0f, 5.0f, -0.3f, 0.0f}},
	{'O',std::vector<float>{0.0f, 4.0f, -0.3f, 0.0f}},
	{'P',std::vector<float>{1.0f, 4.0f, -0.3f, 0.0f}},
	{'Q',std::vector<float>{2.0f, 4.0f, -0.3f, 0.0f}},
	{'R',std::vector<float>{3.0f, 4.0f, -0.3f, 0.0f}},
	{'S',std::vector<float>{4.0f, 4.0f, -0.3f, 0.0f}},
	{'T',std::vector<float>{5.0f, 4.0f, -0.3f, 0.0f}},
	{'U',std::vector<float>{6.0f, 4.0f, -0.3f, 0.0f}},
	{'V',std::vector<float>{7.0f, 4.0f, -0.3f, 0.0f}},
	{'W',std::vector<float>{0.0f, 3.0f, -0.3f, 0.0f}},
	{'X',std::vector<float>{1.0f, 3.0f, -0.3f, 0.0f}},
	{'Y',std::vector<float>{2.0f, 3.0f, -0.3f, 0.0f}},
	{'Z',std::vector<float>{3.0f, 3.0f, -0.3f, 0.0f}},
	{'a',std::vector<float>{4.0f, 3.0f, -0.3f, 0.0f}},
	{'b',std::vector<float>{5.0f, 3.0f, -0.3f, 0.0f}},
	{'c',std::vector<float>{6.0f, 3.0f, -0.3f, 0.0f}},
	{'d',std::vector<float>{7.0f, 3.0f, -0.3f, 0.0f}},
	{'e',std::vector<float>{0.0f, 2.0f, -0.2f, 0.0f}},
	{'f',std::vector<float>{1.0f, 2.0f, -0.3f, 0.0f}},
	{'g',std::vector<float>{2.0f, 2.0f, -0.3f, 0.0f}},
	{'h',std::vector<float>{3.0f, 2.0f, -0.3f, 0.0f}},
	{'i',std::vector<float>{4.0f, 2.0f, -0.4f, 0.0f}},
	{'j',std::vector<float>{5.0f, 2.0f, -0.3f, 0.0f}},
	{'k',std::vector<float>{6.0f, 2.0f, -0.3f, 0.0f}},
	{'l',std::vector<float>{7.0f, 2.0f, -0.3f, 0.0f}},
	{'m',std::vector<float>{0.0f, 1.0f, -0.3f, 0.0f}},
	{'n',std::vector<float>{1.0f, 1.0f, -0.3f, 0.0f}},
	{'o',std::vector<float>{2.0f, 1.0f, -0.3f, 0.0f}},
	{'p',std::vector<float>{3.0f, 1.0f, -0.3f, 0.0f}},
	{'q',std::vector<float>{4.0f, 1.0f, -0.3f, 0.0f}},
	{'r',std::vector<float>{5.0f, 1.0f, -0.3f, 0.0f}},
	{'s',std::vector<float>{6.0f, 1.0f, -0.3f, 0.0f}},
	{'t',std::vector<float>{7.0f, 1.0f, -0.3f, 0.0f}},
	{'u',std::vector<float>{0.0f, 0.0f, -0.3f, 0.0f}},
	{'v',std::vector<float>{1.0f, 0.0f, -0.3f, 0.0f}},
	{'w',std::vector<float>{2.0f, 0.0f, -0.3f, 0.0f}},
	{'x',std::vector<float>{3.0f, 0.0f, -0.3f, 0.0f}},
	{'y',std::vector<float>{4.0f, 0.0f, -0.3f, 0.0f}},
	{'z',std::vector<float>{5.0f, 0.0f, -0.3f, 0.0f}},
	{'-',std::vector<float>{6.0f, 0.0f, -0.3f, 0.0f}},
	{',',std::vector<float>{7.0f, 0.0f, -0.3f, 0.0f}},
};

class TextRenderer
{
public:
	TextRenderer(Shader* shader, float ScreenWidth, float ScreenHeight);
	TextRenderer();
	~TextRenderer();

	void renderText(std::string, float x, float y, unsigned int fontSize, unsigned int alignment, unsigned int color);
private:
	Shader* m_shader = nullptr;
	Texture* m_characterAtlas[2] = {nullptr};

	float m_width = 0.0f;
	float m_height = 0.0f;
	float atlasSquareSize = 0.125f;

	void buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int characterCount, unsigned int maxVertices, std::string text, float alignment);
	void buildIndices(GLuint* indices, unsigned int characterCount);
	void addSpace(GLfloat* vertices, float xPos, float yPos, unsigned int fontSize, int i);
	float findAlignment(unsigned int alignment, std::string text, unsigned int fontSize);
};