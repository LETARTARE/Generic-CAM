///////////////////////////////////////////////////////////////////////////////
// Name               : AffineTransformMatrix.cpp
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

#include "AffineTransformMatrix.h"

#include "Vector3.h"

#include <wx/tokenzr.h>
#include <wx/string.h>
#include <wx/txtstrm.h>

#include <math.h>
#include <stdint.h>
#include <assert.h>

AffineTransformMatrix::AffineTransformMatrix()
{
	SetIdentity();
}

/*!\brief Copies a matrix by inserting a given matrix into \a a.
 *  \param b The matrix to copy.
 */
void AffineTransformMatrix::Set(AffineTransformMatrix const& b)
{
	if(this == &b) return;
	for(uint_fast8_t i = 0; i < 16; i++)
		a[i] = b.a[i];
	TakeMatrixApart();
}

//! Resets the matrix to the identity matrix.
void AffineTransformMatrix::SetIdentity()
{
	rx = ry = rz = 0.0;
	tx = ty = tz = 0.0;
	sx = sy = sz = 1.0;
	for(uint_fast8_t i = 0; i < 16; i++)
		a[i] = 0;
	a[0] = 1.0;
	a[5] = 1.0;
	a[10] = 1.0;
	a[15] = 1.0;
}

//! Returns the center point of the matrix.
Vector3 AffineTransformMatrix::GetCenter(void) const
{
	Vector3 temp;
	temp.x = a[12];
	temp.y = a[13];
	temp.z = a[14];
	return temp;
}

//! Generate a string containing the matrix.
wxString AffineTransformMatrix::ToString()
{
	TakeMatrixApart();
	wxString temp;
	temp += wxString::Format(_T("%f#%f#%f#"), tx, ty, tz);
	temp += wxString::Format(_T("%f#%f#%f#"), rx, ry, rz);
	temp += wxString::Format(_T("%f#%f#%f"), sx, sy, sz);
	return temp;
}

//! Setup the matrix from a string.
void AffineTransformMatrix::FromString(wxString const& string)
{
	wxStringTokenizer tkz(string, wxT("#"));
	while(tkz.HasMoreTokens()){
		wxString token = tkz.GetNextToken();
		switch(tkz.CountTokens()){
		case 8:
			token.ToDouble(&tx);
			break;
		case 7:
			token.ToDouble(&ty);
			break;
		case 6:
			token.ToDouble(&tz);
			break;
		case 5:
			token.ToDouble(&rx);
			break;
		case 4:
			token.ToDouble(&ry);
			break;
		case 3:
			token.ToDouble(&rz);
			break;
		case 2:
			token.ToDouble(&sx);
			break;
		case 1:
			token.ToDouble(&sy);
			break;
		case 0:
			token.ToDouble(&sz);
			break;
		}
	}
	PutMatrixTogether();
}

void AffineTransformMatrix::ToStream(wxTextOutputStream& stream)
{
	for(uint_fast8_t n = 0; n < 16; n++){
		if(n > 0) stream << _T(" ");
		stream.WriteDouble(a[n]);
	}
}

void AffineTransformMatrix::FromStream(wxTextInputStream& stream)
{
	for(uint_fast8_t n = 0; n < 16; n++)
		stream >> a[n];
	TakeMatrixApart();
}

//! Calculate rx,ry,rz,tx,ty,tz and sx,sy,sz from the matrix.
void AffineTransformMatrix::TakeMatrixApart(void)
{
	double b[16];

	tx = a[12];
	ty = a[13];
	tz = a[14];

	sx = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	sy = sqrt(a[4] * a[4] + a[5] * a[5] + a[6] * a[6]);
	sz = sqrt(a[8] * a[8] + a[9] * a[9] + a[10] * a[10]);

	if(fabs(sx) > 0.0){
		b[0] = a[0] / sx;
		b[1] = a[1] / sx;
		b[2] = a[2] / sx;
	}else{
		b[0] = 0.0;
		b[1] = 0.0;
		b[2] = 0.0;
	}
	if(fabs(sy) > 0.0){
		b[4] = a[4] / sy;
		b[5] = a[5] / sy;
		b[6] = a[6] / sy;
	}else{
		b[4] = 0.0;
		b[5] = 0.0;
		b[6] = 0.0;
	}
	if(fabs(sz) > 0.0){
		b[8] = a[8] / sz;
		b[9] = a[9] / sz;
		b[10] = a[10] / sz;
	}else{
		b[8] = 0.0;
		b[9] = 0.0;
		b[10] = 0.0;
	}

	//FIXME: I think this if(...) is wrong, because b[0] can be 0.
	if(fabs(b[0]) > 0.0 || fabs(b[1]) > 0.0){
		rz = atan2(b[1], b[0]);
	}else{
		rz = 0.0;
	}
	double coz = cos(rz);
	double siz = sin(rz);

	if(fabs(b[0]) > 0.0 || fabs(b[1]) > 0.0 || fabs(b[2]) > 0.0){
		ry = atan2(-b[2], sqrt(b[0] * b[0] + b[1] * b[1]));
	}else{
		ry = 0.0;
	}
	double coy = cos(ry);
	double siy = sin(ry);

	b[0] = b[5] * coy * siz - b[6] * siy + b[4] * coy * coz;
	b[1] = -b[4] * siz + b[5] * coz;
	b[2] = b[5] * siy * siz + b[4] * coz * siy + b[6] * coy;

	if(fabs(b[1]) > 0.0 || fabs(b[2]) > 0.0){
		rx = atan2(b[2], b[1]);
	}else{
		rx = 0.0;
	}
}

