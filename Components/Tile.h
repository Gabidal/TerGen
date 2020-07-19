#ifndef _TILE_H_
#define _TILE_H_

enum Textures{
	VOID,
	WALL,
	PATH
};

class Dot{
public:
	Dot() {};
	Dot(int x, int y, int z) : X(x), Y(y), Z(z){}
	int X = 0;
	int Y = 0;
	int Z = 0;
};

class Tile : public Dot{
	public:
	int Texture = VOID; //Default texture.
};

#endif