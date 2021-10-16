#include "Producer.h"
#include "Args.h"

extern Args* CMD;

Producer::Producer(vector<Node*> out)
{
	Output = out;

	Factory();
}

void Producer::Factory()
{
	Write_Output_As_Raw_TXT();
}

void Producer::Write_Output_As_Raw_TXT()
{
	if (CMD->Output_Format != Formats::RAW)
		return;

	ofstream file(CMD->Output.c_str());

	string Result = "";

	for (auto i : Output) {
		Result += to_string(i->X) + ", " + to_string(i->Y) + ", " + to_string(i->Z) + "\n";
	}

	file << Result;
	file.close();
}
