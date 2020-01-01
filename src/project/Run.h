///////////////////////////////////////////////////////////////////////////////
// Name               : Run.h
// Purpose            : Defines a machine run.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
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

#ifndef RUN_H_
#define RUN_H_

/*!\class Run
 * \ingroup document
 * \brief Single run of a machine
 *
 * The workpiecePlacement matrix herein is for rotating the workpiece.
 *
 * The machine itself contains another matrix used for placing the
 * workpiece in the machine.
 *
 * Every operation run is centered around one Workpiece. (Please not that a
 * workpiece may exist over the course several machine Run%s.)
 *
 *
 *
 * \dot
 * digraph classes {
 *    rankdir=LR;
 *	  node [shape=record, fontname=Helvetica, fontsize=10];
 *    ini [ label="Initialisation"];
 *    tp1 [ label="Generated Toolpath"];
 *    tp2 [ label="Generated Toolpath"];
 *    cont [ label="..." shape=none];
 *
 *    ini -> tp1;
 *    tp1 -> tp2;
 *    tp2 -> cont;
 *  }
 *  \enddot
 *
 */

#include "generator/Generator.h"

#include "../3D/Geometry.h"
#include "../3D/OpenGLImage.h"
#include "../3D/AffineTransformMatrix.h"

#include <map>
#include <string>

#include "../3D/BoundingBox.h"
#include "Selection.h"

class Project;
class Run {
	friend class Project;

public:
	Run();
	virtual ~Run();

public:
	Project * parent; ///< Pointer back to the Project this Run belongs to.
	wxString name;

	Selection object;

	Selection coordX;
	Selection coordY;
	Selection coordZ;

	enum StockType {
		sObject, BoxTop, BoxCenter, BoxBottom
	} stocktype;
	size_t stockobject;
	Vector3 stocksize;
	Vector3 stockorigin;

	double slotWidth;

	std::map <size_t, Generator*> generators; ///< List of Generator%s applied to the workpiece in this run

	// Set up by Update()
	BoundingBox stock;
	AffineTransformMatrix origin; //!< Origin and coordinate-system

private:
	OpenGLImage touchpoint;

public:
	void Update(Project * project);

	void GenerateToolpaths(void);
//	bool SaveToolpaths(wxFileName fileName);

	void Paint(void) const;

	void ToStream(wxTextOutputStream & stream) const;
	bool FromStream(wxTextInputStream & stream, size_t runID,
			Project * project);

//	void ToolpathToStream(wxTextOutputStream & stream);

//	Workpiece* GetWorkpiece(void);
//	const Workpiece* GetWorkpiece(void) const;
//	ToolPath* GetFirstSelectedToolpath(void);
//	const ToolPath* GetFirstSelectedToolpath(void) const;

	friend bool operator<(const Run& a, const Run& b)
	{
		return a.name.Cmp(b.name) < 0;
	}

};

#endif /* RUN_H_ */
