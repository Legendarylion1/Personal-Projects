#pragma once
#include "Attack.h"
#include "StatusChart.h"

namespace AttackIDs
{
	static const unsigned int null = 0;
	static const unsigned int struggle = 1;
	static const unsigned int punch = 2;
	static const unsigned int kick = 3;
	static const unsigned int lightningBolt = 4;
	static const unsigned int flameThrower = 5;
	static const unsigned int heavyKick = 6;
}


static Attack nullAttack("-", NORMAL, 0, 0, 0, 0, nullptr, AttackIDs::null);
static Attack struggle("Struggle", NORMAL, 5, 10, 500, 80, nullptr, AttackIDs::struggle);
static Attack punchAttack("Punch", NORMAL, 10, 20, 2, 100, nullptr, AttackIDs::punch);
static Attack kickAttack("Kick", NORMAL, 0, 20, 5, 100, nullptr, AttackIDs::kick);
static Attack lightningBolt("Lightning Bolt", WATER, 30, 60, 15, 100, nullptr, AttackIDs::lightningBolt);
static Attack flameThrower("Flamethrower", FIRE, 30, 20, 15, 50, &burn, AttackIDs::flameThrower);
static Attack heavyKick("Heavy Kick", NORMAL, 100, 20, 5, 50, nullptr, AttackIDs::heavyKick);

static std::unordered_map<unsigned int, Attack> id_to_attack ={

	{AttackIDs::null, nullAttack},
	{AttackIDs::struggle, struggle},

	{AttackIDs::punch, punchAttack},
	{AttackIDs::kick, kickAttack},
	{AttackIDs::lightningBolt, lightningBolt},
	{AttackIDs::flameThrower, flameThrower},
	{AttackIDs::heavyKick, heavyKick}
};