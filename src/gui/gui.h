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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/page.h>
#include <wx/ribbon/control.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/panel.h>
#include "CanvasMain.h"
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/bmpbuttn.h>
#include <wx/notebook.h>
#include <wx/radiobox.h>
#include <wx/choicebk.h>
#include <wx/choice.h>
#include <wx/scrolwin.h>
#include <wx/slider.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/filepicker.h>
#include <wx/radiobut.h>
#include <wx/dialog.h>
#include <wx/treelist.h>
#include "PanelTool.h"
#include <wx/listctrl.h>
#include "CanvasTool.h"
#include <wx/statline.h>
#include <wx/menu.h>
#include "CanvasMachine.h"
#include <wx/listbox.h>
#include <wx/richtext/richtextctrl.h>

///////////////////////////////////////////////////////////////////////////

#define ID_VIEWPREFERENCES 1000
#define ID_TOGGLESTEREO3D 1001
#define ID_OBJECTLOAD 1002
#define ID_OBJECTFLIPNORMALS 1003
#define ID_OBJECTMODIFY 1004
#define ID_RUNMODIFY 1005
#define ID_2D 1006
#define ID_3D 1007
#define ID_DRILLING 1008
#define ID_MULTIAXIS 1009
#define ID_SIMULATE 1010
#define ID_TOOLPATHEXPORT 1011
#define ID_MANAGETOOLS 1012
#define ID_MANAGEPOSTPROCESS 1013
#define ID_MANAGEMACHINES 1014
#define ID_TOOLMEASURE 1015
#define ID_GCODETEST 1016
#define ID_MULTTEN 1017
#define ID_DIVTEN 1018
#define ID_SCALEUNITX 1019
#define ID_SCALEUNITY 1020
#define ID_SCALEUNITZ 1021
#define ID_SCALEPERCENTX 1022
#define ID_SCALEPERCENTY 1023
#define ID_SCALEPERCENTZ 1024
#define ID_SCALEPERCENT 1025
#define ID_MOVEZP 1026
#define ID_MOVEYP 1027
#define ID_MOVEXN 1028
#define ID_MOVEXP 1029
#define ID_MOVEYN 1030
#define ID_MOVEZN 1031
#define ID_ALIGNTOP 1032
#define ID_ALIGNMIDDLE 1033
#define ID_ALIGNBOTTOM 1034
#define ID_ALIGNCENTER 1035
#define ID_ROTATEYN 1036
#define ID_ROTATEXN 1037
#define ID_ROTATEYP 1038
#define ID_ROTATEZN 1039
#define ID_ROTATEZP 1040
#define ID_ROTATEXP 1041
#define ID_FLIPX 1042
#define ID_FLIPY 1043
#define ID_FLIPZ 1044
#define ID_SELECTOBJECT 1045
#define ID_SELECTAXISX 1046
#define ID_SELECTAXISY 1047
#define ID_SELECTAXISZ 1048
#define ID_SETSIZEX 1049
#define ID_SETSIZEY 1050
#define ID_SETSIZEZ 1051
#define ID_SELECTOBJECTSTOCK 1052
#define ID_SELECTORIGIN 1053
#define ID_SELECTAREAOBJECT 1054
#define ID_TOOLLIBRARYMANAGE 1055
#define ID_SPEED 1056
#define ID_FEED 1057
#define ID_MARGINSIDE 1058
#define ID_MARGINBELOW 1059
#define ID_CLEARANCEHEIGHT 1060
#define ID_CONTROLLERSHOW 1061
#define ID_VIEWSTEREO3D 1062
#define ID_AXISX 1063
#define ID_AXISY 1064
#define ID_AXISZ 1065
#define ID_TEXTX 1066
#define ID_TEXTY 1067
#define ID_TEXTZ 1068
#define ID_AXISA 1069
#define ID_AXISB 1070
#define ID_AXISC 1071
#define ID_TEXTA 1072
#define ID_TEXTB 1073
#define ID_TEXTC 1074
#define ID_AXISU 1075
#define ID_AXISV 1076
#define ID_AXISW 1077
#define ID_TEXTU 1078
#define ID_TEXTV 1079
#define ID_TEXTW 1080

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameMain
///////////////////////////////////////////////////////////////////////////////
class GUIFrameMain : public wxDocChildFrame
{
	private:
	
