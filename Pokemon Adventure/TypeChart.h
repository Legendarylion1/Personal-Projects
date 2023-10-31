#pragma once

#include <unordered_map>

static const unsigned int NOTYPE	= 100;

static const unsigned int NORMAL	= 0;
static const unsigned int FIRE		= 1;
static const unsigned int WATER		= 2;
static const unsigned int GRASS		= 3;


// {Attacker Type: {Defender Type: Effectiveness} } 
static std::unordered_map<unsigned int, std::unordered_map<unsigned int, float>> TypeChart = {

	{NORMAL,
		{std::unordered_map<unsigned int, float>	{
														{NORMAL,	1.0f},
														{FIRE,		1.0f},
														{GRASS,		1.0f},
														{WATER,		1.0f}

													}}},

	{FIRE, 
		{std::unordered_map<unsigned int, float>	{	
														{NORMAL,	1.0f},
														{FIRE,		0.5f},
														{GRASS,		2.0f},
														{WATER,		0.5f}
															
													}}},

	{WATER,
		{std::unordered_map<unsigned int, float>	{ 
														{NORMAL,	1.0f},
														{FIRE,		2.0f},
														{GRASS,		0.5f},
														{WATER,		0.5f}
															
													}}},

	{GRASS,
		{std::unordered_map<unsigned int, float>	{ 
														{NORMAL,	1.0f},
														{FIRE,		0.5f},
														{GRASS,		0.5f},
														{WATER,		2.0f}
													}}},
};