///////////////////////////////////////////////////////////////////////////////
// Name               : AffineTransformMatrix.cpp
// Purpose            : A class to store a 3D affine transform matrix and provide operations upon.
// Thread Safe        : Yes
// Platform dependend : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 22.07.2009
//$LastChangedDate    : $
//$Revision           : $
//$LastChangedBy      : $
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
///////////////////////////////////////////////////////////////////////////////


#include "AffineTransformMatrix.h"

#include <cmath>
#include <wx/tokenzr.h>
#include <wx/string.h>

AffineTransformMatrix::AffineTransformMatrix()
{
	SetIdentity();
	linkScaling = true;
}

AffineTransformMatrix::~AffineTransformMatrix()
{
}

/*! Copies a matrix by inserting a given matrix into \a a.
 *  \param matrix The matrix to copy.
 */
void AffineTransformMatrix::Set(const AffineTransformMatrix &matrix)
{
	unsigned char i;
	for(i = 0; i < 16; i++)
		a[i] = matrix.a[i];
	TakeMatrixApart();
}

//! Resets the matrix to the identity matrix.
void AffineTransformMatrix::SetIdentity()
{
	rx = ry = rz = 0.0;
	tx = ty = tz = 0.0;
	sx = sy = sz = 1.0;
	unsigned char i;
	for(i = 0; i < 16; i++)
		a[i] = 0;
	a[0] = 1.0;
	a[5] = 1.0;
	a[10] = 1.0;
	a[15] = 1.0;
}

//! Generate a string containing the matrix.
wxString AffineTransformMatrix::ToString()
{
	TakeMatrixApart();
	wxString temp;
	temp += wxString::Format(_T("%f\n%f\n%f\n"), tx, ty, tz);
	temp += wxString::Format(_T("%f\n%f\n%f\n"), rx, ry, rz);
	temp += wxString::Format(_T("%f\n%f\n%f\n"), sx, sy, sz);
	return temp;
}

//! Setup the matrix from a string.
void AffineTransformMatrix::FromString(wxString string)
{
	wxStringTokenizer tkz(string, wxT("\n"));
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

	if(sx > 0.0){
		b[0] = a[0] / sx;
		b[1] = a[1] / sx;
		b[2] = a[2] / sx;
	}else{
		b[0] = 0.0;
		b[1] = 0.0;
		b[2] = 0.0;
	}
	if(sy > 0.0){
		b[4] = a[4] / sy;
		b[5] = a[5] / sy;
		b[6] = a[6] / sy;
	}else{
		b[4] = 0.0;
		b[5] = 0.0;
		b[6] = 0.0;
	}
	if(sz > 0.0){
		b[8] = a[8] / sz;
		b[9] = a[9] / sz;
		b[10] = a[10] / sz;
	}else{
		b[8] = 0.0;
		b[9] = 0.0;
		b[10] = 0.0;
	}

	if(b[0] != 0.0 || b[1] != 0.0){
		rz = atan2(b[1], b[0]);
	}else{
		rz = 0.0;
	}
	double coz = cos(rz);
	double siz = sin(rz);

	if(b[0] != 0.0 || b[1] != 0.0 || b[2] != 0.0){
		ry = atan2(-b[2], sqrt(b[0] * b[0] + b[1] * b[1]));
	}else{
		ry = 0.0;
	}
	double coy = cos(ry);
	double siy = sin(ry);

	b[0] = b[5] * coy * siz - b[6] * siy + b[4] * coy * coz;
	b[1] = -b[4] * siz + b[5] * coz;
	b[2] = b[5] * siy * siz + b[4] * coz * siy + b[6] * coy;

	if(b[1] != 0.0 || b[2] != 0.0){
		rx = atan2(b[2], b[1]);
	}else{
		rx = 0.0;
	}
}

