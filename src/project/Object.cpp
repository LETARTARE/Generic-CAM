///////////////////////////////////////////////////////////////////////////////
// Name               : Object.cpp
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "Object.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfObject)

#include <wx/log.h>

#include "../3D/FileGTS.h"
#include "../3D/FileSTL.h"
#include "../3D/FileDXF.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Paint(void)
{
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].Paint();
}

void Object::UpdateBoundingBox(void)
{
	size_t i;
	bbox.Reset();
	for(i = 0; i < geometries.GetCount(); i++)
		bbox.Insert((geometries[i]));
}

bool Object::LoadObject(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	return ReloadObject();
}

bool Object::ReloadObject(void)
{
	Geometry g;
	size_t i;
	if(!fileName.IsOk()) return false;

	// Process a GTS-file:
	if(fileName.GetExt().CmpNoCase(_T("gts")) == 0){
		FileGTS temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage(_("GTS file not readable!"));
			return false;
		}else{
			geometries.Clear();
			for(i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				g.Clear();
				g.CopyFrom(temp.geometry[i]);
				g.objectName = fileName.GetName();
				geometries.Add(g);
			}
		}
		return true;
	}

	// Process a STL-file:
	if(fileName.GetExt().CmpNoCase(_T("stl")) == 0){
		FileSTL temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage(_("STL file not readable!"));
			return false;
		}else{
			geometries.Clear();
			for(i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				g.Clear();
				g.CopyFrom(temp.geometry[i]);
				g.CalculateNormals();
				g.objectName = fileName.GetName();
				geometries.Add(g);
			}
		}
		return true;
	}

	// Process a DXF-file:
	if(fileName.GetExt().CmpNoCase(_T("dxf")) == 0){
		FileDXF temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage(_("DXF file not readable!"));
		}else{
			geometries.Clear();
			for(i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				g.Clear();
				g.CopyFrom(temp.geometry[i]);
				g.objectName = temp.geometry[i].objectName;
				geometries.Add(g);
			}
		}
		return true;
	}

	return false;
}
