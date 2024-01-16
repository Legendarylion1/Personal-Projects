#include "GameEngine.h"

int main()
{

	//		~ High Priority ~
	
	//TODO: Set randomized seed, and re randomize at certain intervals. Bad luck is sometimes impossible
	//TODO: PC Background && Fight Background
	//TODO: post victory chat from opponent when battling. I think thats a thing but idk
	//TODO: Refactor input so that we dont need firstEntered variable. It will make sure to reset the counter if a button is being held.
	//TODO: Change Items to have a set order
	//TODO: Add settings class. Will handle the changing of all settings
	//TODO: General Refactor for engine and map sections
	//TODO: Finish animation refactor
	

	//		~ Medium Priority ~
	
	//TODO: Standardize the error codes
	//TODO: Pull PC, and Pokecenter heal into a namespace or class like thing so that its not happening in the engine
	//TODO: Setting for text speed
	//TODO: Setting for show framerate


	//		~ Low Priority ~
	
	//TODO: If Autosaving the game impacts gameplay then we may need to thread it
	//TODO: invesigate why FPS gets so low in menus
	//TODO: Organize Colors in the Renderer. We can easily have a map for colors.
	//TODO: When all done make all rendering scale based on screen size, and I suppose clicks need to be adjusted too :)
	//TODO: Link Inputs to the Renderer in the case of resize or the movement of graphical components
	//TODO: Add Shader Errors
	//TODO: Organize Images

	srand(time(NULL));
	
	GameEngine gameEngine;
	
	gameEngine.setup();
	
	gameEngine.run();
	
	gameEngine.shutdown();
	
	return 0;
}