//! Calculate the matrix from rx,ry,rz,tx,ty,tz and sx,sy,sz.
void AffineTransformMatrix::PutMatrixTogether(void)
{
	double cox = cos(rx);
	double six = sin(rx);
	double coy = cos(ry);
	double siy = sin(ry);
	double coz = cos(rz);
	double siz = sin(rz);

	// Matrix calculated with Axiom:

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
AffineTransformMatrix AffineTransformMatrix::Inverse() const
{
	// Code generated with axiom:
	//)set fortran optlevel 2
	//)set output fortran on
	//R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	//inverse(R)

	double T11 = (a[0] * a[5] + (-a[1] * a[4])) * a[10] + ((-a[0] * a[6])
			+ a[2] * a[4]) * a[9] + (a[1] * a[6] + (-a[2] * a[5])) * a[8];
	// T11 is the determinant of the matrix. This should
	// not be zero for a correct transformation matrix.
	wxASSERT(T11!=0)

	double T12 = a[4] * a[9];
	double T13 = a[5] * a[8];
	double T14 = a[4] * a[10];
	double T15 = a[6] * a[8];
	double T16 = a[5] * a[10];
	double T17 = a[6] * a[9];
	double T18 = a[0] * a[9];
	double T19 = a[1] * a[8];
	double T21 = a[0] * a[10];
	double T22 = a[2] * a[8];
	double T24 = a[1] * a[10];
	double T25 = a[2] * a[9];
	double T27 = a[1] * a[6] + (-a[2] * a[5]);
	double T28 = (-a[0] * a[6]) + a[2] * a[4];
	double T29 = a[0] * a[5] + (-a[1] * a[4]);
	double T30 = a[0] * a[5];
	double T31 = a[1] * a[4];
	double T32 = a[0] * a[6];
	double T33 = a[2] * a[4];
	double T34 = a[1] * a[6];
	double T35 = a[2] * a[5];

	AffineTransformMatrix b;

	b.a[0] = (T16 - T17) / T11;
	b.a[4] = (-T14 + T15) / T11;
	b.a[8] = (T12 - T13) / T11;
	b.a[12] = ((-T12 + T13) * a[14] + (T14 - T15) * a[13] + (-T16 + T17)
			* a[12]) / T11;
	b.a[1] = (-T24 + T25) / T11;
	b.a[5] = (T21 - T22) / T11;
	b.a[9] = (-T18 + T19) / T11;
	b.a[13] = ((T18 - T19) * a[14] + (-T21 + T22) * a[13] + (-T25 + T24)
			* a[12]) / T11;
	b.a[2] = T27 / T11;
	b.a[6] = T28 / T11;
	b.a[10] = T29 / T11;
	b.a[14] = ((-T30 + T31) * a[14] + (T32 - T33) * a[13] + (-T34 + T35)
			* a[12]) / T11;
	b.a[2] = 0;
	b.a[6] = 0;
	b.a[11] = 0;
	b.a[15] = 1;
	return b;
}

//! Overloaded operator to allow correct multiplication of two matrices.
AffineTransformMatrix AffineTransformMatrix::operator*(
		const AffineTransformMatrix& b) const
{
	//Generated with this code:
	//php -r'for($i=0;$i<4;$i++){for($j=0;$j<4;$j++){printf("c.a[%u]=",$i*4+$j);for($k=0;$k<4;$k++){printf("a[%u]*b.a[%u]%s",$k*4+$j,$i*4+$k,($k==3)?";\r\n":"+");}}}'

	AffineTransformMatrix c;
	c.a[0] = a[0] * b.a[0] + a[4] * b.a[1] + a[8] * b.a[2];
	c.a[1] = a[1] * b.a[0] + a[5] * b.a[1] + a[9] * b.a[2];
	c.a[2] = a[2] * b.a[0] + a[6] * b.a[1] + a[10] * b.a[2];
	c.a[3] = 0;
	c.a[4] = a[0] * b.a[4] + a[4] * b.a[5] + a[8] * b.a[6];
	c.a[5] = a[1] * b.a[4] + a[5] * b.a[5] + a[9] * b.a[6];
	c.a[6] = a[2] * b.a[4] + a[6] * b.a[5] + a[10] * b.a[6];
	c.a[7] = 0;
	c.a[8] = a[0] * b.a[8] + a[4] * b.a[9] + a[8] * b.a[10];
	c.a[9] = a[1] * b.a[8] + a[5] * b.a[9] + a[9] * b.a[10];
	c.a[10] = a[2] * b.a[8] + a[6] * b.a[9] + a[10] * b.a[10];
	c.a[11] = 0;
	c.a[12] = a[0] * b.a[12] + a[4] * b.a[13] + a[8] * b.a[14] + a[12];
	c.a[13] = a[1] * b.a[12] + a[5] * b.a[13] + a[9] * b.a[14] + a[13];
	c.a[14] = a[2] * b.a[12] + a[6] * b.a[13] + a[10] * b.a[14] + a[14];
	c.a[15] = 1;
	return c;
}

/*!\brief  Overloaded operator to allow correct division of two matrices.
 *
 * The division is done by inverting the second matrix and the multiplying both.
 */
AffineTransformMatrix AffineTransformMatrix::operator/(
		const AffineTransformMatrix& b) const
{
	return *(this) * (b.Inverse());
}

//! Apply the transformation matrix on a given vector.
Vector3 AffineTransformMatrix::Transform(const Vector3& v) const
{
	//R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	//R*matrix([[x],[y],[z],[1]])

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12];
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13];
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14];
	return temp;
}

