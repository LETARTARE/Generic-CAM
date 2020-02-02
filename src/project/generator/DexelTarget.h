///////////////////////////////////////////////////////////////////////////////
// Name               : DexelTarget.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.07.2011
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

#ifndef DEXELTARGET_H_
#define DEXELTARGET_H_

/*!\class DexelTarget
 * \ingroup GeneratorBasic
 *
 * \brief Simplified representation of 3D data using a depth-pixel approach
 *
 * Collection of function to generate ToolPath%s from dexel data.
 */

#include "Imprinter.h"

#include "../Tool.h"
#include "../Object.h"
#include "../../3D/Polygon25.h"

#include <wx/xml/xml.h>
#include <vector>

#include "CNCPosition.h"
//#include <cstddef>

class DexelTarget:public Imprinter {
	// Constructor/ Destructor
public:
	DexelTarget();
	virtual ~DexelTarget();

//Methods:
public:
//	void ToXml(wxXmlNode* parentNode);
//	bool FromXml(wxXmlNode* node);

// ***** Construction / Debugging *****

	void InsertObject(const Object &object, const AffineTransformMatrix &shift);
	void SetupTool(const Tool &tool, const double resolutionX,
			const double resolutionY);
	void MarkOutline(void);

	void DocumentField(int x, int y, double height);
	void DocumentField(int x, int y);
	void Paint(void) const;
	void Simulate(const std::vector<CNCPosition> &toolpath, const Tool &tool);

// ***** Traversing data *****

	double GetMinLevelD(void);
	double GetMaxLevelAD(int &x, int &y);
	bool IsInsideWorkingAreaAU(int x, int y);
	bool HasToBeCutBDAU(int x, int y);
	bool HadBeenCutBDAU(int x, int y);
	int NextDir(int sx, int sy, double height, int olddir);
	int NextDir(int sx, int sy, int olddir);
	int NextDirReverseDistance(int sx, int sy, int olddir);
	int NextDirForwardDistance(int sx, int sy, int olddir);
	void MoveInDir(int &x, int &y, int dir);

	// ***** Operations on data *****

	const Polygon25 GeneratePolygon(int sx, int sy, double height);
	const Polygon25 GeneratePolygon(int sx, int sy);
	const Polygon25 GenerateConvexOutline(void);

	void GenerateDistanceMap(double height, bool invert = false);

	void RaiseDistanceMap(double height, bool invert);
	void FoldLowerDistance(int x, int y, const DexelTarget &b);
	bool FindNextDistanceBDAU(int &x, int&y);

	bool FindStartCutting(int &x, int &y);
	Polygon25 FindCut(int &x, int &y);

	void FillBlock(double maxLevel, double minLevel = 0.0);

	double FindLevelAbove(double startLevel, double normalDeviation);
	void GenerateDistanceMap(double minLevel, double maxLevel);
	double FindPeak(int &x, int &y);
	double FindCircle(double x, double y, double radius);
	std::vector<Vector3> GeneratePolygonAtDistance(double level);

	// Polygon3 Methods
	void PolygonCutInTarget(Polygon3 &polygon, DexelTarget &tool);
	void PolygonPunchThroughTarget(Polygon3 &polygon, double level,
			DexelTarget &tool);

	/**\brief Drop a polygon down onto the target or onto the level.
	 *
	 * Moves every vertex of a polygon until it touches the target or
	 * the level given whichever is higher. Movement in only in the Z
	 * direction.
	 *
	 * @param polygon Polygon3 to manipulate
	 * @param level Lowest level to move to
	 */
	void PolygonDropOntoTarget(Polygon3 &polygon, double level);
	void VectorDropOntoTarget(double &x, double &y, double &z, double level);
	void FillOutsidePolygon(Polygon3 &polygon);

	void AddSupport(Polygon3 &polygon, double distance, double height,
			double width, double slotWidth);

	void FilterAD(void);

	void CopyNormal(const DexelTarget& other);
	void CopyToUp(int f, double factor = 1.0);

	//Member variables:
public:
	Polygon25 outLine;
	Polygon25 supportLine;
};

#endif /* DEXELTARGET_H_ */
