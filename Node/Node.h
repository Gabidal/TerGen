#ifndef __NODE_H__
#define __NODE_H__

class Node {
public:
	double X;
	double Y;
	double Z;

	Node(double x, double y, double z) {
		X = x;
		Y = y;
		Z = z;
	}
};

#endif