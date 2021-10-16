#include "Core.h"

Core::Core(vector<Node*> Out)
{
	Output = Out;

	Factory();
}

Core::Core(vector<Node*> Out, Node* SP, Node* EP)
{
	Output = Out;
	Start_Point = SP;
	End_Point = EP;

	Factory();
}

void Core::Factory()
{
	//Populize();
	Noise();
}

void Core::Populize()
{
	for (int X = 0; X < 100; X++) {
		for (int Y = 0; Y < 100; Y++) {
			Output.push_back(new Node(X, Y, 0));
		}
	}
}

void Core::Noise()
{
	for (int X = 0; X < 100; X++) {
		for (int Y = 0; Y < 100; Y++) {
			int Height = rand() % 10;
			for (int Z = 0; Z < Height; Z++) {
				Output.push_back(new Node(X, Y, Z));
			}
		}
	}
}
