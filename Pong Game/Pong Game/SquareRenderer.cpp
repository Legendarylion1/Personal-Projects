#include "SquareRenderer.h"
#include <iostream>

SquareRenderer::SquareRenderer(float bottom_left_x, float bottom_left_y, float width, float height, unsigned int shader, float color[3])
    :m_ib( m_indices,6),
    m_renderer(shader)
{
    m_width = width;
    m_height = height;
    m_vertices[0] = bottom_left_x;			m_vertices[1] = bottom_left_y;			// bottom Left
    m_vertices[2] = bottom_left_x + width;	m_vertices[3] = bottom_left_y;			// bottom Right
    m_vertices[4] = bottom_left_x + width;  m_vertices[5] = bottom_left_y + height;	// top Right
    m_vertices[6] = bottom_left_x;			m_vertices[7] = bottom_left_y + height;	// top Left
    
    //TODO: Normalize colors coming in so that I can write as rgb
    m_color.push_back(color[0]);
    m_color.push_back(color[1]);
    m_color.push_back(color[2]);

    m_shader = shader;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    VertexBuffer vb2(m_vertices, 8 * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SquareRenderer::move(float xTranslation, float yTranslation)
{
    m_xTranslation += xTranslation;
    m_yTranslation += yTranslation;
    if (yTranslation > 0)
    {
        tempCount += 1;
    }
    else if (yTranslation < 0)
    {
        tempCount -= 1;
    }
}

void SquareRenderer::draw()
{
    glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), glm::vec3(m_xTranslation, m_yTranslation, 0.0f));
    glm::mat4 position = pos1 * m_renderer.p_aspectRatio;
    m_renderer.draw(m_vao, m_ib, m_color, position);
}

float SquareRenderer::getX()
{
    return m_vertices[0] + (m_xTranslation * m_xTranslationScalar);
}

float SquareRenderer::getY()
{
    return m_vertices[1] + (m_yTranslation * m_yTranslationScalar);
}

float* SquareRenderer::getVertices()
{
    return m_vertices;
}

float SquareRenderer::getWidth()
{
    return m_width;
}

float SquareRenderer::getHeight()
{
    return m_height;
}

int SquareRenderer::getCount()
{
    return tempCount;
}

float SquareRenderer::getXTranslation()
{
    return m_xTranslation;
}

float SquareRenderer::getYTranslation()
{
    return m_yTranslation;
}

unsigned int SquareRenderer::getVAO()
{
    return m_vao;
}

IndexBuffer* SquareRenderer::getIB()
{
    return &m_ib;
}

std::vector<float> SquareRenderer::getColor()
{
    return m_color;
}

void SquareRenderer::setXScalar(float scale)
{
    m_xTranslationScalar = scale;
}

void SquareRenderer::setYScalar(float scale)
{
    m_yTranslationScalar = scale;
}

void SquareRenderer::resetPos()
{
    m_xTranslation = 0;
    m_yTranslation = 0;
}