//! Calculate the matrix from rx,ry,rz,tx,ty,tz and sx,sy,sz.
void AffineTransformMatrix::PutMatrixTogether(void)
{
	const double cox = cos(rx);
	const double six = sin(rx);
	const double coy = cos(ry);
	const double siy = sin(ry);
	const double coz = cos(rz);
	const double siz = sin(rz);

	//Matrix calculated with Axiom:
	// Rx := matrix[[1,0,0],[0,cox,-six],[0,six,cox]]
	// Ry := matrix[[coy,0,siy],[0,1,0],[-siy,0,coy]]
	// Rz := matrix[[coz,-siz,0],[siz,coz,0],[0,0,1]]
	// S := matrix[[sx,0,0],[0,sy,0],[0,0,sz]]
	// Rz*Ry*Rx*S

	a[0] = coy * coz * sx;
	a[1] = coy * siz * sx;
	a[2] = -siy * sx;
	a[3] = 0.0;
	a[4] = (-cox * siz + coz * six * siy) * sy;
	a[5] = (six * siy * siz + cox * coz) * sy;
	a[6] = coy * six * sy;
	a[7] = 0.0;
	a[8] = (six * siz + cox * coz * siy) * sz;
	a[9] = (cox * siy * siz - coz * six) * sz;
	a[10] = cox * coy * sz;
	a[11] = 0.0;
	a[12] = tx;
	a[13] = ty;
	a[14] = tz;
	a[15] = 1.0;
}

/*! \brief Inverts the matrix.
 *
 * The transform used in here is optimized for matrices with 0,0,0,1 in the last row.
 * It would not give the correct results for other matrices,
 *
 * \return Inverted matrix.
 */
const AffineTransformMatrix AffineTransformMatrix::Inverse() const
{
	//Axiom code:
	// )set fortran optlevel 2
	// )set output fortran on
	// R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// inverse(R)

	const double T11 = (a[0] * a[5] + (-a[1] * a[4])) * a[10]
			+ ((-a[0] * a[6]) + a[2] * a[4]) * a[9]
			+ (a[1] * a[6] + (-a[2] * a[5])) * a[8];
	// T11 is the determinant of the matrix. This can
	// not be zero for a correct transformation matrix.
	assert(T11 != 0);

	const double T12 = a[4] * a[9];
	const double T13 = a[5] * a[8];
	const double T14 = a[4] * a[10];
	const double T15 = a[6] * a[8];
	const double T16 = a[5] * a[10];
	const double T17 = a[6] * a[9];
	const double T18 = a[0] * a[9];
	const double T19 = a[1] * a[8];
	const double T21 = a[0] * a[10];
	const double T22 = a[2] * a[8];
	const double T24 = a[1] * a[10];
	const double T25 = a[2] * a[9];
	const double T27 = a[1] * a[6] + (-a[2] * a[5]);
	const double T28 = (-a[0] * a[6]) + a[2] * a[4];
	const double T29 = a[0] * a[5] + (-a[1] * a[4]);
	const double T30 = a[0] * a[5];
	const double T31 = a[1] * a[4];
	const double T32 = a[0] * a[6];
	const double T33 = a[2] * a[4];
	const double T34 = a[1] * a[6];
	const double T35 = a[2] * a[5];

	AffineTransformMatrix b;

	b.a[0] = (T16 - T17) / T11;
	b.a[4] = (-T14 + T15) / T11;
	b.a[8] = (T12 - T13) / T11;
	b.a[12] =
			((-T12 + T13) * a[14] + (T14 - T15) * a[13] + (-T16 + T17) * a[12])
					/ T11;
	b.a[1] = (-T24 + T25) / T11;
	b.a[5] = (T21 - T22) / T11;
	b.a[9] = (-T18 + T19) / T11;
	b.a[13] =
			((T18 - T19) * a[14] + (-T21 + T22) * a[13] + (-T25 + T24) * a[12])
					/ T11;
	b.a[2] = T27 / T11;
	b.a[6] = T28 / T11;
	b.a[10] = T29 / T11;
	b.a[14] =
			((-T30 + T31) * a[14] + (T32 - T33) * a[13] + (-T34 + T35) * a[12])
					/ T11;
	b.a[3] = 0;
	b.a[7] = 0;
	b.a[11] = 0;
	b.a[15] = 1;
	return b;
}

