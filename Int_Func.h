#ifndef _INT_FUNC_H_
#defien _INT_FUNC_H_

#include "Func.h"

class Int_Func :public Func{
	public:
	  Int_Func(){
	  	Type = INT;
	  }
	  vector<int> Function(vector<int>);
}

#endif