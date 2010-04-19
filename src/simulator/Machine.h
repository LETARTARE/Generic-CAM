/*
 * Machine.h
 *
 *  Created on: 21.02.2010
 *      Author: Tobias Schaefer
 */
#ifndef MACHINE_H_
#define MACHINE_H_
#include "LUACodeEvaluator.h"
#include "MachineComponent.h"
#include "MachinePosition.h"
#include "Toolbox.h"
#include "Workpiece.h"
#include <wx/string.h>
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(MachineComponent, ArrayOfMachineComponent)
;
class Machine {
	friend class LUACodeEvaluator;
	//Constructor / Destructor
public:
	Machine();
	virtual ~Machine();

	// Member variables
public:
	LUACodeEvaluator evaluator;
	wxString machineDescription;
	wxFileName programFile;
	ArrayOfMachineComponent components;
	wxString textOut;

	Toolbox toolbox;
	unsigned int activeTool;

	Workpiece workpiece;

	MachinePosition position;

	AffineTransformMatrix toolPosition;
	AffineTransformMatrix workpiecePosition;
private:
	int componentWithTool;
	int componentWithMaterial;
	AffineTransformMatrix toolPositionRelativ;
	AffineTransformMatrix workpiecePositionRelativ;

	// Methods
public:
	void SetMachineDescription(wxString text);

	void ClearComponents(void);
	bool AddComponent(wxString nameOfComponent);
	bool PlaceComponent(wxString nameOfComponent,
			const AffineTransformMatrix &matrix);

	void Assemble(void);
	void Paint(void);

};

#endif /* MACHINE_H_ */
