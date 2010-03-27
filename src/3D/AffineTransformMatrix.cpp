/*
 * AffineTransformMatrix.cpp
 *
 *  Created on: 22.07.2009
 *      Author: Tobias Schaefer
 */

#include "AffineTransformMatrix.h"

#include <cmath>
#include <wx/tokenzr.h>
#include <wx/string.h>

AffineTransformMatrix::AffineTransformMatrix()
{
	Identity();
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

void AffineTransformMatrix::Identity()
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

void AffineTransformMatrix::RotateXY(int x, int y, double scale)
{

	double dx = (double) x / scale;
	double dy = (double) y / scale;

	double dist = sqrt(dx * dx + dy * dy);

	if(dist > 0.001){
		double ang = -atan2(dy, dx);

		double coy = cos(dist / 100);
		double siy = sin(dist / 100);
		double coz = cos(ang);
		double siz = sin(ang);

		double b[16];
		b[0] = coz * coz * coy + siz * siz;
		b[1] = coz * siz * coy - coz * siz;
		b[2] = -coz * siy;
		b[3] = 0.0;
		b[4] = siz * coz * coy - coz * siz;
		b[5] = siz * siz * coy + coz * coz;
		b[6] = -siz * siy;
		b[7] = 0.0;
		b[8] = coz * siy;
		b[9] = siz * siy;
		b[10] = coy;
		b[11] = 0.0;
		b[12] = 0.0;
		b[13] = 0.0;
		b[14] = 0.0;
		b[15] = 1.0;

		PreMult(b);
	}
}

void AffineTransformMatrix::RotateXYZ(double x, double y, double z)
{
	unsigned char i;
	double b[16];
	double s, c;

	for(i = 0; i < 16; i++)
		b[i] = 0.0f;
	b[0] = 1.0f;
	b[15] = 1.0f;
	s = sin(-x);
	c = cos(-x);
	b[5] = c;
	b[10] = c;
	b[6] = -s;
	b[9] = s;
	PostMult(b);

	for(i = 0; i < 16; i++)
		b[i] = 0.0f;
	b[5] = 1.0f;
	b[15] = 1.0f;
	s = sin(-y);
	c = cos(-y);
	b[0] = c;
	b[10] = c;
	b[8] = -s;
	b[2] = s;
	PostMult(b);

	for(i = 0; i < 16; i++)
		b[i] = 0.0f;
	b[10] = 1.0f;
	b[15] = 1.0f;
	s = sin(-z);
	c = cos(-z);
	b[0] = c;
	b[5] = c;
	b[1] = -s;
	b[4] = s;
	PostMult(b);
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

void AffineTransformMatrix::RotateAroundVector(Vector3 vector, double phi)
{
	double c = cos(phi);
	double s = sin(phi);
	double t = 1 - c;

	vector.Normalize();

	double b[16];
	b[0] = t * vector.x * vector.x + c;
	b[1] = t * vector.x * vector.y + s * vector.z;
	b[2] = t * vector.x * vector.z - s * vector.y;
	b[3] = 0.0;

	b[4] = t * vector.x * vector.y - s * vector.z;
	b[5] = t * vector.y * vector.y + c;
	b[6] = t * vector.y * vector.z + s * vector.x;
	b[7] = 0.0;

	b[8] = t * vector.x * vector.z + s * vector.y;
	b[9] = t * vector.y * vector.z - s * vector.x;
	b[10] = t * vector.z * vector.z + c;
	b[11] = 0.0;

	b[12] = 0.0;
	b[13] = 0.0;
	b[14] = 0.0;
	b[15] = 1.0;

	PreMult(b);
}

void AffineTransformMatrix::RotateInterwoven(double x, double y, double z)
{
	double alpha = sqrt(x * x + y * y + z * z);
	if(alpha == 0) return;
	Vector3 R;
	R.Set(x / alpha, y / alpha, z / alpha);
	RotateAroundVector(R, alpha);
}

void AffineTransformMatrix::PreMult(const double *b)
{
	int i, j, k, pa, pb, pc;
	double c[16];
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++){
			pc = i + j * 4; // position in the result
			c[pc] = 0.0f;
			for(k = 0; k < 4; k++){
				pa = k + j * 4;
				pb = i + k * 4;
				c[pc] += b[pb] * a[pa];
			}
		}
	for(i = 0; i < 16; i++)
		a[i] = c[i];
}

void AffineTransformMatrix::PostMult(const double *b)
{
	int i, j, k, pa, pb, pc;
	double c[16];
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++){
			pc = i + j * 4;
			c[pc] = 0.0f;
			for(k = 0; k < 4; k++){
				pa = i + k * 4;
				pb = k + j * 4;
				c[pc] += a[pa] * b[pb];
			}
		}
	for(i = 0; i < 16; i++)
		a[i] = c[i];
}

