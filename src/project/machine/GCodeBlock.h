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
 */

#include <wx/string.h>
#include <wx/dynarray.h>

class GCodeBlock {
public:

	static const size_t maxGModes = 15;
	static const size_t maxMModes = 11;

	GCodeBlock(wxString block = _T(""), double conversionFactor = 0.001);
	wxString GetCode(void) const;

	void CopySelective(const GCodeBlock &other);

	void ClearGM(void);
	void SetG(unsigned int nr, unsigned char subnr = 0);
	void SetM(unsigned int nr);

	void Rapid(void);
	void FeedSpeed(void);
	void ArcCW(void);
	void ArcCCW(void);

	int Motion(void) const;

	bool IsStateChange(void) const;
	bool IsMotion(void) const;
	bool IsLinearMotion(void) const;
	bool IsPureLinearMotion(void) const;
	bool IsCutting(void) const;

	double conversionFactor; //!< Current conversion factor (for mm: 0.001, for inch: 0.0254)

	double tStart; //!< time this block is passed to the Machine. The Machine begins moving afterwards. Calculated in Machine.
	double duration; //!< estimated duration for this block. Calculated in Machine.
	double length; //!< distance the head moves in XYZ. Calculated in Machine.

	bool block_delete; //!< Enable block delete switch for this block
	bool message; //!< is the comment a message (displayed to the user on the machine)?
	double A; //!< Rotation around X axis in rad
	bool AFlag;
	double B; //!< Rotation around Y axis in rad
	bool BFlag;
	double C; //!< Rotation around Z axis in rad
	bool CFlag;
	wxString Comment;
	int D;
	wxString error;
	double F;
	int G[maxGModes];
	int H;
	double I; //!< Center of rotation in X direction in meter
	bool IFlag;
	double J; //!< Center of rotation in Y direction in meter
	bool JFlag;
	double K; //!< Center of rotation in Z direction in meter
	bool KFlag;
	int L;
	int MCount;
	int M[maxMModes];
	int N;
	double P;
	double Q;
	double R;
	bool RFlag;
	double S; //!< Spindle speed in Hertz
	int T;
	double U; //!< Extra axis in X direction in meter
	bool UFlag;
	double V; //!< Extra axis in Y direction in meter
	bool VFlag;
	double W; //!< Extra axis in Z direction in meter
	bool WFlag;
	double X; //!< X position in meter
	bool XFlag;
	double Y; //!< Y position in meter
	bool YFlag;
	double Z; //!< Z position in meter
	bool ZFlag;

private:
	void Update(char key, bool negative, int numberI, double numberD);

};
WX_DECLARE_OBJARRAY(GCodeBlock, ArrayOfGCodeBlock);

#endif /* GCODEBLOCK_H_ */
