#include "Args.h"

Args::Args(const char** argv, int argc)
{
	Arguments = argv;
	Argument_Count = argc;

	Factory();
}

void Args::Factory()
{
	for (int i = 1; i < Argument_Count; i++) {
		Detect_File_Output(i);
	}
}

void Args::Detect_File_Output(int& i)
{
	//  ./TerGen.exe [Output_File_Name].txt
	if (Argument_Count == 2) {
		Output = Arguments[i];
	}
}
