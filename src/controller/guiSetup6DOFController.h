///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiSetup6DOFController__
#define __guiSetup6DOFController__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>
#include <wx/slider.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_BUTTONCONNECT 10000
#define ID_BUTTONDISCONNECT 10001

///////////////////////////////////////////////////////////////////////////////
/// Class GUISetup6DOFController
///////////////////////////////////////////////////////////////////////////////
class GUISetup6DOFController : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText;
		wxTextCtrl* textPort;
		wxRadioBox* radioDeviceSelect;
		wxStaticText* m_staticTextTx;
		wxSlider* m_sliderTx;
		wxStaticText* m_staticTextTy;
		wxSlider* m_sliderTy;
		wxStaticText* m_staticTextTz;
		wxSlider* m_sliderTz;
		wxStaticText* m_staticTextRx;
		wxSlider* m_sliderRx;
		wxStaticText* m_staticTextRy;
		wxSlider* m_sliderRy;
		wxStaticText* m_staticTextRz;
		wxSlider* m_sliderRz;
		wxButton* buttonConnect;
		wxButton* buttonDisconnect;
		wxButton* buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnConnect( wxCommandEvent& event ) = 0;
		virtual void OnDisconnect( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUISetup6DOFController( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup 6DOF Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,600 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUISetup6DOFController();
	
};

#endif //__guiSetup6DOFController__
