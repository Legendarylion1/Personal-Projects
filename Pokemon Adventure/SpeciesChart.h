#pragma once
#include "Pokemon_Species.h"
#include "TypeChart.h"
#include "AttackChart.h"

namespace speciesIDs
{
	static const unsigned int charmander = 0;
	static const unsigned int charmeleon = 1;
	static const unsigned int torchic = 2;
}


struct pokemonRenderData
{
	unsigned int sheetNumber;
	unsigned int sheetIndex;
	float xCoord;
	float yCoord;
};

//For reference weedle is 39 xp yield and about 300 for fully evolved pokemon
const static Pokemon_Species charmeleon("Charmeleon", speciesIDs::charmeleon, std::unordered_map<int, Pokemon_Species> {}, std::unordered_map<int, Attack>{}, FIRE, NOTYPE, 80, 110, 60, 60, 65, 150);
const static Pokemon_Species charmander("Charmander", speciesIDs::charmander, std::unordered_map<int, Pokemon_Species> { {7, charmeleon}}, std::unordered_map<int, Attack>{ {2, id_to_attack[AttackIDs::heavyKick]}, { 3, id_to_attack[AttackIDs::lightningBolt]} }, FIRE, NOTYPE, 62, 100, 50, 50, 55, 200);
const static Pokemon_Species torchic("Torchic", speciesIDs::torchic, std::unordered_map<int, Pokemon_Species> {}, std::unordered_map<int, Attack>{ {2, id_to_attack[AttackIDs::flameThrower]}, { 3, id_to_attack[AttackIDs::lightningBolt] } }, GRASS, NOTYPE, 62, 80, 50, 50, 60, 200);

static std::unordered_map<unsigned int, Pokemon_Species> id_to_species = {

	{speciesIDs::charmander, charmander},
	{speciesIDs::charmeleon, charmeleon},
	{speciesIDs::torchic, torchic}
};

static std::unordered_map<unsigned int, pokemonRenderData> species_render_data =
{
	{speciesIDs::charmander, pokemonRenderData{1,0}},
	{speciesIDs::charmeleon, pokemonRenderData{1,0}},
	{speciesIDs::torchic, pokemonRenderData{1,0}}
};

static std::unordered_map<unsigned int, const char *> species_Sheets_Front =
{
	{1,"Images/Pokemon/Front_Sheet_1.png"}
};

static std::unordered_map<unsigned int, const char*> species_Sheets_Back =
{
	{1,"Images/Pokemon/Back_Sheet_1.png"}
};