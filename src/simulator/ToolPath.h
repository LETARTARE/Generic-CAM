//============================================================================
// Name        : ToolPath.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 30.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef TOOLPATH_H_
#define TOOLPATH_H_
#include <gts.h>
#include "Tool.h"

class ToolPath {
	// Constructor / Destructor

public:
	ToolPath();
	virtual ~ToolPath();

	// Member variables
public:
	GtsSurface * linkedWorkpiece;

	// Methods
public:

};

#endif /* TOOLPATH_H_ */
