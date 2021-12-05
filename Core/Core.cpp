#include "Core.h"

Core::Core(int Chunk_Count, int resolution)
{
	Resolution = resolution;

	this->Chunk_Count = Chunk_Count;
}

void Core::Factory()
{
	Populize();

	for (auto* Chunk : Chunks) {
		for (auto F : Pattern_Functions) {
			//F.first 0(0%) - 255(100%)
			int Rand_Value = rand() % 255;
			if (Rand_Value <= F.first) {
				Patterns.push_back(F.second(Chunk));
			}
		}
	}

	Integrate();

	Calculate_All_Chunk_Height();
}

void Core::Integrate() {
	for (int X = 0; X < Chunk_Count; X++) {
		for (int Z = 0; Z < Chunk_Count; Z++)
			for (int Y = 0; Y < Chunk_Count; Y++) {
				for (auto F : Behaviour_Functions) {
					F(Chunks, X, Y, Z);
				}
			}
	}
}

void Core::Populize()
{
	for (int i = 0; i < Chunk_Count * Chunk_Count * Chunk_Count; i++) {
		Chunks.push_back(new Chunk());
	}
}

void Core::Calculate_All_Chunk_Height()
{
	for (auto* C : Chunks) {
		unsigned int Max_Height = 0;
		for (int N_X = 0; N_X < Resolution; N_X++)
			for (int N_Z = 0; N_Z < Resolution; N_Z++)
				for (int N_Y = 0; N_Y < Resolution; N_Y++) {
					long Index = (N_Y * Resolution * Resolution) + (N_Z * Resolution) + N_X;
					
					if (C->Nodes[Index] > 0 && N_Y > Max_Height) {
						Max_Height = N_Y;
					}
				}
		C->Max_Height = Max_Height;
	}
}

int Core::Allocate_Color(Pattern* pattern)
{
	//the idea here is to increment the results R.G.B values
	//to represent the largest  values of the all

	int Result = 0;

	//if there is no previus color set use 0.
	if (Colors.size() > 0)
		Result = Colors.back().first;

	Result++;

	Colors.push_back({ Result, pattern });

	return Result;
}

