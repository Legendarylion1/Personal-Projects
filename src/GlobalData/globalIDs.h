#pragma once

const static int NONE = -1;

enum class Type
{
	NONE,
	NORMAL,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	ICE,
	FIGHTING,
	POISON,
	GROUND,
	FLYING,
	PSYCHIC,
	BUG,
	ROCK,
	GHOST,
	DRAGON,
	DARK,
	STEEL,
	FAIRY
};

enum PokemonID
{
	Baroot,
	Bery,
	Fitty
};

enum AttackID
{
	STRUGGLE,
	HYPERFANG,
	BONERUSH,
	EMBER,
	TORPID_PUNCH,
	GET_PUMPED,
	LONG_JAB,
	DIG
};

enum ItemID
{
	SMALL_POTION,
	MEDIUM_POTION,
	LARGE_POTION,
	POKEBALL,
	GREATBALL,
	ULTRABALL,
	MASTERBALL,
	ROID_JUICE
};

enum class StatusID	//TODO: Check and see if status is being Saved
{
	NO_STATUS,
	ALL,
	FAINTED,
	BURN,
	FREEZE,
	PARALYSIS,
	POISON,
	SLEEP,
	FLINCH,
	BURRIED
};

enum class SectionID
{
	MAIN_SECTION,
	LINKED_SECTION
};

enum class CharacterID
{
	PLAYER,
	FIRST_TRAINER
};

enum CutSceneID
{
	FIRST_CUTSCENE
};