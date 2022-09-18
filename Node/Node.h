#ifndef __NODE_H__
#define __NODE_H__

class Node {
public:
	float Y;
	float Delta;
	unsigned char Color;
	/*short Moisture;
	short Tempature;*/

	//Node(float y = 0, unsigned char c = 0, short moisture = 0, short tempature = 0, float delta = 0) {
	//	Y = y;
	//	Color = c;
	//	Moisture = moisture;
	//	Tempature = tempature;
	//	Delta = delta;
	//}

	Node(float y = 0, unsigned char c = 0, float delta = 0) {
		Y = y;
		Color = c;
		Delta = delta;
	}
};

#endif