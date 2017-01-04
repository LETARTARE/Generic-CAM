///////////////////////////////////////////////////////////////////////////////
// Name               : StockFile.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
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

#include "StockFile.h"

StockFile::StockFile()
{
	StockMaterial default1;
	default1.sx = 0.3;
	default1.sy = 0.2;
	default1.sz = 0.05;
	default1.name = _("Small board");
	stockMaterials.Add(default1);

	StockMaterial default2;
	default2.sx = 3 * 12 * 25.4e-3;
	default2.sy = 4 * 25.4e-3;
	default2.sz = 4 * 25.4e-3;
	default2.name = _("4\" by 4\", 3 feet long");
	stockMaterials.Add(default2);

	StockMaterial default3;
	default3.sx = 0.1;
	default3.sy = 0.1;
	default3.sz = 0.1;
	default3.name = _("Cube 10cm x 10cm x 10cm");
	stockMaterials.Add(default3);

	StockMaterial default4;
	default4.sx = 0.626 - 0.063;
	default4.sy = 0.435 - 0.008 - 0.020;
	default4.sz = 0.0145;
	default4.name = _("MFD board on left stack in my workshop");
	stockMaterials.Add(default4);

	StockMaterial default5;
	default5.sx = 0.700;
	default5.sy = 0.390;
	default5.sz = 0.027;
	default5.available = true;
	default5.name = _("MDF Board 70 x 46 x 2.7 cm");
	stockMaterials.Add(default5);
}

StockFile::~StockFile()
{
}

bool StockFile::LoadFromFile(wxString filename)
{
	return false;
}

bool StockFile::WriteToFile(wxString filename)
{
	return false;
}
