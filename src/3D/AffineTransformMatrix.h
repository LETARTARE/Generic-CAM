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
// http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
//
class Vector3;
class wxString;
class wxTextOutputStream;
class wxTextInputStream;
class AffineTransformMatrix {
public:
	enum orientation {
		rhs, //!< Right-handed system
		lhs  //!< Left-handed system
	};

	AffineTransformMatrix();
	AffineTransformMatrix(const Vector3& ex, const Vector3& ey,
			const Vector3& ez, const Vector3& center);

private:
	double a[16]; //!< Transformation matrix
	orientation side; //!< Handedness of the coordinate system

public:
	void SetOrientation(orientation side); //!< Preset the behavior for future Set and Calculate operations
	orientation GetOrientation(void) const; //!< Return the orientation flag
	orientation CheckOrientation(void) const; //!< Calculate the orientations of the coordinate system by analysing the matrix
	void UpdateOrientation(void); //!< Set the orientation flag according the the matrix values

	void SetIdentity(void); //!< Resets the matrix to the identity matrix.
	void ResetRotationAndScale(void); //!< Resets the rotation and scale, but keeps the translation

	void Set(AffineTransformMatrix const& b); //!< Copies a matrix by inserting a given matrix into \a a.
	void SetOrigin(const Vector3& center);

	void SetEx(const Vector3& ex);
	void SetEy(const Vector3& ey);
	void SetEz(const Vector3& ez);
	void CalculateEx(void);
	void CalculateEy(void);
	void CalculateEz(void);
	AffineTransformMatrix Normal(void) const;
	void Normalize(void);

	Vector3 GetOrigin(void) const; //!< Returns the center point of the matrix.
	Vector3 GetEx(void) const;
	Vector3 GetEy(void) const;
	Vector3 GetEz(void) const;

	AffineTransformMatrix& operator*=(const AffineTransformMatrix& b); //!< Overloaded operator to allow correct multiplication of two matrices.
	const AffineTransformMatrix operator*(const AffineTransformMatrix& b) const; //!< Overloaded operator to allow correct multiplication of two matrices.
	/*!\brief  Overloaded operator to allow correct division of two matrices.
	 *
	 * The division is done by inverting the second matrix and the multiplying both.
	 */
	AffineTransformMatrix& operator/=(const AffineTransformMatrix& b);
	const AffineTransformMatrix operator/(const AffineTransformMatrix& b) const; //!< Overloaded operator to allow correct division of two matrices.

	void Invert(void); //!< Inverts the matrix itself

	/*! \brief Returns an inverted matrix
	 *
	 * The transform used in here is optimized for matrices with 0,0,0,1 in the last row.
	 * It would not give the correct results for other matrices,
	 *
	 * \return Inverted matrix.
	 */
	const AffineTransformMatrix Inverse(void) const;

	static AffineTransformMatrix Identity(); //!< Function returning an identity matrix.

	/*!\brief Rotation matrix around a given vector.
	 *
	 * Generates a rotation matrix around a given vector.
	 * \param vector Axis of rotation.
	 * \param phi Angle of rotation.
	 * \return Rotation matrix.
	 */
	static AffineTransformMatrix RotationAroundVector(Vector3 const& vector,
			double const& phi);

	/*!\brief An interwoven rotation matrix.
	 *
	 * Generates a rotation matrix around x,y,z.
	 * In this case the rotations are interwoven:
	 *
	 * Every rotation (around x, around y and around z) is done
	 * in infinitesimal small steps. On step around x, one step around y, ...
	 *
	 * This results in a rotation as expected from a 6 DOF controller.
	 */

	static AffineTransformMatrix RotationInterwoven(double const& x,
			double const& y, double const& z);

