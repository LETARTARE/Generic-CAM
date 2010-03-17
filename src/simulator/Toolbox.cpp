//============================================================================
// Name        : Toolbox.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 16.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "Toolbox.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfTools)
#include "../Config.h"

Toolbox::Toolbox()
{
	xmlDocument = new wxXmlDocument();
	xmlDocument->SetFileEncoding(_T("UTF-8"));
	xmlDocument->SetVersion(_T(_GENERICCAM_VERSION));


	// an example Tool for the toolbox

	Tool* temp = new Tool;

	ToolElement* e;

	e = new ToolElement;
	e->h = 0.1;
	e->d = 0.7;
	e->r = 0.0;
	e->t = 2;
	e->cutting=false;
	temp->elements.Add(e);

	e = new ToolElement;
	e->h = 0.1;
	e->d = 0.0;
	e->r = 0.0;
	e->t = 2;
	e->cutting=true;
	temp->elements.Add(e);

	temp->toolName=_T("Generic Cutter");
	temp->comment = _T("for testing purposes");
	temp->shaftDiameter=0.006;
	temp->shaftLength=0.01;
	temp->maxSpeed = 100e3;
	temp->feedCoefficient=0.003;
	temp->nrOfTeeth=2;

	tools.Add(temp);
}

Toolbox::~Toolbox()
{
	delete xmlDocument;
}

bool Toolbox::LoadToolbox(wxString fileName)
{

	wxXmlDocument* tempTree = new wxXmlDocument();
	tempTree->SetFileEncoding(_T("UTF-8"));
	tempTree->SetVersion(_T(_GENERICCAM_VERSION));
	if(!tempTree->Load(fileName, wxT("UTF-8"), wxXMLDOC_KEEP_WHITESPACE_NODES)){
		delete tempTree;
		return false;
	}
	// Swap XML trees
	delete xmlDocument;
	xmlDocument = tempTree;


	//TODO: Loading code comes here.

	return true;
}

bool Toolbox::SaveToolbox(wxString fileName)
{

	if(!xmlDocument->Save(fileName, wxXML_NO_INDENTATION)){
		return false;
	}
	return true;
}
