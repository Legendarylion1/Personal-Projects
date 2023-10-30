#include "renderer.h"

Renderer::Renderer(const unsigned int shader)
{
    m_shader = shader;
    m_colorID = glGetUniformLocation(m_shader, "u_Color");
    m_positionMatrixID = glGetUniformLocation(m_shader, "u_PositionMatrix");
}

void Renderer::draw(const unsigned int vao, const IndexBuffer& ib, const std::vector<float>& color, glm::mat4& positionMatrix)
{
    glBindVertexArray(vao);

    glUniform4f(m_colorID, color[0], color[1], color[2], 1.0f);
    glUniformMatrix4fv(m_positionMatrixID, 1, GL_FALSE, &positionMatrix[0][0]);

    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
    ib.Unbind();

    glBindVertexArray(0);
}