#ifndef _TILE_H_
#define _TILE_H_

enum Textures{
	VOID,
	WALL,
	PATH
};

struct Dot{
	double X;
	double Y;
	double Z;
};

class Tile{
	public:
	int Texture = VOID; //Default texture.
};

#endif