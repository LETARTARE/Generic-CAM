///////////////////////////////////////////////////////////////////////////////
// Name               : Geometry.cpp
// Purpose            : Class for managing 3D geometry data
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.02.2010
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

#include "Geometry.h"

#include <GL/gl.h>
#include <wx/log.h>
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(ArrayOfGeometry);

Geometry::Geometry()
{
	visible = true;
	color.Set(0.8, 0.8, 0.8);
	colorNewObjects.Set(0.8, 0.8, 0.8);
	useColor = geometryColorGlobal;
}

Geometry::~Geometry()
{
}

void Geometry::Clear(void)
{
	triangles.Clear();
}

void Geometry::InsertTrianglesFrom(const Geometry& geometry, bool recolor)
{
	size_t i;
	Triangle temp;
	for(i = 0; i < geometry.triangles.GetCount(); i++){
		temp = geometry.triangles[i];
		if(recolor){
			temp.c[0] = colorNewObjects;
			temp.c[1] = colorNewObjects;
			temp.c[2] = colorNewObjects;
		}
		this->triangles.Add(temp);
	}
}

void Geometry::ApplyTransformation(const AffineTransformMatrix& matrix)
{
	size_t i;
	for(i = 0; i < triangles.Count(); i++)
		triangles[i].ApplyTransformation(matrix);
}

void Geometry::ApplyTransformation(void)
{
	size_t i;
	for(i = 0; i < triangles.Count(); i++)
		triangles[i].ApplyTransformation(this->matrix);
}

void Geometry::Paint(GeometryColorStyle style) const
{
	if(!visible) return;

	if(style == geometryColorDefault) style = useColor;

	// GL_RESCALE_NORMAL is faster, but doesn't work on non-uniform scaled models
	// GL_NORMALIZE is slower, but works always
	// ... and there seems to be a problem under Windows with OpenGL 1.1...

#if defined __WIN32__
	::glEnable(GL_NORMALIZE);
#else
	::glEnable(GL_RESCALE_NORMAL);
#endif

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	size_t i;
	::glBegin(GL_TRIANGLES);
	switch(style){
	case geometryColorNone:
		for(i = 0; i < triangles.Count(); i++)
			triangles[i].Paint(true, false);
		break;
	case geometryColorGlobal:
		::glColor3f(color.x, color.y, color.z);
		for(i = 0; i < triangles.Count(); i++)
			triangles[i].Paint(true, false);
		break;
	case geometryColorTriangle:
		for(i = 0; i < triangles.Count(); i++){
			::glColor3f(triangles[i].c[0].x, triangles[i].c[0].y,
					triangles[i].c[0].z);
			triangles[i].Paint(true, false);
		}
		break;
	case geometryColorVertex:
		for(i = 0; i < triangles.Count(); i++)
			triangles[i].Paint(true, true);
		break;

	}
	::glEnd();
	::glPopMatrix();
#if defined (__WIN32__)
	::glDisable(GL_NORMALIZE);
#else
	::glDisable(GL_RESCALE_NORMAL);
#endif
}

void Geometry::AddTriangle(const Vector3& a, const Vector3& b, const Vector3& c)
{
	Triangle* tri = new Triangle;
	tri->p[0] = a;
	tri->p[1] = b;
	tri->p[2] = c;
	tri->c[0] = colorNewObjects;
	tri->CalculateNormal();
	triangles.Add(tri);
}

void Geometry::AddTriangleWithNormals(const Vector3& a, const Vector3& b,
		const Vector3& c, const Vector3& na, const Vector3& nb,
		const Vector3& nc)
{
	Triangle* tri = new Triangle;
	tri->p[0] = a;
	tri->p[1] = b;
	tri->p[2] = c;
	tri->n[0] = na;
	tri->n[1] = nb;
	tri->n[2] = nc;
	tri->c[0] = colorNewObjects;
	triangles.Add(tri);
}

void Geometry::AddTriangleTransform(const Vector3& a, const Vector3& b,
		const Vector3& c, const AffineTransformMatrix& transformMatrix)
{
	Triangle* tri = new Triangle;
	tri->p[0] = transformMatrix.Transform(a);
	tri->p[1] = transformMatrix.Transform(b);
	tri->p[2] = transformMatrix.Transform(c);
	tri->c[0] = colorNewObjects;
	tri->CalculateNormal();
	triangles.Add(tri);
}

void Geometry::AddTriangle(const Triangle& tri, bool copyNormals)
{
	Triangle * temp = new Triangle(tri);
	if(!copyNormals) temp->CalculateNormal();
	triangles.Add(temp);
}

