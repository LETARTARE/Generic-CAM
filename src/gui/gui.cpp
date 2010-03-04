///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 21 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

GUIMainFrame::GUIMainFrame(wxWindow* parent, wxWindowID id,
		const wxString& title, const wxPoint& pos, const wxSize& size,
		long style) :
	wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_menubar = new wxMenuBar(0);
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem19;
	m_menuItem19
			= new wxMenuItem(m_menu1, wxID_EXIT, wxString(_("&Quit"))
					+ wxT('\t') + wxT("CTRL+Q"), _("Exit the program"),
					wxITEM_NORMAL);
	m_menu1->Append(m_menuItem19);

	m_menubar->Append(m_menu1, _("&File"));

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem(m_menu2, wxID_ANY, wxString(
			_("&Setup 6DOF controller")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem21);

	m_menubar->Append(m_menu2, _("&Settings"));

	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem39;
	m_menuItem39 = new wxMenuItem(m_menu3, wxID_ABOUT, wxString(_("&Info"))
			+ wxT('\t') + wxT("CTRL+I"), _("About the program"),
			wxITEM_NORMAL);
	m_menu3->Append(m_menuItem39);

	m_menubar->Append(m_menu3, _("&Help"));

	this->SetMenuBar(m_menubar);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_button1 = new wxButton(this, wxID_SELECTMACHINE, _("Select a machine"),
			wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button1, 0, wxALL | wxEXPAND, 5);

	m_button2 = new wxButton(this, wxID_ANY, _("Select data"),
			wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button2, 0, wxALL | wxEXPAND, 5);

	m_button3 = new wxButton(this, wxID_ANY, _("Select raw material"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_button3->Enable(false);

	bSizer1->Add(m_button3, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(bSizer1);
	this->Layout();


	// Connect Events
	this->Connect(m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMainFrame::OnQuit ));
	this->Connect(m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMainFrame::OnSetupController ));
	this->Connect(m_menuItem39->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMainFrame::OnAbout ));
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIMainFrame::OnSelectMachine ), NULL, this);
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIMainFrame::OnSelectData ), NULL, this);
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMainFrame::OnQuit ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMainFrame::OnSetupController ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMainFrame::OnAbout ));
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIMainFrame::OnSelectMachine ), NULL, this);
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIMainFrame::OnSelectData ), NULL, this);
}

GUIAboutDialog::GUIAboutDialog(wxWindow* parent, wxWindowID id,
		const wxString& title, const wxPoint& pos, const wxSize& size,
		long style) :
	wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	bSizer3->Add(0, 0, 1, wxEXPAND, 5);

	m_button1 = new wxButton(this, wxID_CLOSE, _("Close"), wxDefaultPosition,
			wxDefaultSize, 0);
	bSizer3->Add(m_button1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	this->SetSizer(bSizer3);
	this->Layout();


	// Connect Events
	m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIAboutDialog::OnClose ), NULL, this);
}

GUIAboutDialog::~GUIAboutDialog()
{
	// Disconnect Events
	m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIAboutDialog::OnClose ), NULL, this);
}

