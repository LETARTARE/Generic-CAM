///////////////////////////////////////////////////////////////////////////////
// Name               : GCodeBlock.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.07.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef GCODEBLOCK_H_
#define GCODEBLOCK_H_

/*!\class GCodeBlock
 * \ingroup Machine
 * \brief Single G-Code block
 *
 * Contains all parameters and values in a line of G-Code. This is called a block.
 *
 * All supported G-Codes:
 *
 * 0 1 2 3 4 10 17 18 19 20 21 28 30 32 33 38.2 40 41 42 43 49 50 52 53 54 55 56 57 58 59 59.1 59.2 59.3 61 61.1 64 80 81 82 83 84 85 86 87 88 89 90 91 92 92.1 92.2 92.3 93 94 96 97 98 99
 *
 *
 * All Supported M-Codes:
 *
 * 0 1 2 3 4 5 6 7 8 9 30 48 49 60 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119
 *
 * These are valid codes for a GCodeBlock. The MachineSimulator may have problems with some of these.
 *
 * The boolean flags in the class are part of the NIST RS274NGC Interpreter. They are used to indicate if a
 * value is actually changing in one code block.
 *
 * \attention All values are stored in SI standard units. They are converted upon read-in.
 */

#include <string>

class GCodeBlock {
public:

	static const size_t maxGModes = 15;
	static const size_t maxMModes = 11;

	GCodeBlock(std::string block = "", double conversionFactor = 0.001);
	std::string GetCode(void) const;

	/*!\brief Copy only the changed values
	 *
	 * A G-Code block can have values that are marked as "not changed". These values are not copied.
	 */
	void CopySelective(const GCodeBlock &other);

	void ClearGM(void);
	void SetG(unsigned int nr, unsigned char subnr = 0);
	void SetM(unsigned int nr);

	void Rapid(void);
	void FeedSpeed(void);
	void ArcCW(void);
	void ArcCCW(void);

	int Motion(void) const;

	GCodeBlock& operator+=(const GCodeBlock& rhs);
	GCodeBlock& operator-=(const GCodeBlock& rhs);
	GCodeBlock& operator*=(const double& rhs);
	GCodeBlock& operator/=(const double& rhs);

	friend GCodeBlock operator+(GCodeBlock lhs, const GCodeBlock& rhs);
	friend GCodeBlock operator-(GCodeBlock lhs, const GCodeBlock& rhs);
	friend GCodeBlock operator*(GCodeBlock lhs, const double& rhs);
	friend GCodeBlock operator/(GCodeBlock lhs, const double& rhs);

	bool IsStateChange(void) const;
	bool IsMotion(void) const;
	bool IsLinearMotion(void) const;
	bool IsPureLinearMotion(void) const;
	bool IsCutting(void) const;

	double conversionFactor; //!< Current conversion factor (0.001 mm per m or 0.0254 inch per m)

	double t; //!< time this block is passed to the Machine. The Machine starts moving at this point. Calculated in the MachineSimulator.
	double duration; //!< estimated duration for this block. Calculated in the MachineSimulator.

	bool block_delete; //!< Enable block-delete-switch sensitivity for this block
	bool message; //!< is the comment a message (displayed to the user on the machine)?
	double A; //!< Rotation around X axis (rad)
	bool AFlag;
	double B; //!< Rotation around Y axis (rad)
	bool BFlag;
	double C; //!< Rotation around Z axis (rad)
	bool CFlag;
	std::string Comment;
	int D; //!< Tool radius compensation number
	std::string error;
	double F; //!< Feedrate (m/s)
	int G[maxGModes];
	int H; //!< Tool length offset index
	double I; //!< Center of rotation in X direction (m)
	bool IFlag;
	double J; //!< Center of rotation in Y direction (m)
	bool JFlag;
	double K; //!< Center of rotation in Z direction (m)
	bool KFlag;
	int L; //!< Number of repetitions in canned cycles
	int MCount; //!< ?
	int M[maxMModes];
	int N; //!< Line number
	double P; //!< Dwell time (s)
	double Q; //!< Feed increment in canned cycles (m)
	double R; //!< Arc radius (m)
	bool RFlag;
	double S; //!< Spindle speed (1/s)
	int T; //!< Tool selection
	double U; //!< Extra axis in X direction (m)
	bool UFlag;
	double V; //!< Extra axis in Y direction (m)
	bool VFlag;
	double W; //!< Extra axis in Z direction (m)
	bool WFlag;
	double X; //!< X position (m)
	bool XFlag;
	double Y; //!< Y position (m)
	bool YFlag;
	double Z; //!< Z position (m)
	bool ZFlag;

private:
	void Update(char key, bool negative, int numberI, double numberD);
	void UpdateFlags(const GCodeBlock& rhs);
};

GCodeBlock operator+(GCodeBlock lhs, const GCodeBlock& rhs);
GCodeBlock operator-(GCodeBlock lhs, const GCodeBlock& rhs);
GCodeBlock operator*(GCodeBlock lhs, const double& rhs);
GCodeBlock operator/(GCodeBlock lhs, const double& rhs);

#endif /* GCODEBLOCK_H_ */
