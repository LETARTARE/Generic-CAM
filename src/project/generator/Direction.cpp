///////////////////////////////////////////////////////////////////////////////
// Name               : Direction.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.12.2017
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Direction.h"

#include <float.h>
//#include <cmath>

Direction::Direction()
{
	direction = 0;
	X = 0;
	Y = 0;
	resolutionX = 1.0;
	resolutionY = 1.0;
	offsetX = 0.0;
	offsetY = 0.0;
}

Direction::~Direction()
{
}

void Direction::TurnLeft()
{
	direction = (direction + 1) % 8;
}

void Direction::Reverse()
{
	direction = (direction + 4) % 8;
}

void Direction::TurnRight()
{
	direction = (direction + 7) % 8;
}

void Direction::Move()
{
	switch(direction){
	case 0:
		X++;
		break;
	case 1:
		X++;
		Y++;
		break;
	case 2:
		Y++;
		break;
	case 3:
		X--;
		Y++;
		break;
	case 4:
		X--;
		break;
	case 5:
		X--;
		Y--;
		break;
	case 6:
		Y--;
		break;
	case 7:
		X++;
		Y--;
		break;
	}
}

double Direction::Xfl(void) const
{
	return (double) X * resolutionX + offsetX;
}

double Direction::Yfl(void) const
{
	return (double) Y * resolutionY + offsetY;
}

int Direction::OnKey(void) const
{
	switch(direction){
	case 0:
		return 6;
	case 1:
		return 9;
	case 2:
		return 8;
	case 3:
		return 7;
	case 4:
		return 4;
	case 5:
		return 1;
	case 6:
		return 2;
	case 7:
		return 3;
	}
	return 0;
}

void Direction::SetResolution(double rx, double ry)
{
	resolutionX = rx;
	if(ry < 0)
		resolutionY = rx;
	else
		resolutionY = ry;
}

Direction& Direction::operator =(const Vector3& other)
{
	if(other.x < 0){
		if(other.y < 0){
			if(other.x < other.y)
				direction = 4;
			else
				direction = 6;
		}else{
			if(-other.x > other.y)
				direction = 4;
			else
				direction = 2;
		}
	}else{
		if(other.y < 0){
			if(other.x > -other.y)
				direction = 0;
			else
				direction = 6;
		}else{
			if(other.x > other.y)
				direction = 0;
			else
				direction = 2;
		}
	}
	return *this;
}

Direction& Direction::operator =(const int& other)
{
	if(other < 0)
		this->direction = (8 - ((-other) % 8)) % 8;
	else
		this->direction = other % 8;
	return *this;
}

Direction& Direction::operator ++()
{
	direction = (direction + 1) % 8;
	return *this;
}

Direction Direction::operator ++(int dummy)
{
	Direction tmp(*this);
	direction = (direction + 1) % 8;
	return tmp;
}

Direction& Direction::operator --()
{
	direction = (direction + 7) % 8;
	return *this;
}

Direction Direction::operator --(int int1)
{
	Direction tmp(*this);
	direction = (direction + 7) % 8;
	return tmp;
}

Vector3 Direction::GetNormal(void) const
{
	switch(direction){
	case 0:
		return Vector3(1, 0, 0);
	case 1:
		return Vector3(M_SQRT1_2, M_SQRT1_2, 0);
	case 2:
		return Vector3(0, 1, 0);
	case 3:
		return Vector3(-M_SQRT1_2, M_SQRT1_2, 0);
	case 4:
		return Vector3(-1, 0, 0);
	case 5:
		return Vector3(-M_SQRT1_2, -M_SQRT1_2, 0);
	case 6:
		return Vector3(0, -1, 0);
	case 7:
		return Vector3(M_SQRT1_2, -M_SQRT1_2, 0);
	}
	return Vector3();
}

bool Direction::operator ==(const Direction& b) const
{
	if(this->X != b.X) return false;
	if(this->Y != b.Y) return false;
	if(fabs(this->offsetX - b.offsetX) > FLT_EPSILON) return false;
	if(fabs(this->offsetY - b.offsetY) > FLT_EPSILON) return false;
	if(fabs(this->resolutionX - b.resolutionX) > FLT_EPSILON) return false;
	if(fabs(this->resolutionY - b.resolutionY) > FLT_EPSILON) return false;
	if(this->direction != b.direction) return false;
	return true;
}

Vector3 Direction::GetPosition(void) const
{
	return Vector3((double) X * resolutionX + offsetX,
			(double) Y * resolutionY + offsetY, 0);
}
