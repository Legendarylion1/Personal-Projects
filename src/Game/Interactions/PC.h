#pragma once
#include "../../Characters/Trainer/Trainer.h"
#include "../../Menu/Menu.h"
#include "../../Battle/Attack/Attack.h"


const static int NUMBER_OF_BOXES = 8;
const static int POKEMON_IN_BOX = 30;

class PC
{
public:
	PC(){};
	PC(Trainer* trainer, Menu* menu);

	bool addPokemon(Pokemon pokemon);

	Pokemon getPokemon(int box, int index) { return m_pcPokemon[box][index]; };
	void setPokemon(int box, int index, Pokemon pokemon) { m_pcPokemon[box][index] = pokemon; };
	void run();

private:
	void swapPokemon();

	void moveBoxRight();
	void moveBoxLeft();

	void displayBox();
	void displayPokemonStats();

	void getPokemonStatIndex();

	bool playerHasEnoughPokemon();
	bool isValidSelection();

private:
	int m_pokemonStatsIndex = 0;

	int m_currentBox = 0;
	int m_currentPokemonIndex = 0;

	int m_previousBox = 0;
	int m_previousPokemonIndex = 0;
	// 8 boxes
	// 5x6

	// Meun only needs images
	//	- We will need to add overlays to the menu
	//	- Only thing to be updated for the menu would be the textures in the future
	//	- Right now we only need to link the boxes and allow for selection
	//	- We can display everything else locally to the pc for now to allow for testing

	Pokemon m_pcPokemon[NUMBER_OF_BOXES][POKEMON_IN_BOX];
	Trainer* m_trainer = nullptr;
	Menu* m_menu = nullptr;



	///Requirements
	/// 
	/// [DONE]	Add pokemon to the PC
	/// [DONE]	Change the position of pokemon in the pc
	/// []		view the stats of the hovered pokemon in the pc
	/// [DONE]	move pokemon between roster and box
	/// [DONE]	switch between 8 boxes
	///

};