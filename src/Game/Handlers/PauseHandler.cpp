#include "PauseHandler.h"

void PauseHandler::setup(Menu* menu, Trainer* player, Input* input, DataManager* dataManager, Renderer* renderer, CharacterMover* characterMover, Timer* timer, RosterDisplayData* rosterData)
{
	m_menu = menu;
	m_player = player;
	m_input = input;
	m_dataManager = dataManager;
	m_renderer = renderer;
	m_characterMover = characterMover;
	m_timer = timer;
	m_rosterData = rosterData;

	m_menu->setupPauseData(&m_items, &m_playerBalance, &m_playTime, m_rosterData, &m_badgeData, &m_pauseSettingData);
}

void PauseHandler::run()
{
	m_selection = NONE;
	m_menu->setCanLeave(true);
	m_menu->setscene(MenuScene::PAUSE_MENU);
	m_menu->setRequestedData(&m_selection);
	m_menu->preRun();

	m_playerBalance = std::to_string(m_player->getBalance());
	m_playTime = m_timer->getPlayTimeDisplay();
	setBadgeVisibility();

	while (true)
	{
		//system("CLS");
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		if (m_selection != NONE)
		{
			switch (m_selection)
			{
			case 0:
				handleRoster();
				break;
			case 1:
				handleItems();
				break;
			case 2:
				handleMap();
				break;
			case 3:
				handleSettings();
				break;
			case 4:
				handleSave();
				break;
			case 5:
				m_dataManager->saveGame();
				std::cout << "Game Saved!" << std::endl;
				exit(0);
				break;
			}

			m_selection = NONE;
			m_playTime = m_timer->getPlayTimeDisplay();
		}

	}

	m_menu->clearRequestedData();
	m_menu->resetScene(MenuScene::PAUSE_MENU);
	m_menu->postRun();

}

void PauseHandler::handleRoster()
{
	updateDisplayPokemon(m_player, m_rosterData);
	m_selection = NONE;
	int swapIndex = NONE;

	int hoveredIndex = -1;

	m_menu->preRun();
	while (true)
	{
		updateDisplayPokemonStats(&hoveredIndex, m_player, m_menu->getButtonIndex(), m_rosterData);
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			if (swapIndex == NONE)
			{
				m_menu->resetScene(MenuScene::PAUSE_ROSTER);
				m_menu->setscene(MenuScene::PAUSE_MENU);
				return;
			}
			else
			{
				swapIndex = NONE;
				continue;
			}
		}


		if (m_selection == NONE)
			continue;
		
		if (swapIndex != NONE)
		{
			Pokemon pokemon = m_player->getPokemon(swapIndex);
			m_player->setPokemon(swapIndex, m_player->getPokemon(m_selection));
			m_player->setPokemon(m_selection, pokemon);
			swapIndex = NONE;
		}
		else
			swapIndex = m_selection;
		
		m_selection = NONE;
	}
	m_menu->postRun();
}

void PauseHandler::handleItems()
{
	m_bagIndex = 0;
	m_selection = NONE;

	updatePlayerItems();	//TOOD: Finish Implementing


	m_menu->preRun();
	while (true)
	{
		//system("CLS");
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			m_menu->resetScene(MenuScene::PAUSE_BAG);
			return;
		}

		if (m_selection == NONE)
			continue;



	}

	m_menu->postRun();
}

void PauseHandler::handleSettings()
{
	m_selection = NONE;
	m_menu->preRun();
	m_input->updateKeyBinds(&m_pauseSettingData);
	m_renderer->adjustRenderSettings(&m_pauseSettingData);

	while (true)
	{
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			m_menu->resetScene(MenuScene::PAUSE_SETTINGS);
			m_menu->setscene(MenuScene::PAUSE_MENU);
			return;
		}
		
		if (m_selection == NONE)
			continue;

		if (m_selection < 16)
		{
			selectNewInput(ControlType::KEYBOARD);
			m_input->updateKeyBinds(&m_pauseSettingData);
		}
		else if (m_selection >= 21)
		{
			selectNewInput(ControlType::CONTROLLER_BUTTON);
			m_input->updateKeyBinds(&m_pauseSettingData);
		}
		else if (m_selection == 16)
		{
			selectResolution();
			m_renderer->adjustRenderSettings(&m_pauseSettingData);
		}
		else if (m_selection == 17)
		{
			m_renderer->toggleFullScreen();
			m_renderer->adjustRenderSettings(&m_pauseSettingData);
		}
		else if (m_selection == 18)
		{
			m_renderer->toggleShowFPS();
			m_renderer->adjustRenderSettings(&m_pauseSettingData);
		}

		m_selection = NONE;
	}
	m_menu->postRun();
}

