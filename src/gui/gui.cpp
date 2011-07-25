///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
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
	wxMenuItem* m_menuItem35;
	m_menuItem35 = new wxMenuItem( m_menuProject, wxID_NEW, wxString( _("&Create new project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem35 );
	
	wxMenuItem* m_menuItem36;
	m_menuItem36 = new wxMenuItem( m_menuProject, wxID_OPEN, wxString( _("&Load Project...") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem36 );
	
	wxMenuItem* m_menuItem37;
	m_menuItem37 = new wxMenuItem( m_menuProject, wxID_SAVEAS, wxString( _("&Save Project as...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem37 );
	
	wxMenuItem* m_menuItem371;
	m_menuItem371 = new wxMenuItem( m_menuProject, wxID_SAVE, wxString( _("&Save Project") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem371 );
	
	wxMenuItem* m_separator4;
	m_separator4 = m_menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem( m_menuProject, wxID_EXIT, wxString( _("&Quit") ) + wxT('\t') + wxT("CTRL+Q"), _("Exit the program"), wxITEM_NORMAL );
	m_menuProject->Append( m_menuItem19 );
	
	m_menubar->Append( m_menuProject, _("&Project") );
	
	m_menuObject = new wxMenu();
	wxMenuItem* m_menuItem17;
	m_menuItem17 = new wxMenuItem( m_menuObject, wxID_ANY, wxString( _("&Load Object File") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItem17 );
	
	wxMenuItem* m_menuItem38;
	m_menuItem38 = new wxMenuItem( m_menuObject, wxID_ANY, wxString( _("&Modify Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItem38 );
	
	wxMenuItem* m_menuItem421;
	m_menuItem421 = new wxMenuItem( m_menuObject, wxID_ANY, wxString( _("Edit Subobjects") ) , _("For DXF files"), wxITEM_NORMAL );
	m_menuObject->Append( m_menuItem421 );
	m_menuItem421->Enable( false );
	
	wxMenuItem* m_menuItem431;
	m_menuItem431 = new wxMenuItem( m_menuObject, wxID_GENERATETARGET, wxString( _("&Generate Targets") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItem431 );
	
	m_menubar->Append( m_menuObject, _("&Object") );
	
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Load Machine...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItem11 );
	
	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Reload machine") ) + wxT('\t') + wxT("CTRL+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItem12 );
	
	m_menubar->Append( m_menuMachine, _("&Machine") );
	
	m_menuToolbox = new wxMenu();
	wxMenuItem* m_menuItem15;
	m_menuItem15 = new wxMenuItem( m_menuToolbox, wxID_ANY, wxString( _("Edit Toolbox") ) + wxT('\t') + wxT("CTRL+T"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItem15 );
	
	wxMenuItem* m_menuItem13;
	m_menuItem13 = new wxMenuItem( m_menuToolbox, wxID_ANY, wxString( _("Load Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItem13 );
	
	wxMenuItem* m_menuItem14;
	m_menuItem14 = new wxMenuItem( m_menuToolbox, wxID_ANY, wxString( _("Save Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItem14 );
	
	m_menubar->Append( m_menuToolbox, _("&Toolbox") );
	
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItem44;
	m_menuItem44 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Organize Stock") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem44 );
	
	wxMenuItem* m_menuItem43;
	m_menuItem43 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Load Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem43 );
	
	wxMenuItem* m_menuItem42;
	m_menuItem42 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Save Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem42 );
	
	m_menubar->Append( m_menuStock, _("&Stock") );
	
	m_menuToolpath = new wxMenu();
	wxMenuItem* m_menuItem47;
	m_menuItem47 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Generate Toolpaths") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem47 );
	
	wxMenuItem* m_menuItem48;
	m_menuItem48 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Flip Run") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem48 );
	
	wxMenuItem* m_separator7;
	m_separator7 = m_menuToolpath->AppendSeparator();
	
	wxMenuItem* m_menuItem491;
	m_menuItem491 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Prepare Machinebed") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem491 );
	
	wxMenuItem* m_separator5;
	m_separator5 = m_menuToolpath->AppendSeparator();
	
	wxMenuItem* m_menuItem16;
	m_menuItem16 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("L&oad G-Codes") ) + wxT('\t') + wxT("CTRL+G"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem16 );
	
	wxMenuItem* m_menuItem441;
	m_menuItem441 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Save G-Codes") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem441 );
	
	m_menubar->Append( m_menuToolpath, _("Tool&path") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menuSettings, wxID_SETUPCONTROLLER, wxString( _("Setup 6DOF &controller") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem22;
	m_menuItem22 = new wxMenuItem( m_menuSettings, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem22 );
	
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	wxMenuItem* m_menuItem46;
	m_menuItem46 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( _("Show &Animation Control") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem46 );
	
	m_menubar->Append( m_menuSettings, _("S&ettings") );
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemTop;
	m_menuItemTop = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Top") ) + wxT('\t') + wxT("CTRL+8"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemTop );
	
	wxMenuItem* m_menuItemBottom;
	m_menuItemBottom = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Bottom") ) + wxT('\t') + wxT("CTRL+2"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemBottom );
	
	wxMenuItem* m_menuItemFront;
	m_menuItemFront = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Front") ) + wxT('\t') + wxT("CTRL+5"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemFront );
	
	wxMenuItem* m_menuItemBack;
	m_menuItemBack = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Back") ) + wxT('\t') + wxT("CTRL+0"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemBack );
	
	wxMenuItem* m_menuItemLeft;
	m_menuItemLeft = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Left") ) + wxT('\t') + wxT("CTRL+4"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemLeft );
	
	wxMenuItem* m_menuItemRight;
	m_menuItemRight = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Right") ) + wxT('\t') + wxT("CTRL+6"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemRight );
	
	m_menubar->Append( m_menuView, _("&View") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItem49;
	m_menuItem49 = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( _("&About") ) + wxT('\t') + wxT("CTRL+A"), _("About the program"), wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItem49 );
	
	m_menubar->Append( m_menuHelp, _("&Help") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE );
	m_splitter->SetMinimumPaneSize( 100 );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIMainFrame::m_splitterOnIdle ), NULL, this );
	m_panel1 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	tree = new wxTreeCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS|wxTR_HAS_BUTTONS|wxTR_HIDE_ROOT|wxTR_SINGLE );
	bSizer19->Add( tree, 1, wxALL|wxEXPAND, 5 );
	
	m_panel1->SetSizer( bSizer19 );
	m_panel1->Layout();
	bSizer19->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new MainCanvas(m_panel2);
	bSizer18->Add( m_canvas, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_panel2->SetSizer( bSizer18 );
	m_panel2->Layout();
	bSizer18->Fit( m_panel2 );
	m_splitter->SplitVertically( m_panel1, m_panel2, 144 );
	bSizer1->Add( m_splitter, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItem35->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnCreateProject ) );
	this->Connect( m_menuItem36->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadProject ) );
	this->Connect( m_menuItem37->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProjectAs ) );
	this->Connect( m_menuItem371->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProject ) );
	this->Connect( m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Connect( m_menuItem17->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadObject ) );
	this->Connect( m_menuItem38->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnModifyObject ) );
	this->Connect( m_menuItem431->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnGenerateTargets ) );
	this->Connect( m_menuItem11->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadMachine ) );
	this->Connect( m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnReloadMachine ) );
	this->Connect( m_menuItem15->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditToolbox ) );
	this->Connect( m_menuItem13->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadToolbox ) );
	this->Connect( m_menuItem14->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveToolbox ) );
	this->Connect( m_menuItem44->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditStock ) );
	this->Connect( m_menuItem47->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnGenerateToolpath ) );
	this->Connect( m_menuItem48->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnFlipRun ) );
	this->Connect( m_menuItem491->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnPrepareMachinebed ) );
	this->Connect( m_menuItem16->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadGCodes ) );
	this->Connect( m_menuItem441->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveGCodes ) );
	this->Connect( m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupController ) );
	this->Connect( m_menuItem22->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeStereo3D ) );
	this->Connect( m_menuItem23->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupUnits ) );
	this->Connect( m_menuItem46->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnShowAnimationFrame ) );
	this->Connect( m_menuItem49->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
	tree->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnBeginLabelEdit ), NULL, this );
	tree->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnEndLabelEdit ), NULL, this );
	tree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIMainFrame::OnActivateRightClickMenu ), NULL, this );
	tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIMainFrame::OnSelectionChanged ), NULL, this );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnCreateProject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadProject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProjectAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadObject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnModifyObject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnGenerateTargets ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadMachine ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnReloadMachine ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditStock ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnGenerateToolpath ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnFlipRun ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnPrepareMachinebed ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadGCodes ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveGCodes ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupController ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupUnits ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnShowAnimationFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
	tree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnBeginLabelEdit ), NULL, this );
	tree->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnEndLabelEdit ), NULL, this );
	tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIMainFrame::OnActivateRightClickMenu ), NULL, this );
	tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIMainFrame::OnSelectionChanged ), NULL, this );
}

