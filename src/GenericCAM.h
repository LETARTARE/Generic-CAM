/*
 * GenericCAM.h
 *
 *  Created on: 21.2.2010
 *      Author: Tobias Schaefer
 */

#ifndef GENERICCAM_H_
#define GENERICCAM_H_

#include "StdInclude.h"
#include "Config.h"

#include <wx/docview.h>

#include "MainFrame.h"

class GenericCAMApp: public wxApp
{
	// Constructor
public:
	GenericCAMApp(void);

	// Member variables
protected:

public:
	MainFrame* frame;

	// Methods
public:
	virtual bool OnInit();

};

DECLARE_APP(GenericCAMApp)
#endif /* GENERICCAM_H_ */
