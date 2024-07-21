#pragma once

#include "../../Characters/Pokemon/Pokemon.h"
#include "../Status/Status.h"

#include "../SimulationCommands.h"
#include <string>
#include <unordered_map>

class Item
{
public:
	Item();
	Item(std::string itemName, ItemID itemID, int cost);

	virtual std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);
	virtual bool canBeUsedOnPokemon(Pokemon* pokemon) { return false; };
	virtual int getHealingValue() { return 0; };
	virtual StatusID getStatus() { return StatusID::NO_STATUS; };

	std::string getName() { return m_name; };
	ItemID getID() { return m_id; };
	int getCost() { return m_cost; };
	
private:
	std::string m_name;
	ItemID m_id;
	int m_cost;
};

class Pokeball : public Item
{
public:
	explicit Pokeball() : Item(), m_captureRate(255) {};
	explicit Pokeball(std::string itemName, ItemID itemID, int cost, float captureRate) : Item(itemName, itemID, cost) { m_captureRate = captureRate; };

	std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);


private:
	float m_captureRate;
};

class Heal : public Item
{
public:
	explicit Heal() : Item() {};
	explicit Heal(std::string itemName, ItemID itemID, int cost, int flatHeal, bool revive, StatusID status = StatusID::NO_STATUS)
		: Item(itemName, itemID, cost), m_healingValue(flatHeal), m_statusID(status), m_revive(revive) {};

	std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);
	bool canBeUsedOnPokemon(Pokemon* pokemon);
	StatusID getStatus() { return m_statusID; };

private:
	int m_healingValue;
	bool m_revive;
	StatusID m_statusID;
};

class StatBooster : public Item
{
public:
	explicit StatBooster() : Item() {};
	explicit StatBooster(std::string itemName, ItemID itemID, int cost, PokemonStats statBoost) : Item(itemName, itemID, cost) { m_statBoost = statBoost; };

	std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);
	bool canBeUsedOnPokemon(Pokemon* pokemon);

private:
	PokemonStats m_statBoost = PokemonStats();
};

static Heal smallPotion("Small Potion", ItemID::SMALL_POTION, 100, 10, false);
static Heal mediumPotion("Medium Potion", ItemID::MEDIUM_POTION, 200, 20, false);
static Heal largePotion("Large Potion", ItemID::LARGE_POTION, 300, 50, false);

static Pokeball pokeball("Pokeball", ItemID::POKEBALL, 100, 1.0f);
static Pokeball greatball("GreatBall", ItemID::GREATBALL, 200, 1.5f);
static Pokeball ultraball("UltraBall", ItemID::ULTRABALL, 300, 2.0f);
static Pokeball masterball("MasterBall", ItemID::MASTERBALL, 0, 2.0f);

static StatBooster roidJuice("RoidJuice", ItemID::ROID_JUICE, 50, { 0, StatBoost::SHARP_INCREASE, 0, 0, 0, 0, 0, 0 });

static std::unordered_map<ItemID, Item*> id_to_item
{
	{ItemID::SMALL_POTION, &smallPotion},
	{ItemID::MEDIUM_POTION, &mediumPotion},
	{ItemID::LARGE_POTION, &largePotion},
	{ItemID::POKEBALL, &pokeball},
	{ItemID::GREATBALL, &greatball},
	{ItemID::ULTRABALL, &ultraball},
	{ItemID::MASTERBALL, &masterball},
	{ItemID::ROID_JUICE, &roidJuice}
};

static Item* getItemFromID(ItemID id)
{
	try
	{
		return id_to_item[id];
	}
	catch (...)
	{
		logger->log(LogLevel::CRITICAL, "Unable to retrieve item with unkown ID", "getItem");
		logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
	}
	//TODO: Error out
}

static bool isPokeball(Item item)
{
	switch (item.getID())
	{
	case ItemID::POKEBALL:
	case ItemID::GREATBALL:
	case ItemID::ULTRABALL:
	case ItemID::MASTERBALL:
		return true;
	default:
		return false;
	}
}