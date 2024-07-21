#pragma once
#include "../../Characters/CharacterMover.h"
#include "../../Graphics/DialogueRenderer.h"

struct CutsceneInstruction
{
	Trainer* character;
	InstructionType type;
	Direction direction;
	Dialogue dialogue;
};

class Cutscene
{
public:
	Cutscene(){};

	Cutscene(MapHandler* mapHandler, CharacterMover* characterMover, Trainer* player, Renderer* renderer, DialogueRenderer* dialogueRenderer);

	void onUpdate();

	void setCurrentScene(CutSceneID scene) { m_currentScene = scene; };

	CutSceneID getCurrentScene() { return m_currentScene; };
private:

	void playCutscene();

	void initCutscenes();

private:

	void addCharacterToMover(CutsceneInstruction instruction);
	void moveCharacters();
	void displayDialogue(Dialogue dialogue);	//TODO: Maybe add a dialogue class


	CutSceneID m_currentScene = FIRST_CUTSCENE;

	MapHandler* m_mapHandler = nullptr;
	CharacterMover* m_characterMover = nullptr;
	Trainer* m_player = nullptr;
	Renderer* m_renderer = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;

	std::unordered_map<CutSceneID, std::vector<CutsceneInstruction>> m_cutscenes;
};