#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <vector>
#include <string>

class Node {
public:
	float Y;
	unsigned char Color;

	Node(float y = 0, char c = 0) {
		Y = y;
		Color = c;
	}
};

//-res [how much points shall there be?]
//Note the default chunk size is 16x16
[[nodiscard]]
extern std::vector<Node*> TerGen(std::string args);

#endif