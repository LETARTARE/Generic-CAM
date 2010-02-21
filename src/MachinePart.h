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
	AffineTransformMatrix matrix;

	// Methods
public:
	void Paint(void);

};

#endif /* MACHINEPART_H_ */
