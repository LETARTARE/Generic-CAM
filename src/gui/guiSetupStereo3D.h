///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUISETUPSTEREO3D_H__
#define __GUISETUPSTEREO3D_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/slider.h>
#include <wx/sizer.h>
#include "CanvasStereoTest.h"
#include <wx/clrpicker.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define ID_COLORLR 10100
#define ID_COLORLG 10101
#define ID_COLORLB 10102
#define ID_COLORRR 10103
#define ID_COLORRG 10104
#define ID_COLORRB 10105
#define ID_COLORLEFT 10106
#define ID_COLORRIGHT 10107
#define ID_TEXTLR 10108
#define ID_TEXTLG 10109
#define ID_TEXTLB 10110
#define ID_EYEDISTANCE 10111
#define ID_TEXTEYEDISTANCE 10112
#define ID_FOCALDISTANCE 10113
#define ID_TEXTFOCALDISTANCE 10114
#define ID_TEXTRR 10115
#define ID_TEXTRG 10116
#define ID_TEXTRB 10117

///////////////////////////////////////////////////////////////////////////////
/// Class GUISetupStereo3D
///////////////////////////////////////////////////////////////////////////////
class GUISetupStereo3D : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText120;
		wxSlider* m_sliderLR;
		wxSlider* m_sliderLG;
		wxSlider* m_sliderLB;
		CanvasStereoTest * m_canvas;
		wxStaticText* m_staticText1201;
		wxSlider* m_sliderRR;
		wxSlider* m_sliderRG;
		wxSlider* m_sliderRB;
		wxColourPickerCtrl* m_colourPickerLeft;
		wxButton* m_buttonSwapColors;
		wxColourPickerCtrl* m_colourPickerRight;
		wxStaticText* m_staticText113;
		wxTextCtrl* m_textCtrlLR;
		wxStaticText* m_staticText1131;
		wxTextCtrl* m_textCtrlLG;
		wxStaticText* m_staticText11311;
		wxTextCtrl* m_textCtrlLB;
		wxSlider* m_sliderEyeDistance;
		wxStaticText* m_staticText125;
		wxTextCtrl* m_textCtrlEyeDistance;
		wxStaticText* m_staticTextUnitEyeDistance;
		wxSlider* m_sliderFocalDistance;
		wxStaticText* m_staticText127;
		wxTextCtrl* m_textCtrlFocalDistance;
		wxStaticText* m_staticTextUnitFocalDistance;
		wxStaticText* m_staticText1132;
		wxTextCtrl* m_textCtrlRR;
		wxStaticText* m_staticText11312;
		wxTextCtrl* m_textCtrlRG;
		wxStaticText* m_staticText113111;
		wxTextCtrl* m_textCtrlRB;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnColorChanged( wxColourPickerEvent& event ) = 0;
		virtual void OnSwap( wxCommandEvent& event ) = 0;
		virtual void OnTextChange( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUISetupStereo3D( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Stereo "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 771,691 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUISetupStereo3D();
	
};

#endif //__GUISETUPSTEREO3D_H__
