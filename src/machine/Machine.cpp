///////////////////////////////////////////////////////////////////////////////
// Name               : Machine.cpp
// Purpose            : The machine.
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#include "Machine.h"

#include <wx/log.h>
#include <GL/gl.h>
#include <wx/textfile.h>

Machine::Machine()
{
	initialized = false;
	tool = NULL;
	toolpath = NULL;
	position.Zero();
	ClearComponents();
}

Machine::~Machine()
{
}

void Machine::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;


	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("machine") && temp->GetPropVal(_T("name"),
				_T("")) == fileName.GetFullName()) nodeObject = temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("machine"));
		nodeObject->AddProperty(_T("name"), fileName.GetFullName());
		parentNode->InsertChild(nodeObject, NULL);
	}

	// Remove the subelements, that will be updated
	temp = nodeObject->GetChildren();
	while(temp != NULL){
		temp2 = NULL;
		if(temp->GetName() == _T("filename")) temp2 = temp;
		if(temp->GetName() == _T("description")) temp2 = temp;
		temp = temp->GetNext();
		if(temp2 != NULL){
			nodeObject->RemoveChild(temp2);
			delete (temp2);
		}
	}

	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("filename"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			fileName.GetFullPath());
	temp->InsertChild(temp2, NULL);

	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("description"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			machineDescription);
	temp->InsertChild(temp2, NULL);

}

bool Machine::FromXml(wxXmlNode* node)
{
	//	objectName = node->GetPropVal(_T("name"), _T(""));
	if(node->GetName() != _T("machine")) return false;

	wxXmlNode *temp = node->GetChildren();
	while(temp != NULL){
		if(temp->GetName() == _T("filename")){
			fileName = temp->GetNodeContent();
		}
		if(temp->GetName() == _T("description")){
			machineDescription = temp->GetNodeContent();
		}
		temp = temp->GetNext();
	}
	return true;
}

void Machine::Paint(void) const
{
	size_t i;
	for(i = 0; i < components.GetCount(); i++){
		components[i].Paint();
	}

	if(tool != NULL){
		::glPushMatrix();
		::glMultMatrixd(toolPosition.a);
		tool->Paint();
		::glPopMatrix();
	}
	//	::glPushMatrix();
	//	::glMultMatrixd(workpiecePosition.a);
	//	workpiece.Paint();
	//	::glPopMatrix();


	//if(toolpath != NULL) toolpath->Paint();

}

void Machine::ClearComponents(void)
{
	components.Empty();
	AddComponent(_T("Base"));
}

bool Machine::AddComponent(wxString const& nameOfComponent)
{
	size_t i;
	for(i = 0; i < components.GetCount(); i++){
		if(components[i].nameOfComponent.Cmp(nameOfComponent) == 0) return false;
	}
	MachineComponent temp(nameOfComponent);
	components.Add(temp);
	return true;
}

bool Machine::PlaceComponent(wxString const& nameOfComponent,
		AffineTransformMatrix const& matrix)
{
	size_t i;
	bool flag = false;
	for(i = 0; i < components.GetCount(); i++){
		if(components[i].nameOfComponent.Cmp(nameOfComponent) == 0){
			flag = true;
			components[i].matrix.Set(matrix);


			// Sideeffect of placing the components:
			// The tool and the material matrices are set up.
			if(i == componentWithMaterial){
				workpiecePosition.Set(workpiecePositionRelativ);
				workpiecePosition = matrix * workpiecePosition;
			}
			if(i == componentWithTool){
				toolPosition.Set(toolPositionRelativ);
				toolPosition = matrix * toolPosition;
			}
		}
	}
	return flag;
}

void Machine::Assemble()
{
	if(initialized) evaluator.EvaluateAssembly();
}

void Machine::EvaluateDescription(void)
{
	wxLogMessage(_T("Machine::InsertMachineDescription"));
	evaluator.LinkToProject(this);
	if(evaluator.EvaluateProgram())
		initialized = true;
	else
		initialized = false;
	Assemble();
	textOut = evaluator.GetOutput();
}

bool Machine::ReLoad(void)
{
	if(!fileName.IsOk()) return false;
	wxTextFile file(fileName.GetFullPath());
	if(!file.Open(wxConvLocal)){
		if(!file.Open(wxConvFile)){
			wxLogError(_T("Opening of the file failed!"));
			return false;
		}
	}
	wxString str;
	machineDescription.Empty();
	for(str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()){
		machineDescription += str + _T("\n");
	}
	EvaluateDescription();
	//wxLogMessage(machineDescription);
	return true;
}

bool Machine::Load(wxFileName const& fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	return ReLoad();
}