void PauseHandler::handleMap()
{
}

void PauseHandler::handleSave()
{
	m_dataManager->saveGame();
	std::cout << "Game Has Been Saved!\n";
	//TODO: Overlay save complete pop up
	//system("pause");
}

void PauseHandler::selectResolution()
{
	m_selection = NONE;
	m_menu->setCanLeave(true);

	while (true)
	{
		
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		if (m_selection == NONE)
			continue;

		switch (m_selection)
		{
		case RendererResolutiion::_1280x720:
			m_renderer->setResolution(RendererResolutiion::_1280x720);
			break;
		case RendererResolutiion::_1920x1080:
			m_renderer->setResolution(RendererResolutiion::_1920x1080);
			break;
		case RendererResolutiion::_2560x1440:
			m_renderer->setResolution(RendererResolutiion::_2560x1440);
			break;
		default:
			break;
		}

		m_characterMover->setTileSize(m_renderer->getTileSize());
		break;
		
	}

	m_menu->setCanLeave(false);
}

void PauseHandler::selectNewInput(ControlType type)
{
	KeyPriority priority = KeyPriority::MAIN;
	InputRequest request = InputRequest::EMPTY;
	float currentDelay = 0.0f;
	float preSwapDelay = 0.02f;
	float postSwapDelay = 0.01f;

	if ((m_selection < 16 && m_selection % 2 == 1) || (m_selection >= 21 && m_selection % 2 == 0 ))
			priority = KeyPriority::ALT;

	int requestValue = m_selection;

	if (requestValue >= 21)
		requestValue -= 21;

	requestValue = (int)floor(requestValue / 2.0f);

	if (requestValue == 0)
		request = InputRequest::UP;
	else if (requestValue == 1)
		request = InputRequest::DOWN;
	else if (requestValue == 2)
		request = InputRequest::LEFT;
	else if (requestValue == 3)
		request = InputRequest::RIGHT;
	else if (requestValue == 4)
		request = InputRequest::SELECT;
	else if (requestValue == 5)
		request = InputRequest::BACK;
	else if (requestValue == 6)
		request = InputRequest::PAUSE;
	else if (requestValue == 7)
		request = InputRequest::SPRINT;

	while (currentDelay < preSwapDelay)
	{
		m_timer->onUpdate();
		currentDelay += m_timer->getDelta();
		m_menu->onUpdate();
	}

	while (m_input->changingInput(type, priority, request))
		m_menu->run();

	currentDelay = 0.0f;
	while (currentDelay < postSwapDelay)
	{
		m_timer->onUpdate();
		currentDelay += m_timer->getDelta();
		m_menu->onUpdate();
	}

	m_menu->setOverlay(MenuOverlay::NONE);
	m_selection = NONE;
}

