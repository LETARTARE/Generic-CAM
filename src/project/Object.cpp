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

#include "../3D/FileSTL.h"
#include "../3D/FileDXF.h"
#include "../3D/FileGTS.h"

#include <wx/string.h>
#include <wx/log.h>
#include <GL/gl.h>

#include "../Config.h"

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfObject)

Object::Object()
{
	show = true;
	selected = false;
//	modified = false;
}

Object::~Object()
{
}

bool Object::IsEmpty(void) const
{
	return (geometries.GetCount() == 0);
}

void Object::Paint(const bool absolutCoordinates) const
{
	if(!show) return;
	glPushMatrix();
	if(absolutCoordinates){
		glMultMatrixd(displayTransform.a);
#ifdef _DEBUGMODE
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex3i(0, 0, 0);
		glEnd();
#endif
	}
	glMultMatrixd(matrix.a);
	for(size_t i = 0; i < geometries.GetCount(); i++)
		geometries[i].Paint();
	glPopMatrix();
}

void Object::Update(void)
{
	bbox.Clear();
	for(size_t i = 0; i < geometries.GetCount(); i++)
		bbox.Insert((geometries[i]), displayTransform * matrix);
	displayTransform.TranslateGlobal(bbox.xmin, bbox.ymin, bbox.zmin);
	matrix.TranslateGlobal(-bbox.xmin, -bbox.ymin, -bbox.zmin);
	bbox.xmax -= bbox.xmin;
	bbox.ymax -= bbox.ymin;
	bbox.zmax -= bbox.zmin;
	bbox.xmin = 0;
	bbox.ymin = 0;
	bbox.zmin = 0;
}

void Object::UpdateNormals(void)
{
	for(size_t i = 0; i < geometries.GetCount(); i++)
		geometries[i].CalculateNormals();
}

void Object::TransformFromCenter(void)
{
	const double dx = bbox.xmin + bbox.GetSizeX() / 2;
	const double dy = bbox.ymin + bbox.GetSizeY() / 2;
	const double dz = bbox.zmin + bbox.GetSizeZ() / 2;
	displayTransform.TranslateGlobal(dx, dy, dz);
	matrix.TranslateGlobal(-dx, -dy, -dz);
	bbox.xmin -= dx;
	bbox.ymin -= dy;
	bbox.zmin -= dz;
	bbox.xmax -= dx;
	bbox.ymax -= dy;
	bbox.zmax -= dz;
}

void Object::FlipNormals(void)
{
	for(size_t i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipNormals();
}
void Object::FlipX(void)
{
	for(size_t i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipX();
}
void Object::FlipY(void)
{
	for(size_t i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipY();
}
void Object::FlipZ(void)
{
	for(size_t i = 0; i < geometries.GetCount(); i++)
		geometries[i].FlipZ();
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

	if(!fileName.IsOk()) return false;

	// Process a GTS-file:
	if(fileName.GetExt().CmpNoCase(_T("gts")) == 0){
		FileGTS temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage(_("GTS file not readable!"));
			return false;
		}else{
			geometries.Clear();
			for(size_t i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				Geometry g;
				g.InsertTrianglesFrom(temp.geometry[i]);
				g.name = fileName.GetName();
				geometries.Add(g);
			}
		}
		Update();
		UpdateNormals();
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
			for(size_t i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				Geometry g;
				g.InsertTrianglesFrom(temp.geometry[i]);
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
		Update();
		UpdateNormals();
		return true;
	}

	// Process a DXF-file:
	if(fileName.GetExt().CmpNoCase(_T("dxf")) == 0){
		FileDXF temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage(_("DXF file not readable!"));
		}else{
			geometries.Clear();
			for(size_t i = 0; i < temp.geometry.GetCount(); i++){
				temp.geometry[i].ApplyTransformation();
				Geometry g;
				g.InsertTrianglesFrom(temp.geometry[i]);
				g.name = temp.geometry[i].name;
				geometries.Add(g);
			}
		}
		Update();
		UpdateNormals();
		return true;
	}
	return false;
}

void Object::ToStream(wxTextOutputStream& stream, size_t n)
{
	stream << _T("Name:") << endl;
	stream << name << endl;
	stream << _T("Matrix: ");
	matrix.ToStream(stream);
	stream << endl;
	stream << _T("DisplayMatrix: ");
	displayTransform.ToStream(stream);
	stream << endl;
	stream << _T("Show: ");
	stream << ((show)? 1 : 0);
	stream << endl;
	stream << _T("Geometries: ");
	stream << wxString::Format(_T("%u"), geometries.GetCount());
	stream << endl;
	for(size_t m = 0; m < geometries.GetCount(); m++){
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
	if(temp.Cmp(_T("DisplayMatrix:")) != 0) return false;
	displayTransform.FromStream(stream);
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Show:")) != 0) return false;
	show = (stream.Read8() == 1);
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Geometries:")) != 0) return false;
	const size_t N = stream.Read32();
	Geometry geometry;
	geometries.Clear();
	for(size_t n = 0; n < N; n++){
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
