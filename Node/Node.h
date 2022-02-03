#ifndef __NODE_H__
#define __NODE_H__

class Node {
public:
	float Y;
	unsigned char Color;

	Node(float y = 0, char c = 0) {
		Y = y;
		Color = c;
	}
};

#endif