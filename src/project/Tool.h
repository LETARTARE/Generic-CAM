///////////////////////////////////////////////////////////////////////////////
// Name               : Tool.h
// Purpose            : A tool for the machine
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef TOOL_H_
#define TOOL_H_

/*!\class Tool
 * \brief Definition of a tool
 *
 *
 *  Various Stuff:
 *
 *	SFM = Surface Feet per Minute = edge speed of the tool
 *	450 - 650 for HSS cutters
 *
 *
 *
 */

#include <stddef.h>
#include <string>
#include <vector>

#include "../3D/Vector3.h"

class Tool {
public:
	class Segment {
	public:
		Segment();
		double height;
		double lowerdiameter;
		double upperdiameter;
	};
	class Geometry {
	public:
		Geometry();
		bool CSP;
		double DC;
		bool HAND;
		double LB;
		double LCF;
		size_t NOF;
		double NT; //?
		double OAL;
		double RE;
		double SFDM;
		double SIG;
		double TA;
		double TP;
		double shoulderlength;
		double threadprofileangle;
		double tipdiameter;
		double tiplength;
		double tipoffset;
	};
	class PostProcess {
	public:
		PostProcess();
		bool breakcontrol;
		std::string comment;
		size_t diameteroffset;
		size_t lengthoffset;
		bool live;
		bool manualtoolchange;
		size_t number;
		std::string toolcoolant;
		size_t turret;
	};
	class StartValues {
	public:
		StartValues();
		double fn;
		double fz;
		double n;
		double nramp;
		double vc;
		double vf;
		double vfleadin;
		double vfleadout;
		double vfplunge;
		double vframp;
		double vfretract;
	};

//	friend class DexelTarget;
//	friend class DialogToolbox;
	friend class PanelTool;
	// Constructor / Destructor
public:
	Tool();
	virtual ~Tool();

	std::string description;
	std::string guid;
	std::string productid;
	std::string type;
	std::string vendor;
	std::string unit;
	std::string BMC;
	std::string GRADE;
	std::string productlink;

	bool hasGeometry;
	Geometry geometry;
	bool hasPostProcess;
	PostProcess postprocess;
	bool hasStartValues;
	StartValues startvalues;

	std::vector <Segment> segments;

private:

	class ContourElement {
	public:
		ContourElement(bool cutting = false, bool partOfShaft = false);
		Vector3 p1;
		Vector3 p2;
		Vector3 n1;
		Vector3 n2;
		bool isCutting;
		bool belongsToShaft;
	};
	std::vector <ContourElement> contour;

	// Methods
public:
	void Clear(void);

	float GetToolLength(void) const; ///< Total length of the tool outside the chuck. (Distance between Controlled-Point and Gauge-Point).
	float GetNegativeLength(void) const; ///< Length of the part, that disappears in the chuck.
	float GetMaxDiameter(void) const; ///< Maximum diameter of the tool.
	float GetCuttingDepth(void) const; ///< Length measured from the tip of the tool, that can cut.

	void GenerateContour(void);

//	void ToStream(wxTextOutputStream & stream);
//	bool FromStream(wxTextInputStream & stream);

	void Paint(void) const;
};

#endif /* TOOL_H_ */
