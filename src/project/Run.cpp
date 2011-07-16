///////////////////////////////////////////////////////////////////////////////
// Name               : Run.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
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


#include "Run.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfRun)

Run::Run()
{

}

Run::~Run()
{

}

void Run::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("run") && temp->GetPropVal(_T("name"),
				_T("")) == runName) nodeObject = temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("run"));
		nodeObject->AddProperty(_T("name"), runName);
		parentNode->InsertChild(nodeObject, NULL);
	}

//	// Remove the subelements, that will be updated
//	temp = nodeObject->GetChildren();
//	while(temp != NULL){
//		temp2 = NULL;
//		if(temp->GetName() == _T("matrix")) temp2 = temp;
//		if(temp->GetName() == _T("tri")) temp2 = temp;
//		temp = temp->GetNext();
//		if(temp2 != NULL){
//			nodeObject->RemoveChild(temp2);
//			delete (temp2);
//		}
//	}
//
//	// Insert new matrix
//	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("matrix"));
//	nodeObject->InsertChild(temp, NULL);
//	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
//			matrix.ToString());
//	temp->InsertChild(temp2, NULL);
//
//
//	// Insert new triangles
//	size_t i;
//	for(i = 0; i < triangles.GetCount(); i++){
//		temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("tri"));
//		nodeObject->InsertChild(temp, NULL);
//		temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
//				triangles[i].ToString());
//		temp->InsertChild(temp2, NULL);
//	}
}

bool Run::FromXml(wxXmlNode* node)
{
	if(node->GetName()!=_T("run"))return false;

	runName = node->GetPropVal(_T("name"), _T(""));
	wxXmlNode *temp = node->GetChildren();
//	long tempLong;
//
//	triangles.Empty();
//	Triangle* tri;
//
//	while(temp != NULL){
//		if(temp->GetName() == _T("tri")){
//			tri = new Triangle(temp->GetNodeContent());
//			triangles.Add(tri);
//		}
//		if(temp->GetName() == _T("matrix")) matrix.FromString(
//				temp->GetNodeContent());
//		temp = temp->GetNext();
//	}
	return true;
}


void Run::WriteToFile(wxTextFile &f)
{
	toolPath.WriteToFile(f);
}
