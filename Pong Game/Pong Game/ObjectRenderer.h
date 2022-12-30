#pragma once

#include "Renderer.h"
#include "VertexBuffer.h"
#include "DataConstants.h"

class ObjectRenderer
{
private:
	std::vector<float> m_vertices;
	std::vector<float> m_indices;

	float m_xTranslation = 0;
	float m_yTranslation = 0;
	float m_xTranslationScalar = 350.0f;
	float m_yTranslationScalar = 350.0f;

	std::vector<float> m_color;

	Renderer m_renderer;
	IndexBuffer m_ib;
	unsigned int m_shader = 0;
	unsigned int m_vao ;

public:
	ObjectRenderer(float* vertices, unsigned int verticeCount, const unsigned int* indices, unsigned int indiceCount, unsigned int shader, float color[3]);
	ObjectRenderer(DC::objectRenderData& object, unsigned int shader);

	void move(float xTranslation, float yTranslation);
	void draw();

	void setXScalar(float scale);
	void setYScalar(float scale);
	void resetPos();

	void updateAll(DC::objectRenderData& newData);
};