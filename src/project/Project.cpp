///////////////////////////////////////////////////////////////////////////////
// Name               : Project.cpp
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


#include "Project.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfProject)

#include <wx/xml/xml.h>
#include <GL/gl.h>

Project::Project()
{
	modified = false;
	projectName = _("Untitled");

	activeObject = 0;
	activeTarget = 0;
	activeStock = 0;

	displayGeometry = true;
	displayBoundingBox = false;
	displayMachine = false;
	displayStock = true;
	displayWorkpiece = false;
	displayTarget = true;
	displayToolpath = true;

	Tolerance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	Distance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	RotationalSpeed.Setup(_T("1/s"), _T("rpm"), (double) 1 / 60);
	LinearSpeed.Setup(_T("m/s"), _T("mm/s"), (double) 1 / 1000);

	slotWidth = 0.010;
	resolution = 0.0005;

}

Project::~Project()
{
}

bool Project::Save(wxFileName fileName)
{
	if(!file) return false;

	wxASSERT(xmlDocument!=NULL);

	// OnSave returns false is saving failed.
	// Save code insert below this line

	wxXmlNode* root = xmlDocument->GetRoot();
	if(root == NULL){
		root = new wxXmlNode(wxXML_ELEMENT_NODE, _T("ringelwolfdatafile"));
		xmlDocument->SetRoot(root);
	}

	wxXmlNode *nodeGeometry = NULL;
	wxXmlNode *nodeSource = NULL;
	wxXmlNode *nodeConnection = NULL;
	wxXmlNode *nodeResult = NULL;
	wxXmlNode *temp;

	temp = root->GetChildren();
	while(temp != NULL){
		if(temp->GetName() == _T("geometry")) nodeGeometry = temp;
		if(temp->GetName() == _T("source")) nodeSource = temp;
		if(temp->GetName() == _T("connection")) nodeConnection = temp;
		if(temp->GetName() == _T("result")) nodeResult = temp;
		temp = temp->GetNext();
	}
	if(nodeGeometry == NULL){
		nodeGeometry = new wxXmlNode(wxXML_ELEMENT_NODE, _T("geometry"));
		root->InsertChild(nodeGeometry, NULL);
	}
	if(nodeSource == NULL){
		nodeSource = new wxXmlNode(wxXML_ELEMENT_NODE, _T("source"));
		root->InsertChild(nodeSource, NULL);
	}
	if(nodeConnection == NULL){
		nodeConnection = new wxXmlNode(wxXML_ELEMENT_NODE, _T("connection"));
		root->InsertChild(nodeConnection, NULL);
	}
	if(nodeResult == NULL){
		nodeResult = new wxXmlNode(wxXML_ELEMENT_NODE, _T("result"));
		root->InsertChild(nodeResult, NULL);
	}

	unsigned int i;
	for(i = 0; i < geometry.Count(); i++)
		geometry[i].ToXml(nodeGeometry);
	for(i = 0; i < connection.Count(); i++)
		connection[i].ToXml(nodeConnection);
	for(i = 0; i < source.Count(); i++)
		source[i].ToXml(nodeSource);
	for(i = 0; i < result.Count(); i++)
		result[i].ToXml(nodeResult);

	if(!xmlDocument->Save(file, wxXML_NO_INDENTATION)){
		return false;
	}
	Modify(false);
	SetFilename( file);
	SetDocumentSaved(true);
#if defined( __WXOSX_MAC__ ) && wxOSX_USE_CARBON
	wxFileName fn(file);
	fn.MacSetDefaultTypeAndCreator();
#endif
	return true;
}
bool Project::Load(wxFileName fileName)
{
	wxXmlDocument* tempTree = new wxXmlDocument();
	tempTree->SetFileEncoding(_T("UTF-8"));
	tempTree->SetVersion(_T(_RINGELWOLF_VERSION));
	if(!tempTree->Load(file, wxT("UTF-8"), wxXMLDOC_KEEP_WHITESPACE_NODES)){
		delete tempTree;
		return false;
	}
	// Swap XML trees
	delete xmlDocument;
	xmlDocument = tempTree;


	// Take the tree apart
	wxXmlNode *temp = xmlDocument->GetRoot();
	if(temp == NULL){
		wxLogWarning(_T("File contains no data (i.e. no root)!"));
		return false;
	}
	if(temp->GetName() != _T("ringelwolfdatafile")){
		wxLogWarning(_T("Not a Ringelwolf datafile!"));
		return false;
	}

	ClearDocument();

	Geometry *tempGeometryObject = NULL;
	Source *tempSourceObject = NULL;
	Connection *tempConnectionObject = NULL;
	Result *tempResultObject = NULL;

	wxXmlNode *temp2;


	//TODO: Remove this dialog. The Parsing should be made "infinite-loop"-less.
	bool flagParseGeometry = false;
	wxMessageDialog dialog(NULL, _T("Parse object gemetry?"), _T("Parse data"),
			wxYES_NO | wxYES_DEFAULT);
	if(dialog.ShowModal() == wxID_YES) flagParseGeometry = true;

	temp = temp->GetChildren();
	while(temp != NULL){
		if(temp->GetName() == _T("geometry")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				tempGeometryObject = new Geometry();
				tempGeometryObject->FromXml(temp2);

				if(flagParseGeometry) tempGeometryObject->Generate();

				geometry.Add(tempGeometryObject);
				temp2 = temp2->GetNext();
			}

			wxLogMessage(_T("Geometry found!"));
		}
		if(temp->GetName() == _T("source")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				tempSourceObject = new Source();
				tempSourceObject->FromXml(temp2);
				source.Add(tempSourceObject);
				temp2 = temp2->GetNext();
			}

			wxLogMessage(_T("Source found!"));
		}
		if(temp->GetName() == _T("connection")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				tempConnectionObject = new Connection();
				tempConnectionObject->FromXml(temp2);
				connection.Add(tempConnectionObject);
				temp2 = temp2->GetNext();
			}

			wxLogMessage(_T("Connection found!"));
		}
		if(temp->GetName() == _T("result")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				tempResultObject = new Result();
				tempResultObject->FromXml(temp2);
				result.Add(tempResultObject);
				temp2 = temp2->GetNext();
			}

			wxLogMessage(_T("Result found!"));
		}

		temp = temp->GetNext();
	}

	SetFilename(file, true);


	// stretching the logic a little this does make sense because the document
	// had been saved into the file we just loaded it from, it just could have
	// happened during a previous program execution, it's just that the name of
	// this method is a bit unfortunate, it should probably have been called
	// HasAssociatedFileName()
	SetDocumentSaved(true);
	EvaluateConnections();
	UpdateAllViews();
	return true;
}

