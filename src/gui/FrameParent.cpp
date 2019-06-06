///////////////////////////////////////////////////////////////////////////////
// Name               : FrameParent.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.10.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "FrameParent.h"

#include "../StdInclude.h"
#include <wx/generic/choicdgg.h>
#include <cstdio>
#include "../languages.h"
#include "../project/ProjectView.h"
#include "IDs.h"
#ifdef _USE_6DOFCONTROLLER
#include "../controller/DialogSetup6DOFController.h"
#endif

wxBEGIN_EVENT_TABLE(FrameParent, wxDocParentFrame)

EVT_MENU(ID_SETUPLANGUAGE , FrameParent::OnChangeLanguage)
EVT_MENU(ID_SETUPUNITS , FrameParent::OnSetupUnits)
EVT_MENU(ID_SETUPSTEREO3D , FrameParent::OnSetupStereo3D)
#ifdef _USE_6DOFCONTROLLER
EVT_MENU(ID_SETUPCONTROLLER , FrameParent::OnSetupController)
#endif
#ifdef _USE_MIDI
EVT_MENU(ID_SETUPMIDI , FrameParent::OnSetupMidi)
#endif
EVT_MENU(wxID_ABOUT, FrameParent::OnAbout)
EVT_MENU(wxID_HELP, FrameParent::OnHelp)

EVT_MENU(ID_REFRESHALL, FrameParent::OnRefreshAll)
EVT_MENU(ID_REFRESHALL3DVIEW, FrameParent::OnRefreshAll3D)
EVT_MENU(ID_REFRESHVIEW, FrameParent::OnRefreshView)
EVT_MENU(ID_REFRESH3DVIEW, FrameParent::OnRefreshView3D)
wxEND_EVENT_TABLE()

FrameParent::FrameParent(wxDocManager *manager, wxConfig* config,
		wxFrame *parent, wxWindowID id, const wxString& title) :
		wxDocParentFrame(manager, parent, id, title)
{
	this->config = config;
	settingsStereo3D.Load(config);
	units.Load(config);
#ifdef _USE_6DOFCONTROLLER
	control.GetConfigFrom(config);
#endif
	wxMenu *m_menuFile = new wxMenu;
	m_menuFile->Append(wxID_NEW);
	m_menuFile->Append(wxID_OPEN);
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_PRINT_SETUP, "Print &Setup...");
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_EXIT);

	wxMenu *m_menuPreferences = new wxMenu;
	m_menuPreferences->Append(ID_SETUPLANGUAGE, _T("Change Language"));
#ifdef _USE_6DOFCONTROLLER
	m_menuPreferences->Append(ID_SETUPCONTROLLER, _("Setup 6DOF &Controller"));
#endif
	m_menuPreferences->Append(ID_SETUPSTEREO3D, _("Setup &Stereo 3D"));
#ifdef _USE_MIDI
	m_menuPreferences->Append(ID_SETUPMIDI, _("Setup &MIDI"));
#endif
	m_menuPreferences->Append(ID_SETUPUNITS,
	_("Setup &Units") + wxT("\tCtrl+U"));

	wxMenu *m_menuHelp = new wxMenu;
	m_menuHelp->Append(wxID_HELP, _("&Help") + wxT("\tF1"));
	m_menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menubar = new wxMenuBar;
	menubar->Append(m_menuFile, wxGetStockLabel(wxID_FILE));
	menubar->Append(m_menuPreferences, wxGetStockLabel(wxID_PREFERENCES));
	menubar->Append(m_menuHelp, wxGetStockLabel(wxID_HELP));

	SetMenuBar(menubar);

	m_helpController = new wxHelpController();

	dialogSetupStereo3D = new DialogSetupStereo3D(this, &settingsStereo3D,
			&units);
#ifdef _USE_MIDI
	dialogSetupMidi = new DialogSetupMidi(this, &midi);
