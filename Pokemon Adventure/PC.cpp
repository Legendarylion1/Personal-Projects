#include "PC.h"

bool PC::addPokemon(Trainer& trainer, Pokemon pokemon)
{
	loadPC(trainer, false);
	int openBox = -1;
	for (int i = 0; i < 8; i++)
	{
		if (m_boxPokemonCount[i] != 20)
		{
			openBox = i;
			break;
		}
	}

	if (openBox == -1)
	{
		std::cout << "\n" << "All boxes are full. The pokemon cannot be saved to the pc." << std::endl;
		return false;
	}

	for (int i = 0; i < 20; i++)
	{
		if (m_allPokemon[openBox][i].getLevel() == 0)
		{
			m_allPokemon[openBox][i] = pokemon;
			break;
		}
	}

	m_boxPokemonCount[openBox] += 1;

	std::cout << "\n" << pokemon.getName() << " has been added to PC box #" << openBox << std::endl;

	//TODO: Make this optional
	//savePC(trainer);
	return true;
}

void PC::movePokemon(unsigned int box1, unsigned int index1, unsigned int box2, unsigned int index2)
{
	Pokemon pokemon1 = m_allPokemon[box1][index1];
	Pokemon pokemon2 = m_allPokemon[box2][index2];

	m_allPokemon[box1][index1] = pokemon2;
	m_allPokemon[box2][index2] = pokemon1;
}

void PC::insertPokemon(Pokemon pokemon, unsigned int box, unsigned int index)
{
	m_allPokemon[box][index] = pokemon;
}

Pokemon PC::popPokemon(unsigned int box, unsigned int index)
{
	Pokemon boxPokemon = m_allPokemon[box][index];

	m_allPokemon[box][index] = Pokemon();
	m_boxPokemonCount[box] -= 1;

	return boxPokemon;
}

std::vector<unsigned int> PC::getPlayerLocation()
{
	return std::vector<unsigned int>{m_playerTileX, m_playerTileY, m_playerMapID, m_playerDirection, m_buildingEvent, m_cutsceneCount};
}

std::vector<Pokemon> PC::getBox(unsigned int index)
{
	std::vector<Pokemon> boxPokemon;
	//TODO: Hard code this 20 box size
	for (int i = 0; i < 20; i++)
	{
		boxPokemon.push_back(m_allPokemon[index][i]);
	}
	return boxPokemon;
}

std::string PC::getBoxName(unsigned int index)
{
	return "Box " + std::to_string(index + 1);
}

std::vector<std::vector<bool>> PC::getNptData()
{
	return m_nptData;
}

void PC::printBox(unsigned int box)
{
	std::cout << "\n\nBox #" << box << std::endl;

	for (int i = 0; i < 20; i++)
	{
		if (i % 4 == 0)
			std::cout << "\n";

		if (m_allPokemon[box][i].getLevel() != 0)
			std::cout << i + 1 << ". " << m_allPokemon[box][i].getName() << "\t";
		else
			std::cout << i + 1 << ".  None\t";
	}
	std::cout << "\n";
}

void PC::setPlayerPosition(unsigned int mapID, unsigned int x, unsigned int y, unsigned int direction)
{
	m_playerMapID = mapID;
	m_playerTileX = x;
	m_playerTileY = y;
	m_playerDirection = direction;
}

void PC::setBuildingEvent(unsigned int buildingEvent)
{
	m_buildingEvent = buildingEvent;
}

void PC::setCutsceneCount(unsigned int cutsceneCount)
{
	m_cutsceneCount = cutsceneCount;
}

void PC::setNptData(std::vector<std::vector<bool>> nptData)
{
	m_nptData = nptData;
}

void PC::setAutoSave(bool autoSave)
{
	m_autoSave = autoSave;
}

