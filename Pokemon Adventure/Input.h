#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

static bool* mouseClicked = nullptr;

static enum INPUT_EVENT
{
	NONE,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	INTERACT,
	ESCAPE
};

class Input {

public:
	Input();

	void setup(GLFWwindow* window, bool* clicked, double* mouseX, double* mouseY, bool* up, bool* down, bool* left, bool* right, bool* interact, bool* escape);

	void onUpdate();

	bool getClicked();

	void setInputValues(int up, int down, int left, int right, int interact);


	int getKey(INPUT_EVENT input);
	int getNewInput(int key);
	INPUT_EVENT getEvent(int key);

	void updateKey(int oldKey, int newKey);
	void swapKey(int oldKey, int newKey);

private:
	void evaluateKey(unsigned int key);

private:
	GLFWwindow* m_window = nullptr;

	bool* m_clicked = nullptr;

	double* m_mouseX = nullptr;
	double* m_mouseY = nullptr;

	bool* m_up = nullptr;
	bool* m_down = nullptr;
	bool* m_left = nullptr;
	bool* m_right = nullptr;
	bool* m_interact = nullptr;
	bool* m_escape = nullptr;

	std::unordered_map<INPUT_EVENT, bool> mappedBoolean
	{
		{MOVE_UP, m_up},
		{MOVE_DOWN, m_down},
		{MOVE_LEFT, m_left},
		{MOVE_RIGHT, m_right},
		{INTERACT, m_interact},
		{ESCAPE, m_escape}
	};
};

static std::vector<unsigned int> active_inputs
{
	GLFW_KEY_A,
	GLFW_KEY_D,
	GLFW_KEY_E,
	GLFW_KEY_S,
	GLFW_KEY_W,
	GLFW_KEY_ESCAPE
};

//TODO: Add controller support
static std::unordered_map<unsigned int, INPUT_EVENT> keyEvents
{
	//	Letters
	{GLFW_KEY_A,INPUT_EVENT::MOVE_LEFT},
	{GLFW_KEY_B,INPUT_EVENT::NONE},
	{GLFW_KEY_C,INPUT_EVENT::NONE},
	{GLFW_KEY_D,INPUT_EVENT::MOVE_RIGHT},
	{GLFW_KEY_E,INPUT_EVENT::INTERACT},
	{GLFW_KEY_F,INPUT_EVENT::NONE},
	{GLFW_KEY_G,INPUT_EVENT::NONE},
	{GLFW_KEY_H,INPUT_EVENT::NONE},
	{GLFW_KEY_I,INPUT_EVENT::NONE},
	{GLFW_KEY_J,INPUT_EVENT::NONE},
	{GLFW_KEY_K,INPUT_EVENT::NONE},
	{GLFW_KEY_L,INPUT_EVENT::NONE},
	{GLFW_KEY_M,INPUT_EVENT::NONE},
	{GLFW_KEY_N,INPUT_EVENT::NONE},
	{GLFW_KEY_O,INPUT_EVENT::NONE},
	{GLFW_KEY_P,INPUT_EVENT::NONE},
	{GLFW_KEY_Q,INPUT_EVENT::NONE},
	{GLFW_KEY_R,INPUT_EVENT::NONE},
	{GLFW_KEY_S,INPUT_EVENT::MOVE_DOWN},
	{GLFW_KEY_T,INPUT_EVENT::NONE},
	{GLFW_KEY_U,INPUT_EVENT::NONE},
	{GLFW_KEY_V,INPUT_EVENT::NONE},
	{GLFW_KEY_W,INPUT_EVENT::MOVE_UP},
	{GLFW_KEY_X,INPUT_EVENT::NONE},
	{GLFW_KEY_Y,INPUT_EVENT::NONE},
	{GLFW_KEY_Z,INPUT_EVENT::NONE},

	// Arrows
	{GLFW_KEY_UP,INPUT_EVENT::NONE},
	{GLFW_KEY_DOWN,INPUT_EVENT::NONE},
	{GLFW_KEY_LEFT,INPUT_EVENT::NONE},
	{GLFW_KEY_RIGHT,INPUT_EVENT::NONE},

	// Numbers
	{GLFW_KEY_0,INPUT_EVENT::NONE},
	{GLFW_KEY_1,INPUT_EVENT::NONE},
	{GLFW_KEY_2,INPUT_EVENT::NONE},
	{GLFW_KEY_3,INPUT_EVENT::NONE},
	{GLFW_KEY_4,INPUT_EVENT::NONE},
	{GLFW_KEY_5,INPUT_EVENT::NONE},
	{GLFW_KEY_6,INPUT_EVENT::NONE},
	{GLFW_KEY_7,INPUT_EVENT::NONE},
	{GLFW_KEY_8,INPUT_EVENT::NONE},
	{GLFW_KEY_9,INPUT_EVENT::NONE},

	// Others
	{GLFW_KEY_ESCAPE,INPUT_EVENT::ESCAPE}
};


static std::unordered_map<unsigned int, std::string> keyStrings
{
	//	Letters
	{GLFW_KEY_A,"A"},
	{GLFW_KEY_B,"B"},
	{GLFW_KEY_C,"C"},
	{GLFW_KEY_D,"D"},
	{GLFW_KEY_E,"E"},
	{GLFW_KEY_F,"F"},
	{GLFW_KEY_G,"G"},
	{GLFW_KEY_H,"H"},
	{GLFW_KEY_I,"I"},
	{GLFW_KEY_J,"J"},
	{GLFW_KEY_K,"K"},
	{GLFW_KEY_L,"L"},
	{GLFW_KEY_M,"M"},
	{GLFW_KEY_N,"N"},
	{GLFW_KEY_O,"O"},
	{GLFW_KEY_P,"P"},
	{GLFW_KEY_Q,"Q"},
	{GLFW_KEY_R,"R"},
	{GLFW_KEY_S,"S"},
	{GLFW_KEY_T,"T"},
	{GLFW_KEY_U,"U"},
	{GLFW_KEY_V,"V"},
	{GLFW_KEY_W,"W"},
	{GLFW_KEY_X,"X"},
	{GLFW_KEY_Y,"Y"},
	{GLFW_KEY_Z,"Z"},

	// Arrows
	{GLFW_KEY_UP,"UP"},
	{GLFW_KEY_DOWN,"DWN"},
	{GLFW_KEY_LEFT,"LFT"},
	{GLFW_KEY_RIGHT,"RGT"},

	// Numbers
	{GLFW_KEY_0,"0"},
	{GLFW_KEY_1,"1"},
	{GLFW_KEY_2,"2"},
	{GLFW_KEY_3,"3"},
	{GLFW_KEY_4,"4"},
	{GLFW_KEY_5,"5"},
	{GLFW_KEY_6,"6"},
	{GLFW_KEY_7,"7"},
	{GLFW_KEY_8,"8"},
	{GLFW_KEY_9,"9"},

	// Others
	{GLFW_KEY_ESCAPE,"ESC"}
};