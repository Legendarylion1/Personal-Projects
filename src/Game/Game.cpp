#include "Game.h"

Game::Game()
{
	m_player = Trainer("Torin", CharacterID::PLAYER);

	m_menu = Menu(&m_input);
	m_mapHandler = MapHandler(&m_player, &m_renderer);
	m_characterMover = CharacterMover(&m_mapHandler, &m_timer);
	m_input = Input(&m_inputVariables);
	m_pc = PC(&m_player, &m_menu);		//TODO: Consider moving some data to the heap because compiler is yelling at me
	m_cutScene = Cutscene(&m_mapHandler, &m_characterMover, &m_player, &m_renderer, &m_dialogueRenderer);

	m_renderer.init(&m_player.position.coords, &m_timer);
	m_characterMover.setTileSize(m_renderer.getTileSize());

	//TODO: Clean up
	m_input.setup(m_renderer.getWindow(), m_pauseHandler.getPauseSettingData());
	m_menu.setup(&m_inputVariables, &m_renderer);
	m_dataManager.setup(&m_player, &m_pc, &m_mapHandler, &m_input, &m_renderer, &m_timer, &m_characterMover);
	m_encounterHandler.setup(&m_battlesimulator, &m_mapHandler, &m_player, &m_pc, &m_menu, &m_characterMover, &m_rosterData, &m_dialogueRenderer, &m_animator, &m_renderer, &m_input, &m_timer);
	m_interactionHandler.setup(&m_player, &m_mapHandler, &m_menu, &m_pc, &m_battlesimulator);
	m_pauseHandler.setup(&m_menu, &m_player, &m_input, &m_dataManager, &m_renderer, &m_characterMover, &m_timer, &m_rosterData);
	m_dialogueRenderer.setup(&m_menu, &m_input, &m_timer);	//TODO: Remove Timer From classes that dont need it
	m_mapHandler.setup();
	m_animator.setup(&m_renderer, &m_timer);
}

void Game::run()
{
	startUp();

	while (!m_renderer.shouldClose())
	{
		if (m_inputVariables.up)
		{
			m_characterMover.moveCharacter(&m_player, Direction::UP);
		}
		if (m_inputVariables.down)
		{
			m_characterMover.moveCharacter(&m_player, Direction::DOWN);
		}
		if (m_inputVariables.left)
		{
			m_characterMover.moveCharacter(&m_player, Direction::LEFT);
		}
		if (m_inputVariables.right)
		{
			m_characterMover.moveCharacter(&m_player, Direction::RIGHT);
		}
		if (m_inputVariables.interact)
		{
			m_interactionHandler.evaluateInteraction();
		}
		if (m_inputVariables.pause)
		{
			m_pauseHandler.run();
		}
		
		onUpdate();
	}

}

void Game::startUp()
{
	StartupHandler startupHandler = StartupHandler(&m_player, &m_dataManager, &m_menu, &m_timer, &m_input, &m_dialogueRenderer, &m_animator);
	startupHandler.run();

	m_timer.resetTimer();
	m_timer.countPlay(true);
}

void Game::onUpdate()
{
	//system("CLS");
	m_characterMover.onUpdate();
	m_cutScene.onUpdate();
	m_encounterHandler.onUpdate();
	m_mapHandler.onUpdate();
	m_player.onUpdate(&m_renderer);
	m_input.onUpdate();
	m_renderer.onUpdate();
}