GUIAboutDialog::GUIAboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl12 = new wxTextCtrl( this, wxID_ANY, _("Generic CAM  Copyright (C) 2010  Tobias Schaefer\n\nLicence for Generic CAM:\nGNU General Public License version 3.0 (GPLv3)\n\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\n\nYou should have received a copy of the GNU General Public License along with this program. \nIf not, see <http://www.gnu.org/licenses/>."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
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
	
	wxMenuItem* m_separator3;
	m_separator3 = m_menuTools->AppendSeparator();
	
	wxMenuItem* m_menuItem17;
	m_menuItem17 = new wxMenuItem( m_menuTools, wxID_CLOSE, wxString( _("&Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem17 );
	
	m_menubar->Append( m_menuTools, _("&Tools") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem22;
	m_menuItem22 = new wxMenuItem( m_menuSettings, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem22 );
	
	m_menubar->Append( m_menuSettings, _("&Settings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBoxToolSelector = new wxComboBox( this, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer14->Add( m_comboBoxToolSelector, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonToolNew = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonToolNew, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonToolUpdate = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonToolUpdate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonToolDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonToolDelete, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
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
	
	m_staticTextUnitShaftDiameter = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftDiameter->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitShaftDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Shaft length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftLength = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlShaftLength->SetToolTip( _("This is the length of the that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftLength, 0, wxALL, 5 );
	
	m_staticTextUnitShaftLength = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftLength->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitShaftLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("Maximum speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer1->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlMaxSpeed->SetToolTip( _("Max. speed: Look at label on box you got the tools shipped in.") );
	
	fgSizer1->Add( m_textCtrlMaxSpeed, 0, wxALL, 5 );
	
	m_staticTextUnitMaxSpeed = new wxStaticText( this, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMaxSpeed->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Feed coefficient"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFeedCoefficient = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlFeedCoefficient->SetToolTip( _("Feed per tooth: How deep can a tooth cut per revolution. Usually in the range of 0.02 mm to 0.05 mm.") );
	
	fgSizer1->Add( m_textCtrlFeedCoefficient, 0, wxALL, 5 );
	
	m_staticTextUnitFeedCoefficient = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedCoefficient->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitFeedCoefficient, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
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
	
	m_buttonShapeNew = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_buttonShapeNew, 0, wxALL, 5 );
	
	m_buttonShapeUpdate = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_buttonShapeUpdate, 0, wxALL, 5 );
	
	m_buttonShapeDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_buttonShapeDelete, 0, wxALL, 5 );
	
	bSizer16->Add( bSizer17, 0, 0, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Linear or bend line"), _("Corner: first diameter change, then height change"), _("Corner: first height change, then diameter change"), _("Sphere: radius at upper limit, calculate height"), _("Sphere: radius at lower limit, calculate height") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 4 );
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
	
	m_staticTextUnitDiameter = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlHeight->SetToolTip( _("Height of this segment.") );
	
	fgSizer2->Add( m_textCtrlHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHeight = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHeight->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRadius = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlRadius->SetToolTip( _("Radius of curvature:\r\nPositive radius = convex surface = bulged to the outside.\r\nNegative radius = concave surface = bulged to the inside.\r\nRadius of 0 = straight line. ") );
	
	fgSizer2->Add( m_textCtrlRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitRadius = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRadius->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitRadius, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
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
	this->Connect( m_menuItem22->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnChangeStereo3D ) );
	m_buttonToolNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnNewTool ), NULL, this );
	m_buttonToolUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnUpdateTool ), NULL, this );
	m_buttonToolDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnDeleteTool ), NULL, this );
	m_buttonShapeNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnShapeNew ), NULL, this );
	m_buttonShapeUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnShapeUpdate ), NULL, this );
	m_buttonShapeDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnShapeDelete ), NULL, this );
	m_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIToolboxFrame::OnShapeSelect ), NULL, this );
}

