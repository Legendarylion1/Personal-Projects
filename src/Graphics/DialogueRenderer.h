#pragma once
#include "../Menu/Menu.h"
#include "../Game/Timer.h"

class DialogueRenderer
{
public:

	DialogueRenderer() {};

	void setup(Menu* menu, Input* input, Timer* timer)
	{ 
		m_menu = menu;
		m_input = input;
		m_timer = timer;

		m_menu->setupDialogueRenderer(&m_dialogueText);
	};

	void setDialogue(std::string topLine, std::string bottomLine, bool awaitClick, bool battleDialogue = false)
	{
		m_topLine = topLine;
		m_bottomLine = bottomLine;
		m_awaitClick = awaitClick;
		m_battleDialogue = battleDialogue;
		m_dialogueText.string1 = "";
		m_dialogueText.string2 = "";
		m_menu->setOverlay(MenuOverlay::DIALOGUE);
		m_menu->setCanLeave(false);
		m_timer->resetTimer();
		m_count = 0;

		if (m_battleDialogue)
			m_menu->setOverlayBackground(MenuOverlay::DIALOGUE, new ImageRenderData{ 50.0f, 12.5f, 50.0f, 10.0f, g_overlayTextureLocations[MenuOverlay::BATTLE_CHAT] });
		else
			m_menu->setOverlayBackground(MenuOverlay::DIALOGUE, new ImageRenderData{ 50.0f, 12.5f, 50.0f, 10.0f, g_overlayTextureLocations[MenuOverlay::DIALOGUE] });
	}

	bool rendereringDialogue()
	{
		if (m_topLine.size() == m_dialogueText.string1.size() && m_bottomLine.size() == m_dialogueText.string2.size())
		{
			if (m_awaitClick && m_input->anyButtonPressed())	//TODO: Visualize await click
			{
				m_menu->setOverlay(MenuOverlay::NONE);
				m_menu->setCanLeave(true);
				return false;
			}
			else if (!m_awaitClick)
			{
				m_menu->setOverlay(MenuOverlay::NONE);
				m_menu->setCanLeave(true);
				return false;
			}
		}

		return true;
	}

	void renderDialogue()
	{
		m_menu->renderMenu();
		
		if (m_topLine.size() != m_dialogueText.string1.size())
			addCharacter(m_topLine, true);
		else
			addCharacter(m_bottomLine, false);
	};

private:

	void addCharacter(std::string line, bool top)
	{
		if (m_dialogueText.string1 == m_topLine && m_dialogueText.string2 == m_bottomLine)
			return;

		if (m_count >= 100)
		{
			if (top)
				m_dialogueText.string1 += line.at(m_dialogueText.string1.size());
			else
				m_dialogueText.string2 += line.at(m_dialogueText.string2.size());

			m_count = 0;
			return;
		}

		m_count += (int)(200 * m_timer->getDelta() * m_textSpeed);
	};

private:
	SharedString m_dialogueText;

	Menu* m_menu = nullptr;
	Input* m_input = nullptr;
	Timer* m_timer = nullptr;

	int m_count = 0;

	float m_textSpeed = 10;


	std::string m_topLine;
	std::string m_bottomLine;
	bool m_awaitClick = false;
	bool m_battleDialogue = false;

};