///////////////////////////////////////////////////////////////////////////////
// Name               : Vector3.cpp
// Purpose            : A 3D vector class with support functions.
// Thread Safe        : Yes
// Platform dependend : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 28.01.2010
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "Vector3.h"

Vector3::~Vector3(void)
{
}

float Vector3::Abs(void)
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::Zero(void)
{
	x = y = z = 0.0;
}

Vector3 Vector3::Normalize(void)
{
	float d = Abs();
	if(d > 0){
		x /= d;
		y /= d;
		z /= d;
	}
	return Vector3(x, y, z);
}
