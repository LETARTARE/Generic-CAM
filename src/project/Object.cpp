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
}

Object::~Object()
{
}

void Object::Paint(void)
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
	bbox.Reset();
	for(i = 0; i < geometries.GetCount(); i++)
		bbox.Insert((geometries[i]), matrix);
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
				g.CopyFrom(temp.geometry[i]);
				g.objectName = fileName.GetName();
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
				g.CopyFrom(temp.geometry[i]);
				//TODO: Remove the calculation of normals.
				g.CalculateNormals();
				if(g.objectName.IsEmpty()){
					g.objectName = fileName.GetName()
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
				g.CopyFrom(temp.geometry[i]);
				g.objectName = temp.geometry[i].objectName;
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

// Recursive tree deletion.
void Object::XMLRemoveAllChildren(wxXmlNode* node)
{
	wxXmlNode *temp, *temp2;
	temp = node->GetChildren();
	while(temp != NULL){
		XMLRemoveAllChildren(temp);
		temp2 = temp;
		temp = temp->GetNext();
		node->RemoveChild(temp2);
		delete (temp2);
	}
}

void Object::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("object")
				&& temp->GetPropVal(_T("name"), _T("")) == fileName.GetName()) nodeObject =
				temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("object"));
		nodeObject->AddProperty(_T("name"), fileName.GetName());
		parentNode->InsertChild(nodeObject, NULL);
	}

	// Remove the subelements, that will be updated
	temp = nodeObject->GetChildren();
	while(temp != NULL){
		temp2 = NULL;
		if(temp->GetName() == _T("geometry")) temp2 = temp;
		if(temp->GetName() == _T("matrix")) temp2 = temp;
		temp = temp->GetNext();
		if(temp2 != NULL){
			XMLRemoveAllChildren(temp2);
			nodeObject->RemoveChild(temp2);
			delete (temp2);
		}
	}

	// Insert new geometries
	size_t i;
	for(i = 0; i < geometries.GetCount(); i++)
		geometries[i].ToXml(nodeObject);

	// Insert new matrix
	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("matrix"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			matrix.ToString());
	temp->InsertChild(temp2, NULL);
}

bool Object::FromXml(wxXmlNode* node)
{
	if(node->GetName() != _T("object")) return false;

	fileName.SetName(node->GetPropVal(_T("name"), _T("")));
	wxXmlNode *temp = node->GetChildren();
	Geometry * geometry;

	while(temp != NULL){
		if(temp->GetName() == _T("geometry")){
			geometry = new Geometry();
			if(geometry->FromXml(temp))
				geometries.Add(geometry);
			else
				delete geometry;
		}
		if(temp->GetName() == _T("matrix")) matrix.FromString(
				temp->GetNodeContent());

		temp = temp->GetNext();
	}
	UpdateBoundingBox();
	return true;
}
