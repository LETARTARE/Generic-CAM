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
///////////////////////////////////////////////////////////////////////////////

#include "Run.h"

#include "generator/GeneratorCollection.h"

#include <wx/log.h>
#include <GL/gl.h>
#include <float.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfRun)

Run::Run()
{
	selected = false;
//	modified = false;
	name = _T("Run #");
	refWorkpiece = 0;
//	toolbox.Empty();
//	selectedTool = 0;
	parent = NULL;
}

Run::Run(const Run& other)
{
	throw(__FILE__ "Copy Constructor called.");
}

Run::~Run()
{
	for(size_t i = 0; i < generators.GetCount(); i++)
		delete generators[i];
}

//void Run::Paint(const ArrayOfObject& objects,
//		const ArrayOfWorkpiece& workpieces) const
//{
//	machine.Paint();
//
//	::glPushMatrix();
//
//	if(refWorkpiece > -1){
//		::glPushMatrix();
//		::glMultMatrixd(machine.workpiecePosition.a);
//		::glMultMatrixd(workpiecePlacement.a);
//		for(int n = 0; n < toolpaths.GetCount(); n++){
//			toolpaths[n].Paint();
//			if(toolpaths[n].generator != NULL) toolpaths[n].generator->Paint();
//		}
//		workpieces[refWorkpiece].Paint(objects);
//		::glPopMatrix();
//	}
//
//	::glPopMatrix();
//	if(selectedTool < toolbox.GetToolCount()){
//		::glPushMatrix();
//		::glMultMatrixd(machine.toolPosition.a);
//		::glColor3f(0.7, 0.7, 0.7);
//		toolbox.tools[selectedTool].Paint();
//		::glPopMatrix();
//	}
//
//}

void Run::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;
	throw(__FILE__ "Not yet implemented.");
	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("run")
				&& temp->GetPropVal(_T("name"), _T("")) == name) nodeObject =
				temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("run"));
		nodeObject->AddProperty(_T("name"), name);
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
	if(node->GetName() != _T("run")) return false;
	throw(__FILE__ "Not yet implemented.");
	name = node->GetPropVal(_T("name"), _T(""));
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

void Run::Update(void)
{
	for(size_t i = 0; i < generators.GetCount(); i++)
		generators[i]->parent = this;
}

void Run::ToolpathToStream(wxTextOutputStream & stream)
{
//	toolPath.ToolpathToStream(f);
	throw(__FILE__ "Not yet implemented.");
}

void Run::ToStream(wxTextOutputStream& stream)
{
	stream << _T("Name:") << endl << name << endl;
	stream << wxString::Format(_T("Workpiece: %u"), refWorkpiece) << endl;
	stream << wxString::Format(_T("Tools: %u"), tools.GetCount()) << endl;
	for(size_t n = 0; n < tools.GetCount(); n++){
		stream << wxString::Format(_T("Tool: %u"), n) << endl;
		tools[n].ToStream(stream);
	}
	GeneratorCollection gc;
	stream << wxString::Format(_T("Generators: %u"), generators.GetCount())
			<< endl;
	for(size_t n = 0; n < generators.GetCount(); n++){
		stream << wxString::Format(_T("Generator: %u"), n) << endl;
		size_t g;
		if(!gc.FindGenerator(generators[n], &g)) throw(__FILE__ "Cannot find generator.");
		stream << gc.GetName(g) << endl;
		generators[n]->ToStream(stream);
	}
}

bool Run::FromStream(wxTextInputStream& stream, int runNr, Project * project)
{
	wxString temp;
	temp = stream.ReadLine();
	if(temp.Cmp(_T("Name:")) != 0) return false;
	name = stream.ReadLine();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Workpiece:")) != 0) return false;
	refWorkpiece = stream.Read32S();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Tools:")) != 0) return false;
	size_t NTools = stream.Read32S();
	tools.Clear();
	for(size_t n = 0; n < NTools; n++){
		temp = stream.ReadWord();
		if(temp.Cmp(_T("Tool:")) != 0) return false;
		size_t index = stream.Read32S();
		if(index != n) return false;
		Tool temp;
		temp.FromStream(stream);
		tools.Add(temp);
	}
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Generators:")) != 0) return false;
	size_t N = stream.Read32();

	for(size_t n = 0; n < generators.GetCount(); n++)
		delete generators[n];
	generators.Clear();
	GeneratorCollection gc;
	for(size_t n = 0; n < N; n++){
		temp = stream.ReadLine();
		if(temp.Cmp(_T("Generator:")) != 0) return false;
		size_t index = stream.Read32S();
		if(index != n) return false;
		temp = stream.ReadLine();
		size_t generatorNr;
		if(!gc.FindGenerator(temp, &generatorNr)) return false;
		Generator* tempGen = gc.NewGenerator(generatorNr);
		tempGen->FromStream(stream);
		generators.Add(&tempGen);
	}
	return true;
}
