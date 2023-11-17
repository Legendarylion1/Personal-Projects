#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
/*
		1656	Lines of code	4/21/23
		4500	Lines of code	720 header, 3780 cpp - 5/12/23

			TODO

			~ High Priority ~
				- AI need to set off the legendary gun animation
				- When pressing tab you cannot move down to the left
				- Items scale in stats as the game goes on
				- Players get teleported to arena when fight begins
				- Online Functionality
				- Add start Screen
				- Add death screen
				- Limit fps
				- Count player kills for end screen
				- Camera matrix z is causing the sword to overlay the tab menu fix.
					* Maybe create another torin definition that boosts elements by 2.0f if they are UI elements
				- Throwables in projectile need to be drawn and animated too

			~ Medium Priority ~

				- AI spear seems to do double damage
				- Fix function descriptions on modified functions
				- AI with gun sometimes dont shoot. (Maybe)
				- I dont like when the AI walk over eachother. Try to keep distance between them. Like half a playerSize is good
				- Throwables either arent on the same plane as the player or something, but they need to be overlayed how they were before. Maybe check github to see what changed
				- If we want to we can batch render higher number of particles, but split up the draw call. So maybe 500 in one and 500 in another
				- Figure out how to make particles omni directional and not just based on quadrants
					* For Gun and Sword

			~ Low Priority ~

				- Distance function can be looked at for a rework. I dont know if it is possible though
				- take a look at deleting ebo vectors directly after creation. To see what happens (slowed down the game a lot last time)
				- Remove hit ids for AI and player bullets
				- Possibly rework AI index for throwables
				- Rework starting item
				- Make all member variables MEMBER VARIABLES
				- Rename map section function variables because they confict with variable names
				- Particle Positions stay from where they last were if you swap weapons
				- Maybe rework the particle system to be a centralized system. Where you send particles and it just draws what it has. That way particles can linger and dont blink out of existence.
			
*/

int main()
{
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "Dungeon Crawler", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	//0,0 is bottom left, and then width height
	glViewport(0, 0, WINDOWWIDTH, WINDOWHEIGHT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Game game(WINDOWWIDTH, WINDOWHEIGHT);

	bool closeWindow = false;
	while (!game.shouldExit())
	{
		glfwSetMouseButtonCallback(window, mouseButtonCallBack);
		closeWindow = true;

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.05f, 0.73f, 0.24f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			if (game.recieveInput(window) == 1)
				game.nextLevel();
			else
				game.progressAI();

			if (!game.continueGame(window))
			{
				closeWindow = false;
				break;
			}


			game.drawGame();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		if (closeWindow)
			break;

		game.resetGame();
	}

	game.~Game();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}