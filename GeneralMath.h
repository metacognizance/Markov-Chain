#pragma once
#include <math.h>
#include <random>

namespace math{
	int random(int low, int high);

	///<summary>Get a random number between low(inclusive), and high(inclusive), but not exclude</summary>
	int random(int low, int high, int exclude);

	///<summary>Get a random number between low(inclusive), and high(inclusive), but not exclude</summary>
	int random(int low, int high, std::vector<int> exclude);

	///<summary> Converts an angle in radians to degrees </summary>
	float toDegrees(float x);

	///<summary> Converts an angle in degrees to radians</summary>
	float toRadians(float x);
}