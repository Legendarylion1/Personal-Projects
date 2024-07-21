#pragma once

#include <String>
#include <vector>
#include <unordered_map>

#include "../Status/Status.h"

enum class DamageType
{
	PHYSICAL,
	SPECIAL
};

//TODO: Consider adding priority moves. We currently have none

class Attack
{

public:
	explicit Attack(std::string name,Type type, DamageType damageType, int power, int pp, int critChance, int accuracy);
	Attack() {};

	std::string getName() { return m_name; };
	Type getType() { return m_type; };
	DamageType getPowerType() { return m_damageType; };	//TODO: Rename Damage to power for consistency
	int getPower() { return m_power; };
	int getPP() { return m_pp; };
	int getCritChance() { return m_critChance; };
	int getAccuracy() { return m_accuracy; };

	int calculateAttackDamage(Pokemon* attacker, Pokemon* defender, Attack* attack, bool applyDamage = false, AttackCommand* command = nullptr);
public:
	SimulationCommand getMissedAttackData(Pokemon* attacker, SelectedUser commander);
	SimulationCommand getNotEffectedData(Pokemon* defender, SelectedUser commander);

	virtual std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	virtual int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 0; };
	virtual StatusID getStatus() { return StatusID::NO_STATUS; };
	virtual PokemonStats getPlayerStat() { return PokemonStats{0,0,0,0,0,0,0,0}; };
	virtual PokemonStats getOpponentStat() { return PokemonStats{0,0,0,0,0,0,0,0}; };
	virtual int getPotentialDamage(Pokemon* attacker, Pokemon* defender) { return calculateAttackDamage(attacker, defender, this); };

private:
	std::string m_name;

	Type m_type = Type::NORMAL;
	DamageType m_damageType = DamageType::PHYSICAL;
	int m_power = 0;
	int m_pp = 0;
	int m_critChance = 0;
	int m_accuracy = 0;
};





