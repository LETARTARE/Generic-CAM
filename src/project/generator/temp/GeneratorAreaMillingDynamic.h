///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorAreaMillingDynamic.h
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

#ifndef GENERATORAREAMILLINGDYNAMIC_H_
#define GENERATORAREAMILLINGDYNAMIC_H_

#include "GeneratorDexel.h"

#include "../../3D/Polygon3.h"
#include "../Tool.h"

/*!\class GeneratorAreaMillingDynamic
 * \ingroup Generator
 * \brief ...
 *
 * ...
 */
class GeneratorAreaMillingDynamic:public GeneratorDexel {
	// Constructor/ Destructor
public:
	GeneratorAreaMillingDynamic();
	virtual ~GeneratorAreaMillingDynamic();

	virtual void CopyParameterFrom(const Generator * other);
	virtual wxString GetName(void) const;
	virtual void AddToPanel(wxPanel * panel, CollectionUnits* settings);
	virtual void TransferDataToPanel(void) const;
	virtual void TransferDataFromPanel(void);

	virtual void GenerateToolpath(void);

	//Member variables:
public:
	double toolDiameter;
	double freeHeightAboveMaterial;
	double maxSingleStep;
	double raiseStep;
	double dropStep;

private:

	wxStaticText* m_staticText10;
	wxTextCtrl* m_textCtrlMaxSingleStep;
	wxStaticText* m_staticTextUnit1;
	wxStaticText* m_staticText12;
	wxTextCtrl* m_textCtrlRaiseStep;
	wxStaticText* m_staticTextUnit2;
	wxStaticText* m_staticText14;
	wxTextCtrl* m_textCtrlDropStep;
	wxStaticText* m_staticTextUnit3;

	//Methods:

private:
	ToolPath GenerateSpiral(double x, double y, double radius);
	ToolPath GenerateDrill(double x, double y, double diameter, double depth);
	bool IsDirectlyReachable(DexelTarget &target, double sx, double sy,
			double sz, double x, double y, double z);
	ToolPath MoveSafely(DexelTarget &target, double sx, double sy, double sz,
			double x, double y, double z);

};

#endif /* GENERATORAREAMILLINGDYNAMIC_H_ */
