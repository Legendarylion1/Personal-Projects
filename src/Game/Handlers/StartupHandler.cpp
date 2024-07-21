#include "StartupHandler.h"

StartupHandler::StartupHandler(Trainer* player, DataManager* dataManager, Menu* menu, Timer* timer, Input* input, DialogueRenderer* dialogueRenderer, Animator* animator)	//TODO: Will need timer for animations
{
	m_player = player;
	m_dataManager = dataManager;
	m_menu = menu;
	m_timer = timer;
	m_input = input;
	m_dialogueRenderer = dialogueRenderer;
	m_animator = animator;
}

void StartupHandler::run()
{
	playIntro();

	getSetupData();

	playNewGameSequence();

	m_menu->setscene(MenuScene::NONE);
	//TODO: Skip Setup Data for first time sign on. Use file 2 for default
}

void StartupHandler::playIntro()
{
	m_timer->resetTimer();

	bool studioVisible = false;
	bool pressAnyButton = false;

	// Intro Links
	{
		m_menu->setupIntroData(&studioVisible, &pressAnyButton);		//TODO: Remove Studio Visible
		m_menu->setCanLeave(false);
		m_menu->preRun();
		m_menu->setscene(MenuScene::INTRO_LINKS);
		
		float count = 0.0f;
		float target = 2.5f;

		m_animator->loadAnimations({ Animation::LEGENDARY_STUDIO, Animation::FADE_IN, Animation::FADE_OUT, Animation::LEGENDARY_POKEMON });

		std::cout << "Pre While Loop" << std::endl;

		while (count < target || !m_animator->loadingComplete())
		{
			m_menu->renderMenu();
			m_animator->updateRenderer();
			count += m_timer->getDelta();
		}

		std::cout << "Count: " << count << std::endl;
		
	}

	// Fade Out from Intro Links
	{
		m_animator->setAnimation(Animation::FADE_OUT);

		while (m_animator->animationPlaying())
		{
			m_menu->renderMenu();
			m_animator->playAnimation();
			m_animator->updateRenderer();
		}
	}

	// Fade Into studio
	{
		m_menu->setscene(MenuScene::INTRO_STUDIO);
		m_animator->setAnimation(Animation::FADE_IN);

		while (m_animator->animationPlaying())
		{
			m_menu->renderMenu();
			m_animator->playAnimation();
			m_animator->updateRenderer();
		}
	}
	
	// Studio Animation
	{
		std::cout << "Pre set Animation" << std::endl;

		m_animator->setAnimation(Animation::LEGENDARY_STUDIO);

		while (m_animator->animationPlaying())
		{
			m_animator->playAnimation();
			m_animator->updateRenderer();
		}
	}

	// Fade Out from Studio Animation
	{
		m_menu->setscene(MenuScene::INTRO_STUDIO_CROWN);
		m_animator->setAnimation(Animation::FADE_OUT);

		while (m_animator->animationPlaying())
		{
			m_menu->renderMenu();
			m_animator->playAnimation();
			m_animator->updateRenderer();
		}
	}

	// Fade into Legendary display
	{
		m_menu->setscene(MenuScene::INTRO_LEGENDARY);
		m_animator->setAnimation(Animation::FADE_IN);

		while (m_animator->animationPlaying())
		{
			m_menu->renderMenu();
			m_animator->playAnimation();
			m_animator->updateRenderer();
		}
	}

	//Frame 17 press true

	// Legendary Display
	{
		m_menu->setscene(MenuScene::INTRO_PRESS_ANY_BUTTON);
		m_animator->setAnimation(Animation::LEGENDARY_POKEMON, true);

		while (true)
		{
			if (!pressAnyButton && m_animator->getFrameCount() > 17)
				pressAnyButton = true;

			if (pressAnyButton && m_input->anyButtonPressed())
				break;

			m_animator->playAnimation();
			m_menu->renderMenu();
			m_animator->updateRenderer();

		}
	}

	m_animator->unloadAnimations({ Animation::LEGENDARY_STUDIO, Animation::FADE_IN, Animation::FADE_OUT, Animation::LEGENDARY_POKEMON });
	m_animator->loadAnimations({ Animation::THROW_POKEBALL, Animation::THROW_GREATBALL, Animation::THROW_ULTRABALL, Animation::THROW_MASTERBALL, Animation::ESCAPE_POKEBALL, Animation::ESCAPE_GREATBALL, Animation::ESCAPE_ULTRABALL, Animation::ESCAPE_MASTERBALL, Animation::XP_GAIN, Animation::XP_LEVEL_UP_UI });

	//TODO: Load these as items when they are in the players bag. Unload when they arent. Loading it here for testing purposes
	

	m_menu->postRun();
	m_menu->setCanLeave(true);
}

