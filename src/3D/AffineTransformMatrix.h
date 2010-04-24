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

// http://www.parashift.com/c++-faq-lite/operator-overloading.html

// Form of the Matrix:

//   0   4   8  12
//   1   5   9  13
//   2   6  10  14
//   3   7  11  15

//  R11 R12 R13 Tx
//  R21 R22 R23 Ty
//  R31 R32 R33 Tz
//   0   0   0   1

// Right handed coordinate system:
// X to the right of the screen
// Y to the top of the screen
// Z towards the viewer

class AffineTransformMatrix {


	// Constructor / Destructor
public:
	AffineTransformMatrix();
	virtual ~AffineTransformMatrix();

	// Member variables
public:
	double a[16];

	double rx, ry, rz;
	double tx, ty, tz;
	double sx, sy, sz;

	bool linkScaling;

	// Methods
	//AffineTransformMatrix& operator=(const AffineTransformMatrix& b);
	AffineTransformMatrix operator*(const AffineTransformMatrix& b) const;
	AffineTransformMatrix operator/(const AffineTransformMatrix& b) const;

	void Set(const AffineTransformMatrix &matrix);
	void SetIdentity();

	//>\brief Multiplies a given matrix in front: a=b*a
	//void PreMult(const double *b);
	//>\brief Multiplies a given matrix behind: a=a*b
	//void PostMult(const double *b);

	AffineTransformMatrix Inverse() const;

	static AffineTransformMatrix Identity();
	static AffineTransformMatrix RotateAroundVector(Vector3 vector, double phi);
	static AffineTransformMatrix RotateInterwoven(double x, double y, double z);
	static AffineTransformMatrix RotateXY(int x, int y, double scale);
	static AffineTransformMatrix RotateXYZ(double x, double y, double z);

	void TranslateGlobal(double x, double y, double z);
	void TranslateLocal(double x, double y, double z);

	Vector3 Transform(const Vector3& v) const;

	wxString ToString();
	void FromString(wxString string);

	//private:
	void TakeMatrixApart(void);
	void PutMatrixTogether(void);
};

#endif /* AFFINETRANSFORMMATRIX_H_ */