void Project::Assemble(void)
{
	machine.Assemble();
	if(machine.IsInitialized()) stock.matrix = machine.workpiecePosition;

}

void Project::Paint(void)
{
	size_t i;
	if(displayGeometry){
		for(i = 0; i < objects.GetCount(); i++)
			objects[i].Paint();
	}
	if(displayMachine) machine.Paint();
	if(displayStock) stock.Paint();

	if(displayTarget){
		for(i = 0; i < targets.GetCount(); i++)
			targets[i].Paint();
	}


	//if(displayWorkpiece) workpiece.Paint();
	//if(displayBoundingBox) bbox.Paint();
}

//bool Project::LoadObject(wxFileName)


void Project::GenerateTargets(void)
{
	targets.Clear();

	Target temp;

	Object* obj = &(objects[activeObject]);

	obj->UpdateBoundingBox();

	size_t i, n;
	n = ceil(obj->bbox.zmax / stock.stockMaterials[activeStock].z);

	Target discSlot;
	discSlot.SetupCylinder(slotWidth, stock.stockMaterials[activeStock].z,
			resolution, resolution);

	discSlot.matrix.TranslateGlobal(0.1, -0.1, 0);
	targets.Add(discSlot);

	for(i = 2; i < 3; i++){

		temp.SetupBox(obj->bbox.xmax + 4 * slotWidth, obj->bbox.ymax + 4
				* slotWidth, stock.stockMaterials[activeStock].z, resolution,
				resolution);

		temp.shift.SetIdentity();
		temp.shift.TranslateGlobal(2.0 * slotWidth, 2.0 * slotWidth, (double) i
				* -stock.stockMaterials[activeStock].z);

		temp.InsertObject(*obj, temp.shift);
		temp.FoldRaise(discSlot);
		temp.outline = temp.GeneratePolygon(-1, -1);
		temp.PolygonSmooth(temp.outline);
		temp.PolygonSmooth(temp.outline);
		temp.PolygonSmooth(temp.outline);


		//temp.ClearField();

		if(temp.outline.elements.GetCount() >= 2){

			ToolPathGenerator.GenerateToolpath(temp, *obj, toolbox.tools[0]);
			targets.Add(temp);

		}

	}

	displayGeometry = false;
	displayStock = false;

}