void StartupHandler::getSetupData()
{
	SharedString* startupHeader1 = new SharedString;
	SharedString* startupHeader2 = new SharedString;	//TODO: No need to have these as pointers lol
	SharedString* startupHeader3 = new SharedString;

	bool* header1Visible = new bool;
	bool* header2Visible = new bool;
	bool* header3Visible = new bool;

	*header1Visible = true;
	*header2Visible = true;
	*header3Visible = true;


	m_menu->setupStartupData(startupHeader1, startupHeader2, startupHeader3, header1Visible, header2Visible, header3Visible);

	int selection = NONE;
	m_menu->setCanLeave(false);
	m_menu->setscene(MenuScene::STARTUP_SCENE);
	m_menu->setRequestedData(&selection);



	HeaderSave save1 = m_dataManager->loadHeader(FileNumber::FILE_ONE);
	HeaderSave save2 = m_dataManager->loadHeader(FileNumber::FILE_TWO);
	HeaderSave save3 = m_dataManager->loadHeader(FileNumber::FILE_THREE);


	formatSave(save1, startupHeader1, header1Visible);
	formatSave(save2, startupHeader2, header2Visible);
	formatSave(save3, startupHeader3, header3Visible);

	if (save1.playerName == "New Game")
		*header1Visible = false;
	if (save2.playerName == "New Game")
		*header2Visible = false;
	if (save3.playerName == "New Game")
		*header3Visible = false;

	if (*header1Visible == false && *header2Visible == false && *header3Visible == false)
	{
		//TODO: These dont need to be heap allocated anymore lol. Revert at some point
		//Also this entire funtion is ugly. Clean it up
		m_dataManager->setFile(FileNumber::FILE_TWO);

		delete startupHeader1;
		delete startupHeader2;
		delete startupHeader3;

		delete header1Visible;
		delete header2Visible;
		delete header3Visible;

		m_newGame = true;
		return;
	}

	m_menu->preRun();
	while (true)
	{
		//system("CLS");
		m_menu->run();

		if (selection == NONE)
			continue;

		if (selection == 3)
		{
			if (deleteFile(&selection))
			{
				m_dataManager->deleteSave(FileNumber::FILE_ONE);
				selection = NONE;
				*header1Visible = false;
				formatSave(save1, startupHeader1, header1Visible);
				m_menu->resetScene(MenuScene::STARTUP_SCENE);
			}
		}
		else if (selection == 4)
		{
			if (deleteFile(&selection))
			{
				m_dataManager->deleteSave(FileNumber::FILE_TWO);
				selection = NONE;
				*header2Visible = false;
				formatSave(save2, startupHeader2, header2Visible);
				m_menu->resetScene(MenuScene::STARTUP_SCENE);
			}
		}
		else if (selection == 5)
		{
			if (deleteFile(&selection))
			{
				m_dataManager->deleteSave(FileNumber::FILE_THREE);
				*header3Visible = false;
				formatSave(save3, startupHeader3, header3Visible);
				m_menu->resetScene(MenuScene::STARTUP_SCENE);
			}
		}
		else
		{
			break;
		}
		
		selection = NONE;
	}

	if (selection == 0)
		m_dataManager->setFile(FileNumber::FILE_ONE);
	else if (selection == 1)
		m_dataManager->setFile(FileNumber::FILE_TWO);
	else
		m_dataManager->setFile(FileNumber::FILE_THREE);

	m_menu->clearRequestedData();
	m_menu->postRun();

	if (selection == 0 && startupHeader1->string1 == "New Game")
	{
		m_newGame = true;
	}
	else if (selection == 1 && startupHeader2->string1 == "New Game")
	{
		m_newGame = true;
		m_dataManager->loadNewGame();
	}
	else if (selection == 2 && startupHeader3->string1 == "New Game")
	{
		m_newGame = true;
		m_dataManager->loadNewGame();
	}
	else
		m_dataManager->loadGame();

	delete startupHeader1;
	delete startupHeader2;
	delete startupHeader3;

	delete header1Visible;
	delete header2Visible;
	delete header3Visible;
}