//									~ All Attack Classes ~ 
class HyperFang : public Attack
{
public:
	explicit HyperFang(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
};

class Ember : public Attack
{
public:
	explicit Ember(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 40; };
	StatusID getStatus() { return StatusID::BURN; };
};

class BoneRush : public Attack
{
public:
	explicit BoneRush(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	int getPotentialDamage(Pokemon* attacker, Pokemon* defender);
};

class TorpidPunch : public Attack
{
public:
	explicit TorpidPunch(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 100 - (int)(100 * (defender->getCurHealth() / (float)defender->getStats().hp)); };
	StatusID getStatus() { return StatusID::SLEEP; };
};

class GetPumped : public Attack
{
public:
	explicit GetPumped(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	PokemonStats getPlayerStat() { return { 0,StatBoost::SHARP_INCREASE,0,0,0,0,0,0 }; };
};

class LongJab : public Attack
{
public:
	explicit LongJab(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	StatusID getStatus() { return StatusID::FLINCH; };
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 70; };
};

class Dig : public Attack
{
public:
	explicit Dig(std::string name, Type type, DamageType damageType, int damage, int pp, int critChance, int accuracy) : Attack(name, type, damageType, damage, pp, critChance, accuracy) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	StatusID getStatus() { return StatusID::BURRIED; };
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 100; };
};

//									~ All Attack Classes ~ 





//									~ All Attack Definitions ~

//TODO: Fix Typing and balance moves
static Attack noAttack("None", Type::NONE, DamageType::PHYSICAL, 0, 0, 0, 0);
static Attack struggle("Struggle", Type::GRASS, DamageType::PHYSICAL, 5, 1, 0, 100); //TODO:Make normal Type
static HyperFang hyperFang("Hyper Fang", Type::GRASS, DamageType::PHYSICAL, 80, 10, 30, 100);
static Ember ember("Ember", Type::FIRE, DamageType::SPECIAL, 5, 10, 0, 80);
static BoneRush boneRush("BoneRush", Type::WATER, DamageType::PHYSICAL, 10, 10, 10, 50);
static TorpidPunch torpidPunch("Torpid Punch", Type::GRASS, DamageType::PHYSICAL, 5, 10, 50, 50);
static GetPumped getPumped("Get Pumped", Type::GRASS, DamageType::PHYSICAL, 0, 10, 0, 100);
static LongJab longJab("Long Jab", Type::WATER, DamageType::PHYSICAL, 20, 10, 0, 100);
static Dig dig("Dig", Type::FIRE, DamageType::SPECIAL, 20, 5, 0, 95);

//									~ All Attack Definitions ~

static std::unordered_map<int, Attack*> id_to_attack
{
	{NONE, &noAttack},
	{AttackID::STRUGGLE, &struggle},
	{AttackID::HYPERFANG, &hyperFang},
	{AttackID::EMBER, &ember},
	{AttackID::BONERUSH, &boneRush},
	{AttackID::TORPID_PUNCH, &torpidPunch},
	{AttackID::GET_PUMPED, &getPumped},
	{AttackID::LONG_JAB, &longJab},
	{AttackID::DIG, &dig}
};

static Attack* getAttackFromID(int id)
{
	try
	{
		return id_to_attack[id];
	}
	catch (...)
	{
		logger->log(LogLevel::CRITICAL, "Unable to retrieve attack of ID: " + std::to_string(id), "getAttack");
		logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
		return id_to_attack[NONE];
	}
}


//TODO: Maybe implement more types. Can implement them as they come
static std::unordered_map<Type, std::unordered_map<Type, float>> typeChart
{
	{Type::NONE,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::NORMAL,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 0.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::FIRE,
		
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 2.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 2.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::WATER,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 2.0f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 2.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::GRASS,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 2.0f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 2.0f},
			{Type::FLYING, 0.5f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 0.5f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::ELECTRIC,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 2.0f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 0.5f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 0.0f},
			{Type::FLYING, 2.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::ICE,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 0.5f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 2.0f},
			{Type::FLYING, 2.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 2.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::FIGHTING,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 2.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 0.5f},
			{Type::PSYCHIC, 0.5f},
			{Type::BUG, 0.5f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 0.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 2.0f},
			{Type::STEEL, 2.0f},
			{Type::FAIRY, 0.5f}
			}}
	},
	{Type::POISON,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 0.5f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 0.5f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.0f},
			{Type::FAIRY, 2.0f}
			}}
	},
	{Type::GROUND,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 2.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 2.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 2.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 0.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 0.5f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 2.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::FLYING,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 0.5f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 2.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 2.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::PSYCHIC,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 2.0f},
			{Type::POISON, 2.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 0.5f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 0.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::BUG,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 0.5f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 0.5f},
			{Type::PSYCHIC, 2.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 0.5f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 2.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 0.5f}
			}}
	},
	{ Type::ROCK,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 2.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 0.5f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 0.5f},
			{Type::FLYING, 2.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 2.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
		}}
	},
	{ Type::GHOST,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 0.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 2.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 2.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 0.5f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
		}}
	},
	{Type::DRAGON,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 2.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 0.0f}
			}}
	},
	{ Type::DARK,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 0.5f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 2.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 2.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 0.5f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 0.5f}
			}}
	},
	{ Type::STEEL,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 0.5f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 2.0f}
			}}
	},
	{ Type::FAIRY,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 2.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 2.0f},
			{Type::DARK, 2.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
};

static StatusID calculateMajorStatus(Pokemon* defender, StatusID id, int applicationOdds)
{
	if (outOfHundred(applicationOdds) && canHaveStatus(defender, id))
	{
		defender->applyMajorStatus(id, getStatusFromID(id)->getData().isBlocker);
		return id;
	}
	else
		return StatusID::NO_STATUS;
}

static StatusID calculateMinorStatus(Pokemon* targetPokemon, StatusID id, int applicationOdds)
{
	if (outOfHundred(applicationOdds) && canHaveStatus(targetPokemon, id))
	{
		targetPokemon->applyMinorStatus(id, getStatusFromID(id)->getData().isBlocker, getStatusFromID(id)->getData().isEvasive, getStatusFromID(id)->getData().forcedAttackID);
		return id;
	}
	else
		return StatusID::NO_STATUS;
}


