#pragma once

#include "../../Graphics/PositionalData.h"
#include "../../Characters/Trainer/NPT.h"
#include "../../Characters/Pokemon/Pokemon.h"
#include "../../Battle/BattleSimulator.h"
#include "../../Characters/CharacterMover.h"
#include "../Interactions/PC.h"

class EncounterHandler
{
public:
	EncounterHandler() {};

	void setup(BattleSimulator* battleSimulator, MapHandler* mapHandler, Trainer* trainer, PC* pc, Menu* menu, CharacterMover* characterMover, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, Animator* animator, Renderer* renderer, Input* input, Timer* timer);

	void onUpdate();
private:
	void attemptPokemonEncounter();

	void addPokemon(Pokemon pokemon);

	bool inRangeOfPlayer(NPT* npt);

private:

	void spotPlayer();
	void moveAIToPlayer(NPT* npt);
	void playAiDialogue(NPT* npt);

private:

	BattleSimulator* m_battleSim = nullptr;
	CharacterMover* m_characterMover = nullptr;
	Trainer* m_player = nullptr;
	PC* m_pc = nullptr;
	MapHandler* m_mapHandler = nullptr;
	Animator* m_animator = nullptr;
	Renderer* m_renderer = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;

	Position m_lastPosition = Position{{-1,-1}};
};