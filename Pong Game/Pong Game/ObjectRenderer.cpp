#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(float* vertices, unsigned int verticeCount, const unsigned int* indices, unsigned int indiceCount, unsigned int shader, float color[3])
	:m_renderer(shader)
{
    m_ib.initIndexBuffer(indices, indiceCount);
    
    m_color.push_back(color[0]);
    m_color.push_back(color[1]);
    m_color.push_back(color[2]);
    
    m_shader = shader;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    VertexBuffer vb2(vertices, verticeCount * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ObjectRenderer::ObjectRenderer(DC::objectRenderData& object, unsigned int shader)
    : m_renderer(shader)
{
    m_ib.initIndexBuffer(object.indices, object.indiceCount);

    m_color.push_back(object.color[0]);
    m_color.push_back(object.color[1]);
    m_color.push_back(object.color[2]);

    m_shader = shader;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    VertexBuffer vb2(object.vertices, object.verticeCount * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ObjectRenderer::move(float xTranslation, float yTranslation)
{
    m_xTranslation += xTranslation;
    m_yTranslation += yTranslation;
}

void ObjectRenderer::draw()
{
    glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), glm::vec3(m_xTranslation, m_yTranslation, 0.0f));
    glm::mat4 position = pos1 * m_renderer.p_aspectRatio;
    m_renderer.draw(m_vao, m_ib, m_color, position);
}

void ObjectRenderer::setXScalar(float scale)
{
    m_xTranslationScalar = scale;
}

void ObjectRenderer::setYScalar(float scale)
{
    m_yTranslationScalar = scale;
}

void ObjectRenderer::resetPos()
{
    m_xTranslation = 0;
    m_yTranslation = 0;
}

void ObjectRenderer::updateAll(DC::objectRenderData& newData)
{
    m_ib.initIndexBuffer(newData.indices, newData.indiceCount);

    glBindVertexArray(m_vao);
    VertexBuffer vb2(newData.vertices, newData.verticeCount * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}