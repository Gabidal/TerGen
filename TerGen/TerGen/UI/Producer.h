#include "../Node/Node.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Producer {
	vector<Node*> Output;


	void Factory();
	void Write_Output_As_Raw_TXT();
public:
	Producer(vector<Node*> out);
};