#pragma once

#include "Handlers/EncounterHandler.h"
#include "../Characters/CharacterMover.h"
#include "Handlers/InteractionHandler.h"
#include "Handlers/PauseHandler.h"
#include "Handlers/StartupHandler.h"
#include "Interactions/Cutscene.h"
#include "../Battle/BattleSimulator.h"
#include "../Map/MapHandler.h"
#include "Input/InputData.h"
#include "../Menu/menuData.h"
#include "../Characters/Trainer/Trainer.h"
#include "Input/Input.h"
#include "Interactions/PC.h"
#include "../Menu/Menu.h"

class Game
{
public:

	Game();

	void run();

private:
	void startUp();

	void onUpdate();
 
	Renderer m_renderer;
	Timer m_timer;

	Trainer m_player;
	CharacterMover m_characterMover;
	Input m_input;
	Menu m_menu;
	PC m_pc;

	Cutscene m_cutScene;
	StartupHandler startupHandler;			//TODO: I want this to be deleted after startup
	BattleSimulator m_battlesimulator;
	InteractionHandler m_interactionHandler;
	EncounterHandler m_encounterHandler;
	MapHandler m_mapHandler;
	PauseHandler m_pauseHandler;
	DialogueRenderer m_dialogueRenderer;
	DataManager m_dataManager;
	Animator m_animator;

	InputVariables m_inputVariables;

	RosterDisplayData m_rosterData{};
};