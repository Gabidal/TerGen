#include "Core.h"

// Save information of all other counters, for different ranges.
map<int, SimplexNoise*> Smart_Counter::Counters;

//this is to keep the pattern population natural in paralell with the X & Z axis
int Smart_Counter::Count(int X, int Z, int Range) {
	SimplexNoise* Counter = Counters[Range];

	if (Counter == nullptr) {
		Counters[Range] = new SimplexNoise();
		Counter = Counters[Range];
	}

	return (int)floor((Counter->noise(X, Z) + 1) * 100.0) % (Range + 1);
}