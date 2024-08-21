#pragma once

#include "../../Map/MapHandler.h"
#include "../../Menu/Menu.h"
#include "../Interactions/PC.h"
#include "../../Battle/Battle.h"

class InteractionHandler
{
public:
	InteractionHandler() {};

	void setup(Trainer* player, MapHandler* mapHandler, Menu* menu, PC* pc, Battle* battleSimulator, DialogueRenderer* dialogueRenderer, Renderer* renderer);

	void evaluateInteraction();
private:

	void nurseInteraction();
	void buyItems();
	void aiInteraction(Coordinate aiPosition);

private:

	void updateShopItems();
	void purchaseItem(int index);

	void turnAIToPlayer(NPT* npt);
	void renderDialogue(std::string topLine, std::string botLine, bool awaitClick);

private:

	Menu* m_menu = nullptr;
	Trainer* m_player = nullptr;
	MapHandler* m_mapHandler = nullptr;
	PC* m_pc = nullptr;
	Battle* m_battleSimulator = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	Renderer* m_renderer = nullptr;

	int m_itemIndex = 0;
	SharedString m_availableItems;
	std::string m_playerBalance;
};