//! Overloaded operator to allow correct multiplication of two matrices.
AffineTransformMatrix& AffineTransformMatrix::operator*=(
		const AffineTransformMatrix& b)
{
	//Generated with this code:
	//php -r'for($i=0;$i<4;$i++){for($j=0;$j<4;$j++){printf("this->a[%u]=",$i*4+$j);for($k=0;$k<4;$k++){printf("c[%u]*b.a[%u]%s",$k*4+$j,$i*4+$k,($k==3)?";\r\n":"+");}}}'

	// The php code generates all combinations.
	// The axiom code optimizes it a little more, because b.a[3], b.a[7] and b.a[11] are
	// zero and b.a[15] is one.

	// Axiom:
	// this:=matrix([[c[0],c[4],c[8],c[12]],[c[1],c[5],c[9],c[13]],[c[2],c[6],c[10],c[14]],[0,0,0,1]]);
	// b:=matrix([[ba[0],ba[4],ba[8],ba[12]],[ba[1],ba[5],ba[9],ba[13]],[ba[2],ba[6],ba[10],ba[14]],[0,0,0,1]]);

	double c[16];
	for(uint_fast8_t i = 0; i < 16; i++)
		c[i] = this->a[i];

	this->a[0] = c[0] * b.a[0] + c[4] * b.a[1] + c[8] * b.a[2];
	this->a[1] = c[1] * b.a[0] + c[5] * b.a[1] + c[9] * b.a[2];
	this->a[2] = c[2] * b.a[0] + c[6] * b.a[1] + c[10] * b.a[2];
	this->a[3] = 0;

	this->a[4] = c[0] * b.a[4] + c[4] * b.a[5] + c[8] * b.a[6];
	this->a[5] = c[1] * b.a[4] + c[5] * b.a[5] + c[9] * b.a[6];
	this->a[6] = c[2] * b.a[4] + c[6] * b.a[5] + c[10] * b.a[6];
	this->a[7] = 0;

	this->a[8] = c[0] * b.a[8] + c[4] * b.a[9] + c[8] * b.a[10];
	this->a[9] = c[1] * b.a[8] + c[5] * b.a[9] + c[9] * b.a[10];
	this->a[10] = c[2] * b.a[8] + c[6] * b.a[9] + c[10] * b.a[10];
	this->a[11] = 0;

	this->a[12] = c[0] * b.a[12] + c[4] * b.a[13] + c[8] * b.a[14] + c[12];
	this->a[13] = c[1] * b.a[12] + c[5] * b.a[13] + c[9] * b.a[14] + c[13];
	this->a[14] = c[2] * b.a[12] + c[6] * b.a[13] + c[10] * b.a[14] + c[14];
	this->a[15] = 1;

	return *this;
}

//! Overloaded operator to allow correct multiplication of two matrices.
const AffineTransformMatrix AffineTransformMatrix::operator*(
		const AffineTransformMatrix& b) const
{
	AffineTransformMatrix c = *this;
	c *= b;
	return c;
}

/*!\brief  Overloaded operator to allow correct division of two matrices.
 *
 * The division is done by inverting the second matrix and the multiplying both.
 */
AffineTransformMatrix& AffineTransformMatrix::operator/=(
		const AffineTransformMatrix& b)
{
	(*this) = (*this) * (b.Inverse());
	return *this;
}

//! Overloaded operator to allow correct division of two matrices.
const AffineTransformMatrix AffineTransformMatrix::operator/(
		const AffineTransformMatrix& b) const
{
	AffineTransformMatrix c = *this;
	c /= b;
	return c;
}

//! Apply the transformation matrix on a given vector.
Vector3 AffineTransformMatrix::Transform(Vector3 const& v) const
{
	//Axiom code:
	// R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// V:=matrix([[x],[y],[z],[1]])
	// R*V

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12];
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13];
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14];
	return temp;
}

//! Operator reference for Vector3 transformations.
Vector3 AffineTransformMatrix::operator ()(const Vector3 &v) const
{
	Vector3 temp;
		temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12];
		temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13];
		temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14];
		return temp;
}

//! Apply the transformation matrix on a given vector without shifting the vector.
Vector3 AffineTransformMatrix::TransformNoShift(Vector3 const& v) const
{
	//Axiom code:
	// R:=matrix([[a[0],a[4],a[8],0],[a[1],a[5],a[9],0],[a[2],a[6],a[10],0],[0,0,0,1]])
	// V:=matrix([[x],[y],[z],[1]])
	// R*V

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z;
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z;
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z;
	return temp;
}

//! Function returning an identity matrix.
AffineTransformMatrix AffineTransformMatrix::Identity()
{
	AffineTransformMatrix a;
	return a;
}

//! Translate matrix in the global coordinate system.
void AffineTransformMatrix::TranslateGlobal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// T:=matrix([[1,0,0,x],[0,1,0,y],[0,0,1,z],[0,0,0,1]]);
	// T*this
	a[12] += x;
	a[13] += y;
	a[14] += z;
}

//! Translate matrix in the local, rotated coordinate system.
void AffineTransformMatrix::TranslateLocal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// T:=matrix([[1,0,0,x],[0,1,0,y],[0,0,1,z],[0,0,0,1]]);
	// this*T
	a[12] += x * a[0] + y * a[4] + z * a[8];
	a[13] += x * a[1] + y * a[5] + z * a[9];
	a[14] += x * a[2] + y * a[6] + z * a[10];
}

//! Scale matrix in the global coordinate system.
void AffineTransformMatrix::ScaleGlobal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// S:=matrix([[x,0,0,0],[0,y,0,0],[0,0,z,0],[0,0,0,1]]);
	// S*this

	a[0] *= x;
	a[1] *= y;
	a[2] *= z;
	a[4] *= x;
	a[5] *= y;
	a[6] *= z;
	a[8] *= x;
	a[9] *= y;
	a[10] *= z;
	a[12] *= x;
	a[13] *= y;
	a[14] *= z;
}

//! Scale matrix in the local coordinate system.
void AffineTransformMatrix::ScaleLocal(const double& x, const double& y,
		const double& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// S:=matrix([[x,0,0,0],[0,y,0,0],[0,0,z,0],[0,0,0,1]]);
	// this*S

	a[0] *= x;
	a[1] *= x;
	a[2] *= x;
	a[4] *= y;
	a[5] *= y;
	a[6] *= y;
	a[8] *= z;
	a[9] *= z;
	a[10] *= z;
}

/*!\brief Rotation around a given vector.
 *
 * Generates a rotation matrix around a given vector.
 * \param vector Axis of rotation.
 * \param phi Angle of rotation.
 * \return Rotation matrix.
 */
