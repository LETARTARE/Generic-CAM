///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guiSetupStereo3D.h"

///////////////////////////////////////////////////////////////////////////

GUISetupStereo3D::GUISetupStereo3D( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer80;
	bSizer80 = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizerMain;
	fgSizerMain = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerMain->AddGrowableCol( 1 );
	fgSizerMain->AddGrowableRow( 0 );
	fgSizerMain->SetFlexibleDirection( wxBOTH );
	fgSizerMain->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizerLeftSilders;
	bSizerLeftSilders = new wxBoxSizer( wxVERTICAL );
	
	m_staticText120 = new wxStaticText( this, wxID_ANY, _("Left Eye"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText120->Wrap( -1 );
	bSizerLeftSilders->Add( m_staticText120, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderLR = new wxSlider( this, ID_COLORLR, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer76->Add( m_sliderLR, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderLG = new wxSlider( this, ID_COLORLG, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer76->Add( m_sliderLG, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderLB = new wxSlider( this, ID_COLORLB, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer76->Add( m_sliderLB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizerLeftSilders->Add( bSizer76, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizerMain->Add( bSizerLeftSilders, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_canvas = new CanvasStereoTest(this);
	fgSizerMain->Add( m_canvas, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizerRightSliders;
	bSizerRightSliders = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1201 = new wxStaticText( this, wxID_ANY, _("Right Eye"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1201->Wrap( -1 );
	bSizerRightSliders->Add( m_staticText1201, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer761;
	bSizer761 = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderRR = new wxSlider( this, ID_COLORRR, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer761->Add( m_sliderRR, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRG = new wxSlider( this, ID_COLORRG, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer761->Add( m_sliderRG, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRB = new wxSlider( this, ID_COLORRB, 100, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer761->Add( m_sliderRB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizerRightSliders->Add( bSizer761, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizerMain->Add( bSizerRightSliders, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_colourPickerLeft = new wxColourPickerCtrl( this, ID_COLORLEFT, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerMain->Add( m_colourPickerLeft, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonSwapColors = new wxButton( this, wxID_ANY, _("<-   Swap Colors   ->"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerMain->Add( m_buttonSwapColors, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_colourPickerRight = new wxColourPickerCtrl( this, ID_COLORRIGHT, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerMain->Add( m_colourPickerRight, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizerLeftText;
	fgSizerLeftText = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizerLeftText->SetFlexibleDirection( wxBOTH );
	fgSizerLeftText->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText113 = new wxStaticText( this, wxID_ANY, _("R:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText113->Wrap( -1 );
	fgSizerLeftText->Add( m_staticText113, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlLR = new wxTextCtrl( this, ID_TEXTLR, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerLeftText->Add( m_textCtrlLR, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1131 = new wxStaticText( this, wxID_ANY, _("G:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1131->Wrap( -1 );
	fgSizerLeftText->Add( m_staticText1131, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlLG = new wxTextCtrl( this, ID_TEXTLG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerLeftText->Add( m_textCtrlLG, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText11311 = new wxStaticText( this, wxID_ANY, _("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11311->Wrap( -1 );
	fgSizerLeftText->Add( m_staticText11311, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlLB = new wxTextCtrl( this, ID_TEXTLB, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerLeftText->Add( m_textCtrlLB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizerMain->Add( fgSizerLeftText, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizerMiddle;
	bSizerMiddle = new wxBoxSizer( wxVERTICAL );
	
	m_sliderEyeDistance = new wxSlider( this, ID_EYEDISTANCE, 100, 0, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizerMiddle->Add( m_sliderEyeDistance, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText125 = new wxStaticText( this, wxID_ANY, _("Eye Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText125->Wrap( -1 );
	bSizer82->Add( m_staticText125, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlEyeDistance = new wxTextCtrl( this, ID_TEXTEYEDISTANCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer82->Add( m_textCtrlEyeDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitEyeDistance = new wxStaticText( this, wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitEyeDistance->Wrap( -1 );
	bSizer82->Add( m_staticTextUnitEyeDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizerMiddle->Add( bSizer82, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderFocalDistance = new wxSlider( this, ID_FOCALDISTANCE, 100, 0, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizerMiddle->Add( m_sliderFocalDistance, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText127 = new wxStaticText( this, wxID_ANY, _("Focal Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText127->Wrap( -1 );
	bSizer83->Add( m_staticText127, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFocalDistance = new wxTextCtrl( this, ID_TEXTFOCALDISTANCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer83->Add( m_textCtrlFocalDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitFocalDistance = new wxStaticText( this, wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFocalDistance->Wrap( -1 );
	bSizer83->Add( m_staticTextUnitFocalDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizerMiddle->Add( bSizer83, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizerMain->Add( bSizerMiddle, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizerRightText;
	fgSizerRightText = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizerRightText->SetFlexibleDirection( wxBOTH );
	fgSizerRightText->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1132 = new wxStaticText( this, wxID_ANY, _("R:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1132->Wrap( -1 );
	fgSizerRightText->Add( m_staticText1132, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRR = new wxTextCtrl( this, ID_TEXTRR, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerRightText->Add( m_textCtrlRR, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText11312 = new wxStaticText( this, wxID_ANY, _("G:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11312->Wrap( -1 );
	fgSizerRightText->Add( m_staticText11312, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRG = new wxTextCtrl( this, ID_TEXTRG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerRightText->Add( m_textCtrlRG, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText113111 = new wxStaticText( this, wxID_ANY, _("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText113111->Wrap( -1 );
	fgSizerRightText->Add( m_staticText113111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRB = new wxTextCtrl( this, ID_TEXTRB, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerRightText->Add( m_textCtrlRB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizerMain->Add( fgSizerRightText, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer80->Add( fgSizerMain, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	this->SetSizer( bSizer80 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISetupStereo3D::OnXClose ) );
	m_sliderLR->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_colourPickerLeft->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUISetupStereo3D::OnColorChanged ), NULL, this );
	m_buttonSwapColors->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupStereo3D::OnSwap ), NULL, this );
	m_colourPickerRight->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUISetupStereo3D::OnColorChanged ), NULL, this );
	m_textCtrlLR->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlLG->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlLB->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_textCtrlEyeDistance->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_textCtrlFocalDistance->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlRR->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlRG->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlRB->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
}

GUISetupStereo3D::~GUISetupStereo3D()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISetupStereo3D::OnXClose ) );
	m_sliderLR->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLR->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLG->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderLB->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRR->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRG->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderRB->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_colourPickerLeft->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUISetupStereo3D::OnColorChanged ), NULL, this );
	m_buttonSwapColors->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupStereo3D::OnSwap ), NULL, this );
	m_colourPickerRight->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUISetupStereo3D::OnColorChanged ), NULL, this );
	m_textCtrlLR->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlLG->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlLB->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderEyeDistance->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_textCtrlEyeDistance->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_sliderFocalDistance->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUISetupStereo3D::OnScroll ), NULL, this );
	m_textCtrlFocalDistance->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlRR->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlRG->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
	m_textCtrlRB->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUISetupStereo3D::OnTextChange ), NULL, this );
}
