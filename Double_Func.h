#ifndef _DOUBLE_FUNC_H_
#defien _DOUBLE_FUNC_H_

#include "Func.h"

class Double_Func :public Func{
	public:
	  Double_Func(){
	  	Type = DOUBLE;
	  }
	  vector<double> Function(vector<double>);
}

#endif