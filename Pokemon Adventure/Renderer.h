#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TextRenderer.h"
#include "VBO.h"

#include "NPT.h"
#include "SpeciesChart.h"

 
const static float WIDTH = 1920.0f;
const static float HEIGHT = 1080.0f;

const static unsigned int POKEMON_SHEET_COLS = 1;
const static unsigned int POKEMON_SHEET_ROWS = 1;
const static float POKEMON_SHEET_COL_SIZE = 1 / POKEMON_SHEET_COLS;
const static float POKEMON_SHEET_ROW_SIZE = 1 / POKEMON_SHEET_ROWS;




//Box Data
const unsigned int boxesWide = 5;
const unsigned int boxesTall = 4;

const unsigned int boxX = 200;
const unsigned int boxY = 700;

const unsigned int boxWidth = 200;
const unsigned int boxHeight = 100;

const unsigned int hSpacing = boxWidth + 50;
const unsigned int vSpacing = boxHeight + 50;

const unsigned int vDataPoints = 32;
const unsigned int iDataPoints = 6;

// Player Roster Data
const float playerPokemonStartingX = 1500.0f;
const float playerPokemonStartingY = 600.0f;

const unsigned int playerPokemonWidth = 150;
const unsigned int playerPokemonHeight = 100;

const unsigned int playerHSpacing = playerPokemonWidth + 10;
const unsigned int playerVSpacing = playerPokemonWidth + 10;

// Box Banner
const unsigned int bannerCenterX = 960;
const unsigned int bannerCenterY = 980;
const unsigned int bannerWidth = 300;
const unsigned int bannerHeight = 50;
const unsigned int boxBannerVertices = 32;
const unsigned int boxBannerIndices = 6;


// Data Calculations
const unsigned int verticeCount = (boxesWide * boxesTall * vDataPoints) + boxBannerVertices;
const unsigned int pokemonVerticeCount = (boxesWide * boxesTall * vDataPoints);

const unsigned int indiceCount = (boxesWide * boxesTall * iDataPoints) + boxBannerIndices;
const unsigned int pokemonIndiceCount = (boxesWide * boxesTall * iDataPoints);



//TODO: Turn this into a namespace
const static unsigned int BLACKSCREEN		= 0;
const static unsigned int DEFAULT_ENCOUNTER = 1;
const static unsigned int SELECT_ATTACK		= 2;
const static unsigned int SELECT_POKEMON	= 3;
const static unsigned int SELECT_ITEM		= 4;
const static unsigned int DISPLAY_MAP		= 5;
const static unsigned int DISPLAY_ESCAPE	= 6;
const static unsigned int DISPLAY_PC		= 7;
const static unsigned int DISPLAY_BUY_ITEMS	= 8;

namespace SpriteState
{
	static unsigned int STEP1 = 0;
	static unsigned int IDLE = 1;
	static unsigned int STEP2 = 2;
}

class Renderer
{
public:
	void setup(GLFWwindow* window);

	
	void setState(unsigned int newState);
	void setTrainer(Trainer* trainer);
	void setPokemon(Pokemon* playerPokemon, Pokemon* opponentPokemon);
	void setBagIndex(unsigned int index);
	void setTextBox(std::string topLine, std::string bottomLine);
	void setAwaitClick(bool awaitClick);
	void setMapStats(std::string texturePath, int width, int height);
	void setPlayerState(float playerX, float playerY, unsigned int walkDirection, unsigned int walkState);
	void setPlayerCoords(float playerX, float playerY);
	void setPlayerAnimation(unsigned int walkDirection, unsigned int walkState);
	void setGrassPosition(int x, int y);
	void setRosterIndex(unsigned int index);
	void setEncounter(bool inEncounter);
	void setAiPositions(std::vector<NPT>* aiTrainers);
	void setRosterSize(unsigned int rosterSize);
	void setBoxPokemon(std::vector<Pokemon> newBox);
	void setBoxName(std::string boxName);
	void setAvailableItems(std::vector<std::string> availableItems);
	void setExclamationSize(unsigned int size);
	void setExclamationPos(glm::vec2 pos);
	void onUpdate();

	void shutdown();

private:
	void drawDefaultEncounter();
	void drawAttacks();
	void drawPokemonSelect();
	void drawItems();
	void drawDownArrow();
	void drawPlayer();
	void drawGrass();
	void drawAI();
	void drawPokeCenterPokeballs();
	void drawPC();
	void drawBuyItems();
	void drawPCPokemon(GLfloat vertices[640], GLuint indices[120]);
	void drawExclamation();
	void drawTrainerDialogue();

	void drawEscapeMenu();

	void drawMap();
	void positionCamera(glm::vec3 translate);

private:
	GLFWwindow* m_window = nullptr;
	Shader m_shader;
	TextRenderer m_textRenderer;

	Trainer* m_trainer = nullptr;
	Pokemon* m_playerPokemon = nullptr;
	Pokemon* m_opponentPokemon = nullptr;

	unsigned int m_state = 0;
	unsigned int m_bagIndex = 0;
	unsigned int m_rosterIndex = 7;
	unsigned int m_rosterSize = 0;

	bool m_inEncounter = false;
	bool m_awaitClick = false;

	std::string m_topLine;
	std::string m_botLine;

	std::vector<NPT>* m_aiSprites;
	std::vector<std::string> m_availableItems;

	

private:
	Texture m_mapTexture;
	Texture m_playerTexture;
	Texture m_aiTexture;
	Texture m_grassTexture;
	Texture m_pokeballTexture;
	Texture m_boxTexture;
	Texture m_buyMenuTexture;
	Texture m_exclamationTexture;

	float m_backgroundWidth = 0;
	float m_backgroundHeight = 0;

	unsigned int playerWalkingDirection = 0;
	unsigned int playerWalkingState = 0;

	float m_playerX = 0;
	float m_playerY = 0;

	bool m_inGrass = false;
	std::vector<glm::vec2> m_grassPositions = {glm::vec2(-1.0f,-1.0f) };

	std::vector<Pokemon> m_boxPokemon;

	std::string m_boxName;

	unsigned int m_exclamationSize = 0;
	glm::vec2 m_exclamationPosition = glm::vec2(0.0f, 0.0f);

	glm::vec3 m_camPosition = glm::vec3(0.0f, 0.0f, 0.0f);

private:
	void setupPokemonRenderPositions();

	void drawFightingPokemon();
	void drawBackGroundBlur();
	void drawTextBox();
};