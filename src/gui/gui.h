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
#include "MachineCanvas.h"
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "DataCanvas.h"
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/slider.h>
#include <wx/combobox.h>
#include <wx/statbox.h>
#include "ToolPanel.h"
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/listctrl.h>
#include "ToolCanvas.h"

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
			wxID_VIEWSTEREO3D = 1000,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuProject;
		wxMenu* m_menuSettings;
		wxMenu* m_menuView;
		wxMenu* m_menuHelp;
		MachineCanvas* m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLoadMachine( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnReloadMachine( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLoadToolbox( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveToolbox( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditToolbox( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLoadGCodes( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSelectDataFrame( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSetupController( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnChangeStereo3D( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generic CAM"), const wxPoint& pos = wxPoint( -1,300 ), const wxSize& size = wxSize( 500,448 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUIMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAboutDialog
///////////////////////////////////////////////////////////////////////////////
class GUIAboutDialog : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl12;
		wxButton* m_button1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIAboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 447,375 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~GUIAboutDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDataFrame
///////////////////////////////////////////////////////////////////////////////
class GUIDataFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_VIEWSTEREO3D = 1000,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuMachine;
		wxMenu* m_menuView;
		DataCanvas* m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLoadSTLData( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveData( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSetScale( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnChangeStereo3D( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIDataFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("3D data view"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 507,452 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUIDataFrame();
	
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
		GUIControl6DOFDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup 6DOF Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 354,527 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUIControl6DOFDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIErrorFrame
///////////////////////////////////////////////////////////////////////////////
class GUIErrorFrame : public wxFrame 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl;
		wxButton* m_button;
		wxMenuBar* m_menubar;
		wxMenu* m_menu;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIErrorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("An error occured"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,370 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIErrorFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIToolboxFrame
///////////////////////////////////////////////////////////////////////////////
class GUIToolboxFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_VIEWSTEREO3D = 1000,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuTools;
		wxMenu* m_menuSettings;
		wxComboBox* m_comboBoxToolSelector;
		wxButton* m_button6;
		wxButton* m_button7;
		wxButton* m_button8;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textCtrlShaftDiameter;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textCtrlShaftLength;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrlMaxSpeed;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlFeedCoefficient;
		wxStaticText* m_staticText15;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textCtrlNrOfTeeth;
		wxStaticText* m_staticText17;
		wxStaticText* m_staticText26;
		wxTextCtrl* m_textCtrlComment;
		ToolPanel* m_panel;
		wxButton* m_button11;
		wxButton* m_button10;
		wxButton* m_button9;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textCtrlDiameter;
		wxStaticText* m_staticText19;
		wxStaticText* m_staticText20;
		wxTextCtrl* m_textCtrlHeight;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrlRadius;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText24;
		wxCheckBox* m_checkBoxCutting;
		wxStaticText* m_staticText25;
		wxListCtrl* m_listCtrl;
		ToolCanvas* m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnChangeStereo3D( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		GUIToolboxFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolbox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 611,790 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIToolboxFrame();
	
};

#endif //__gui__
