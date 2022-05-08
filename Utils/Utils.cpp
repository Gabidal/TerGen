#include "Utils.h"

#include "../Core/Core.h"
#include "../Node/Node.h"
#include "../Node/Chunk.h"
#include "../Node/Simplex.h"

extern TerGen_Core* core;

unsigned char UTILS::Get_Free_Color(){
    return core->Allocate_Color();
}

//NOTE: The given chunk will be destroyed after the TerGen core is shutdown.
TerGen_Chunk* UTILS::Get_Chunk(TerGen_Chunk_Coordinates coordinates){
    return core->At(coordinates.X, coordinates.Z);
}

//NOTE: The given chunk will be destroyed after the TerGen core is shutdown.
TerGen_Chunk* UTILS::Get_Chunk(TerGen_Node_Coordinates coordinates){
    return core->At(coordinates.X / CHUNK_SIZE, coordinates.Z / CHUNK_SIZE);
}

Node* UTILS::Get_Node(int x, int z) {
    //First we need to normalize the x and y to get the chunk.
    int Chunk_X = x / CHUNK_SIZE;
    int Chunk_Z = z / CHUNK_SIZE;

    //Then we get the chunk.
    TerGen_Chunk* chunk = core->At(Chunk_X, Chunk_Z);

    //Then we get the node.
    return chunk->At(x % CHUNK_SIZE, z % CHUNK_SIZE);
}

//This function goes through all the nodes in the world and starts the given lambda function.
void UTILS::For_All_Nodes(std::vector<Node*> nodes, std::function<void(Node*, double, double, double, double)> lambda) {
    //Now that we have the list of nodes we want to convert them to chunks
	for (int c_x = 0; c_x < core->World_Size; c_x++) {
		for (int c_y = 0; c_y < core->World_Size; c_y++) {

			int Chunk_X = c_x * CHUNK_SIZE;

			int Chunk_Y = c_y * CHUNK_SIZE;

			int Chunk_Index = (core->World_Size * c_x + c_y) * CHUNK_SIZE * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					int Node_index = CHUNK_SIZE * x + y;

					lambda(nodes[Chunk_Index + Node_index], x, y, Chunk_X, Chunk_Y);
				}
			}
		}
	}
}

//This function goes through all the nodes in the world and starts the given lambda function.
void UTILS::For_All_Nodes(std::function<void(Node*, double, double, double, double)> lambda) {
	//Now that we have the list of nodes we want to convert them to chunks

	for (int c_x = 0; c_x < core->World_Size; c_x++) {
		for (int c_y = 0; c_y < core->World_Size; c_y++) {
			TerGen_Chunk* chunk = core->At(c_x, c_y);

			//int Chunk_Index = (core->World_Size * c_x + c_y) * CHUNK_SIZE * CHUNK_SIZE;

			int Chunk_X = core->World_Size * c_x * CHUNK_SIZE * CHUNK_SIZE;

			int Chunk_Y = c_y * CHUNK_SIZE * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					//int Node_index = CHUNK_SIZE * x + y;

					int X = x * CHUNK_SIZE + Chunk_X;

					int Y = y + Chunk_Y;

					lambda(chunk->At(x, y), x, y, X, Y);
				}
			}
		}
	}
}

static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long UTILS::Rand() {          //period 2^96-1
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}

unsigned char UTILS::Get_Color(FUNCTION func)
{
	for (auto i : core->Patterns) {
		if (i.Function == func)
			return i.Color;
	}

	return -1;
}

FUNCTION UTILS::Get_Function(unsigned char color) {
	for (auto i : core->Patterns) {
		if (i.Color == color)
			return i.Function;
	}

	return nullptr;
}

//NOTE!: this Path_Find algorithm is only made for non decimal A & B coordinates.
//for docimal coorniate path finding, try Chaos::Path_Find(A, B);
vector<pair<TerGen_Node_Coordinates, pair<float, float>>> UTILS::Path_Find(std::vector<Node>& nodes, TerGen_Node_Coordinates A, TerGen_Node_Coordinates B, float budget, int Width) {
	//The way that we make this path finding algorithm is by calculating
	//each tile next to the current tile and calculate their relative distance between the A and B.
	vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Result;

	TerGen_Node_Coordinates Previus = A;

	float Default_Distance = sqrt(pow(1 - 0, 2) + pow(1 - 0, 2));
	float New_Distance = sqrt(pow(1 - 1, 2) + pow(1 - 0, 2));

	float Allowed_Error = abs(New_Distance - Default_Distance);

	float Distance = sqrt(pow(B.X - A.X, 2) + pow(B.Z - A.Z, 2));

	while (Distance > 1) {

		pair<TerGen_Node_Coordinates, pair<float, float>> Best_Candidate = { {0, 0}, {0, 0} };

		int Closest_X = Clamp(Previus.X + Sign(B.X - Previus.X), { 0, Width -1 });
		int Closest_Z = Clamp(Previus.Z + Sign(B.Z - Previus.Z), { 0, Width -1 });

		float Closest_Cost = nodes[Width * Previus.X + Previus.Z].Y - nodes[Width * Closest_X, Closest_Z].Y;

		Distance = sqrt(pow(B.X - Closest_X, 2) + pow(B.Z - Closest_Z, 2));

		Best_Candidate = { {Closest_X, Closest_Z},{Distance, Closest_Cost} };

		for (auto n : Get_Surrounding_Coordinates(Previus, 1, { 0, Width })) {

			if (n.X == Closest_X && n.Z == Closest_Z)
				continue;

			float Cost = nodes[Width * Previus.X + Previus.Z].Y - nodes[Width * n.X, n.Z].Y;

			if (Cost <= budget && Cost < Closest_Cost) {

				float New_Distance = sqrt(pow(B.X - n.X, 2) + pow(B.Z - n.Z, 2));

				if (abs(New_Distance - Distance) <= Allowed_Error) {
					Best_Candidate = { {n.X, n.Z}, {New_Distance, Cost} };
				}
			}
		}

		Result.push_back(Best_Candidate);
		Previus = Best_Candidate.first;
	}

	return Result;
}