#endif
	//TODO Logging is disable here, because the SESSION_MANAGER variable is not defined since Ubuntu 16.04.
	// The initialisation of the help controller will always lead to the message:
	// 	Debug: Failed to connect to session manager: SESSION_MANAGER environment variable not defined
	wxLog::EnableLogging(false);
	m_helpController->Initialize(_T("doc/help/help.hhp"));
	wxLog::EnableLogging(true);

	timer.SetOwner(this);

	t = 0.0;
	dt = 50e-3; // s
	timer.Start(round(dt * 1000.0)); // ms

	this->Connect(wxEVT_TIMER, wxTimerEventHandler(FrameParent::OnTimer), NULL,
			this);
}

FrameParent::~FrameParent()
{
	printf("FrameParent: Destructor called\n");

#ifdef _USE_6DOFCONTROLLER
	// Save the configuration of the 6DOF controller
	control.WriteConfigTo(config);
#endif
	settingsStereo3D.Save(config);
	units.Save(config);

	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(FrameParent::OnTimer),
	NULL, this);

	delete m_helpController;
}

void FrameParent::OnAbout(wxCommandEvent&)
{
	GUIDialogAbout dialog(this);
	dialog.ShowModal();
}

void FrameParent::OnHelp(wxCommandEvent&)
{
	m_helpController->DisplayContents();
}

void FrameParent::OnTimer(wxTimerEvent& event)
{
	t += dt;

//	wxString temp;
//	temp = wxString::Format(_T("Free RAM: %lu MB"),
//			GetFreeSystemMemory() / 1024 / 1024);
//
//	m_statusBar->SetStatusText(temp, 1);

//	if(project.processToolpath){
//		if(project.GenerateToolpaths()) TransferDataToWindow();
//	}
}

void FrameParent::OnChangeLanguage(wxCommandEvent& event)
{
	long lng =
			wxGetSingleChoiceIndex(
					_T(
							"Please choose language:\nChanges will take place after restart!"),
					_T("Language"), WXSIZEOF(langNames), langNames);
	if(lng >= 0) config->Write(_T("Language"), langNames[lng]);
}
#ifdef _USE_6DOFCONTROLLER
void FrameParent::OnSetupController(wxCommandEvent& event)
{
	DialogSetup6DOFController temp(this);
	temp.InsertController(control);
	temp.ShowModal();
}
#endif
void FrameParent::OnSetupStereo3D(wxCommandEvent& event)
{
	dialogSetupStereo3D->Show(true);
	dialogSetupStereo3D->Raise();
}
#ifdef _USE_MIDI
void FrameParent::OnSetupMidi(wxCommandEvent& event)
{
	dialogSetupMidi->Show(true);
	dialogSetupMidi->Raise();
}
#endif
void FrameParent::OnSetupUnits(wxCommandEvent& event)
{
	DialogSetupUnits * temp = new DialogSetupUnits(this, &units);
	temp->Show();
	temp->Raise();
}

void FrameParent::OnRefreshAll(wxCommandEvent& event)
{
	wxDocManager * mgr = GetDocumentManager();
	wxDocVector docs = mgr->GetDocumentsVector();
	for(size_t i = 0; i < docs.size(); ++i)
		docs[i]->UpdateAllViews();
}

void FrameParent::OnRefreshAll3D(wxCommandEvent& event)
{
	wxDocManager * mgr = GetDocumentManager();
	wxDocVector docs = mgr->GetDocumentsVector();
	for(size_t i = 0; i < docs.size(); ++i){
		wxViewVector views = docs[i]->GetViewsVector();
		for(size_t j = 0; j < views.size(); ++j){
			ProjectView* projectview = wxStaticCast(views[j], ProjectView);
			projectview->OnUpdate3D();
		}
	}
}

void FrameParent::OnRefreshView(wxCommandEvent& event)
{
	wxDocManager * mgr = GetDocumentManager();
	wxDocument * doc = mgr->GetCurrentDocument();
	if(doc != NULL) doc->UpdateAllViews();
}

void FrameParent::OnRefreshView3D(wxCommandEvent& event)
{
	wxDocManager * mgr = GetDocumentManager();
	wxDocument * doc = mgr->GetCurrentDocument();
	wxViewVector views = doc->GetViewsVector();
	for(size_t i = 0; i < views.size(); ++i){
		ProjectView* projectview = wxStaticCast(views[i], ProjectView);
		projectview->OnUpdate3D();
	}
}
