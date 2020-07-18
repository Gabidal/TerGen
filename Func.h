#ifndef _FUNC_H_
#define _FUNC_H_

enum Types{
	INT,
	DOIBLE,
	FLOAT
}

class Func{
	public:
	  Func(int type) : Type(type){}
	  //the parameter type MUST be same as the returning type!!!
	  int Return_Amount;
	  int Parameter_Amount;
	  int Type;
}

#endif