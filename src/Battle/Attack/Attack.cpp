#include "Attack.h"

Attack::Attack(std::string name, Type type, DamageType damageType, int power, int pp, int critChance, int accuracy)
{
	m_name = name;

	m_type = type;
	m_damageType = damageType;

	m_power = power;
	m_pp = pp;
	m_critChance = critChance;
	m_accuracy = accuracy;
}

std::vector<SimulationCommand> Attack::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;
	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;

	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		allAttackData.push_back(getMissedAttackData(attacker, commander));
	else if (attackData.attackData.damage == -2)
		allAttackData.push_back(getNotEffectedData(defender, commander));	//TODO: Generate Miss data so that we print the move that was used and the fact that they arent effected


	//				~ Push back final data ~
	allAttackData.push_back(attackData);
	
	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "Attack");
	return allAttackData;
}

// Returns 0 if there was an evasion
// Returns -1 if the opponent has fainted
// Returns -2 if it doesnt effect the pokemon
// Else damage of the move
int Attack::calculateAttackDamage(Pokemon* attacker, Pokemon* defender, Attack* attack, bool applyDamage, AttackCommand* command)
{
	if (defender->getCurHealth() == 0)
		return -1;

	if (defender->hasEvasiveStatus() != StatusID::NO_STATUS)
		return 0;


	float userAccuracy = 1.0f;
	float targetEvasion = 1.0f;

	if (attacker->getBattleStats()->accuracy > 0)
		userAccuracy = (2.0f + attacker->getBattleStats()->accuracy) / 2.0f;
	else if (attacker->getBattleStats()->accuracy < 0)
		userAccuracy = 2.0f / (2.0f + abs(attacker->getBattleStats()->accuracy));

	if (attacker->getBattleStats()->evasiveness > 0)
		targetEvasion = (2.0f + attacker->getBattleStats()->evasiveness) / 2.0f;
	else if (attacker->getBattleStats()->evasiveness < 0)
		targetEvasion = 2.0f / (2.0f + abs(attacker->getBattleStats()->evasiveness));


	float accuracy = attack->getAccuracy() * userAccuracy * targetEvasion;

	if (!outOfHundred((int)accuracy))
	{
		if (command != nullptr)
			command->message = attacker->getName() + " missed!";

		return 0;
	}


	//TODO: Possibly make attack command default to nullptr
	int critical = 1;
	if (outOfHundred(attack->getCritChance()))
	{
		if (command != nullptr)
			command->crit = true;
		critical = 2;
	}

	float statDamage = ((2.0f * attacker->getLevel() * critical) / 5.0f) + 2.0f;


	float attackMultiplier = 1.0f;
	float defenseMultiplier = 1.0f;

	if (attack->getPowerType() == DamageType::PHYSICAL)
	{
		if (attacker->getBattleStats()->attack > 0)
			attackMultiplier = (2.0f + attacker->getBattleStats()->attack) / 2.0f;
		else if (attacker->getBattleStats()->attack < 0)
			attackMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->attack));

		if (attacker->getBattleStats()->defense > 0)
			defenseMultiplier = (2.0f + attacker->getBattleStats()->defense) / 2.0f;
		else if (attacker->getBattleStats()->defense < 0)
			defenseMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->defense));
	}
	else
	{
		if (attacker->getBattleStats()->spAttack > 0)
			attackMultiplier = (2.0f + attacker->getBattleStats()->spAttack) / 2.0f;
		else if (attacker->getBattleStats()->spAttack < 0)
			attackMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->spAttack));

		if (attacker->getBattleStats()->spDefense > 0)
			defenseMultiplier = (2.0f + attacker->getBattleStats()->spDefense) / 2.0f;
		else if (attacker->getBattleStats()->spDefense < 0)
			defenseMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->spDefense));
	}






	float powerRatio = (attacker->getStats().attack * attackMultiplier) / (float)(defender->getStats().defense * defenseMultiplier);
	if (attack->getPowerType() == DamageType::SPECIAL)
		powerRatio = (attacker->getStats().spAttack * attackMultiplier) / (float)(defender->getStats().spDefense * defenseMultiplier);


	float baseDamage = ((statDamage * attack->getPower() * powerRatio) / 50.0f) + 2;

	if (attack->getType() == attacker->getSpecies().type1 || attack->getType() == attacker->getSpecies().type2)
		baseDamage *= 1.5;

	baseDamage *= typeChart[attack->getType()][defender->getSpecies().type1];
	baseDamage *= typeChart[attack->getType()][defender->getSpecies().type2];


	if (typeChart[attack->getType()][defender->getSpecies().type1] * typeChart[attack->getType()][defender->getSpecies().type2] == 0)
		return -2;

	float random = (randomNumber(41) + 215.0f) / 255.0f;

	baseDamage *= random;

	if (baseDamage < 1)
		baseDamage = 1;

	int damage = (int)baseDamage;


	if (command != nullptr)
	{
		command->message = attacker->getName() + " used " + attack->getName();

		if (typeChart[attack->getType()][defender->getSpecies().type1] * typeChart[attack->getType()][defender->getSpecies().type2] <= .50f)
		{
			command->effectiveness = EffectiveStatus::NOT_VERY;
		}
		else if (typeChart[attack->getType()][defender->getSpecies().type1] * typeChart[attack->getType()][defender->getSpecies().type2] >= 1.5)
		{
			command->effectiveness = EffectiveStatus::SUPER;
		}
		else
		{
			command->effectiveness = EffectiveStatus::EFFECTIVE;
		}
	}


	if (defender->getCurHealth() - damage < 0)
		damage = defender->getCurHealth();

	if (applyDamage)
		defender->adjustCurHealth(-damage);

	return damage;
}

