#pragma once

#include "../Characters/Trainer/Trainer.h"
#include "../Game/Interactions/PC.h"
#include "../Map/MapHandler.h"
#include "../GlobalData/helperFunctions.h"
#include "../Characters/CharacterMover.h"

enum FileNumber
{
	FILE_ONE,
	FILE_TWO,
	FILE_THREE
};

static const std::string MAIN_HEADER = "MAIN_HEADER";
static const std::string INPUT_HEADER = "INPUT_HEADER";
static const std::string TRAINER_HEADER = "TRAINER_HEADER";
static const std::string RENDERER_HEADER = "RENDERER_HEADER";
static const std::string ROSTER_HEADER = "ROSTER_HEADER";
static const std::string PC_HEADER = "PC_HEADER";
static const std::string ITEM_HEADER = "ITEM_HEADER";

class DataManager
{
public:

	DataManager() {};

	void setup(Trainer* player, PC* pc, MapHandler* mapHandler, Input* input, Renderer* renderer, Timer* timer, CharacterMover* characterMover);

	void setFile(FileNumber fileNumber) { m_file = fileNumber; };

	void saveGame();
	void loadGame();

	void loadNewGame();

	void deleteSave(FileNumber fileNumber);
	HeaderSave loadHeader(FileNumber fileNumber);

private:

	void saveHeader(std::ofstream* file);
	void saveInput(std::ofstream* file);
	void saveTrainer(std::ofstream* file);
	void saveRoster(std::ofstream* file);
	void savePC(std::ofstream* file);
	void saveRenderer(std::ofstream* file);
	void saveItems(std::ofstream* file);

	void loadHeader(std::vector<std::string> data);
	void loadInput(std::vector<std::string> data);
	void loadTrainer(std::vector<std::string> data);
	void loadRoster(std::vector<std::string> data);
	void loadPC(std::vector<std::string> data);
	void loadRenderer(std::vector<std::string> data);
	void loadItem(std::vector<std::string> data);

private:
	void loadNewInput();
	void loadNewRenderer();

private:

	FileNumber m_file = FILE_TWO;

	Renderer* m_renderer = nullptr;
	Trainer* m_player = nullptr;
	PC* m_pc = nullptr;
	MapHandler* m_mapHandler = nullptr;
	Input* m_input = nullptr;
	Timer* m_timer = nullptr;
	CharacterMover* m_characterMover = nullptr;
	ItemStorage* m_itemStorage = nullptr;

	
	std::unordered_map<FileNumber, std::string> m_fileLocation =
	{
		{FileNumber::FILE_ONE, "save1.data"},
		{FileNumber::FILE_TWO, "save2.data"},
		{FileNumber::FILE_THREE, "save3.data"}
	};

};