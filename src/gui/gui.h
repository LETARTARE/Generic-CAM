///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include "CanvasMain.h"
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/clrpicker.h>
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
#include "PanelTopView.h"
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include "CanvasMachine.h"
#include <wx/combobox.h>
#include "PanelTool.h"
#include "CanvasTool.h"
#include <wx/radiobox.h>
#include <wx/statline.h>
#include <wx/dialog.h>
#include <wx/choicebk.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/radiobut.h>

///////////////////////////////////////////////////////////////////////////

#define ID_OBJECTMODIFY 1000
#define ID_OBJECTFLIPNORMALS 1001
#define ID_OBJECTLOAD 1002
#define ID_OBJECTRENAME 1003
#define ID_OBJECTDELETE 1004
#define ID_STOCKORGANIZE 1005
#define ID_WORKPIECEADD 1006
#define ID_STOCKLOAD 1007
#define ID_STOCKSAVE 1008
#define ID_WORKPIECESETUP 1009
#define ID_WORKPIECEDELETE 1010
#define ID_WORKPIECEDELETEUNUSED 1011
#define ID_MACHINELOAD 1012
#define ID_MACHINERELOAD 1013
#define ID_MACHINEDEBUGGER 1014
#define ID_TOOLBOXEDIT 1015
#define ID_TOOLBOXLOAD 1016
#define ID_TOOLBOXSAVE 1017
#define ID_RUNEDIT 1018
#define ID_RUNADD 1019
#define ID_RUNDELETE 1020
#define ID_GENERATORSETUP 1021
#define ID_GENERATORSTART 1022
#define ID_GENERATORAUTOMATIC 1023
#define ID_GENERATORRESTART 1024
#define ID_DIALECT_RS274NGC 1025
#define ID_DIALECT_FANUCM 1026
#define ID_TOOLPATHSAVE 1027
#define ID_VIEWSTEREO3D 1028
#define ID_CLOSEEXTRAWINDOWS 1029
#define ID_LOGSHOW 1030
#define ID_VIEWTOP 1031
#define ID_VIEWBOTTOM 1032
#define ID_VIEWFRONT 1033
#define ID_VIEWBACK 1034
#define ID_VIEWRIGHT 1035
#define ID_VIEWLEFT 1036
#define ID_TESTGCODE 1037
#define ID_MULTTEN 1038
#define ID_DIVTEN 1039
#define ID_SCALEUNITX 1040
#define ID_SCALEUNITY 1041
#define ID_SCALEUNITZ 1042
#define ID_SCALEPERCENTX 1043
#define ID_SCALEPERCENTY 1044
#define ID_SCALEPERCENTZ 1045
#define ID_SCALEPERCENT 1046
#define ID_MOVEZP 1047
#define ID_MOVEYP 1048
#define ID_MOVEXN 1049
#define ID_MOVEXP 1050
#define ID_MOVEYN 1051
#define ID_MOVEZN 1052
#define ID_ALIGNTOP 1053
#define ID_ALIGNMIDDLE 1054
#define ID_ALIGNBOTTOM 1055
#define ID_ALIGNCENTER 1056
#define ID_ROTATEYN 1057
#define ID_ROTATEXN 1058
#define ID_ROTATEYP 1059
#define ID_ROTATEZN 1060
#define ID_ROTATEZP 1061
#define ID_ROTATEXP 1062
#define ID_FLIPX 1063
#define ID_FLIPY 1064
#define ID_FLIPZ 1065
#define ID_POSX 1066
#define ID_POSY 1067
#define ID_POSZ 1068
#define ID_ANGLE 1069
#define ID_FORMCONTOUR 1070
#define ID_DISTANCE 1071
#define ID_WORKPIECEROTATEX 1072
#define ID_WORKPIECEROTATEY 1073
#define ID_WORKPIECEROTATEZ 1074
#define ID_CONTROLLERSHOW 1075
#define ID_AXISX 1076
#define ID_AXISY 1077
#define ID_AXISZ 1078
#define ID_TEXTX 1079
#define ID_TEXTY 1080
#define ID_TEXTZ 1081
#define ID_AXISA 1082
#define ID_AXISB 1083
#define ID_AXISC 1084
#define ID_TEXTA 1085
#define ID_TEXTB 1086
#define ID_TEXTC 1087
#define ID_AXISU 1088
#define ID_AXISV 1089
#define ID_AXISW 1090
#define ID_TEXTU 1091
#define ID_TEXTV 1092
#define ID_TEXTW 1093
#define ID_XSTART 1094
#define ID_XEND 1095
#define ID_YSTART 1096
#define ID_YEND 1097
#define ID_ZSTART 1098
#define ID_ZEND 1099
#define ID_SELECTAREAOBJECT 1100
#define ID_MARGINSIDE 1101
#define ID_MARGINBELOW 1102

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameMain
///////////////////////////////////////////////////////////////////////////////
class GUIFrameMain : public wxDocChildFrame
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxMenu* m_menuEdit;
		wxMenu* m_menuObject;
		wxMenu* m_menuStock;
		wxMenu* m_menuWorkpiece;
		wxMenu* m_menuMachine;
		wxMenu* m_menuToolbox;
		wxMenu* m_menuRun;
		wxMenu* m_menuToolpath;
		wxMenu* m_menuDialect;
		wxMenu* m_menuSettings;
		wxMenu* m_menuView;
		wxMenu* m_menuHelp;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panelTree;
		wxTreeCtrl* m_tree;
		wxPanel* m_panelCanvasMain;
		CanvasMain* m_canvas;
		wxStatusBar* m_statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) = 0;
		virtual void OnObjectModify( wxCommandEvent& event ) = 0;
		virtual void OnObjectFlipNormals( wxCommandEvent& event ) = 0;
		virtual void OnObjectLoad( wxCommandEvent& event ) = 0;
		virtual void OnObjectRename( wxCommandEvent& event ) = 0;
		virtual void OnObjectDelete( wxCommandEvent& event ) = 0;
		virtual void OnStockEdit( wxCommandEvent& event ) = 0;
		virtual void OnWorkpieceAdd( wxCommandEvent& event ) = 0;
		virtual void OnWorkpieceSetup( wxCommandEvent& event ) = 0;
		virtual void OnWorkpieceDelete( wxCommandEvent& event ) = 0;
		virtual void OnWorkpieceDeleteUnused( wxCommandEvent& event ) = 0;
		virtual void OnMachineLoad( wxCommandEvent& event ) = 0;
		virtual void OnMachineReload( wxCommandEvent& event ) = 0;
		virtual void OnMachineDebugger( wxCommandEvent& event ) = 0;
		virtual void OnFlipDrillSetup( wxCommandEvent& event ) = 0;
		virtual void OnToolboxEdit( wxCommandEvent& event ) = 0;
		virtual void OnToolboxLoad( wxCommandEvent& event ) = 0;
		virtual void OnToolboxSave( wxCommandEvent& event ) = 0;
		virtual void OnRunEdit( wxCommandEvent& event ) = 0;
		virtual void OnRunAdd( wxCommandEvent& event ) = 0;
		virtual void OnRunDelete( wxCommandEvent& event ) = 0;
		virtual void OnGeneratorSetup( wxCommandEvent& event ) = 0;
		virtual void OnGeneratorStart( wxCommandEvent& event ) = 0;
		virtual void OnGeneratorAutomatic( wxCommandEvent& event ) = 0;
		virtual void OnGeneratorRestart( wxCommandEvent& event ) = 0;
		virtual void OnGeneratorSaveToolpath( wxCommandEvent& event ) = 0;
		virtual void OnShowAnimationControl( wxCommandEvent& event ) = 0;
		virtual void OnActivateStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnExtraWindowClose( wxCommandEvent& event ) = 0;
		virtual void OnShowLogWindow( wxCommandEvent& event ) = 0;
		virtual void OnViewSet( wxCommandEvent& event ) = 0;
		virtual void OnTestGCode( wxCommandEvent& event ) = 0;
		virtual void OnBeginLabelEdit( wxTreeEvent& event ) = 0;
		virtual void OnEndLabelEdit( wxTreeEvent& event ) = 0;
		virtual void OnActivate( wxTreeEvent& event ) = 0;
		virtual void OnActivateRightClickMenu( wxTreeEvent& event ) = 0;
		virtual void OnSelectionChanged( wxTreeEvent& event ) = 0;
		virtual void OnSelectionChanging( wxTreeEvent& event ) = 0;
		virtual void On3DDClick( wxMouseEvent& event ) = 0;
		virtual void On3DSelect( wxMouseEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 803,627 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~GUIFrameMain();
		
		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 250 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIFrameMain::m_splitterOnIdle ), NULL, this );
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
		wxColourPickerCtrl* m_colourPickerObject;
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
		wxButton* m_button50;
		wxPanel* m_panelRotate;
		wxStaticText* m_staticText76;
		wxTextCtrl* m_textCtrlRotateStep;
		wxStaticText* m_staticTextUnitAngle;
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
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnChangeObjectColor( wxColourPickerEvent& event ) = 0;
		virtual void OnSelectObject( wxCommandEvent& event ) = 0;
		virtual void OnTransform( wxCommandEvent& event ) = 0;
		virtual void OnSetFactors( wxCommandEvent& event ) = 0;
		virtual void OnFlipNormals( wxCommandEvent& event ) = 0;
		
	
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
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSize( wxSizeEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnAddUpdate( wxCommandEvent& event ) = 0;
		virtual void OnDelete( wxCommandEvent& event ) = 0;
		virtual void OnActivate( wxListEvent& event ) = 0;
		virtual void OnSelected( wxListEvent& event ) = 0;
		
	
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
		wxStaticText* m_staticTextStock;
		wxChoice* m_choiceStock;
		wxButton* m_buttonAdd;
		wxGrid* m_grid;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSize( wxSizeEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnAddStock( wxCommandEvent& event ) = 0;
		virtual void OnDBLClick( wxGridEvent& event ) = 0;
		
	
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
		wxMenu* m_menuPlacement;
		wxMenu* m_menuEdit;
		wxMenu* m_menuSettings;
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
		wxCheckBox* m_checkBoxContour;
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
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSize( wxSizeEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnSelectWorkpiece( wxCommandEvent& event ) = 0;
		virtual void OnSelectObject( wxCommandEvent& event ) = 0;
		virtual void OnChange( wxCommandEvent& event ) = 0;
		virtual void OnChangeSlider( wxScrollEvent& event ) = 0;
		virtual void OnTransform( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIPlacement( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Objects in Workpiece Placement"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 840,712 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
		
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
		wxMenu* m_menuToolbox;
		wxMenu* m_menuEdit;
		wxMenu* m_menuSettings;
		wxChoice* m_choiceRun;
		wxChoice* m_choiceWorkpiece;
		wxButton* m_buttonRotX90;
		wxButton* m_buttonRotY90;
		wxButton* m_buttonRotZ90;
		wxTextCtrl* m_textCtrlMachineName;
		wxButton* m_buttonLoadMachine;
		wxStaticText* m_statiTextToolsAvailable;
		wxListBox* m_listBoxTool;
		wxStaticText* m_staticTextToolSlot;
		wxSpinCtrl* m_spinCtrlToolSlot;
		wxButton* m_buttonToolAdd;
		wxStaticText* m_staticTextToolsInMachine;
		wxListCtrl* m_listCtrlTools;
		wxButton* m_buttonToolDelete;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnRunSelect( wxCommandEvent& event ) = 0;
		virtual void OnWorkpieceSelect( wxCommandEvent& event ) = 0;
		virtual void OnRotate( wxCommandEvent& event ) = 0;
		virtual void OnMachineLoad( wxCommandEvent& event ) = 0;
		virtual void OnToolAdd( wxCommandEvent& event ) = 0;
		virtual void OnToolRemove( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIRun( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup a Machine Run"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 901,531 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		wxMenu* m_menuMachine;
		wxMenu* m_menuSettings;
		wxMenu* m_menuView;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panel;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panelEditor;
		wxTextCtrl* m_textCtrlScript;
		wxButton* m_buttonRestart;
		wxPanel* m_panelOutput;
		wxTextCtrl* m_textCtrlOutput;
		wxPanel* m_panelMachineView;
		CanvasMachine* m_canvas;
		wxStatusBar* m_statusBar3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnMachineLoad( wxCommandEvent& event ) = 0;
		virtual void OnMachineSave( wxCommandEvent& event ) = 0;
		virtual void OnScriptEvaluate( wxCommandEvent& event ) = 0;
		virtual void OnShowController( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnChangeStereo3D( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIMachineDebugger( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine debugger"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 831,596 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~GUIMachineDebugger();
		
		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 326 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitterOnIdle ), NULL, this );
		}
		
		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 409 );
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
		wxMenuBar* m_menubar;
		wxMenu* m_menuController;
		wxMenu* m_menuSettings;
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
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnZero( wxMouseEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnTrack( wxScrollEvent& event ) = 0;
		virtual void OnTextChanged( wxCommandEvent& event ) = 0;
		
	
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
		wxMenu* m_menuView;
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
		wxStaticText* m_staticTextFlutes;
		wxTextCtrl* m_textCtrlNrOfTeeth;
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
		wxCheckBox* m_checkBoxCutting;
		wxListCtrl* m_listCtrl;
		CanvasTool* m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnShapeWizard( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		virtual void OnChangeStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnToolSelect( wxCommandEvent& event ) = 0;
		virtual void OnToolRename( wxCommandEvent& event ) = 0;
		virtual void OnToolNew( wxCommandEvent& event ) = 0;
		virtual void OnToolUpdate( wxCommandEvent& event ) = 0;
		virtual void OnToolDelete( wxCommandEvent& event ) = 0;
		virtual void OnEnter( wxCommandEvent& event ) = 0;
		virtual void OnShapeNew( wxCommandEvent& event ) = 0;
		virtual void OnShapeUpdate( wxCommandEvent& event ) = 0;
		virtual void OnShapeDelete( wxCommandEvent& event ) = 0;
		virtual void OnShapeSelect( wxListEvent& event ) = 0;
		
	
	public:
		
		GUIToolbox( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolbox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 885,757 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIToolbox();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIToolWizard
///////////////////////////////////////////////////////////////////////////////
class GUIToolWizard : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* m_radioBoxToolType;
		wxStaticText* m_staticText128;
		wxTextCtrl* m_textCtrl68;
		wxStaticText* m_staticText129;
		wxStaticText* m_staticText134;
		wxTextCtrl* m_textCtrl71;
		wxStaticText* m_staticText135;
		wxStaticText* m_staticText138;
		wxTextCtrl* m_textCtrl73;
		wxStaticText* m_staticText139;
		wxStaticLine* m_staticline1;
		wxStaticLine* m_staticline2;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText130;
		wxTextCtrl* m_textCtrl69;
		wxStaticText* m_staticText131;
		wxStaticText* m_staticText136;
		wxTextCtrl* m_textCtrl72;
		wxStaticText* m_staticText137;
		wxStaticText* m_staticText132;
		wxTextCtrl* m_textCtrl70;
		wxStaticText* m_staticText133;
		wxButton* m_buttonAdd;
		wxButton* m_buttonSetShape;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAddTool( wxCommandEvent& event ) = 0;
		virtual void OnSetShape( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIToolWizard( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolshape Wizard"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~GUIToolWizard();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIToolpathGenerator
///////////////////////////////////////////////////////////////////////////////
class GUIToolpathGenerator : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText125;
		wxChoice* m_choiceRun;
		wxStaticText* m_staticText145;
		wxChoice* m_choiceToolpath;
		wxButton* m_buttonAddNew;
		wxStaticText* m_staticTextX;
		wxTextCtrl* m_textCtrlX1;
		wxStaticText* m_staticTextUnitX1;
		wxStaticText* m_staticText130;
		wxTextCtrl* m_textCtrlX2;
		wxStaticText* m_staticTextUnitX2;
		wxStaticText* m_staticTextY;
		wxTextCtrl* m_textCtrlY1;
		wxStaticText* m_staticTextUnitY1;
		wxStaticText* m_staticText132;
		wxTextCtrl* m_textCtrlY2;
		wxStaticText* m_staticTextUnitY2;
		wxStaticText* m_staticTextZ;
		wxTextCtrl* m_textCtrlZ1;
		wxStaticText* m_staticTextUnitZ1;
		wxStaticText* m_staticText1312;
		wxTextCtrl* m_textCtrlZ2;
		wxStaticText* m_staticTextUnitZ2;
		wxButton* m_buttonSelectAreaFromObject;
		wxStaticText* m_staticTextSide;
		wxTextCtrl* m_textCtrlMarginSide;
		wxStaticText* m_staticTextUnitMarginSide;
		wxStaticText* m_staticTextBelow;
		wxTextCtrl* m_textCtrlMarginBelow;
		wxStaticText* m_staticTextUnitMarginBelow;
		wxChoice* m_choiceTool;
		wxStaticText* m_staticTextDiameter;
		wxTextCtrl* m_textCtrlToolDiameter;
		wxStaticText* m_staticTextUnitDiameter;
		wxStaticText* m_staticTextFreeHeight;
		wxTextCtrl* m_textCtrlFreeHeight;
		wxStaticText* m_staticTextUnitFreeHeight;
		wxChoicebook* m_choicebookGenerator;
		wxButton* m_buttonUpdate;
		wxButton* m_buttonReset;
		wxButton* m_buttonDelete;
		wxButton* m_buttonClose;
		wxTextCtrl* m_textCtrlInfo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSelectRun( wxCommandEvent& event ) = 0;
		virtual void OnSelectToolpath( wxCommandEvent& event ) = 0;
		virtual void OnAdd( wxCommandEvent& event ) = 0;
		virtual void OnChangeText( wxCommandEvent& event ) = 0;
		virtual void OnSelectArea( wxCommandEvent& event ) = 0;
		virtual void OnSelectTool( wxCommandEvent& event ) = 0;
		virtual void OnPageChanged( wxChoicebookEvent& event ) = 0;
		virtual void OnUpdate( wxCommandEvent& event ) = 0;
		virtual void OnResetChanges( wxCommandEvent& event ) = 0;
		virtual void OnDelete( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIToolpathGenerator( wxWindow* parent, wxWindowID id = wxID_CLOSE, const wxString& title = _("Add / Update Toolpath Generators"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 826,802 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIToolpathGenerator();
	
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
		wxTextCtrl* m_textCtrl0;
		wxTextCtrl* m_textCtrl1;
		wxTextCtrl* m_textCtrl2;
		wxTextCtrl* m_textCtrl3;
		wxTextCtrl* m_textCtrl4;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_textCtrlTime;
		wxStaticText* m_staticText72;
		wxTextCtrl* m_textCtrlMaxTime;
		wxSlider* m_sliderTime;
		wxCheckBox* m_checkBoxSimulateWorkpiece;
		wxBitmapButton* m_bpButtonFirst;
		wxBitmapButton* m_bpButtonPrev;
		wxBitmapButton* m_bpButtonPlayStop;
		wxBitmapButton* m_bpButtonNext;
		wxBitmapButton* m_bpButtonLast;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSelectToolpath( wxCommandEvent& event ) = 0;
		virtual void OnChangeTime( wxCommandEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnChangeSimulation( wxCommandEvent& event ) = 0;
		virtual void OnFirst( wxCommandEvent& event ) = 0;
		virtual void OnPrev( wxCommandEvent& event ) = 0;
		virtual void OnPlayStop( wxCommandEvent& event ) = 0;
		virtual void OnNext( wxCommandEvent& event ) = 0;
		virtual void OnLast( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIAnimation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolpath Animation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 558,413 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~GUIAnimation();
	
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
		virtual void OnChangeUnit( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUISetupUnits( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup display units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~GUISetupUnits();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogAbout
///////////////////////////////////////////////////////////////////////////////
class GUIDialogAbout : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl;
		wxButton* m_buttonClose;
	
	public:
		
		GUIDialogAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 504,373 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP ); 
		~GUIDialogAbout();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class StartupText
///////////////////////////////////////////////////////////////////////////////
class StartupText : public wxFrame 
{
	private:
	
	protected:
	
	public:
		wxRichTextCtrl* m_richText;
		
		StartupText( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Release Info"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 629,481 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~StartupText();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUITestGCode
///////////////////////////////////////////////////////////////////////////////
class GUITestGCode : public wxFrame 
{
	private:
	
	protected:
		wxRadioButton* m_radioBtnG20;
		wxRadioButton* m_radioBtnG21;
		wxTextCtrl* m_textCtrlInput;
		wxButton* m_buttonClear;
		wxTextCtrl* m_textCtrlOutput;
		wxTextCtrl* m_textCtrlRecreated;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnText( wxCommandEvent& event ) = 0;
		virtual void OnClear( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUITestGCode( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("G-Code parser"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~GUITestGCode();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUISetupMidi
///////////////////////////////////////////////////////////////////////////////
class GUISetupMidi : public wxFrame 
{
	private:
	
	protected:
		wxListBox* m_listBoxDevices;
		wxButton* m_buttonRefresh;
		wxButton* m_buttonCycle;
		wxButton* m_buttonConnect;
		wxButton* m_buttonDisconnect;
		wxButton* m_buttonClose;
		wxTextCtrl* m_textCtrlReceived;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCycle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClear( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUISetupMidi( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup MIDI Connection"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,482 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUISetupMidi();
	
};

#endif //__GUI_H__