GUIMachineFrame::GUIMachineFrame(wxWindow* parent, wxWindowID id,
		const wxString& title, const wxPoint& pos, const wxSize& size,
		long style) :
	wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_menubar = new wxMenuBar(0);
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem(m_menuMachine, wxID_OPEN, wxString(
			_("&Load Machine")) + wxT('\t') + wxT("CTRL+L"),
			wxEmptyString, wxITEM_NORMAL);
	m_menuMachine->Append(m_menuItem11);

	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem(m_menuMachine, wxID_ANY, wxString(
			_("&Reload machine")) + wxT('\t') + wxT("CTRL+R"),
			wxEmptyString, wxITEM_NORMAL);
	m_menuMachine->Append(m_menuItem12);

	m_menuMachine->AppendSeparator();

	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem(m_menuMachine, wxID_CLOSE, wxString(
			_("&Close")) + wxT('\t') + wxT("CTRL+Q"), wxEmptyString,
			wxITEM_NORMAL);
	m_menuMachine->Append(m_menuItem19);

	m_menubar->Append(m_menuMachine, _("&Machine"));

	m_menuView = new wxMenu();
	wxMenuItem* m_menuItem25;
	m_menuItem25 = new wxMenuItem(m_menuView, wxID_VIEWSTEREO3D, wxString(
			_("&Stereo 3D")), wxEmptyString, wxITEM_CHECK);
	m_menuView->Append(m_menuItem25);

	m_menubar->Append(m_menuView, _("&View"));

	this->SetMenuBar(m_menubar);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_canvas = new MachineCanvas(this, wxID_ANY, wxDefaultPosition,
			wxDefaultSize);
	bSizer4->Add(m_canvas, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

	this->SetSizer(bSizer4);
	this->Layout();


	// Connect Events
	this->Connect(m_menuItem11->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnLoadMachine ));
	this->Connect(m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnReloadMachine ));
	this->Connect(m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnClose ));
	this->Connect(m_menuItem25->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnChangeStereo3D ));
}

GUIMachineFrame::~GUIMachineFrame()
{
	// Disconnect Events
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnLoadMachine ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnReloadMachine ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnClose ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIMachineFrame::OnChangeStereo3D ));
}

GUIDataFrame::GUIDataFrame(wxWindow* parent, wxWindowID id,
		const wxString& title, const wxPoint& pos, const wxSize& size,
		long style) :
	wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_menubar = new wxMenuBar(0);
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem(m_menuMachine, wxID_OPEN, wxString(
			_("&Load data...")) + wxT('\t') + wxT("CTRL+L"),
			wxEmptyString, wxITEM_NORMAL);
	m_menuMachine->Append(m_menuItem11);

	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem(m_menuMachine, wxID_SAVE, wxString(
			_("&Save data")) + wxT('\t') + wxT("CTRL+S"), wxEmptyString,
			wxITEM_NORMAL);
	m_menuMachine->Append(m_menuItem12);
	m_menuItem12->Enable(false);

	m_menuMachine->AppendSeparator();

	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem(m_menuMachine, wxID_CLOSE, wxString(
			_("&Close")) + wxT('\t') + wxT("CTRL+Q"), wxEmptyString,
			wxITEM_NORMAL);
	m_menuMachine->Append(m_menuItem19);

	m_menubar->Append(m_menuMachine, _("&Data"));

	m_menuView = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem(m_menuView, wxID_ANY, wxString(
			_("S&et scale...")), wxEmptyString, wxITEM_NORMAL);
	m_menuView->Append(m_menuItem21);

	wxMenuItem* m_menuItem25;
	m_menuItem25 = new wxMenuItem(m_menuView, wxID_VIEWSTEREO3D, wxString(
			_("&Stereo 3D")), wxEmptyString, wxITEM_CHECK);
	m_menuView->Append(m_menuItem25);

	m_menubar->Append(m_menuView, _("&View"));

	this->SetMenuBar(m_menubar);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_canvas = new DataCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	bSizer4->Add(m_canvas, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

	this->SetSizer(bSizer4);
	this->Layout();


	// Connect Events
	this->Connect(m_menuItem11->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnLoadSTLData ));
	this->Connect(m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnSaveData ));
	this->Connect(m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnClose ));
	this->Connect(m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnSetScale ));
	this->Connect(m_menuItem25->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnChangeStereo3D ));
}

GUIDataFrame::~GUIDataFrame()
{
	// Disconnect Events
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnLoadSTLData ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnSaveData ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnClose ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnSetScale ));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIDataFrame::OnChangeStereo3D ));
}

