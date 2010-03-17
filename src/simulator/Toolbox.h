//============================================================================
// Name        : Toolbox.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 16.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include "Tool.h"
#include <wx/dynarray.h>
WX_DECLARE_OBJARRAY(Tool, ArrayOfTools)
;
#include <wx/xml/xml.h>
#include <wx/string.h>

class Toolbox {
	//Constructor / Destructor
public:
	Toolbox();
	virtual ~Toolbox();

	//Member variables
public:

	ArrayOfTools tools;


private:
	wxXmlDocument* xmlDocument;



	// Methods
public:
	bool LoadToolbox(wxString fileName);
	bool SaveToolbox(wxString fileName);

};

#endif /* TOOLBOX_H_ */
