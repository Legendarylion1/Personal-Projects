#pragma once


#include <stdlib.h>
#include <algorithm>
#include<windows.h>
#include "NPT.h"
#include "PC.h"
#include "Renderer.h"
#include "Input.h"

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

	void getPlayerAction();
	bool getAIAction();

	bool playerSelectedMove();
	bool playerSelecetedPokemon(bool fainted);
	bool playerSelectedItem();
	bool runSuccesful();

	bool handleFaint(Pokemon& pokemon);
	int calculateXPGain(Pokemon& pokemon);
	void animateXPGain(Pokemon* pokemon, int xpGain);

	int calculateDamageTaken(Pokemon& attackingPokemon, Pokemon& defendingPokemon, Attack& attack);
	void animateDamageTaken(Pokemon* pokemon, int damage);
	void giveStatus(Pokemon& defendingPokemon, Attack& attack);
	void evaluateStatus(Pokemon* pokemon);
	bool useItem(Trainer& trainer, Pokemon* pokemon, Item& item);

	void swapAIPokemon();
	void recordAttack();
	void removeAttackRecord();

	bool caughtPokemon(Item& item);
	bool healedPokemon(Item& item);
	bool appliedItem(Item& item);

	

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

	bool m_flee = false;

	std::vector< std::vector<int> > m_xpRecords;
};