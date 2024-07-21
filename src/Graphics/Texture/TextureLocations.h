#pragma once

#include <unordered_map>

#include "../../GlobalData/globalIDs.h"
#include "Texture.h"

enum class MenuScene
{
	NONE,
	STARTUP_SCENE,
	BATTLE,
	BUY_ITEMS,
	USE_PC,
	PAUSE_MENU,
	PAUSE_ROSTER,
	PAUSE_SETTINGS,
	PAUSE_BAG,
	INTRO_LINKS,
	INTRO_LEGENDARY,
	INTRO_STUDIO,
	INTRO_STUDIO_CROWN,
	INTRO_PRESS_ANY_BUTTON,
	BATTLE_ROSTER,
	BATTLE_ITEMS,
	SET_PLAYER_NAME,
	PROFESSOR_M
};

enum class MenuOverlay	//TODO: Page For Menu Data
{
	NONE,
	ON_SCREEN_KEYBOARD,
	DELETE_CONFIRMATION,
	DIALOGUE,
	BATTLE_OPTIONS,
	ATTACK_SELECT,
	ITEM_SELECT,
	BATTLE_CHAT,
	IMAGE_FRAME,
	RESOLUTION_SELECTION,
	CHANGE_INPUT,
	LEVEL_UP_STAT_CHANGE,
	LEVEL_UP_STAT_VALUE
};

static std::unordered_map<CharacterID, std::string> g_CharacterTextureLocations = {
	{CharacterID::PLAYER, "Images/Characters/Player.png"},
	{CharacterID::FIRST_TRAINER, "Images/Characters/aiSprite.png"}
};

static std::unordered_map<SectionID, std::string> g_MapTextureLocations = {
	{SectionID::MAIN_SECTION, "Images/Maps/HVRoute1.png"},
	{SectionID::LINKED_SECTION, "Images/Maps/PokeShop.png"},
};

static std::unordered_map<Type, std::string> g_typeTextureLocations = {
	{Type::NONE, ""},
	{Type::NORMAL, "Images/Pokemon/Typing/normalType.png"},
	{Type::FIRE, "Images/Pokemon/Typing/fireType.png"},
	{Type::WATER, "Images/Pokemon/Typing/waterType.png"},
	{Type::GRASS, "Images/Pokemon/Typing/grassType.png"},
	{Type::ELECTRIC, "Images/Pokemon/Typing/electricType.png"},
	{Type::ICE, "Images/Pokemon/Typing/iceType.png"},
	{Type::FIGHTING, "Images/Pokemon/Typing/fightingType.png"},
	{Type::POISON, "Images/Pokemon/Typing/poisonType.png"},
	{Type::GROUND, "Images/Pokemon/Typing/groundType.png"},
	{Type::FLYING, "Images/Pokemon/Typing/flyingType.png"},
	{Type::PSYCHIC, "Images/Pokemon/Typing/psychicType.png"},
	{Type::BUG, "Images/Pokemon/Typing/bugType.png"},
	{Type::ROCK, "Images/Pokemon/Typing/rockType.png"},
	{Type::GHOST, "Images/Pokemon/Typing/ghostType.png"},
	{Type::DRAGON, "Images/Pokemon/Typing/dragonType.png"},
	{Type::DARK, "Images/Pokemon/Typing/darkType.png"},
	{Type::STEEL, "Images/Pokemon/Typing/steelType.png"},
	{Type::FAIRY, "Images/Pokemon/Typing/fairyType.png"}
};

static std::unordered_map<MenuScene, std::string> g_sceneTextureLocations = {
	{MenuScene::SET_PLAYER_NAME, "Images/Backgrounds/Scenes/keyboard.png" },
	{MenuScene::STARTUP_SCENE, "Images/Backgrounds/Scenes/selectSave.png" },
	{MenuScene::PROFESSOR_M, "Images/Backgrounds/Scenes/professorM.png" },
	{MenuScene::BATTLE, "Images/Backgrounds/Scenes/battleUI.png" },
	{MenuScene::PAUSE_ROSTER, "Images/Backgrounds/Scenes/pokemonRoster.png" },
	{MenuScene::INTRO_LINKS, "Images/Backgrounds/Scenes/intro_links.png"},
	{MenuScene::INTRO_LEGENDARY, "Images/Backgrounds/Scenes/aganiteIntro.png"},
	{MenuScene::INTRO_STUDIO, "Images/Backgrounds/Scenes/LegendaryStudio.png"},
	{MenuScene::INTRO_STUDIO_CROWN, "Images/Backgrounds/Scenes/LegendaryStudioCrown.png"},
	{MenuScene::PAUSE_MENU, "Images/Backgrounds/Scenes/pauseMenu.png" },
	{MenuScene::PAUSE_SETTINGS, "Images/Backgrounds/Scenes/settings.png" },
	{MenuScene::BATTLE_ITEMS, "Images/Backgrounds/Scenes/battle_items.png" },
};

static std::unordered_map<MenuOverlay, std::string> g_overlayTextureLocations ={
	{MenuOverlay::DELETE_CONFIRMATION, "Images/Backgrounds/overlays/deleteConfirmation.png"},
	{MenuOverlay::DIALOGUE, "Images/Backgrounds/overlays/normalChat.png"},
	{MenuOverlay::BATTLE_CHAT, "Images/Backgrounds/overlays/battleChat.png"},
	{MenuOverlay::IMAGE_FRAME, "Images/Backgrounds/overlays/imageFrame.png"},
	{MenuOverlay::LEVEL_UP_STAT_CHANGE, "Images/Backgrounds/overlays/levelUp.png"},
	{MenuOverlay::LEVEL_UP_STAT_VALUE, "Images/Backgrounds/overlays/levelUp.png"},
};

static std::string pokemonFrontTexture(std::string pokemonName)
{
	return "Images/Pokemon/" + pokemonName + "_Front.png";
}

static std::string pokemonBackTexture(std::string pokemonName)
{
	return "Images/Pokemon/" + pokemonName + "_Back.png";
}