AffineTransformMatrix AffineTransformMatrix::RotationAroundVector(
		Vector3 const& vector, double const& phi)
{
	const double c = cos(phi);
	const double s = sin(phi);
	const double t = 1 - c;

	Vector3 v(vector);
	v.Normalize();

	AffineTransformMatrix a;

	a.a[0] = t * v.x * v.x + c;
	a.a[1] = t * v.x * v.y + s * v.z;
	a.a[2] = t * v.x * v.z - s * v.y;

	a.a[4] = t * v.x * v.y - s * v.z;
	a.a[5] = t * v.y * v.y + c;
	a.a[6] = t * v.y * v.z + s * v.x;

	a.a[8] = t * v.x * v.z + s * v.y;
	a.a[9] = t * v.y * v.z - s * v.x;
	a.a[10] = t * v.z * v.z + c;

	return a;
}

/*! \brief Rotation by mouse.
 *
 * This function is only a drop in until the RotateByTrackball function works.
 *
 * \param x Movement of mouse in x direction (=xnew-xold).
 * \param y Movement of mouse in y direction (=ynew-yold).
 * \param scale Scaling of the movement.
 * \return Rotation matrix.
 */
AffineTransformMatrix AffineTransformMatrix::RotationXY(int const& x,
		int const& y, double const& scale)
{

	const double dx = (double) x / scale;
	const double dy = (double) y / scale;

	const double dist = sqrt(dx * dx + dy * dy);

	AffineTransformMatrix a;

	if(dist > 0.001){
		const double ang = -atan2(dy, dx);

		const double coy = cos(dist / 100);
		const double siy = sin(dist / 100);
		const double coz = cos(ang);
		const double siz = sin(ang);

		a.a[0] = coz * coz * coy + siz * siz;
		a.a[1] = coz * siz * coy - coz * siz;
		a.a[2] = -coz * siy;
		a.a[4] = siz * coz * coy - coz * siz;
		a.a[5] = siz * siz * coy + coz * coz;
		a.a[6] = -siz * siy;
		a.a[8] = coz * siy;
		a.a[9] = siz * siy;
		a.a[10] = coy;
	}
	return a;
}

//! Rotation by the Z,Y,X rule.
AffineTransformMatrix AffineTransformMatrix::RotationXYZ(double const& x,
		double const& y, double const& z)
{
	AffineTransformMatrix a;

	//Axiom code:
	// Rx := matrix[[1,0,0,0],[0,cox,-six,0],[0,six,cox,0],[0,0,0,1]]
	// Ry := matrix[[coy,0,siy,0],[0,1,0,0],[-siy,0,coy,0],[0,0,0,1]]
	// Rz := matrix[[coz,-siz,0,0],[siz,coz,0,0],[0,0,1,0],[0,0,0,1]]
	// Rz*Ry*Rx

	const double six = sin(x);
	const double siy = sin(y);
	const double siz = sin(z);
	const double cox = cos(x);
	const double coy = cos(y);
	const double coz = cos(z);

	a.a[0] = coy * coz;
	a.a[1] = coy * siz;
	a.a[2] = -siy;

	a.a[4] = -cox * siz + coz * six * siy;
	a.a[5] = six * siy * siz + cox * coz;
	a.a[6] = coy * six;

	a.a[8] = six * siz + cox * coz * siy;
	a.a[9] = cox * siy * siz - coz * six;
	a.a[10] = cox * coy;

	return a;
}

/*!\brief An interwoven rotation.
 *
 * Generates a rotation matrix around x,y,z.
 * In this case the rotations are interwoven:
 *
 * Every rotation (around x, around y and around z) is done
 * in infinitesimal small steps. On step around x, one step around y, ...
 *
 * This results in a rotation as expected from a 6 DOF controller.
 */
AffineTransformMatrix AffineTransformMatrix::RotationInterwoven(double const& x,
		double const& y, double const& z)
{
	const double alpha = sqrt(x * x + y * y + z * z);
	if(alpha == 0) return AffineTransformMatrix::Identity();
	const Vector3 R(x / alpha, y / alpha, z / alpha);
	return AffineTransformMatrix::RotationAroundVector(R, alpha);
}

/*!\brief Rotate around a virtual trackball.
 *
 * @param x1 Old x-mouse position on screen
 * @param y1 Old y-mouse position on screen
 * @param x2 New x-mouse position on screen
 * @param y2 New y-mouse position on screen
 * @param r Radius of a sphere in screen units.
 * @return Rotational Matrix
 */
AffineTransformMatrix AffineTransformMatrix::RotationTrackball(const double& x1,
		const double& y1, const double& x2, const double& y2, const double& r)
{
	Vector3 r1(x1, y1, 0);
	r1 /= r;
	const double d1 = r1.Abs2();
	if(d1 >= 1.0){
		r1 /= sqrt(d1);
	}else{
		r1.z = sqrt(1 - d1);
	}
	Vector3 r2(x2, y2, 0);
	r2 /= r;
	const double d2 = r2.Abs2();
	if(d2 >= 1.0){
		r2 /= sqrt(d2);
	}else{
		r2.z = sqrt(1 - d2);
	}
	const Vector3 A = r1 * r2;
	const double alpha = asin(A.Abs());
	return AffineTransformMatrix::RotationAroundVector(A, alpha);
}

