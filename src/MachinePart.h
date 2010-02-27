/*
 * MachinePart.h
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#ifndef MACHINEPART_H_
#define MACHINEPART_H_

#include "AffineTransformMatrix.h"
#include <wx/string.h>

class MachinePart {
	// Constructor / Destructor
public:
	MachinePart();
	MachinePart(wxString name);

	virtual ~MachinePart();

	// Member variables
public:

	wxString partname;
private:
	AffineTransformMatrix matrix;

	// Methods
public:
	void Paint(void);
	void InsertBox(AffineTransformMatrix matrix,float x,float y,float z);
	void InsertCylinder(AffineTransformMatrix matrix,float h,float r);

};

#endif /* MACHINEPART_H_ */
