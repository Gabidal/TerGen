#ifndef _ARGS_H_
#define _ARGS_H_

#include <string>

namespace TerGen{

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
        void Detect_World_Size(int& i);
    public:
        std::string Output = "";
        Formats Output_Format = Formats::RAW;
        int Resolution = 1;
        int World_Size = 1;

        Args(const char** argv, int argc);
    };

}

#endif