//============================================================================
// Name        : ToolElement.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "ToolElement.h"

ToolElement::ToolElement()
{
	d = h = 1.0;
	r = 0.0;
	cutting = false;
	t = 0;
}

ToolElement::~ToolElement()
{
}
