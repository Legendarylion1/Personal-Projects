#pragma once

#include "ItemStorage.h"
#include "../../Graphics/PositionalData.h"

#include "../../Battle/Attack/Attack.h" //TODO: Remove. This is only here for the roster updatings at the bottom


enum class MovingStatus
{
	MOVING,
	STOPPED
};

class Trainer
{
public:
	Trainer() {};
	explicit Trainer(std::string name, CharacterID id);

	virtual bool isTrainer() { return true; };

	void onUpdate(Renderer* renderer);

	void printLocation() { std::cout << "Player: (" << position.coords.xTile << "," << position.coords.yTile << ")"; };
	void load(TrainerSave save);

	bool unableToBattle();

	void setName(std::string name) { m_name = name; };
	void setPokemon(int index, Pokemon pokemon);
	void setMovingStatus(MovingStatus status) { m_movingStatus = status; };
	void setLastStep(SpriteState state) { m_lastStep = state; };

	std::string getName() { return m_name; };
	Pokemon* getRoster() { return m_roster; };
	Pokemon getPokemon(int index);
	ItemStorage* getItemStorage();
	int getBalance() { return m_money; };
	int getBadgeCount() { return m_badges; };
	MovingStatus getMovingStatus() { return m_movingStatus; };
	SpriteState getLastStep() { return m_lastStep; };


	void giveMoney(int value) { m_money += value; };
	void reduceMoney(int value) { m_money -= value; };

	void addItem(ItemID item);
	void removeItem(ItemID item);

	Position position;

	operator TrainerSave const()
	{
		TrainerSave saveData;

		saveData.name = m_name;
		saveData.money = m_money;
		saveData.x = position.coords.xTile;
		saveData.y = position.coords.yTile;
		saveData.direction = position.direction;
		saveData.badgeCount = m_badges;

		return saveData;
	}

private:
	std::string m_name;
	int m_money = 0;
	int m_badges = 0;

	CharacterID m_id = CharacterID::PLAYER;
	SpriteState m_lastStep = SpriteState::STEP1;

	Pokemon m_roster[6];
	ItemStorage m_itemStorage;
	MovingStatus m_movingStatus = MovingStatus::STOPPED;
};

//TODO: Find a home for these functions
static void updateDisplayPokemon(Trainer* player, RosterDisplayData* data)
{
	Pokemon displayPokemon;

	//TODO: Try to clean up

	if (player->getPokemon(0).getLevel() != 0)
	{
		displayPokemon = player->getPokemon(0);

		data->pokemon1.name = displayPokemon.getName();
		data->pokemon1.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
		data->pokemon1.level = "Lv" + std::to_string(displayPokemon.getLevel());
		data->pokemon1.pokemonTexture = pokemonFrontTexture(displayPokemon.getSpecies().name);
	}
	else
	{
		data->pokemon1.name = "NONE";
		data->pokemon1.hp = "";
		data->pokemon1.level = "";
		data->pokemon1.pokemonTexture = "";
	}

	if (player->getPokemon(1).getLevel() != 0)
	{
		displayPokemon = player->getPokemon(1);

		data->pokemon2.name = displayPokemon.getName();
		data->pokemon2.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
		data->pokemon2.level = "Lv" + std::to_string(displayPokemon.getLevel());
		data->pokemon2.pokemonTexture = pokemonFrontTexture(displayPokemon.getSpecies().name);
	}
	else
	{
		data->pokemon2.name = "NONE";
		data->pokemon2.hp = "";
		data->pokemon2.level = "";
		data->pokemon2.pokemonTexture = "";
	}

	if (player->getPokemon(2).getLevel() != 0)
	{
		displayPokemon = player->getPokemon(2);

		data->pokemon3.name = displayPokemon.getName();
		data->pokemon3.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
		data->pokemon3.level = "Lv" + std::to_string(displayPokemon.getLevel());
		data->pokemon3.pokemonTexture = pokemonFrontTexture(displayPokemon.getSpecies().name);
	}
	else
	{
		data->pokemon3.name = "NONE";
		data->pokemon3.hp = "";
		data->pokemon3.level = "";
		data->pokemon3.pokemonTexture = "";
	}

	if (player->getPokemon(3).getLevel() != 0)
	{
		displayPokemon = player->getPokemon(3);

		data->pokemon4.name = displayPokemon.getName();
		data->pokemon4.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
		data->pokemon4.level = "Lv" + std::to_string(displayPokemon.getLevel());
		data->pokemon4.pokemonTexture = pokemonFrontTexture(displayPokemon.getSpecies().name);
	}
	else
	{
		data->pokemon4.name = "NONE";
		data->pokemon4.hp = "";
		data->pokemon4.level = "";
		data->pokemon4.pokemonTexture = "";
	}

	if (player->getPokemon(4).getLevel() != 0)
	{
		displayPokemon = player->getPokemon(4);

		data->pokemon5.name = displayPokemon.getName();
		data->pokemon5.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
		data->pokemon5.level = "Lv" + std::to_string(displayPokemon.getLevel());
		data->pokemon5.pokemonTexture = pokemonFrontTexture(displayPokemon.getSpecies().name);
	}
	else
	{
		data->pokemon5.name = "NONE";
		data->pokemon5.hp = "";
		data->pokemon5.level = "";
		data->pokemon5.pokemonTexture = "";
	}

	if (player->getPokemon(5).getLevel() != 0)
	{
		displayPokemon = player->getPokemon(5);

		data->pokemon6.name = displayPokemon.getName();
		data->pokemon6.hp = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp) + " HP";
		data->pokemon6.level = "Lv" + std::to_string(displayPokemon.getLevel());
		data->pokemon6.pokemonTexture = pokemonFrontTexture(displayPokemon.getSpecies().name);
	}
	else
	{
		data->pokemon6.name = "NONE";
		data->pokemon6.hp = "";
		data->pokemon6.level = "";
		data->pokemon6.pokemonTexture = "";
	}
}

