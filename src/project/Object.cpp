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

#include "../Config.h"
#include "../3D/FileSTL.h"
#include "../3D/FileDXF.h"
#include "../3D/FileGTS.h"
#include "../3D/OpenGLMaterial.h"

#include <wx/string.h>
#include <wx/log.h>

#include <algorithm>
#include <iostream>
#include <sstream>

#include "../3D/OpenGL.h"
#include "../math/JSON.h"

Object::Object(size_t ID) :
		ID(ID)
{
	show = true;
	selectable = true;
//	modified = false;
}

Object::~Object()
{
}

bool Object::operator ==(const size_t ID) const
{
	return (this->ID == ID);
}

size_t Object::GetID(void) const
{
	return ID;
}

bool Object::IsEmpty(void) const
{
	return geometry.IsEmpty();
}

void Object::Paint(const OpenGLMaterial &face, const OpenGLMaterial &edge,
		const Selection& sel) const
{
	if(!show) return;

//#ifdef _DEBUGMODE
//		if(geometries.GetCount() > 0){
//			glColor3f(geometries[0].color.x, geometries[0].color.y,
//					geometries[0].color.z);
//		}
	// Paint a little dot at the origin of the Object.
//		glPointSize(5);
//		glBegin(GL_POINTS);
//		glVertex3i(0, 0, 0);
//		glEnd();
//#endif

	const bool invert = sel.IsInverted();
	glPushMatrix();
	matrix.GLMultMatrix();
	face.UseMaterial();
	glPushName(Selection::TriangleGroup);
	if(sel.IsType(Selection::TriangleGroup)){
		geometry.PaintTriangles(sel.GetSet(), invert);
	}else{
		if(invert) geometry.PaintTriangles(std::set <size_t>(), true);
	}
	glPopName();

	if(OpenGLMaterial::ColorsAllowed()){
		edge.UseMaterial();
		glLineWidth(3);
		glPushMatrix();

		GLdouble modelview[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		modelview[14] = modelview[14] + 0.001; // Move edges a little bit towards the camera
		glLoadMatrixd(modelview);

		glPushName(Selection::EdgeGroup);
		if(sel.IsType(Selection::EdgeGroup)){
			geometry.PaintEdges(sel.GetSet(), invert);
		}else{
			if(invert) geometry.PaintEdges(std::set <size_t>(), true);
		}
		glPopName();

		glPopMatrix();
		glLineWidth(1);
	}
	glPopMatrix();
}

void Object::Update(void)
{
	bbox.Clear();

	const size_t N = geometry.GetVertexCount();
	for(size_t n = 0; n < N; ++n)
		bbox.Insert(geometry.GetVertex(n));
	bbox.Transform(geometry.matrix);
	bbox.Transform(matrix);
}

//void Object::UpdateNormals(void)
//{
//	geometry.CalculateNormals();
//}

void Object::PaintPick(void) const
{
	if(!show) return;
	glPushMatrix();
	matrix.GLMultMatrix();
	glPushName(Selection::TriangleGroup);
	geometry.PaintTriangles();
	glPopName();

	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	modelview[14] = modelview[14] + 0.001; // Move edges a little bit towards the camera
	glLoadMatrixd(modelview);

	glPushName(Selection::EdgeGroup);
	geometry.PaintEdges();
	glPopName();
	glPushName(Selection::VertexGroup);
	geometry.PaintVertices();
	glPopName();
	glPopMatrix();
}

void Object::FlipNormals(void)
{
	geometry.FlipNormals();
}
void Object::FlipX(void)
{
//	geometry.FlipX();
}
void Object::FlipY(void)
{
//	geometry.FlipY();
}
void Object::FlipZ(void)
{
//	geometry.FlipZ();
}

bool Object::LoadObject(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	this->name = fileName.GetName();
	return ReloadObject();
}

bool IsLess(Triangle a, Triangle b)
{
	return (a.p[0].x < b.p[0].x);
}

bool Object::ReloadObject(void)
{

	if(!fileName.IsOk()) return false;

// Process a GTS-file:
	if(fileName.GetExt().CmpNoCase(_T("gts")) == 0){
		FileGTS temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage
			(_("GTS file not readable!"));
			return false;
		}
		if(temp.geometry.Size() > 0){
			temp.geometry.ApplyTransformation();
			temp.geometry.matrix = AffineTransformMatrix();
			geometry.Clear();
			geometry.CopyFrom(temp.geometry);
			this->name = fileName.GetName();
			geometry.CalcNormals();
			geometry.CalcGroups();
			geometry.ApplyTransformation();
		}
		return true;
	}

// Process a STL-file:
	if(fileName.GetExt().CmpNoCase(_T("stl")) == 0){
		FileSTL temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage
			(_("STL file not readable!"));
			wxLogMessage
			(temp.error);
			return false;
		}
		AffineTransformMatrix scaledown;
		scaledown.ScaleGlobal(1, 1, 1);
		if(temp.geometry.Size() > 0){
			temp.geometry.ApplyTransformation();
			temp.geometry.ApplyTransformation(scaledown);
			temp.geometry.matrix = AffineTransformMatrix();
			std::sort(temp.geometry.triangles.begin(),
					temp.geometry.triangles.end(), IsLess);
			geometry.Clear();
			geometry.CopyFrom(temp.geometry);
			this->name = fileName.GetName();
			geometry.CalcNormals();
			geometry.CalcGroups();
//				geometry.color.Set(
//						(float) rand() / (float) RAND_MAX / 2.0 + 0.5,
//						(float) rand() / (float) RAND_MAX / 2.0 + 0.5,
//						(float) rand() / (float) RAND_MAX / 2.0 + 0.5);
		}
		if(!temp.error.IsEmpty()) wxLogMessage
		(temp.error);
//		geometry.paintNormals = true;
		return true;
	}

