#include "Core.h"
#include "../Utils/Utils.h"

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

//This function will integrate different chunks together for more cohisive terrain generation
void Core::Integrate()
{
	//First cohisive terrain step is to make a gradient chunk coloring.
	//So if we have a chunk  surrounded with different chunks we want this middle chunk to have the right flowing gradient with its surrounding chunks.
	//For an example. if the top left corner chunk is a colored red chunk and the bottom right corner chunk is a colored blue chunk.
	//The middle chunks top left corner will be red and towards the center of the middle chunk will be mixed with the red and blue colors.
	//The bottom right corner of the middle chunk is blue.

	int Sub_Divider = CHUNK_SIZE / (pow(2, SUB_DIVISIONS_SIZE));

	//But how do we do this then? 
	//We will use chunk splitting. to fine control the color gradient.
	for (int Chunk_X = 0; Chunk_X < World_Size; Chunk_X++) {
		for (int Chunk_Y = 0; Chunk_Y < World_Size; Chunk_Y++) {
			TerGen_Chunk* Center_Chunk = &At(Chunk_X, Chunk_Y);
			//slice the center chunk into sub chunks
			for (int Sub_Area_X = 0; Sub_Area_X < CHUNK_SIZE * CHUNK_SIZE; Sub_Area_X += Sub_Divider) {
				for (int Sub_Area_Y = 0; Sub_Area_Y < CHUNK_SIZE * CHUNK_SIZE; Sub_Area_Y += Sub_Divider) {
					vector<pair<float, vector<Pattern*>>> Distances;

					int Absolute_X = Sub_Area_X + Chunk_X * CHUNK_SIZE;
					int Absolute_Y = Sub_Area_Y + Chunk_Y * CHUNK_SIZE;

					//Investigate the information of surrounding chunks and theyre patterns and distances
					for (int Surround_X = max(0, Chunk_X - 1); Surround_X <= min(World_Size - 1, Chunk_X + 1); Surround_X++) {
						for (int Surround_Y = max(0, Chunk_Y - 1); Surround_Y <= min(World_Size - 1, Chunk_Y + 1); Surround_Y++) {
							if (Chunk_X == Surround_X && Chunk_Y == Surround_Y)
								continue;

							int Surround_Center_X = (Surround_X * CHUNK_SIZE) + CHUNK_SIZE / 2;
							int Surround_Center_Y = (Surround_Y * CHUNK_SIZE) + CHUNK_SIZE / 2;

							Distances.push_back({
								((Absolute_X - Surround_Center_X) * (Absolute_X - Surround_Center_X)) +
								((Absolute_Y - Surround_Center_Y) * (Absolute_Y - Surround_Center_Y)),
								At(Surround_X, Surround_Y).Patterns
							});
						}
					}

					for (int i = 0; i < Distances.size(); i++) {
						Distances[i].first = 1 / Distances[i].first;
					}

					float Total_Distances = 0;

					for (auto i : Distances) {
						Total_Distances += i.first;
					}

					vector<float> Probabilities;

					for (auto i : Distances) {
						Probabilities.push_back(i.first / Total_Distances * INTENSIVITY_SCALER);
					}

					//Integrate the known knoledge to this sub divised area
					for (int Node_X = Sub_Area_X; Node_X < Sub_Area_X + Sub_Divider; Node_X++) {
						for (int Node_Y = Sub_Area_Y; Node_Y < Sub_Area_Y + Sub_Divider; Node_Y++) {
							float r = UTILS::Rand() / (float)ULONG_MAX;

							int Hit = -1;

							float Current_Sum = 0;
							for (int i = 0; i < Probabilities.size(); i++) {
								if (r < Probabilities[i] + Current_Sum && r > Current_Sum) {
									Hit = i;
								}
								Current_Sum += Probabilities[i];
							}

							if (Hit != -1 && Distances[Hit].second.size() > 0)
								Center_Chunk->At(Node_X, Node_Y).Color = Distances[Hit].second[0]->Color;
						}
					}
				}
			}
		}
	}
}