SimulationCommand Attack::getMissedAttackData(Pokemon* attacker, SelectedUser commander)
{
	SimulationCommand attackData{};

	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;
	attackData.attackData.damage = 0;
	attackData.attackData.message = attacker->getName() + " used " + this->getName();

	return attackData;
}

SimulationCommand Attack::getNotEffectedData(Pokemon* defender, SelectedUser commander)
{
	SimulationCommand attackData{};

	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;
	attackData.attackData.damage = 0;
	attackData.attackData.message = "It doesnt affect " + defender->getName();
	return SimulationCommand();
}

std::vector<SimulationCommand> Ember::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;
	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;


	attackData.attackData.damage = calculateAttackDamage(attacker,defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		allAttackData.push_back(getMissedAttackData(attacker, commander));
	else
		attackData.attackData.statusGiven = calculateMajorStatus(defender, getStatus(), getStatusOdds(attacker, defender));
	

	//				~ Push back final data ~
	allAttackData.push_back(attackData);


	SelectedUser recipient = SelectedUser::AI;
	if (commander == SelectedUser::AI)
		recipient = SelectedUser::PLAYER;

	if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
		allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(defender, recipient));

	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "Ember");
	return allAttackData;
}

std::vector<SimulationCommand> TorpidPunch::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	// More odds of them falling asleep the lower their health ratio is

	std::vector<SimulationCommand> allAttackData;
	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;

	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		allAttackData.push_back(getMissedAttackData(attacker, commander));
	else
		attackData.attackData.statusGiven = calculateMajorStatus(defender, getStatus(), getStatusOdds(attacker, defender));


	allAttackData.push_back(attackData);


	SelectedUser recipient = SelectedUser::AI;
	if (commander == SelectedUser::AI)
		recipient = SelectedUser::PLAYER;

	if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
		allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(defender, recipient));

	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "TorpidPunch");
	return allAttackData;
}

