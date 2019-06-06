///////////////////////////////////////////////////////////////////////////////
// Name               : AffineTransformMatrix.h
// Purpose            : A class to store a 3D affine transform matrix and provide operations upon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 22.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef AFFINETRANSFORMMATRIX_H_
#define AFFINETRANSFORMMATRIX_H_

/** \class AffineTransformMatrix
 * 	\code #include "AffineTransformMatrix.h"\endcode
 * 	\ingroup Base3D
 *  \brief A class to store a 3D affine transform matrix and provide operations upon.
 *
 * This class stores and manages a 4x4 matrix. This matrix is organized the same way,
 * the transformation matrices of OpenGL are:
 *
 * <table>
 * <tr><td>R11</td><td>R12</td><td>R13</td><td>Tx</td></tr>
 * <tr><td>R21</td><td>R22</td><td>R23</td><td>Ty</td></tr>
 * <tr><td>R31</td><td>R32</td><td>R33</td><td>Tz</td></tr>
 * <tr><td>0</td><td>0</td><td>0</td><td>1</td></tr>
 * </table>
 *
 * Where R is responsible for rotation and scaling
 * and T for translation.
 * The vector \c a is organized as follows:
 *
 * <table>
 * <tr><td>0</td><td>4</td><td>8</td><td>12</td></tr>
 * <tr><td>1</td><td>5</td><td>9</td><td>13</td></tr>
 * <tr><td>2</td><td>6</td><td>10</td><td>14</td></tr>
 * <tr><td>3</td><td>7</td><td>11</td><td>15</td></tr>
 * </table>
 *
 * Right handed coordinate system:
 *  * X to the right of the screen
 *  * Y to the top of the screen
 *  * Z towards the viewer
 *
 */

// http://www.parashift.com/c++-faq-lite/operator-overloading.html
class Vector3;

class wxString;
class wxTextOutputStream;
class wxTextInputStream;

class AffineTransformMatrix {
	// Constructor / Destructor
public:
	AffineTransformMatrix();

	// Member variables
public:
	double a[16]; //!< The transformation matrix.

	double rx, ry, rz; //!< Rotation after taking the matrix apart.
	double tx, ty, tz; //!< Translation after taking the matrix apart.
	double sx, sy, sz; //!< Scaling after taking the matrix apart.

	// Methods
public:

	void TakeMatrixApart(void);
	void PutMatrixTogether(void);

	wxString ToString();
	void FromString(wxString const& string);

	void ToStream(wxTextOutputStream & stream);
	void FromStream(wxTextInputStream & stream);

	void Set(AffineTransformMatrix const& b);

	AffineTransformMatrix& operator*=(const AffineTransformMatrix &b);
	const AffineTransformMatrix operator*(const AffineTransformMatrix& b) const;

	AffineTransformMatrix& operator/=(const AffineTransformMatrix &b);
	const AffineTransformMatrix operator/(const AffineTransformMatrix& b) const;

	void SetIdentity();

	const AffineTransformMatrix Inverse() const;

	static AffineTransformMatrix Identity();
	static AffineTransformMatrix RotationAroundVector(Vector3 const& vector,
			double const& phi);
	static AffineTransformMatrix RotationInterwoven(double const& x,
			double const& y, double const& z);
	static AffineTransformMatrix RotationXY(int const& x, int const& y,
			double const& scale);
	static AffineTransformMatrix RotationXYZ(double const& x, double const& y,
			double const& z);
	static AffineTransformMatrix RotationTrackball(double const& x1,
			double const& y1, double const& x2, double const& y2,
			double const& r);

	void TranslateGlobal(double const& x, double const& y, double const& z);
	void TranslateLocal(double const& x, double const& y, double const& z);

	void ScaleGlobal(double const& x, double const& y, double const& z);
	void ScaleLocal(double const& x, double const& y, double const& z);

	Vector3 Transform(Vector3 const& v) const;
	Vector3 operator()(const Vector3 &v) const;
	Vector3 TransformNoShift(Vector3 const& v) const;

	Vector3 GetCenter(void) const;
	double Distance(const AffineTransformMatrix &other) const;

};

#endif /* AFFINETRANSFORMMATRIX_H_ */
