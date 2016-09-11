///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorFast.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.08.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef GENERATORFAST_H_
#define GENERATORFAST_H_

#include "GeneratorDexel.h"

#include "../../3D/Polygon3.h"
#include "../Tool.h"

/*!\class GeneratorFast
 * \ingroup Generator
 * \brief ...
 *
 * ...
 */
class GeneratorFast:public GeneratorDexel {
	// Constructor/ Destructor
public:
	GeneratorFast();
	virtual ~GeneratorFast();

	virtual void CopyParameterFrom(const Generator * other);
	virtual wxString GetName(void) const;
	virtual void AddToPanel(wxPanel * panel, DisplaySettings* settings);
	virtual void TransferDataToPanel(void) const;
	virtual void TransferDataFromPanel(void);
	virtual wxString ToString(void) const;
	virtual void FromString(const wxString & text);

	virtual void GenerateToolpath(void);

	//Member variables:
public:

	double freeHeightAboveMaterial;
	double maxSingleStep;
	double raiseStep;

	double dropStep;

private:
	double toolDiameter;

	//Methods:

private:
	ToolPath GenerateSpiral(double x, double y, double radius);
	ToolPath GenerateDrill(double x, double y, double diameter, double depth);
	bool IsDirectlyReachable(DexelTarget &target, double sx, double sy,
			double sz, double x, double y, double z);
	ToolPath MoveSavely(DexelTarget &target, double sx, double sy, double sz,
			double x, double y, double z);

};

#endif /* GENERATORFAST_H_ */
