#ifndef _NODE_H_
#define _NODE_H_

namespace TerGen{
    // Guide on using HIGH_PRECISION flag when compiling: gcc TerGen.cpp -o TerGen -D HIGH_PRECISION
    #if HIGH_PRECISION
        using Decimal = double;
    #else
        using Decimal = float;
    #endif
}

#endif