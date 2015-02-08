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
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/bmpbuttn.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/grid.h>
#include <wx/slider.h>
#include <wx/radiobut.h>
#include "PanelTopView.h"
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include "PanelTool.h"
#include "ToolCanvas.h"
#include <wx/radiobox.h>
#include <wx/dialog.h>
#include "CanvasStereoTest.h"
#include <wx/clrpicker.h>

///////////////////////////////////////////////////////////////////////////

#define ID_PROJECTRENAME 1000
#define ID_OBJECTMODIFY 1001
#define ID_OBJECTFLIPNORMALS 1002
#define ID_OBJECTLOAD 1003
#define ID_OBJECTRENAME 1004
#define ID_OBJECTDELETE 1005
#define ID_STOCKORGANIZE 1006
#define ID_WORKPIECEADD 1007
#define ID_STOCKLOAD 1008
#define ID_STOCKSAVE 1009
#define ID_WORKPIECESETUP 1010
#define ID_WORKPIECEDELETE 1011
#define ID_WORKPIECEDELETEUNUSED 1012
#define ID_RUNEDIT 1013
#define ID_RUNADD 1014
#define ID_RUNDELETE 1015
#define ID_MACHINELOAD 1016
#define ID_MACHINERELOAD 1017
#define ID_MACHINEDEBUGGER 1018
#define ID_TOOLBOXEDIT 1019
#define ID_TOOLBOXLOAD 1020
#define ID_VIEWSTEREO3D 1021
#define ID_SETUPCONTROLLER 1022
#define ID_SETUPUNITS 1023
#define ID_CLOSEEXTRAWINDOWS 1024
#define ID_LOGSHOW 1025
#define ID_VIEWTOP 1026
#define ID_VIEWBOTTOM 1027
#define ID_VIEWFRONT 1028
#define ID_VIEWBACK 1029
#define ID_VIEWLEFT 1030
#define ID_VIEWRIGHT 1031
#define ID_DISPLAYMACHINE 1032
#define ID_DISPLAYMATERIAL 1033
#define ID_TOOLDRILLING 1034
#define ID_MULTTEN 1035
#define ID_DIVTEN 1036
#define ID_SCALEUNITX 1037
#define ID_SCALEUNITY 1038
#define ID_SCALEUNITZ 1039
#define ID_SCALEPERCENTX 1040
#define ID_SCALEPERCENTY 1041
#define ID_SCALEPERCENTZ 1042
#define ID_SCALEPERCENT 1043
#define ID_MOVEZP 1044
#define ID_MOVEYP 1045
#define ID_MOVEXN 1046
#define ID_MOVEXP 1047
#define ID_MOVEYN 1048
#define ID_MOVEZN 1049
#define ID_ALIGNTOP 1050
#define ID_ALIGNMIDDLE 1051
#define ID_ALIGNBOTTOM 1052
#define ID_ROTATEYN 1053
#define ID_ROTATEXN 1054
#define ID_ROTATEYP 1055
#define ID_ROTATEZN 1056
#define ID_ROTATEZP 1057
#define ID_ROTATEXP 1058
#define ID_FLIPX 1059
#define ID_FLIPY 1060
#define ID_FLIPZ 1061
#define ID_EXTRAADDFLIPDRILLS 1062
#define ID_POSX 1063
#define ID_POSY 1064
#define ID_POSZ 1065
#define ID_ANGLE 1066
#define ID_FORMBOX 1067
#define ID_FORMCONTOUR 1068
#define ID_WORKPIECEROTATEX 1069
#define ID_WORKPIECEROTATEY 1070
#define ID_WORKPIECEROTATEZ 1071
#define wxID_LOAD 1072
#define ID_AXISX 1073
#define ID_AXISY 1074
#define ID_AXISZ 1075
#define ID_TEXTX 1076
#define ID_TEXTY 1077
#define ID_TEXTZ 1078
#define ID_AXISA 1079
#define ID_AXISB 1080
#define ID_AXISC 1081
#define ID_TEXTA 1082
#define ID_TEXTB 1083
#define ID_TEXTC 1084
#define ID_AXISU 1085
#define ID_AXISV 1086
#define ID_AXISW 1087
#define ID_TEXTU 1088
#define ID_TEXTV 1089
#define ID_TEXTW 1090
#define ID_BUTTONCONNECT 1091
#define ID_BUTTONDISCONNECT 1092
#define ID_COLORLR 1093
#define ID_COLORLG 1094
#define ID_COLORLB 1095
#define ID_COLORRR 1096
#define ID_COLORRG 1097
#define ID_COLORRB 1098
#define ID_COLORLEFT 1099
#define ID_COLORRIGHT 1100
#define ID_TEXTLR 1101
#define ID_TEXTLG 1102
#define ID_TEXTLB 1103
#define ID_EYEDISTANCE 1104
#define ID_TEXTEYEDISTANCE 1105
#define ID_FOCALDISTANCE 1106
#define ID_TEXTFOCALDISTANCE 1107
#define ID_TEXTRR 1108
#define ID_TEXTRG 1109
#define ID_TEXTRB 1110

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuProject;
		wxMenu* m_menuEdit;
		wxMenu* m_menuObject;
		wxMenu* m_menuStock;
		wxMenu* m_menuWorkpiece;
		wxMenu* m_menuRun;
		wxMenu* m_menuMachine;
		wxMenu* m_menuToolbox;
		wxMenu* m_menuToolpath;
		wxMenu* m_menuSettings;
		wxMenu* m_menuView;
		wxMenu* m_menuHelp;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panel1;
		wxTreeCtrl* m_tree;
		wxPanel* m_panelMainCanvas;
		MainCanvas* m_canvas;
		wxStatusBar* m_statusBar;
		wxToolBar* m_toolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnProjectNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectRename( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUndo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRedo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnObjectModify( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnObjectFlipNormals( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnObjectLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnObjectRename( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnObjectDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStockEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWorkpieceAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWorkpieceSetup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWorkpieceDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWorkpieceDeleteUnused( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRunEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRunAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRunDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMachineLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMachineReload( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMachineDebugger( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolboxEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolboxLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolboxSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateToolpath( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRecollectToolpath( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCleanToolpath( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFlipRun( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPrepareMachinebed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadGCodes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveGCodes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowAnimationControl( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeLanguage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnActivateStereo3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupController( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupStereo3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupUnits( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExtraWindowClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowLogWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewSet( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBeginLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnEndLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnActivate( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnActivateRightClickMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnSelectionChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnSelectionChanging( wxTreeEvent& event ) { event.Skip(); }
		virtual void On3DSelect( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnToolbarButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddGenerator( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 803,627 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUIMainFrame();
		void m_splitterOnIdle( wxIdleEvent& )
		{
		m_splitter->SetSashPosition( 144 );
		m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIMainFrame::m_splitterOnIdle ), NULL, this );
		}
		
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIObjectTransformation
///////////////////////////////////////////////////////////////////////////////
class GUIObjectTransformation : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuObject;
		wxMenu* m_menuEdit;
		wxMenu* m_menuSettings;
		wxChoice* m_choiceObjectSelection;
		wxStaticText* m_staticText37;
		wxTextCtrl* m_textCtrlSizeX;
		wxStaticText* m_staticTextUnitX;
		wxStaticText* m_staticText38;
		wxTextCtrl* m_textCtrlSizeY;
		wxStaticText* m_staticTextUnitY;
		wxStaticText* m_staticText39;
		wxTextCtrl* m_textCtrlSizeZ;
		wxStaticText* m_staticTextUnitZ;
		wxNotebook* m_notebook;
		wxPanel* m_panelScale;
		wxButton* m_buttonMultTen;
		wxButton* m_buttonDivTen;
		wxStaticText* m_staticText44;
		wxTextCtrl* m_textCtrlScaleUnitX;
		wxStaticText* m_staticTextUnitX2;
		wxButton* m_button19;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_textCtrlScaleUnitY;
		wxStaticText* m_staticTextUnitY2;
		wxButton* m_button21;
		wxStaticText* m_staticText52;
		wxTextCtrl* m_textCtrlScaleUnitZ;
		wxStaticText* m_staticTextUnitZ2;
		wxButton* m_button23;
		wxCheckBox* m_checkBoxScaleProportionally;
		wxStaticText* m_staticText50;
		wxTextCtrl* m_textCtrlScalePercentX;
		wxStaticText* m_staticText51;
		wxButton* m_button20;
		wxStaticText* m_staticText48;
		wxTextCtrl* m_textCtrlScalePercentY;
		wxStaticText* m_staticText55;
		wxButton* m_button22;
		wxStaticText* m_staticText54;
		wxTextCtrl* m_textCtrlScalePercentZ;
		wxStaticText* m_staticText43;
		wxButton* m_button24;
		wxStaticText* m_staticText68;
		wxTextCtrl* m_textCtrlScalePercent;
		wxStaticText* m_staticText49;
		wxButton* m_button15;
		wxPanel* m_panelMove;
		
		wxStaticText* m_staticText62;
		wxTextCtrl* m_textCtrlMoveStep;
		wxStaticText* m_staticTextUnitMove;
		
		wxBitmapButton* m_bpButton6;
		wxBitmapButton* m_bpButton7;
		wxBitmapButton* m_bpButton8;
		
		wxBitmapButton* m_bpButton9;
		wxBitmapButton* m_bpButton10;
		wxBitmapButton* m_bpButton11;
		
		
		wxButton* m_button18;
		wxButton* m_button17;
		wxButton* m_button16;
		
		wxPanel* m_panelRotate;
		
		wxStaticText* m_staticText76;
		wxTextCtrl* m_textCtrlRotateStep;
		wxStaticText* m_staticText77;
		wxButton* m_button32;
		wxButton* m_button33;
		wxButton* m_button28;
		wxButton* m_button29;
		
		wxButton* m_button30;
		
		wxButton* m_button31;
		
		
		wxPanel* m_panelMirror;
		
		wxButton* m_button39;
		wxButton* m_button40;
		wxButton* m_button41;
		
		wxButton* m_buttonFlipNormalVectors;
		
		wxStatusBar* m_statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupUnits( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTransform( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetFactors( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFlipNormals( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIObjectTransformation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Object Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 709,468 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIObjectTransformation();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIStockMaterial
///////////////////////////////////////////////////////////////////////////////
class GUIStockMaterial : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuStock;
		wxMenu* m_menuSettings;
		
		wxStaticText* m_staticText96;
		wxTextCtrl* m_textCtrlName;
		
		wxStaticText* m_staticText27;
		wxTextCtrl* m_textCtrlX;
		wxStaticText* m_staticTextUnitX;
		wxStaticText* m_staticText29;
		wxTextCtrl* m_textCtrlY;
		wxStaticText* m_staticTextUnitY;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_textCtrlZ;
		wxStaticText* m_staticTextUnitZ;
		wxStaticText* m_staticText33;
		wxTextCtrl* m_textCtrlMaxSpeed;
		wxStaticText* m_staticTextUnitRotationalSpeed;
		wxStaticText* m_staticText35;
		wxTextCtrl* m_textCtrlMaxFeedrate;
		wxStaticText* m_staticTextUnitLinearSpeed;
		wxCheckBox* m_checkBoxAvailable;
		wxButton* m_buttonStockAdd;
		wxButton* m_buttonStockDelete;
		wxListCtrl* m_listCtrl;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnActivate( wxListEvent& event ) { event.Skip(); }
		virtual void OnSelected( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIStockMaterial( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Overview of all Stock Material"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 765,557 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIStockMaterial();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIWorkpiece
///////////////////////////////////////////////////////////////////////////////
class GUIWorkpiece : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuStock;
		wxMenu* m_menuEdit;
		wxStaticText* m_staticText97;
		wxChoice* m_choiceStock;
		wxButton* m_buttonAdd;
		wxGrid* m_grid;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddStock( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDBLClick( wxGridEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIWorkpiece( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Add Objects to Workpieces"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 559,457 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIWorkpiece();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIPlacement
///////////////////////////////////////////////////////////////////////////////
class GUIPlacement : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuEdit;
		wxMenu* m_menuExtras;
		wxChoice* m_choiceWorkpiece;
		wxChoice* m_choicePlacement;
		
		wxStaticText* m_staticText100;
		wxTextCtrl* m_textCtrlX;
		wxStaticText* m_staticTextUnitX;
		wxStaticText* m_staticText102;
		wxTextCtrl* m_textCtrlY;
		wxStaticText* m_staticTextUnitY;
		wxStaticText* m_staticText104;
		wxTextCtrl* m_textCtrlZ;
		wxStaticText* m_staticTextUnitZ;
		wxStaticText* m_staticText106;
		wxTextCtrl* m_textCtrlAngle;
		wxStaticText* m_staticTextunitAngle;
		wxSlider* m_sliderAngle;
		wxRadioButton* m_radioBtnBox;
		wxRadioButton* m_radioBtnContour;
		
		wxStaticText* m_staticText108;
		wxTextCtrl* m_textCtrlDistance;
		wxStaticText* m_staticTextUnitDistance;
		
		wxBitmapButton* m_bpButtonYP;
		
		wxBitmapButton* m_bpButtonXN;
		
		wxBitmapButton* m_bpButtonXP;
		
		wxBitmapButton* m_bpButtonYM;
		
		wxButton* m_buttonAlignTop;
		wxButton* m_buttonAlignMiddle;
		wxButton* m_buttonAlignBottom;
		PanelTopView * m_topview;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExtraAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectWorkpiece( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangePosition( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnSelectForm( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTransform( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIPlacement( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Objects in Workpiece Placement"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 773,726 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
		~GUIPlacement();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIRun
///////////////////////////////////////////////////////////////////////////////
class GUIRun : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuEdit;
		wxMenu* m_menuToolbox;
		wxMenu* m_menuSettings;
		wxChoice* m_choiceRun;
		wxChoice* m_choiceWorkpiece;
		wxButton* m_buttonRotX90;
		wxButton* m_buttonRotY90;
		wxButton* m_buttonRotZ90;
		wxTextCtrl* m_textCtrlMachineName;
		wxButton* m_buttonLoadMachine;
		wxStaticText* m_staticText99;
		wxListCtrl* m_listCtrlTools;
		wxButton* m_buttonToolDelete;
		wxChoice* m_choiceTool;
		wxStaticText* m_staticText100;
		wxSpinCtrl* m_spinCtrlToolSlot;
		wxButton* m_buttonToolAdd;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRunSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWorkpieceSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRotate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMachineLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolAdd( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIRun( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup a Machine Run"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 657,531 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIRun();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMachineDebugger
///////////////////////////////////////////////////////////////////////////////
class GUIMachineDebugger : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxMenu* m_menuMachine;
		wxSplitterWindow* m_splitter2;
		wxPanel* m_panel;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panelEditor;
		wxTextCtrl* m_textCtrlScript;
		wxButton* m_buttonRestart;
		wxPanel* m_panelOutput;
		wxTextCtrl* m_textCtrlOutput;
		wxPanel* m_panelMachineView;
		MainCanvas* m_canvas;
		wxStatusBar* m_statusBar3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMachineLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMachineSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScriptEvaluate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowController( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMachineDebugger( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine debugger"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 771,594 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUIMachineDebugger();
		void m_splitter2OnIdle( wxIdleEvent& )
		{
		m_splitter2->SetSashPosition( 325 );
		m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitter2OnIdle ), NULL, this );
		}
		
		void m_splitter3OnIdle( wxIdleEvent& )
		{
		m_splitter3->SetSashPosition( 222 );
		m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitter3OnIdle ), NULL, this );
		}
		
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMachineControl
///////////////////////////////////////////////////////////////////////////////
class GUIMachineControl : public wxFrame 
{
	private:
	
	protected:
		
		wxStaticText* m_staticText69;
		wxSlider* m_sliderX;
		wxStaticText* m_staticText70;
		wxSlider* m_sliderY;
		wxStaticText* m_staticText71;
		wxSlider* m_sliderZ;
		wxStaticText* m_staticText73;
		wxTextCtrl* m_textCtrlX;
		wxStaticText* m_staticTextUnitX;
		wxStaticText* m_staticText75;
		wxTextCtrl* m_textCtrlY;
		wxStaticText* m_staticTextUnitY;
		wxStaticText* m_staticText77;
		wxTextCtrl* m_textCtrlZ;
		wxStaticText* m_staticTextUnitZ;
		wxStaticText* m_staticText78;
		wxSlider* m_sliderA;
		wxStaticText* m_staticText79;
		wxSlider* m_sliderB;
		wxStaticText* m_staticText80;
		wxSlider* m_sliderC;
		wxStaticText* m_staticText731;
		wxTextCtrl* m_textCtrlA;
		wxStaticText* m_staticTextUnitA;
		wxStaticText* m_staticText751;
		wxTextCtrl* m_textCtrlB;
		wxStaticText* m_staticTextUnitB;
		wxStaticText* m_staticText771;
		wxTextCtrl* m_textCtrlC;
		wxStaticText* m_staticTextUnitC;
		wxStaticText* m_staticText81;
		wxSlider* m_sliderU;
		wxStaticText* m_staticText82;
		wxSlider* m_sliderV;
		wxStaticText* m_staticText83;
		wxSlider* m_sliderW;
		wxStaticText* m_staticText732;
		wxTextCtrl* m_textCtrlU;
		wxStaticText* m_staticTextUnitU;
		wxStaticText* m_staticText752;
		wxTextCtrl* m_textCtrlV;
		wxStaticText* m_staticTextUnitV;
		wxStaticText* m_staticText772;
		wxTextCtrl* m_textCtrlW;
		wxStaticText* m_staticTextUnitW;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnZero( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTrack( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTextChanged( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMachineControl( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,491 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		~GUIMachineControl();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIToolbox
///////////////////////////////////////////////////////////////////////////////
class GUIToolbox : public wxFrame 
{
	private:
	
	protected:
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
		PanelTool* m_panel;
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
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
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
		
		GUIToolbox( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolbox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 646,765 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIToolbox();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAnimation
///////////////////////////////////////////////////////////////////////////////
class GUIAnimation : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText70;
		wxChoice* m_choiceToolpath;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_textCtrlTime;
		wxStaticText* m_staticText72;
		wxTextCtrl* m_textCtrlMaxTime;
		wxSlider* m_sliderTime;
		wxBitmapButton* m_bpButtonFirst;
		wxBitmapButton* m_bpButtonPrev;
		wxBitmapButton* m_bpButtonPlayStop;
		wxBitmapButton* m_bpButtonNext;
		wxBitmapButton* m_bpButtonLast;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnFirst( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPrev( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlayStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNext( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLast( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIAnimation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolpath Animation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 478,187 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		~GUIAnimation();
	
};

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
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUISetup6DOFController( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup 6DOF Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,600 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUISetup6DOFController();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUISetupUnits
///////////////////////////////////////////////////////////////////////////////
class GUISetupUnits : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText57;
		wxChoice* m_choiceUnitLength;
		wxStaticText* m_staticText58;
		wxChoice* m_choiceUnitSpeedLinear;
		wxStaticText* m_staticText59;
		wxChoice* m_choiceUnitSpeedRotational;
		wxStaticText* m_staticText65;
		wxChoice* m_choiceUnitTime;
		wxStaticText* m_staticText110;
		wxChoice* m_choiceUnitSmallDistance;
		wxStaticText* m_staticText111;
		wxChoice* m_choiceUnitTolerance;
		wxStaticText* m_staticText112;
		wxChoice* m_choiceUnitAngle;
		wxButton* m_buttonClose;
		wxStaticText* m_staticText64;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChangeUnit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUISetupUnits( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup display units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~GUISetupUnits();
	
};

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
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnColorChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnSwap( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextChange( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUISetupStereo3D( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Stereo "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 771,691 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUISetupStereo3D();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAbout
///////////////////////////////////////////////////////////////////////////////
class GUIAbout : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl12;
		wxButton* m_button1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 504,373 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUIAbout();
	
};

#endif //__gui__
