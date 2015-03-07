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

#include <float.h>
#include <GL/gl.h>
#include <wx/log.h>
#include <wx/arrimpl.cpp>

#include "../generator/GeneratorCollection.h"
WX_DEFINE_OBJARRAY(ArrayOfRun)

Run::Run()
{
	selected = false;
	modified = false;
	name = _T("Run #");
	workpieceNr = -1;
	toolbox.Empty();
	selectedTool = 0;
}

Run::~Run()
{
}

void Run::Paint(const ArrayOfObject& objects,
		const ArrayOfWorkpiece& workpieces) const
{
	machine.Paint();

	::glPushMatrix();

	if(workpieceNr > -1){
		::glPushMatrix();
		::glMultMatrixd(machine.workpiecePosition.a);
		::glMultMatrixd(workpiecePlacement.a);
		workpieces[workpieceNr].Paint(objects);
		for(int n = 0; n < toolpaths.GetCount(); n++){
			toolpaths[n].Paint();
			if(toolpaths[n].generator != NULL) toolpaths[n].generator->Paint();
		}
		::glPopMatrix();
	}

	::glPopMatrix();
	if(selectedTool < toolbox.GetToolCount()){
		::glPushMatrix();
		::glMultMatrixd(machine.toolPosition.a);
		::glColor3f(0.7, 0.7, 0.7);
		toolbox.tools[selectedTool].Paint();
		::glPopMatrix();
	}

}

void Run::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

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

void Run::ToolpathToStream(wxTextOutputStream & stream)
{
//	toolPath.ToolpathToStream(f);
}

void Run::ToStream(wxTextOutputStream& stream)
{
	stream << _T("Name:") << endl;
	stream << name << endl;
	stream << _T("Workpiece: ");
	stream << wxString::Format(_T("%i"), workpieceNr);
	stream << endl;
	toolbox.ToStream(stream);
	size_t n;
	GeneratorCollection gc;
	stream << _T("Generators: ");
	stream << wxString::Format(_T("%u"), toolpaths.GetCount());
	stream << endl;
	int g;
	for(n = 0; n < toolpaths.GetCount(); n++){
		toolpaths[n].ToStream(stream);
		stream << _T("Generator:") << endl;
		g = gc.FindGenerator(toolpaths[n].generator);
		stream << gc.GetName(g) << endl;
		toolpaths[n].generator->ToStream(stream);
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
	workpieceNr = stream.Read32S();
	if(!toolbox.FromStream(stream)) return false;
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Generators:")) != 0) return false;
	size_t N = stream.Read32();
	size_t n;
	size_t toolpathIndex;
	int generatorNr;
	ToolPath toolpath;
	toolpaths.Clear();
	GeneratorCollection gc;
	for(n = 0; n < N; n++){
		toolpath.FromStream(stream);
		toolpaths.Add(toolpath);
		toolpathIndex = toolpaths.GetCount() - 1;
		temp = stream.ReadLine();
		if(temp.Cmp(_T("Generator:")) != 0) return false;
		temp = stream.ReadLine();
		generatorNr = gc.FindGenerator(temp);
		toolpaths[toolpathIndex].generator = gc.NewGenerator(generatorNr,
				project, runNr, n);
		toolpaths[toolpathIndex].generator->FromStream(stream);
		printf(toolpaths[toolpathIndex].generator->GetName().ToAscii());
		printf("\n");
	}
	return true;
}

