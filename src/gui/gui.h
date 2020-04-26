///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/docview.h>
#include <wx/config.h>

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
#include <wx/filepicker.h>
#include <wx/slider.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/radiobut.h>
#include <wx/dialog.h>
#include <wx/treelist.h>
#include <wx/dataview.h>
#include "CanvasTool.h"
#include "CanvasMachine.h"
#include <wx/menu.h>
#include <wx/listbox.h>

///////////////////////////////////////////////////////////////////////////

#define ID_NEW 1000
#define ID_OPEN 1001
#define ID_SAVE 1002
#define ID_VIEWPREFERENCES 1003
#define ID_TOGGLESTEREO3D 1004
#define ID_OBJECTLOAD 1005
#define ID_OBJECTFLIPNORMALS 1006
#define ID_OBJECTMODIFY 1007
#define ID_RUNMODIFY 1008
#define ID_2D 1009
#define ID_3D 1010
#define ID_DRILLING 1011
#define ID_MULTIAXIS 1012
#define ID_SIMULATE 1013
#define ID_TOOLPATHEXPORT 1014
#define ID_MANAGETOOLS 1015
#define ID_MANAGEMACHINES 1016
#define ID_GCODETEST 1017
#define ID_MULTTEN 1018
#define ID_DIVTEN 1019
#define ID_SCALEUNITX 1020
#define ID_SCALEUNITY 1021
#define ID_SCALEUNITZ 1022
#define ID_SCALEPERCENTX 1023
#define ID_SCALEPERCENTY 1024
#define ID_SCALEPERCENTZ 1025
#define ID_SCALEPERCENT 1026
#define ID_MOVEZP 1027
#define ID_MOVEYP 1028
#define ID_MOVEXN 1029
#define ID_MOVEXP 1030
#define ID_MOVEYN 1031
#define ID_MOVEZN 1032
#define ID_ALIGNTOP 1033
#define ID_ALIGNMIDDLE 1034
#define ID_ALIGNBOTTOM 1035
#define ID_ALIGNCENTER 1036
#define ID_ROTATEYN 1037
#define ID_ROTATEXN 1038
#define ID_ROTATEYP 1039
#define ID_ROTATEZN 1040
#define ID_ROTATEZP 1041
#define ID_ROTATEXP 1042
#define ID_FLIPX 1043
#define ID_FLIPY 1044
#define ID_FLIPZ 1045
#define ID_SELECTOBJECT 1046
#define ID_SELECTAXISX 1047
#define ID_SELECTAXISY 1048
#define ID_SELECTAXISZ 1049
#define ID_SETSIZEX 1050
#define ID_SETSIZEY 1051
#define ID_SETSIZEZ 1052
#define ID_SELECTOBJECTSTOCK 1053
#define ID_SELECTORIGIN 1054
#define ID_SELECTAREAOBJECT 1055
#define ID_TOOLLIBRARYMANAGE 1056
#define ID_SPEED 1057
#define ID_FEED 1058
#define ID_MARGINSIDE 1059
#define ID_MARGINBELOW 1060
#define ID_CLEARANCEHEIGHT 1061
#define wxID_LOAD 1062
#define ID_MACHINEDESCRIPTIONEVALUATE 1063
#define ID_MACHINEDEBUGGERSHOWCONTROLLER 1064
#define ID_SHOWPREFERENCES 1065
#define ID_MACHINEDEBUGGERTOGGLESTEREO3D 1066
#define ID_CONTROLLERSHOW 1067
#define ID_AXISX 1068
#define ID_AXISY 1069
#define ID_AXISZ 1070
#define ID_TEXTX 1071
#define ID_TEXTY 1072
#define ID_TEXTZ 1073
#define ID_AXISRX 1074
#define ID_AXISRY 1075
#define ID_AXISRZ 1076
#define ID_TEXTRX 1077
#define ID_TEXTRY 1078
#define ID_TEXTRZ 1079

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
		virtual void OnCAMManageMachines( wxRibbonButtonBarEvent& event ) = 0;
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
		wxButton* m_buttonCalculateX;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_textCtrlScaleUnitY;
		wxStaticText* m_staticTextUnitY2;
		wxButton* m_buttonCalculateY;
		wxStaticText* m_staticText52;
		wxTextCtrl* m_textCtrlScaleUnitZ;
		wxStaticText* m_staticTextUnitZ2;
		wxButton* m_buttonCalculateZ;
		wxCheckBox* m_checkBoxScaleProportionally;
		wxStaticText* m_staticText50;
		wxTextCtrl* m_textCtrlScalePercentX;
		wxStaticText* m_staticText51;
		wxButton* m_buttonScaleX;
		wxStaticText* m_staticText48;
		wxTextCtrl* m_textCtrlScalePercentY;
		wxStaticText* m_staticText55;
		wxButton* m_buttonScaleY;
		wxStaticText* m_staticText54;
		wxTextCtrl* m_textCtrlScalePercentZ;
		wxStaticText* m_staticText43;
		wxButton* m_buttonScaleZ;
		wxStaticText* m_staticText68;
		wxTextCtrl* m_textCtrlScalePercent;
		wxStaticText* m_staticText49;
		wxButton* m_buttonScaleAll;
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
		
		GUIObjectTransformation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 709,468 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
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
		wxPanel* m_panelSupports;
		wxScrolledWindow* m_scrolledWindowSupports;
		wxStaticText* m_staticTextSupportSlotwidth;
		wxTextCtrl* m_textCtrlSupportSlotwidth;
		wxStaticText* m_staticTextUnitSupportSlotwidth;
		wxStaticText* m_staticTextSupportWidth;
		wxTextCtrl* m_textCtrlSupportWidth;
		wxStaticText* m_staticTextUnitSupportWidth;
		wxStaticText* m_staticTextSupportHeight;
		wxTextCtrl* m_textCtrlSupportHeight;
		wxStaticText* m_staticTextUnitSupportHeight;
		wxChoice* m_choiceSupportLevel;
		wxStaticText* m_staticTextSupportLevel;
		wxTextCtrl* m_textCtrlSupportLevel;
		wxStaticText* m_staticTextUnitSupportLevel;
		wxStaticText* m_staticTextSupportXDistance;
		wxTextCtrl* m_textCtrlSupportXDistance;
		wxStaticText* m_staticTextUnitSupportXDistance;
		wxStaticText* m_staticTextSupportXOffset;
		wxTextCtrl* m_textCtrlSupportXOffset;
		wxStaticText* m_staticTextUnitSupportXOffset;
		wxStaticText* m_staticTextSupportYDistance;
		wxTextCtrl* m_textCtrlSupportYDistance;
		wxStaticText* m_staticTextUnitSupportYDistance;
		wxStaticText* m_staticTextSupportYOffset;
		wxTextCtrl* m_textCtrlSupportYOffset;
		wxStaticText* m_staticTextUnitSupportYOffset;
		wxStaticText* m_staticTextSupportOCount;
		wxTextCtrl* m_textCtrlSupportOCount;
		wxStaticText* m_staticTextSupportOOffset;
		wxTextCtrl* m_textCtrlSupportOOffset;
		wxStaticText* m_staticTextUnitSupportOOffset;
		wxPanel* m_panelMachine;
		wxStaticText* m_staticTextMachine;
		wxFilePickerCtrl* m_filePickerMachine;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnSelect( wxCommandEvent& event ) = 0;
		virtual void OnChoicebookPageChanged( wxChoicebookEvent& event ) = 0;
		virtual void OnTextEnter( wxCommandEvent& event ) = 0;
		virtual void OnGetSizeFromObject( wxCommandEvent& event ) = 0;
		virtual void OnRadioBox( wxCommandEvent& event ) = 0;
		virtual void OnMachineSelected( wxFileDirPickerEvent& event ) = 0;
		
	
	public:
		
		GUIJobSetup( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
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
		
		GUIToolpathGenerator( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 491,611 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		wxChoice* m_choiceDisplay;
		wxChoice* m_choiceFocus;
		
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
		
		GUIAnimation( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Simulation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		
		GUIPostProcess( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 536,300 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		
		GUITestGCode( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("G-Code parser"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		
		GUISetupPaths( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Paths"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 701,469 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
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
		wxStaticText* m_staticTextType;
		wxScrolledWindow* m_scrolledWindowType;
		wxChoice* m_choiceType;
		wxStaticText* m_staticText81;
		wxTextCtrl* m_textCtrlShaftDiameter2;
		wxStaticText* m_staticText101;
		wxTextCtrl* m_textCtrlShaftLength1;
		wxStaticText* m_staticText131;
		wxTextCtrl* m_textCtrlMaxSpeed1;
		wxStaticText* m_staticText141;
		wxTextCtrl* m_textCtrlFeedCoefficient1;
		wxStaticText* m_staticTextFlutes1;
		wxTextCtrl* m_textCtrlNrOfTeeth1;
		wxStaticText* m_staticTextComment1;
		wxTextCtrl* m_textCtrlComment1;
		wxStaticText* m_staticText186;
		wxTextCtrl* m_textCtrl101;
		wxRadioBox* m_radioBox3;
		wxPanel* m_panelGeometry;
		wxScrolledWindow* m_scrolledWindowTool;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textCtrl90;
		wxStaticText* m_staticText162;
		wxStaticText* m_staticText164;
		wxTextCtrl* m_textCtrlShaftDiameter;
		wxStaticText* m_staticTextUnitShaftDiameter;
		wxStaticText* m_staticText163;
		wxTextCtrl* m_textCtrl91;
		wxStaticText* m_staticText165;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textCtrlShaftLength;
		wxStaticText* m_staticTextUnitShaftLength;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrlMaxSpeed;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlFeedCoefficient;
		wxStaticText* m_staticTextFlutes;
		wxTextCtrl* m_textCtrlNrOfTeeth;
		wxStaticText* m_staticText166;
		wxStaticText* m_staticTextComment;
		wxTextCtrl* m_textCtrlComment;
		wxStaticText* m_staticText167;
		wxStaticText* m_staticText168;
		wxTextCtrl* m_textCtrl92;
		wxStaticText* m_staticText169;
		wxStaticText* m_staticText170;
		wxChoice* m_choice13;
		wxStaticText* m_staticText172;
		wxChoice* m_choice12;
		wxStaticText* m_staticText174;
		wxTextCtrl* m_textCtrl95;
		wxStaticText* m_staticText175;
		wxStaticText* m_staticText176;
		wxTextCtrl* m_textCtrl96;
		wxStaticText* m_staticText177;
		wxStaticText* m_staticText178;
		wxTextCtrl* m_textCtrl97;
		wxStaticText* m_staticText179;
		wxStaticText* m_staticText180;
		wxTextCtrl* m_textCtrl98;
		wxStaticText* m_staticText1811;
		wxStaticText* m_staticText1821;
		wxTextCtrl* m_textCtrl99;
		wxStaticText* m_staticText183;
		wxStaticText* m_staticText184;
		wxTextCtrl* m_textCtrl100;
		wxStaticText* m_staticText185;
		wxPanel* m_panelShape;
		wxCheckBox* m_checkBoxShape;
		wxButton* m_buttonShapeNew2;
		wxButton* m_buttonShapeUpdate2;
		wxButton* m_buttonShapeDelete2;
		wxStaticText* m_staticText182;
		wxTextCtrl* m_textCtrlDiameter3;
		wxStaticText* m_staticTextUnitDiameter3;
		wxStaticText* m_staticText202;
		wxTextCtrl* m_textCtrlHeight2;
		wxStaticText* m_staticTextUnitHeight2;
		wxStaticText* m_staticText222;
		wxTextCtrl* m_textCtrlRadius2;
		wxStaticText* m_staticTextUnitRadius2;
		wxDataViewListCtrl* m_dataViewListCtrlShape;
		wxDataViewColumn* m_dataViewListColumn7;
		wxDataViewColumn* m_dataViewListColumn8;
		wxDataViewColumn* m_dataViewListColumn9;
		wxPanel* m_panelHolder;
		wxChoice* m_choiceHolder;
		wxButton* m_buttonShapeNew1;
		wxButton* m_buttonShapeUpdate1;
		wxButton* m_buttonShapeDelete1;
		wxStaticText* m_staticText181;
		wxTextCtrl* m_textCtrlDiameter2;
		wxStaticText* m_staticTextUnitDiameter2;
		wxStaticText* m_staticText201;
		wxTextCtrl* m_textCtrlHeight1;
		wxStaticText* m_staticTextUnitHeight1;
		wxStaticText* m_staticText221;
		wxTextCtrl* m_textCtrlRadius1;
		wxStaticText* m_staticTextUnitRadius1;
		wxDataViewListCtrl* m_dataViewListCtrl2;
		wxDataViewColumn* m_dataViewListColumn4;
		wxDataViewColumn* m_dataViewListColumn5;
		wxDataViewColumn* m_dataViewListColumn6;
		wxPanel* m_panelShaft;
		wxCheckBox* m_checkBoxShaft;
		wxButton* m_buttonShapeNew;
		wxButton* m_buttonShapeUpdate;
		wxButton* m_buttonShapeDelete;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textCtrlDiameter;
		wxStaticText* m_staticTextUnitDiameter;
		wxStaticText* m_staticText20;
		wxTextCtrl* m_textCtrlHeight;
		wxStaticText* m_staticTextUnitHeight;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrlRadius;
		wxStaticText* m_staticTextUnitRadius;
		wxDataViewListCtrl* m_dataViewListCtrl3;
		wxDataViewColumn* m_dataViewListColumn1;
		wxDataViewColumn* m_dataViewListColumn2;
		wxDataViewColumn* m_dataViewListColumn3;
		wxPanel* m_panelFeedsSpeeds;
		wxScrolledWindow* m_scrolledWindow4;
		wxStaticText* m_staticTextTipDiameter11;
		wxTextCtrl* m_textCtrlTipDiameter11;
		wxStaticText* m_staticTextUnitTipDiameter11;
		wxStaticText* m_staticTextShaftDiameter11;
		wxTextCtrl* m_textCtrlShaftDiameter111;
		wxStaticText* m_staticTextUnitShaftDiameter111;
		wxStaticText* m_staticTextLengthOutside11;
		wxTextCtrl* m_textCtrlLengthOutside11;
		wxStaticText* m_staticTextUnitLengthOutside11;
		wxStaticText* m_staticTextLengthCutting11;
		wxTextCtrl* m_textCtrlLengthCutting11;
		wxStaticText* m_staticTextUnitLengthCutting11;
		wxStaticText* m_staticTextDiameter;
		wxTextCtrl* m_textCtrlDiameter1;
		wxStaticText* m_staticTextUnitDiameter1;
		wxStaticText* m_staticTextShaftDiameter;
		wxTextCtrl* m_textCtrlShaftDiameter1;
		wxStaticText* m_staticTextUnitShaftDiameter1;
		wxStaticText* m_staticTextLengthOutside;
		wxTextCtrl* m_textCtrlLengthOutside;
		wxStaticText* m_staticTextUnitLengthOutside;
		wxStaticText* m_staticTextLengthCutting;
		wxTextCtrl* m_textCtrlLengthCutting;
		wxStaticText* m_staticTextUnitLengthCutting;
		wxStaticText* m_staticTextDiameter1;
		wxTextCtrl* m_textCtrlDiameter11;
		wxStaticText* m_staticTextUnitDiameter11;
		wxStaticText* m_staticTextTipDiameter1;
		wxTextCtrl* m_textCtrlTipDiameter1;
		wxStaticText* m_staticTextUnitTipDiameter1;
		wxStaticText* m_staticTextShaftDiameter1;
		wxTextCtrl* m_textCtrlShaftDiameter11;
		wxStaticText* m_staticTextUnitShaftDiameter11;
		wxStaticText* m_staticTextLengthOutside1;
		wxTextCtrl* m_textCtrlLengthOutside1;
		wxStaticText* m_staticTextUnitLengthOutside1;
		wxStaticText* m_staticTextLengthCutting1;
		wxTextCtrl* m_textCtrlLengthCutting1;
		wxStaticText* m_staticTextUnitLengthCutting1;
		wxStaticText* m_staticTextToolLength1;
		wxTextCtrl* m_textCtrlToolLength1;
		wxStaticText* m_staticTextUnitToolLength1;
		wxStaticText* m_staticTextDiameter11;
		wxTextCtrl* m_textCtrlDiameter111;
		wxStaticText* m_staticTextUnitDiameter111;
		wxPanel* m_panelPostprocess;
		wxScrolledWindow* m_scrolledWindow5;
		wxCheckBox* m_checkBox5;
		wxStaticText* m_staticText1661;
		wxTextCtrl* m_textCtrl931;
		wxStaticText* m_staticText1711;
		wxTextCtrl* m_textCtrl981;
		wxCheckBox* m_checkBox6;
		wxCheckBox* m_checkBox7;
		wxStaticText* m_staticText1671;
		wxTextCtrl* m_textCtrl941;
		wxStaticText* m_staticText1681;
		wxTextCtrl* m_textCtrl951;
		wxStaticText* m_staticText1691;
		wxTextCtrl* m_textCtrl961;
		wxStaticText* m_staticText1701;
		wxTextCtrl* m_textCtrl971;
		CanvasTool* m_canvasshaft;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnItemChecked( wxTreeListEvent& event ) = 0;
		virtual void OnItemContextMenu( wxTreeListEvent& event ) = 0;
		virtual void OnSelectionChanged( wxTreeListEvent& event ) = 0;
		virtual void OnEnter( wxCommandEvent& event ) = 0;
		virtual void OnShapeNew( wxCommandEvent& event ) = 0;
		virtual void OnShapeUpdate( wxCommandEvent& event ) = 0;
		virtual void OnShapeDelete( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIToolbox( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Toolbox"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIToolbox();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMachineDebugger
///////////////////////////////////////////////////////////////////////////////
class GUIMachineDebugger : public wxFrame 
{
	private:
	
	protected:
		wxRibbonBar* m_ribbonBar;
		wxRibbonPage* m_ribbonPage;
		wxRibbonPanel* m_ribbonPanelFileOperations;
		wxRibbonButtonBar* m_ribbonButtonBarScript;
		wxRibbonPanel* m_ribbonPanelSettings;
		wxRibbonButtonBar* m_ribbonButtonBarSettings;
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
		virtual void OnMachineLoad( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnMachineSave( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnScriptEvaluate( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnShowController( wxCommandEvent& event ) = 0;
		virtual void OnShowPreferencesMenu( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnToggleStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnScriptEvaluate( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIMachineDebugger( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine Debugger"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 831,596 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		wxStaticText* m_staticTextX;
		wxSlider* m_sliderX;
		wxStaticText* m_staticTextY;
		wxSlider* m_sliderY;
		wxStaticText* m_staticTextZ;
		wxSlider* m_sliderZ;
		wxStaticText* m_staticTexttX;
		wxTextCtrl* m_textCtrlX;
		wxStaticText* m_staticTextUnitX;
		wxStaticText* m_staticTexttY;
		wxTextCtrl* m_textCtrlY;
		wxStaticText* m_staticTextUnitY;
		wxStaticText* m_staticTexttZ;
		wxTextCtrl* m_textCtrlZ;
		wxStaticText* m_staticTextUnitZ;
		wxStaticText* m_staticTextRX;
		wxSlider* m_sliderRX;
		wxStaticText* m_staticTextRY;
		wxSlider* m_sliderRY;
		wxStaticText* m_staticTextRZ;
		wxSlider* m_sliderRZ;
		wxStaticText* m_staticTextrRX;
		wxTextCtrl* m_textCtrlRX;
		wxStaticText* m_staticTextUnitRX;
		wxStaticText* m_staticTextrRY;
		wxTextCtrl* m_textCtrlRY;
		wxStaticText* m_staticTextUnitRY;
		wxStaticText* m_staticTextrRZ;
		wxTextCtrl* m_textCtrlRZ;
		wxStaticText* m_staticTextUnitRZ;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnZero( wxMouseEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnTrack( wxScrollEvent& event ) = 0;
		virtual void OnTextChanged( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIMachineControl( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Machine Controller"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,500 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
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
		
		GUISetupUnits( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup Display Units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
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
		
		GUISetupMidi( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup MIDI Connection"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,482 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~GUISetupMidi();
	
};

#endif //__GUI_H__