std::vector<SimulationCommand> GetPumped::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;

	SimulationCommand attackData{};

	attackData.commander = commander;
	attackData.type = SimulationType::ATTACK;
	attackData.attackData.message = attacker->getName() + " used " + getName();

	allAttackData.push_back(attackData);


	SimulationCommand statData{};

	statData.type = SimulationType::STAT;
	statData.statData.recipient = commander;
	statData.statData.stats = getPlayerStat();

	int value = calculateStatChange(statData.statData.stats, attacker, true);

	if (value == 2)
		statData.statData.message = attacker->getName() + " attack rose sharply!!";
	else if (value == 1)
		statData.statData.message = attacker->getName() + " attack rose";
	else
		statData.statData.message = attacker->getName() + "'s attack wont go any higher";

	allAttackData.push_back(statData);

	return allAttackData;
};

std::vector<SimulationCommand> BoneRush::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	//Hits 3-5 times
	std::vector<SimulationCommand> allAttackData;
	int missedHits = 0;

	SimulationCommand attackData{};

	attackData.commander = commander;
	attackData.type = SimulationType::ATTACK;
	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		allAttackData.push_back(getMissedAttackData(attacker, commander));
	else
	{
		missedHits--;
		allAttackData.push_back(attackData);
	}

	
	

	for (int i = 1; i < 5; i++)
	{
		if (i >= 3 && outOfHundred(50))
		{
			
			//TODO: Test further

			//SimulationCommand messageData{};
			//messageData.commander = commander;
			//messageData.type = SimulationType::ATTACK;
			//messageData.attackData.message = "It hit " + std::to_string(i - missedHits) + " times!";
			//allAttackData.push_back(messageData);

			break;
		}
		
		SimulationCommand nextAttack{};

		nextAttack.commander = commander;
		nextAttack.type = SimulationType::ATTACK;
		nextAttack.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &nextAttack.attackData);

		if (nextAttack.attackData.damage == -1)
			break;

		if (nextAttack.attackData.damage == 0)
		{
			nextAttack.attackData.message = attacker->getName() + " missed!";
			missedHits ++;
		}
		else
		{
			nextAttack.attackData.message = "It hit " + std::to_string(i - missedHits) + " times!";
		}

		allAttackData.push_back(nextAttack);
	}

	return allAttackData;
}

int BoneRush::getPotentialDamage(Pokemon* attacker, Pokemon* defender)
{
	int count = 0;

	for (int i = 0; i < 5; i++)
	{
		if (i >= 3 && outOfHundred(50))
			break;

		count += calculateAttackDamage(attacker, defender, this);
	}

	return count;
}

std::vector<SimulationCommand> LongJab::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;
	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;

	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);
	attackData.attackData.statusGiven = calculateMinorStatus(defender, getStatus(), getStatusOdds(attacker, defender));



	//				~ Push back final data ~
	allAttackData.push_back(attackData);



	SelectedUser recipient = SelectedUser::AI;
	if (commander == SelectedUser::AI)
		recipient = SelectedUser::PLAYER;

	if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
		allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(defender, recipient));


	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "LongJab");
	return allAttackData;
}

std::vector<SimulationCommand> Dig::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;

	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;


	if (attacker->hasEvasiveStatus() == StatusID::BURRIED)
	{

		attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

		if (attackData.attackData.damage == 0)
			allAttackData.push_back(getMissedAttackData(attacker, commander));


		//				~ Push back final data ~
		allAttackData.push_back(attackData);

		attacker->removeMinorStatus(StatusID::BURRIED);
		allAttackData.push_back(getStatusFromID(StatusID::BURRIED)->getCureCommand(attacker, commander));
	}
	else
	{
		attackData.attackData.damage = 0;

		attackData.attackData.statusGiven = calculateMinorStatus(attacker, getStatus(), getStatusOdds(attacker, defender));

		//				~ Push back final data ~
		allAttackData.push_back(attackData);

		if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
			allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(attacker, commander));
	}

	

	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "Dig");
	return allAttackData;
}