// Process a DXF-file:
	if(fileName.GetExt().CmpNoCase(_T("dxf")) == 0){
		FileDXF temp;
		if(!temp.ReadFile(fileName.GetFullPath())){
			wxLogMessage
			(_("DXF file not readable!"));
		}
		geometry.Clear();
		if(temp.geometry.Size() > 0){
			temp.geometry.ApplyTransformation();
			temp.geometry.matrix = AffineTransformMatrix();
			geometry.CopyFrom(temp.geometry);
			this->name = temp.geometry.name;
			geometry.CalcNormals();
			geometry.CalcGroups();
			geometry.ApplyTransformation();
		}
		return true;
	}

// Process a Wavefront OBJ-file:
	if(fileName.GetExt().CmpNoCase(_T("obj")) == 0){
		Hull temp;
		if(!temp.LoadObj(std::string(fileName.GetFullPath().mb_str()))){
			wxLogMessage
			(_("OBJ file not readable!"));
			return false;
		}
		geometry = temp;
		this->name = fileName.GetName();
		geometry.CalcNormals();
		geometry.CalcGroups();
		geometry.ApplyTransformation();

//		geometry.paintNormals = true;

		return true;
	}
	return false;
}

void Object::ToJSON(JSON &js) const
{
	js.SetObject(true);
	js["ID"].SetNumber(ID);
	js["Name"].SetString(name.ToStdString());
	std::ostringstream out;
	out << "object_" << ID << ".obj";
	js["Filename"].SetString(out.str());
	JSON &m = js["Matrix"];
	m.SetArray(16);
	for(size_t n = 0; n < 16; ++n)
		m[n].SetNumber(matrix[n]);
	js["Show"].SetBool(show);
	js["Selectable"].SetBool(selectable);

//	stream << _T("Color: ");
//	stream << geometry.color.x << _T(" ");
//	stream << geometry.color.y << _T(" ");
//	stream << geometry.color.z << endl;
}

bool Object::FromJSON(const JSON& js)
{
	if(!js.HasKey("ID")) return false;
	ID = (size_t) round(js["ID"].GetNumber());
	if(!js.HasKey("Name")) return false;
	name = js["Name"].GetString();
	const JSON &m = js["Matrix"];
	for(size_t n = 0; n < 16; ++n)
		matrix[n] = m[n].GetNumber();
	show = js["Show"].GetBool();
	selectable = js["Selectable"].GetBool();

	//	if(temp.Cmp(_T("Color:")) != 0) return false;
	//	geometry.color.x = stream.ReadDouble();
	//	geometry.color.y = stream.ReadDouble();
	//	geometry.color.z = stream.ReadDouble();

}