void PC::loadPC(Trainer& trainer, bool overwriteData)
{
	try
	{
		unsigned int loadState = boxSection;

		std::string data;

		std::fstream pcFile;
		m_nptData.clear();	//TODO: Evaluate this. I think it should technically be clear because we dont load besides the start but evaluate this please.

		pcFile.open("data.pc", std::ofstream::in);

		if (pcFile.is_open())
		{

			while (getline(pcFile, data)) {
				if (data == m_boxSection)
				{
					loadState = boxSection;
					continue;
				}
				else if (data == m_rosterSection)
				{
					loadState = rosterSection;
					continue;
				}
				else if (data == m_itemSection)
				{
					loadState = itemSection;
					continue;
				}
				else if (data == m_coordSection)
				{
					loadState = coordSection;
					continue;
				}
				else if (data == m_nptSection)
				{
					loadState = nptSection;
					continue;
				}
				buildPokemon(decrypt(data), loadState);
			}
			pcFile.close();
		}

		if (overwriteData)
		{
			trainer.setRoster(m_roster);

			for (int i = 0; i < m_items.size(); i++)
			{
				trainer.addItem(id_to_item[m_items.at(i)]);
			}

			m_items.clear();
		}


	}
	catch (...)
	{
		std::cout << "Error Reading Data From File. " << std::endl;
		exit(404);
	}
}