// Adjusts stat parameter to a useable value
// returns 0 there is no stat change
// returns 1 for normal change
// returns 2 for sharp change
static int calculateStatChange(PokemonStats stats, Pokemon* pokemon, bool applyChange = false)
{
	//TODO: Think about moving stats to its own file. It may deserve it considering how important it is
	int value = 0;

	stats.hp = 0;

	for (int i = 0; i < 2; i++)
	{
		if (stats.attack == StatBoost::NONE)
			break;
		if ((stats.attack > 0 && stats.attack + pokemon->getBattleStats()->attack <= StatBoost::MAX) || (stats.attack < 0 && stats.attack + pokemon->getBattleStats()->attack >= StatBoost::MIN))
		{
			if ((stats.attack == StatBoost::INCREASE || stats.attack == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.attack == StatBoost::SHARP_INCREASE || stats.attack == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.attack > 0)
			stats.attack += StatBoost::DECREASE;
		else
			stats.attack += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.defense == StatBoost::NONE)
			break;
		if ((stats.defense > 0 && stats.defense + pokemon->getBattleStats()->defense <= StatBoost::MAX) || (stats.defense < 0 && stats.defense + pokemon->getBattleStats()->defense >= StatBoost::MIN))
		{
			if ((stats.defense == StatBoost::INCREASE || stats.defense == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.defense == StatBoost::SHARP_INCREASE || stats.defense == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.defense > 0)
			stats.defense += StatBoost::DECREASE;
		else
			stats.defense += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.spAttack == StatBoost::NONE)
			break;
		if ((stats.spAttack > 0 && stats.spAttack + pokemon->getBattleStats()->spAttack <= StatBoost::MAX) || (stats.spAttack < 0 && stats.spAttack + pokemon->getBattleStats()->spAttack >= StatBoost::MIN))
		{
			if ((stats.spAttack == StatBoost::INCREASE || stats.spAttack == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.spAttack == StatBoost::SHARP_INCREASE || stats.spAttack == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.spAttack > 0)
			stats.spAttack += StatBoost::DECREASE;
		else
			stats.spAttack += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.spDefense == StatBoost::NONE)
			break;
		if ((stats.spDefense > 0 && stats.spDefense + pokemon->getBattleStats()->spDefense <= StatBoost::MAX) || (stats.spDefense < 0 && stats.spDefense + pokemon->getBattleStats()->spDefense >= StatBoost::MIN))
		{
			if ((stats.spDefense == StatBoost::INCREASE || stats.spDefense == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.spDefense == StatBoost::SHARP_INCREASE || stats.spDefense == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.spDefense > 0)
			stats.spDefense += StatBoost::DECREASE;
		else
			stats.spDefense += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.speed == StatBoost::NONE)
			break;
		if ((stats.speed > 0 && stats.speed + pokemon->getBattleStats()->speed <= StatBoost::MAX) || (stats.speed < 0 && stats.speed + pokemon->getBattleStats()->speed >= StatBoost::MIN))
		{
			if ((stats.speed == StatBoost::INCREASE || stats.speed == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.speed == StatBoost::SHARP_INCREASE || stats.speed == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.speed > 0)
			stats.speed += StatBoost::DECREASE;
		else
			stats.speed += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.evasiveness == StatBoost::NONE)
			break;
		if ((stats.evasiveness > 0 && stats.evasiveness + pokemon->getBattleStats()->evasiveness <= StatBoost::MAX) || (stats.evasiveness < 0 && stats.evasiveness + pokemon->getBattleStats()->evasiveness >= StatBoost::MIN))
		{
			if ((stats.evasiveness == StatBoost::INCREASE || stats.evasiveness == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.evasiveness == StatBoost::SHARP_INCREASE || stats.evasiveness == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.evasiveness > 0)
			stats.evasiveness += StatBoost::DECREASE;
		else
			stats.evasiveness += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.accuracy == StatBoost::NONE)
			break;
		if ((stats.accuracy > 0 && stats.accuracy + pokemon->getBattleStats()->accuracy <= StatBoost::MAX) || (stats.accuracy < 0 && stats.accuracy + pokemon->getBattleStats()->accuracy >= StatBoost::MIN))
		{
			if ((stats.accuracy == StatBoost::INCREASE || stats.accuracy == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.accuracy == StatBoost::SHARP_INCREASE || stats.accuracy == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.accuracy > 0)
			stats.accuracy += StatBoost::DECREASE;
		else
			stats.accuracy += StatBoost::INCREASE;
	}


	if (applyChange)
		pokemon->addBattleStats(stats);

	return value;
}