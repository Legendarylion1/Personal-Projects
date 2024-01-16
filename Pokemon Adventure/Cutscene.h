#pragma once
#include "Renderer.h"
#include "NPT.h"
#include "MapSection.h"
#include "Encounter.h"	//TODO: Remove encounter from here. Its only here because of await click. Await click doesnt even need to be in encounter. Make it global or inside of input
#include "Animation.h"


//TODO: Entire class needs refactoring
class Cutscene
{
public:
	Cutscene();

	void setup(Renderer* renderer, Encounter* encounter, bool* fasterText);

	void setCutsceneCount(unsigned int count);
	unsigned int getCutsceneCount();

	void renderRouteTransition(Renderer& renderer, std::string title, bool toTown);
	bool storyCutscene(MapSection& mapSection);

	
	void spottedTrainer(NPT& npt, unsigned int trainerTileX, unsigned int trainerTileY);
	void nptDialogue(NPT& npt);
	//TODO: Alpha controls for screen transitioning (Fade in scenes - GPU Alpha)

private:
	bool isCutScene();
	void evaluateCutscene(std::string cutsceneEvent, int value);

	void moveNPTUp(NPT& npt);
	void moveNPTDown(NPT& npt);
	void moveNPTLeft(NPT& npt);
	void moveNPTRight(NPT& npt);

	void cutsceneDialogue();
	void resetAIPositions();

	void displayExclamation(float xPos, float yPos);

private:

	std::unordered_map<unsigned int, unsigned int> m_speakIndex = {};

	Renderer* m_renderer = nullptr;
	MapSection* m_mapSection = nullptr;
	Encounter* m_encounter = nullptr;	//TODO: PLEASE PLEASE PLEASE GET THIS OUT OF HERE. IT DOES NOT BELONG. Im only using it for await click

	unsigned int m_cutsceneCount = 0;
	unsigned int m_aiIndex = 0;

	float m_playerSpeed = 4.0f;	//TODO: Make this a pointer to real player speed
	float m_textWriteSpeed = 5.0f;

	bool* m_fasterText = nullptr;
};