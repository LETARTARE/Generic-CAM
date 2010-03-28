///////////////////////////////////////////////////////////////////////////////
// Name:        AffineTransformMatrix.cpp
// Purpose:     class to store a 3D affine transform matrix and provide operations upon.
// Author:      Tobias Schaefer
// Modified by:
// Created:     22.07.2009
// RCS-ID:
// Copyright:   (c) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence:     GNU General Public License version 3.0 (GPLv3)
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

void AffineTransformMatrix::Set(const AffineTransformMatrix &matrix)
{
	unsigned char i;
	for(i = 0; i < 16; i++)
		a[i] = matrix.a[i];
	TakeMatrixApart();
}

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

wxString AffineTransformMatrix::ToString()
{
	TakeMatrixApart();
	wxString temp;
	temp += wxString::Format(_T("%f\n%f\n%f\n"), tx, ty, tz);
	temp += wxString::Format(_T("%f\n%f\n%f\n"), rx, ry, rz);
	temp += wxString::Format(_T("%f\n%f\n%f\n"), sx, sy, sz);
	return temp;
}
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

AffineTransformMatrix AffineTransformMatrix::Inverse() const
{
	//)set fortran optlevel 2
	//)set output fortran on
	//R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	//inverse(R)

	double T11 = (a[0] * a[5] + (-a[1] * a[4])) * a[10] + ((-a[0] * a[6])
			+ a[2] * a[4]) * a[9] + (a[1] * a[6] + (-a[2] * a[5])) * a[8];

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

AffineTransformMatrix AffineTransformMatrix::operator*(
		const AffineTransformMatrix& b) const
{
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

AffineTransformMatrix AffineTransformMatrix::operator/(
		const AffineTransformMatrix& b) const
{
	return *(this) * (b.Inverse());
}

//void AffineTransformMatrix::PreMult(const double *b)
//{
//	int i, j, k, pa, pb, pc;
//	double c[16];
//	for(i = 0; i < 4; i++)
//		for(j = 0; j < 4; j++){
//			pc = i + j * 4; // position in the result
//			c[pc] = 0.0f;
//			for(k = 0; k < 4; k++){
//				pa = k + j * 4;
//				pb = i + k * 4;
//				c[pc] += b[pb] * a[pa];
//			}
//		}
//	for(i = 0; i < 16; i++)
//		a[i] = c[i];
//
//}
//
//void AffineTransformMatrix::PostMult(const double *b)
//{
//	int i, j, k, pa, pb, pc;
//	double c[16];
//	for(i = 0; i < 4; i++)
//		for(j = 0; j < 4; j++){
//			pc = i + j * 4;
//			c[pc] = 0.0f;
//			for(k = 0; k < 4; k++){
//				pa = i + k * 4;
//				pb = k + j * 4;
//				c[pc] += a[pa] * b[pb];
//			}
//		}
//	for(i = 0; i < 16; i++)
//		a[i] = c[i];
//}


AffineTransformMatrix AffineTransformMatrix::Identity()
{
	AffineTransformMatrix a;
	return a;
}

void AffineTransformMatrix::TranslateGlobal(double x, double y, double z)
{
	a[12] += x;
	a[13] += y;
	a[14] += z;
}

void AffineTransformMatrix::TranslateLocal(double x, double y, double z)
{
	a[12] += x * a[0] + y * a[4] + z * a[8];
	a[13] += x * a[1] + y * a[5] + z * a[9];
	a[14] += x * a[2] + y * a[6] + z * a[10];
}

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

AffineTransformMatrix AffineTransformMatrix::RotateInterwoven(double x,
		double y, double z)
{
	double alpha = sqrt(x * x + y * y + z * z);
	if(alpha == 0) return AffineTransformMatrix::Identity();
	Vector3 R;
	R.Set(x / alpha, y / alpha, z / alpha);
	return AffineTransformMatrix::RotateAroundVector(R, alpha);
}

// RotateTrackball(x1,y1,x2,y2,r)
// r1= (0,0,r )-(x1,y1,0)
// r2= (0,0,r )-(x2,y2,0)
// P1 = SphereIntersect(r1,C,r);
// P2 = SphereIntersect(r2,C,r);
// V1 = (P1-C)
// V2 = (P2-C)
// V1.Normalize();
// V2.Normlize();
// A = V1xV2;
// alpha = arcsin(abs(A));
// if(V1*V2 <0)alpha+=M_PI/2;
//RotateAroundVector(A,alpha);


