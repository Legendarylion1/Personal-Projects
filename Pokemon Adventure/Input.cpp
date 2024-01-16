#include "Input.h"
#include <iostream>

Input::Input() {}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);

void Input::setup(GLFWwindow* window, bool* clicked, double* mouseX, double* mouseY, bool* up, bool* down, bool* left, bool* right, bool* interact, bool* escape)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);

	m_window = window;
	m_clicked = clicked;
	m_mouseX = mouseX;
	m_mouseY = mouseY;
	m_up = up;
	m_down = down;
	m_left = left;
	m_right = right;
	m_interact = interact;
	m_escape = escape;

	mouseClicked = m_clicked;
}

void Input::onUpdate()
{
	*m_clicked = false;
	*m_up = false;
	*m_down = false;
	*m_left = false;
	*m_right = false;
	*m_interact = false;
	*m_escape = false;

	for (unsigned int key : active_inputs)
	{
		if (glfwGetKey(m_window, key) == GLFW_PRESS)
		{
			evaluateKey(key);
			
			//mappedBoolean[keyEvents[key]] = true;
			//*mappedBoolean.at(keyEvents[key]) = true;
		}
	}

	glfwGetCursorPos(m_window, m_mouseX, m_mouseY);

	*m_mouseY = -*m_mouseY + 1080.0f;
}

bool Input::getClicked()
{
	return *m_clicked;
}

void Input::setInputValues(int up, int down, int left, int right, int interact)
{
	for (unsigned int key : active_inputs)
	{
		keyEvents[key] == INPUT_EVENT::NONE;
	}
	active_inputs.clear();

	active_inputs.push_back(up);
	active_inputs.push_back(down);
	active_inputs.push_back(left);
	active_inputs.push_back(right);
	active_inputs.push_back(interact);
	active_inputs.push_back(GLFW_KEY_ESCAPE);

	keyEvents[up]				= INPUT_EVENT::MOVE_UP;
	keyEvents[down]				= INPUT_EVENT::MOVE_DOWN;
	keyEvents[left]				= INPUT_EVENT::MOVE_LEFT;
	keyEvents[right]			= INPUT_EVENT::MOVE_RIGHT;
	keyEvents[interact]			= INPUT_EVENT::INTERACT;
	keyEvents[GLFW_KEY_ESCAPE]	= INPUT_EVENT::ESCAPE;
}

int Input::getKey(INPUT_EVENT input)
{
	for (unsigned int key : active_inputs)
	{
		if (keyEvents[key] == input)
			return key;
	}
	return -1;
}

int Input::getNewInput(int key)
{
	for (auto& keyMap : keyEvents)
	{
		if (glfwGetKey(m_window, keyMap.first) == GLFW_PRESS)
		{
			if (key == keyMap.first)
				return key;

			for (int activeKey : active_inputs)
			{
				if (keyMap.first == activeKey && activeKey != GLFW_KEY_ESCAPE)
				{
					return -1 * activeKey;
				}
			}

			return keyMap.first;
		}
	}
	return -1;
}

INPUT_EVENT Input::getEvent(int key)
{
	return keyEvents[key];
}

void Input::updateKey(int oldKey, int newKey)
{
	int index = 0;

	//Keeping it all inside the for loop ensures that the correct key was found and replaced
	for (int i = 0; i < active_inputs.size(); i++)
	{
		if (active_inputs.at(i) == oldKey)
		{
			active_inputs.erase(active_inputs.begin() + i);
			active_inputs.push_back(newKey);


			INPUT_EVENT associatedEvent = keyEvents[oldKey];
			keyEvents[oldKey] = INPUT_EVENT::NONE;
			keyEvents[newKey] = associatedEvent;
			return;
		}
	}
}

void Input::swapKey(int oldKey, int newKey)
{
	INPUT_EVENT oldEvent = keyEvents[oldKey];

	keyEvents[oldKey] = keyEvents[newKey];
	keyEvents[newKey] = oldEvent;
}

void Input::evaluateKey(unsigned int key)
{
	if (keyEvents[key] == INPUT_EVENT::MOVE_UP)
		*m_up = true;
	else if (keyEvents[key] == INPUT_EVENT::MOVE_DOWN)
		*m_down = true;
	else if (keyEvents[key] == INPUT_EVENT::MOVE_LEFT)
		*m_left = true;
	else if (keyEvents[key] == INPUT_EVENT::MOVE_RIGHT)
		*m_right = true;
	else if (keyEvents[key] == INPUT_EVENT::INTERACT)
		*m_interact = true;
	else if (keyEvents[key] == INPUT_EVENT::ESCAPE)
		*m_escape = true;
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		*mouseClicked = true;
	}
}
