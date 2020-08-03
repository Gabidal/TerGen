#ifndef _TILE_H_
#define _TILE_H_

#include "Pool/ctpl_stl.h"

#include <vector>
#include <thread>
using namespace std;


enum type {
	_VOID,
	_GRASS,
	_STONE
};

class Point {
public:
	int Type = _VOID;
};

class Chunk {
	int Scale;
	Point* Points;
public:
	void init(int scale) {
		Scale = scale;
		Points = new Point[scale * scale * scale];
	}
	Point& operator[](int xyz) {
		return Points[xyz];
	}
	Chunk() {}
};


typedef int (*Func)(Chunk&, vector<long>);

class TerGen {
	vector<Func> Functions;
public:
	Chunk* Chunks;
	int Scale;
	int Chunk_Size;
	TerGen(int scale, int chunk_size) {
		Scale = scale;
		Chunk_Size = chunk_size;
		Chunks = new Chunk[scale * scale * scale];
		for (int i = 0; i < scale * scale * scale; i++)
			Chunks[i].init(chunk_size);
	}
	void Add_Function(Func f) {
		Functions.push_back(f);
	}
	void Apply_Functions() {
		ctpl::thread_pool pool(std::thread::hardware_concurrency() - 2);
		for (auto f : Functions) {
			for (int x = 0; x < Scale; x++)
				for (int y = 0; y < Scale; y++)
					for (int z = 0; z < Scale; z++) {
						Chunk& Current_Chunk = Chunks[x + (y * Scale) + (z * Scale * Scale)];
						pool.push([=](int id) mutable {
							for (int ix = 0; ix < Chunk_Size; ix++)
								for (int iy = 0; iy < Chunk_Size; iy++)
									for (int iz = 0; iz < Chunk_Size; iz++)
										Current_Chunk[ix + (iy * Chunk_Size) + (iz * Chunk_Size * Chunk_Size)].Type = f(Current_Chunk, { ix + x * Scale, iy + y * Scale, iz + z * Scale });
							});
					}
			while (pool.n_idle() != std::thread::hardware_concurrency() - 2) {}
		}
	}
};

#endif