double AffineTransformMatrix::Distance(const AffineTransformMatrix& other) const
{
	const bool useNaiveDistance = true;

	if(useNaiveDistance){
		double temp = 0.0;
		for(uint_fast8_t n = 0; n < 16; ++n)
			temp += (a[n] - other.a[n]) * (a[n] - other.a[n]);
		return sqrt(temp);
	}


	// If two matrices are identical, the matrix times the inverse of the other
	// should be the identity matrix.

	// A:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// B:=matrix([[b[0],b[4],b[8],b[12]],[b[1],b[5],b[9],b[13]],[b[2],b[6],b[10],b[14]],[0,0,0,1]])
	// I:=matrix([[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]])
	// R:=A*inverse(B)-I
	// trace(R*transpose(R))

	const double T2 = a[2];
	const double T3 = a[1];
	const double T4 = a[0];
	const double T5 = other.a[4];
	const double T6 = a[6];
	const double T7 = a[5];
	const double T8 = a[4];
	const double T9 = other.a[0];
	const double T10 = T2 * T2;
	const double T11 = T3 * T3;
	const double T12 = T4 * T4;
	const double T13 = 2 * T2 * T6;
	const double T14 = 2 * T3 * T7;
	const double T15 = 2 * T4 * T8;
	const double T16 = T13 + T14 + T15;
	const double T17 = T6 * T6;
	const double T18 = T7 * T7;
	const double T19 = T8 * T8;
	const double T20 = other.a[1];
	const double T21 = a[10];
	const double T22 = a[9];
	const double T23 = a[8];
	const double T24 = T9 * T9;
	const double T25 = other.a[5];
	const double T26 = 2 * T2 * T21;
	const double T27 = 2 * T3 * T22;
	const double T28 = 2 * T4 * T23;
	const double T29 = T5 * T5;
	const double T30 = 2 * T6 * T21;
	const double T31 = 2 * T7 * T22;
	const double T32 = 2 * T8 * T23;
	const double T33 = other.a[9];
	const double T34 = T10 + T11 + T12;
	const double T35 = -T13 - T14 - T15;
	const double T36 = T17 + T18 + T19;
	const double T37 = other.a[8];
	const double T38 = -T26 - T27 - T28;
	const double T39 = T25 * T25;
	const double T40 = T26 + T27 + T28;
	const double T41 = T30 + T31 + T32;
	const double T42 = -T30 - T31 - T32;
	const double T43 = T20 * T20;
	const double T44 = T21 * T21;
	const double T45 = T22 * T22;
	const double T46 = T23 * T23;
	const double T47 = T44 + T45 + T46;
	const double T48 = (-2 * T10) + (-2 * T11) + (-2 * T12);
	const double T49 = (-2 * T17) + (-2 * T18) + (-2 * T19);
	const double T50 = 2 * T10;
	const double T51 = 2 * T11;
	const double T52 = 2 * T12;
	const double T53 = 2 * T17;
	const double T54 = 2 * T18;
	const double T55 = 2 * T19;
	const double T56 = (T50 + T51 + T52) * T5 + T35 * T9;
	const double T57 = T53 + T54 + T55;
	const double T58 = other.a[2];
	const double T59 = T38 * T9 * T5 + T41 * T24;
	const double T60 = other.a[6];
	const double T61 = T37 * T37;
	const double T62 = (-2 * T44) + (-2 * T45) + (-2 * T46);
	const double T63 = 2 * T44;
	const double T64 = 2 * T45;
	const double T65 = 2 * T46;
	const double T66 = T63 + T64 + T65;
	const double T67 = T56 * T25 + T35 * T20 * T5 + T57 * T9 * T20;
	const double T68 = 4 * T2 * T6 + 4 * T3 * T7 + 4 * T4 * T8;
	const double T69 = T38 * T20 * T5;
	const double T70 = T42 * T9 * T20;
	const double T71 = other.a[10];
	const double T72 = T48 * T5 + T16 * T9;
	const double T73 = T33 * T33;
	const double T74 = T50 + T51 + T52;
	const double T75 = 4 * T2 * T21 + 4 * T3 * T22 + 4 * T4 * T23;
	const double T76 = T38 * T58 * T5;
	const double T77 = 4 * T6 * T21 + 4 * T7 * T22 + 4 * T8 * T23;
	const double T78 = a[14];
	const double T79 = a[13];
	const double T80 = a[12];
	const double T81 = 2 * T2 * T78;
	const double T82 = 2 * T3 * T79;
	const double T83 = 2 * T4 * T80;
	const double T84 = 2 * T6 * T78;
	const double T85 = 2 * T7 * T79;
	const double T86 = 2 * T8 * T80;
	const double T87 = T81 + T82 + T83;
	const double T88 = -T81 - T82 - T83;
	const double T89 = -T84 - T85 - T86;
	const double T90 = T84 + T85 + T86;
	const double T91 = (-2 * T21 * T78) + (-2 * T22 * T79) + (-2 * T23 * T80);
	const double T92 = T88 * T20 * T5;
	const double T93 = 2 * T21 * T78;
	const double T94 = 2 * T22 * T79;
	const double T95 = 2 * T23 * T80;
	const double T96 = T93 + T94 + T95;
	const double T97 = other.a[14];
	const double T98 = T34 * T29 + T35 * T9 * T5 + T36 * T24;
	const double T99 = T72 * T60 + T16 * T58 * T5 + T49 * T9 * T58;
	const double T100 = T40 * T9 * T5 + T42 * T24;
	const double T101 = T60 * T60;
	const double T102 = T58 * T58;
	const double T103 = other.a[13];
	const double T104 = T72 * T25 + T16 * T20 * T5 + T49 * T9 * T20;
	const double T105 = T71 * T71;
	const double T106 = T56 * T60 + T35 * T58 * T5 + T57 * T9 * T58;
	const double T107 = ((T74 * T25 + T35 * T20) * T60 + T35 * T58 * T25
			+ T57 * T20 * T58) * T37;
	const double T108 = T38 * T9 * T25;
	const double T109 = T42 * T9 * T58;
	const double T110 = T42 * T20 * T58 * T5;
	const double T111 = T76 + T109;
	const double T112 = other.a[12];
	const double T113 = T87 * T9 * T5 + T89 * T24;
	const double T114 = T88 * T9 * T5 + T90 * T24;
	const double T115 = T88 * T9 * T25;
	const double T116 = 4 * T2 * T78 + 4 * T3 * T79 + 4 * T4 * T80;
	const double T117 = T89 * T9 * T20;
	const double T118 = 4 * T6 * T78 + 4 * T7 * T79 + 4 * T8 * T80;
	const double T119 = T89 * T20 * T58 * T5;
	const double T120 = (T96 * T24 * T25 + T91 * T9 * T20 * T5) * T60;
	const double T121 = T91 * T9 * T58 * T5 * T25;
	const double T122 = T96 * T20 * T58 * T29;
	const double T123 = T88 * T58 * T5;
	const double T124 = T89 * T9 * T58;
	const double T125 = 4 * T21 * T78 + 4 * T22 * T79 + 4 * T23 * T80;
	const double T126 = T34 * T39 + T35 * T20 * T25 + T36 * T43;
	const double T127 = (T48 * T25 + T16 * T20) * T60 + T16 * T58 * T25
			+ T49 * T20 * T58;
	const double T128 = T34 * T101 + T35 * T58 * T60 + T36 * T102;
	const double T129 = T123 + T124;
	const double T130 = (T91 * T9 * T20 * T25 + T96 * T43 * T5) * T60;
	const double T131 = T96 * T9 * T58 * T39;
	const double T132 = T91 * T20 * T58 * T5 * T25;
	const double T133 = T96 * T9 * T20 * T101;
	const double T134 = (T91 * T9 * T58 * T25 + T91 * T20 * T58 * T5) * T60;
	const double T135 = T96 * T102 * T5 * T25;
	const double T136 = T78 * T78;
	const double T137 = T79 * T79;
	const double T138 = T80 * T80;
	const double T139 = T136 + T137 + T138 + 3;
	const double T140 = T35 * T9;
	const double T141 = T36 * T43;
	const double T142 = T36 * T24;
	const double T143 = (-2 * T136) + (-2 * T137) + (-2 * T138) - 6;
	const double T144 = 2 * T136;
	const double T145 = 2 * T137;
	const double T146 = 2 * T138;
	const double T147 = 2 * T4;
	const double T148 = 2 * T3 * T9;
	const double T149 = 2 * T8 * T9;
	const double T150 = 2 * T7 * T24;
	const double T151 = (T144 + T145 + T146 + 6) * T9 - T147;
	const double T152 = -T149 + T13 + T14 + T15;
	const double T153 = T49 * T20 * T58;
	const double T154 = T151 * T20 - T148;
	const double T155 = 2 * T8 * T43;
	const double T156 = 2 * T7 * T9 * T20;
	const double T157 = T16 * T9;
	const double T158 = T143 * T9 + T147;
	const double T159 = 2 * T2 * T9;
	const double T160 = T144 + T145 + T146 + 6;
	const double T161 = 2 * T3;
	const double T162 = 2 * T2 * T20;
	const double T163 = -2 * T6 * T9 * T20;
	const double T164 = T49 * T9 * T58;
	const double T165 = T42 * T43;
	const double T166 = T42 * T24;
	const double T167 = 2 * T23 * T9;
	const double T168 = T41 * T20 * T58;
	const double T169 = T41 * T9 * T58 * T5;
	const double T170 = T139 * T24 + (-2 * T4 * T9) + T10 + T11 + T12;
	const double T171 = T158 * T58 + T159;
	const double T172 = T149 - T13 - T14 - T15;
	const double T173 = 2 * T6 * T24;
	const double T174 = T36 * T102;
	const double T175 = T158 * T20 + T148;
	const double T176 = T151 * T58 - T159;
	const double T177 = ((T160 * T20 - T161) * T58 - T162) * T5;
	const double T178 = -2 * T8 * T20;
	const double T179 = -2 * T7 * T9;
	const double T180 = 2 * T8 * T102;
	const double T181 = 2 * T6 * T9 * T58;
	const double T182 = T16 * T20;
	const double T183 = T49 * T9 * T20;
	const double T184 = T167 - T26 - T27 - T28;
	const double T185 = 2 * T22 * T24;
	const double T186 = -T167 + T26 + T27 + T28;
	const double T187 = 2 * T21 * T24;
	const double T188 = -2 * T23 * T20;
	const double T189 = T40 * T9;
	const double T190 = T41 * T9 * T20 * T5;
	const double T191 = T139 * T43 + (-2 * T3 * T20) + T10 + T11 + T12;
	const double T192 = (T143 * T20 + T161) * T58 + T162;
	const double T193 = 2 * T7 * T20;
	const double T194 = 2 * T6 * T43;
	const double T195 = T139 * T102 + (-2 * T2 * T58) + T10 + T11 + T12;
	const double T196 = 2 * T7 * T102;
	const double T197 = 2 * T6 * T20 * T58;
	const double T198 = T35 * T20;
	const double T199 = 2 * T23 * T43;
	const double T200 = 2 * T22 * T9 * T20;
	const double T201 = -2 * T22 * T9;
	const double T202 = -2 * T21 * T9 * T20;
	const double T203 = 2 * T22 * T20;
	const double T204 = 2 * T21 * T43;
	const double T205 = T41 * T9 * T58;
	const double T206 = 2 * T23 * T102;
	const double T207 = 2 * T21 * T9 * T58;
	const double T208 = T38 * T9;
	const double T209 = 2 * T22 * T102;
	const double T210 = 2 * T21 * T20 * T58;
	const double T211 = T41 * T9 * T20;
	const double T212 = T42 * T102;
	const double T213 = T47 * T24;
	const double T214 = T62 * T9 * T20 * T5 * T25;
	const double T215 = T47 * T102;
	const double T216 = T47 * T43;
	const double T217 = (T98 * T73
			+ (T104 * T37 + T100 * T25 + T38 * T20 * T29 + T190) * T33
			+ T126 * T61
			+ (T38 * T9 * T39 + (T40 * T20 * T5 + T211) * T25 + T42 * T43 * T5)
					* T37 + T47 * T24 * T39 + T214 + T47 * T43 * T29) * T97
			* T97
			+ ((((T48 * T29 + T68 * T9 * T5 + T49 * T24) * T33 + T67 * T37
					+ T59 * T25 + T40 * T20 * T29 + T42 * T9 * T20 * T5) * T71
					+ (T106 * T37 + T59 * T60 + T40 * T58 * T29
							+ T42 * T9 * T58 * T5) * T33 + T127 * T61
					+ ((T75 * T9 * T25 + T69 + T70) * T60 + T111 * T25
							+ T77 * T20 * T58 * T5) * T37
					+ (T62 * T24 * T25 + T66 * T9 * T20 * T5) * T60
					+ T66 * T9 * T58 * T5 * T25 + T62 * T20 * T58 * T29) * T103
					+ ((T67 * T33
							+ (T48 * T39 + T68 * T20 * T25 + T49 * T43) * T37
							+ T40 * T9 * T39 + (T69 + T70) * T25
							+ T41 * T43 * T5) * T71 + T99 * T73
							+ (T107 + (T108 + T75 * T20 * T5 + T70) * T60
									+ (T76 + T77 * T9 * T58) * T25 + T110) * T33
							+ ((T38 * T20 * T25 + T41 * T43) * T60
									+ T40 * T58 * T39 + T42 * T20 * T58 * T25)
									* T37
							+ (T66 * T9 * T20 * T25 + T62 * T43 * T5) * T60
							+ T62 * T9 * T58 * T39 + T66 * T20 * T58 * T5 * T25)
							* T112
					+ ((T114 * T25 + T87 * T20 * T29 + T89 * T9 * T20 * T5)
							* T33
							+ (T87 * T9 * T39 + (T92 + T117) * T25
									+ T90 * T43 * T5) * T37 + T91 * T24 * T39
							+ T125 * T9 * T20 * T5 * T25 + T91 * T43 * T29)
							* T71
					+ (T113 * T60 + T88 * T58 * T29 + T90 * T9 * T58 * T5) * T73
					+ (((T115 + T92 + T118 * T9 * T20) * T60
							+ (T116 * T58 * T5 + T124) * T25 + T119) * T37
							+ T120 + T121 + T122) * T33
					+ ((T87 * T20 * T25 + T89 * T43) * T60 + T88 * T58 * T39
							+ T90 * T20 * T58 * T25) * T61
					+ (T130 + T131 + T132) * T37) * T97
			+ (T98 * T105
					+ (T99 * T37 + T100 * T60 + T38 * T58 * T29 + T169) * T71
					+ T128 * T61
					+ (T38 * T9 * T101 + (T40 * T58 * T5 + T205) * T60
							+ T42 * T102 * T5) * T37 + T47 * T24 * T101
					+ T62 * T9 * T58 * T5 * T60 + T47 * T102 * T29) * T103
					* T103;
	const double T218 = T217
			+ ((T104 * T105
					+ (T106 * T33 + T107 + (T108 + T69 + T77 * T9 * T20) * T60
							+ (T75 * T58 * T5 + T109) * T25 + T110) * T71
					+ ((T48 * T101 + T68 * T58 * T60 + T49 * T102) * T37
							+ T40 * T9 * T101 + T111 * T60 + T41 * T102 * T5)
							* T33
					+ (T40 * T20 * T101
							+ (T38 * T58 * T25 + T42 * T20 * T58) * T60
							+ T41 * T102 * T25) * T37 + T62 * T9 * T20 * T101
					+ (T66 * T9 * T58 * T25 + T66 * T20 * T58 * T5) * T60
					+ T62 * T102 * T5 * T25) * T112
					+ (T113 * T25 + T88 * T20 * T29 + T90 * T9 * T20 * T5)
							* T105
					+ ((T114 * T60 + T87 * T58 * T29 + T89 * T9 * T58 * T5)
							* T33
							+ ((T115 + T116 * T20 * T5 + T117) * T60
									+ (T123 + T118 * T9 * T58) * T25 + T119)
									* T37 + T120 + T121 + T122) * T71
					+ ((T87 * T9 * T101 + T129 * T60 + T90 * T102 * T5) * T37
							+ T91 * T24 * T101 + T125 * T9 * T58 * T5 * T60
							+ T91 * T102 * T29) * T33
					+ (T88 * T20 * T101
							+ (T87 * T58 * T25 + T90 * T20 * T58) * T60
							+ T89 * T102 * T25) * T61
					+ (T133 + T134 + T135) * T37) * T103
			+ (T126 * T105
					+ (T127 * T33 + (T40 * T20 * T25 + T165) * T60
							+ T38 * T58 * T39 + T41 * T20 * T58 * T25) * T71
					+ T128 * T73
					+ (T38 * T20 * T101 + (T40 * T58 * T25 + T168) * T60
							+ T42 * T102 * T25) * T33 + T47 * T43 * T101
					+ T62 * T20 * T58 * T25 * T60 + T47 * T102 * T39) * T112
					* T112
			+ ((T88 * T9 * T39 + (T87 * T20 * T5 + T90 * T9 * T20) * T25
					+ T89 * T43 * T5) * T105
					+ (((T116 * T9 * T25 + T92 + T117) * T60 + T129 * T25
							+ T118 * T20 * T58 * T5) * T33
							+ ((T88 * T20 * T25 + T90 * T43) * T60
									+ T87 * T58 * T39 + T89 * T20 * T58 * T25)
									* T37 + T130 + T131 + T132) * T71
					+ (T88 * T9 * T101 + (T87 * T58 * T5 + T90 * T9 * T58) * T60
							+ T89 * T102 * T5) * T73
					+ ((T87 * T20 * T101
							+ (T88 * T58 * T25 + T89 * T20 * T58) * T60
							+ T90 * T102 * T25) * T37 + T133 + T134 + T135)
							* T33
					+ (T91 * T43 * T101 + T125 * T20 * T58 * T25 * T60
							+ T91 * T102 * T39) * T37) * T112;
	const double T219 = T218
			+ (T170 * T39 + (T175 * T5 + T172 * T20 - T150) * T25 + T191 * T29
					+ (-T155 + T156 + T140) * T5 + T141 + T142) * T105
			+ ((((T143 * T24 + 4 * T4 * T9 - T50 - T51 - T52) * T25 + T154 * T5
					+ T152 * T20 + T150) * T60
					+ (T176 * T5 + T152 * T58 + T173) * T25 + T192 * T29
					+ ((4 * T8 * T20 + T179) * T58 + T163) * T5 + T153) * T33
					+ ((T154 * T25
							+ (T143 * T43 + 4 * T3 * T20 - T50 - T51 - T52) * T5
							+ T155 - T156 + T157) * T60 + T171 * T39
							+ (T177 + (T178 + 4 * T7 * T9) * T58 + T163) * T25
							+ ((-T193 + T13 + T14 + T15) * T58 + T194) * T5
							+ T164) * T37
					+ ((T186 * T20 + T185) * T25 + (T199 - T200 + T189) * T5
							+ T165 + T166) * T60 + (T184 * T58 - T187) * T39
					+ (((T188 + T201) * T58 + 4 * T21 * T9 * T20) * T5 + T168)
							* T25
					+ ((T203 - T26 - T27 - T28) * T58 - T204) * T29 + T169)
					* T71
			+ (T170 * T101 + (T171 * T5 + T172 * T58 - T173) * T60 + T195 * T29
					+ (-T180 + T181 + T140) * T5 + T174 + T142) * T73
			+ ((T175 * T101
					+ (T176 * T25 + T177 + (T178 + T179) * T58
							+ 4 * T6 * T9 * T20) * T60
					+ ((T143 * T102 + 4 * T2 * T58 - T50 - T51 - T52) * T5
							+ T180 - T181 + T157) * T25
					+ (T196 - T197 + T182) * T5 + T183) * T37
					+ (T184 * T20 - T185) * T101
					+ ((T186 * T58 + T187) * T25
							+ ((T188 + 4 * T22 * T9) * T58 + T202) * T5 + T168)
							* T60
					+ ((T206 - T207 + T189) * T5 + T212 + T166) * T25
					+ (-T209 + T210 + T38 * T20) * T29 + T190) * T33
			+ (T191 * T101
					+ (T192 * T25 + (T193 - T13 - T14 - T15) * T58 - T194) * T60
					+ T195 * T39 + (-T196 + T197 + T198) * T25 + T174 + T141)
					* T61
			+ ((-T199 + T200 + T208) * T101
					+ (((4 * T23 * T20 + T201) * T58 + T202) * T25
							+ ((-T203 + T26 + T27 + T28) * T58 + T204) * T5
							+ T205) * T60 + (-T206 + T207 + T208) * T39
					+ ((T209 - T210 + T40 * T20) * T5 + T211) * T25
					+ (T212 + T165) * T5) * T37;
	const double R22 = (T219 + (T216 + T213) * T101
			+ (T62 * T20 * T58 * T25 + T62 * T9 * T58 * T5) * T60
			+ (T215 + T213) * T39 + T214 + (T215 + T216) * T29)
			/ ((T24 * T39 + (-2 * T9 * T20 * T5 * T25) + T43 * T29) * T105
					+ ((((-2 * T24 * T25) + 2 * T9 * T20 * T5) * T60
							+ 2 * T9 * T58 * T5 * T25 + (-2 * T20 * T58 * T29))
							* T33
							+ ((2 * T9 * T20 * T25 + (-2 * T43 * T5)) * T60
									+ (-2 * T9 * T58 * T39)
									+ 2 * T20 * T58 * T5 * T25) * T37) * T71
					+ (T24 * T101 + (-2 * T9 * T58 * T5 * T60) + T102 * T29)
							* T73
					+ ((-2 * T9 * T20 * T101)
							+ (2 * T9 * T58 * T25 + 2 * T20 * T58 * T5) * T60
							+ (-2 * T102 * T5 * T25)) * T37 * T33
					+ (T43 * T101 + (-2 * T20 * T58 * T25 * T60) + T102 * T39)
							* T61);

	return sqrt(R22);
}

