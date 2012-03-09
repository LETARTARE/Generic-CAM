///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
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
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include "MainCanvas.h"
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
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
#include <wx/notebook.h>

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
			wxID_GENERATETARGET = 1000,
			wxID_SETUPCONTROLLER,
			wxID_VIEWSTEREO3D,
			wxID_SETUPUNITS,
			wxID_DISPLAYMACHINE,
			wxID_DISPLAYMATERIAL,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuProject;
		wxMenu* m_menuObject;
		wxMenu* m_menuMachine;
		wxMenu* m_menuToolbox;
		wxMenu* m_menuStock;
		wxMenu* m_menuToolpath;
		wxMenu* m_menuSettings;
		wxMenu* m_menuView;
		wxMenu* m_menuHelp;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panel1;
		wxTreeCtrl* tree;
		wxPanel* m_panel2;
		MainCanvas* m_canvas;
		wxStatusBar* m_statusBar;
		wxToolBar* m_toolBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCreateProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveProjectAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnModifyObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateTargets( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadMachine( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReloadMachine( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditToolbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadToolbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveToolbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditStock( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateToolpath( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRecollectToolpath( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCleanToolpath( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFlipRun( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPrepareMachinebed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadGCodes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveGCodes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeLanguage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupController( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeStereo3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupUnits( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowAnimationControl( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBeginLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnEndLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnActivateRightClickMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnSelectionChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnUpdateVisibility( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generic CAM"), const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 639,600 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUIMainFrame();
		void m_splitterOnIdle( wxIdleEvent& )
		{
		m_splitter->SetSashPosition( 144 );
		m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIMainFrame::m_splitterOnIdle ), NULL, this );
		}
		
	
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
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIAboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 447,308 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~GUIAboutDialog();
	
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
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIControl6DOFDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup 6DOF Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,600 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
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
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
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
			wxID_SETUPUNITS = 1000,
			wxID_VIEWSTEREO3D,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuTools;
		wxMenu* m_menuSettings;
		wxComboBox* m_comboBoxToolSelector;
		wxButton* m_buttonToolNew;
		wxButton* m_buttonToolUpdate;
		wxButton* m_buttonToolDelete;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textCtrlShaftDiameter;
		wxStaticText* m_staticTextUnitShaftDiameter;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textCtrlShaftLength;
		wxStaticText* m_staticTextUnitShaftLength;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrlMaxSpeed;
		wxStaticText* m_staticTextUnitMaxSpeed;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlFeedCoefficient;
		wxStaticText* m_staticTextUnitFeedCoefficient;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textCtrlNrOfTeeth;
		wxStaticText* m_staticText17;
		wxStaticText* m_staticText26;
		wxTextCtrl* m_textCtrlComment;
		ToolPanel* m_panel;
		wxButton* m_buttonShapeNew;
		wxButton* m_buttonShapeUpdate;
		wxButton* m_buttonShapeDelete;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textCtrlDiameter;
		wxStaticText* m_staticTextUnitDiameter;
		wxStaticText* m_staticText20;
		wxTextCtrl* m_textCtrlHeight;
		wxStaticText* m_staticTextUnitHeight;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrlRadius;
		wxStaticText* m_staticTextUnitRadius;
		wxStaticText* m_staticText24;
		wxCheckBox* m_checkBoxCutting;
		wxStaticText* m_staticText25;
		wxListCtrl* m_listCtrl;
		ToolCanvas* m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeStereo3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewTool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateTool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteTool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShapeNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShapeUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShapeDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShapeSelect( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIToolboxFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolbox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 611,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIToolboxFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIStockFrame
///////////////////////////////////////////////////////////////////////////////
class GUIStockFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_SETUPUNITS = 1000,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuStock;
		wxMenu* m_menuSettings;
		wxListCtrl* m_listCtrl;
		wxStaticText* m_staticText27;
		wxTextCtrl* m_textCtrlX;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxTextCtrl* m_textCtrlY;
		wxStaticText* m_staticText30;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_textCtrlZ;
		wxStaticText* m_staticText32;
		wxStaticText* m_staticText33;
		wxTextCtrl* m_textCtrlMaxSpeed;
		wxStaticText* m_staticText34;
		wxStaticText* m_staticText35;
		wxTextCtrl* m_textCtrlMaxFeedrate;
		wxStaticText* m_staticText36;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIStockFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Stock"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIStockFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIObjectFrame
///////////////////////////////////////////////////////////////////////////////
class GUIObjectFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_SETUPUNITS = 1000,
			wxID_UPDATE,
		};
		
		wxMenuBar* m_menubar;
		wxMenu* m_menuObject;
		wxMenu* m_menuSettings;
		wxComboBox* m_comboBox;
		wxButton* m_buttonUpdate;
		wxNotebook* m_notebook2;
		wxPanel* m_panel5;
		wxStaticText* m_staticText37;
		wxTextCtrl* m_textCtrlSizeX;
		wxStaticText* m_staticTextUnitX;
		wxStaticText* m_staticText38;
		wxTextCtrl* m_textCtrlSizeY;
		wxStaticText* m_staticTextUnitY;
		wxStaticText* m_staticText39;
		wxTextCtrl* m_textCtrlSizeZ;
		wxStaticText* m_staticTextUnitZ;
		wxCheckBox* m_checkBoxScaleProportionally;
		wxButton* m_buttonMultTen;
		wxButton* m_buttonDivTen;
		
		wxTextCtrl* m_textCtrlPercent;
		wxStaticText* m_staticText43;
		wxButton* m_button15;
		wxStaticText* m_staticText44;
		wxTextCtrl* m_textCtrlScaleUnitX;
		wxStaticText* m_staticTextUnitX2;
		wxButton* m_button19;
		
		wxStaticText* m_staticText50;
		wxTextCtrl* m_textCtrlScalePercentX;
		wxStaticText* m_staticText51;
		wxButton* m_button20;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_textCtrlScaleUnitY;
		wxStaticText* m_staticTextUnitY2;
		wxButton* m_button21;
		
		wxStaticText* m_staticText48;
		wxTextCtrl* m_textCtrlScalePercentY;
		wxStaticText* m_staticText49;
		wxButton* m_button22;
		wxStaticText* m_staticText52;
		wxTextCtrl* m_textCtrlScaleUnitZ;
		wxStaticText* m_staticTextUnitZ2;
		wxButton* m_button23;
		
		wxStaticText* m_staticText54;
		wxTextCtrl* m_textCtrlScalePercentZ;
		wxStaticText* m_staticText55;
		wxButton* m_button24;
		wxPanel* m_panel6;
		wxButton* m_button32;
		wxButton* m_button33;
		wxButton* m_button28;
		wxButton* m_button29;
		
		wxButton* m_button30;
		
		wxButton* m_button31;
		
		wxPanel* m_panel7;
		wxButton* m_button16;
		wxButton* m_button17;
		wxButton* m_button18;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMultiplyByTen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDivideByTen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScalePercent( wxCommandEvent& event ) { event.Skip(); }
		virtual void ScaleUnitX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScalePercentX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScaleUnitY( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScalePercentY( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScaleUnitZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScalePercentZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnYMinus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnXMinus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnYPlus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZMinus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZPlus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnXPlus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignWithStock( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignWithMiddle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlignWithTop( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIObjectFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Object Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 655,408 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIObjectFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIUnitDialog
///////////////////////////////////////////////////////////////////////////////
class GUIUnitDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText57;
		wxChoice* m_choiceUnitLength;
		wxStaticText* m_staticText58;
		wxChoice* m_choiceUnitTolerances;
		wxStaticText* m_staticText59;
		wxChoice* m_choiceRotationalSpeed;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIUnitDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GUIUnitDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUITargetDialog
///////////////////////////////////////////////////////////////////////////////
class GUITargetDialog : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel3;
		wxStaticText* m_staticText67;
		wxTextCtrl* m_textCtrlSliceThickness;
		wxStaticText* m_staticText69;
		wxButton* m_button28;
		wxStaticText* m_staticText72;
		wxTextCtrl* m_textCtrlSliceNumber;
		
		
		wxPanel* m_panel4;
		wxStaticText* m_staticText59;
		wxTextCtrl* m_textCtrlSlotWidth;
		wxStaticText* m_staticText60;
		wxStaticText* m_staticText61;
		wxTextCtrl* m_textCtrlSupportDistance;
		wxStaticText* m_staticText62;
		wxStaticText* m_staticText63;
		wxTextCtrl* m_textCtrlSupportWidth;
		wxStaticText* m_staticText64;
		wxStaticText* m_staticText65;
		wxTextCtrl* m_textCtrlSupportHeight;
		wxStaticText* m_staticText66;
		wxCheckBox* m_checkBoxMultipiece;
		wxCheckBox* m_checkBoxSuperstuff;
		wxButton* m_buttonGenerate;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnFromStock( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerate( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUITargetDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Prepare Targets"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUITargetDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAnimationFrame
///////////////////////////////////////////////////////////////////////////////
class GUIAnimationFrame : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText70;
		wxTextCtrl* m_textCtrlToolpath;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_textCtrlTime;
		wxStaticText* m_staticText72;
		wxTextCtrl* m_textCtrlMaxTime;
		wxSlider* m_sliderTime;
		wxButton* m_button31;
		wxButton* m_button28;
		wxButton* m_button29;
		wxButton* m_button30;
		wxButton* m_button32;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLast( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBegin( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlayStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNext( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIAnimationFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolpath Animation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIAnimationFrame();
	
};

#endif //__gui__
