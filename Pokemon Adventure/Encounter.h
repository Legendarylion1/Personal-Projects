#pragma once

//TODO: Change the order and grouping of functions

#include <stdlib.h>
#include <algorithm>
#include<windows.h>
#include "NPT.h"
#include "PC.h"
#include "Renderer.h"
#include "Input.h"

static enum battleActions
{
	FIGHT,
	POKEMON,
	HEAL,
	MISC,
	POKEBALL,
	FLEE
};

class Encounter
{
public:
	Encounter();

	bool setup(GLFWwindow* window, Renderer* renderer, Input* input, bool* clicked, double* mouseX, double* mouseY);

	void setupEncounter(Trainer& trainer, NPT& npt);
	void setupEncounter(Trainer& trainer, Pokemon& pokemon, PC& pc);

	void beginEncounter();
	void clearEncounter();
	void awaitClick();

	void onUpdate();
private:

	bool battleEnded();

	void getPlayerAction();
	bool getAIAction();

	void simulateActions();


	void simulateCombat();
	void simulatePlayerAttack();
	void simulateAIAttack();

	bool fleeSuccessful();

	void swapPlayerPokemon();
	void useItem(bool playerItem);

	bool playerSelectedMove();
	bool playerSelecetedPokemon(bool mainAction);
	bool playerSelectedItem();
	bool playerSelectedFlee();

	bool pokemonFainted(Pokemon* pokemon);
	int calculateXPGain(Pokemon& pokemon);
	void animateXPGain(Pokemon* pokemon, int xpGain);

	void replacePlayerPokemon();
	bool AIOutOfPokemon();

	int calculateDamageTaken(Pokemon& attackingPokemon, Pokemon& defendingPokemon, Attack& attack);
	void animateDamageTaken(Pokemon* pokemon, int damage);
	void giveStatus(Pokemon& defendingPokemon, Attack& attack);
	void evaluateStatus(Pokemon* pokemon);
	bool useItem(Trainer& trainer, Pokemon* pokemon, Item& item);
	void findItemType(int pokeballCount, int healCount, int miscCount);

	void swapAIPokemon();
	void recordAttack();
	void removeAttackRecord();
	void recordLevelUp();

	void checkEvolutions();
	void awardPlayer();

	bool caughtPokemon();
	bool healedPokemon(unsigned int pokeballCount);
	bool appliedItem(Item& item);

	bool canUseItem(Pokemon* pokemon, Item& item);
	bool canCatchPokemon();

	bool mouseOverFightOption();
	bool mouseOverPokemonOption();
	bool mouseOverItemOption();
	bool mouseOverFleeOption();

	bool mouseOverItem(bool isX, int boxNumber = 0);

private:
	GLFWwindow* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	Input* m_input = nullptr;

	bool* m_clicked = nullptr;
	double* m_mouseX = nullptr;
	double* m_mouseY = nullptr;

private:

	PC* m_pc = nullptr;
	Trainer* m_activeTrainer = nullptr;
	NPT* m_activeNPT = nullptr;

	Pokemon* m_activeTrainerPokemon = nullptr;
	Pokemon* m_activeAIPokemon = nullptr;

	unsigned int m_trainerPokemonIndex = 0;
	unsigned int m_AIPokemonIndex = 0;

	battleActions m_playerAction = FIGHT;
	battleActions m_aiAction = FIGHT;

	unsigned int m_playerActionIndex = 0;
	unsigned int m_aiActionIndex = 0;

	unsigned int m_selectionIndex = 0;

	bool m_flee = false;

	std::vector< std::vector<int> > m_xpRecords;
	std::vector<unsigned int> m_evolutionIndexes;
};