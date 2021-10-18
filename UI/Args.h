#include <iostream>

using namespace std;

enum class Formats
{
	RAW,
	OBJ,
};

class Args {
private:
	const char** Arguments;
	int Argument_Count;

	void Factory();
	void Detect_Fast_File_Output(int& i);
	void Detect_File_Output(int& i);
	void Detect_Resolution(int& i);
public:
	string Output = "";
	Formats Output_Format = Formats::RAW;
	int Resolution = 0;

	Args(const char** argv, int argc);
};