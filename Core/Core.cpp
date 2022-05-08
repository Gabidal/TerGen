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
void TerGen_Core::Integrate()
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
			TerGen_Chunk* Center_Chunk = At(Chunk_X, Chunk_Y);

			if (Center_Chunk->Patterns.size() > 0)
				continue;

			//slice the center chunk into sub chunks
			for (int Sub_Area_X = 0; Sub_Area_X < CHUNK_SIZE * CHUNK_SIZE; Sub_Area_X += Sub_Divider) {
				for (int Sub_Area_Y = 0; Sub_Area_Y < CHUNK_SIZE * CHUNK_SIZE; Sub_Area_Y += Sub_Divider) {
					vector<pair<float, vector<Pattern*>&>> Distances;

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
								At(Surround_X, Surround_Y)->Patterns
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

							if (Hit == -1 || Distances[Hit].second.size() == 0)
								continue;

							int Closest_Pattern_Index = 0;

							for (int i = 0; i < Distances[Hit].second.size(); i++) {
								if (abs(Distances[Hit].second[i]->Weight - r) < abs(Distances[Hit].second[Closest_Pattern_Index]->Weight - r)) {
									Closest_Pattern_Index = i;
								}
							}

							Node tmp;

							Pattern pattern = *Distances[Hit].second[Closest_Pattern_Index];
							pattern.X = Node_X;
							pattern.Z = Node_Y;
							pattern.Nodes = &tmp;

							Node* Target = Center_Chunk->At(Node_X, Node_Y);

							unsigned Color = pattern.Function(&pattern, Target);

							Target->Color = Color;

						}
					}
				}
			}
		}
	}
}

//void TerGen_Core::River() {
//	
//	// We can use the warp noise to single out too low height areas.
//	//This is because warp noise generates some river like patterns.
//
//	UTILS::For_All_Nodes([](Node* node, int x, int z, int Chunk_X, int Chunk_Z) {
//		float Real_X = x + Chunk_X * CHUNK_SIZE;
//		float Real_Y = z + Chunk_Z * CHUNK_SIZE;
//		
//		float Noise = UTILS::Warp_noise({ Real_X, Real_Y });
//
//		if (Noise < 0.05) {
//			node->Y = 0;
//		}
//	});
//
//}

//void TerGen_Core::River() {
//	vector<pair<TerGen_Chunk*, TerGen_Chunk_Coordinates>> Most_Moist_Chunks;
//	vector<pair<TerGen_Chunk*, TerGen_Chunk_Coordinates>> Least_Moist_Chunks;
//
//	short Min_Moisture = SHRT_MAX;
//	short Max_Moisture = 0;
//
//	int Average_Moisture = 0;
//
//	float Realtive_Scale_Towards_Frequenzy = min(2 / Frequenzy, (float)10);
//	float River_Width_Radius = max(Realtive_Scale_Towards_Frequenzy, (float)2);
//	float Intensity = 0.05 / Amplitude;
//
//	vector<Node*> Liquid_Buffer;
//
//	Liquid_Buffer.resize(World_Size * World_Size * CHUNK_SIZE * CHUNK_SIZE);
//
//	UTILS::For_All_Nodes([&Liquid_Buffer](Node* node, int x, int y, int Chunk_X, int Chunk_Y) {
//		Liquid_Buffer[Chunk_X + Chunk_Y] = node;
//		});
//
//	//draw A points to most moist chunks,  and B points into least moist chunks.
//
//	//Calculate the most extreme points
//	for (auto i : Chunks) {
//		if (i->Max_Moisture > Max_Moisture)
//			Max_Moisture = i->Max_Moisture;
//
//		if (i->Max_Moisture < Min_Moisture)
//			Min_Moisture = i->Max_Moisture;
//
//		Average_Moisture += i->Max_Moisture;
//	}
//
//	Average_Moisture /= Chunks.size();
//	Average_Moisture = (Frequenzy * (float)Average_Moisture) * Amplitude * 10;
//
//	//sort the chunks that are close enough to the extreme points.
//	for (int x = 0; x < World_Size; x++) {
//		for (int z = 0; z < World_Size; z++) {
//			TerGen_Chunk* chunk = At(x, z);
//
//			if (abs(chunk->Max_Moisture - Max_Moisture) <= Average_Moisture)
//				Most_Moist_Chunks.push_back({ chunk, {x, z} });
//			else if (abs(chunk->Max_Moisture - Min_Moisture) <= Average_Moisture)
//				Least_Moist_Chunks.push_back({ chunk, {x, z} });
//		}
//	}
//
//	vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Paths;
//
//	//combine every single Most_Moist_Chunks with all the Least_Moist_Chunks.
//	for (auto Most : Most_Moist_Chunks) {
//
//		vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Tmp_Paths;
//
//		TerGen_Node_Coordinates A = At(Most.second.X, Most.second.Z)->Highest_Point.second;
//		A.X += CHUNK_SIZE * Most.second.X;
//		A.Z += CHUNK_SIZE * Most.second.Z;
//
//		for (auto Least : Least_Moist_Chunks) {
//
//			TerGen_Node_Coordinates B = At(Least.second.X, Least.second.Z)->Highest_Point.second;
//			B.X += CHUNK_SIZE * Least.second.X;
//			B.Z += CHUNK_SIZE * Least.second.Z;
//
//			UTILS::Append(Tmp_Paths, UTILS::Path_Find(Liquid_Buffer, A, B, 0, World_Size * CHUNK_SIZE));
//		}
//
//		UTILS::Append(Paths, Tmp_Paths);
//
//	}
//
//	//We can image the center being always at the center [0, 0]
//	float Most_Distant_Point_From_Center = sqrt(pow(0 - River_Width_Radius, (float)2) + pow(0 - River_Width_Radius, (float)2));
//
//	for (auto& p : Paths) {
//
//		for (auto n : UTILS::Get_Surrounding_Coordinates({ p.first.X, p.first.Z }, River_Width_Radius, { 0, World_Size * CHUNK_SIZE - 1 })) {
//			TerGen_Chunk* chunk = At({ n.X, n.Z });
//			Node* node = chunk->At(n.X, n.Z);
//
//			//measure the effect
//			float Distance_From_Center = sqrt(pow(p.first.X - n.X, 2) + pow(p.first.Z - n.Z, 2));
//
//			float Modifier = pow(Distance_From_Center / Most_Distant_Point_From_Center, Intensity);
//
//			/*if (Modifier == 0) {
//				continue;
//			}*/
//
//			node->Y *= Modifier;
//		}
//
//		//Get_Surrounding_Coordinates doesnt ofcourse give us the middle node, thus we need to do it here
//		/*TerGen_Chunk* chunk = At({ p.first.X, p.first.Z });
//		Node* node = chunk->At(p.first.X, p.first.Z);
//
//		node->Y *= pow(0.1, Intensity);*/
//	}
//}

