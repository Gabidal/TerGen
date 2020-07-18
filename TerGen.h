#ifndef _TERGEN_H_
#define _TERGEN_H_

#include "Chunk.h"
#include "Func.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class TerGen {
	  private:
	    //The Map Size
	    long Size = 0;
	    vector<Func*> Generator_Layers;
	    map<Dot, Chunk> Map;
    public:
      TerGen(vector<Func*> ge_la){
    	  Generator_Layers = ge_la;
      }
      
    
};

#endif