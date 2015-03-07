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
///////////////////////////////////////////////////////////////////////////////

#include "Object.h"

#include <wx/arrimpl.cpp>
#include <wx/string.h>
WX_DEFINE_OBJARRAY(ArrayOfObject)

#include <wx/log.h>
#include <GL/gl.h>

#include "../3D/FileGTS.h"
#include "../3D/FileSTL.h"
#include "../3D/FileDXF.h"

Object::Object()
{
	selected = false;
	modified = false;
}

Object::~Object()
{
}

void Object::Paint(void) const
{
	::glPushMatrix();
	::glMultMatrixd(matrix.a);
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].Paint();
	::glPopMatrix();
}

void Object::UpdateBoundingBox(void)
{
	size_t i;
	bbox.Clear();
	for(i = 0; i < geometries.GetCount(); i++)
		bbox.Insert((geometries[i]), this->matrix);
}

void Object::UpdateBoundingBox(AffineTransformMatrix const &matrix)
{
	size_t i;
	bbox.Clear();
	for(i = 0; i < geometries.GetCount(); i++)
		bbox.Insert((geometries[i]), matrix * this->matrix);
}

void Object::UpdateNormals(void)
{
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].CalculateNormals();
}

void Object::Update(void)
{
	UpdateBoundingBox();
	UpdateNormals();
}

bool Object::LoadObject(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	this->name = fileName.GetName();
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
				g.InsertTrianglesFrom(temp.geometry[i]);
				g.name = fileName.GetName();
				geometries.Add(g);
			}
		}
		UpdateBoundingBox();
		return true;
	}

	// Process a STL-file:
	if(fileName.GetExt().CmpNoCase(_T("stl")) == 0){
		FileSTL temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage(_("STL file not readable!"));
			wxLogMessage(temp.error);
			return false;
		}else{
			geometries.Clear();
			for(i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				g.Clear();
				g.InsertTrianglesFrom(temp.geometry[i]);
				//TODO: Remove the calculation of normals.
				g.CalculateNormals();
				if(g.name.IsEmpty()){
					g.name = fileName.GetName()
							+ wxString::Format(_T(" - %u"), i);
				}
				g.color.Set((float) rand() / (float) RAND_MAX,
						(float) rand() / (float) RAND_MAX,
						(float) rand() / (float) RAND_MAX);
				geometries.Add(g);
			}
			if(!temp.error.IsEmpty()) wxLogMessage(temp.error);
		}
		UpdateBoundingBox();
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
				g.InsertTrianglesFrom(temp.geometry[i]);
				g.name = temp.geometry[i].name;
				geometries.Add(g);
			}
		}
		UpdateBoundingBox();
		return true;
	}

	return false;
}

bool Object::IsEmpty(void) const
{
	return (geometries.GetCount() == 0);
}

void Object::FlipNormals(void)
{
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipNormals();
}
void Object::FlipX(void)
{
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipX();
}
void Object::FlipY(void)
{
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipY();
}
void Object::FlipZ(void)
{
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipZ();
}

void Object::ToStream(wxTextOutputStream& stream, int n)
{
	stream << _T("Name:") << endl;
	stream << name << endl;
	stream << _T("Matrix: ");
	matrix.ToStream(stream);
	stream << endl;
	stream << _T("Geometries: ");
	stream << wxString::Format(_T("%u"), geometries.GetCount());
	stream << endl;
	for(int m = 0; m < geometries.GetCount(); m++){
		stream << _T("Geometry: ");
		stream << wxString::Format(_T("%u"), m);
		stream << endl;
		stream << _T("Name:") << endl;
		stream << geometries[m].name << endl;
		stream << _T("Filename:") << endl;
		stream << wxString::Format(_T("object_%u_geometry_%u.stl"), n, m)
				<< endl;
		stream << _T("Matrix: ");
		geometries[m].matrix.ToStream(stream);
		stream << endl;
		stream << _T("Color: ");
		stream << geometries[m].color.x << _T(" ");
		stream << geometries[m].color.y << _T(" ");
		stream << geometries[m].color.z << endl;
	}
}

bool Object::FromStream(wxTextInputStream& stream)
{
	wxString temp;
	temp = stream.ReadLine();
	if(temp.Cmp(_T("Name:")) != 0) return false;
	name = stream.ReadLine();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Matrix:")) != 0) return false;
	matrix.FromStream(stream);
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Geometries:")) != 0) return false;
	size_t N = stream.Read32();
	size_t n;
	Geometry geometry;
	geometries.Clear();
	for(n = 0; n < N; n++){
		temp = stream.ReadWord();
		if(temp.Cmp(_T("Geometry:")) != 0) return false;
		if(n != stream.Read32()) return false;
		temp = stream.ReadLine();
		if(temp.Cmp(_T("Name:")) != 0) return false;
		geometry.name = stream.ReadLine();
		temp = stream.ReadLine();
		if(temp.Cmp(_T("Filename:")) != 0) return false;
		temp = stream.ReadLine();
		temp = stream.ReadWord();
		if(temp.Cmp(_T("Matrix:")) != 0) return false;
		geometry.matrix.FromStream(stream);
		temp = stream.ReadWord();
		if(temp.Cmp(_T("Color:")) != 0) return false;
		geometry.color.x = stream.ReadDouble();
		geometry.color.y = stream.ReadDouble();
		geometry.color.z = stream.ReadDouble();
		geometries.Add(geometry);
	}
	return true;
}
