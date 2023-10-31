#include "TextRenderer.h"

TextRenderer::TextRenderer(Shader* shader, float ScreenWidth, float ScreenHeight) :
	m_shader(shader)
{
	m_characterAtlas[WHITE] = new Texture("Images/alphaNumerics.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterAtlas[WHITE]->texUnit(*m_shader, "tex0", 0);

	m_characterAtlas[BLACK] = new Texture("Images/alphaNumericsBlack.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterAtlas[BLACK]->texUnit(*m_shader, "tex0", 0);

	m_width = ScreenWidth;
	m_height = ScreenHeight;
}

TextRenderer::TextRenderer()
{
}

TextRenderer::~TextRenderer()
{
	//delete m_characterAtlas;
}

void TextRenderer::renderText(std::string text, float x, float y, unsigned int fontSize, unsigned int alignment, unsigned int color)
{
	// TODO: Handle our limit special Characters
	// TODO: Make it so that if we need more characters than 100, then it flushes early and draws the remaining characters

	unsigned int characterCount = text.size();

	const unsigned int MAX_QUADS = 100;
	const unsigned int MAX_VERTICES = MAX_QUADS * 32;
	const unsigned int MAX_INDICES = MAX_QUADS * 6;



	GLfloat vertices[MAX_VERTICES]{};
	GLuint indices[MAX_INDICES]{};

	buildIndices(indices, MAX_INDICES);
	buildVertices(vertices, x, y, fontSize, characterCount, MAX_VERTICES, text, findAlignment(alignment, text, fontSize));

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	m_characterAtlas[color]->Bind();
	VAO1.Bind();

	glm::mat4 proj = glm::ortho(0.0f, m_width, 0.0f, m_height, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj));

	glDrawElements(GL_TRIANGLES, 6 * characterCount, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();
	m_characterAtlas[color]->Unbind();

	EBO1.Delete();
	VBO1.Delete();
	VAO1.Delete();
}

void TextRenderer::buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int characterCount, unsigned int maxVertices, std::string text, float alignment)
{
	// Font size is the width and height of the quad
	// If Odd character Count we center Around the middle value
	// If Even character Count we center around the middle of the spacing between the characters


	// Step 1. Find the far left
	// Step 2. Build up the vertices
	// Step 2.5		Find the positions of the characters in the atlas
	// Step 3  Return



	// Step 1
	float xPos = x + alignment;
	float yPos = y;


	// Step 2

	for (int i = 0; i < characterCount; i++)
	{

		glm::vec2 bottomLeftAtlas;

		//Step 2.5
		if (text.at(i) == ' ')
		{
			addSpace(vertices, xPos, yPos, fontSize, i);
			xPos += fontSize;
			continue;
		}
		bottomLeftAtlas = glm::vec2(fontMap[text.at(i)][TEXTXPOS] * 0.125f, fontMap[text.at(i)][TEXTYPOS] * 0.125);

		//quadBufferPtr->Position = { xPos, yPos, LAYER_FIVE };
		//quadBufferPtr->Color = { 0.0f,0.0f,0.0f };
		//quadBufferPtr->TexCoords = {bottomLeftAtlas.x,bottomLeftAtlas.y};
		//quadBufferPtr++;


		// Bottom Left
		vertices[32 * i] = xPos + (fontMap[text.at(i)][HPADDING] * fontSize);
		vertices[(32 * i) + 1] = yPos + (fontMap[text.at(i)][VPADDING] * fontSize);
		vertices[(32 * i) + 2] = 0.0f;
		vertices[(32 * i) + 3] = 0.0f;
		vertices[(32 * i) + 4] = 0.0f;
		vertices[(32 * i) + 5] = 0.0f;
		vertices[(32 * i) + 6] = bottomLeftAtlas.x;
		vertices[(32 * i) + 7] = bottomLeftAtlas.y;

		// Top Left
		vertices[(32 * i) + 8] = xPos + (fontMap[text.at(i)][HPADDING] * fontSize);
		vertices[(32 * i) + 9] = yPos + fontSize + (fontMap[text.at(i)][VPADDING] * fontSize);
		vertices[(32 * i) + 10] = 0.0f;
		vertices[(32 * i) + 11] = 0.0f;
		vertices[(32 * i) + 12] = 0.0f;
		vertices[(32 * i) + 13] = 0.0f;
		vertices[(32 * i) + 14] = bottomLeftAtlas.x;
		vertices[(32 * i) + 15] = bottomLeftAtlas.y + atlasSquareSize;

		// Top Right
		vertices[(32 * i) + 16] = xPos + fontSize + (fontMap[text.at(i)][HPADDING] * fontSize);
		vertices[(32 * i) + 17] = yPos + fontSize + (fontMap[text.at(i)][VPADDING] * fontSize);
		vertices[(32 * i) + 18] = 0.0f;
		vertices[(32 * i) + 19] = 0.0f;
		vertices[(32 * i) + 20] = 0.0f;
		vertices[(32 * i) + 21] = 0.0f;
		vertices[(32 * i) + 22] = bottomLeftAtlas.x + atlasSquareSize;
		vertices[(32 * i) + 23] = bottomLeftAtlas.y + atlasSquareSize;

		// Bottom Right
		vertices[(32 * i) + 24] = xPos + fontSize + (fontMap[text.at(i)][HPADDING] * fontSize);
		vertices[(32 * i) + 25] = yPos + (fontMap[text.at(i)][VPADDING] * fontSize);
		vertices[(32 * i) + 26] = 0.0f;
		vertices[(32 * i) + 27] = 0.0f;
		vertices[(32 * i) + 28] = 0.0f;
		vertices[(32 * i) + 29] = 0.0f;
		vertices[(32 * i) + 30] = bottomLeftAtlas.x + atlasSquareSize;
		vertices[(32 * i) + 31] = bottomLeftAtlas.y;


		//Go to next square
		xPos += fontSize + (fontMap[text.at(i)][HPADDING] * fontSize);
		
	}

	// Step 3 :)
}

void TextRenderer::buildIndices(GLuint* indices, unsigned int characterCount)
{
	//0, 2, 1,
	//0, 3, 2,

	unsigned int offset = 0;
	for (int i = 0; i < characterCount; i += 6)
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

void TextRenderer::addSpace(GLfloat* vertices, float xPos, float yPos, unsigned int fontSize, int i)
{
	glm::vec2 bottomLeftAtlas = glm::vec2(0.001f, 0.001f);


	// Bottom Left
	vertices[32 * i] = xPos;
	vertices[(32 * i) + 1] = yPos;
	vertices[(32 * i) + 2] = 0.0f;
	vertices[(32 * i) + 3] = 0.0f;
	vertices[(32 * i) + 4] = 0.0f;
	vertices[(32 * i) + 5] = 0.0f;
	vertices[(32 * i) + 6] = bottomLeftAtlas.x;
	vertices[(32 * i) + 7] = bottomLeftAtlas.y;

	// Top Left
	vertices[(32 * i) + 8] = xPos;
	vertices[(32 * i) + 9] = yPos + fontSize;
	vertices[(32 * i) + 10] = 0.0f;
	vertices[(32 * i) + 11] = 0.0f;
	vertices[(32 * i) + 12] = 0.0f;
	vertices[(32 * i) + 13] = 0.0f;
	vertices[(32 * i) + 14] = bottomLeftAtlas.x;
	vertices[(32 * i) + 15] = bottomLeftAtlas.y;

	// Top Right
	vertices[(32 * i) + 16] = xPos + fontSize;
	vertices[(32 * i) + 17] = yPos + fontSize;
	vertices[(32 * i) + 18] = 0.0f;
	vertices[(32 * i) + 19] = 0.0f;
	vertices[(32 * i) + 20] = 0.0f;
	vertices[(32 * i) + 21] = 0.0f;
	vertices[(32 * i) + 22] = bottomLeftAtlas.x;
	vertices[(32 * i) + 23] = bottomLeftAtlas.y;

	// Bottom Right
	vertices[(32 * i) + 24] = xPos + fontSize;
	vertices[(32 * i) + 25] = yPos;
	vertices[(32 * i) + 26] = 0.0f;
	vertices[(32 * i) + 27] = 0.0f;
	vertices[(32 * i) + 28] = 0.0f;
	vertices[(32 * i) + 29] = 0.0f;
	vertices[(32 * i) + 30] = bottomLeftAtlas.x;
	vertices[(32 * i) + 31] = bottomLeftAtlas.y;
}

float TextRenderer::findAlignment(unsigned int alignment, std::string text, unsigned int fontSize)
{

	if (alignment == LEFT_ALIGN)
	{
		return 0.0f;
	}
	else if (alignment == CENTER_ALIGN)
	{
		float totalDistance = 0.0f;

		for (int i = 0; i < text.size(); i++)
		{
			if (text.at(i) = ' ')
			{
				totalDistance += fontSize;
				continue;
			}

			totalDistance += fontSize + (fontMap[text.at(i)][HPADDING] * fontSize);
		}
		return -(totalDistance / 2);
	}
	else if (alignment == RIGHT_ALIGN)
	{
		float totalDistance = 0.0f;

		for (int i = 0; i < text.size(); i++)
		{
			if (text.at(i) = ' ')
			{
				totalDistance += fontSize;
				continue;
			}

			totalDistance += fontSize + (fontMap[text.at(i)][HPADDING] * fontSize);
		}
		return -totalDistance;
	}

	return 0.0f;
}
