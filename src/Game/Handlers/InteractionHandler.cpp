#include "InteractionHandler.h"

void InteractionHandler::setup(Trainer* player, MapHandler* mapHandler, Menu* menu, PC* pc, BattleSimulator* battleSimulator)
{
	m_player = player;
	m_mapHandler = mapHandler;
	m_menu = menu;
	m_pc = pc;
	m_battleSimulator = battleSimulator;

	m_menu->setupInteractionData(&m_availableItems, &m_playerBalance);
}

void InteractionHandler::evaluateInteraction()
{
	Coordinate interactionTile = m_player->position.coords;

	if (m_player->position.direction == Direction::UP)
		interactionTile.yTile += 1;
	else if (m_player->position.direction == Direction::DOWN)
		interactionTile.yTile -= 1;
	else if (m_player->position.direction == Direction::LEFT)
		interactionTile.xTile -= 1;
	else if (m_player->position.direction == Direction::RIGHT)
		interactionTile.xTile += 1;

	char tile = m_mapHandler->getTile(interactionTile);

	if (tile == 'N')
		nurseInteraction();
	else if (tile == 'I')
		buyItems();
	else if (tile == 'C')
		m_pc->run();
	else if (tile == 'A')
		aiInteraction(interactionTile);
}

void InteractionHandler::nurseInteraction()
{
	for (int i = 0; i < 6; i++)
	{
		m_player->getRoster()[i].fullRestore();
		Moveset moveset = m_player->getRoster()[i].getMoveset();
		
		if (moveset.move1 != NONE)
			moveset.move1pp = getAttackFromID(moveset.move1)->getPP();

		if (moveset.move2 != NONE)
			moveset.move2pp = getAttackFromID(moveset.move2)->getPP();

		if (moveset.move3 != NONE)
			moveset.move3pp = getAttackFromID(moveset.move3)->getPP();

		if (moveset.move4 != NONE)
			moveset.move4pp = getAttackFromID(moveset.move4)->getPP();


		m_player->getRoster()[i].setMoveset(moveset);
	}
	std::cout << "Pokemon have been healed" << std::endl;
}

void InteractionHandler::buyItems()
{
	//TODO: Probably add a cancel in menu
	m_playerBalance = "Balance: " + std::to_string(m_player->getBalance());

	m_itemIndex = 0;

	updateShopItems();

	int selection = NONE;

	m_menu->setRequestedData(&selection);
	m_menu->setscene(MenuScene::BUY_ITEMS);
	m_menu->setCanLeave(true);
	m_menu->preRun();

	while (selection == NONE)
	{
		//system("CLS");
		m_menu->run();
		if (m_menu->leaveRequested())
			break;

		if (selection != NONE)
		{
			if (selection == arrowDirections::UP && m_itemIndex != 0)
				m_itemIndex--;
			else if (selection == arrowDirections::DOWN && (size_t)(m_itemIndex + 6) < m_mapHandler->getAvailableItems().size())
				m_itemIndex++;
			else if (selection >= 0 && selection <= 5)
			{
				purchaseItem(selection);
			}

			selection = NONE;
			
		}
	}

	m_menu->setCanLeave(false);
	m_menu->clearRequestedData();
	m_menu->clearScenes();
	m_menu->postRun();

}

void InteractionHandler::aiInteraction(Coordinate aiPosition)
{

	NPT* ai = m_mapHandler->getAI(aiPosition);

	for (Dialogue dialogue : ai->getDialogue())
	{
		std::cout << dialogue.topLine << "\n" << dialogue.botLine << std::endl;
		system("pause");
	}

	if (ai == nullptr)
	{
		std::cout << "AI doesnt exist. Interaction Handler. Handle error. Position entered (" << aiPosition.xTile << "," << aiPosition.yTile << ")" << std::endl;
		exit(ErrorCodes::OUTSIDE_SCOPE);
	}
	

	if (ai->wantsToBattle())
	{
		m_battleSimulator->beginBattle(ai);


		//Check the winner

		//If the winner is AI then white out

		//If the winner is player then mark the AI as unable to fight. Maybe mark the AI in battle sim

		if (m_player->unableToBattle())
		{
			//Handle White out. Maybe set a flag for the game to handle white out 
		}
	}





	

}

void InteractionHandler::updateShopItems()
{
	std::vector<ItemID> items = m_mapHandler->getAvailableItems();

	int count = 0;
	int itemCount = 0;

	for (ItemID id : items)
	{
		if (itemCount != m_itemIndex)
		{
			itemCount++;
			continue;
		}

		if (count == 6)
			break;

		if (count == 0)
			m_availableItems.string1 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
		else if (count == 1)
			m_availableItems.string2 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
		else if (count == 2)
			m_availableItems.string3 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
		else if (count == 3)
			m_availableItems.string4 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
		else if (count == 4)
			m_availableItems.string5 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
		else if (count == 5)
			m_availableItems.string6 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());

		count++;
	}
}

void InteractionHandler::purchaseItem(int index)
{
	ItemID id = m_mapHandler->getAvailableItems().at(index + m_itemIndex);
	int itemCost = getItemFromID(id)->getCost();
	if (m_player->getBalance() >= itemCost)
	{
		m_player->reduceMoney(itemCost);
		m_playerBalance = "Balance: " + std::to_string(m_player->getBalance());
		m_player->addItem(id);
	}

}