GUIToolboxFrame::~GUIToolboxFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolboxFrame::OnChangeStereo3D ) );
	m_buttonToolNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnNewTool ), NULL, this );
	m_buttonToolUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnUpdateTool ), NULL, this );
	m_buttonToolDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnDeleteTool ), NULL, this );
	m_buttonShapeNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnShapeNew ), NULL, this );
	m_buttonShapeUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnShapeUpdate ), NULL, this );
	m_buttonShapeDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolboxFrame::OnShapeDelete ), NULL, this );
	m_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIToolboxFrame::OnShapeSelect ), NULL, this );
}

GUIStockFrame::GUIStockFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItem43;
	m_menuItem43 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Load Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem43 );
	
	wxMenuItem* m_menuItem42;
	m_menuItem42 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Save Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem42 );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menuStock->AppendSeparator();
	
	wxMenuItem* m_menuItem34;
	m_menuItem34 = new wxMenuItem( m_menuStock, wxID_CLOSE, wxString( _("&Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem34 );
	
	m_menubar->Append( m_menuStock, _("&Stock") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	m_menubar->Append( m_menuSettings, _("S&ettings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer20->Add( m_listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText27 = new wxStaticText( this, wxID_ANY, _("Size X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer4->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlX = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText28 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer4->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText29 = new wxStaticText( this, wxID_ANY, _("Size Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer4->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlY = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText30 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer4->Add( m_staticText30, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText31 = new wxStaticText( this, wxID_ANY, _("Size Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer4->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlZ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText32 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer4->Add( m_staticText32, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, _("Max speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer4->Add( m_staticText33, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText34 = new wxStaticText( this, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer4->Add( m_staticText34, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText35 = new wxStaticText( this, wxID_ANY, _("Max feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer4->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlMaxFeedrate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlMaxFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText36 = new wxStaticText( this, wxID_ANY, _("mm/s"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer4->Add( m_staticText36, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer20->Add( fgSizer4, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer20 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItem34->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIStockFrame::OnClose ) );
}

GUIStockFrame::~GUIStockFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIStockFrame::OnClose ) );
}

GUIObjectFrame::GUIObjectFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuObject = new wxMenu();
	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menuObject, wxID_OPEN, wxString( _("&Load Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemOpen );
	
	wxMenuItem* m_menuItemReLoad;
	m_menuItemReLoad = new wxMenuItem( m_menuObject, wxID_REVERT_TO_SAVED, wxString( _("&Reload Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemReLoad );
	
	wxMenuItem* m_menuItemSaveAs;
	m_menuItemSaveAs = new wxMenuItem( m_menuObject, wxID_SAVEAS, wxString( _("&Save Object As ...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemSaveAs );
	
	wxMenuItem* m_separator;
	m_separator = m_menuObject->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuObject, wxID_CLOSE, wxString( _("&Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuObject, _("&Object") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	m_menubar->Append( m_menuSettings, _("&Settings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBox = new wxComboBox( this, wxID_ANY, _(" No objects in project!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY ); 
	bSizer22->Add( m_comboBox, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonUpdate = new wxButton( this, wxID_UPDATE, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( m_buttonUpdate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer21->Add( bSizer22, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel5 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel5, wxID_ANY, _("Size of object") ), wxHORIZONTAL );
	
	m_staticText37 = new wxStaticText( m_panel5, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	sbSizer3->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeX = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer3->Add( m_textCtrlSizeX, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( m_panel5, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	sbSizer3->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText38 = new wxStaticText( m_panel5, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	sbSizer3->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeY = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer3->Add( m_textCtrlSizeY, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( m_panel5, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	sbSizer3->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText39 = new wxStaticText( m_panel5, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	sbSizer3->Add( m_staticText39, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeZ = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer3->Add( m_textCtrlSizeZ, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( m_panel5, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	sbSizer3->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer29->Add( sbSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel5, wxID_ANY, _("Rescale") ), wxVERTICAL );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxScaleProportionally = new wxCheckBox( m_panel5, wxID_ANY, _("Scale proportionally"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxScaleProportionally->SetValue(true); 
	bSizer24->Add( m_checkBoxScaleProportionally, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonMultTen = new wxButton( m_panel5, wxID_ANY, _("XYZ * 10"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_buttonMultTen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDivTen = new wxButton( m_panel5, wxID_ANY, _("XYZ / 10"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_buttonDivTen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlPercent = new wxTextCtrl( m_panel5, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_textCtrlPercent, 0, wxALL, 5 );
	
	m_staticText43 = new wxStaticText( m_panel5, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer24->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button15 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_button15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer4->Add( bSizer24, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 3, 9, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText44 = new wxStaticText( m_panel5, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	fgSizer6->Add( m_staticText44, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitX = new wxTextCtrl( m_panel5, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScaleUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX2 = new wxStaticText( m_panel5, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX2->Wrap( -1 );
	fgSizer6->Add( m_staticTextUnitX2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button19 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer6->Add( 30, 0, 1, wxEXPAND, 5 );
	
	m_staticText50 = new wxStaticText( m_panel5, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	fgSizer6->Add( m_staticText50, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercentX = new wxTextCtrl( m_panel5, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScalePercentX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText51 = new wxStaticText( m_panel5, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer6->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button20 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText46 = new wxStaticText( m_panel5, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer6->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitY = new wxTextCtrl( m_panel5, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScaleUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY2 = new wxStaticText( m_panel5, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY2->Wrap( -1 );
	fgSizer6->Add( m_staticTextUnitY2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button21 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button21, 0, wxALL, 5 );
	
	
	fgSizer6->Add( 30, 0, 1, wxEXPAND, 5 );
	
	m_staticText48 = new wxStaticText( m_panel5, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer6->Add( m_staticText48, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercentY = new wxTextCtrl( m_panel5, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScalePercentY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText49 = new wxStaticText( m_panel5, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer6->Add( m_staticText49, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button22 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText52 = new wxStaticText( m_panel5, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	fgSizer6->Add( m_staticText52, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitZ = new wxTextCtrl( m_panel5, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScaleUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ2 = new wxStaticText( m_panel5, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ2->Wrap( -1 );
	fgSizer6->Add( m_staticTextUnitZ2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button23 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer6->Add( 30, 0, 1, wxEXPAND, 5 );
	
	m_staticText54 = new wxStaticText( m_panel5, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	fgSizer6->Add( m_staticText54, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercentZ = new wxTextCtrl( m_panel5, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScalePercentZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText55 = new wxStaticText( m_panel5, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	fgSizer6->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button24 = new wxButton( m_panel5, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer4->Add( fgSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer29->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	m_panel5->SetSizer( bSizer29 );
	m_panel5->Layout();
	bSizer29->Fit( m_panel5 );
	m_notebook2->AddPage( m_panel5, _("Scale"), true );
	m_panel6 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panel6, wxID_ANY, _("label") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_button32 = new wxButton( m_panel6, wxID_ANY, _("Y -90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button32, 0, wxALL, 5 );
	
	m_button33 = new wxButton( m_panel6, wxID_ANY, _("X -90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button33, 0, wxALL, 5 );
	
	m_button28 = new wxButton( m_panel6, wxID_ANY, _("Y +90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button28, 0, wxALL, 5 );
	
	m_button29 = new wxButton( m_panel6, wxID_ANY, _("Z -90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button29, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button30 = new wxButton( m_panel6, wxID_ANY, _("Z +90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button30, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button31 = new wxButton( m_panel6, wxID_ANY, _("X +90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button31, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	sbSizer8->Add( fgSizer9, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer291->Add( sbSizer8, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel6->SetSizer( bSizer291 );
	m_panel6->Layout();
	bSizer291->Fit( m_panel6 );
	m_notebook2->AddPage( m_panel6, _("Rotate"), false );
	m_panel7 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, _("Position") ), wxVERTICAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button16 = new wxButton( m_panel7, wxID_ANY, _("Align with stock origin"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_button16, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button17 = new wxButton( m_panel7, wxID_ANY, _("Align with middle of stock"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_button17, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button18 = new wxButton( m_panel7, wxID_ANY, _("Align with top of stock"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_button18, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer5->Add( bSizer25, 0, wxEXPAND, 5 );
	
	m_panel7->SetSizer( sbSizer5 );
	m_panel7->Layout();
	sbSizer5->Fit( m_panel7 );
	m_notebook2->AddPage( m_panel7, _("Move"), false );
	
	bSizer21->Add( m_notebook2, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer21 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnOpen ) );
	this->Connect( m_menuItemReLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnReLoad ) );
	this->Connect( m_menuItemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnSaveAs ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnClose ) );
	m_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnSelectObject ), NULL, this );
	m_buttonUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnUpdate ), NULL, this );
	m_buttonMultTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnMultiplyByTen ), NULL, this );
	m_buttonDivTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnDivideByTen ), NULL, this );
	m_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercent ), NULL, this );
	m_button19->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::ScaleUnitX ), NULL, this );
	m_button20->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercentX ), NULL, this );
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScaleUnitY ), NULL, this );
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercentY ), NULL, this );
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScaleUnitZ ), NULL, this );
	m_button24->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercentZ ), NULL, this );
	m_button32->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnYMinus ), NULL, this );
	m_button33->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnXMinus ), NULL, this );
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnYPlus ), NULL, this );
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnZMinus ), NULL, this );
	m_button30->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnZPlus ), NULL, this );
	m_button31->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnXPlus ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnAlignWithStock ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnAlignWithMiddle ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnAlignWithTop ), NULL, this );
}

GUIObjectFrame::~GUIObjectFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnReLoad ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnClose ) );
	m_comboBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUIObjectFrame::OnSelectObject ), NULL, this );
	m_buttonUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnUpdate ), NULL, this );
	m_buttonMultTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnMultiplyByTen ), NULL, this );
	m_buttonDivTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnDivideByTen ), NULL, this );
	m_button15->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercent ), NULL, this );
	m_button19->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::ScaleUnitX ), NULL, this );
	m_button20->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercentX ), NULL, this );
	m_button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScaleUnitY ), NULL, this );
	m_button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercentY ), NULL, this );
	m_button23->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScaleUnitZ ), NULL, this );
	m_button24->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnScalePercentZ ), NULL, this );
	m_button32->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnYMinus ), NULL, this );
	m_button33->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnXMinus ), NULL, this );
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnYPlus ), NULL, this );
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnZMinus ), NULL, this );
	m_button30->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnZPlus ), NULL, this );
	m_button31->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnXPlus ), NULL, this );
	m_button16->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnAlignWithStock ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnAlignWithMiddle ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectFrame::OnAlignWithTop ), NULL, this );
}

GUIUnitDialog::GUIUnitDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Units ") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText57 = new wxStaticText( this, wxID_ANY, _("Length Units"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText57->Wrap( -1 );
	fgSizer6->Add( m_staticText57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitLengthChoices[] = { _("um"), _("mm"), _("cm"), _("m"), _("inch"), _("mil") };
	int m_choiceUnitLengthNChoices = sizeof( m_choiceUnitLengthChoices ) / sizeof( wxString );
	m_choiceUnitLength = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitLengthNChoices, m_choiceUnitLengthChoices, 0 );
	m_choiceUnitLength->SetSelection( 1 );
	fgSizer6->Add( m_choiceUnitLength, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticText58 = new wxStaticText( this, wxID_ANY, _("Tolerances"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText58->Wrap( -1 );
	fgSizer6->Add( m_staticText58, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitTolerancesChoices[] = { _("um"), _("mm"), _("cm"), _("m"), _("inch"), _("mil") };
	int m_choiceUnitTolerancesNChoices = sizeof( m_choiceUnitTolerancesChoices ) / sizeof( wxString );
	m_choiceUnitTolerances = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitTolerancesNChoices, m_choiceUnitTolerancesChoices, 0 );
	m_choiceUnitTolerances->SetSelection( 1 );
	fgSizer6->Add( m_choiceUnitTolerances, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticText59 = new wxStaticText( this, wxID_ANY, _("Rotational Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	fgSizer6->Add( m_staticText59, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceRotationalSpeedChoices[] = { _("rpm"), _("1/s"), _("1/min"), _("rad/s") };
	int m_choiceRotationalSpeedNChoices = sizeof( m_choiceRotationalSpeedChoices ) / sizeof( wxString );
	m_choiceRotationalSpeed = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceRotationalSpeedNChoices, m_choiceRotationalSpeedChoices, 0 );
	m_choiceRotationalSpeed->SetSelection( 2 );
	fgSizer6->Add( m_choiceRotationalSpeed, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	sbSizer6->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	bSizer25->Add( sbSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer25 );
	this->Layout();
	bSizer25->Fit( this );
	
	// Connect Events
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIUnitDialog::OnClose ), NULL, this );
}

GUIUnitDialog::~GUIUnitDialog()
{
	// Disconnect Events
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIUnitDialog::OnClose ), NULL, this );
}

GUITargetDialog::GUITargetDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText67 = new wxStaticText( m_panel3, wxID_ANY, _("Thickness of slice"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText67->Wrap( -1 );
	fgSizer8->Add( m_staticText67, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSliceThickness = new wxTextCtrl( m_panel3, wxID_ANY, _("30"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( m_textCtrlSliceThickness, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText69 = new wxStaticText( m_panel3, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText69->Wrap( -1 );
	fgSizer8->Add( m_staticText69, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button28 = new wxButton( m_panel3, wxID_ANY, _("from stock material"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( m_button28, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText72 = new wxStaticText( m_panel3, wxID_ANY, _("Number of slices"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText72->Wrap( -1 );
	fgSizer8->Add( m_staticText72, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSliceNumber = new wxTextCtrl( m_panel3, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer8->Add( m_textCtrlSliceNumber, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer26->Add( fgSizer8, 1, wxEXPAND, 5 );
	
	m_panel3->SetSizer( bSizer26 );
	m_panel3->Layout();
	bSizer26->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, _("Slice"), true );
	m_panel4 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel4->Enable( false );
	
	m_notebook1->AddPage( m_panel4, _("Mould"), false );
	
	bSizer25->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Support Structure") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText59 = new wxStaticText( this, wxID_ANY, _("Slot around structure"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	fgSizer7->Add( m_staticText59, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSlotWidth = new wxTextCtrl( this, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer7->Add( m_textCtrlSlotWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText60 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText60->Wrap( -1 );
	fgSizer7->Add( m_staticText60, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText61 = new wxStaticText( this, wxID_ANY, _("Distance between supports"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	fgSizer7->Add( m_staticText61, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSupportDistance = new wxTextCtrl( this, wxID_ANY, _("50"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer7->Add( m_textCtrlSupportDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText62 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( -1 );
	fgSizer7->Add( m_staticText62, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText63 = new wxStaticText( this, wxID_ANY, _("Width of support"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText63->Wrap( -1 );
	fgSizer7->Add( m_staticText63, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSupportWidth = new wxTextCtrl( this, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer7->Add( m_textCtrlSupportWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText64 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	fgSizer7->Add( m_staticText64, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText65 = new wxStaticText( this, wxID_ANY, _("Height of support"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	fgSizer7->Add( m_staticText65, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSupportHeight = new wxTextCtrl( this, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer7->Add( m_textCtrlSupportHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText66 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText66->Wrap( -1 );
	fgSizer7->Add( m_staticText66, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer7->Add( fgSizer7, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer25->Add( sbSizer7, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxMultipiece = new wxCheckBox( this, wxID_ANY, _("Multiple targets per workpiece"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxMultipiece->SetValue(true); 
	bSizer28->Add( m_checkBoxMultipiece, 0, wxALL, 5 );
	
	m_checkBoxSuperstuff = new wxCheckBox( this, wxID_ANY, _("Superstuff"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxSuperstuff->Enable( false );
	
	bSizer28->Add( m_checkBoxSuperstuff, 0, wxALL|wxEXPAND, 5 );
	
	bSizer25->Add( bSizer28, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonGenerate = new wxButton( this, wxID_ANY, _("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonGenerate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer25 );
	this->Layout();
	
	// Connect Events
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUITargetDialog::OnFromStock ), NULL, this );
	m_buttonGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUITargetDialog::OnGenerate ), NULL, this );
}

GUITargetDialog::~GUITargetDialog()
{
	// Disconnect Events
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUITargetDialog::OnFromStock ), NULL, this );
	m_buttonGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUITargetDialog::OnGenerate ), NULL, this );
}

GUIAnimationFrame::GUIAnimationFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText70 = new wxStaticText( this, wxID_ANY, _("Toolpath:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	bSizer30->Add( m_staticText70, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlToolpath = new wxTextCtrl( this, wxID_ANY, _("No toolpath selected!"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer30->Add( m_textCtrlToolpath, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer29->Add( bSizer30, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText71 = new wxStaticText( this, wxID_ANY, _("Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	bSizer31->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_textCtrlTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText72 = new wxStaticText( this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText72->Wrap( -1 );
	bSizer31->Add( m_staticText72, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer31->Add( m_textCtrlMaxTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer29->Add( bSizer31, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderTime = new wxSlider( this, wxID_ANY, 0, 0, 1000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer29->Add( m_sliderTime, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button31 = new wxButton( this, wxID_ANY, _("Last"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button31, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button28 = new wxButton( this, wxID_ANY, _("Begin"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button28, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button29 = new wxButton( this, wxID_ANY, _("Play"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button29, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button30 = new wxButton( this, wxID_ANY, _("End"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button30, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button32 = new wxButton( this, wxID_ANY, _("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button32, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer29->Add( bSizer32, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer29 );
	this->Layout();
	
	// Connect Events
	m_button31->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnLast ), NULL, this );
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnBegin ), NULL, this );
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnPlayStop ), NULL, this );
	m_button30->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnEnd ), NULL, this );
	m_button32->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnNext ), NULL, this );
}

GUIAnimationFrame::~GUIAnimationFrame()
{
	// Disconnect Events
	m_button31->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnLast ), NULL, this );
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnBegin ), NULL, this );
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnPlayStop ), NULL, this );
	m_button30->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnEnd ), NULL, this );
	m_button32->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimationFrame::OnNext ), NULL, this );
}
