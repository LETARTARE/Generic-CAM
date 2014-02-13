///////////////////////////////////////////////////////////////////////////////
// Name               : GenericCAM.cpp
// Purpose            : Main entry point.
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////

#include "GenericCAM.h"

#ifndef __WIN32__
#include "icon/logo.xpm"
#endif

#include "languages.h"
// The line that starts it all.
IMPLEMENT_APP(GenericCAMApp)

GenericCAMApp::GenericCAMApp()
{

	config = new wxConfig(_T("GenericCAM"));

	unsigned int selectedLanguage = wxLocale::GetSystemLanguage();
	if(selectedLanguage == wxLANGUAGE_UNKNOWN) selectedLanguage
			= wxLANGUAGE_DEFAULT;


	// Read language from config.
	wxString str;
	if(config->Read(_T("Language"), &str)){
		unsigned int i;
		for(i = 0; i < WXSIZEOF(langNames); i++)
			if(str.CmpNoCase(langNames[i]) == 0){
				selectedLanguage = langIds[i];
			}
	}

	//CHECK: Why does wxLOCALE_CONV_ENCODING not work?
	if(!locale.Init(selectedLanguage, wxLOCALE_LOAD_DEFAULT)){
		wxLogError(_T("This language is not supported by the system."));
		return;
	}

	//	wxLogMessage(wxString::Format(_T("id language : %u " ), selectedLanguage));
	//	wxLogMessage(wxString::Format(_T("id language : %u " ),
	//			locale.GetLanguage()));
	//	wxLogMessage(_T("name language :") + locale.GetCanonicalName());

	locale.AddCatalogLookupPathPrefix(_T("i18n"));
	bool catalogLoaded = locale.AddCatalog(_T("GenericCAM"));
	if(!catalogLoaded){
		wxLogError(_T("The translation catalog for ")
				+ locale.GetCanonicalName() + _T(" was not loaded !"));
	}
}

// The Commandline is parsed before OnInit is called.
bool GenericCAMApp::OnInitCmdLine(wxCmdLineParser& parser)
{
	parser.AddParam(_("<filepath of document to open>"), wxCMD_LINE_VAL_STRING,
			wxCMD_LINE_PARAM_OPTIONAL);
	return wxApp::OnInitCmdLine(parser);
}

bool GenericCAMApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	wxString str;
	int count = parser.GetParamCount();
	if(count == 1){
		str = parser.GetParam(0);
		//		if(_DEBUGMODE) wxLogMessage(_T("cmd line param: ") + str);
		loadOnStartup = str;

	}
	return true;
}

bool GenericCAMApp::OnInit()
{
	if(!wxApp::OnInit()) return false;

	frame = new MainFrame(NULL, &locale, config);

	if(!loadOnStartup.IsEmpty()){
		frame->LoadProject(loadOnStartup);

	}


	//TODO: Check, why the icon is not working under Windows / Code::Blocks.
#ifndef __WIN32__
	wxIcon iconLogo(logo_xpm);
	frame->SetIcon(iconLogo);
#endif
	frame->Show(true);
	SetTopWindow(frame);

	return true;
}

/*! \mainpage Generic CAM - Developers Documentation
 *
 * \image html  pictures/start.png
 *
 */

