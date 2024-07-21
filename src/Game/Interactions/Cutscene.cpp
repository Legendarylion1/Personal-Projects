#include "Cutscene.h"

Cutscene::Cutscene(MapHandler* mapHandler, CharacterMover* characterMover, Trainer* player, Renderer* renderer, DialogueRenderer* dialogueRenderer)
{
	m_mapHandler = mapHandler;
	m_characterMover = characterMover;
	m_player = player;
	m_renderer = renderer;
	m_dialogueRenderer = dialogueRenderer;

	initCutscenes();
}

void Cutscene::onUpdate()
{
	if (m_player->getMovingStatus() != MovingStatus::STOPPED)
		return;

	if (m_mapHandler->getTile(m_player->position.coords) != 'U')
		return;

	if (m_mapHandler->getCutsceneID(m_player->position.coords) != m_currentScene)
		return;

	playCutscene();
}

void Cutscene::playCutscene()
{
	m_characterMover->setPriorityOnly(true);

	for (CutsceneInstruction instruction : m_cutscenes[m_currentScene])
	{
		if (instruction.type == InstructionType::MOVE || instruction.type == InstructionType::TURN)
			addCharacterToMover(instruction);
		else if (instruction.type == InstructionType::PLAY)
			moveCharacters();
		else
			displayDialogue(instruction.dialogue);
	}

	m_characterMover->setPriorityOnly(false);

	m_currentScene = (CutSceneID)((int)m_currentScene + 1);
}

void Cutscene::initCutscenes()
{
	CutsceneInstruction instruction1;

	std::vector<CutsceneInstruction> instructions =
	{
		{m_player, InstructionType::TURN, Direction::LEFT, {}},
		{m_player, InstructionType::PLAY},
		{m_player, InstructionType::MOVE, Direction::LEFT, {}},
		{m_player, InstructionType::PLAY},
		{m_player, InstructionType::MOVE, Direction::LEFT, {}},
		{m_player, InstructionType::PLAY},
		{m_player, InstructionType::MOVE, Direction::LEFT, {}},
		{m_player, InstructionType::PLAY},
		{m_player, InstructionType::TURN, Direction::UP, {}},
		{m_player, InstructionType::PLAY},
		{m_player, InstructionType::MOVE, Direction::UP, {}},
		{m_player, InstructionType::PLAY},
		//{m_mapHandler->getAI(0), InstructionType::DIALOGUE, Direction::DOWN, {"Hey Where are you going","Stop Running"}}
	};


	m_cutscenes[CutSceneID::FIRST_CUTSCENE] = instructions;
}

void Cutscene::addCharacterToMover(CutsceneInstruction instruction)
{
	m_characterMover->moveCharacter(instruction.character, instruction.direction);
}

void Cutscene::moveCharacters()
{
	m_mapHandler->onUpdate();
	m_player->onUpdate(m_renderer);
	m_renderer->onUpdate();

	while (!m_characterMover->priorityQueueEmpty())
	{
		m_characterMover->onUpdate();
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_renderer->onUpdate();
	}
	
}

void Cutscene::displayDialogue(Dialogue dialogue)
{
	std::cout << dialogue.topLine << "\n" << dialogue.botLine << std::endl;

	m_dialogueRenderer->setDialogue(dialogue.topLine, dialogue.botLine, true);

	while (m_dialogueRenderer->rendereringDialogue())
	{
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_dialogueRenderer->renderDialogue();
		m_renderer->onUpdate();
	}
}
