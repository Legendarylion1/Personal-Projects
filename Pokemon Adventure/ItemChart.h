#pragma once
#include "Items.h"

//TODO: No Item for pokemon.h

namespace itemIDs
{
	static const unsigned int pokeball = 0;
	static const unsigned int greatball = 1;
	static const unsigned int ultraball = 2;
	static const unsigned int revive = 3;
	static const unsigned int smallHeal = 4;
	static const unsigned int burnHeal = 5;
}

static Pokeball pokeball("Pokeball", 100, 1.0f, NOTYPE, itemIDs::pokeball);
static Pokeball greatball("Greatball", 300, 1.5f, NOTYPE, itemIDs::greatball);
static Pokeball ultraball("Ultraball", 500,  2.0f, NOTYPE, itemIDs::ultraball);

static Potion revive("Revive", 400, true, 0, nullptr, itemIDs::revive);
static Potion smallHeal("Small Heal", 50, false, 20, nullptr, itemIDs::smallHeal);
static Potion burnHeal("Burn Heal", 50, false, 0, &burn, itemIDs::burnHeal);

static std::unordered_map<unsigned int, Item> id_to_item = {

	{itemIDs::pokeball,pokeball},
	{itemIDs::greatball,greatball},
	{itemIDs::ultraball,ultraball},
	{itemIDs::revive,revive},
	{itemIDs::smallHeal,smallHeal},
	{itemIDs::burnHeal,burnHeal}

};