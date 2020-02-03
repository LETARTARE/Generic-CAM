///////////////////////////////////////////////////////////////////////////////
// Name               : genericcam.h
// Purpose            : Main entry point
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
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

#ifndef GENERICCAM_H_
#define GENERICCAM_H_

#include "StdInclude.h"

#include <wx/cmdline.h>
#include <wx/string.h>
#include <wx/app.h>
#include <wx/intl.h>
#include <wx/config.h>
#include <wx/docview.h>

class GenericCAMApp:public wxApp {
public:
	GenericCAMApp(void);
	virtual ~GenericCAMApp(void);
	// Member variables
public:
//	FrameMain* frame;
	wxString loadOnStartup;

protected:
	wxLocale locale;
	wxConfig* config;

	// Methods
public:
	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
	virtual bool OnInit();
	virtual int OnExit();
	wxFrame* CreateChildFrame(wxView* view);
	wxDECLARE_NO_COPY_CLASS(GenericCAMApp);
};
DECLARE_APP(GenericCAMApp)

#endif /* GENERICCAM_H_ */
