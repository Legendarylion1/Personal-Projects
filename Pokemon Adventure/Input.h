#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static bool* mouseClicked = nullptr;

class Input {

public:
	Input();

	void setup(GLFWwindow* window, bool* clicked, double* mouseX, double* mouseY, bool* up, bool* down, bool* left, bool* right, bool* interact, bool* escape);

	void onUpdate();

private:
	GLFWwindow* m_window = nullptr;

	bool* m_clicked = nullptr;

	double* m_mouseX	= nullptr;
	double* m_mouseY	= nullptr;

	bool* m_up			= nullptr;
	bool* m_down		= nullptr;
	bool* m_left		= nullptr;
	bool* m_right		= nullptr;
	bool* m_interact	= nullptr;
	bool* m_escape		= nullptr;
};