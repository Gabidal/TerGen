#include "Core.h"

//Use this constructor if you dont want to limit the world size.
Core::Core(vector<Node*> Out, int resolution)
{
	Output = Out;

	Resolution = resolution;

	Factory();

	Calculate_World_Size();
}

//Use this constructor to limit the size of the world
Core::Core(vector<Node*> Out, Node* SP, Node* EP, int resolution)
{
	Output = Out;
	Start_Point = SP;
	End_Point = EP;

	Resolution = resolution;

	Width = End_Point->X - Start_Point->X + 1;
	Depth = End_Point->Z - Start_Point->Z + 1;
	Height = End_Point->Y - Start_Point->Y + 1;

	Factory();
}

void Core::Factory()
{
	Populize();
	Noise();
}

void Core::Populize()
{
	Output.resize(Resolution * Resolution);
}

void Core::Noise()
{
	for (int Z = 0; Z < Resolution; Z++) {
		for (int X = 0; X < Resolution; X++) {
			Output[Index(X, Z)] = new Node(X, Z, rand() % 100);
		}
	}
}

int Core::Index(int X, int Z)
{
	return X + Z * Resolution;
}

void Core::Calculate_World_Size()
{
	double Most_Wide  = 0.0;
	double Most_Depth  = 0.0;
	double Most_Height = 0.0;

	double Least_Wide = 0.0;
	double Least_Depth = 0.0;
	double Least_Height = 0.0;

	//traverse through the list of points in space
	for (auto point : Output) {

		//Calculate the largest points in space
		//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
		if (point->X > Most_Wide)
			Most_Wide = point->X;

		if (point->Z > Most_Depth)
			Most_Depth = point->Z;

		if (point->Y > Most_Height)
			Most_Height = point->Y;

		//Calculate least points in space
		//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
		if (point->X < Least_Wide)
			Least_Wide = point->X;

		if (point->Z < Least_Depth)
			Least_Depth = point->Z;

		if (point->Y < Least_Height)
			Least_Height = point->Y;

	}

	Width = Most_Wide - Least_Wide + 1;
	Depth = Most_Depth - Least_Depth + 1;
	Height = Most_Height - Least_Height + 1;
}
