#pragma once

#define UP		1
#define DOWN	2
#define LEFT	3
#define RIGHT	4

#define MAP_UP				1
#define MAP_DOWN			2
#define MAP_LEFT			4
#define MAP_RIGHT			8
#define MAP_UP_DOWN			3
#define MAP_UP_LEFT			5
#define MAP_UP_RIGHT		9
#define MAP_DOWN_LEFT		6
#define MAP_DOWN_RIGHT		10
#define MAP_LEFT_RIGHT		12
#define MAP_UP_DOWN_LEFT	7
#define MAP_UP_DOWN_RIGHT	11
#define MAP_UP_LEFT_RIGHT	13
#define MAP_DOWN_LEFT_RIGHT	14
#define MAP_OMNI_DIRECTION	15
#define MAP_VERTICAL_HALL	16
#define MAP_HORIZONTAL_HALL	0

#define LAYER_ONE	0.0f
#define LAYER_TWO	0.1f
#define LAYER_THREE 0.2f
#define LAYER_FOUR	0.3f
#define LAYER_FIVE	0.4f
#define LAYER_SIX	0.5f
#define LAYER_SEVEN 0.6f

#define PI 3.14159265
#define MAP_SECTION_SIZE 900.0f
#define MAP_CONNECTION_MARGIN_SIZE (MAP_SECTION_SIZE * 150) / 512
#define MAP_END_MARGIN_SIZE (MAP_SECTION_SIZE * .25)
#define PLAYER_SIZE 100.0f
#define GROUNDED_ITEM_SIZE 100.0f

#define WINDOWWIDTH 1920
#define WINDOWHEIGHT 1080



#define BASIC		0
#define COMMON		1
#define RARE		2
#define LEGENDARY	3

#define SWORD		3
#define	SPEAR		2
#define THROWABLE	1
#define GUN			0

/// <summary>
/// A math square function
/// </summary>
/// <param name="value">- The value to be squared</param>
/// <returns>value squared</returns>
static double square(double value)
{
	return value * value;
}