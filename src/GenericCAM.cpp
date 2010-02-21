//============================================================================
// Name        : GenericCAM.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Copyright   : (c) 2009
// Description : CAM Software
//============================================================================


#include "GenericCAM.h"

// The line that starts it all.
IMPLEMENT_APP(GenericCAMApp)

GenericCAMApp::GenericCAMApp()
{



}

bool GenericCAMApp::OnInit()
{
	frame = new MainFrame(NULL);
	frame -> Show();
	return true;
}
