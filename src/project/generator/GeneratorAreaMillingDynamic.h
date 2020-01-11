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

/*!\class GeneratorAreaMillingDynamic
 * \ingroup Generator
 * \brief ...
 *
 * ...
 */

#include "GeneratorDexel.h"

#include "../../3D/Polygon3.h"
#include "../Tool.h"

#include "GeneratorFactory.h"

class GeneratorAreaMillingDynamic:public GeneratorDexel {
	// Constructor/ Destructor
public:
	GeneratorAreaMillingDynamic();
	virtual ~GeneratorAreaMillingDynamic();

	virtual void CopyParameterFrom(const Generator * other);
	virtual size_t GetType(void) const
			{
				return TYPE_GENERATORAREAMILLINGDYNAMIC;
			}
	virtual wxString GetTypeName(void) const;
	virtual wxSizer * AddToPanel(wxPanel * panel, CollectionUnits* settings) const;
	virtual void TransferDataToPanel(wxPanel* panel,
			CollectionUnits* settings) const;
	virtual void TransferDataFromPanel(CollectionUnits* settings);
	virtual bool operator==(const Generator &b) const;

	virtual void GenerateToolpath(const Run &run,
			const std::map <size_t, Object> &objects, const Tool &tool,
			const DexelTarget &base);

	//Member variables:
public:
	double toolDiameter;
	double freeHeightAboveMaterial;
	double maxSingleStep;
	double raiseStep;
	double dropStep;

private:

	mutable wxStaticText* m_staticText10;
	mutable wxTextCtrl* m_textCtrlMaxSingleStep;
	mutable wxStaticText* m_staticTextUnit1;
	mutable wxStaticText* m_staticText12;
	mutable wxTextCtrl* m_textCtrlRaiseStep;
	mutable wxStaticText* m_staticTextUnit2;
	mutable wxStaticText* m_staticText14;
	mutable wxTextCtrl* m_textCtrlDropStep;
	mutable wxStaticText* m_staticTextUnit3;

	//Methods:

private:
	std::vector <CNCPosition> GenerateSpiral(double x, double y, double radius);
	std::vector <CNCPosition> GenerateDrill(double x, double y, double diameter, double depth);
	bool IsDirectlyReachable(DexelTarget &target, double sx, double sy,
			double sz, double x, double y, double z);
	std::vector <CNCPosition> MoveSafely(DexelTarget &target, double sx, double sy, double sz,
			double x, double y, double z);

};

#endif /* GENERATORAREAMILLINGDYNAMIC_H_ */
