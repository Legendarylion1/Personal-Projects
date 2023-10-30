#pragma once
#include "IndexBuffer.h"
#include "GL/glew.h"
#include <vector>
#include "ThirdParty/glm/glm.hpp"
#include "ThirdParty/glm/gtc/matrix_transform.hpp"

class Renderer
{
private:
	unsigned int m_shader;
	int m_colorID;
	int m_positionMatrixID;
public:
	// 4:3 uses a lot less memory than 16:9
	glm::mat4 p_aspectRatio = glm::ortho(0.0f, 1200.0f, 0.0f, 700.0f, -1.0f, 1.0f);
public:
	Renderer(const unsigned int shader);
	void draw(const unsigned int vao, const IndexBuffer& ib, const std::vector<float>& color, glm::mat4& positionMatrix);
};