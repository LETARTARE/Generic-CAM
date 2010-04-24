/*
 * MachineComponent.h
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */
#ifndef MACHINECOMPONENT_H_
#define MACHINECOMPONENT_H_
#include "../3D/AffineTransformMatrix.h"
#include "../3D/Geometry.h"

#include <wx/string.h>
#include <wx/filename.h>

class MachineComponent {
	// Constructor / Destructor
public:
	MachineComponent(wxString nameOfComponent = _T(""));
	virtual ~MachineComponent();

	// Member variables
public:

	wxString nameOfComponent;

	AffineTransformMatrix matrix;
private:
	Geometry geometry;

	// Methods
public:
	void Paint(void);
	void InsertBox(AffineTransformMatrix matrix, float x, float y, float z);
	void InsertCylinder(AffineTransformMatrix matrix, float h, float r);
	void InsertCone(AffineTransformMatrix matrix, float h, float r1, float r2);
	bool InsertSTL(AffineTransformMatrix matrix, wxFileName file);
private:
};

#endif /* MACHINECOMPONENT_H_ */
