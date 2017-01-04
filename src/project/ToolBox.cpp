///////////////////////////////////////////////////////////////////////////////
// Name               : ToolBox.cpp
// Purpose            : Holds a collection of tools.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.03.2010
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

#include "ToolBox.h"

#include "../Config.h"

ToolBox::ToolBox()
{
//	xmlDocument = new wxXmlDocument();
//	xmlDocument->SetFileEncoding(_T("UTF-8"));
//	xmlDocument->SetVersion(_T(_GENERICCAM_VERSION));

// an example Tool for the toolbox

	Tool* temp;
	ToolElement* e;

	initialized = false;

	temp = new Tool;

	e = new ToolElement;
	e->t = 0;
	e->h = 0.005;
	e->d = 0.005;
	e->r = 0.0;
	e->cutting = false;
	temp->elements.Add(e);

	e = new ToolElement;
	e->t = 2;
	e->h = 0.01;
	e->d = 0.006;
	e->r = 0.0;
	e->cutting = false;
	temp->elements.Add(e);

	e = new ToolElement;
	e->t = 2;
	e->h = 0.020;
	e->d = 0.00;
	e->r = 0.0;
	e->cutting = true;
	temp->elements.Add(e);

	temp->toolName = _("Standard cutter");
	temp->comment = _("all purpose cylindrical");
	temp->shaftDiameter = 0.006;
	temp->shaftLength = 0.01;
	temp->maxSpeed = 166.67;
	temp->feedCoefficient = 0.004;
	temp->nrOfTeeth = 1;

	temp->GenerateContour();

	tools.Add(temp);

	temp = new Tool;

	e = new ToolElement;
	e->t = 0;
	e->h = 0.005;
	e->d = 0.005;
	e->r = 0.0;
	e->cutting = false;
	temp->elements.Add(e);

	e = new ToolElement;
	e->t = 2;
	e->h = 0.02;
	e->d = 0.01;
	e->r = 0.0;
	e->cutting = false;
	temp->elements.Add(e);

	e = new ToolElement;
	e->t = 4;
	e->h = 0.0;
	e->d = 0.02;
	e->r = 0.0;
	e->cutting = true;
	temp->elements.Add(e);

	e = new ToolElement;
	e->t = 3;
	e->h = 0.0;
	e->d = 0.0;
	e->r = 0.0;
	e->cutting = true;
	temp->elements.Add(e);

	temp->toolName = _T("Round cutter");
	temp->comment = _T("for testing circle generation");
	temp->shaftDiameter = 0.006;
	temp->shaftLength = 0.01;
	temp->maxSpeed = 300;
	temp->feedCoefficient = 0.003;
	temp->nrOfTeeth = 2;

	temp->GenerateContour();

	tools.Add(temp);

}

ToolBox::~ToolBox()
{
//	if(xmlDocument != NULL) delete xmlDocument;
}

bool ToolBox::LoadToolBox(wxFileName& fileName)
{

//	wxXmlDocument* tempTree = new wxXmlDocument();
//	tempTree->SetFileEncoding(_T("UTF-8"));
//	tempTree->SetVersion(_T(_GENERICCAM_VERSION));
//	if(!tempTree->Load(fileName.GetFullPath(), wxT("UTF-8"),
//			wxXMLDOC_KEEP_WHITESPACE_NODES)){
//		delete tempTree;
//		return false;
//	}
//	// Swap XML trees
//	delete xmlDocument;
//	xmlDocument = tempTree;
//
//	this->fileName = fileName;

//TODO: Loading code comes here.

	return true;
}

bool ToolBox::SaveToolBox(wxFileName& fileName)
{

//	if(!xmlDocument->Save(fileName.GetFullPath(), wxXML_NO_INDENTATION)){
//		return false;
//	}
//	this->fileName = fileName;
	return true;
}

void ToolBox::Empty(void)
{
	tools.Empty();
	initialized = false;
	fileName.Clear();
}

size_t ToolBox::GetToolCount(void) const
{
	return tools.GetCount();
}

bool ToolBox::IsInitialized(void) const
{
	return initialized;
}

void ToolBox::ToStream(wxTextOutputStream& stream)
{
	stream << _T("ToolBox:") << endl;
	stream << fileName.GetFullPath() << endl;
	stream << _T("Tools: ");
	stream << wxString::Format(_T("%u"), tools.GetCount()) << endl;
	for(size_t n = 0; n < tools.GetCount(); n++){
		tools[n].ToStream(stream);
	}
}

bool ToolBox::FromStream(wxTextInputStream& stream)
{
	wxString temp;
	temp = stream.ReadLine();
	if(temp.Cmp(_T("ToolBox:")) != 0) return false;
	fileName = stream.ReadLine();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Tools:")) != 0) return false;
	size_t N = stream.Read32();
	size_t n;
	Tool tool;
	bool flag = true;
	tools.Clear();
	for(n = 0; n < N; n++){
		flag = tool.FromStream(stream);
		if(!flag) break;
		tools.Add(tool);
	}
	return flag;
}
