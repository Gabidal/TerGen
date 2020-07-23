#ifndef _TILE_H_
#define _TILE_H_

enum Textures {
	VOID,
	WALL,
	GRASS,
	ROCK,
	WATER,
};

class Dot {
public:
	long X;
	long Y;
	long Z;
};

class Tile : public Dot{
public:
	int Texture = VOID;
};

#endif