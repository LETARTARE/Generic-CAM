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

#include "Config.h"
#include "languages.h"
#include "gui/FrameParent.h"
#include "gui/FrameMain.h"
#include "project/Project.h"
#include "project/ProjectView.h"
#include "test/test.h"
#include <wx/aboutdlg.h>
#include <wx/splash.h>

#if wxUSE_DEBUG_CONTEXT == 1
#include  <wx/memory.h>
#endif

IMPLEMENT_APP(GenericCAMApp)
wxBEGIN_EVENT_TABLE(GenericCAMApp, wxApp)
EVT_MENU(wxID_ABOUT, GenericCAMApp::OnAbout)
wxEND_EVENT_TABLE()

void GenericCAMApp::OnAbout(wxCommandEvent&)
{
	wxAboutDialogInfo aboutInfo;

	aboutInfo.SetName(_T("Generic CAM"));
	aboutInfo.SetVersion(_T("0.3"));
	aboutInfo.SetDescription(_("CAM Processor for CNC Machines"));
	aboutInfo.SetCopyright(_T("(C) 2010-2020"));
	aboutInfo.SetWebSite(_T("https://sourceforge.net/projects/genericcam/"));
	aboutInfo.SetLicence(
			_T(
					"GNU General Public License version 3.0 (GPLv3)\n\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\n\nYou should have received a copy of the GNU General Public License along with this program.\nIf not, see http://www.gnu.org/licenses/."));
	aboutInfo.AddDeveloper(_T("Tobias Schäfer"));
	aboutInfo.AddTranslator(_T("Jacques-Louis Tartarin (French)"));
	aboutInfo.AddTranslator(_T("Sandro Dalle Nogare (Italian)"));

	wxAboutBox(aboutInfo);
}

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

	locale.AddCatalogLookupPathPrefix(_T("i18n"));
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
	printf("GenericCAMApp: Destructor called\n");
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
	parser.AddSwitch("t", "test", "Runs unit tests on some of the classes.");
	wxApp::OnInitCmdLine(parser);
}

bool GenericCAMApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	if(parser.FoundSwitch("t") == wxCMD_SWITCH_ON){
		TestAll();
		return false;
	}
	int count = parser.GetParamCount();
	if(count == 1){
		wxString str = parser.GetParam(0);
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
	parent->Show(false);

	if(loadOnStartup.IsEmpty()){
		docManager->CreateDocument(wxEmptyString, wxDOC_NEW);
	}else{
		docManager->CreateDocument(loadOnStartup, wxDOC_SILENT);
	}

	wxBitmap bitmap;
	if(bitmap.LoadFile(_T("doc/images/splash.png"), wxBITMAP_TYPE_PNG)){
		new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
				6000, parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
				wxSIMPLE_BORDER | wxSTAY_ON_TOP);
	}
	return true;
}

int GenericCAMApp::OnExit()
{
	printf("GenericCAMApp::OnExit called\n");
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

