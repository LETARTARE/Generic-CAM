///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 21 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include "../MachineCanvas.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>
#include <wx/slider.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_SELECTMACHINE = 1000,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		wxMenu* m_menu3;
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSetupController( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectMachine( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generic CAM"), const wxPoint& pos = wxPoint( -1,300 ), const wxSize& size = wxSize( 500,189 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAboutDialog
///////////////////////////////////////////////////////////////////////////////
class GUIAboutDialog : public wxDialog 
{
	private:
	
	protected:
		
		wxButton* m_button1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIAboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 414,229 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GUIAboutDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMachineFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMachineFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar2;
		wxMenu* m_menu1;
		MachineCanvas* m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLoadMachine( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnReloadMachine( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIMachineFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine View"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIMachineFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIControl6DOFDialog
///////////////////////////////////////////////////////////////////////////////
class GUIControl6DOFDialog : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_BUTTONCONNECT = 1000,
			ID_BUTTONDISCONNECT,
		};
		
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
		virtual void OnConnect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIControl6DOFDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup 6DOF Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUIControl6DOFDialog();
	
};

#endif //__gui__