vector<pair<TerGen_Node_Coordinates, pair<float, float>>> UTILS::Path_Find(std::vector<Node*>& nodes, TerGen_Node_Coordinates A, TerGen_Node_Coordinates B, float budget, int Width) {
	//The way that we make this path finding algorithm is by calculating
	//each tile next to the current tile and calculate their relative distance between the A and B.
	vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Result;

	TerGen_Node_Coordinates Previus = A;

	float Default_Distance = sqrt(pow(1 - 0, 2) + pow(1 - 0, 2));
	float New_Distance = sqrt(pow(1 - 1, 2) + pow(1 - 0, 2));

	float Allowed_Error = abs(New_Distance - Default_Distance);

	float Distance = sqrt(pow(B.X - A.X, 2) + pow(B.Z - A.Z, 2));

	while (Distance > 1) {

		pair<TerGen_Node_Coordinates, pair<float, float>> Best_Candidate = {{0, 0}, {0, 0}};

		int Closest_X = Clamp(Previus.X + Sign(B.X - Previus.X), { 0, Width - 1 });
		int Closest_Z = Clamp(Previus.Z + Sign(B.Z - Previus.Z), { 0, Width - 1 });

		float Closest_Cost = nodes[Width * Previus.X + Previus.Z]->Y - nodes[Width * Closest_X, Closest_Z]->Y;

		Distance = sqrt(pow(B.X - Closest_X, 2) + pow(B.Z - Closest_Z, 2));

		Best_Candidate = { {Closest_X, Closest_Z},{Distance, Closest_Cost} };
			
		for (auto n : Get_Surrounding_Coordinates(Previus, 1, { 0, Width })) {

			if (n.X == Closest_X && n.Z == Closest_Z)
				continue;

			float Cost = nodes[Width * Previus.X + Previus.Z]->Y - nodes[Width * n.X, n.Z]->Y;

			if (Cost <= budget && Cost < Closest_Cost) {

				float New_Distance = sqrt(pow(B.X - n.X, 2) + pow(B.Z - n.Z, 2));

				if (abs(New_Distance - Distance) <= Allowed_Error) {
					Best_Candidate = {{n.X, n.Z}, {New_Distance, Cost}};
				}
			}
		}

		Result.push_back(Best_Candidate);
		Previus = Best_Candidate.first;
	}

	return Result;
}

vector<TerGen_Node_Coordinates> UTILS::Get_Surrounding_Coordinates(TerGen_Node_Coordinates coordinates, int radius, pair<int, int> MinMax) {
	int Max_X = min(coordinates.X + radius + 1, MinMax.second);
	int Max_Z = min(coordinates.Z + radius + 1, MinMax.second);

	int Min_X = max(coordinates.X - radius, MinMax.first);
	int Min_Z = max(coordinates.Z - radius, MinMax.first);

	vector<TerGen_Node_Coordinates> Result;

	for (int x = Min_X; x < Max_X; x++) {
		for (int z = Min_Z; z < Max_Z; z++) {
			if (x == coordinates.X && z == coordinates.Z)
				continue;

			Result.push_back({ x, z });

		}
	}

	return Result;
}

int UTILS::Sign(float x)
{
	if (x >= 0)
		return 1;
	else
		return -1;
}

int UTILS::Clamp(int x, pair<int, int> MinMax) {
	return min(max(x, MinMax.first), MinMax.second);
}

float UTILS::Warp_Noise(Vector2 Position) {
	float Result = 0;

	SimplexNoise fbm = *core->Ground_Noise_Generator;//SimplexNoise(core->Frequenzy, core->Amplitude, core->Lacuranity, core->Persistance, core->Seed);
	const int Resolution = core->Warp_Octaves;
	const float Final_Offset = 4;

	//For every loop we make a new p + fbm(p) to the current value.
	Vector2 Current(0, 0);
	for (int i = 0; i < Resolution; i++) {
		float R1 = core->Offsetters[i][0];
		float R2 = core->Offsetters[i][1];


		Vector2 Offsetter1(Position + Vector2{R1, R2} + Current * Final_Offset);

		R1 = core->Offsetters[i][2];
		R2 = core->Offsetters[i][3];

		Vector2 Offsetter2(Position + Vector2{ R1, R2 } + Current * Final_Offset);

		Current = Vector2(
			fbm.fractal(core->FBM_Octaves, Offsetter1.X, Offsetter1.Z),
			fbm.fractal(core->FBM_Octaves, Offsetter2.X, Offsetter2.Z)
		);

	}

	Vector2 tmp = Position + Current * Final_Offset;

	Result = fbm.fractal(core->FBM_Octaves, tmp.X, tmp.Z);

	return Result;
}