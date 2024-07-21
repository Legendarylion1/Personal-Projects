#pragma once
#include "../Graphics/PositionalData.h"

namespace BattleAnimations
{
	namespace
	{
		static int m_catchFrame = 30;
		static int m_catchDuration = 7;

		static int m_releaseFrame = 0;
		static int m_releaseDuration = 8; //TODO: Maybe 5

	}

	static void wildPokemonIntoPokeball(int frame, DynamicImageRenderData* wildPokemonData)
	{
		if (frame < m_catchFrame || frame > m_catchFrame + m_catchDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_catchDuration;

		int differenceDown = m_catchDuration - (frame - m_catchFrame);
		int differenceUp = frame - m_catchFrame;

		float dimensionMultiplier = frameMultiplier * differenceDown;

		wildPokemonData->widthPercent = 10.0f * dimensionMultiplier;
		wildPokemonData->heightPercent = 10.0f * (16.0f / 9.0f) * dimensionMultiplier;

		{
			float currentXPercent = 74.4f;
			float ballXPercent = ((740.0f / 1000.0f) * 100.0f);

			float amountToMove = ballXPercent - currentXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageX = currentXPercent + perFrameMovePercent;
		}
		

		{
			float currentYPercent = (443.0f / 563.0f) * 100.0f;
			float ballYPercent = ((523.0f / 563.0f) * 100.0f);

			float amountToMove = ballYPercent - currentYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageY = currentYPercent + perFrameMovePercentY;
		}

		{
			float amountToIncrease = 0.3f * frameMultiplier * differenceUp;
			wildPokemonData->color.r = 0.7f + amountToIncrease;
		}
	}

	static void wildPokemonEscapePokeball(int frame, DynamicImageRenderData* wildPokemonData)
	{
		if (frame < m_releaseFrame || frame > m_releaseFrame + m_releaseDuration)
			return;

		float frameMultiplier = 1.0f / (float)m_releaseDuration;
		int differenceUp =  frame - m_releaseFrame;
		int differenceDown = m_releaseDuration - (frame - m_releaseFrame);

		float dimensionMultiplier = frameMultiplier * differenceUp;

		wildPokemonData->widthPercent = 10.0f * dimensionMultiplier;
		wildPokemonData->heightPercent = 10.0f * (16.0f / 9.0f) * dimensionMultiplier;

		{
			float originalXPercent = 74.4f;
			float ballXPercent = ((741.0f / 1000.0f) * 100.0f);

			float amountToMove = originalXPercent - ballXPercent;

			float perFrameMovePercent = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageX = ballXPercent + perFrameMovePercent;
		}


		{
			float originalYPercent = (443.0f / 563.0f) * 100.0f;
			float ballYPercent = ((403.0f / 563.0f) * 100.0f);

			float amountToMove = originalYPercent - ballYPercent;

			float perFrameMovePercentY = amountToMove * frameMultiplier * differenceUp;

			wildPokemonData->percentageY = ballYPercent + perFrameMovePercentY;
		}

		{
			float amountToDecrease = 1.0f * frameMultiplier * differenceUp;
			wildPokemonData->color.r = 1.0f - amountToDecrease;
		}
	}
}