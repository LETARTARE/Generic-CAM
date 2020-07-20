///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiSetup6DOFController.h"

///////////////////////////////////////////////////////////////////////////

GUISetup6DOFController::GUISetup6DOFController( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,-1 ), wxSize( -1,-1 ) );

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
	radioDeviceSelect->SetSelection( 2 );
	bSizer1->Add( radioDeviceSelect, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizerTx;
	bSizerTx = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextTx = new wxStaticText( this, wxID_ANY, "Tx", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTx->Wrap( -1 );
	bSizerTx->Add( m_staticTextTx, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_sliderTx = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTx->Enable( false );

	bSizerTx->Add( m_sliderTx, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	bSizer1->Add( bSizerTx, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTy;
	bSizerTy = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextTy = new wxStaticText( this, wxID_ANY, "Ty", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTy->Wrap( -1 );
	bSizerTy->Add( m_staticTextTy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	m_sliderTy = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTy->Enable( false );

	bSizerTy->Add( m_sliderTy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	bSizer1->Add( bSizerTy, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerTz;
	bSizerTz = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextTz = new wxStaticText( this, wxID_ANY, "Tz", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTz->Wrap( -1 );
	bSizerTz->Add( m_staticTextTz, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_sliderTz = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTz->Enable( false );

	bSizerTz->Add( m_sliderTz, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	bSizer1->Add( bSizerTz, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerRx;
	bSizerRx = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextRx = new wxStaticText( this, wxID_ANY, "Rx", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRx->Wrap( -1 );
	bSizerRx->Add( m_staticTextRx, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	m_sliderRx = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRx->Enable( false );

	bSizerRx->Add( m_sliderRx, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	bSizer1->Add( bSizerRx, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerRy;
	bSizerRy = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextRy = new wxStaticText( this, wxID_ANY, "Ry", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRy->Wrap( -1 );
	bSizerRy->Add( m_staticTextRy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	m_sliderRy = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRy->Enable( false );

	bSizerRy->Add( m_sliderRy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	bSizer1->Add( bSizerRy, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerRz;
	bSizerRz = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextRz = new wxStaticText( this, wxID_ANY, "Rz", wxDefaultPosition, wxDefaultSize, 0 );
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
	buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnConnect ), NULL, this );
	buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnDisconnect ), NULL, this );
	buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnClose ), NULL, this );
}

GUISetup6DOFController::~GUISetup6DOFController()
{
	// Disconnect Events
	buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnConnect ), NULL, this );
	buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnDisconnect ), NULL, this );
	buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnClose ), NULL, this );
}
