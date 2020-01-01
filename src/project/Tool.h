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
 *  Stuff:
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
		bool CSP; ///< Coolant supply property
		double DC; ///< Cutting diameter
		bool HAND; ///< Hand
		double LB; ///< Body length: Length of tool from tip to chuck.
		double LCF; ///< Chip flute length: Length that is cutting measured from the tip.
		size_t NOF; ///< Number of flutes
		size_t NT; ///< Tooth count
		double OAL; ///< Overall length
		double RE; ///< Corner radius
		double SFDM; ///< Shaft diameter
		double SIG; ///< Point angle
		double TA; ///< Taper angle
		double TP; ///< Thread pitch
		double shoulderlength; ///< Shoulder length: Length from tip to point, where the tool widens to the shaft diameter. Otherwise same as overall length.
		double threadprofileangle;
		double tipdiameter; ///< Tip diameter
		double tiplength; ///< Tip length
		double tipoffset; ///< Tip offset
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
		double fn; ///<
		double fz; ///< Feed per tooth [m]
		double n; ///< max. Spindle speed [1/s]
		double nramp; ///< Ramp spindle speed [1/s]
		double vc; ///< Cutting feedrate [m/s]
		double vf; ///<
		double vfleadin; ///< Lead-in feedrate [m/s]
		double vfleadout; ///< Lead-out feedrate [m/s]
		double vfplunge; ///< Plunge feedrate [m/s]
		double vframp; ///< Rampe feedrate [m/s]
		double vfretract; ///< Retraction feedrate [m/s]
	};

//	friend class DexelTarget;
//	friend class DialogToolbox;
	friend class PanelTool;
	// Constructor / Destructor
public:
	Tool();
	virtual ~Tool();

	std::string description;
	std::string guid; ///< UID to find the tool when it is copied around.
	std::string productid;
	enum ToolType {
		flat_end_mill, radius_mill, camfer_mill, bull_nose_end_mill
	} type; ///< Type of the cutting part of the tool.
	std::string vendor;
	std::string unit; ///< Unit when writing or reading from file. Internalls everything is stored as SI-base-units. Values: "millimeters", "inches"
	std::string BMC; ///< Material of tool ("carbide", "HSS")
	std::string GRADE;
	std::string productlink;

	bool hasGeometry;
	Geometry geometry;
	bool hasStartValues;
	StartValues startvalues;

	PostProcess postprocess;

	std::vector <Segment> segments;

	class ContourElement {
	public:
		ContourElement();
		void Set(float x0, float z0, float x1, float z1, bool isCutting = false,
				bool belongsToShaft = false);
		void Set(float x1, float z1, bool isCutting = false,
				bool belongsToShaft = false);
		float x0;
		float z0;
		float x1;
		float z1;
		float nx;
		float nz;
		bool isCutting;
		bool belongsToShaft;
	};
	std::vector <ContourElement> contour;

	// Methods
public:
	void Update(void);

	float GetToolLength(void) const; ///< Total length of the tool outside the chuck. (Distance between Controlled-Point and Gauge-Point).
	float GetMaxDiameter(void) const; ///< Maximum diameter of the tool.
	float GetCuttingDepth(void) const; ///< Length measured from the tip of the tool, that can cut.

//	void ToStream(wxTextOutputStream & stream);
//	bool FromStream(wxTextInputStream & stream);

	void Paint(void) const;
};

#endif /* TOOL_H_ */
