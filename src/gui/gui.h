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

#define ID_VIEWPREFERENCES 1000
#define ID_TOGGLESTEREO3D 1001
#define ID_OBJECTLOAD 1002
#define ID_OBJECTMODIFY 1003
#define ID_OBJECTUNIFYSURFACE 1004
#define ID_OBJECTFLIPNORMALS 1005
#define ID_RUNMODIFY 1006
#define ID_2D 1007
#define ID_3D 1008
#define ID_DRILLING 1009
#define ID_MULTIAXIS 1010
#define ID_SIMULATE 1011
#define ID_TOOLPATHEXPORT 1012
#define ID_MANAGETOOLS 1013
#define ID_MANAGEMACHINES 1014
#define ID_GCODETEST 1015
#define ID_MULTTEN 1016
#define ID_DIVTEN 1017
#define ID_SCALEUNITX 1018
#define ID_SCALEUNITY 1019
#define ID_SCALEUNITZ 1020
#define ID_SCALEPERCENTX 1021
#define ID_SCALEPERCENTY 1022
#define ID_SCALEPERCENTZ 1023
#define ID_SCALEPERCENT 1024
#define ID_MOVEZP 1025
#define ID_MOVEYP 1026
#define ID_MOVEXN 1027
#define ID_MOVEXP 1028
#define ID_MOVEYN 1029
#define ID_MOVEZN 1030
#define ID_ALIGNTOP 1031
#define ID_ALIGNMIDDLE 1032
#define ID_ALIGNBOTTOM 1033
#define ID_ALIGNCENTER 1034
#define ID_ROTATEYN 1035
#define ID_ROTATEXN 1036
#define ID_ROTATEYP 1037
#define ID_ROTATEZN 1038
#define ID_ROTATEZP 1039
#define ID_ROTATEXP 1040
#define ID_FLIPX 1041
#define ID_FLIPY 1042
#define ID_FLIPZ 1043
#define ID_SELECTOBJECT 1044
#define ID_SELECTAXISX 1045
#define ID_SELECTAXISY 1046
#define ID_SELECTAXISZ 1047
#define ID_SETSIZEX 1048
#define ID_SETSIZEY 1049
#define ID_SETSIZEZ 1050
#define ID_SELECTOBJECTSTOCK 1051
#define ID_SELECTORIGIN 1052
#define ID_SELECTAREAOBJECT 1053
#define ID_TOOLLIBRARYMANAGE 1054
#define ID_SPEED 1055
#define ID_FEED 1056
#define ID_MARGINSIDE 1057
#define ID_MARGINBELOW 1058
#define ID_CLEARANCEHEIGHT 1059
#define ID_TOOLBOXLIST 1060
#define ID_TOOLTYPE 1061
#define ID_TOOLDESCRIPTION 1062
#define ID_TOOLVENDOR 1063
#define ID_TOOLGUID 1064
#define ID_TOOLPRODUCTID 1065
#define ID_TOOLPRODUCTLINK 1066
#define ID_TOOLGRADE 1067
#define ID_TOOLBMC 1068
#define ID_TOOLUNIT 1069
#define ID_TOOLDC 1070
#define ID_TOOLLCF 1071
#define ID_TOOLLB 1072
#define ID_TOOLOAL 1073
#define ID_TOOLNOF 1074
#define ID_TOOLNT 1075
#define ID_TOOLRE 1076
#define ID_TOOLSIG 1077
#define ID_TOOLTA 1078
#define ID_TOOLCSP 1079
#define ID_TOOLHAND 1080
#define ID_TOOLSFDM 1081
#define ID_TOOLSHOULDERLENGTH 1082
#define ID_TOOLTIPDIAMETER 1083
#define ID_TOOLLENGTH 1084
#define ID_TOOLTIPOFFSET 1085
#define ID_THREADPROFILEANGLE 1086
#define ID_SHAPEFROMGEOMETRY 1087
#define ID_SHAPESEGMENTADD 1088
#define ID_SHAPESEGMENTDELETE 1089
#define ID_SHAPEUPPERDIAMETER 1090
#define ID_SHAPELOWERDIAMETER 1091
#define ID_SHAPEHEIGHT 1092
#define ID_SHAFTFROMGEOMETRY 1093
#define ID_SHAFTSEGMENTADD 1094
#define ID_SHAFTSEGMENTDELETE 1095
#define ID_SHAFTUPPERDIAMETER 1096
#define ID_SHAFTLOWERDIAMETER 1097
#define ID_SHAFTHEIGHT 1098
#define ID_HOLDERSEGMENTADD 1099
#define ID_HOLDERSEGMENTDELETE 1100
#define ID_UPPERDIAMETER 1101
#define ID_HOLDERLOWERDIAMETER 1102
#define ID_HOLDERHEIGHT 1103
#define ID_SETNAME 1104
#define ID_SETGUID 1105
#define ID_SETDESCRIPTION 1106
#define ID_SETTOOLCOOLANT 1107
#define ID_FEEDPERREVOLUTION 1108
#define ID_FEEDPERTOOTH 1109
#define ID_SPINDLESPEED 1110
#define ID_SPINDLESPEEDRAMP 1111
#define ID_CUTTINGFEEDRATE 1112
#define ID_AVGFEEDRATE 1113
#define ID_LEADINFEEDRATE 1114
#define ID_LEADOUTFEEDRATE 1115
#define ID_PLUNGEFEEDRATE 1116
#define ID_RAMPFEEDRATE 1117
#define ID_RETRACTIONFEEDRATE 1118
#define ID_POSTPROCESSLIVE 1119
#define ID_POSTPROCESSCOMMENT 1120
#define ID_POSTPROCESSNUMBER 1121
#define ID_POSTPROCESSMANUALTOOLCHANGE 1122
#define ID_POSTPROCESSBREAKCONTROL 1123
#define ID_POSTPROCESSDIAMETEROFFSET 1124
#define ID_POSTPROCESSLENGTHOFFSET 1125
#define ID_POSTPROCESSTOOLCOOLANT 1126
#define ID_POSTPROCESSTURRET 1127
#define ID_MACHINEDESCRIPTIONLOAD 1128
#define ID_MACHINEDESCRIPTIONSAVE 1129
#define ID_MACHINEDESCRIPTIONEVALUATE 1130
#define ID_MACHINEDEBUGGERSHOWCONTROLLER 1131
#define ID_SHOWPREFERENCES 1132
#define ID_MACHINEDEBUGGERTOGGLESTEREO3D 1133
#define ID_CONTROLLERSHOW 1134
#define ID_AXISX 1135
#define ID_AXISY 1136
#define ID_AXISZ 1137
#define ID_TEXTX 1138
#define ID_TEXTY 1139
#define ID_TEXTZ 1140
#define ID_AXISRX 1141
#define ID_AXISRY 1142
#define ID_AXISRZ 1143
#define ID_TEXTRX 1144
#define ID_TEXTRY 1145
#define ID_TEXTRZ 1146

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
		virtual void OnObjectModify( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnObjectUnifySurface( wxRibbonButtonBarEvent& event ) = 0;
		virtual void OnObjectFlipNormals( wxRibbonButtonBarEvent& event ) = 0;
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
		virtual void OnChangeView( wxCommandEvent& event ) = 0;
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
		wxScrolledWindow* m_scrolledWindowTool;
		wxStaticText* m_staticTextToolType;
		wxChoice* m_choiceToolType;
		wxStaticText* m_staticTextToolDescription;
		wxTextCtrl* m_textCtrlToolDescription;
		wxStaticText* m_staticTextToolVendor;
		wxTextCtrl* m_textCtrlToolVendor;
		wxStaticText* m_staticTextToolGUID;
		wxTextCtrl* m_textCtrlToolGUID;
		wxStaticText* m_staticTextToolProductID;
		wxTextCtrl* m_textCtrlToolProductID;
		wxStaticText* m_staticTextToolProductLink;
		wxTextCtrl* m_textCtrlToolProductLink;
		wxStaticText* m_staticTextToolGrade;
		wxTextCtrl* m_textCtrlToolGrade;
		wxStaticText* m_staticTextToolBMC;
		wxTextCtrl* m_textCtrlToolBMC;
		wxRadioBox* m_radioBoxToolUnit;
		wxPanel* m_panelGeometry;
		wxScrolledWindow* m_scrolledWindowGeometry;
		wxStaticText* m_staticTextDC;
		wxTextCtrl* m_textCtrlDC;
		wxStaticText* m_staticTextUnitDC;
		wxStaticText* m_staticTextLCF;
		wxTextCtrl* m_textCtrlLCF;
		wxStaticText* m_staticTextUnitLCF;
		wxStaticText* m_staticTextLB;
		wxTextCtrl* m_textCtrlLB;
		wxStaticText* m_staticTextUnitLB;
		wxStaticText* m_staticTextOAL;
		wxTextCtrl* m_textCtrlOAL;
		wxStaticText* m_staticTextUnitOAL;
		wxStaticText* m_staticTextNOF;
		wxTextCtrl* m_textCtrlNOF;
		wxStaticText* m_staticTextNT;
		wxTextCtrl* m_textCtrlNT;
		wxStaticText* m_staticTextRE;
		wxTextCtrl* m_textCtrlRE;
		wxStaticText* m_staticTextUnitRE;
		wxStaticText* m_staticTextSIG;
		wxTextCtrl* m_textCtrlSIG;
		wxStaticText* m_staticTextUnitSIG;
		wxStaticText* m_staticTextTA;
		wxTextCtrl* m_textCtrlTA;
		wxStaticText* m_staticTextUnitTA;
		wxStaticText* m_staticTextCSP;
		wxChoice* m_choiceCSP;
		wxStaticText* m_staticTextHAND;
		wxChoice* m_choiceHAND;
		wxStaticText* m_staticTextSFDM;
		wxTextCtrl* m_textCtrlSFDM;
		wxStaticText* m_staticTextUnitSFDM;
		wxStaticText* m_staticTextShoulderLength;
		wxTextCtrl* m_textCtrlShoulderLength;
		wxStaticText* m_staticTextUnitShoulderLength;
		wxStaticText* m_staticTextTipDiameter;
		wxTextCtrl* m_textCtrlTipDiameter;
		wxStaticText* m_staticTextUnitTipDiameter;
		wxStaticText* m_staticTextTipLength;
		wxTextCtrl* m_textCtrlTipLength;
		wxStaticText* m_staticTextUnitTipLength;
		wxStaticText* m_staticTextTipOffset;
		wxTextCtrl* m_textCtrlTipOffset;
		wxStaticText* m_staticTextUnitTipOffset;
		wxStaticText* m_staticTextThreadProfileAngle;
		wxTextCtrl* m_textCtrlThreadProfileAngle;
		wxStaticText* m_staticTextUnitThreadProfileAngle;
		wxPanel* m_panelShape;
		wxCheckBox* m_checkBoxShapeFromGeometry;
		wxButton* m_buttonShapeSegmentAdd;
		wxButton* m_buttonShapeSegmentDelete;
		wxStaticText* m_staticTextShapeUpperDiameter;
		wxTextCtrl* m_textCtrlShapeUpperDiameter;
		wxStaticText* m_staticTextUnitShapeUpperDiameter;
		wxStaticText* m_staticTextShapeLowerDiameter;
		wxTextCtrl* m_textCtrlShapeLowerDiameter;
		wxStaticText* m_staticTextUnitShapeLowerDiameter;
		wxStaticText* m_staticTextShapeHeight;
		wxTextCtrl* m_textCtrlShapeHeight;
		wxStaticText* m_staticTextUnitShapeHeight;
		wxDataViewListCtrl* m_dataViewListCtrlShapeSegments;
		wxDataViewColumn* m_dataViewListColumnShapeUpper;
		wxDataViewColumn* m_dataViewListColumnShapeLower;
		wxDataViewColumn* m_dataViewListColumnShapeHeight;
		wxPanel* m_panelShaft;
		wxCheckBox* m_checkBoxShaftFromGeometry;
		wxButton* m_buttonShaftSegmentAdd;
		wxButton* m_buttonShapeDelete;
		wxStaticText* m_staticTextShaftUpperDiameter;
		wxTextCtrl* m_textCtrlShaftUpperDiameter;
		wxStaticText* m_staticTextUnitShaftUpperDiameter;
		wxStaticText* m_staticTextShaftLowerDiameter;
		wxTextCtrl* m_textCtrlShaftLowerDiameter;
		wxStaticText* m_staticTextUnitShaftLowerDiameter;
		wxStaticText* m_staticTextShaftHeight;
		wxTextCtrl* m_textCtrlShaftHeight;
		wxStaticText* m_staticTextUnitShaftHeight;
		wxDataViewListCtrl* m_dataViewListCtrlShaftSegments;
		wxDataViewColumn* m_dataViewListColumnShaftUpperDiameter;
		wxDataViewColumn* m_dataViewListColumnShaftLowerDiameter;
		wxDataViewColumn* m_dataViewListColumnShaftHeight;
		wxPanel* m_panelHolder;
		wxChoice* m_choiceHolder;
		wxButton* m_buttonHolderSegmentAdd;
		wxButton* m_buttonHolderSegmentDelete;
		wxStaticText* m_staticTextHolderUpperDiameter;
		wxTextCtrl* m_textCtrlHolderUpperDiameter;
		wxStaticText* m_staticTextUnitHolderUpperDiameter;
		wxStaticText* m_staticTextHolderLowerDiameter;
		wxTextCtrl* m_textCtrlHolderLowerDiameter;
		wxStaticText* m_staticTextUnitHolderLowerDiameter;
		wxStaticText* m_staticTextHolderHeight;
		wxTextCtrl* m_textCtrlHolderHeight;
		wxStaticText* m_staticTextUnitHolderHeight;
		wxDataViewListCtrl* m_dataViewListCtrlHolderSegments;
		wxDataViewColumn* m_dataViewListColumnHolderUpper;
		wxDataViewColumn* m_dataViewListColumnHolderLower;
		wxDataViewColumn* m_dataViewListColumnHolderHeight;
		wxPanel* m_panelFeedsSpeeds;
		wxScrolledWindow* m_scrolledWindowFeedsSpeeds;
		wxStaticText* m_staticTextSetName;
		wxTextCtrl* m_textCtrlSetName;
		wxStaticText* m_staticTextSetGUID;
		wxTextCtrl* m_textCtrlSetGUID;
		wxStaticText* m_staticTextSetDescription;
		wxTextCtrl* m_textCtrlSetDescription;
		wxStaticText* m_staticTextSetToolCoolant;
		wxTextCtrl* m_textCtrlSetToolCoolant;
		wxStaticText* m_staticTextFeedPerRevolution;
		wxTextCtrl* m_textCtrlFeedPerRevolution;
		wxStaticText* m_staticTextUnitFeedPerRevolution;
		wxStaticText* m_staticTextFeedPerTooth;
		wxTextCtrl* m_textCtrlFeedPerTooth;
		wxStaticText* m_staticTextUnitFeedPerTooth;
		wxStaticText* m_staticTextFeedSpindleSpeed;
		wxTextCtrl* m_textCtrlFeedSpindleSpeed;
		wxStaticText* m_staticTextUnitFeedSpindleSpeed;
		wxStaticText* m_staticTextFeedSpindleSpeedRampe;
		wxTextCtrl* m_textCtrlFeedSpindleSpeedRamp;
		wxStaticText* m_staticTextUnitFeedSpindleSpeedRamp;
		wxStaticText* m_staticTextSpeedCuttingFeedrate;
		wxTextCtrl* m_textCtrlSpeedCuttingFeedrate;
		wxStaticText* m_staticTextUnitSpeedCuttingFeedrate;
		wxStaticText* m_staticTextSpeedAvgFeedrate;
		wxTextCtrl* m_textCtrlSpeedAvgFeedrate;
		wxStaticText* m_staticTextUnitSpeedAvgFeedrate;
		wxStaticText* m_staticTextSpeedLeadInFeedrate;
		wxTextCtrl* m_textCtrlSpeedLeadInFeedrate;
		wxStaticText* m_staticTextUnitSpeedLeadInFeedrate;
		wxStaticText* m_staticTextSpeedLeadOutFeedrate;
		wxTextCtrl* m_textCtrlSpeedLeadOutFeedrate;
		wxStaticText* m_staticTextUnitSpeedLeadOutFeedrate;
		wxStaticText* m_staticTextSpeedPlungeFeedrate;
		wxTextCtrl* m_textCtrlSpeedPlungeFeedrate;
		wxStaticText* m_staticTextUnitSpeedPlungeFeedrate;
		wxStaticText* m_staticTextSpeedRampFeedrate;
		wxTextCtrl* m_textCtrlSpeedRampFeedrate;
		wxStaticText* m_staticTextUnitSpeedRampFeedrate;
		wxStaticText* m_staticTextSpeedRetractionFeedrate;
		wxTextCtrl* m_textCtrlSpeedRetractionFeedrate;
		wxStaticText* m_staticTextUnitSpeedRetractionFeedrate;
		wxPanel* m_panelPostProcess;
		wxScrolledWindow* m_scrolledWindowPostProcess;
		wxCheckBox* m_checkBoxLive;
		wxStaticText* m_staticTextPostProcessComment;
		wxTextCtrl* m_textCtrlPostProcessComment;
		wxStaticText* m_staticTextPostProcessNumber;
		wxTextCtrl* m_textCtrlPostProcessNumber;
		wxCheckBox* m_checkBoxManualToolChange;
		wxCheckBox* m_checkBoxBreakControl;
		wxStaticText* m_staticTextPostProcessDiameterOffset;
		wxTextCtrl* m_textCtrlPostProcessDiameterOffset;
		wxStaticText* m_staticTextPostProcessLengthOffset;
		wxTextCtrl* m_textCtrlPostProcessLengthOffset;
		wxStaticText* m_staticTextPostProcessToolCoolant;
		wxTextCtrl* m_textCtrlPostProcessToolCoolant;
		wxStaticText* m_staticTextPostProcessTurret;
		wxTextCtrl* m_textCtrlPostProcessTurret;
		CanvasTool* m_canvastool;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnXClose( wxCloseEvent& event ) = 0;
		virtual void OnToolChecked( wxTreeListEvent& event ) = 0;
		virtual void OnToolContextMenu( wxTreeListEvent& event ) = 0;
		virtual void OnToolboxExpanding( wxTreeListEvent& event ) = 0;
		virtual void OnToolSelectionChanged( wxTreeListEvent& event ) = 0;
		virtual void OnChoice( wxCommandEvent& event ) = 0;
		virtual void OnEnter( wxCommandEvent& event ) = 0;
		virtual void OnRadioBox( wxCommandEvent& event ) = 0;
		virtual void OnCheckBox( wxCommandEvent& event ) = 0;
		virtual void OnSegmentAdd( wxCommandEvent& event ) = 0;
		virtual void OnSegmentDelete( wxCommandEvent& event ) = 0;
		virtual void OnItemBeginDrag( wxDataViewEvent& event ) = 0;
		virtual void OnItemDrop( wxDataViewEvent& event ) = 0;
		virtual void OnSelectionChanged( wxDataViewEvent& event ) = 0;
		
	
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