	protected:
		wxRibbonBar* m_ribbonBarProjectViewEdit;
		wxRibbonPage* m_ribbonPageViewEdit;
		wxRibbonPanel* m_ribbonPanelProject;
		wxRibbonButtonBar* m_ribbonButtonBarProject;
		wxRibbonPanel* m_ribbonPanelView;
		wxRibbonButtonBar* m_ribbonButtonBarView;
		wxRibbonPanel* m_ribbonPanelEdit;
		wxRibbonButtonBar* m_ribbonButtonBarEdit;
		wxRibbonBar* m_ribbonBarCANCAM;
		wxRibbonPage* m_ribbonPageCAD;
		wxRibbonPanel* m_ribbonPanelObject;
		wxRibbonButtonBar* m_ribbonButtonBarObject;
		wxRibbonPage* m_ribbonPageCAM;
		wxRibbonPanel* m_ribbonPanelSetup;
		wxRibbonButtonBar* m_ribbonButtonBarSetup;
		wxRibbonPanel* m_ribbonPanelToolpath;
		wxRibbonButtonBar* m_ribbonButtonBarToolpath;
		wxRibbonPanel* m_ribbonPanelPostProcess;
		wxRibbonButtonBar* m_ribbonButtonBarPostProcess;
		wxRibbonPanel* m_ribbonPanelManage;
		wxRibbonButtonBar* m_ribbonButtonBarManageCam;
		wxRibbonPanel* m_ribbonPanelTools;
		wxRibbonButtonBar* m_ribbonButtonBarTools;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panelTree;
		wxTreeCtrl* m_tree;
		wxPanel* m_panelCanvasMain;
		CanvasMain* m_canvas;
		wxStatusBar* m_statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) = 0;
		virtual void OnSize( wxSizeEvent& event ) = 0;
		virtual void OnProjectNew( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnProjectOpen( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnProjectOpenMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnProjectSave( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnProjectSaveMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnViewPreferencesMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnViewStereo3DToggle( wxCommandEvent& event ) = 0;
		virtual void OnUndo( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnRedo( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnHelp( wxRibbonBarEvent& event ) = 0;
		virtual void OnObjectLoad( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnObjectFlipNormals( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnObjectModify( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMSetup( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAM2DMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAM3DMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMDrilling( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMMultiAxisMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMPostProcessSimulate( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMPostProcessExport( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMManageTools( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMManagePostProcesses( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMManageMachines( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMToolsMeasure( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnCAMToolsTestGCode( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnChar( wxKeyEvent& event ) = 0;
		virtual void OnBeginLabelEdit( wxTreeEvent& event ) = 0;
		virtual void OnEndLabelEdit( wxTreeEvent& event ) = 0;
		virtual void OnActivate( wxTreeEvent& event ) = 0;
		virtual void OnActivateRightClickMenu( wxTreeEvent& event ) = 0;
		virtual void OnSelectionChanged( wxTreeEvent& event ) = 0;
		virtual void OnSelectionChanging( wxTreeEvent& event ) = 0;
		virtual void On3DSelect( wxMouseEvent& event ) = 0;
		virtual void On3DMotion( wxMouseEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Generic CAM"), const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 1261,581 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
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
		virtual void OnTransform( wxCommandEvent& event ) = 0;
		virtual void OnSetFactors( wxCommandEvent& event ) = 0;
		virtual void OnFlipNormals( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIObjectTransformation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Object Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 709,468 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~GUIObjectTransformation();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIJobSetup
///////////////////////////////////////////////////////////////////////////////
class GUIJobSetup : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook;
		wxPanel* m_panelObject;
		wxButton* m_buttonSelectObject;
		wxTextCtrl* m_textCtrlObject;
		wxPanel* m_panelCoordinates;
		wxButton* m_buttonAxisX;
		wxTextCtrl* m_textCtrlAxisX;
		wxButton* m_buttonAxisY;
		wxTextCtrl* m_textCtrlAxisY;
		wxButton* m_buttonAxisZ;
		wxTextCtrl* m_textCtrlAxisZ;
		wxPanel* m_panelStock;
		wxChoicebook* m_choicebookStock;
		wxPanel* m_panelStockBox;
		wxStaticText* m_staticTextBoxX;
		wxTextCtrl* m_textCtrlBoxX;
		wxStaticText* m_staticTextUnitBoxX;
		wxStaticText* m_staticTextBoxY;
		wxTextCtrl* m_textCtrlBoxY;
		wxStaticText* m_staticTextUnitBoxY;
		wxStaticText* m_staticTextBoxZ;
		wxTextCtrl* m_textCtrlBoxZ;
		wxStaticText* m_staticTextUnitBoxZ;
		wxButton* m_buttonFromObject;
		wxRadioBox* m_radioBox;
		wxPanel* m_panelStockObject;
		wxTextCtrl* m_textCtrlStockObject;
		wxButton* m_buttonStockObjectSelect;
		wxPanel* m_panelOrigin;
		wxTextCtrl* m_textCtrlOrigin;
		wxButton* m_buttonOrigin;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSelect( wxCommandEvent& event ) = 0;
		virtual void OnChoicebookPageChanged( wxChoicebookEvent& event ) = 0;
		virtual void OnTextEnter( wxCommandEvent& event ) = 0;
		virtual void OnGetSizeFromObject( wxCommandEvent& event ) = 0;
		virtual void OnRadioBox( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIJobSetup( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Run"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 407,465 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~GUIJobSetup();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIToolpathGenerator
///////////////////////////////////////////////////////////////////////////////
class GUIToolpathGenerator : public wxFrame 
{
	private:
	
	protected:
		wxScrolledWindow* m_scrolledWindow;
		wxTextCtrl* m_textCtrlGeometry;
		wxButton* m_buttonSelectGeometry;
		wxChoice* m_choiceTool;
		wxButton* m_buttonToolSelect;
		wxStaticText* m_staticTextSpindle;
		wxTextCtrl* m_textCtrlSpindle;
		wxStaticText* m_staticTextUnitSpindle;
		wxStaticText* m_staticTextFeed;
		wxTextCtrl* m_textCtrlFeed;
		wxStaticText* m_staticTextUnitFeed;
		wxStaticText* m_staticTextSide;
		wxTextCtrl* m_textCtrlMarginSide;
		wxStaticText* m_staticTextUnitMarginSide;
		wxStaticText* m_staticTextBelow;
		wxTextCtrl* m_textCtrlMarginBelow;
		wxStaticText* m_staticTextUnitMarginBelow;
		wxStaticText* m_staticTextFreeHeight;
		wxTextCtrl* m_textCtrlFreeHeight;
		wxStaticText* m_staticTextUnitFreeHeight;
		wxPanel* m_panel;
		wxButton* m_buttonUpdate;
		wxTextCtrl* m_textCtrlInfo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChar( wxKeyEvent& event ) = 0;
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnLeftDown( wxMouseEvent& event ) = 0;
		virtual void OnSelectArea( wxCommandEvent& event ) = 0;
		virtual void OnSelectTool( wxCommandEvent& event ) = 0;
		virtual void OnTextEnter( wxCommandEvent& event ) = 0;
		virtual void OnUpdate( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIToolpathGenerator( wxWindow* parent, wxWindowID id = wxID_CLOSE, const wxString& title = _("..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 491,611 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIToolpathGenerator();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAnimation
///////////////////////////////////////////////////////////////////////////////
class GUIAnimation : public wxFrame 
{
	private:
	
	protected:
		wxSlider* m_sliderTime;
		wxStaticText* m_staticTextTime;
		wxTextCtrl* m_textCtrlTime;
		wxStaticText* m_staticTextSlash;
		wxTextCtrl* m_textCtrlMaxTime;
		wxBitmapButton* m_bpButtonFirst;
		wxBitmapButton* m_bpButtonPrev;
		wxBitmapButton* m_bpButtonPlayStop;
		wxBitmapButton* m_bpButtonNext;
		wxBitmapButton* m_bpButtonLast;
		wxCheckBox* m_checkBoxSimulateWorkpiece;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnChangeTime( wxCommandEvent& event ) = 0;
		virtual void OnFirst( wxCommandEvent& event ) = 0;
		virtual void OnPrev( wxCommandEvent& event ) = 0;
		virtual void OnPlayStop( wxCommandEvent& event ) = 0;
		virtual void OnNext( wxCommandEvent& event ) = 0;
		virtual void OnLast( wxCommandEvent& event ) = 0;
		virtual void OnChangeSimulation( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIAnimation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolpath Animation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 750,120 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIAnimation();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIPostProcess
///////////////////////////////////////////////////////////////////////////////
class GUIPostProcess : public wxFrame 
{
	private:
	
	protected:
		wxChoice* m_choiceSelect;
		wxButton* m_buttonRefresh;
		wxPropertyGrid* m_propertyGrid;
		wxFilePickerCtrl* m_filePickerExport;
		wxButton* m_buttonExport;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnChoice( wxCommandEvent& event ) = 0;
		virtual void OnRefresh( wxCommandEvent& event ) = 0;
		virtual void OnPropertyGridChange( wxPropertyGridEvent& event ) = 0;
		virtual void OnExport( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIPostProcess( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Post-Process"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 536,300 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxTAB_TRAVERSAL );
		
		~GUIPostProcess();
	
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
		
		GUITestGCode( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("G-Code parser"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUITestGCode();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUISetupPaths
///////////////////////////////////////////////////////////////////////////////
class GUISetupPaths : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextProject;
		wxDirPickerCtrl* m_dirPickerProjectDirectory;
		wxStaticText* m_staticTextObjectDirectory;
		wxDirPickerCtrl* m_dirPickerObjectDirectory;
		wxStaticText* m_staticTextToolpathDirectory;
		wxDirPickerCtrl* m_dirPickerToolpathDirectory;
		wxStaticText* m_staticTextToolboxDirectory;
		wxDirPickerCtrl* m_dirPickerToolboxDirectory;
		wxStaticText* m_staticTextPostProcessorDirectory;
		wxDirPickerCtrl* m_dirPickerPostProcessorDirectory;
		wxStaticText* m_staticTextMachineDirectory;
		wxDirPickerCtrl* m_dirPickerMachineDirectory;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUISetupPaths( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Path Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 701,469 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~GUISetupPaths();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIToolbox
///////////////////////////////////////////////////////////////////////////////
class GUIToolbox : public wxFrame 
{
	private:
	
	protected:
		wxTreeListCtrl* m_treeListCtrl;
		wxNotebook* m_notebook;
		wxPanel* m_panelTool;
		wxRadioBox* m_radioBoxToolType;
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
		PanelTool* m_paneltool;
		wxPanel* m_panelShaft;
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
		CanvasTool* m_canvasshaft;
		wxPanel* m_panelHolder;
		CanvasTool* m_canvasholder;
		wxPanel* m_panelFeedsSpeeds;
		wxStaticText* m_staticTextDiameter;
		wxTextCtrl* m_textCtrlDiameter1;
		wxStaticText* m_staticTextUnitDiameter1;
		wxStaticText* m_staticTextTipDiameter;
		wxTextCtrl* m_textCtrlTipDiameter;
		wxStaticText* m_staticTextUnitTipDiameter;
		wxStaticText* m_staticTextShaftDiameter;
		wxTextCtrl* m_textCtrlShaftDiameter1;
		wxStaticText* m_staticTextUnitShaftDiameter1;
		wxStaticLine* m_staticline1;
		wxStaticLine* m_staticline2;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticTextLengthOutside;
		wxTextCtrl* m_textCtrlLengthOutside;
		wxStaticText* m_staticTextUnitLengthOutside;
		wxStaticText* m_staticTextLengthCutting;
		wxTextCtrl* m_textCtrlLengthCutting;
		wxStaticText* m_staticTextUnitLengthCutting;
		wxStaticText* m_staticTextToolLength;
		wxTextCtrl* m_textCtrlToolLength;
		wxStaticText* m_staticTextUnitToolLength;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnItemChecked( wxTreeListEvent& event ) = 0;
		virtual void OnItemContextMenu( wxTreeListEvent& event ) = 0;
		virtual void OnSelectionChanged( wxTreeListEvent& event ) = 0;
		virtual void OnEnter( wxCommandEvent& event ) = 0;
		virtual void OnShapeNew( wxCommandEvent& event ) = 0;
		virtual void OnShapeUpdate( wxCommandEvent& event ) = 0;
		virtual void OnShapeDelete( wxCommandEvent& event ) = 0;
		virtual void OnShapeSelect( wxListEvent& event ) = 0;
		
	
	public:
		
		GUIToolbox( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolbox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1089,944 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIToolbox();
	
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
		wxMenu* m_menuPreferences;
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
		
		GUIMachineDebugger( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine debugger"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 831,596 ), long style = wxCAPTION|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		wxMenu* m_menuPreferences;
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
		
		GUIMachineControl( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,500 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIMachineControl();
	
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
		
		GUISetupMidi( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup MIDI Connection"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,482 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~GUISetupMidi();
	
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
		
		GUIDialogAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 504,373 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSTAY_ON_TOP ); 
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

#endif //__GUI_H__