static void updateHighlightedPokemonHP(Pokemon displayPokemon, PausePokemonData* data)
{
	float maxPercent = 13.8f;

	data->hpPercent = maxPercent * ((float)displayPokemon.getCurHealth() / (float)displayPokemon.getStats().hp);
}

static void formatMoveStringData(Pokemon displayPokemon, RosterDisplayData* data, int moveIndex)
{
	Attack* attack = nullptr;
	MoveStringData* move = nullptr;

	if (moveIndex == 1)
	{
		attack = getAttackFromID(displayPokemon.getMoveset().move1);
		move = &data->pausePokemonData.move1;
		move->currentPP = std::to_string(displayPokemon.getMoveset().move1pp);
	}
	else if (moveIndex == 2)
	{
		attack = getAttackFromID(displayPokemon.getMoveset().move2);
		move = &data->pausePokemonData.move2;
		move->currentPP = std::to_string(displayPokemon.getMoveset().move2pp);
	}
	else if (moveIndex == 3)
	{
		attack = getAttackFromID(displayPokemon.getMoveset().move3);
		move = &data->pausePokemonData.move3;
		move->currentPP = std::to_string(displayPokemon.getMoveset().move3pp);
	}
	else
	{
		attack = getAttackFromID(displayPokemon.getMoveset().move4);
		move = &data->pausePokemonData.move4;
		move->currentPP = std::to_string(displayPokemon.getMoveset().move4pp);
	}

	if (attack->getName() != getAttackFromID(NONE)->getName())
	{
		move->moveName = attack->getName();
		move->maxPP = std::to_string(attack->getPP());
		move->moveTextureLocation = g_typeTextureLocations[attack->getType()];
	}
	else
	{
		move->moveName = "NONE";
		move->currentPP = "0";
		move->maxPP = "NONE";
		move->moveTextureLocation = "";
	}
}

static void updateDisplayPokemonStats(int* hoveredIndex, Trainer* player, int menuButtonIndex, RosterDisplayData* data)
{
	if (*hoveredIndex == menuButtonIndex)
		return;

	Pokemon displayPokemon = player->getPokemon(menuButtonIndex);

	data->pausePokemonData.attack = std::to_string(displayPokemon.getStats().attack);
	data->pausePokemonData.defense = std::to_string(displayPokemon.getStats().defense);
	data->pausePokemonData.spAttack = std::to_string(displayPokemon.getStats().spAttack);
	data->pausePokemonData.spDefense = std::to_string(displayPokemon.getStats().spDefense);
	data->pausePokemonData.speed = std::to_string(displayPokemon.getStats().speed);

	formatMoveStringData(displayPokemon, data, 1);
	formatMoveStringData(displayPokemon, data, 2);
	formatMoveStringData(displayPokemon, data, 3);
	formatMoveStringData(displayPokemon, data, 4);

	updateHighlightedPokemonHP(displayPokemon, &data->pausePokemonData);

	*hoveredIndex = menuButtonIndex;

	data->pausePokemonData.name = displayPokemon.getName();
	data->pausePokemonData.level = "Lv" + std::to_string(displayPokemon.getLevel());
	data->pausePokemonData.health = std::to_string(displayPokemon.getCurHealth()) + ":" + std::to_string(displayPokemon.getStats().hp);
	data->pausePokemonData.type1 = g_typeTextureLocations[displayPokemon.getSpecies().type1];
	data->pausePokemonData.type2 = g_typeTextureLocations[displayPokemon.getSpecies().type2];
}