#include <iostream>

using namespace std;

enum class Formats
{
	RAW,

};

class Args {
private:
	const char** Arguments;
	int Argument_Count;

	void Factory();
	void Detect_File_Output(int& i);
public:
	string Output = "";
	Formats Output_Format = Formats::RAW;

	Args(const char** argv, int argc);
};