	/*! \brief Rotation matrix for rotation by mouse.
	 *
	 * This function is only a drop in until the RotateByTrackball function works.
	 *
	 * \param x Movement of mouse in x direction (=xnew-xold).
	 * \param y Movement of mouse in y direction (=ynew-yold).
	 * \param scale Scaling of the movement.
	 * \return Rotation matrix.
	 */
	static AffineTransformMatrix RotationXY(int const& x, int const& y,
			double const& scale);

	/*! \brief Rotation matrix composed by the Z,Y,X rule.
	 */
	static AffineTransformMatrix RotationXYZ(double const& x, double const& y,
			double const& z);

	/*!\brief Rotation matrix around a virtual trackball.
	 *
	 * @param x1 Old x-mouse position on screen
	 * @param y1 Old y-mouse position on screen
	 * @param x2 New x-mouse position on screen
	 * @param y2 New y-mouse position on screen
	 * @param r Radius of a sphere in screen units.
	 * @return Rotational Matrix
	 */
	static AffineTransformMatrix RotationTrackball(double const& x1,
			double const& y1, double const& x2, double const& y2,
			double const& r);

	void TranslateGlobal(double const& x, double const& y, double const& z); //!< Translate matrix in the global coordinate system.
	void TranslateLocal(double const& x, double const& y, double const& z); //!< Translate matrix in the local, rotated coordinate system.

	void ScaleGlobal(double const& x, double const& y, double const& z); //!< Scale matrix in the global coordinate system.
	void ScaleLocal(double const& x, double const& y, double const& z); //!< Scale matrix in the local coordinate system.

	Vector3 Transform(Vector3 const& v) const; //!< Apply the transformation matrix on a given vector.
	Vector3 Transform(const double x, const double y = 0.0,
			const double z = 0.0) const;
	Vector3 TransformNoShift(Vector3 const& v) const; //!< Apply the transformation matrix on a given vector without shifting the vector.
	Vector3 TransformNoShift(const double x, const double y = 0.0,
			const double z = 0.0) const;
	Vector3 operator*(const Vector3& v) const;
	double &operator[](unsigned char index);
	const double operator[](unsigned char index) const;
	Vector3 operator()(const Vector3& v) const; //!< Operator reference for Vector3 transformations.
	Vector3 operator()(const double x, const double y = 0.0, const double z =
			0.0) const;

	double LocalX(const Vector3& v) const; ///< Maps a global point onto the local coordinate system, returns the local x.
	double LocalY(const Vector3& v) const; ///< Maps a global point onto the local coordinate system, returns the local y.
	double LocalZ(const Vector3& v) const; ///< Maps a global point onto the local coordinate system, returns the local z.
	double GlobalX(double x = 0.0, double y = 0.0, double z = 0.0) const; ///< Calculates the global x, given a local point.
	double GlobalY(double x = 0.0, double y = 0.0, double z = 0.0) const; ///< Calculates the global y, given a local point.
	double GlobalZ(double x = 0.0, double y = 0.0, double z = 0.0) const; ///< Calculates the global z, given a local point.

	double Distance(const AffineTransformMatrix &other) const;

public:
	void TakeMatrixApart(void); //!< Calculate rx,ry,rz,tx,ty,tz and sx,sy,sz from the matrix.
	double rx, ry, rz; //!< Rotation after taking the matrix apart.
	double tx, ty, tz; //!< Translation after taking the matrix apart.
	double sx, sy, sz; //!< Scaling after taking the matrix apart.
	void PutMatrixTogether(void); //!< Calculate the matrix from rx,ry,rz,tx,ty,tz and sx,sy,sz.

	wxString ToString(); //!< Generate a string containing the matrix.
	void FromString(wxString const& string); //!< Setup the matrix from a string.
	void ToStream(wxTextOutputStream & stream);
	void FromStream(wxTextInputStream & stream);

	void GLMultMatrix(void) const; //!< Multiply the matrix onto the active OpenGL matrix (right multiply)
	void Paint(const double scale = 1.0) const; //!< Display the coordinate system in OpenGL
};

#endif /* AFFINETRANSFORMMATRIX_H_ */
