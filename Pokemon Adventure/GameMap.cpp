#include "GameMap.h"

GameMap::GameMap()
{
}

void GameMap::setup(bool* up, bool* down, bool* left, bool* right, bool* interact, Renderer* renderer)
{
	m_up = up;
	m_down = down;
	m_left = left;
	m_right = right;
	m_interact = interact;

	setupMapSections();

	m_allSections.at(m_currentMap).setupRenderer(renderer);

	initBuildingEvent(renderer);
}

std::vector<unsigned int> GameMap::pollEvents()
{
	///		~ DRAWING MAP ~
	/// # -	Boundary
	/// R - Return
	/// N - Nurse
	/// P - PokeCenter
	/// C - PC
	/// S - PokeMart
	/// I - Buy Items
	/// M - Buy Moves
	/// G - Grass
	/// T - Trainer
	/// 0 - Top Link
	/// 1 - Bot Link
	/// U - Cutscene
	///		~ DRAWING MAP ~

	std::vector<unsigned int> events;
	char tileValue = ' ';

	if (nptSpottedIndex() != -1)
	{
		//TODO: Remove
		std::cout << "Trainer has been spotted\n";
		events.push_back(Events::trainerSpotted);
		return events;
	}

	if (*m_up)
	{
		if (m_yPos + 1 < m_allSections.at(m_currentMap).getHeight())
		{
			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos + 1).at(m_xPos);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos + 1).at(m_xPos);

			if (tileValue == 'P')
			{
				events.push_back(Events::pokeCenter);
				return events;
			}
			if (tileValue == 'S')
			{
				events.push_back(Events::pokeShop);
				return events;
			}
			if (tileValue == 'G')
			{
				events.push_back(Events::inGrass);
			}
			if (tileValue != '#' && tileValue != 'N' && tileValue != 'C' && tileValue != 'I' && tileValue != 'M' && tileValue != 'T')
			{
				events.push_back(Events::movedUp);
			}
			if (tileValue == '#' || tileValue == 'N' || tileValue == 'C' || tileValue == 'I' || tileValue == 'M' || tileValue == 'T')
			{
				events.push_back(Events::turnUp);
			}
			if (tileValue == 'U')
			{
				events.push_back(Events::startCutScene);
			}
			if (tileValue == '0')
			{
				events.push_back(Events::transferUp);
			}
		}
	}
	else if (*m_down)
	{
		if (m_currentBuilding.getHeight() != 0 && m_currentBuilding.sectionLayout.at(m_yPos).at(m_xPos) == 'R')
		{
			events.push_back(Events::returnSection);
			return events;
		}

		if (m_yPos - 1 >= 0)
		{

			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos - 1).at(m_xPos);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos - 1).at(m_xPos);

			if (tileValue == 'G')
			{
				events.push_back(Events::inGrass);
			}
			if (tileValue != '#' && tileValue != 'T')
			{
				events.push_back(Events::movedDown);
			}
			if (tileValue == '#' || tileValue == 'T')
			{
				events.push_back(Events::turnDown);
			}
			if (tileValue == 'U')
			{
				events.push_back(Events::startCutScene);
			}
			if (tileValue == '1')
			{
				events.push_back(Events::transferDown);
			}
		}
	}
	else if (*m_left)
	{
		if (m_xPos - 1 >= 0 )
		{


			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos).at(m_xPos - 1);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos).at(m_xPos - 1);

			if (tileValue == 'G')
			{
				events.push_back(Events::inGrass);
			}
			if (tileValue != '#' && tileValue != 'T')
			{
				events.push_back(Events::movedLeft);
			}
			if (tileValue == '#' || tileValue == 'T')
			{
				events.push_back(Events::turnLeft);
			}
			if (tileValue == 'U')
			{
				events.push_back(Events::startCutScene);
			}
			if (tileValue == '2')
			{
				events.push_back(Events::transferLeft);
			}
		}
	}
	else if (*m_right)
	{
		if (m_xPos + 1 < m_allSections.at(m_currentMap).getWidth())
		{

			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos).at(m_xPos + 1);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos).at(m_xPos + 1);

			if (tileValue == 'G')
			{
				events.push_back(Events::inGrass);
			}
			if (tileValue != '#' && tileValue != 'T')
			{
				events.push_back(Events::movedRight);
			}
			if (tileValue == '#' || tileValue == 'T')
			{
				events.push_back(Events::turnRight);
			}
			if (tileValue == 'U')
			{
				events.push_back(Events::startCutScene);
			}
			if (tileValue == '3')
			{
				events.push_back(Events::transferRight);
			}
		}
	}
	else if (*m_interact)
	{
		if (m_characterDirection == Direction::UP)
		{
			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos + 1).at(m_xPos);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos + 1).at(m_xPos);


			if (tileValue == 'C')
			{
				events.push_back(Events::interactPC);
			}
			else if (tileValue == 'N')
			{
				events.push_back(Events::interactNurse);
			}
			else if (tileValue == 'T')
			{
				std::cout << "Interact Trainer Event Pushed Back\n";
				events.push_back(Events::interactTrainer);
			}
			else if (tileValue == 'I')
			{
				events.push_back(Events::interactItemBuy);
			}
			else if (tileValue == 'M')
			{
				events.push_back(Events::interactMoveBuy);
			}

		}
		else if (m_characterDirection == Direction::DOWN)
		{
			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos - 1).at(m_xPos);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos - 1).at(m_xPos);

			if (tileValue == 'T')
			{
				std::cout << "Interact Trainer Event Pushed Back\n";
				events.push_back(Events::interactTrainer);
			}


		}
		else if (m_characterDirection == Direction::LEFT)
		{
			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos).at(m_xPos - 1);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos).at(m_xPos - 1);


			if (tileValue == 'T')
			{
				std::cout << "Interact Trainer Event Pushed Back\n";
				events.push_back(Events::interactTrainer);
			}

		}
		else if (m_characterDirection == Direction::RIGHT)
		{
			if (m_currentBuilding.getHeight() == 0)
				tileValue = m_allSections.at(m_currentMap).sectionLayout.at(m_yPos).at(m_xPos + 1);
			else
				tileValue = m_currentBuilding.sectionLayout.at(m_yPos).at(m_xPos + 1);


			if (tileValue == 'T')
			{
				std::cout << "Interact Trainer Event Pushed Back\n";
				events.push_back(Events::interactTrainer);
			}

		}
	}


	return events;
}