GUIControl6DOFDialog::GUIControl6DOFDialog(wxWindow* parent, wxWindowID id,
		const wxString& title, const wxPoint& pos, const wxSize& size,
		long style) :
	wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(-1, -1), wxSize(-1, -1));

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_staticText = new wxStaticText(this, wxID_ANY, _("Serial port:"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticText->Wrap(-1);
	bSizer1->Add(m_staticText, 0, wxALL, 5);

	textPort = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
			wxDefaultSize, 0);
	bSizer1->Add(textPort, 0, wxALL | wxEXPAND, 5);

	wxString radioDeviceSelectChoices[] =
		{_("SpaceBall"), _("SpaceOrb"), _("SpaceMouse")};
	int radioDeviceSelectNChoices = sizeof(radioDeviceSelectChoices)
			/ sizeof(wxString);
	radioDeviceSelect = new wxRadioBox(this, wxID_ANY, _("Type of controller"),
			wxDefaultPosition, wxDefaultSize, radioDeviceSelectNChoices,
			radioDeviceSelectChoices, 1, wxRA_SPECIFY_COLS);
	radioDeviceSelect->SetSelection(0);
	bSizer1->Add(radioDeviceSelect, 0, wxALL | wxEXPAND, 5);

	wxBoxSizer* bSizerTx;
	bSizerTx = new wxBoxSizer(wxHORIZONTAL);

	m_staticTextTx = new wxStaticText(this, wxID_ANY, _("Tx"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextTx->Wrap(-1);
	bSizerTx->Add(m_staticTextTx, 0, wxALIGN_CENTER_VERTICAL
			| wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_sliderTx = new wxSlider(this, wxID_ANY, 0, -1024, 1023,
			wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	m_sliderTx->Enable(false);

	bSizerTx->Add(m_sliderTx, 1, wxALL | wxALIGN_CENTER_VERTICAL
			| wxALIGN_CENTER_HORIZONTAL | wxEXPAND, 5);

	bSizer1->Add(bSizerTx, 1, wxEXPAND, 5);

	wxBoxSizer* bSizerTy;
	bSizerTy = new wxBoxSizer(wxHORIZONTAL);

	m_staticTextTy = new wxStaticText(this, wxID_ANY, _("Ty"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextTy->Wrap(-1);
	bSizerTy->Add(m_staticTextTy, 0, wxALL | wxALIGN_CENTER_HORIZONTAL
			| wxALIGN_CENTER_VERTICAL, 5);

	m_sliderTy = new wxSlider(this, wxID_ANY, 0, -1024, 1023,
			wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	m_sliderTy->Enable(false);

	bSizerTy->Add(m_sliderTy, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer1->Add(bSizerTy, 1, wxEXPAND, 5);

	wxBoxSizer* bSizerTz;
	bSizerTz = new wxBoxSizer(wxHORIZONTAL);

	m_staticTextTz = new wxStaticText(this, wxID_ANY, _("Tz"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextTz->Wrap(-1);
	bSizerTz->Add(m_staticTextTz, 0, wxALL | wxALIGN_CENTER_VERTICAL
			| wxALIGN_CENTER_HORIZONTAL, 5);

	m_sliderTz = new wxSlider(this, wxID_ANY, 0, -1024, 1023,
			wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	m_sliderTz->Enable(false);

	bSizerTz->Add(m_sliderTz, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer1->Add(bSizerTz, 1, wxEXPAND, 5);

	wxBoxSizer* bSizerRx;
	bSizerRx = new wxBoxSizer(wxHORIZONTAL);

	m_staticTextRx = new wxStaticText(this, wxID_ANY, _("Rx"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextRx->Wrap(-1);
	bSizerRx->Add(m_staticTextRx, 0, wxALL | wxALIGN_CENTER_HORIZONTAL
			| wxALIGN_CENTER_VERTICAL, 5);

	m_sliderRx = new wxSlider(this, wxID_ANY, 0, -1024, 1023,
			wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	m_sliderRx->Enable(false);

	bSizerRx->Add(m_sliderRx, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer1->Add(bSizerRx, 1, wxEXPAND, 5);

	wxBoxSizer* bSizerRy;
	bSizerRy = new wxBoxSizer(wxHORIZONTAL);

	m_staticTextRy = new wxStaticText(this, wxID_ANY, _("Ry"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextRy->Wrap(-1);
	bSizerRy->Add(m_staticTextRy, 0, wxALL | wxALIGN_CENTER_HORIZONTAL
			| wxALIGN_CENTER_VERTICAL, 5);

	m_sliderRy = new wxSlider(this, wxID_ANY, 0, -1024, 1023,
			wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	m_sliderRy->Enable(false);

	bSizerRy->Add(m_sliderRy, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer1->Add(bSizerRy, 1, wxEXPAND, 5);

	wxBoxSizer* bSizerRz;
	bSizerRz = new wxBoxSizer(wxHORIZONTAL);

	m_staticTextRz = new wxStaticText(this, wxID_ANY, _("Rz"),
			wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextRz->Wrap(-1);
	bSizerRz->Add(m_staticTextRz, 0, wxALL | wxALIGN_CENTER_HORIZONTAL
			| wxALIGN_CENTER_VERTICAL, 5);

	m_sliderRz = new wxSlider(this, wxID_ANY, 0, -1024, 1023,
			wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	m_sliderRz->Enable(false);

	bSizerRz->Add(m_sliderRz, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer1->Add(bSizerRz, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	buttonConnect = new wxButton(this, ID_BUTTONCONNECT, _("Connect"),
			wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(buttonConnect, 1, wxALL | wxEXPAND, 5);

	buttonDisconnect = new wxButton(this, ID_BUTTONDISCONNECT, _("Disconnect"),
			wxDefaultPosition, wxDefaultSize, 0);
	buttonDisconnect->Enable(false);

	bSizer2->Add(buttonDisconnect, 1, wxALL | wxEXPAND, 5);

	buttonClose = new wxButton(this, wxID_CLOSE, _("Close"), wxDefaultPosition,
			wxDefaultSize, 0);
	bSizer2->Add(buttonClose, 1, wxALL | wxEXPAND, 5);

	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	this->SetSizer(bSizer1);
	this->Layout();
	bSizer1->Fit(this);


	// Connect Events
	buttonConnect->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIControl6DOFDialog::OnConnect ), NULL,
			this);
	buttonDisconnect->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIControl6DOFDialog::OnDisconnect ), NULL,
			this);
	buttonClose->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIControl6DOFDialog::OnClose ), NULL, this);
}

GUIControl6DOFDialog::~GUIControl6DOFDialog()
{
	// Disconnect Events
	buttonConnect->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIControl6DOFDialog::OnConnect ), NULL,
			this);
	buttonDisconnect->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIControl6DOFDialog::OnDisconnect ), NULL,
			this);
	buttonClose->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIControl6DOFDialog::OnClose ), NULL, this);
}

GUIErrorFrame::GUIErrorFrame(wxWindow* parent, wxWindowID id,
		const wxString& title, const wxPoint& pos, const wxSize& size,
		long style) :
	wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
			wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxTE_AUTO_URL
					| wxTE_MULTILINE | wxTE_NOHIDESEL | wxTE_READONLY);
	bSizer->Add(m_textCtrl, 1, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

	m_button = new wxButton(this, wxID_CLOSE, _("&Close"), wxDefaultPosition,
			wxDefaultSize, 0);
	bSizer->Add(m_button, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	this->SetSizer(bSizer);
	this->Layout();
	m_menubar = new wxMenuBar(0);
	m_menu = new wxMenu();
	wxMenuItem* m_menuItem9;
	m_menuItem9 = new wxMenuItem(m_menu, wxID_CLOSE, wxString(
			_("&Close Window")) + wxT('\t') + wxT("CTRL+Q"),
			wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(m_menuItem9);

	m_menubar->Append(m_menu, _("Error"));

	this->SetMenuBar(m_menubar);


	// Connect Events
	m_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIErrorFrame::OnClose ), NULL, this);
	this->Connect(m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIErrorFrame::OnClose ));
}

GUIErrorFrame::~GUIErrorFrame()
{
	// Disconnect Events
	m_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler( GUIErrorFrame::OnClose ), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( GUIErrorFrame::OnClose ));
}
