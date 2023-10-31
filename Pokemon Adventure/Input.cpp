#include "Input.h"

Input::Input(){}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);

void Input::setup(GLFWwindow* window, bool* clicked, double* mouseX, double* mouseY, bool* up, bool* down, bool* left, bool* right, bool* interact, bool* escape)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);

	m_window	= window;
	m_clicked	= clicked;
	m_mouseX	= mouseX;
	m_mouseY	= mouseY;
	m_up		= up;
	m_down		= down;
	m_left		= left;
	m_right		= right;
	m_interact	= interact;
	m_escape	= escape;

	mouseClicked = m_clicked;
}

void Input::onUpdate()
{
	*m_clicked	= false;
	*m_up		= false;
	*m_down		= false;
	*m_left		= false;
	*m_right	= false;
	*m_interact = false;
	*m_escape	= false;

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		*m_up = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		*m_down = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		*m_left = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		*m_right = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
	{
		*m_interact = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		*m_escape = true;
	}



	glfwGetCursorPos(m_window, m_mouseX, m_mouseY);

	*m_mouseY = -*m_mouseY + 1080.0f;
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		*mouseClicked = true;
	}
}
