///////////////////////////////////////////////////////////////////////////////
// Name               : MachinePosition.cpp
// Purpose            : The position of the machine.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CNCPosition.h"

#include <math.h>

CNCPosition::CNCPosition(double x, double y, double z, double nx, double ny,
		double nz)
{
	position.Set(x, y, z);
	normal.Set(nx, ny, nz);
	toolSlot = -1;
	S = 0;
	F = 0;
	rapid = false;
	circle = false;
	t = 0.0;
	dt = 0.0;
}

CNCPosition::CNCPosition(const Vector3& position, const Vector3& normal)
{
	this->position = position;
	this->normal = normal;
	toolSlot = -1;
	S = 0;
	F = 0;
	rapid = false;
	circle = false;
	t = 0.0;
	dt = 0.0;
}

CNCPosition::CNCPosition(const AffineTransformMatrix& matrix)
{
	position = matrix.GetOrigin();
	normal = matrix.GetEz();
	toolSlot = -1;
	S = 0;
	F = 0;
	rapid = false;
	circle = false;
	t = 0.0;
	dt = 0.0;
}

CNCPosition::~CNCPosition()
{
}

CNCPosition& CNCPosition::operator+=(const Vector3& a)
{
	position += a;
	return *this;
}

CNCPosition& CNCPosition::operator-=(const Vector3& a)
{
	position -= a;
	return *this;
}

double CNCPosition::Abs(const CNCPosition& b) const
{
	return (position - b.position).Abs();
}

double CNCPosition::Rotation(const CNCPosition& b) const
{
	return asin(normal.Dot(b.normal));
}

void CNCPosition::Set(double x, double y, double z, bool rapid)
{
	position.Set(x, y, z);
	this->rapid = rapid;
}

void CNCPosition::Rapid(void)
{
	rapid = true;
}

void CNCPosition::FeedSpeed(void)
{
	rapid = false;
}

AffineTransformMatrix CNCPosition::GetMatrix(void) const
{
	AffineTransformMatrix temp;
	temp.SetOrigin(position);
	temp.SetEz(normal);
	temp.SetEx(Vector3(1, 0, 0));
	temp.CalculateEy();
	if(temp.GetEy().Abs2() < 1e-6){
		temp.SetEy(Vector3(0, 1, 0));
		temp.CalculateEx();
	}
	temp.Normalize();
	return temp;
}

