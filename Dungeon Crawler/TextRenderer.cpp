#include "TextRenderer.h"

TextRenderer::TextRenderer(Shader& shader, Camera& camera):
	m_shader(shader), m_camera(camera)
{
	m_characterAtlas = Texture("Images/alphaNumeric.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterAtlas.texUnit(shader, "tex0", 0);
}

void TextRenderer::renderText(const char* text, float x, float y, unsigned int fontSize, unsigned int fontSpacing)
{
	// TODO: Handle spaces
	// TODO: Handle Numbers
	// TODO: Handle our limit special Characters
	// TODO: Make it so that if we need more characters than 100, then it flushes early and draws the remaining characters

	unsigned int characterCount = lengthOf(text);

	const unsigned int MAX_QUADS = 100;
	const unsigned int MAX_VERTICES = MAX_QUADS * 32;
	const unsigned int MAX_INDICES = MAX_QUADS * 6;



	GLfloat vertices[MAX_VERTICES]{};
	GLuint indices[MAX_INDICES]{};

	buildIndices(indices, MAX_INDICES);
	buildVertices(vertices, x, y, fontSize, fontSpacing, characterCount, MAX_VERTICES, text);
	
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
	
	m_characterAtlas.Bind();
	VAO1.Bind();
	m_camera.Matrix(m_shader, glm::vec3(x,y,0.0f));
	glDrawElements(GL_TRIANGLES, 6*characterCount, GL_UNSIGNED_INT, nullptr);
	VAO1.Unbind();
	m_characterAtlas.Unbind();
	
	EBO1.Delete();
	VBO1.Delete();
	VAO1.Delete();

	
}

unsigned int TextRenderer::lengthOf(const char* text)
{
	unsigned int size = 0;

	while (text[size] != '\0')
		size++;

	return size;
}

void TextRenderer::buildVertices(GLfloat* vertices, float x, float y, unsigned int fontSize, unsigned int fontSpacing, unsigned int characterCount, unsigned int maxVertices, const char* text)
{
	// Font size is the width and height of the quad
	// If Odd character Count we center Around the middle value
	// If Even character Count we center around the middle of the spacing between the characters


	// Step 1. Find the far left
	// Step 2. Build up the vertices
	// Step 2.5		Find the positions of the characters in the atlas
	// Step 3  Return



	// Step 1
	float xPos = 0.0f;
	float yPos = -1 * (fontSize/2.0f);

	if (characterCount % 2 == 0)
		xPos -= fontSpacing / 2.0f;
	else
		xPos -= fontSize / 2.0f;

	xPos -= ((characterCount / 2.0f) - 1) * fontSpacing;

	xPos -= (characterCount / 2.0f) * fontSize;


	// Step 2

	float atlasSquareSize = 0.125f;

	for (int i = 0; i < characterCount; i++)
	{
		//Step 2.5
		//char toFind = ;
		glm::vec2 bottomLeftAtlas = findCharAtlas(text[i]);

		//quadBufferPtr->Position = { xPos, yPos, LAYER_FIVE };
		//quadBufferPtr->Color = { 0.0f,0.0f,0.0f };
		//quadBufferPtr->TexCoords = {bottomLeftAtlas.x,bottomLeftAtlas.y};
		//quadBufferPtr++;


		// Bottom Left
		vertices[ 32 * i ] = xPos; 
		vertices[(32 * i) + 1] = yPos; 
		vertices[(32 * i) + 2] = LAYER_SEVEN; 
		vertices[(32 * i) + 3] = 0.0f; 
		vertices[(32 * i) + 4] = 0.0f; 
		vertices[(32 * i) + 5] = 0.0f; 
		vertices[(32 * i) + 6] = bottomLeftAtlas.x; 
		vertices[(32 * i) + 7] = bottomLeftAtlas.y;

		// Top Left
		vertices[(32 * i) + 8] = xPos; 
		vertices[(32 * i) + 9] = yPos + fontSize;
		vertices[(32 * i) + 10] = LAYER_SEVEN; 
		vertices[(32 * i) + 11] = 0.0f; 
		vertices[(32 * i) + 12] = 0.0f; 
		vertices[(32 * i) + 13] = 0.0f; 
		vertices[(32 * i) + 14] = bottomLeftAtlas.x;
		vertices[(32 * i) + 15] = bottomLeftAtlas.y + atlasSquareSize;
		// Top Right
		vertices[(32 * i) + 16] = xPos + fontSize; 
		vertices[(32 * i) + 17] = yPos + fontSize; 
		vertices[(32 * i) + 18] = LAYER_SEVEN; 
		vertices[(32 * i) + 19] = 0.0f; 
		vertices[(32 * i) + 20] = 0.0f; 
		vertices[(32 * i) + 21] = 0.0f; 
		vertices[(32 * i) + 22] = bottomLeftAtlas.x + atlasSquareSize; 
		vertices[(32 * i) + 23] = bottomLeftAtlas.y + atlasSquareSize;

		// Bottom Right
		vertices[(32 * i) + 24] = xPos + fontSize; 
		vertices[(32 * i) + 25] = yPos; 
		vertices[(32 * i) + 26] = LAYER_SEVEN;
		vertices[(32 * i) + 27] = 0.0f; 
		vertices[(32 * i) + 28] = 0.0f; 
		vertices[(32 * i) + 29] = 0.0f; 
		vertices[(32 * i) + 30] = bottomLeftAtlas.x + atlasSquareSize; 
		vertices[(32 * i) + 31] = bottomLeftAtlas.y;
	
	
		//Go to next square
		xPos += fontSize + fontSpacing;
	}

	// Step 3 :)
}

void TextRenderer::buildIndices(GLuint *indices, unsigned int characterCount)
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

glm::vec2 TextRenderer::findCharAtlas(char character)
{
	// Is it a number
	// Is it capital
	// Is it lowercase

	// For capital we can figure out how far away it is from 65
	// For lowercase we can do the same
	// numbers are similar except they across the top

	unsigned int numbersX = 0;
	unsigned int numbersY = 7;


	unsigned int capitalX = 2;
	unsigned int capitalY = 6;

	unsigned int lowerX = 4;
	unsigned int lowerY = 3;

	int test = int(character);

	//Capital Letters
	if (int(character) >= 65 && int(character) <= 90)
	{
		for (int i = 0; i < int(character) - 65; i++)
		{
			if (capitalX == 7)
			{
				capitalX = 0;
				capitalY -= 1;
			}
			else
				capitalX += 1;
		}
		return glm::vec2(capitalX * 0.125f, capitalY * 0.125f);
	}
	else if (int(character) >= 97 && int(character) <= 122)
	{

		for (int i = 0; i < int(character) - 97; i++)
		{
			if (lowerX == 7)
			{
				lowerX = 0;
				lowerY -= 1;
			}
			else
				lowerX += 1;
		}
		return glm::vec2(lowerX * 0.125f, lowerY * 0.125f);
	}
	else if (int(character) == 32)
	{
		return glm::vec2(7 * 0.125f, 0.0f);
	}
	else if (int(character) >= 48 && int(character) <= 57)
	{
		for (int i = 0; i < int(character) - 48; i++)
		{
			if (numbersX == 7)
			{
				numbersX = 0;
				numbersY -= 1;
			}
			else
				numbersX += 1;
		}
		return glm::vec2(numbersX * 0.125f, numbersY * 0.125f);
	}
	else if (int(character) == 45)
	{
		return glm::vec2(6 * 0.125f, 0.0f);
	}
	else
	{
		return glm::vec2();
	}

	return glm::vec2();
}
