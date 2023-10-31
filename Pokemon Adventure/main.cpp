#include "GameEngine.h"

int main()
{
	//TODO: Set randomized seed, and re randomize at certain intervals. Bad luck is sometimes impossible
	//TODO: When all done make all rendering scale based on screen size, and I suppose clicks need to be adjusted too :)
	//TODO: Standardize the error codes
	//TODO: Add Shader Errors
	//TODO: Organize Images
	//TODO: PC Background && Fight Background
	//TODO: Pull PC, and Pokecenter heal into a namespace or class like thing so that its not happening in the engine
	//TODO: Setting for text speed
	//TODO: Setting for show framerate
	//TODO: I probably have something somewhere but pokemon do not evolve until after the fight
	//TODO: post victory chat from opponent when battling. I think thats a thing but idk


	srand(time(NULL));
	
	GameEngine gameEngine;
	
	gameEngine.setup();
	
	gameEngine.run();
	
	gameEngine.shutdown();
	
	return 0;
}