bool PC::savePC(Trainer& trainer)
{
	try
	{
		std::ofstream pcFile;
		pcFile.open("data.pc", std::ofstream::out | std::ofstream::trunc);

		if (pcFile.is_open())
		{
			//Roster Section
			{
				pcFile << m_rosterSection << "\n";

				for (int i = 0; i < 6; i++)
				{
					pcFile << encrypt(getRosterData(trainer, i)) << "\n";
				}

			}


			//Box Section
			{
				pcFile << m_boxSection << "\n";
				for (int box = 0; box < 8; box++)
				{
					for (int index = 0; index < 20; index++)
					{
						if (m_allPokemon[box][index].getLevel() != 0)
							pcFile << encrypt(getPCData(box,index)) << "\n";
					}
				}
			}


			//Item Section
			{
				pcFile << m_itemSection << "\n";
				while (trainer.getUniquePokeballCount() > 0)
				{
					pcFile << encrypt(  getItemData(trainer.getPokeball(0)->getID())  ) << "\n";
					trainer.removeItem(*trainer.getPokeball(0));
				}
				while (trainer.getUniqueHealCount() > 0)
				{
					pcFile << encrypt(getItemData(trainer.getHealItem(0)->getID())) << "\n";
					trainer.removeItem(*trainer.getHealItem(0));
				}
				while (trainer.getUniqueMiscCount() > 0)
				{
					pcFile << encrypt(getItemData(trainer.getMiscItem(0)->getID())) << "\n";
					trainer.removeItem(*trainer.getMiscItem(0));
				}
			}

			//Coord Section
			pcFile << m_coordSection << "\n";
			pcFile << encrypt(getCoordData()) << "\n";

			//NPT Section

			pcFile << m_nptSection << "\n";
			for (int i = 0; i < m_nptData.size(); i++)
			{
				pcFile << encrypt(getNptData(m_nptData.at(i))) << "\n";
			}


			pcFile.close();
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		std::cout << "Error Writing Data To File. " << std::endl;
		exit(404);
	}
}

void PC::autoSave(Trainer& trainer, unsigned int mapID, unsigned int x, unsigned int y, unsigned int direction, std::vector<std::vector<bool>> nptData)
{
	if (m_autoSave)
	{
		setPlayerPosition(mapID, x, y, direction);
		setNptData(nptData);
		savePC(trainer);
	}
}

void PC::loadUserSettings(userSettings* settings)
{	
	try
	{
		std::string data;
		std::fstream pcFile;
		std::vector<std::string> allData;

		pcFile.open("user.settings", std::ofstream::in);

		if (!pcFile.is_open())
			return;

		while (getline(pcFile, data))
		{
			allData.push_back(getColonData(data));
		}
		pcFile.close();

		settings->resolution = allData.at(0);

		settings->up = atoi(allData.at(1).c_str());
		settings->down = atoi(allData.at(2).c_str());
		settings->left = atoi(allData.at(3).c_str());
		settings->right = atoi(allData.at(4).c_str());
		settings->interact = atoi(allData.at(5).c_str());

		settings->showFps = atoi(allData.at(6).c_str());
		settings->autoSave = atoi(allData.at(7).c_str());
		settings->fasterText = atoi(allData.at(8).c_str());
	}
	catch (...)
	{
		std::cout << "Error Reading Data From File. " << std::endl;
		exit(404);
	}
}

void PC::saveUserSettings(userSettings* settings)
{
	try
	{
		std::ofstream pcFile;
		pcFile.open("user.settings", std::ofstream::out | std::ofstream::trunc);

		//TODO: Make a bool so we know that the save was a fail as well as for the load Settings
		if (!pcFile.is_open())
			return;

		pcFile << "Resolution: " << settings->resolution << "\n";
		pcFile << "Up: " << settings->up << "\n";
		pcFile << "Down: " << settings->down << "\n";
		pcFile << "Left: " << settings->left << "\n";
		pcFile << "Right: " << settings->right << "\n";
		pcFile << "Interact: " << settings->interact << "\n";
		pcFile << "ShowFps: " << settings->showFps << "\n";
		pcFile << "AutoSave: " << settings->autoSave << "\n";
		pcFile << "FasterText: " << settings->fasterText << "\n";


		pcFile.close();

	}
	catch (...)
	{
		std::cout << "Error Writing Data To File. " << std::endl;
		exit(404);
	}
}

//TODO: Rename from build pokemon
void PC::buildPokemon(std::string line, unsigned int loadState)
{
	if (line == "")
		return;

	if (loadState == boxSection)
		buildBoxPokemon(line);
	else if (loadState == rosterSection)
		buildRosterPokemon(line);
	else if (loadState == itemSection)
		buildItemSection(line);
	else if (loadState == coordSection)
		buildCoordinates(line);
	else if (loadState == nptSection)
		buildNptData(line);
}

std::string PC::getRosterData(Trainer& trainer, unsigned int index)
{
	return std::to_string(index) + "-"
		+ trainer.getPokemon(index)->getName() + "-"
		+ std::to_string(trainer.getPokemon(index)->getSpecies().getID()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(0).getID()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(0).getCurrentPP()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(1).getID()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(1).getCurrentPP()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(2).getID()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(2).getCurrentPP()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(3).getID()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getAttack(3).getCurrentPP()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getItem().getID()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getLevel()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getCurrentXP()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getHealth()) + "-"
		+ std::to_string(trainer.getPokemon(index)->getStatus().getID());;
}

std::string PC::getPCData(unsigned int box, unsigned int index)
{
	// (box,index)name-speciesID-attack1ID,pp-attack2ID,pp-attack3ID,pp-attack4ID,pp-ItemID-level-currentXP-currentHealth-status
	return std::to_string(box) + "-" + std::to_string(index) + '-'
		+ m_allPokemon[box][index].getName() + "-"
		+ std::to_string(m_allPokemon[box][index].getSpecies().getID()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(0).getID()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(0).getCurrentPP()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(1).getID()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(1).getCurrentPP()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(2).getID()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(2).getCurrentPP()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(3).getID()) + "-"
		+ std::to_string(m_allPokemon[box][index].getAttack(3).getCurrentPP()) + "-"
		+ std::to_string(m_allPokemon[box][index].getItem().getID()) + "-"
		+ std::to_string(m_allPokemon[box][index].getLevel()) + "-"
		+ std::to_string(m_allPokemon[box][index].getCurrentXP()) + "-"
		+ std::to_string(m_allPokemon[box][index].getHealth()) + "-"
		+ std::to_string(m_allPokemon[box][index].getStatus().getID());;
}

std::string PC::getItemData(unsigned int ID)
{
	return std::to_string(ID) + "-" + std::to_string(randomNumber()) + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber());
}

std::string PC::getCoordData()
{
	return std::to_string(m_playerTileX) + "-" + std::to_string(randomNumber()) + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(m_playerTileY) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + std::to_string(randomNumber()) + "-" + std::to_string(m_playerMapID)
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(m_playerDirection) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + std::to_string(randomNumber()) + "-" + std::to_string(m_buildingEvent)
		+ "-" + std::to_string(randomNumber()) + std::to_string(randomNumber()) + "-" + std::to_string(m_cutsceneCount)
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber())
		+ "-" + std::to_string(randomNumber()) + "-" + std::to_string(randomNumber());
}

