﻿

#pragma once

#include "../GPUBase.h"



class AssignOrientations :
	public GPUBase
{
public:

	/*!
	* Destructor.
	*/
	~AssignOrientations(void);

	/*!
	* Constructor, creates a program object for a context, loads the source code (.cl files) and build the program.
	*/
	AssignOrientations();

	Keys* Process(float sigma, int scale, int scale2, int* countKeys, int maxNumberKeys);

};


