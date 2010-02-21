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
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem( m_menu1, wxID_QUIT, wxString( _("&Quit") ) + wxT('\t') + wxT("CTRL+Q"), _("Exit the program"), wxITEM_NORMAL );
	m_menu1->Append( m_menuItem19 );
	
	m_menubar->Append( m_menu1, _("&File") );
	
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem39;
	m_menuItem39 = new wxMenuItem( m_menu3, wxID_ABOUT, wxString( _("&Info") ) + wxT('\t') + wxT("CTRL+I"), _("About the program"), wxITEM_NORMAL );
	m_menu3->Append( m_menuItem39 );
	
	m_menubar->Append( m_menu3, _("&Help") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_button1 = new wxButton( this, wxID_SELECTMACHINE, _("Select a machine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button1, 0, wxALL|wxEXPAND, 5 );
	
	m_button2 = new wxButton( this, wxID_ANY, _("Select data"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button2->Enable( false );
	
	bSizer1->Add( m_button2, 0, wxALL|wxEXPAND, 5 );
	
	m_button3 = new wxButton( this, wxID_ANY, _("Select raw material"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button3->Enable( false );
	
	bSizer1->Add( m_button3, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnSelectMachine ), NULL, this );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnSelectMachine ), NULL, this );
}

GUIAbout::GUIAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button1 = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAbout::OnClose ), NULL, this );
}

GUIAbout::~GUIAbout()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAbout::OnClose ), NULL, this );
}