//! Function returning an identity matrix.
AffineTransformMatrix AffineTransformMatrix::Identity()
{
	AffineTransformMatrix a;
	return a;
}

//! Translate matrix in the global coordinate system.
void AffineTransformMatrix::TranslateGlobal(double x, double y, double z)
{
	a[12] += x;
	a[13] += y;
	a[14] += z;
}

//! Translate matrix in the local, rotated coordinate system.
void AffineTransformMatrix::TranslateLocal(double x, double y, double z)
{
	a[12] += x * a[0] + y * a[4] + z * a[8];
	a[13] += x * a[1] + y * a[5] + z * a[9];
	a[14] += x * a[2] + y * a[6] + z * a[10];
}

/*! Rotation around a given vector.
 *
 * Generates a rotation matrix around a given vector.
 * \param vector Axis of rotation.
 * \param phi Angle of rotation.
 * \return Rotation matrix.
 */
AffineTransformMatrix AffineTransformMatrix::RotateAroundVector(Vector3 vector,
		double phi)
{
	double c = cos(phi);
	double s = sin(phi);
	double t = 1 - c;

	vector.Normalize();

	AffineTransformMatrix a;

	a.a[0] = t * vector.x * vector.x + c;
	a.a[1] = t * vector.x * vector.y + s * vector.z;
	a.a[2] = t * vector.x * vector.z - s * vector.y;

	a.a[4] = t * vector.x * vector.y - s * vector.z;
	a.a[5] = t * vector.y * vector.y + c;
	a.a[6] = t * vector.y * vector.z + s * vector.x;

	a.a[8] = t * vector.x * vector.z + s * vector.y;
	a.a[9] = t * vector.y * vector.z - s * vector.x;
	a.a[10] = t * vector.z * vector.z + c;

	return a;
}

/*! Rotation by mouse.
 *
 * This function is only a drop in until the RotateByTrackball function works.
 *
 * \param x Movement of mouse in x direction (=xnew-xold).
 * \param y Movement of mouse in y direction (=ynew-yold).
 * \param scale Scaling of the movement.
 * \return Rotation matrix.
 */
AffineTransformMatrix AffineTransformMatrix::RotateXY(int x, int y,
		double scale)
{

	double dx = (double) x / scale;
	double dy = (double) y / scale;

	double dist = sqrt(dx * dx + dy * dy);

	AffineTransformMatrix a;

	if(dist > 0.001){
		double ang = -atan2(dy, dx);

		double coy = cos(dist / 100);
		double siy = sin(dist / 100);
		double coz = cos(ang);
		double siz = sin(ang);

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
AffineTransformMatrix AffineTransformMatrix::RotateXYZ(double x, double y,
		double z)
{
	AffineTransformMatrix a;

	// Rx := matrix[[1,0,0,0],[0,cox,-six,0],[0,six,cox,0],[0,0,0,1]]
	// Ry := matrix[[coy,0,siy,0],[0,1,0,0],[-siy,0,coy,0],[0,0,0,1]]
	// Rz := matrix[[coz,-siz,0,0],[siz,coz,0,0],[0,0,1,0],[0,0,0,1]]
	// Rz*Ry*Rx

	double six = sin(x);
	double siy = sin(y);
	double siz = sin(z);
	double cox = cos(x);
	double coy = cos(y);
	double coz = cos(z);

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

/*! An interwoven rotation.
 *
 * Generates a rotation matrix around x,y,z.
 * In this case the rotations are interwoven:
 *
 * Every rotation (around x, around y and around z) is done
 * in infinitesimal small steps. On step around x, one step around y, ...
 *
 * This results in a rotation as expected from a 6 DOF controller.
 */
AffineTransformMatrix AffineTransformMatrix::RotateInterwoven(double x,
		double y, double z)
{
	double alpha = sqrt(x * x + y * y + z * z);
	if(alpha == 0) return AffineTransformMatrix::Identity();
	Vector3 R;
	R.Set(x / alpha, y / alpha, z / alpha);
	return AffineTransformMatrix::RotateAroundVector(R, alpha);
}

//TODO: Program this: RotateTrackball(x1,y1,x2,y2,r)
// r1= (0,0,r )-(x1,y1,0)
// r2= (0,0,r )-(x2,y2,0)
// P1 = SphereIntersect(r1,C,r);
// P2 = SphereIntersect(r2,C,r);
// V1 = (P1-C)
// V2 = (P2-C)
// V1.Normalize();
// V2.Normalize();
// A = V1xV2;
// alpha = arcsin(abs(A));
// if(V1*V2 <0)alpha+=M_PI/2;
// return RotateAroundVector(A,alpha);


