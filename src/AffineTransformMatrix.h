/*
 * AffineTransformMatrix.h
 *
 *  Created on: 22.07.2009
 *      Author: toby
 */

#ifndef AFFINETRANSFORMMATRIX_H_
#define AFFINETRANSFORMMATRIX_H_

#include <wx/string.h>
#include "Vector3.h"

// Form of the Matrix:

//   0   4   8  12
//   1   5   9  13
//   2   6  10  14
//   3   7  11  15

//  R11 R12 R13 Tx
//  R21 R22 R23 Ty
//  R31 R32 R33 Tz
//   0   0   0   1


class AffineTransformMatrix {


	// Constructor / Destructor
public:
	AffineTransformMatrix();
	virtual ~AffineTransformMatrix();

	// Member variables
public:
	double a[16];

	double rx,ry,rz;
	double tx,ty,tz;
	double sx,sy,sz;

	bool linkScaling;

	wxString ToString();
	void FromString(wxString string);

	// Methods
	void Identity();


	///>\brief Multiplies a given matrix in front: a=b*a
	void PreMult(double *b);

	///>\brief Multiplies a given matrix behind: a=a*b
	void PostMult(double *b);

	void RotateByMouse(int x, int y, double scale);
	void RotateByTrackball(double x, double y, double z);
	void TranslateByTrackball(double x, double y, double z);

	void RotateAroundVector(CVector3 vector, double phi);


//private:
	void TakeMatrixApart(void);
	void PutMatrixTogether(void);

};

#endif /* AFFINETRANSFORMMATRIX_H_ */
