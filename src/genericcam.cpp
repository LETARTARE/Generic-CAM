///////////////////////////////////////////////////////////////////////////////
// Name               : genericcam.cpp
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

#include "genericcam.h"
#include "languages.h"

#include "wx/richtext/richtextxml.h"

#include "gui/FrameParent.h"
#include "project/ProjectView.h"
#if wxUSE_DEBUG_CONTEXT == 1
#include  <wx/memory.h>
#endif

// The line that starts it all.
IMPLEMENT_APP(GenericCAMApp)

GenericCAMApp::GenericCAMApp()
{
	config = new wxConfig(_T("genericcam"));

	unsigned int selectedLanguage = wxLocale::GetSystemLanguage();
	if(selectedLanguage == wxLANGUAGE_UNKNOWN) selectedLanguage =
			wxLANGUAGE_DEFAULT;

	// Read language from config.
	wxString str;
	if(config->Read(_T("Language"), &str)){
		unsigned int i;
		for(i = 0; i < WXSIZEOF(langNames); i++)
			if(str.CmpNoCase(langNames[i]) == 0){
				selectedLanguage = langIds[i];
			}
	}

	if(!locale.Init(selectedLanguage, wxLOCALE_DONT_LOAD_DEFAULT)){
		wxLogWarning
		(_T("This language is not supported by the system."));
		return;
	}

	//	wxLogMessage(wxString::Format(_T("id language : %u " ), selectedLanguage));
	//	wxLogMessage(wxString::Format(_T("id language : %u " ),
	//			locale.GetLanguage()));
	//	wxLogMessage(_T("name language :") + locale.GetCanonicalName());

	locale.AddCatalogLookupPathPrefix(_T("./i18n"));
	bool catalogLoaded = locale.AddCatalog(_T("GenericCAM"));
	if(!catalogLoaded){
		wxString temp;
		temp =
		_T("The translation catalog for ") + locale.GetCanonicalName() +
		_T(" was not loaded !");
		wxLogWarning
		(temp);
	}
	locale.AddCatalog("wxstd");
}

GenericCAMApp::~GenericCAMApp(void)
{
#if wxUSE_DEBUG_CONTEXT == 1
	wxDebugContext::PrintStatistics(true);
#endif
	delete config; // config is written back on deletion of object
}

// The Commandline is parsed before OnInit is called.
void GenericCAMApp::OnInitCmdLine(wxCmdLineParser& parser)
{
	parser.AddParam(_("<filepath of document to open>"), wxCMD_LINE_VAL_STRING,
			wxCMD_LINE_PARAM_OPTIONAL);
	wxApp::OnInitCmdLine(parser);
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

	SetAppName("genericcam");
	SetAppDisplayName("Generic CAM");

	wxDocManager *docManager = new wxDocManager;

	new wxDocTemplate(docManager, "Generic CAM Project", "*.zip", "", "zip",
			"Project", "Project View", CLASSINFO(Project),
			CLASSINFO(ProjectView));

#if defined( __WXMAC__ )  && wxOSX_USE_CARBON
	wxFileName::MacRegisterDefaultTypeAndCreator("zip" , 'WXMB' , 'WXMA'); // ?
#endif

	docManager->FileHistoryLoad(*config);

	wxFrame* parent;
	parent = new FrameParent(docManager, config, NULL, wxID_ANY,
			GetAppDisplayName());

	SetTopWindow(parent);
	parent->Show(true);

	Project* project;
	if(loadOnStartup.IsEmpty()){
		project = (Project*) docManager->CreateDocument(wxEmptyString,
				wxDOC_NEW);
	}else{
		project = (Project*) docManager->CreateDocument(loadOnStartup,
				wxDOC_SILENT);
	}

	// Show release notes
//	wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
//	StartupText * temp = new StartupText(frame);
//	temp->m_richText->LoadFile(_T("releasenote.xml"), wxRICHTEXT_TYPE_XML);
	//	temp->Show();

	return true;
}

int GenericCAMApp::OnExit()
{
	wxDocManager* const docManager = wxDocManager::GetDocumentManager();
	docManager->FileHistorySave(*config);
	delete docManager;
	return wxApp::OnExit();
}

wxFrame* GenericCAMApp::CreateChildFrame(wxView* view)
{
	wxDocument *doc = view->GetDocument();
	wxFrame *subframe = new FrameMain(doc, view, config,
			wxStaticCast(GetTopWindow(), wxDocParentFrame));
	return subframe;
}
