#pragma once

namespace nc
{
	void SeedRandom(unsigned int seed);

	float Random();
	float RandomRange(float min, float max);

	int randomInt();
	int randomInt(int max);
	int randomRangeInt(int min, int max);
}
