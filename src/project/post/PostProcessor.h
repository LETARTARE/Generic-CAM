///////////////////////////////////////////////////////////////////////////////
// Name               : PostProcessor.h
// Purpose            : Abstract Base Postprocessor
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

#ifndef SRC_PROJECT_POST_POSTPROCESSOR_H_
#define SRC_PROJECT_POST_POSTPROCESSOR_H_

#include <map>
#include <string>
#include <vector>

#include "../../3D/AffineTransformMatrix.h"
#include "../generator/CNCPosition.h"

class PostProcessor {
public:
	PostProcessor(const std::string name);
	virtual ~PostProcessor();

	std::string GetName(void) const;
	virtual std::map <std::string, std::string> GetParameter(void) const = 0;
	virtual bool SetParameter(std::map <std::string, std::string> parameter);
	virtual bool SetParameter(std::string name, std::string value) = 0;

	virtual void SetToolPath(const std::vector <CNCPosition> * toolpath);
	virtual void SetCoordinateSystem(const AffineTransformMatrix &matrix);
	virtual bool SaveGCode(std::string filename) = 0;

protected:
	std::string name;
	AffineTransformMatrix matrix;
	const std::vector <CNCPosition> * toolpath;
};

#endif /* SRC_PROJECT_POST_POSTPROCESSOR_H_ */
