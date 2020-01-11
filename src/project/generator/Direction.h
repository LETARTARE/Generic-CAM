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

#ifndef DIRECTION_H_
#define DIRECTION_H_

/*!\class Direction
 * \brief Stores a direction and provides manipulation thereon
 *
 *
 */

#include "../../3D/Vector3.h"
#include <stdint.h>

class Direction {
public:
	Direction();
	virtual ~Direction();
	int X;
	int Y;
	double offsetX;
	double offsetY;
	double resolutionX;
	double resolutionY;
	int_fast8_t direction;

//	Direction& operator =(const Direction &other);
	Direction& operator =(const Vector3 &other);
	Direction& operator =(const int &other);
	Direction& operator++();
	Direction operator++(int);
	Direction& operator--();
	Direction operator--(int);

	bool operator==(const Direction &b) const;
	bool operator!=(const Direction &b) const
	{
		return !(*this == b);
	}

	void SetResolution(double rx, double ry = -1);

	void TurnRight();
	void TurnLeft();
	void Reverse();
	void Move();

	double Xfl(void) const;
	double Yfl(void) const;

	int OnKey(void) const;
	Vector3 GetNormal(void) const;
	Vector3 GetPosition(void) const;
};

#endif /* DIRECTION_H_ */
