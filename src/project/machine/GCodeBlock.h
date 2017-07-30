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
 */

#include <wx/string.h>
#include <wx/dynarray.h>

class GCodeBlock {
public:

	static const size_t maxGModes = 15;
	static const size_t maxMModes = 11;

	GCodeBlock(wxString block = _T(""), double conversionFactor = 0.001);
	wxString GetCode(void) const;

	void ClearGM(void);
	void SetG(unsigned int nr, unsigned char subnr = 0);
	void SetM(unsigned int nr);

	void Rapid(void);
	void FeedSpeed(void);
	void ArcCW(void);
	void ArcCCW(void);

	bool IsCutting(void) const;
	int Motion(void) const;

	double conversionFactor; //!< Current conversion factor (for mm: 0.001, for inch: 0.0254)

	double dt; //!< estimated duration for this block. Calculated in Machine.
	double dL; //!< distance the head moves in XYZ. Calculated in Machine.

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