bool StartupHandler::deleteFile(int* selection)
{
	*selection = NONE;

	while (true)
	{
		m_menu->run();

		if (*selection == NONE)
			continue;

		if (*selection == 0)
		{
			*selection = NONE;
			return true;
		}
		else
		{
			*selection = NONE;
			return false;
		}
	}
}

void StartupHandler::playNewGameSequence()
{
	if (!m_newGame)
		return;

	playProfessorMessage();

	//m_dataManager->loadNewGame();


	std::string playerName;
	AlphabetStringData stringData;
	m_menu->setupKeyboard(&stringData, &playerName);		//TODO: Move somewhere more accessible. Maybe keyboard class

	int selection = NONE;

	m_menu->setRequestedData(&selection);
	m_menu->setCanLeave(false);
	m_menu->setscene(MenuScene::SET_PLAYER_NAME);
	m_menu->setOverlay(MenuOverlay::ON_SCREEN_KEYBOARD);
	m_menu->preRun();

	while (true)
	{
		//system("CLS");
		m_menu->run();

		if (selection == NONE)
			continue;

		if (selection == 39)
			swapAlphabetData(&stringData);
		else if (selection == 40)
			playerName += " ";
		else if (selection == 41)
		{
			if (playerName.size() > 0)
				playerName.erase(playerName.begin() + playerName.size() - 1);
		}
		else if (selection == 42)
			break;
		else
			playerName += getKeyboardCharacter(&stringData, selection);
		selection = NONE;
	}

	m_menu->setOverlay(MenuOverlay::NONE);
	m_menu->clearRequestedData();
	m_menu->postRun();
	m_menu->setCanLeave(true);



	//TODO: Enforce Name Size

	m_player->setName(playerName);
}

void StartupHandler::formatSave(HeaderSave save, SharedString* string, bool* visible)
{
	string->string1 = save.playerName;

	if (*visible == false)
	{
		string->string1 = "New Game";
		string->string2 = "";
		string->string3 = "";
		string->string4 = "";
		return;
	}

	if (save.playerName == "New Game")
	{
		*visible = false;
		return;
	}

	string->string2 = save.playTime;
	string->string3 = "Pokemon Found: " + std::to_string(save.pokedexFound);	//TODO: Add a pokedex
	string->string4 = "Badges: " + std::to_string(save.badgesObtained);
}

void StartupHandler::playProfessorMessage()
{
	int selection = NONE;

	m_menu->setRequestedData(&selection);
	m_menu->setCanLeave(false);
	m_menu->setscene(MenuScene::PROFESSOR_M);
	m_menu->preRun();

	m_dialogueRenderer->setDialogue("Test Prof Dialogue", "Lets See", true);
	while (m_dialogueRenderer->rendereringDialogue())
	{
		m_dialogueRenderer->renderDialogue();
		m_animator->updateRenderer();
	}

	m_menu->clearRequestedData();
	m_menu->postRun();
	m_menu->setCanLeave(true);
}
