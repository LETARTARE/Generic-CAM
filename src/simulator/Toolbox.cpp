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
	temp->maxSpeed = 100e3;
	temp->feedCoefficient = 0.003;
	temp->nrOfTeeth = 2;
	temp->slot = 2;

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
	e->t = 2;
	e->h = 0.015;
	e->d = 0.00;
	e->r = 0.0;
	e->cutting = true;
	temp->elements.Add(e);

	temp->toolName = _T("Standard cutter");
	temp->comment = _T("all purpose cylindrical");
	temp->shaftDiameter = 0.006;
	temp->shaftLength = 0.01;
	temp->maxSpeed = 100e3;
	temp->feedCoefficient = 0.003;
	temp->nrOfTeeth = 2;
	temp->slot = 1;

	temp->GenerateContour();

	tools.Add(temp);

}

Toolbox::~Toolbox()
{
	delete xmlDocument;
}

bool Toolbox::LoadToolbox(wxFileName& fileName)
{

	wxXmlDocument* tempTree = new wxXmlDocument();
	tempTree->SetFileEncoding(_T("UTF-8"));
	tempTree->SetVersion(_T(_GENERICCAM_VERSION));
	if(!tempTree->Load(fileName.GetFullPath(), wxT("UTF-8"),
			wxXMLDOC_KEEP_WHITESPACE_NODES)){
		delete tempTree;
		return false;
	}
	// Swap XML trees
	delete xmlDocument;
	xmlDocument = tempTree;

	this->fileName = fileName;


	//TODO: Loading code comes here.

	return true;
}

bool Toolbox::SaveToolbox(wxFileName& fileName)
{

	if(!xmlDocument->Save(fileName.GetFullPath(), wxXML_NO_INDENTATION)){
		return false;
	}
	this->fileName = fileName;
	return true;
}
