#pragma once

#include "Trainer.h"

struct Dialogue
{
	std::string topLine;
	std::string botLine;
};

enum class InstructionType
{
	TURN,
	MOVE,
	DIALOGUE,
	PLAY
};

struct CharacterMoveDirections
{
	InstructionType type;
	Direction direction;
};

class NPT : public Trainer
{
public:

	explicit NPT(std::string name, CharacterID id,  int xTile, int yTile, Direction direction, int rewardMoney, int spotDistance) : Trainer(name, id)
	{
		giveMoney(rewardMoney);
		position.coords.xTile = xTile;
		position.coords.yTile = yTile;
		position.direction = direction;
		m_originalPosition = position;
		m_spotDistance = spotDistance;
	};

	explicit NPT(std::string name, CharacterID id, int xTile, int yTile, Direction direction) : Trainer(name, id)
	{
		position.coords.xTile = xTile;
		position.coords.yTile = yTile;
		position.direction = direction;
		m_originalPosition = position;
		setHasBeenDefeated(true);
	};

	std::vector<Dialogue> getDialogue()
	{
		if (wantsToBattle())
			return m_battleDialogue;

		return m_normalConversation;
	}

	int getSpotDistance() { return m_spotDistance; };

	void addBattleDialogue(Dialogue dialogue) { m_battleDialogue.push_back(dialogue); };
	void addNormalDialogue(Dialogue dialogue) { m_normalConversation.push_back(dialogue); };
	void addScriptInstruction(CharacterMoveDirections instruction) { m_script.push_back(instruction); };

	void removeItem(ItemID item)
	{
		m_usedItems.push_back(item);
		Trainer::removeItem(item);
	}

	void restoreItems()
	{
		for (ItemID item : m_usedItems)
		{
			addItem(item);
		}
	}

	bool isTrainer() { return false; };

	void setHasBeenDefeated(bool value) { m_hasBeenDefeated = value; };
	
	bool wantsToMove()
	{
		if (getPokemon(0).getLevel() != 0)
			return wantsToBattle();

		return true;
	}

	bool wantsToBattle()
	{
		if (m_hasBeenDefeated)
			return false;

		if (getPokemon(0).getLevel() == 0)
			return false;

		return true;
	}

	void resetPosition() { position = m_originalPosition; };	//TODO: Reset Bots

	Position getOriginalPosition() { return m_originalPosition; };

	std::vector<CharacterMoveDirections> getScript() { return m_script; };
private:
	
	Position m_originalPosition;

	int m_spotDistance = 0;
	bool m_hasBeenDefeated = false;
	std::vector<ItemID> m_usedItems;

	std::vector<Dialogue> m_battleDialogue;
	std::vector<Dialogue> m_normalConversation;

	std::vector<CharacterMoveDirections> m_script;
};