glm::vec2 GameMap::swapMapSections(unsigned int direction, Renderer* renderer)
{
	m_currentMap = m_allSections.at(m_currentMap).getLinkedSection(direction).getID();

	m_allSections.at(m_currentMap).setupRenderer(renderer);

	return m_allSections.at(m_currentMap).getSpawn(direction);
}

glm::vec2 GameMap::swapPokeCenter(Renderer* renderer)
{
	m_prevMap = m_currentMap;
	m_currentBuilding = m_pokeCenter;

	m_pokeCenter.setupRenderer(renderer);

	return m_pokeCenter.getPokeCenterSpawn();
}

glm::vec2 GameMap::swapPokeShop(Renderer* renderer)
{
	m_prevMap = m_currentMap;
	m_currentBuilding = m_pokeShop;

	m_pokeShop.setupRenderer(renderer);

	return m_pokeShop.getPokeShopSpawn();
}

glm::vec2 GameMap::returnFromBuilding(Renderer* renderer)
{
	m_currentMap = m_prevMap;

	unsigned int location = 0;


	if (m_currentBuilding.getPokeCenterSpawn() != glm::vec2(0, 0))
		location = 1;
	else if (m_currentBuilding.getPokeShopSpawn() != glm::vec2(0, 0))
		location = 2;


	m_currentBuilding = MapSection();

	m_allSections.at(m_currentMap).setupRenderer(renderer);

	if (location == 1)
		return m_allSections.at(m_currentMap).getPokeCenterSpawn();
	else if (location == 2)
		return m_allSections.at(m_currentMap).getPokeShopSpawn();
	else
		return glm::vec2(0, 0);
}

