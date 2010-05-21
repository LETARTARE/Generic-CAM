///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 21 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

GUIMainFrame::GUIMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuProject = new wxMenu();
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem( m_menuProject, wxID_OPEN, wxString( _("&Load Machine...") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem11 );
	
	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem( m_menuProject, wxID_ANY, wxString( _("&Reload machine") ) + wxT('\t') + wxT("CTRL+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem12 );
	
	m_menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItem13;
	m_menuItem13 = new wxMenuItem( m_menuProject, wxID_ANY, wxString( _("Load Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem13 );
	
	wxMenuItem* m_menuItem14;
	m_menuItem14 = new wxMenuItem( m_menuProject, wxID_ANY, wxString( _("Save Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem14 );
	
	wxMenuItem* m_menuItem15;
	m_menuItem15 = new wxMenuItem( m_menuProject, wxID_ANY, wxString( _("Edit Toolbox") ) + wxT('\t') + wxT("CTRL+T"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem15 );
	
	m_menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItem16;
	m_menuItem16 = new wxMenuItem( m_menuProject, wxID_ANY, wxString( _("L&oad G-Codes") ) + wxT('\t') + wxT("CTRL+G"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem16 );
	
	m_menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItem17;
	m_menuItem17 = new wxMenuItem( m_menuProject, wxID_ANY, wxString( _("&Show DataFrame") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem17 );
	
	m_menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem( m_menuProject, wxID_EXIT, wxString( _("&Quit") ) + wxT('\t') + wxT("CTRL+Q"), _("Exit the program"), wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem19 );
	
	m_menubar->Append( m_menuProject, _("&Project") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( _("&Setup 6DOF controller") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem21 );
	
	m_menubar->Append( m_menuSettings, _("&Settings") );
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItem31;
	m_menuItem31 = new wxMenuItem( m_menuView, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItem31 );
	
	m_menubar->Append( m_menuView, _("&View") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItem49;
	m_menuItem49 = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( _("&Info") ) + wxT('\t') + wxT("CTRL+I"), _("About the program"), wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItem49 );
	
	m_menubar->Append( m_menuHelp, _("&Help") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new MachineCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	bSizer1->Add( m_canvas, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItem11->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadMachine ) );
	this->Connect( m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnReloadMachine ) );
	this->Connect( m_menuItem13->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadToolbox ) );
	this->Connect( m_menuItem14->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveToolbox ) );
	this->Connect( m_menuItem15->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditToolbox ) );
	this->Connect( m_menuItem16->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadGCodes ) );
	this->Connect( m_menuItem17->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSelectDataFrame ) );
	this->Connect( m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Connect( m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupController ) );
	this->Connect( m_menuItem31->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeStereo3D ) );
	this->Connect( m_menuItem49->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadMachine ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnReloadMachine ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadGCodes ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSelectDataFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupController ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
}

GUIAboutDialog::GUIAboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl12 = new wxTextCtrl( this, wxID_ANY, _("Generic CAM  Copyright (C) 2010  Tobias Schaefer\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	bSizer3->Add( m_textCtrl12, 1, wxALL|wxEXPAND, 5 );
	
	m_button1 = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAboutDialog::OnClose ), NULL, this );
}

GUIAboutDialog::~GUIAboutDialog()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAboutDialog::OnClose ), NULL, this );
}

GUIDataFrame::GUIDataFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem( m_menuMachine, wxID_OPEN, wxString( _("&Load data...") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItem11 );
	
	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem( m_menuMachine, wxID_SAVE, wxString( _("&Save data") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItem12 );
	m_menuItem12->Enable( false );
	
	m_menuMachine->AppendSeparator();
	
	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem( m_menuMachine, wxID_CLOSE, wxString( _("&Close") ) + wxT('\t') + wxT("CTRL+Q"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItem19 );
	
	m_menubar->Append( m_menuMachine, _("&Data") );
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("S&et scale...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem25;
	m_menuItem25 = new wxMenuItem( m_menuView, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItem25 );
	
	m_menubar->Append( m_menuView, _("&View") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new DataCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	bSizer4->Add( m_canvas, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItem11->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnLoadSTLData ) );
	this->Connect( m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnSaveData ) );
	this->Connect( m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnClose ) );
	this->Connect( m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnSetScale ) );
	this->Connect( m_menuItem25->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnChangeStereo3D ) );
}

GUIDataFrame::~GUIDataFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnLoadSTLData ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnSaveData ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnSetScale ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIDataFrame::OnChangeStereo3D ) );
}

