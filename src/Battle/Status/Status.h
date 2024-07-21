#pragma once

#include "../SimulationCommands.h"

enum class StatusType
{
	MAJOR,
	MINOR
};

enum class IncrementTime
{
	BEFORE,
	DURING,
	AFTER
};

struct StatusData
{
	StatusID id;
	StatusType type;
	IncrementTime time;

	float percentMaxHealth;

	int turnToCure;
	int cureOdds;
	bool isBlocker;
	bool isEvasive;
	int forcedAttackID = NONE;
};

class Status
{
public:
	Status(StatusData data, std::string applicationMessage, std::string afflictionMessage, std::string cureMessage) 
	{
		m_data = data;
		m_applicationMessage = applicationMessage;
		m_afflictionMessage = afflictionMessage;
		m_cureMessage = cureMessage;
	};

	virtual std::vector<SimulationCommand> getStatusData(Pokemon* affectedPokemon, SelectedUser pokemonOwner);

	StatusData getData() { return m_data; };
	SimulationCommand getApplicationCommand(Pokemon* targetPokemon, SelectedUser recipient) { 

		SimulationCommand applicationCommand;

		applicationCommand.type = SimulationType::STATUS;
		applicationCommand.statusData.recipient = recipient;
		applicationCommand.statusData.statusGiven = getData().id;

		if (m_applicationMessage.size() != 0)
			applicationCommand.statusData.message = targetPokemon->getName() + m_applicationMessage;

		return applicationCommand; 
	};
	SimulationCommand getCureCommand(Pokemon* targetPokemon, SelectedUser owner)
	{
		SimulationCommand cureData;
		cureData.commander = owner;
		cureData.type = SimulationType::STATUS;

		cureData.statusData.curedStatus = getData().id;

		if (getCureMessage().size() != 0)
			cureData.statusData.message = targetPokemon->getName() + getCureMessage();

		return cureData;
	}
	std::string getAfflictionMessage() { return m_afflictionMessage; };
	std::string getCureMessage() { return m_cureMessage; };
private:
	StatusData m_data;

	std::string m_applicationMessage;
	std::string m_afflictionMessage;
	std::string m_cureMessage;
};

//TODO: Break cure conditions onto seperate lines
static Status burn = Status({ StatusID::BURN, StatusType::MAJOR, IncrementTime::AFTER, 6.25f, 3, NONE, false, false, NONE }, " has been burned", " is suffering from its burn", " has been cured of its burn");
static Status sleep = Status({ StatusID::SLEEP, StatusType::MAJOR, IncrementTime::BEFORE, 0.0f, 5, 40, true, false, NONE }, " has fallen asleep", " is fast asleep", " has woken up");
static Status paralysis = Status({ StatusID::PARALYSIS, StatusType::MAJOR, IncrementTime::BEFORE, 0.0f, 5, 40, true, false, NONE }, " has been paralyzed", " is unable to move", " is cured of its paralysis");

static Status flinch = Status({ StatusID::FLINCH, StatusType::MINOR, IncrementTime::AFTER, 0.0f, 1, NONE, true, false, NONE }, "", " flinched", "");
static Status burried = Status({ StatusID::BURRIED, StatusType::MINOR, IncrementTime::BEFORE, 0.0f, NONE, NONE, false, true, AttackID::DIG }, " has dug underground", " is underground", " is no longer underground");

static std::unordered_map<StatusID, Status*> id_to_status =
{
	{StatusID::BURN, &burn},
	{StatusID::SLEEP, &sleep},
	{StatusID::PARALYSIS, &paralysis},
	{StatusID::FLINCH, &flinch},
	{StatusID::BURRIED, &burried}
};

static Status* getStatusFromID(StatusID id)
{
	try
	{
		return id_to_status[id];
	}
	catch (...)
	{
		logger->log(LogLevel::CRITICAL, "Unable to retrieve status of unkown ID", "getStatus");
		logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
	}
	//TODOL Error out
}

//For incrementing and curing status
static std::vector<SimulationCommand> incrementStatusTimer(Pokemon* pokemon, StatusTracker* tracker, SelectedUser user)
{
	if (tracker->id == StatusID::NO_STATUS || pokemon->getCurHealth() == 0)
		return std::vector<SimulationCommand>();

	tracker->turnCount += 1;

	if (getStatusFromID(tracker->id)->getData().turnToCure != tracker->turnCount && !outOfHundred(getStatusFromID(tracker->id)->getData().cureOdds))
		return std::vector<SimulationCommand>();

	std::vector<SimulationCommand> statusCureData;
	statusCureData.push_back(getStatusFromID(tracker->id)->getCureCommand(pokemon, user));

	if (getStatusFromID(tracker->id)->getData().type == StatusType::MAJOR)
		pokemon->removeMajorStatus();
	else
		pokemon->removeMinorStatus(tracker->id);

	return statusCureData;
}

static bool canHaveStatus(Pokemon* pokemon, StatusID id)
{
	if (id == StatusID::NO_STATUS)
		return false;

	if (getStatusFromID(id)->getData().type == StatusType::MAJOR)
	{
		if (pokemon->getMajorStatus()->id == StatusID::NO_STATUS)
			return true;
	}
	else
	{
		for (StatusTracker data : *pokemon->getMinorStatus())
		{
			if (data.id == id)
				return false;
		}
		return true;
	}

	//TODO: Shouldnt even be able to get here
	return false;
}