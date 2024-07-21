#pragma once

#include "../../Map/MapHandler.h"
#include "../../Menu/Menu.h"
#include "../Interactions/PC.h"
#include "../../Battle/BattleSimulator.h"

class InteractionHandler
{
public:
	InteractionHandler() {};

	void setup(Trainer* player, MapHandler* mapHandler, Menu* menu, PC* pc, BattleSimulator* battleSimulator);

	void evaluateInteraction();
private:

	void nurseInteraction();
	void buyItems();
	void aiInteraction(Coordinate aiPosition);

private:

	void updateShopItems();
	void purchaseItem(int index);

private:

	Menu* m_menu = nullptr;
	Trainer* m_player = nullptr;
	MapHandler* m_mapHandler = nullptr;
	PC* m_pc = nullptr;
	BattleSimulator* m_battleSimulator = nullptr;

	int m_itemIndex = 0;
	SharedString m_availableItems;
	std::string m_playerBalance;
};