//void PauseHandler::updateDisplayPokemons()
//{
//	Pokemon displayPokemon;
//
//	//TODO: For loop
//
//	if (m_player->getPokemon(0).getLevel() != 0)
//	{
//		displayPokemon = m_player->getPokemon(0);
//
//		m_rosterData.pokemon1.name = displayPokemon.getName();
//		m_rosterData.pokemon1.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) +" HP";
//		m_rosterData.pokemon1.level = "Lv" + std::to_string(displayPokemon.getLevel());
//		m_rosterData.pokemon1.pokemonTexture = pokemonFrontTexture(displayPokemon.getName());
//	}
//	else
//	{
//		m_rosterData.pokemon1.name = "NONE";
//		m_rosterData.pokemon1.hp = "";
//		m_rosterData.pokemon1.level = "";
//		m_rosterData.pokemon1.pokemonTexture = "";
//	}
//
//	if (m_player->getPokemon(1).getLevel() != 0)
//	{
//		displayPokemon = m_player->getPokemon(1);
//
//		m_rosterData.pokemon2.name = displayPokemon.getName();
//		m_rosterData.pokemon2.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
//		m_rosterData.pokemon2.level = "Lv" + std::to_string(displayPokemon.getLevel());
//		m_rosterData.pokemon2.pokemonTexture = pokemonFrontTexture(displayPokemon.getName());
//	}
//	else
//	{
//		m_rosterData.pokemon2.name = "NONE";
//		m_rosterData.pokemon2.hp = "";
//		m_rosterData.pokemon2.level = "";
//		m_rosterData.pokemon2.pokemonTexture = "";
//	}
//
//	if (m_player->getPokemon(2).getLevel() != 0)
//	{
//		displayPokemon = m_player->getPokemon(2);
//
//		m_rosterData.pokemon3.name = displayPokemon.getName();
//		m_rosterData.pokemon3.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
//		m_rosterData.pokemon3.level = "Lv" + std::to_string(displayPokemon.getLevel());
//		m_rosterData.pokemon3.pokemonTexture = pokemonFrontTexture(displayPokemon.getName());
//	}
//	else
//	{
//		m_rosterData.pokemon3.name = "NONE";
//		m_rosterData.pokemon3.hp = "";
//		m_rosterData.pokemon3.level = "";
//		m_rosterData.pokemon3.pokemonTexture = "";
//	}
//
//	if (m_player->getPokemon(3).getLevel() != 0)
//	{
//		displayPokemon = m_player->getPokemon(3);
//
//		m_rosterData.pokemon4.name = displayPokemon.getName();
//		m_rosterData.pokemon4.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
//		m_rosterData.pokemon4.level = "Lv" + std::to_string(displayPokemon.getLevel());
//		m_rosterData.pokemon4.pokemonTexture = pokemonFrontTexture(displayPokemon.getName());
//	}
//	else
//	{
//		m_rosterData.pokemon4.name = "NONE";
//		m_rosterData.pokemon4.hp = "";
//		m_rosterData.pokemon4.level = "";
//		m_rosterData.pokemon4.pokemonTexture = "";
//	}
//
//	if (m_player->getPokemon(4).getLevel() != 0)
//	{
//		displayPokemon = m_player->getPokemon(4);
//
//		m_rosterData.pokemon5.name = displayPokemon.getName();
//		m_rosterData.pokemon5.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
//		m_rosterData.pokemon5.level = "Lv" + std::to_string(displayPokemon.getLevel());
//		m_rosterData.pokemon5.pokemonTexture = pokemonFrontTexture(displayPokemon.getName());
//	}
//	else
//	{
//		m_rosterData.pokemon5.name = "NONE";
//		m_rosterData.pokemon5.hp = "";
//		m_rosterData.pokemon5.level = "";
//		m_rosterData.pokemon5.pokemonTexture = "";
//	}
//
//	if (m_player->getPokemon(5).getLevel() != 0)
//	{
//		displayPokemon = m_player->getPokemon(5);
//
//		m_rosterData.pokemon6.name = displayPokemon.getName();
//		m_rosterData.pokemon6.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
//		m_rosterData.pokemon6.level = "Lv" + std::to_string(displayPokemon.getLevel());
//		m_rosterData.pokemon6.pokemonTexture = pokemonFrontTexture(displayPokemon.getName());
//	}
//	else
//	{
//		m_rosterData.pokemon6.name = "NONE";
//		m_rosterData.pokemon6.hp = "";
//		m_rosterData.pokemon6.level = "";
//		m_rosterData.pokemon6.pokemonTexture = "";
//	}
//}

//void PauseHandler::displayPokemonStats(int* hoveredIndex)
//{
//	if (*hoveredIndex == m_menu->getButtonIndex())
//		return;
//
//	//system("CLS");
//	Pokemon displayPokemon = m_player->getPokemon( m_menu->getButtonIndex() );
//
//	//std::cout << displayPokemon.getName() << "\tLv." << displayPokemon.getLevel() << std::endl;
//	//std::cout << displayPokemon.getSpecies().name << std::endl;
//
//	//std::cout << "-----------------------\n";
//
//
//	m_pausePokemonData.attack = std::to_string(displayPokemon.getStats().attack);
//	m_pausePokemonData.defense = std::to_string(displayPokemon.getStats().defense);
//	m_pausePokemonData.spAttack = std::to_string(displayPokemon.getStats().spAttack);
//	m_pausePokemonData.spDefense = std::to_string(displayPokemon.getStats().spDefense);
//	m_pausePokemonData.speed = std::to_string(displayPokemon.getStats().speed);
//
//	formatMoveStringData(displayPokemon, &m_pausePokemonData.move1, 1);
//	formatMoveStringData(displayPokemon, &m_pausePokemonData.move2, 2);
//	formatMoveStringData(displayPokemon, &m_pausePokemonData.move3, 3);
//	formatMoveStringData(displayPokemon, &m_pausePokemonData.move4, 4);
//
//	setHighlightedPokemonHP(displayPokemon);
//
//	//std::cout << displayPokemon.getCurHealth() << "/" << displayPokemon.getStats().hp << std::endl;
//	//std::cout << "Attack : " << m_pausePokemonData.attack << std::endl;
//	//std::cout << "Defense: " << m_pausePokemonData.defense << std::endl;
//	//std::cout << "SP. ATK: " << m_pausePokemonData.spAttack << std::endl;
//	//std::cout << "SP. DEF: " << m_pausePokemonData.spDefense << std::endl;
//	//std::cout << "Speed  : " << m_pausePokemonData.speed << std::endl;
//	//
//	//std::cout << "-----------------------\n\n";
//	//std::cout << "Moves Learned\n";
//	//std::cout << getAttackFromID(displayPokemon.getMoveset().move1)->getName() << std::endl;
//	//std::cout << getAttackFromID(displayPokemon.getMoveset().move2)->getName() << std::endl;
//	//std::cout << getAttackFromID(displayPokemon.getMoveset().move3)->getName() << std::endl;
//	//std::cout << getAttackFromID(displayPokemon.getMoveset().move4)->getName() << std::endl;
//
//
//	*hoveredIndex = m_menu->getButtonIndex();
//
//	m_pokemonStringData.name = displayPokemon.getName();
//	m_pokemonStringData.level = "Lv" + std::to_string(displayPokemon.getLevel());
//	m_pokemonStringData.health = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp);
//	m_rosterTypings.string1 = g_typeTextureLocations[displayPokemon.getSpecies().type1];
//	m_rosterTypings.string2 = g_typeTextureLocations[displayPokemon.getSpecies().type2];
//}