void Geometry::AddQuad(const Vector3& a, const Vector3& b, const Vector3& c,
		const Vector3& d)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->p[0] = a;
	tri0->p[1] = b;
	tri0->p[2] = c;
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = d;
	tri1->p[2] = tri0->p[0];
	tri0->CalculateNormal();
	tri1->n[0] = tri0->n[0];
	tri1->n[1] = tri0->n[1];
	tri1->n[2] = tri0->n[2];
	tri0->c[0] = colorNewObjects;
	tri1->c[0] = colorNewObjects;
	triangles.Add(tri0);
	triangles.Add(tri1);
}

void Geometry::AddQuadTransform(const Vector3& a, const Vector3& b,
		const Vector3& c, const Vector3& d,
		const AffineTransformMatrix& transformMatrix)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->c[0] = colorNewObjects;
	tri0->p[0] = transformMatrix.Transform(a);
	tri0->p[1] = transformMatrix.Transform(b);
	tri0->p[2] = transformMatrix.Transform(c);
	tri0->CalculateNormal();
	tri1->c[0] = colorNewObjects;
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = transformMatrix.Transform(d);
	tri1->p[2] = tri0->p[0];
	tri1->n[0] = tri0->n[0];
	tri1->n[1] = tri0->n[1];
	tri1->n[2] = tri0->n[2];
	triangles.Add(tri0);
	triangles.Add(tri1);
}

void Geometry::CalculateNormals(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].CalculateNormal();
	}
}

void Geometry::FlipX(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].p[0].x = -triangles[i].p[0].x;
		triangles[i].p[1].x = -triangles[i].p[1].x;
		triangles[i].p[2].x = -triangles[i].p[2].x;
	}
}

void Geometry::FlipY(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].p[0].y = -triangles[i].p[0].y;
		triangles[i].p[1].y = -triangles[i].p[1].y;
		triangles[i].p[2].y = -triangles[i].p[2].y;
	}
}

void Geometry::FlipZ(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].p[0].z = -triangles[i].p[0].z;
		triangles[i].p[1].z = -triangles[i].p[1].z;
		triangles[i].p[2].z = -triangles[i].p[2].z;
	}
}
void Geometry::FlipNormals(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].n[0] = -triangles[i].n[0];
		triangles[i].n[1] = -triangles[i].n[1];
		triangles[i].n[2] = -triangles[i].n[2];
		// Switch the order of edges by swaping vertex 1 and 2
		// 0->1->2->0 becomes 0->2->1->0.
		triangles[i].p[1].Swap(triangles[i].p[2]);
	}
}

void Geometry::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("geometry")
				&& temp->GetPropVal(_T("name"), _T("")) == name) nodeObject =
				temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("geometry"));
		nodeObject->AddProperty(_T("name"), name);
		parentNode->InsertChild(nodeObject, NULL);
	}

	// Remove the subelements, that will be updated
	temp = nodeObject->GetChildren();
	while(temp != NULL){
		temp2 = NULL;
		if(temp->GetName() == _T("matrix")) temp2 = temp;
		if(temp->GetName() == _T("tri")) temp2 = temp;
		temp = temp->GetNext();
		if(temp2 != NULL){
			nodeObject->RemoveChild(temp2);
			delete (temp2);
		}
	}

	// Insert new matrix
	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("matrix"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			matrix.ToString());
	temp->InsertChild(temp2, NULL);

	// Insert new triangles
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("tri"));
		nodeObject->InsertChild(temp, NULL);
		temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
				triangles[i].ToString());
		temp->InsertChild(temp2, NULL);
	}
}

bool Geometry::FromXml(wxXmlNode* parentNode)
{
	if(parentNode->GetName() != _T("geometry")) return false;
	name = parentNode->GetPropVal(_T("name"), _T(""));
	wxXmlNode *temp = parentNode->GetChildren();

	triangles.Empty();
	Triangle* tri;

	while(temp != NULL){
		if(temp->GetName() == _T("tri")){
			tri = new Triangle(temp->GetNodeContent());
			//			if(triangles.GetCount() < 20) wxLogMessage(
			//					_T("Geometry::FromXml: Tri from >")
			//							+ temp->GetNodeContent() + _T("<."));

			triangles.Add(tri);
		}
		if(temp->GetName() == _T("matrix")){
			matrix.FromString(temp->GetNodeContent());
			//			wxLogMessage(_T("Geometry::FromXml: Matrix from >")
			//					+ temp->GetNodeContent() + _T("<."));
		}
		temp = temp->GetNext();
	}
	return true;
}