glm::vec2 GameMap::getPlayerPosition()
{
	return glm::vec2(m_xPos,m_yPos);
}

void GameMap::setCurrentMap(unsigned int mapID)
{
	m_currentMap = mapID;
}

void GameMap::setBuildingEvent(unsigned int buildingEvent)
{
	m_buildingEvent = buildingEvent;
}

void GameMap::setPlayerPosition(unsigned int x, unsigned int y)
{
	m_xPos = x;
	m_yPos = y;
}

void GameMap::setNptData(std::vector<std::vector<bool>> nptData)
{
	for (int i = 0; i < nptData.size(); i++)
	{
		m_allSections.at(i).setNptData(nptData.at(i));
	}
}

void GameMap::adjustPlayerPosition(unsigned int x, unsigned int y)
{
	m_xPos += x;
	m_yPos += y;
}

void GameMap::adjustPlayerDirection(unsigned int direction)
{
	m_characterDirection = direction;
}

std::vector<std::vector<bool>> GameMap::getNptData()
{
	std::vector<std::vector<bool>> nptData;

	for (int i = 0; i < m_allSections.size(); i++)
	{
		nptData.push_back(m_allSections.at(i).getNptData());
	}

	return nptData;
}

std::vector<unsigned int> GameMap::getMapSpecies()
{
	return m_allSections.at(m_currentMap).getPokemonIDs();
}

std::vector<unsigned int> GameMap::getMapItems()
{
	return m_allSections.at(m_currentMap).getAvailableItems();
}

unsigned int GameMap::getMapLevelCap()
{
	return m_allSections.at(m_currentMap).getLevelCap();
}

unsigned int GameMap::getMapID()
{
	return m_currentMap;
}

MapSection& GameMap::getMapSection()
{
	return m_allSections.at(m_currentMap);
}

NPT& GameMap::getNPT()
{
	return m_allSections.at(m_currentMap).getAI().at(nptSpottedIndex(false));
}

NPT& GameMap::getNPT(unsigned int index)
{
	return m_allSections.at(m_currentMap).getAI().at(index);
}

unsigned int GameMap::getNptID(NPT& npt)
{
	std::cout << "Trying to get NPTID\n";
	for (int i = 0; i < m_allSections.at(m_currentMap).getAI().size(); i++)
	{
		if (npt.getX() == m_allSections.at(m_currentMap).getAI().at(i).getX() && npt.getY() == m_allSections.at(m_currentMap).getAI().at(i).getY())
		{
			return i;
		}
	}
	std::cout << "[GameMap] Error getNPTID():  ID not found" << std::endl;
	exit(4);
}

