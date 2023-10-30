#pragma once

#include "Renderer.h"
#include "VertexBuffer.h"

class SquareRenderer
{
private:
	float m_vertices[8];
	unsigned int m_indices[6] = {0, 1, 2,
						         2, 3, 0 };
	
	float m_width;
	float m_height;
	float m_xTranslation = 0;
	float m_yTranslation = 0;
	float m_xTranslationScalar = 350.0f;
	float m_yTranslationScalar = 350.0f;

	std::vector<float> m_color;

	Renderer m_renderer;
	IndexBuffer m_ib;
	unsigned int m_shader;
	unsigned int m_vao;

public:
	int tempCount = 0;

public:
	SquareRenderer(float bottom_left_x, float bottom_left_y, float width, float height, unsigned int shader, float color[3]);
	void move(float xTranslation, float yTranslation);

	void draw();
	unsigned int getVAO();
	IndexBuffer* getIB();

	std::vector<float> getColor();
	float getWidth();
	float getHeight();
	float getX();
	float getY();
	float getXTranslation();
	float getYTranslation();
	float *getVertices();
	int   getCount();

	void setXScalar(float scale);
	void setYScalar(float scale);

	void resetPos();
};