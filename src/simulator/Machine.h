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
#include "Tool.h"
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
	MachinePosition position;
	ArrayOfMachineComponent components;

	wxFileName fileName;
	wxString machineDescription;
	wxString textOut;

	Workpiece workpiece;

	Tool *tool;

	AffineTransformMatrix toolPosition;
	AffineTransformMatrix workpiecePosition;
private:
	int componentWithTool;
	int componentWithMaterial;
	AffineTransformMatrix toolPositionRelativ;
	AffineTransformMatrix workpiecePositionRelativ;

	// Methods
public:
	void Paint(void);

	void ClearComponents(void);

	bool PlaceComponent(wxString nameOfComponent,
			const AffineTransformMatrix &matrix);
	bool AddComponent(wxString nameOfComponent);
	void Assemble(void);
	void EvaluateDescription(void);
	bool ReLoadDescription(void);
	bool LoadDescription(wxFileName fileName);

};

#endif /* MACHINE_H_ */
