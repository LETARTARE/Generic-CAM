//============================================================================
// Name        : GenericCAM.h
// Author      : Tobias Schaefer
// Version     : 0.1
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================

#ifndef GENERICCAM_H_
#define GENERICCAM_H_

#include "StdInclude.h"
#include "Config.h"
#include "gui/MainFrame.h"

class GenericCAMApp:public wxApp {
	// Constructor
public:
	GenericCAMApp(void);

	// Member variables
public:
	MainFrame* frame;

	// Methods
public:
	virtual bool OnInit();

};
DECLARE_APP(GenericCAMApp)
#endif /* GENERICCAM_H_ */