std::string PC::getNptData(std::vector<bool> data)
{
	std::string nptData = "";

	// Actual Data
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i) == true)
			nptData += "1";
		else
			nptData += "0";
	}

	// Padding
	for (int i = data.size(); i < 45; i++)
	{
		if (odds(50))
			nptData += "1";
		else
			nptData += "0";
	}

	return nptData;
}

std::string PC::getColonData(std::string data)
{
	std::string value;
	bool addData = false;
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i) == ':')
		{
			addData = true;
			continue;
		}

		if (addData && data.at(i) != ' ')
			value += data.at(i);
	}
	return value;
}

void PC::buildBoxPokemon(std::string line)
{
	std::vector<std::string> pokemonData = splitString(line, '-');

	Attack pokemonAttacks[4] = { id_to_attack[std::stoi(pokemonData[4])],id_to_attack[std::stoi(pokemonData[6])],id_to_attack[std::stoi(pokemonData[8])],id_to_attack[std::stoi(pokemonData[10])] };
	pokemonAttacks[0].setPP(std::stoi(pokemonData[5]));
	pokemonAttacks[1].setPP(std::stoi(pokemonData[7]));
	pokemonAttacks[2].setPP(std::stoi(pokemonData[9]));
	pokemonAttacks[3].setPP(std::stoi(pokemonData[11]));

	Pokemon newPokemon(id_to_species[std::stoi(pokemonData[3])], std::stoi(pokemonData[13]), pokemonAttacks);
	newPokemon.setName(pokemonData[2]);
	newPokemon.setHP(std::stoi(pokemonData[15]));
	newPokemon.gainXP(std::stoi(pokemonData[14]));
	newPokemon.setItem(&id_to_item[std::stoi(pokemonData[12])]);
	newPokemon.setStatus(&id_to_status[std::stoi(pokemonData[16])]);

	m_allPokemon[std::stoi(pokemonData[0])][std::stoi(pokemonData[1])] = newPokemon;
}

void PC::buildRosterPokemon(std::string line)
{
	std::vector<std::string> pokemonData = splitString(line, '-');

	Attack pokemonAttacks[4] = { id_to_attack[std::stoi(pokemonData[3])],id_to_attack[std::stoi(pokemonData[5])],id_to_attack[std::stoi(pokemonData[7])],id_to_attack[std::stoi(pokemonData[9])] };
	pokemonAttacks[0].setPP(std::stoi(pokemonData[4]));
	pokemonAttacks[1].setPP(std::stoi(pokemonData[6]));
	pokemonAttacks[2].setPP(std::stoi(pokemonData[8]));
	pokemonAttacks[3].setPP(std::stoi(pokemonData[10]));

	Pokemon newPokemon(id_to_species[std::stoi(pokemonData[2])], std::stoi(pokemonData[12]), pokemonAttacks);
	newPokemon.setName(pokemonData[1]);
	newPokemon.setHP(std::stoi(pokemonData[14]));
	newPokemon.gainXP(std::stoi(pokemonData[13]));
	newPokemon.setItem(&id_to_item[std::stoi(pokemonData[11])]);
	newPokemon.setStatus(&id_to_status[std::stoi(pokemonData[15])]);

	m_roster[std::stoi(pokemonData[0])] = newPokemon;
}

void PC::buildItemSection(std::string line)
{
	std::vector<std::string> pokemonData = splitString(line, '-');
	m_items.push_back(std::stoi(pokemonData.at(0)));
}

void PC::buildCoordinates(std::string line)
{
	std::vector<std::string> pokemonData = splitString(line, '-');
	m_playerTileX = std::stoi(pokemonData.at(0));
	m_playerTileY = std::stoi(pokemonData.at(4));
	m_playerMapID = std::stoi(pokemonData.at(7));
	m_playerDirection = std::stoi(pokemonData.at(10));
	m_buildingEvent = std::stoi(pokemonData.at(13));
	m_cutsceneCount = std::stoi(pokemonData.at(15));
}

void PC::buildNptData(std::string line)
{
	std::vector<bool> data;
	for (int i = 0; i < line.size(); i++)
	{
		if (line.at(i) == '1')
			data.push_back(true);
		else
			data.push_back(false);
	}
	m_nptData.push_back(data);
}
