///////////////////////////////////////////////////////////////////////////////
// Name               : Generic PostProcessor.h
// Purpose            : Minimal Postprocessor
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_PROJECT_POST_GENERICPOSTPROCESSOR_H_
#define SRC_PROJECT_POST_GENERICPOSTPROCESSOR_H_

#include "PostProcessor.h"

class GenericPostProcessor:public PostProcessor {
public:
	class Axis {
	public:
		Axis();
		void Set(const Vector3 &position, Vector3 &normal);
		friend std::ostream& operator<<(std::ostream &out, const Axis &axis);
		std::string name;
		bool negativ;
		enum Direction{
			X = 0, Y = 1, Z = 2
		} ref;
		bool rotational;
		double factorLength;
		double factorAngle;
		double value;
		double oldValue;
	};

	GenericPostProcessor(const std::string name);
	virtual ~GenericPostProcessor();

	virtual std::map <std::string, std::string> GetParameter(void) const;
	virtual bool SetParameter(std::string name, std::string value);
	void Update(void);
	virtual bool SaveGCode(std::string filename);

public:
	std::vector <Axis> axis;

	std::string preblock;
	std::string postblock;
	std::string configuration;
};

#endif /* SRC_PROJECT_POST_GENERICPOSTPROCESSOR_H_ */
