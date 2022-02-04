#include "Core.h"

// Save information of all other counters, for different ranges.
map<int, siv::BasicPerlinNoise<float>*> Smart_Counter::Counters;

//this is to keep the pattern population natural in paralell X & Z
int Smart_Counter::Count(int X, int Z, int Range) {
	siv::BasicPerlinNoise<float>* Counter = Counters[Range];
	if (Counter == nullptr) {
		Counters[Range] = new siv::BasicPerlinNoise<float>();
		Counter = Counters[Range];
	}

	return (int)floor(Counter->noise2D(X, Z) * 100.0) % Range + 1;
}