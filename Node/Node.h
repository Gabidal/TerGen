#ifndef __NODE_H__
#define __NODE_H__

class Node {
public:
	float Y;
	unsigned char Color;
	short Moisture;
	short Tempature;

	Node(float y = 0, unsigned char c = 0, short moisture = 0, short tempature = 0) {
		Y = y;
		Color = c;
		Moisture = moisture;
		Tempature = tempature;
	}
};

#endif