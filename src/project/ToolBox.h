///////////////////////////////////////////////////////////////////////////////
// Name               : ToolBox.h
// Purpose            : Holds a collection of tools.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.03.2010
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

#ifndef TOOLBOX_H_
#define TOOLBOX_H_

/*!\class ToolBox
 * \ingroup document
 * \brief Collection of tools
 *
 * A collection of available tools for the machine.
 */

#include <stddef.h>
#include <string>
#include <vector>

#include "Tool.h"

class JSON;

class ToolBox {
	//Constructor / Destructor
public:
	ToolBox();
	virtual ~ToolBox();

	//Member variables
public:
	std::string filename;
	std::string version;

	std::vector <Tool> tools;
private:

	// Methods
public:
	std::string GetName(void) const;
	bool IsLoaded(void) const;
	bool Load(void);
	bool Load(std::string filename);
//	void SaveJSON(std::string filename) const;

//	friend std::istream& operator>>(std::istream &in, ToolBox &hull);
//	friend std::ostream& operator<<(std::ostream &out, const ToolBox &hull);

	size_t Size(void) const;
	Tool & operator[](size_t index);
	const Tool & operator[](size_t index) const;

	//	size_t AddTool(Tool& newTool);
//	bool RemoveToolSlot(size_t slotNr);
//	bool RemoveToolIndex(size_t index);
//	bool IsSlotFilled(size_t slotNr) const;
//	Tool & Slot(size_t slotNr);
//	const Tool & Slot(size_t slotNr) const;

private:
	bool isLoaded;
	void LoadContour(Tool::Contour & contour, const JSON & json);
};

#endif /* TOOLBOX_H_ */
