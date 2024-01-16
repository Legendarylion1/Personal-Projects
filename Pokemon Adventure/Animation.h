#pragma once

#include <iostream>
#include <functional>
#include "Trainer.h"
#include "Renderer.h"
#include "Input.h"


namespace animationControls
{

	struct trainerAnimationPoint
	{
		Direction direction;
		SpriteState spriteState;
		float time;
	};

	static void controlAnimation(float startingValue, float timeMultiplier, float* value, bool addToValue, Renderer* renderer)
	{
		bool firstEntered = true;
		float newY = startingValue;
		float oldY = startingValue;
		float lastTime = 0.0f;
		float deltaTime = 0.0f;

		float deltaValue = 0.0f;

		while (newY < oldY + (TILE_SIZE * TILE_MULTIPLIER))
		{
			//Movement Calculations
			float curTime = (float)glfwGetTime();
			deltaTime = curTime - lastTime;
			lastTime = curTime;

			if (firstEntered)
				deltaTime = 0.0f;

			if (newY + ((TILE_SIZE * TILE_MULTIPLIER) * deltaTime) * timeMultiplier >= oldY + (TILE_SIZE * TILE_MULTIPLIER))
			{
				deltaValue = (oldY + (TILE_SIZE * TILE_MULTIPLIER)) - newY;
				newY += deltaValue;
			}
			else
			{
				deltaValue = (TILE_SIZE * TILE_MULTIPLIER) * deltaTime * timeMultiplier;
				newY += deltaValue;
			}

			if (addToValue)
				*value += deltaValue;
			else
				*value -= deltaValue;

			renderer->onUpdate();

			firstEntered = false;
		}
	}

	static void controlAnimation(float* playerX, float* playerY, bool useX, bool addToValue, bool jump, std::vector<trainerAnimationPoint> animationPoints, float timeMultiplier, Renderer* renderer)
	{
		bool firstEntered = true;

		float newY = 0.0f;
		float jumpMultiplier = 1.0f;
		float lastTime = 0.0f;
		float deltaTime = 0.0f;
		float deltaValue = 0.0f;
		float curHeight = 0.0f;
		float maxHeight = 10.0f;

		unsigned int animationIndex = 0;

		if (jump)
		{
			jumpMultiplier = 2.0f;
			timeMultiplier = timeMultiplier * 0.5f;
		}

		while (newY < (TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier))
		{
			//Movement Calculations
			float curTime = (float)glfwGetTime();
			deltaTime = curTime - lastTime;
			lastTime = curTime;

			if (firstEntered)
				deltaTime = 0.0f;

			if (newY + ((TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier) * deltaTime) * timeMultiplier >= (TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier))
			{
				deltaValue = (TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier) - newY;
				newY += deltaValue;
			}
			else
			{
				deltaValue = (TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier) * deltaTime * timeMultiplier;
				newY += deltaValue;
			}


			if (addToValue)
			{
				if (useX)
					*playerX += deltaValue;
				else
					*playerY += deltaValue;
			}
			else
			{
				if (useX)
					*playerX -= deltaValue;
				else
					*playerY -= deltaValue;
			}

			if (animationIndex < animationPoints.size())
			{
				if (newY >= ((TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier) * animationPoints.at(animationIndex).time))
				{
					renderer->setPlayerAnimation(animationPoints.at(animationIndex).direction, animationPoints.at(animationIndex).spriteState);
					animationIndex++;
				}
			}

			if (jump)
			{
				if (newY <= ((TILE_SIZE * TILE_MULTIPLIER * jumpMultiplier)) * (1.0f/2.0f))
				{
					if (curHeight + deltaValue <= maxHeight)
					{
						curHeight += deltaValue;
						renderer->setPlayerScale(curHeight);
					}
					else
					{
						renderer->setPlayerScale(maxHeight);
					}
				}
				else
				{
					if (curHeight - deltaValue >= 0.0f)
					{
						curHeight -= deltaValue;
						renderer->setPlayerScale(curHeight);
					}
					else
					{
						renderer->setPlayerScale(0.0f);
					}
				}
			}

			renderer->setPlayerCoords(*playerX, *playerY);
			renderer->onUpdate();

			firstEntered = false;
		}
	}

	static void animateDelay(float multiplier, Renderer* renderer)
	{
		float falseValue = 0;
		controlAnimation(0, multiplier, &falseValue, false, renderer);
	}

	static void awaitClick(GLFWwindow* window, Renderer* renderer, Input* input)
	{
		bool firstEntered = true;

		while (!glfwWindowShouldClose(window))
		{

			if (input->getClicked() && !firstEntered)
				break;

			firstEntered = false;
			renderer->setAwaitClick(true);
			renderer->onUpdate();
			input->onUpdate();
		}

		//TODO: Make sure this didnt break anything
		renderer->setAwaitClick(false);
	}
}