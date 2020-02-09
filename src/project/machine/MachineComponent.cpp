///////////////////////////////////////////////////////////////////////////////
// Name               : MachineComponent.cpp
// Purpose            : A component of the machine
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
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

#include "MachineComponent.h"

#include "../../3D/FileSTL.h"
#include "../../3D/FileDXF.h"

#include <wx/log.h>
#include <wx/glcanvas.h>

MachineComponent::MachineComponent(wxString nameOfComponent)
{
	this->nameOfComponent = nameOfComponent;
	geometry.useColor = geometryColorTriangle;
	isColorSet = false;
}

MachineComponent::~MachineComponent()
{
}

void MachineComponent::InsertBox(AffineTransformMatrix matrix, float x, float y,
		float z)
{
	float x2 = x / 2;
	float y2 = y / 2;
	float z2 = z / 2;
	Vector3 p0(x2, y2, z2);
	Vector3 p1(-x2, y2, z2);
	Vector3 p2(-x2, -y2, z2);
	Vector3 p3(x2, -y2, z2);
	Vector3 p4(x2, y2, -z2);
	Vector3 p5(-x2, y2, -z2);
	Vector3 p6(-x2, -y2, -z2);
	Vector3 p7(x2, -y2, -z2);

	geometry.AddQuadTransform(p0, p1, p2, p3, matrix);
	geometry.AddQuadTransform(p0, p3, p7, p4, matrix);
	geometry.AddQuadTransform(p1, p0, p4, p5, matrix);
	geometry.AddQuadTransform(p2, p1, p5, p6, matrix);
	geometry.AddQuadTransform(p3, p2, p6, p7, matrix);
	geometry.AddQuadTransform(p7, p6, p5, p4, matrix);
}

void MachineComponent::InsertCylinder(AffineTransformMatrix matrix, float h,
		float r)
{
	InsertCone(matrix, h, r, r);
}

void MachineComponent::InsertCone(AffineTransformMatrix matrix, float h,
		float r1, float r2)
{
	const unsigned char N = 32;
	unsigned char i;
	float ss[N + 1], cc[N + 1];
	for(i = 0; i <= N; i++){
		ss[i] = sin(2 * M_PI / N * i);
		cc[i] = cos(2 * M_PI / N * i);
	}

	Vector3 m0(0, 0, h / 2);
	Vector3 m1(0, 0, -h / 2);
	Vector3 p0, p1, p2, p3;
	if(r1 > 0){
		for(i = 0; i <= N; i++){
			p1.Set(r1 * cc[i], r1 * ss[i], h / 2);
			if(i > 0){
				geometry.AddTriangleTransform(m0, p0, p1, matrix);
			}
			p0 = p1;
		}
	}
	if(r2 > 0){
		for(i = 0; i <= N; i++){
			p1.Set(r2 * cc[i], r2 * ss[i], -h / 2);
			if(i > 0){
				geometry.AddTriangleTransform(m1, p1, p0, matrix);
			}
			p0 = p1;
		}
	}
	if(r1 > 0 && r2 > 0){
		for(i = 0; i <= N; i++){
			p2.Set(r1 * cc[i], r1 * ss[i], h / 2);
			p3.Set(r2 * cc[i], r2 * ss[i], -h / 2);
			if(i > 0){
				geometry.AddQuadTransform(p0, p1, p3, p2, matrix);
			}
			p0 = p2;
			p1 = p3;
		}
	}
}

bool MachineComponent::InsertSTL(const AffineTransformMatrix &matrix,
		wxFileName file)
{
//	wxLogMessage(_T("@MachineComponent::InsertSTL: "+file.GetFullPath()));
	FileSTL f;
	f.color = geometry.colorNewObjects;
	if(!f.ReadFile(file.GetFullPath())) return false;
	f.geometry.ApplyTransformation(matrix);
	geometry.InsertTrianglesFrom(f.geometry);
//	geometry.matrix *= matrix;
	return true;
}

bool MachineComponent::InsertSTL(const AffineTransformMatrix &matrix,
		wxInputStream &file)
{
	FileSTL f;
	f.color = geometry.colorNewObjects;

	if(!f.ReadStream(file)) return false;

	f.geometry.ApplyTransformation(matrix);
	geometry.InsertTrianglesFrom(f.geometry);
//	geometry.matrix *= matrix;
	return true;
}

bool MachineComponent::InsertDXF(const AffineTransformMatrix &matrix,
		wxFileName file, wxString componentName)
{
	wxLogMessage
	(_T("@MachineComponent::InsertDXF: "+file.GetFullPath()));

	FileDXF f;
	f.color = geometry.colorNewObjects;
	if(!f.ReadFile(file.GetFullPath())) return false;

	size_t i;
	if(f.geometry.name.Cmp(componentName) == 0){
		f.geometry.ApplyTransformation(matrix);
		geometry.InsertTrianglesFrom(f.geometry);
	}
	return true;
}

void MachineComponent::SetColor(float r, float g, float b)
{
	if(isColorSet)
		geometry.useColor = geometryColorTriangle;
	else
		geometry.useColor = geometryColorGlobal;
	geometry.color.Set(r, g, b);
	geometry.colorNewObjects.Set(r, g, b);
	isColorSet = true;
}

void MachineComponent::Paint(void) const
{
	::glPushMatrix();
	matrix.GLMultMatrix();
	geometry.Paint();
	::glPopMatrix();
}