void GameMap::setupMapSections()
{
	///		~ DRAWING MAP ~
	/// # -	Boundary
	/// R - Return
	/// N - Nurse
	/// P - PokeCenter
	/// C - PC
	/// S - PokeMart
	/// I - Buy Items
	/// M - Buy Moves
	/// G - Grass
	/// T - Trainer
	/// 0 - Top Link
	/// 1 - Bot Link
	/// U - Cutscene
	///		~ DRAWING MAP ~



	///		~ WRITING CUTSCENE ~
	/// U - Up
	///	D - Down
	///	L - Left
	///	R - Right
	///	S - Speak
	///		~ WRITING CUTSCENE ~
	/// 
	///		~ NPT DIALOGUE EXAMPLE ~
	/// I0X5Y10U10R1SSI1L1SS
	/// I0 - Set AI Index to 0
	/// X5 - Set the X to 5
	/// Y10 - set the Y to 10
	/// U10 - Walk up 10 tiles
	/// R1 - Walk right 1 tile
	/// S - Speak dialogue option
	/// S - speak dialogue option (goes to next dialogue)
	/// I1 - Set AI Index to 1 (next AI)
	/// L1 - Walk Left 1 tile
	/// S - speak dialogue option (AI index 1 and his first dialogue option)
	/// S - speak dialogue option (AI index 1 and his second dialogue option)
	///		~ NPT DIALOGUE EXAMPLE ~
	
	unsigned int TOP = Direction::UP;
	unsigned int BOTTOM = Direction::DOWN;

	std::vector<std::string> pokeCenterLayout = {
		"##############",
		"##############",
		"####     ##C##",
		"####     #   #",
		"#  ####N##   #",
		"#            #",
		"#####     ####",
		"#####     ####",
		"#####     ####",
		"#    RRR     #"
	};
	m_pokeCenter = MapSection("Images/Map/PokeCenter.png", 100, 224, 160, pokeCenterLayout);
	m_pokeCenter.setPokeCenterSpawn(6, 0);



	std::vector<std::string> pokeShopLayout = {
		"##############",
		"##############",
		"## #     #####",
		"## #     #  ##",
		"#  ##I##M#  ##",
		"#           ##",
		"# ##     ## ##",
		"# ##     ## ##",
		"# ##     ## ##",
		"#    RRR     #"
	};
	m_pokeShop = MapSection("Images/Map/PokeShop.png", 101, 224, 160, pokeShopLayout);
	m_pokeShop.setPokeShopSpawn(6, 0);

	//TODO: Create entrances for the homes and pokemart
	

	// Home Village and Route 1
	std::vector<std::string> homeVillageLayout = {
		"###############000#################",
		"###############000#################",
		"###############000#################",
		"###############000#################",
		"###############000#################",
		"##############     ################",
		"########                    #######",
		"########              GGGGG #######",
		"########              GGGGG #######",
		"########                    #######",
		"########        ##########  #######",
		"######## ########GGG  GGG##########",
		"######## ########GGG   GG##########",
		"######## ########        ##########",
		"######## ########        ##########",
		"######## ###########  #############",
		"########           #        #######",
		"########                    #######",
		"########                    #######",
		"########                    #######",
		"########GGG                 #######",
		"########GGG##               #######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##          GGGGG#######",
		"########GGG##          GGGGG#######",
		"########GGG##          GGGGG#######",
		"#############          GGGGG#######",
		"#############          GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########                    #######",
		"########                    #######",
		"###############   #################",
		"###############   #################",
		"###############   #################",
		"###############   #################",
		"       #      #   ##        ##     ",
		"       #                ### #      ",
		"     ###                ### #      ",
		"     ##########         ### #      ",
		"       ########   #     ### #      ",
		"       ########             #      ",
		"       #    #               ###    ",
		"       #                    ###    ",
		"       #                    ###    ",
		"       #                ##  ###    ",
		"       #          #####     #      ",
		"     ###  #####   #####     #      ",
		"     ###  #####   #############    ",
		"       #  #####    # # ########    ",
		"       #      #        ########    ",
		"       #              ##    ###    ",
		"     ### ##           ##    #      ",
		"     ### ##                 #      ",
		"     ###                    #      ",
		"     ###                    #      ",
		"       ######################      ",
		"            ##   ##     ##         ",
		"            ##   ##     ##         ",
		"            ##   ##     ##         ",
		"                                   ",
		"                                   ",
		"                                   "
	
	};
	MapSection homeVillage = MapSection("Images/Map/HVRoute1.png", 0, 560, 1120, homeVillageLayout);
	std::vector<unsigned int> pokemonInArea = { speciesIDs::charmander, speciesIDs::torchic };
	homeVillage.setPokemonStats(pokemonInArea, 2);
	homeVillage.setSpawn(BOTTOM, 16, 64);


	Attack attackSet[4] = { id_to_attack[AttackIDs::lightningBolt],id_to_attack[AttackIDs::kick],id_to_attack[AttackIDs::null],id_to_attack[AttackIDs::null] };
	Pokemon test1 = Pokemon(id_to_species[speciesIDs::charmander], 2, attackSet);
	test1.setName("Test1");
	
	Pokemon test2 = Pokemon(id_to_species[speciesIDs::charmander], 3, attackSet);
	test2.setName("Test2");


	NPT test = NPT("AI", 18, 12, Direction::DOWN, 3);
	test.nptResources.addedPokemon(test1);
	test.nptResources.addedPokemon(test2);
	test.setFightText(std::vector<std::string>{"Im testing out my new","Will you be my"}, std::vector<std::string>{"Pokemon","Opponent"});
	test.setDefaultText(std::vector<std::string>{"Default Text", "Giggga"}, std::vector<std::string>{"for all", "Chad"});
	test.setCutsceneText(std::vector<std::string>{"Test Top Text 1","Thank god it Works"}, std::vector<std::string>{"Test Bot Text 1","Cutscenes are complete"});



	homeVillage.addAI(test);

	homeVillage.setCutsceneID(0);

	homeVillage.setCutsceneScript("I0X18Y8U3R1U1L1SS");
	
	
	// Small Town and Route 2
	std::vector<std::string> smallTownLayout = {
	"     #       #          #     ",
	"     #       #          #     ",
	"     #       #          #     ",
	"     #       #          #     ",
	"     #       #00#########     ",
	"     #       #  #########     ",
	"     #       #    GGGGGG#     ",
	"     #########    GGGGGG#     ",
	"     #    GGGG#######GGG#     ",
	"     #    GGGG#     #GGG#     ",
	"     #######GG#######GGG#     ",
	"     #     #GG#GGG###GGG#     ",
	"     ####  #GG#GGG###GGG#     ",
	"     #GG#  #GG#GGG GGGGG#     ",
	"     #GG#  #GG#GGG GGGGG#     ",
	"     #GG#  #GG#    GGGGG#     ",
	"     #GG#  #GG#####   ###     ",
	"     #GG####GG#####   # #     ",
	"     #GGGGGGGGGGGGG   # #     ",
	"     #GGGGGGGGGGGGG   # #     ",
	"     ####  ############ #     ",
	"     #  #  #            #     ",
	"     #  #  #            #     ",
	"     #  #  #  ########  #     ",
	"     #  #  #  #GG    #  #     ",
	"     #  #  #  #GG    #  #     ",
	"     #  #  #  #GG#####  #     ",
	"     #  #  ####GG#      #     ",
	"     #  #   GGGGG#      #     ",
	"     #  #   GGGGG#      #     ",
	"     #  ######GGG#      #     ",
	"     #       #GGG#      #     ",
	"     #       #GGG#      #     ",
	"     ##      #GGG#      #     ",
	"     # # #   #GGG###### #     ",
	"     # ## ####GGG##   ###     ",
	"     # ##   ##   #     ##     ",
	"     #                 ##     ",
	"     #########   ########     ",
	"     #####  ##   ###    #     ",
	"     #########   ### ## #     ",
	"     ##  ####    ### ## #     ",
	"     #   ####        ## #     ",
	"     #               ## #     ",
	"     #   ####           #     ",
	"     ########     ##### #     ",
	"     ########     ##### #     ",
	"     #            ##### #     ",
	"     # #####     ###SS# #     ",
	"     # #####            #     ",
	"     # #####            #     ",
	"     # ##PP# #          #     ",
	"     #  #          ######     ",
	"     #             #### #     ",
	"     #                  #     ",
	"     #########111########     ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              "
};
	MapSection smallTown = MapSection("Images/Map/SmallTownRoute2.png", 1, 480, 960, smallTownLayout);
	pokemonInArea = { speciesIDs::charmander, speciesIDs::torchic };
	smallTown.setPokemonStats(pokemonInArea, 5);
	smallTown.setSpawn(TOP, 15, 7);

	smallTown.setPokeCenterSpawn(10,8);
	smallTown.setPokeShopSpawn(21, 11);

	//TODO: Test more than 6 items when buying from the store
	smallTown.setItemsAvailable(std::vector<unsigned int>{itemIDs::pokeball, itemIDs::greatball, itemIDs::ultraball, itemIDs::smallHeal});




	homeVillage.linkSection(Direction::UP, smallTown);
	smallTown.linkSection(Direction::DOWN, homeVillage);




	m_allSections.push_back(homeVillage);
	m_allSections.push_back(smallTown);
}

