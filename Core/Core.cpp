#include "Core.h"

//Use this constructor if you dont want to limit the world size.
Core::Core(int resolution, vector<Generator> functions)
{
	Resolution = resolution;

	Functions = functions;

	Factory();

	Calculate_World_Size();
}

//Use this constructor to limit the size of the world
Core::Core(Node* SP, Node* EP, int resolution, vector<Generator> functions)
{
	Start_Point = SP;
	End_Point = EP;

	Resolution = resolution;

	Functions = functions;

	Width = End_Point->X - Start_Point->X + 1;
	Depth = End_Point->Z - Start_Point->Z + 1;
	Height = End_Point->Y - Start_Point->Y + 1;

	Factory();
}

void Core::Factory()
{
	Populize();

	for (auto f : Functions) {
		f(Master, Cluster);
	}
}

void Core::Populize()
{
	Master.resize(Resolution * Resolution);
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
	for (auto point : Master) {

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

int Core::Allocate_Color(Generator Func)
{
	//the idea here is to increment the results R.G.B values
	//to represent the largest  values of the all

	int Result = 0;

	Result = Colors.back().first;

	Result++;

	Colors.push_back({ Result, Func });

	return Result;
}

