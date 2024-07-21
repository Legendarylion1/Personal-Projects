#include "Game/Game.h"

///
///																					UNOFFICIAL TODO LIST
///		NOTE: I tend to forget about this list because I have an updated list on my phone that I reference
/// 
///						~ BATTLE SIMULATOR ~
///		Do more research on what to do if we crit and its super effective. Should we say both. Should it just be one message?
/// 
///						~ GENERAL ~
/// 
///		Remove all duplicate references. Theres a lot of files being reference that dont need to be due to a lower file
///		Share the logger with all functions in setup
///		Give defaults to struct variables
///		Try to create the big shared string. Really think about the viability of it. Who needs what information and how we pass that information cleanly
///		Handle White out
///		Improve Critical Error data. Like add more last minute data that can help diagnose the problem
///		Refactor Code for clarity
/// 
///						~ GRAPHICS ~
///		
///		After a pokemon levels up print out the stats of the leveled up pokemon and show the increases/decreases in stats
///		Animate Pokemon Swap
///		Animate Evolution
/// 
///						~ Cutscene ~
///		Needs to call renderer for moving characters
/// 
///		When Production Change the locations for save files and the python script


int main()
{

	srand(time(NULL));
	
	Game game;
	game.run();
	
	return 0;

}