void GameMap::initBuildingEvent(Renderer* renderer)
{
	//TODO: Enforce Ordering of functions.
	//Some functions NEEEEED to go before one another. Please enforce :)

	if (m_buildingEvent == Events::pokeCenter)
	{
		swapPokeCenter(renderer);
	}
	else if (m_buildingEvent == Events::pokeShop)
	{
		swapPokeShop(renderer);
	}
}

int GameMap::nptSpottedIndex(bool evaluatingEvents)
{
	int nptIndex = -1;


	//Check and see if interact is pressed.
	//If interact is pressed then we can check the tile right next to the player which literally has to be an AI
	// Then we return the index of the spotted AI
	// IF somehow we dont find one, like in the case of the player running around while holding interact or pressing interact constantly for no reason then we go below

	for (int i = 0; i < m_allSections.at(m_currentMap).getAI().size(); i++)
	{
		unsigned int x = m_allSections.at(m_currentMap).getAI().at(i).getTileX();
		unsigned int y = m_allSections.at(m_currentMap).getAI().at(i).getTileY();
		unsigned int detectDistance = m_allSections.at(m_currentMap).getAI().at(i).getDetectDistance();
		unsigned int direction = m_allSections.at(m_currentMap).getAI().at(i).getDirection();

		unsigned int maxHeight = m_allSections.at(m_currentMap).getHeight() / TILE_SIZE;
		unsigned int maxWidth = m_allSections.at(m_currentMap).getWidth() / TILE_SIZE;


		// If we are trying to click the NPT.
		// TODO: I can probably remove evaluating events but its not necessary
		if (*m_interact && !evaluatingEvents)
		{
			if (m_characterDirection == Direction::UP)
			{
				if (m_xPos == x && m_yPos + 1 == y)
					return i;
			}
			else if (m_characterDirection == Direction::DOWN)
			{
				if (m_xPos == x && m_yPos - 1 == y)
					return i;
			}
			else if (m_characterDirection == Direction::LEFT)
			{
				if (m_xPos - 1 == x && m_yPos == y)
					return i;
			}
			else if (m_characterDirection == Direction::RIGHT)
			{
				if (m_xPos + 1 == x && m_yPos == y)
					return i;
			}
		}
		

		if (!m_allSections.at(m_currentMap).getAI().at(i).nptResources.hasPokemon())
			return nptIndex;

		for (int d = 1; d <= detectDistance; d++)
		{
			if (direction == Direction::UP)
			{
				if (y + d < maxHeight)
				{
					if (y + d == m_yPos)
					{
						if (x == m_xPos)
						{
							std::cout << "[UP] Trainer coords (" << m_xPos << "," << m_yPos << ")\t| AI Coords (" << x << "," << y << ")\n";
							return i;
						}
					}
				}
			}
			else if (direction == Direction::DOWN)
			{
				if (y - d >= 0)
				{
					if (y - d == m_yPos)
					{
						if (x == m_xPos)
						{
							std::cout << "[DOWN] Trainer coords (" << m_xPos << "," << m_yPos << ")\t| AI Coords (" << x << "," << y << ")\n";
							return i;
						}
					}
				}
			}
			else if (direction == Direction::LEFT)
			{
				if (x - d >= 0)
				{
					if (y == m_yPos)
					{
						if (x - d == m_xPos)
						{
							std::cout << "[LEFT] Trainer coords (" << m_xPos << "," << m_yPos << ")\t| AI Coords (" << x << "," << y << ")\n";
							return i;
						}
					}
				}
			}
			else if (direction == Direction::RIGHT)
			{
				if (x + d < maxWidth)
				{
					if (y == m_yPos)
					{
						if (x + d == m_xPos)
						{
							std::cout << "[RIGHT] Trainer coords (" << m_xPos << "," << m_yPos << ")\t| AI Coords (" << x << "," << y << ")\n";
							return i;
						}
					}
				}
			}
		}
	}

	return nptIndex;
}
