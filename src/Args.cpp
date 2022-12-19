#include "Args.h"

namespace TerGen{

    Args::Args(const char** argv, int argc)
    {
        Arguments = argv;
        Argument_Count = argc;

        Factory();
    }

    void Args::Factory()
    {
        for (int i = 1; i < Argument_Count; i++) {
            Detect_Fast_File_Output(i);
            Detect_File_Output(i);
            Detect_Resolution(i);
            Detect_World_Size(i);
        }
    }

    void Args::Detect_Fast_File_Output(int& i)
    {
        //  ./TerGen.exe [Output_File_Name].obj
        if (Argument_Count == 2) {
            Output = Arguments[i];
        }
    }

    void Args::Detect_File_Output(int& i)
    {
        //  ./TerGen.exe -out banana.obj
        if (i + 1 < Argument_Count && strcmp(Arguments[i], "-out") == 0) {
            Output = Arguments[i + 1];
            i++;
        }
    }

    void Args::Detect_Resolution(int& i)
    {
        //  ./TerGen.exe -res 1234
        if (i + 1 < Argument_Count && strcmp(Arguments[i], "-res") == 0) {
            Resolution = atoi(Arguments[i + 1]);
            i++;
        }
    }

    void Args::Detect_World_Size(int& i)
    {
        //  ./TerGen.exe -world_size 123
        if (i + 1 < Argument_Count && strcmp(Arguments[i], "-world_size") == 0) {
            World_Size = atoi(Arguments[i + 1]);
            i++;
        }
    }

}