void PauseHandler::updatePlayerItems()
{


	int count = 0;
	int indexCount = 0;

	for (auto i = m_player->getItemStorage()->getAllItems()->begin(); i != m_player->getItemStorage()->getAllItems()->end(); i++)
	{
		if (indexCount != m_bagIndex)
		{
			indexCount++;
			continue;
		}
		if (count == 6)
			break;
		if (i->second == 0)
			continue;


		switch (count)
		{
		case 0:
			formatRosterData(&m_items.string1, getItemFromID(i->first)->getName() + "x" + std::to_string(i->second));
			break;
		case 1:
			formatRosterData(&m_items.string2, getItemFromID(i->first)->getName() + "x" + std::to_string(i->second));
			break;
		case 2:
			formatRosterData(&m_items.string3, getItemFromID(i->first)->getName() + "x" + std::to_string(i->second));
			break;
		case 3:
			formatRosterData(&m_items.string4, getItemFromID(i->first)->getName() + "x" + std::to_string(i->second));
			break;
		case 4:
			formatRosterData(&m_items.string5, getItemFromID(i->first)->getName() + "x" + std::to_string(i->second));
			break;
		case 5:
			formatRosterData(&m_items.string6, getItemFromID(i->first)->getName() + "x" + std::to_string(i->second));
			break;
		}


		count++;
	}

	for (int i = count; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			formatRosterData(&m_items.string1, "NONE");
			break;
		case 1:
			formatRosterData(&m_items.string2, "NONE");
			break;
		case 2:
			formatRosterData(&m_items.string3, "NONE");
			break;
		case 3:
			formatRosterData(&m_items.string4, "NONE");
			break;
		case 4:
			formatRosterData(&m_items.string5, "NONE");
			break;
		case 5:
			formatRosterData(&m_items.string6, "NONE");
			break;
		}
	}


}

//void PauseHandler::formatMoveStringData(Pokemon displayPokemon, MoveStringData* data, int moveIndex)
//{
//	Attack* attack = nullptr;
//
//	if (moveIndex == 1)
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move1);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move1pp);
//	}
//	else if (moveIndex == 2)
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move2);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move2pp);
//	}
//	else if (moveIndex == 3)
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move3);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move3pp);
//	}
//	else
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move4);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move4pp);
//	}
//
//	if (attack->getName() != getAttackFromID(NONE)->getName())
//	{
//		data->moveName = attack->getName();
//		data->maxPP = std::to_string(attack->getPP());
//		data->moveTextureLocation = g_typeTextureLocations[attack->getType()];
//	}
//	else
//	{
//		data->moveName = "NONE";
//		data->currentPP = "0";
//		data->maxPP = "NONE";
//		data->moveTextureLocation = "";
//	}
//	
//}

void PauseHandler::setHighlightedPokemonHP(Pokemon displayPokemon)
{
	float maxPercent = 13.8f;

	m_pausePokemonData.hpPercent = maxPercent * ((float)displayPokemon.getCurHealth() / (float)displayPokemon.getStats().hp);
}

void PauseHandler::setBadgeVisibility()
{
	switch (m_player->getBadgeCount())
	{
	case 8:
		m_badgeData.dragonBadgeVisibility = true;
	case 7:
		m_badgeData.waterBadgeVisibility = true;
	case 6:
		m_badgeData.rockBadgeVisibility = true;
	case 5:
		m_badgeData.normalBadgeVisibility = true;
	case 4:
		m_badgeData.iceBadgeVisibility = true;
	case 3:
		m_badgeData.grassBadgeVisibility = true;
	case 2:
		m_badgeData.flyingBadgeVisibility = true;
	case 1:
		m_badgeData.fireBadgeVisibility = true;
		break;
	default:
		break;
	}
}
