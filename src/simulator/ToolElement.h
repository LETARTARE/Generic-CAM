//============================================================================
// Name        : ToolElement.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef TOOLELEMENT_H_
#define TOOLELEMENT_H_

class ToolElement {
	// Constructor / Destructor
public:
	ToolElement();
	virtual ~ToolElement();

	// Member variables
public:
	float d;
	float h;
	float r;
	unsigned char t;
	bool cutting;

	// Methods
public:

};

#endif /* TOOLELEMENT_H_ */
