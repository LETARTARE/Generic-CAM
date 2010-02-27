/*
 * MachinePart.cpp
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#include "MachinePart.h"

#include <wx/glcanvas.h>

MachinePart::MachinePart()
{

}
MachinePart::MachinePart(wxString name)
{
	partname = name;
}

MachinePart::~MachinePart()
{
}

void MachinePart::InsertBox(AffineTransformMatrix matrix, float x, float y,
		float z)
{
}
void MachinePart::InsertCylinder(AffineTransformMatrix matrix, float h, float r)
{
}

void MachinePart::Paint(void)
{

}
