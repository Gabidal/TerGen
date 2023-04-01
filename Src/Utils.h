#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>


#include "Node.h"

namespace TerGen{

    std::vector<Decimal> Generate_White_Noise(int Width, int Height);

    std::vector<Decimal> Generate_Perlin_Noise(int Width, int Height);

}

#endif