GUIControl6DOFDialog::GUIControl6DOFDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText = new wxStaticText( this, wxID_ANY, _("Serial port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	bSizer1->Add( m_staticText, 0, wxALL, 5 );
	
	textPort = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( textPort, 0, wxALL|wxEXPAND, 5 );
	
	wxString radioDeviceSelectChoices[] = { _("SpaceBall"), _("SpaceOrb"), _("SpaceMouse") };
	int radioDeviceSelectNChoices = sizeof( radioDeviceSelectChoices ) / sizeof( wxString );
	radioDeviceSelect = new wxRadioBox( this, wxID_ANY, _("Type of controller"), wxDefaultPosition, wxDefaultSize, radioDeviceSelectNChoices, radioDeviceSelectChoices, 1, wxRA_SPECIFY_COLS );
	radioDeviceSelect->SetSelection( 0 );
	bSizer1->Add( radioDeviceSelect, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTx;
	bSizerTx = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTx = new wxStaticText( this, wxID_ANY, _("Tx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTx->Wrap( -1 );
	bSizerTx->Add( m_staticTextTx, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_sliderTx = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTx->Enable( false );
	
	bSizerTx->Add( m_sliderTx, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizerTx, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTy;
	bSizerTy = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTy = new wxStaticText( this, wxID_ANY, _("Ty"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTy->Wrap( -1 );
	bSizerTy->Add( m_staticTextTy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderTy = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTy->Enable( false );
	
	bSizerTy->Add( m_sliderTy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerTy, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTz;
	bSizerTz = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTz = new wxStaticText( this, wxID_ANY, _("Tz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTz->Wrap( -1 );
	bSizerTz->Add( m_staticTextTz, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderTz = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTz->Enable( false );
	
	bSizerTz->Add( m_sliderTz, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerTz, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRx;
	bSizerRx = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRx = new wxStaticText( this, wxID_ANY, _("Rx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRx->Wrap( -1 );
	bSizerRx->Add( m_staticTextRx, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRx = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRx->Enable( false );
	
	bSizerRx->Add( m_sliderRx, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerRx, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRy;
	bSizerRy = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRy = new wxStaticText( this, wxID_ANY, _("Ry"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRy->Wrap( -1 );
	bSizerRy->Add( m_staticTextRy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRy = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRy->Enable( false );
	
	bSizerRy->Add( m_sliderRy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerRy, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRz;
	bSizerRz = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRz = new wxStaticText( this, wxID_ANY, _("Rz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRz->Wrap( -1 );
	bSizerRz->Add( m_staticTextRz, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRz = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRz->Enable( false );
	
	bSizerRz->Add( m_sliderRz, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerRz, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	buttonConnect = new wxButton( this, ID_BUTTONCONNECT, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( buttonConnect, 1, wxALL|wxEXPAND, 5 );
	
	buttonDisconnect = new wxButton( this, ID_BUTTONDISCONNECT, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonDisconnect->Enable( false );
	
	bSizer2->Add( buttonDisconnect, 1, wxALL|wxEXPAND, 5 );
	
	buttonClose = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( buttonClose, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControl6DOFDialog::OnConnect ), NULL, this );
	buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControl6DOFDialog::OnDisconnect ), NULL, this );
	buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControl6DOFDialog::OnClose ), NULL, this );
}

GUIControl6DOFDialog::~GUIControl6DOFDialog()
{
	// Disconnect Events
	buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControl6DOFDialog::OnConnect ), NULL, this );
	buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControl6DOFDialog::OnDisconnect ), NULL, this );
	buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControl6DOFDialog::OnClose ), NULL, this );
}

GUIErrorFrame::GUIErrorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_AUTO_URL|wxTE_MULTILINE|wxTE_NOHIDESEL|wxTE_READONLY );
	bSizer->Add( m_textCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_button = new wxButton( this, wxID_CLOSE, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer );
	this->Layout();
	m_menubar = new wxMenuBar( 0 );
	m_menu = new wxMenu();
	wxMenuItem* m_menuItem9;
	m_menuItem9 = new wxMenuItem( m_menu, wxID_CLOSE, wxString( _("&Close Window") ) + wxT('\t') + wxT("CTRL+Q"), wxEmptyString, wxITEM_NORMAL );
	m_menu->Append( m_menuItem9 );
	
	m_menubar->Append( m_menu, _("Error") );
	
	this->SetMenuBar( m_menubar );
	
	
	// Connect Events
	m_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIErrorFrame::OnClose ), NULL, this );
	this->Connect( m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIErrorFrame::OnClose ) );
}

GUIErrorFrame::~GUIErrorFrame()
{
	// Disconnect Events
	m_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIErrorFrame::OnClose ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIErrorFrame::OnClose ) );
}

GUIToolboxFrame::GUIToolboxFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuTools = new wxMenu();
	wxMenuItem* m_menuItem15;
	m_menuItem15 = new wxMenuItem( m_menuTools, wxID_ANY, wxString( _("&Load Toolbox") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem15 );
	m_menuItem15->Enable( false );
	
	wxMenuItem* m_menuItem16;
	m_menuItem16 = new wxMenuItem( m_menuTools, wxID_ANY, wxString( _("&Save Toolbox") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem16 );
	m_menuItem16->Enable( false );
	
	wxMenuItem* m_menuItem17;
	m_menuItem17 = new wxMenuItem( m_menuTools, wxID_CLOSE, wxString( _("Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem17 );
	
	m_menubar->Append( m_menuTools, _("&Tools") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem18;
	m_menuItem18 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( _("&Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem18 );
	
	wxMenuItem* m_menuItem25;
	m_menuItem25 = new wxMenuItem( m_menuSettings, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem25 );
	
	m_menubar->Append( m_menuSettings, _("&Settings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBoxToolSelector = new wxComboBox( this, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer14->Add( m_comboBoxToolSelector, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_button6 = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_button6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_button7 = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_button7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button8 = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_button8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer13->Add( bSizer14, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->AddGrowableRow( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool definition") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 5, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Shaft diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftDiameter = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlShaftDiameter->SetToolTip( _("Diameter of the part that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftDiameter, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Shaft length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftLength = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlShaftLength->SetToolTip( _("This is the length of the that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftLength, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("Maximum speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer1->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlMaxSpeed->SetToolTip( _("Max. speed: Look at label on box you got the tools shipped in.") );
	
	fgSizer1->Add( m_textCtrlMaxSpeed, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer1->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Feed coefficient"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFeedCoefficient = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlFeedCoefficient->SetToolTip( _("Feed per tooth: How deep can a tooth cut per revolution. Usually in the range of 0.02 mm to 0.05 mm.") );
	
	fgSizer1->Add( m_textCtrlFeedCoefficient, 0, wxALL, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer1->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Number of teeth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer1->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlNrOfTeeth = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlNrOfTeeth->SetToolTip( _("Number of teeth around the cutter.") );
	
	fgSizer1->Add( m_textCtrlNrOfTeeth, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer1->Add( m_staticText17, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( fgSizer1, 0, 0, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	sbSizer1->Add( m_staticText26, 0, wxALL, 5 );
	
	m_textCtrlComment = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	sbSizer1->Add( m_textCtrlComment, 1, wxALL|wxEXPAND, 5 );
	
	fgSizer3->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	m_panel=new ToolPanel(this);
	fgSizer3->Add( m_panel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool shape") ), wxVERTICAL );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button11 = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_button11, 0, wxALL, 5 );
	
	m_button10 = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_button10, 0, wxALL, 5 );
	
	m_button9 = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_button9, 0, wxALL, 5 );
	
	bSizer16->Add( bSizer17, 0, 0, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Linear or bend line"), _("Corner: first diameter change, then height change"), _("Corner: first height change, then diameter change"), _("Sphere: radius at upper limit, calculate height"), _("Sphere: radius at lower limit, calculate height") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	bSizer16->Add( m_choiceType, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, _("Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDiameter = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlDiameter->SetToolTip( _("Diameter of the tool at the end of this segment.") );
	
	fgSizer2->Add( m_textCtrlDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer2->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlHeight->SetToolTip( _("Height of this segment.") );
	
	fgSizer2->Add( m_textCtrlHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRadius = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlRadius->SetToolTip( _("Radius of curvature:\r\nPositive radius = convex surface = bulged to the outside.\r\nNegative radius = concave surface = bulged to the inside.\r\nRadius of 0 = straight line. ") );
	
	fgSizer2->Add( m_textCtrlRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText24 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer2->Add( m_staticText24, 0, wxALL, 5 );
	
	m_checkBoxCutting = new wxCheckBox( this, wxID_ANY, _("surface is cutting"), wxDefaultPosition, wxDefaultSize, 0 );
	
	fgSizer2->Add( m_checkBoxCutting, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer2->Add( m_staticText25, 0, wxALL, 5 );
	
	bSizer16->Add( fgSizer2, 0, 0, 5 );
	
	bSizer15->Add( bSizer16, 0, 0, 5 );
	
	m_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer15->Add( m_listCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	sbSizer2->Add( bSizer15, 1, wxEXPAND, 5 );
	
	fgSizer3->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	m_canvas = new ToolCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	fgSizer3->Add( m_canvas, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer13->Add( fgSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer13 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItem17->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnClose ) );
	this->Connect( m_menuItem25->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnChangeStereo3D ) );
}

GUIToolboxFrame::~GUIToolboxFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnChangeStereo3D ) );
}
