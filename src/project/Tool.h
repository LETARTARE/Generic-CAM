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

class Tool {
public:
	enum UnitType {
		unit_none, unit_SI, unit_inch, unit_millimeter
	};
	enum ToolType {
		no_type,
		flat_end_mill,
		radius_mill,
		camfer_mill,
		bull_nose_end_mill,
		ball_end_mill,
		tool_holder,
		tool_shaft,
		probe
	}; ///< Basic tool shape

	class Segment {
	public:
		Segment();
		double height;
		double lowerdiameter;
		double upperdiameter;

	public:
		float Update(float z);
		float x0;
		float z0;
		float x1;
		float z1;
		float nx;
		float nz;
		bool isCutting;
	};
	class Contour {
	public:
		Contour();
		std::string description;
		std::string guid;
		std::string vendor;
		std::string productid;
		std::string productlink;
		bool hasSegments; ///< Indicates, wheather the tool itself has segments. If not, the segments are generated from the geometry section.
		std::vector <Segment> segments;
		ToolType type;
		UnitType unit; ///< Unit of values in segments

		void ConvertToSI(UnitType baseunit);
		float Update(float z);
		void Paint(void) const;
	};
	class Geometry {
	public:
		Geometry();
		double DC; ///< Cutting diameter
		double LCF; ///< Chip flute length: Length that is cutting measured from the tip.
		double LB; ///< Body length: Length of tool from tip to chuck.
		double OAL; ///< Overall length
		size_t NOF; ///< Number of flutes
		size_t NT; ///< Tooth count
		double RE; ///< Corner radius
		double SIG; ///< Point angle
		double TA; ///< Taper angle
		double TP; ///< Thread pitch
		bool CSP; ///< Coolant supply property
		bool HAND; ///< Hand
		double SFDM; ///< Shaft diameter
		double shoulderlength; ///< Shoulder length: Length from tip to point, where the tool widens to the shaft diameter. Otherwise same as overall length.
		double tipdiameter; ///< Tip diameter
		double tiplength; ///< Tip length
		double tipoffset; ///< Tip offset
		double threadprofileangle;
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
		int number;
		std::string toolcoolant;
		size_t turret;
	};
	class StartValues {
	public:
		StartValues();
		std::string name;
		std::string guid;
		std::string description;
		std::string toolcoolant;
		double fn; ///< Feed per revolution [m]
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

	std::string GRADE;
	std::string BMC; ///< Material of tool ("carbide", "HSS")

	Contour base;

	bool hasShaft;
	Contour shaft;
	bool hasHolder;
	Contour holder;

	bool hasGeometry;
	Geometry geometry;
	bool hasStartValues;
	StartValues startvalues;
	bool hasPostProcess;
	PostProcess postprocess;

	double lastmodified;
	bool addtonewprojects;
private:
	UnitType unitinfile;
	float fullsize;
	// Methods
public:
	bool operator==(const std::string &guid) const;
	std::string GetGUID() const;
	void ConvertToSI(void);

	void Update(void);
	float GetFullLength(void) const; ///< Length used for offset from tooltip to collar of holder
	float GetToolLength(void) const; ///< Total length of the tool outside the chuck. (Distance between Controlled-Point and Gauge-Point).
	float GetMaxDiameter(void) const; ///< Maximum diameter of the tool.
	float GetCuttingDepth(void) const; ///< Length measured from the tip of the tool, that can cut.

//	void ToStream(wxTextOutputStream & stream);
//	bool FromStream(wxTextInputStream & stream);

	void Paint(bool showHolder = true, bool showShaft = true, bool showTool =
			true) const;
};

#endif /* TOOL_H_ */
