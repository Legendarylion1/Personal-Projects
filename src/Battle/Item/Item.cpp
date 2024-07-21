#include "Item.h"

Item::Item():
	m_id(ItemID::SMALL_POTION), m_cost(0)
{
}

Item::Item(std::string itemName, ItemID itemID, int cost)
{
	m_name = itemName;
	m_id = itemID;
	m_cost = cost;
}


std::vector<SimulationCommand> Item::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	return std::vector<SimulationCommand>();
}

std::vector<SimulationCommand> Pokeball::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	std::vector<SimulationCommand> allItemData;

	SimulationCommand itemData{};

	itemData.commander = commander;
	itemData.selection2 = pokemonIndex;
	itemData.type = SimulationType::ITEM;
	itemData.itemData.id = getID();
	itemData.itemData.pokeballData.isPokeball = true;


	int maxValue = (3 * pokemon->getStats().hp);
	int curValue = (2 * pokemon->getCurHealth());

	if (maxValue > 255)
	{
		maxValue = (int)floor(maxValue / 4.0f);
		curValue = (int)floor(curValue / 4.0f);

		if (maxValue == 0)
		{
			maxValue = 1;
			curValue = 1;
		}
	}

	float numerator = (maxValue - curValue) * m_captureRate;
	float denominator = maxValue * 1.0f;

	int catchChance = (int)((numerator / denominator) * 255);
	if (catchChance < 1)
		catchChance = 1;

	//TODO: Check for pokemon status
	// Sleep or Freeze is + 10
	// Paralyze, poison, burn + 5

	int randomValue = randomNumber(256);

	if (randomValue <= catchChance)
	{
		itemData.itemData.pokeballData.shakes = 3;
	}
	else
	{
		int shakeProbability = (int)((randomValue - catchChance) / 2.0f);
		if (shakeProbability < 1)
			shakeProbability = 1;
		for (int i = 0; i < 3; i++)
		{

			if (randomNumber(256) < shakeProbability)
				break;

			itemData.itemData.pokeballData.shakes += 1;
		}
	}

	if (itemData.itemData.pokeballData.shakes == 3)
		itemData.itemData.pokeballData.caught = true;

	allItemData.push_back(itemData);
	logger->log(LogLevel::INFO, "Item Data Created", "getItemData", "Pokeball");

	return allItemData;
}

std::vector<SimulationCommand> Heal::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	std::vector<SimulationCommand> allItemData;

	SimulationCommand itemData{};
	itemData.commander = commander;
	itemData.selection2 = pokemonIndex;
	itemData.type = SimulationType::ITEM;
	itemData.itemData.id = getID();


	if (m_revive)
		itemData.itemData.healAmount = int(pokemon->getStats().hp / 2.0f);
	int previous = itemData.itemData.healAmount;
	pokemon->adjustCurHealth(itemData.itemData.healAmount);


	if (pokemon->getCurHealth() + m_healingValue > pokemon->getStats().hp)
		itemData.itemData.healAmount += pokemon->getStats().hp - pokemon->getCurHealth();
	else
		itemData.itemData.healAmount += m_healingValue;

	pokemon->adjustCurHealth(itemData.itemData.healAmount - previous);

	

	//TODO: Test This
	allItemData.push_back(itemData);	//TODO: Generate a message for healing too


	if (pokemon->getMajorStatus()->id != StatusID::NO_STATUS && m_statusID != StatusID::NO_STATUS)
	{
		if (pokemon->getMajorStatus()->id == m_statusID || m_statusID == StatusID::ALL)
		{
			allItemData.push_back(getStatusFromID(pokemon->getMajorStatus()->id)->getCureCommand(pokemon, commander));
			pokemon->removeMajorStatus();
		}
	}

	

	logger->log(LogLevel::INFO, "Item Data Created", "getItemData", "Heal");
	return allItemData;
}

bool Heal::canBeUsedOnPokemon(Pokemon* pokemon)
{
	if (pokemon->getCurHealth() == 0 && m_revive == false)
		return false;

	if (pokemon->getMajorStatus()->id != StatusID::NO_STATUS && (m_statusID != StatusID::ALL || pokemon->getMajorStatus()->id != m_statusID) && m_healingValue == 0)
		return false;

	return true;
}

std::vector<SimulationCommand> StatBooster::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	std::vector<SimulationCommand> allItemData;

	SimulationCommand itemData{};

	itemData.commander = commander;
	itemData.selection2 = pokemonIndex;
	itemData.type = SimulationType::ITEM;
	itemData.itemData.id = getID();


	itemData.itemData.statsToBoost = m_statBoost;

	return allItemData;
}

bool StatBooster::canBeUsedOnPokemon(Pokemon* pokemon)
{
	if (pokemon->getCurHealth() > 0)
		return true;
	return false;
}