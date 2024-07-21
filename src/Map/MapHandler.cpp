#include "MapHandler.h"

MapHandler::MapHandler(Trainer* trainer, Renderer* renderer)
{

	//renderer->loadMap(SectionID::MAIN_SECTION);
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
	/// A - AI
	/// L - Linked Section
	/// U - Cutscene
	/// 
	///			Jump not implemented yet
	/// V - Jump Down
	/// ^ - Jump Up
	/// > - Jump Right
	/// < - Jump Left
	///		~ DRAWING MAP ~
	/// 
	/// Maps start at 0,0 in the bottom left

	m_trainer = trainer;


	MapSection mapSection = MapSection(renderer);
	std::vector<std::string> map = {
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

	mapSection.setMap(map);
	mapSection.setID(SectionID::MAIN_SECTION);

	mapSection.addPokemonSpawn({ Rarity::COMMON, PokemonID::Baroot });
	mapSection.addPokemonSpawn({ Rarity::UNCOMMON, PokemonID::Bery });
	mapSection.addPokemonSpawn({ Rarity::RARE, PokemonID::Fitty });
	mapSection.setPokemonLevelCaps(1, 8);

	mapSection.setAvailableItems(std::vector<ItemID> {ItemID::POKEBALL, ItemID::GREATBALL, ItemID::SMALL_POTION, ItemID::MEDIUM_POTION, ItemID::LARGE_POTION, ItemID::ROID_JUICE, ItemID::MASTERBALL});

	NPT* testNPT = new NPT("Jake", CharacterID::FIRST_TRAINER, 27, 53, Direction::LEFT, 1000, 3);
	testNPT->setPokemon(0, Pokemon(baroot, 5));
	
	testNPT->addBattleDialogue({"Im so excited", "Lets fight"});
	testNPT->addNormalDialogue({"That was a good fight", "I need to train more"});
	
	
	testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::LEFT });
	testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::LEFT });
	testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::LEFT });
	testNPT->addScriptInstruction({ InstructionType::TURN, Direction::RIGHT });
	testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::RIGHT });
	testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::RIGHT });
	testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::RIGHT });
	testNPT->addScriptInstruction({ InstructionType::TURN, Direction::LEFT });
	
	
	mapSection.addNPT(testNPT);

	mapSection.linkSection({ 1,0 }, SectionID::LINKED_SECTION, { 4,5 });
	mapSection.addCutscene({ 11,1 }, CutSceneID::FIRST_CUTSCENE);

	addMapSection(mapSection);








	MapSection linkedMapSectionTest = MapSection(renderer);
	std::vector<std::string> secondMapTest = {
		"##############",
		"##############",
		"#           ##",
		"#           ##",
		"#           ##",
		"#           ##",
		"#           ##",
		"#           ##",
		"#           ##",
		"#          L##"
	};

	linkedMapSectionTest.setMap(secondMapTest);
	linkedMapSectionTest.setID(SectionID::LINKED_SECTION);

	NPT* secondTestNPT = new NPT("Norton", CharacterID::FIRST_TRAINER, 10, 3, Direction::UP, 500, 4);
	secondTestNPT->setPokemon(0, Pokemon(fitty, 5));

	secondTestNPT->addBattleDialogue({ "All my trianing has led me to this", "Lets go!" });
	secondTestNPT->addNormalDialogue({ "Aw man", "you sure are strong" });

	linkedMapSectionTest.addNPT(secondTestNPT);

	linkedMapSectionTest.linkSection({11,0}, SectionID::MAIN_SECTION, { 6,3 });

	addMapSection(linkedMapSectionTest);

}

void MapHandler::onUpdate()
{
	swapSections();
	m_mapSections[m_currentSection].onUpdate();
	//m_trainer->printLocation();
}

void MapHandler::addMapSection(MapSection section)
{
	if (m_mapSections.count(section.getID()) == 0)
		m_mapSections[section.getID()] = section;
	else
	{
		logger->log(LogLevel::CRITICAL, "Map Section has already been added", "addMapSection", "MapHandler");
		logger->reportCriticalError(ErrorCodes::INVALID_ELEMENT);
	}
}

void MapHandler::swapSections()
{
	if (m_mapSections[m_currentSection].getMapTile(m_trainer->position.coords) != 'L')
		return;

	Coordinate playerSpawn = m_mapSections[m_currentSection].getPlayerSpawn(m_trainer->position.coords);
	SectionID linkedSection = m_mapSections[m_currentSection].getLinkedSection(m_trainer->position.coords);

	m_currentSection = linkedSection;
	m_trainer->position.coords = playerSpawn;

	m_mapSections[m_currentSection].resetAIPositions();
	m_mapSections[m_currentSection].loadMap();
}

bool MapHandler::isValidCharacterPosition(Coordinate coords)
{
	char tile = m_mapSections[m_currentSection].getMapTile(coords);

	switch (tile)
	{
	case '#':
	case 'I':
	case 'M':
	case 'N':
	case 'P':
	case 'C':
	case 'A':
		return false;
	default:
		return true;
	}


	//Add all of the checks for the tile. If it is the player AI and everything
}
