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
			wxID_QUIT = 1000,
			wxID_SELECTMACHINE,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menu1;
		wxMenu* m_menu3;
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectMachine( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generic CAM"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,189 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAbout
///////////////////////////////////////////////////////////////////////////////
class GUIAbout : public wxDialog 
{
	private:
	
	protected:
		
		wxButton* m_button1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 414,229 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GUIAbout();
	
};

#endif //__gui__
