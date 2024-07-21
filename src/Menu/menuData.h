#pragma once

#include <string>

//		Data Needed
//	
// Pokemon Roster
//	- Name
//	- HP formatted
//	- XP formatted
// 
// Move Data
// 
//	

struct SharedString
{
	std::string string1;
	std::string string2;
	std::string string3;
	std::string string4;
	std::string string5;
	std::string string6;
};

struct PokemonStringData
{
	std::string name;
	std::string level;
	std::string health;
	std::string Type1;
	std::string Type2;
	std::string attack;
	std::string defense;
	std::string spAttack;
	std::string spDefense;
	std::string speed;

	std::string move1;
	std::string move2;
	std::string move3;
	std::string move4;
};

struct BattlePokemonData
{
	std::string playerTexture;
	std::string opponentTexture;

	std::string playerName;
	std::string opponentName;

	std::string playerLevel;
	std::string opponentLevel;

	std::string currentHP;
	std::string maxHP;

	std::string botLine;


	std::string pokemonStatName;
	std::string pokemonStatLevel;
	SharedString pokemonStatDifference;
	SharedString pokemonStatValue;

	float playerCurHPPercent = 50.0f;
	float opponentCurHPPercent = 50.0f;

	float playerXPPercent = 50.0f;
};

struct MoveStringData
{
	std::string moveName;
	std::string currentPP;
	std::string maxPP;
	std::string moveTextureLocation;
};

struct PausePokemonData
{
	float hpPercent;

	std::string name;
	std::string level;
	std::string health;
	std::string attack;
	std::string defense;
	std::string spAttack;
	std::string spDefense;
	std::string speed;

	std::string type1;
	std::string type2;

	MoveStringData move1;
	MoveStringData move2;
	MoveStringData move3;
	MoveStringData move4;
};

struct PauseControlData
{
	std::string UpMain;
	std::string UpAlt;

	std::string DownMain;
	std::string DownAlt;

	std::string LeftMain;
	std::string LeftAlt;

	std::string RightMain;
	std::string RightAlt;

	std::string SelectMain;
	std::string SelectAlt;

	std::string BackMain;
	std::string BackAlt;

	std::string PauseMain;
	std::string PauseAlt;

	std::string SprintMain;
	std::string SprintAlt;
};

struct PauseSettingsData
{
	PauseControlData keyboardData;
	PauseControlData controllerData;

	std::string resolution;
	std::string fullscreen;
	std::string showFps;
	std::string autoSave;
	std::string fasterText;
};

struct RosterPokemonData
{
	std::string name;
	std::string pokemonTexture;
	std::string hp;
	std::string level;
};

struct TrainerBadgeData
{
	bool fireBadgeVisibility	= false;
	bool flyingBadgeVisibility	= false;
	bool grassBadgeVisibility	= false;
	bool iceBadgeVisibility		= false;
	bool normalBadgeVisibility	= false;
	bool rockBadgeVisibility	= false;
	bool waterBadgeVisibility	= false;
	bool dragonBadgeVisibility	= false;
};

struct RosterDisplayData
{
	RosterPokemonData pokemon1;
	RosterPokemonData pokemon2;
	RosterPokemonData pokemon3;
	RosterPokemonData pokemon4;
	RosterPokemonData pokemon5;
	RosterPokemonData pokemon6;

	PausePokemonData pausePokemonData;
};

struct ItemDisplayData
{
	SharedString itemName;
	SharedString itemAmount;
};

struct AlphabetStringData
{
	SharedString a_f = { "a","b","c","d","e","f" };
	SharedString g_l = { "g","h","i","j","k","l" };
	SharedString m_r = { "m","n","o","p","q","r" };
	SharedString s_x = { "s","t","u","v","w","x" };
	SharedString y_z = { "y","z"};
};

static void swapAlphabetData(AlphabetStringData* data)
{
	if (data->a_f.string1 == "a")
	{
		data->a_f = { "A","B","C","D","E","F" };
		data->g_l = { "G","H","I","J","K","L" };
		data->m_r = { "M","N","O","P","Q","R" };
		data->s_x = { "S","T","U","V","W","X" };
		data->y_z = { "Y","Z" };
	}
	else
	{
		data->a_f = { "a","b","c","d","e","f" };
		data->g_l = { "g","h","i","j","k","l" };
		data->m_r = { "m","n","o","p","q","r" };
		data->s_x = { "s","t","u","v","w","x" };
		data->y_z = { "y","z" };
	}
}

static char getKeyboardCharacter(AlphabetStringData* stringData, int keySelection)
{
	// a-z = 1-26
	// colon = 27
	// apostrophe = 28
	// 1-0 = 29-38

	int lower = 1;
	if (stringData->a_f.string1 != "a")
		lower = 0;

	if (keySelection == 27)
		return ':';
	else if (keySelection == 28)
		return '\'';
	else if (keySelection == 38)
		return '0';
	else if (keySelection >= 29)
		return '0' + (keySelection - 28);
	else
		return char(64 + keySelection + (lower * 32));
}

//Handles name of pokemon
static void formatRosterData(std::string* value, std::string data)
{
	*value = data;
}

//Handles XP and PP
static void formatRosterData(std::string* value, int data1, int data2)
{

}