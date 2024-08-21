#pragma once

#include <unordered_map>
#include <algorithm>
#include "Attack/Attack.h"
#include "../Characters/Trainer/NPT.h"
#include "../Menu/Menu.h"
#include "../Graphics/DialogueRenderer.h"
#include "../Graphics/Animator.h"
#include "BattleAnimations.h"
#include "BattleFunctions/BattleAction.h"
#include "BattleFunctions/BattleDataSimulator.h"
#include "BattleFunctions/BattleDataGenerator.h"
#include "BattleFunctions/BattleExperience.h"

class Battle
{
public:

	void setup(Trainer* trainer, Menu* menu, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, Animator* animator, Renderer* renderer, Input* input, Timer* timer);

	void beginBattle(NPT* npt);
	Pokemon beginBattle(Pokemon pokemon);

private:

	void loadAnimations();

	void playBattle();
	bool battleOver();

	void rewardPlayer();
	void evolvePokemon();

	bool evolutionAnimated(int preEvolution, int postEvolution, std::string pokemonName);

	void shrinkEvolution(DynamicImageRenderData* evolutionData, float* animationSpeed, bool animate = true);
	void growEvolution(DynamicImageRenderData* evolutionData, float* animationSpeed);

	void changeEvolutionColor(DynamicImageRenderData* evolutionData, bool turnWhite);

	void renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick);
private:

	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;
	Pokemon m_wildPokemon;
	Menu* m_menu = nullptr;

	BattleAction m_battleAction;
	BattleDataGenerator m_dataGenerator;
	BattleDataSimulator m_dataSimulator;
	BattleFaintHandler m_faintHandler;

	BattleMenuGraphics m_battleMenuGraphics;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	Animator* m_animator = nullptr;
	Timer* m_timer = nullptr;


private:

	SimulationCommand m_playerCommand;
	SimulationCommand m_aiCommand;

	int m_playerPokemonIndex = 0;
	int m_opponentPokemonIndex = 0;
	int m_endCondition = NONE;
};