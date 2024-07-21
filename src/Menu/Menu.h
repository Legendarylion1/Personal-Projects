#pragma once

#include "Scene.h"
#include "menuData.h"
#include "../GlobalData/helperFunctions.h"
#include <unordered_map>
#include "../Game/Input/Input.h"

/*

							Menu
							----

Buttons
	- Buttons Link to screens
	- Buttons Manipulate data
	- Buttons can close Menu
	- We remember previous button in the case of a one to many relationship
	- Buttons link to other buttons
	- Buttons need to highlight themselves if selected
		- They need to know if they are selected

Screens
	- Screens are a collection of buttons
	- Screens may have a background
	- Screens get stored in vector
	- If a button isnt selected but the user wants to go to a previous screen then we pop screens
	- If there is no previous screen then we can close the menu
	- Maybe have an option for no menu close without button press

Overlay
	- Overlays are like the screens
	- Overlays display over the current screen
	- No overlays on overlays. Menu screens should be designed so that we do not need overlays on overlays
	- Overlays are also comprised of buttons
	- Back pressed on an overlay closes the overlay in favor of the screen
*/

namespace arrowDirections
{
	const static int UP = -2;
	const static int DOWN = -3;
	const static int LEFT = -4;
	const static int RIGHT = -5;
}

class Menu
{
public:
	Menu(){};
	Menu(Input* input):m_input(input) {};
	~Menu();

	void setup(InputVariables* inputVariables, Renderer* renderer) { 
		m_inputVariables = inputVariables;
		m_renderer = renderer;
	};

	void setupDialogueRenderer(SharedString* dialogueText);
	void setupKeyboard(AlphabetStringData* alphabet, std::string* input);
	void setupIntroData(bool* studioVisible, bool* pressAnyButtonVisible);
	void setupStartupData(SharedString* header1, SharedString* header2, SharedString* header3, bool* f1Visible, bool* f2Visible, bool* f3Visible);
	void setupBattleData(SharedString* moves, SimulationCommand* menuCommand, RosterDisplayData* rosterData, ItemDisplayData* battleItemData, BattlePokemonData* battleData, DynamicImageRenderData* playPokemon, DynamicImageRenderData* oppPokemon);
	void setupInteractionData(SharedString* items, std::string* balance);
	void setupPauseData(SharedString* items, std::string* balance, std::string* time, RosterDisplayData* rosterData, TrainerBadgeData* badgeData, PauseSettingsData* settingData);

	void setscene(MenuScene scene);
	void setOverlay(MenuOverlay overlay);
	void setCanLeave(bool canLeave) { m_canLeave = canLeave; };
	void setRequestedData(int* data) { m_requestedData = data; };
	void setOverlayBackground(MenuOverlay overlay, ImageRenderData* data) { m_overlays[overlay].setOverlayBackground(data); };

	void clearRequestedData() { m_requestedData = nullptr; };
	void clearScenes() { m_previousScreens.clear(); };

	bool leaveRequested() { return m_leaveRequested; };
	void resetScene(MenuScene scene) { m_scenes[scene].reset(); };
	void resetOverlay(MenuOverlay overlay) { m_overlays[overlay].reset(); };

	int getButtonIndex() { return m_scenes[m_currentScene].getButtonIndex(); };
	MenuScene getCurrentScene() { return m_currentScene; };

	void preRun() { m_input->setCanHoldInput(false); };
	void run();
	void postRun() { m_input->setCanHoldInput(true); };

	void onUpdate();
	void renderMenu();

private:

	bool handleSelection(Button* button);
	bool handleLeave();

private:
	SimulationCommand* m_menuCommand = nullptr;
	InputVariables* m_inputVariables = nullptr;
	Renderer* m_renderer = nullptr;
	Input* m_input = nullptr;

private:
	bool m_canLeave = false;
	int* m_requestedData = nullptr;
	bool m_leaveRequested = false;

	MenuScene m_currentScene = MenuScene::NONE;
	MenuOverlay m_currentOverlay = MenuOverlay::NONE;

	std::vector<MenuScene> m_previousScreens;
	std::unordered_map<MenuScene, Scene> m_scenes;
	std::unordered_map<MenuOverlay, Overlay> m_overlays;
};