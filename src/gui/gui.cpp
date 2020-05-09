///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "gui.h"

#include "../icon/arrowxn.xpm"
#include "../icon/arrowxp.xpm"
#include "../icon/arrowyn.xpm"
#include "../icon/arrowyp.xpm"
#include "../icon/arrowzn.xpm"
#include "../icon/arrowzp.xpm"
#include "../icon/controller.xpm"
#include "../icon/export.xpm"
#include "../icon/first.xpm"
#include "../icon/flip.xpm"
#include "../icon/gcode.xpm"
#include "../icon/last.xpm"
#include "../icon/logo48.xpm"
#include "../icon/machine.xpm"
#include "../icon/modify.xpm"
#include "../icon/next.xpm"
#include "../icon/play.xpm"
#include "../icon/prev.xpm"
#include "../icon/setup.xpm"
#include "../icon/stereo3D.xpm"
#include "../icon/tool_2D.xpm"
#include "../icon/tool_3D.xpm"
#include "../icon/tool_drilling.xpm"
#include "../icon/tool_multi.xpm"
#include "../icon/tools.xpm"
#include "../icon/unify.xpm"

///////////////////////////////////////////////////////////////////////////

GUIFrameMain::GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDocChildFrame( doc, view, parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerRibbon;
	bSizerRibbon = new wxBoxSizer( wxHORIZONTAL );
	
	m_ribbonBarProjectViewEdit = new wxRibbonBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL );
	m_ribbonBarProjectViewEdit->SetArtProvider(new wxRibbonMSWArtProvider); 
	m_ribbonPageViewEdit = new wxRibbonPage( m_ribbonBarProjectViewEdit, wxID_ANY, wxEmptyString , wxNullBitmap , 0 );
	m_ribbonPanelProject = new wxRibbonPanel( m_ribbonPageViewEdit, wxID_ANY, _("Project") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarProject = new wxRibbonButtonBar( m_ribbonPanelProject, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarProject->AddButton( wxID_NEW, _("New"), wxArtProvider::GetBitmap( wxART_FOLDER, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarProject->AddHybridButton( wxID_OPEN, _("Open"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarProject->AddHybridButton( wxID_SAVE, _("Save"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelView = new wxRibbonPanel( m_ribbonPageViewEdit, wxID_ANY, _("View") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarView = new wxRibbonButtonBar( m_ribbonPanelView, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarView->AddDropdownButton( ID_VIEWPREFERENCES, _("Preferences"), wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarView->AddToggleButton( ID_TOGGLESTEREO3D, _("Stereo 3D"), wxBitmap( stereo3D_xpm ), wxEmptyString);
	m_ribbonPanelEdit = new wxRibbonPanel( m_ribbonPageViewEdit, wxID_ANY, _("Edit") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarEdit = new wxRibbonButtonBar( m_ribbonPanelEdit, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarEdit->AddButton( wxID_UNDO, _("Undo"), wxArtProvider::GetBitmap( wxART_UNDO, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarEdit->AddButton( wxID_REDO, _("Redo"), wxArtProvider::GetBitmap( wxART_REDO, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonBarProjectViewEdit->Realize();
	
	bSizerRibbon->Add( m_ribbonBarProjectViewEdit, 0, wxEXPAND, 5 );
	
	m_ribbonBarCANCAM = new wxRibbonBar( this, wxID_HELP, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL|wxRIBBON_BAR_SHOW_HELP_BUTTON|wxRIBBON_BAR_SHOW_PAGE_LABELS );
	m_ribbonBarCANCAM->SetArtProvider(new wxRibbonMSWArtProvider); 
	m_ribbonPageCAD = new wxRibbonPage( m_ribbonBarCANCAM, wxID_ANY, _("CAD") , wxNullBitmap , 0 );
	m_ribbonPanelObject = new wxRibbonPanel( m_ribbonPageCAD, wxID_ANY, _("Object") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarObject = new wxRibbonButtonBar( m_ribbonPanelObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarObject->AddButton( ID_OBJECTLOAD, _("Load"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarObject->AddButton( ID_OBJECTMODIFY, _("Modify"), wxBitmap( modify_xpm ), wxEmptyString);
	m_ribbonButtonBarObject->AddButton( ID_OBJECTUNIFYSURFACE, _("Unify Surface"), wxBitmap( unify_xpm ), wxEmptyString);
	m_ribbonButtonBarObject->AddButton( ID_OBJECTFLIPNORMALS, _("Flip Normals"), wxBitmap( flip_xpm ), wxEmptyString);
	m_ribbonPageCAM = new wxRibbonPage( m_ribbonBarCANCAM, wxID_ANY, _("CAM") , wxNullBitmap , 0 );
	m_ribbonBarCANCAM->SetActivePage( m_ribbonPageCAM ); 
	m_ribbonPanelSetup = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Setup") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarSetup = new wxRibbonButtonBar( m_ribbonPanelSetup, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarSetup->AddButton( ID_RUNMODIFY, _("Setup"), wxBitmap( setup_xpm ), wxEmptyString);
	m_ribbonPanelToolpath = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Toolpath") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarToolpath = new wxRibbonButtonBar( m_ribbonPanelToolpath, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarToolpath->AddDropdownButton( ID_2D, _("2D"), wxBitmap( tool_2D_xpm ), wxEmptyString);
	m_ribbonButtonBarToolpath->AddDropdownButton( ID_3D, _("3D"), wxBitmap( tool_3D_xpm ), wxEmptyString);
	m_ribbonButtonBarToolpath->AddButton( ID_DRILLING, _("Drilling"), wxBitmap( tool_drilling_xpm ), wxEmptyString);
	m_ribbonButtonBarToolpath->AddDropdownButton( ID_MULTIAXIS, _("Multi-Axis"), wxBitmap( tool_multi_xpm ), wxEmptyString);
	m_ribbonPanelPostProcess = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Post-Process") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarPostProcess = new wxRibbonButtonBar( m_ribbonPanelPostProcess, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarPostProcess->AddButton( ID_SIMULATE, _("Simulate"), wxBitmap( logo48_xpm ), wxEmptyString);
	m_ribbonButtonBarPostProcess->AddButton( ID_TOOLPATHEXPORT, _("Export"), wxBitmap( export_xpm ), wxEmptyString);
	m_ribbonPanelManage = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Manage") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarManageCam = new wxRibbonButtonBar( m_ribbonPanelManage, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarManageCam->AddButton( ID_MANAGETOOLS, _("Tool- Library"), wxBitmap( tools_xpm ), wxEmptyString);
	m_ribbonButtonBarManageCam->AddButton( ID_MANAGEMACHINES, _("Machine Debugger"), wxBitmap( machine_xpm ), wxEmptyString);
	m_ribbonPanelTools = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Tools") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarTools = new wxRibbonButtonBar( m_ribbonPanelTools, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarTools->AddButton( ID_GCODETEST, _("Test G-Code"), wxBitmap( gcode_xpm ), wxEmptyString);
	m_ribbonBarCANCAM->Realize();
	
	bSizerRibbon->Add( m_ribbonBarCANCAM, 1, 0, 5 );
	
	
	bSizer->Add( bSizerRibbon, 0, wxEXPAND, 5 );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrameMain::m_splitterOnIdle ), NULL, this );
	m_splitter->SetMinimumPaneSize( 100 );
	
	m_panelTree = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerTree;
	bSizerTree = new wxBoxSizer( wxVERTICAL );
	
	m_tree = new wxTreeCtrl( m_panelTree, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS|wxTR_FULL_ROW_HIGHLIGHT|wxTR_HAS_BUTTONS|wxTR_MULTIPLE|wxTR_NO_LINES );
	bSizerTree->Add( m_tree, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelTree->SetSizer( bSizerTree );
	m_panelTree->Layout();
	bSizerTree->Fit( m_panelTree );
	m_panelCanvasMain = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerMainCanvas;
	bSizerMainCanvas = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new CanvasMain(m_panelCanvasMain);
	bSizerMainCanvas->Add( m_canvas, 1, wxEXPAND, 5 );
	
	
	m_panelCanvasMain->SetSizer( bSizerMainCanvas );
	m_panelCanvasMain->Layout();
	bSizerMainCanvas->Fit( m_panelCanvasMain );
	m_splitter->SplitVertically( m_panelTree, m_panelCanvasMain, 250 );
	bSizer->Add( m_splitter, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrameMain::OnSize ) );
	this->Connect( wxID_NEW, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectNew ) );
	this->Connect( wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectOpen ) );
	this->Connect( wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectOpenMenu ) );
	this->Connect( wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectSave ) );
	this->Connect( wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectSaveMenu ) );
	this->Connect( ID_VIEWPREFERENCES, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnViewPreferencesMenu ) );
	this->Connect( ID_TOGGLESTEREO3D, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewStereo3DToggle ) );
	this->Connect( wxID_UNDO, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnUndo ) );
	this->Connect( wxID_REDO, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnRedo ) );
	this->Connect( wxID_HELP, wxEVT_COMMAND_RIBBONBAR_HELP_CLICKED, wxRibbonBarEventHandler( GUIFrameMain::OnHelp ) );
	this->Connect( ID_OBJECTLOAD, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectLoad ) );
	this->Connect( ID_OBJECTMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectModify ) );
	this->Connect( ID_OBJECTUNIFYSURFACE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectUnifySurface ) );
	this->Connect( ID_OBJECTFLIPNORMALS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectFlipNormals ) );
	this->Connect( ID_RUNMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMSetup ) );
	this->Connect( ID_2D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM2DMenu ) );
	this->Connect( ID_3D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM3DMenu ) );
	this->Connect( ID_DRILLING, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMDrilling ) );
	this->Connect( ID_MULTIAXIS, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMMultiAxisMenu ) );
	this->Connect( ID_SIMULATE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessSimulate ) );
	this->Connect( ID_TOOLPATHEXPORT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessExport ) );
	this->Connect( ID_MANAGETOOLS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageTools ) );
	this->Connect( ID_MANAGEMACHINES, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageMachines ) );
	this->Connect( ID_GCODETEST, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMToolsTestGCode ) );
	m_tree->Connect( wxEVT_CHAR, wxKeyEventHandler( GUIFrameMain::OnChar ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnBeginLabelEdit ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnEndLabelEdit ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( GUIFrameMain::OnActivate ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIFrameMain::OnActivateRightClickMenu ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIFrameMain::OnSelectionChanged ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( GUIFrameMain::OnSelectionChanging ), NULL, this );
	m_canvas->Connect( wxEVT_CHAR, wxKeyEventHandler( GUIFrameMain::OnChar ), NULL, this );
	m_canvas->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIFrameMain::On3DSelect ), NULL, this );
	m_canvas->Connect( wxEVT_MOTION, wxMouseEventHandler( GUIFrameMain::On3DMotion ), NULL, this );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrameMain::OnSize ) );
	this->Disconnect( wxID_NEW, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectNew ) );
	this->Disconnect( wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectOpen ) );
	this->Disconnect( wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectOpenMenu ) );
	this->Disconnect( wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectSave ) );
	this->Disconnect( wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnProjectSaveMenu ) );
	this->Disconnect( ID_VIEWPREFERENCES, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnViewPreferencesMenu ) );
	this->Disconnect( ID_TOGGLESTEREO3D, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewStereo3DToggle ) );
	this->Disconnect( wxID_UNDO, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnUndo ) );
	this->Disconnect( wxID_REDO, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnRedo ) );
	this->Disconnect( wxID_HELP, wxEVT_COMMAND_RIBBONBAR_HELP_CLICKED, wxRibbonBarEventHandler( GUIFrameMain::OnHelp ) );
	this->Disconnect( ID_OBJECTLOAD, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectLoad ) );
	this->Disconnect( ID_OBJECTMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectModify ) );
	this->Disconnect( ID_OBJECTUNIFYSURFACE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectUnifySurface ) );
	this->Disconnect( ID_OBJECTFLIPNORMALS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectFlipNormals ) );
	this->Disconnect( ID_RUNMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMSetup ) );
	this->Disconnect( ID_2D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM2DMenu ) );
	this->Disconnect( ID_3D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM3DMenu ) );
	this->Disconnect( ID_DRILLING, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMDrilling ) );
	this->Disconnect( ID_MULTIAXIS, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMMultiAxisMenu ) );
	this->Disconnect( ID_SIMULATE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessSimulate ) );
	this->Disconnect( ID_TOOLPATHEXPORT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessExport ) );
	this->Disconnect( ID_MANAGETOOLS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageTools ) );
	this->Disconnect( ID_MANAGEMACHINES, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageMachines ) );
	this->Disconnect( ID_GCODETEST, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMToolsTestGCode ) );
	m_tree->Disconnect( wxEVT_CHAR, wxKeyEventHandler( GUIFrameMain::OnChar ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnBeginLabelEdit ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnEndLabelEdit ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( GUIFrameMain::OnActivate ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIFrameMain::OnActivateRightClickMenu ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIFrameMain::OnSelectionChanged ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( GUIFrameMain::OnSelectionChanging ), NULL, this );
	m_canvas->Disconnect( wxEVT_CHAR, wxKeyEventHandler( GUIFrameMain::OnChar ), NULL, this );
	m_canvas->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIFrameMain::On3DSelect ), NULL, this );
	m_canvas->Disconnect( wxEVT_MOTION, wxMouseEventHandler( GUIFrameMain::On3DMotion ), NULL, this );
	
}

GUIObjectTransformation::GUIObjectTransformation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerSize;
	sbSizerSize = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Current size of object") ), wxHORIZONTAL );
	
	m_staticText37 = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	sbSizerSize->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeX = new wxTextCtrl( sbSizerSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	sbSizerSize->Add( m_textCtrlSizeX, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	sbSizerSize->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText38 = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	sbSizerSize->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeY = new wxTextCtrl( sbSizerSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	sbSizerSize->Add( m_textCtrlSizeY, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	sbSizerSize->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText39 = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	sbSizerSize->Add( m_staticText39, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeZ = new wxTextCtrl( sbSizerSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	sbSizerSize->Add( m_textCtrlSizeZ, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	sbSizerSize->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( sbSizerSize, 0, wxEXPAND, 5 );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelScale = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_panelScale, wxID_ANY, _("Quick scale:") ), wxHORIZONTAL );
	
	m_buttonMultTen = new wxButton( sbSizer11->GetStaticBox(), ID_MULTTEN, _("XYZ * 10"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( m_buttonMultTen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDivTen = new wxButton( sbSizer11->GetStaticBox(), ID_DIVTEN, _("XYZ / 10"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( m_buttonDivTen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer29->Add( sbSizer11, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer101;
	sbSizer101 = new wxStaticBoxSizer( new wxStaticBox( m_panelScale, wxID_ANY, _("Calculate scaling factors") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer91;
	fgSizer91 = new wxFlexGridSizer( 3, 4, 0, 0 );
	fgSizer91->SetFlexibleDirection( wxBOTH );
	fgSizer91->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText44 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("X ="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	fgSizer91->Add( m_staticText44, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitX = new wxTextCtrl( sbSizer101->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer91->Add( m_textCtrlScaleUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX2 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX2->Wrap( -1 );
	fgSizer91->Add( m_staticTextUnitX2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCalculateX = new wxButton( sbSizer101->GetStaticBox(), ID_SCALEUNITX, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer91->Add( m_buttonCalculateX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText46 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("Y ="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer91->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitY = new wxTextCtrl( sbSizer101->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer91->Add( m_textCtrlScaleUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY2 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY2->Wrap( -1 );
	fgSizer91->Add( m_staticTextUnitY2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCalculateY = new wxButton( sbSizer101->GetStaticBox(), ID_SCALEUNITY, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer91->Add( m_buttonCalculateY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText52 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("Z ="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	fgSizer91->Add( m_staticText52, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitZ = new wxTextCtrl( sbSizer101->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer91->Add( m_textCtrlScaleUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ2 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ2->Wrap( -1 );
	fgSizer91->Add( m_staticTextUnitZ2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCalculateZ = new wxButton( sbSizer101->GetStaticBox(), ID_SCALEUNITZ, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer91->Add( m_buttonCalculateZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer101->Add( fgSizer91, 0, wxEXPAND, 5 );
	
	m_checkBoxScaleProportionally = new wxCheckBox( sbSizer101->GetStaticBox(), wxID_ANY, _("Scale proportionally"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxScaleProportionally->SetValue(true); 
	sbSizer101->Add( m_checkBoxScaleProportionally, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer24->Add( sbSizer101, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panelScale, wxID_ANY, _("Rescale") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 4, 4, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText50 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	fgSizer6->Add( m_staticText50, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlScalePercentX = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercentX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText51 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer6->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonScaleX = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENTX, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_buttonScaleX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText48 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer6->Add( m_staticText48, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlScalePercentY = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercentY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText55 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	fgSizer6->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonScaleY = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENTY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_buttonScaleY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText54 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	fgSizer6->Add( m_staticText54, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlScalePercentZ = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercentZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText43 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	fgSizer6->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonScaleZ = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENTZ, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_buttonScaleZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText68 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Proportional:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText68->Wrap( -1 );
	fgSizer6->Add( m_staticText68, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercent = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercent, 0, wxALL, 5 );
	
	m_staticText49 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer6->Add( m_staticText49, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonScaleAll = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENT, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_buttonScaleAll, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer4->Add( fgSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer24->Add( sbSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer29->Add( bSizer24, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelScale->SetSizer( bSizer29 );
	m_panelScale->Layout();
	bSizer29->Fit( m_panelScale );
	m_notebook->AddPage( m_panelScale, _("Scale"), false );
	m_panelMove = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer34->Add( 0, 0, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panelMove, wxID_ANY, _("Move") ), wxVERTICAL );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText62 = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, _("Step:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( -1 );
	bSizer37->Add( m_staticText62, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMoveStep = new wxTextCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer37->Add( m_textCtrlMoveStep, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitMove = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMove->Wrap( -1 );
	bSizer37->Add( m_staticTextUnitMove, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer9->Add( bSizer37, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bpButton6 = new wxBitmapButton( sbSizer9->GetStaticBox(), ID_MOVEZP, wxBitmap( arrowzp_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer8->Add( m_bpButton6, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_bpButton7 = new wxBitmapButton( sbSizer9->GetStaticBox(), ID_MOVEYP, wxBitmap( arrowyp_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer8->Add( m_bpButton7, 0, wxTOP|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_bpButton8 = new wxBitmapButton( sbSizer9->GetStaticBox(), ID_MOVEXN, wxBitmap( arrowxn_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer8->Add( m_bpButton8, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bpButton9 = new wxBitmapButton( sbSizer9->GetStaticBox(), ID_MOVEXP, wxBitmap( arrowxp_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer8->Add( m_bpButton9, 0, wxRIGHT|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_bpButton10 = new wxBitmapButton( sbSizer9->GetStaticBox(), ID_MOVEYN, wxBitmap( arrowyn_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer8->Add( m_bpButton10, 0, wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_bpButton11 = new wxBitmapButton( sbSizer9->GetStaticBox(), ID_MOVEZN, wxBitmap( arrowzn_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer8->Add( m_bpButton11, 0, wxBOTTOM|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	sbSizer9->Add( fgSizer8, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer34->Add( sbSizer9, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer34->Add( 0, 0, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panelMove, wxID_ANY, _("Align") ), wxVERTICAL );
	
	m_button18 = new wxButton( sbSizer5->GetStaticBox(), ID_ALIGNTOP, _("Align with top"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button18, 1, wxALL|wxEXPAND, 5 );
	
	m_button17 = new wxButton( sbSizer5->GetStaticBox(), ID_ALIGNMIDDLE, _("Align with middle"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button17, 1, wxALL|wxEXPAND, 5 );
	
	m_button16 = new wxButton( sbSizer5->GetStaticBox(), ID_ALIGNBOTTOM, _("Align with bottom"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button16, 1, wxALL|wxEXPAND, 5 );
	
	m_button50 = new wxButton( sbSizer5->GetStaticBox(), ID_ALIGNCENTER, _("Center"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button50, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer34->Add( sbSizer5, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer34->Add( 0, 0, 1, 0, 5 );
	
	
	m_panelMove->SetSizer( bSizer34 );
	m_panelMove->Layout();
	bSizer34->Fit( m_panelMove );
	m_notebook->AddPage( m_panelMove, _("Move"), true );
	m_panelRotate = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer291->Add( 0, 0, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panelRotate, wxID_ANY, _("Rotate stepwise") ), wxVERTICAL );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText76 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, _("Step:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText76->Wrap( -1 );
	bSizer40->Add( m_staticText76, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRotateStep = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer40->Add( m_textCtrlRotateStep, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitAngle = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitAngle->Wrap( -1 );
	bSizer40->Add( m_staticTextUnitAngle, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	sbSizer8->Add( bSizer40, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_button32 = new wxButton( sbSizer8->GetStaticBox(), ID_ROTATEYN, _("Y -"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button32, 0, wxALL, 5 );
	
	m_button33 = new wxButton( sbSizer8->GetStaticBox(), ID_ROTATEXN, _("X -"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button33, 0, wxALL, 5 );
	
	m_button28 = new wxButton( sbSizer8->GetStaticBox(), ID_ROTATEYP, _("Y +"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button28, 0, wxALL, 5 );
	
	m_button29 = new wxButton( sbSizer8->GetStaticBox(), ID_ROTATEZN, _("Z -"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button29, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button30 = new wxButton( sbSizer8->GetStaticBox(), ID_ROTATEZP, _("Z +"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button30, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button31 = new wxButton( sbSizer8->GetStaticBox(), ID_ROTATEXP, _("X +"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button31, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	sbSizer8->Add( fgSizer9, 0, 0, 5 );
	
	
	bSizer291->Add( sbSizer8, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer291->Add( 0, 0, 1, 0, 5 );
	
	
	m_panelRotate->SetSizer( bSizer291 );
	m_panelRotate->Layout();
	bSizer291->Fit( m_panelRotate );
	m_notebook->AddPage( m_panelRotate, _("Rotate"), false );
	m_panelMirror = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer36->Add( 0, 0, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_panelMirror, wxID_ANY, _("Mirror on") ), wxVERTICAL );
	
	m_button39 = new wxButton( sbSizer10->GetStaticBox(), ID_FLIPX, _("X axis"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button39, 0, wxALL|wxEXPAND, 5 );
	
	m_button40 = new wxButton( sbSizer10->GetStaticBox(), ID_FLIPY, _("Y axis"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button40, 0, wxALL|wxEXPAND, 5 );
	
	m_button41 = new wxButton( sbSizer10->GetStaticBox(), ID_FLIPZ, _("Z axis"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button41, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer36->Add( sbSizer10, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer36->Add( 0, 0, 1, 0, 5 );
	
	m_buttonFlipNormalVectors = new wxButton( m_panelMirror, ID_OBJECTFLIPNORMALS, _("Flip normal vectors"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_buttonFlipNormalVectors, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer36->Add( 0, 0, 1, 0, 5 );
	
	
	m_panelMirror->SetSizer( bSizer36 );
	m_panelMirror->Layout();
	bSizer36->Fit( m_panelMirror );
	m_notebook->AddPage( m_panelMirror, _("Mirror"), false );
	
	bSizerMain->Add( m_notebook, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIObjectTransformation::OnXClose ) );
	m_buttonMultTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonDivTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonCalculateX->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_buttonCalculateY->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_buttonCalculateZ->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_buttonScaleX->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonScaleY->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonScaleZ->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonScaleAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button50->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button32->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button33->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button30->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button31->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button39->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button40->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button41->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonFlipNormalVectors->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipNormals ), NULL, this );
}

GUIObjectTransformation::~GUIObjectTransformation()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIObjectTransformation::OnXClose ) );
	m_buttonMultTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonDivTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonCalculateX->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_buttonCalculateY->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_buttonCalculateZ->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_buttonScaleX->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonScaleY->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonScaleZ->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonScaleAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_bpButton11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button16->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button50->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button32->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button33->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button30->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button31->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button39->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button40->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button41->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_buttonFlipNormalVectors->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipNormals ), NULL, this );
	
}

GUIJobSetup::GUIJobSetup( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT );
	m_panelObject = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerObject;
	bSizerObject = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerObject;
	sbSizerObject = new wxStaticBoxSizer( new wxStaticBox( m_panelObject, wxID_ANY, _("Object") ), wxVERTICAL );
	
	m_buttonSelectObject = new wxButton( sbSizerObject->GetStaticBox(), ID_SELECTOBJECT, _("Select..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerObject->Add( m_buttonSelectObject, 0, wxALL, 5 );
	
	m_textCtrlObject = new wxTextCtrl( sbSizerObject->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerObject->Add( m_textCtrlObject, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizerObject->Add( sbSizerObject, 0, wxEXPAND, 5 );
	
	
	m_panelObject->SetSizer( bSizerObject );
	m_panelObject->Layout();
	bSizerObject->Fit( m_panelObject );
	m_notebook->AddPage( m_panelObject, _("Object"), true );
	m_panelCoordinates = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerCoordinates;
	bSizerCoordinates = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerCoordinates;
	sbSizerCoordinates = new wxStaticBoxSizer( new wxStaticBox( m_panelCoordinates, wxID_ANY, _("Coordinate System") ), wxVERTICAL );
	
	m_buttonAxisX = new wxButton( sbSizerCoordinates->GetStaticBox(), ID_SELECTAXISX, _("Select X..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCoordinates->Add( m_buttonAxisX, 0, wxALL, 5 );
	
	m_textCtrlAxisX = new wxTextCtrl( sbSizerCoordinates->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerCoordinates->Add( m_textCtrlAxisX, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonAxisY = new wxButton( sbSizerCoordinates->GetStaticBox(), ID_SELECTAXISY, _("Select Y..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCoordinates->Add( m_buttonAxisY, 0, wxALL, 5 );
	
	m_textCtrlAxisY = new wxTextCtrl( sbSizerCoordinates->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerCoordinates->Add( m_textCtrlAxisY, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonAxisZ = new wxButton( sbSizerCoordinates->GetStaticBox(), ID_SELECTAXISZ, _("Select Z..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCoordinates->Add( m_buttonAxisZ, 0, wxALL, 5 );
	
	m_textCtrlAxisZ = new wxTextCtrl( sbSizerCoordinates->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerCoordinates->Add( m_textCtrlAxisZ, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizerCoordinates->Add( sbSizerCoordinates, 0, wxEXPAND, 5 );
	
	
	m_panelCoordinates->SetSizer( bSizerCoordinates );
	m_panelCoordinates->Layout();
	bSizerCoordinates->Fit( m_panelCoordinates );
	m_notebook->AddPage( m_panelCoordinates, _("Coordinates"), false );
	m_panelStock = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerStock;
	bSizerStock = new wxBoxSizer( wxVERTICAL );
	
	m_choicebookStock = new wxChoicebook( m_panelStock, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
	m_panelStockBox = new wxPanel( m_choicebookStock, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizerStockBox;
	fgSizerStockBox = new wxFlexGridSizer( 5, 3, 0, 0 );
	fgSizerStockBox->AddGrowableCol( 1 );
	fgSizerStockBox->SetFlexibleDirection( wxBOTH );
	fgSizerStockBox->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextBoxX = new wxStaticText( m_panelStockBox, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoxX->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextBoxX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlBoxX = new wxTextCtrl( m_panelStockBox, ID_SETSIZEX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerStockBox->Add( m_textCtrlBoxX, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitBoxX = new wxStaticText( m_panelStockBox, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitBoxX->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextUnitBoxX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBoxY = new wxStaticText( m_panelStockBox, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoxY->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextBoxY, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBoxY = new wxTextCtrl( m_panelStockBox, ID_SETSIZEY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerStockBox->Add( m_textCtrlBoxY, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitBoxY = new wxStaticText( m_panelStockBox, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitBoxY->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextUnitBoxY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBoxZ = new wxStaticText( m_panelStockBox, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoxZ->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextBoxZ, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBoxZ = new wxTextCtrl( m_panelStockBox, ID_SETSIZEZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerStockBox->Add( m_textCtrlBoxZ, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitBoxZ = new wxStaticText( m_panelStockBox, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitBoxZ->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextUnitBoxZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizerStockBox->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonFromObject = new wxButton( m_panelStockBox, wxID_ANY, _("Get box size from object"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerStockBox->Add( m_buttonFromObject, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizerStockBox->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizerStockBox->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxString m_radioBoxChoices[] = { _("Top"), _("Center"), _("Bottom") };
	int m_radioBoxNChoices = sizeof( m_radioBoxChoices ) / sizeof( wxString );
	m_radioBox = new wxRadioBox( m_panelStockBox, wxID_ANY, _("Alignment"), wxDefaultPosition, wxDefaultSize, m_radioBoxNChoices, m_radioBoxChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBox->SetSelection( 0 );
	fgSizerStockBox->Add( m_radioBox, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizerStockBox->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panelStockBox->SetSizer( fgSizerStockBox );
	m_panelStockBox->Layout();
	fgSizerStockBox->Fit( m_panelStockBox );
	m_choicebookStock->AddPage( m_panelStockBox, _("Box"), true );
	m_panelStockObject = new wxPanel( m_choicebookStock, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerStockObject;
	bSizerStockObject = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrlStockObject = new wxTextCtrl( m_panelStockObject, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizerStockObject->Add( m_textCtrlStockObject, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonStockObjectSelect = new wxButton( m_panelStockObject, ID_SELECTOBJECTSTOCK, _("Select ..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStockObject->Add( m_buttonStockObjectSelect, 0, wxALL, 5 );
	
	
	m_panelStockObject->SetSizer( bSizerStockObject );
	m_panelStockObject->Layout();
	bSizerStockObject->Fit( m_panelStockObject );
	m_choicebookStock->AddPage( m_panelStockObject, _("Object as stock"), false );
	bSizerStock->Add( m_choicebookStock, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelStock->SetSizer( bSizerStock );
	m_panelStock->Layout();
	bSizerStock->Fit( m_panelStock );
	m_notebook->AddPage( m_panelStock, _("Stock"), false );
	m_panelOrigin = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerOrigin;
	bSizerOrigin = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerOrigin;
	sbSizerOrigin = new wxStaticBoxSizer( new wxStaticBox( m_panelOrigin, wxID_ANY, _("Origin") ), wxVERTICAL );
	
	m_textCtrlOrigin = new wxTextCtrl( sbSizerOrigin->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerOrigin->Add( m_textCtrlOrigin, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonOrigin = new wxButton( sbSizerOrigin->GetStaticBox(), ID_SELECTORIGIN, _("Select ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerOrigin->Add( m_buttonOrigin, 0, wxALL, 5 );
	
	
	bSizerOrigin->Add( sbSizerOrigin, 0, wxEXPAND, 5 );
	
	
	m_panelOrigin->SetSizer( bSizerOrigin );
	m_panelOrigin->Layout();
	bSizerOrigin->Fit( m_panelOrigin );
	m_notebook->AddPage( m_panelOrigin, _("Origin"), false );
	m_panelSupports = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerSupports;
	bSizerSupports = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindowSupports = new wxScrolledWindow( m_panelSupports, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindowSupports->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerScrolledWindowSupports;
	bSizerScrolledWindowSupports = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerSupportSize;
	sbSizerSupportSize = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowSupports, wxID_ANY, _("Size") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerSupportSize;
	fgSizerSupportSize = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerSupportSize->AddGrowableCol( 1 );
	fgSizerSupportSize->SetFlexibleDirection( wxBOTH );
	fgSizerSupportSize->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSupportSlotwidth = new wxStaticText( sbSizerSupportSize->GetStaticBox(), wxID_ANY, _("Slotwidth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportSlotwidth->Wrap( -1 );
	fgSizerSupportSize->Add( m_staticTextSupportSlotwidth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportSlotwidth = new wxTextCtrl( sbSizerSupportSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportSize->Add( m_textCtrlSupportSlotwidth, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportSlotwidth = new wxStaticText( sbSizerSupportSize->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportSlotwidth->Wrap( -1 );
	fgSizerSupportSize->Add( m_staticTextUnitSupportSlotwidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSupportWidth = new wxStaticText( sbSizerSupportSize->GetStaticBox(), wxID_ANY, _("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportWidth->Wrap( -1 );
	fgSizerSupportSize->Add( m_staticTextSupportWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportWidth = new wxTextCtrl( sbSizerSupportSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportSize->Add( m_textCtrlSupportWidth, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportWidth = new wxStaticText( sbSizerSupportSize->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportWidth->Wrap( -1 );
	fgSizerSupportSize->Add( m_staticTextUnitSupportWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSupportHeight = new wxStaticText( sbSizerSupportSize->GetStaticBox(), wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportHeight->Wrap( -1 );
	fgSizerSupportSize->Add( m_staticTextSupportHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportHeight = new wxTextCtrl( sbSizerSupportSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportSize->Add( m_textCtrlSupportHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportHeight = new wxStaticText( sbSizerSupportSize->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportHeight->Wrap( -1 );
	fgSizerSupportSize->Add( m_staticTextUnitSupportHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerSupportSize->Add( fgSizerSupportSize, 0, wxEXPAND, 5 );
	
	
	bSizerScrolledWindowSupports->Add( sbSizerSupportSize, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerSupportLevel;
	sbSizerSupportLevel = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowSupports, wxID_ANY, _("Level") ), wxVERTICAL );
	
	wxString m_choiceSupportLevelChoices[] = { _("Manual"), _("Individual automatic level"), _("Common automatic level") };
	int m_choiceSupportLevelNChoices = sizeof( m_choiceSupportLevelChoices ) / sizeof( wxString );
	m_choiceSupportLevel = new wxChoice( sbSizerSupportLevel->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSupportLevelNChoices, m_choiceSupportLevelChoices, 0 );
	m_choiceSupportLevel->SetSelection( 0 );
	sbSizerSupportLevel->Add( m_choiceSupportLevel, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizerSupportLevel;
	fgSizerSupportLevel = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizerSupportLevel->AddGrowableCol( 1 );
	fgSizerSupportLevel->SetFlexibleDirection( wxBOTH );
	fgSizerSupportLevel->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSupportLevel = new wxStaticText( sbSizerSupportLevel->GetStaticBox(), wxID_ANY, _("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportLevel->Wrap( -1 );
	fgSizerSupportLevel->Add( m_staticTextSupportLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportLevel = new wxTextCtrl( sbSizerSupportLevel->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportLevel->Add( m_textCtrlSupportLevel, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportLevel = new wxStaticText( sbSizerSupportLevel->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportLevel->Wrap( -1 );
	fgSizerSupportLevel->Add( m_staticTextUnitSupportLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerSupportLevel->Add( fgSizerSupportLevel, 0, wxEXPAND, 5 );
	
	
	bSizerScrolledWindowSupports->Add( sbSizerSupportLevel, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerGridlinesX;
	sbSizerGridlinesX = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowSupports, wxID_ANY, _("Gridlines X") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerSupportGridlinesX;
	fgSizerSupportGridlinesX = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizerSupportGridlinesX->AddGrowableCol( 1 );
	fgSizerSupportGridlinesX->SetFlexibleDirection( wxBOTH );
	fgSizerSupportGridlinesX->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSupportXDistance = new wxStaticText( sbSizerGridlinesX->GetStaticBox(), wxID_ANY, _("Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportXDistance->Wrap( -1 );
	fgSizerSupportGridlinesX->Add( m_staticTextSupportXDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportXDistance = new wxTextCtrl( sbSizerGridlinesX->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportGridlinesX->Add( m_textCtrlSupportXDistance, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportXDistance = new wxStaticText( sbSizerGridlinesX->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportXDistance->Wrap( -1 );
	fgSizerSupportGridlinesX->Add( m_staticTextUnitSupportXDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSupportXOffset = new wxStaticText( sbSizerGridlinesX->GetStaticBox(), wxID_ANY, _("Offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportXOffset->Wrap( -1 );
	fgSizerSupportGridlinesX->Add( m_staticTextSupportXOffset, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportXOffset = new wxTextCtrl( sbSizerGridlinesX->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportGridlinesX->Add( m_textCtrlSupportXOffset, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportXOffset = new wxStaticText( sbSizerGridlinesX->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportXOffset->Wrap( -1 );
	fgSizerSupportGridlinesX->Add( m_staticTextUnitSupportXOffset, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerGridlinesX->Add( fgSizerSupportGridlinesX, 1, wxEXPAND, 5 );
	
	
	bSizerScrolledWindowSupports->Add( sbSizerGridlinesX, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerGridlinesY;
	sbSizerGridlinesY = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowSupports, wxID_ANY, _("Gridlines Y") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerSupportGridlinesY;
	fgSizerSupportGridlinesY = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizerSupportGridlinesY->AddGrowableCol( 1 );
	fgSizerSupportGridlinesY->SetFlexibleDirection( wxBOTH );
	fgSizerSupportGridlinesY->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSupportYDistance = new wxStaticText( sbSizerGridlinesY->GetStaticBox(), wxID_ANY, _("Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportYDistance->Wrap( -1 );
	fgSizerSupportGridlinesY->Add( m_staticTextSupportYDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportYDistance = new wxTextCtrl( sbSizerGridlinesY->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportGridlinesY->Add( m_textCtrlSupportYDistance, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportYDistance = new wxStaticText( sbSizerGridlinesY->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportYDistance->Wrap( -1 );
	fgSizerSupportGridlinesY->Add( m_staticTextUnitSupportYDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSupportYOffset = new wxStaticText( sbSizerGridlinesY->GetStaticBox(), wxID_ANY, _("Offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportYOffset->Wrap( -1 );
	fgSizerSupportGridlinesY->Add( m_staticTextSupportYOffset, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportYOffset = new wxTextCtrl( sbSizerGridlinesY->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportGridlinesY->Add( m_textCtrlSupportYOffset, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportYOffset = new wxStaticText( sbSizerGridlinesY->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportYOffset->Wrap( -1 );
	fgSizerSupportGridlinesY->Add( m_staticTextUnitSupportYOffset, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerGridlinesY->Add( fgSizerSupportGridlinesY, 1, wxEXPAND, 5 );
	
	
	bSizerScrolledWindowSupports->Add( sbSizerGridlinesY, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerGridlinesOutline;
	sbSizerGridlinesOutline = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowSupports, wxID_ANY, _("Gridlines Outline") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerSupportGridlinesOutline;
	fgSizerSupportGridlinesOutline = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizerSupportGridlinesOutline->AddGrowableCol( 1 );
	fgSizerSupportGridlinesOutline->SetFlexibleDirection( wxBOTH );
	fgSizerSupportGridlinesOutline->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSupportOCount = new wxStaticText( sbSizerGridlinesOutline->GetStaticBox(), wxID_ANY, _("Count:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportOCount->Wrap( -1 );
	fgSizerSupportGridlinesOutline->Add( m_staticTextSupportOCount, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportOCount = new wxTextCtrl( sbSizerGridlinesOutline->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportGridlinesOutline->Add( m_textCtrlSupportOCount, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizerSupportGridlinesOutline->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextSupportOOffset = new wxStaticText( sbSizerGridlinesOutline->GetStaticBox(), wxID_ANY, _("Offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSupportOOffset->Wrap( -1 );
	fgSizerSupportGridlinesOutline->Add( m_staticTextSupportOOffset, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlSupportOOffset = new wxTextCtrl( sbSizerGridlinesOutline->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerSupportGridlinesOutline->Add( m_textCtrlSupportOOffset, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitSupportOOffset = new wxStaticText( sbSizerGridlinesOutline->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSupportOOffset->Wrap( -1 );
	fgSizerSupportGridlinesOutline->Add( m_staticTextUnitSupportOOffset, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerGridlinesOutline->Add( fgSizerSupportGridlinesOutline, 1, wxEXPAND, 5 );
	
	
	bSizerScrolledWindowSupports->Add( sbSizerGridlinesOutline, 0, wxEXPAND, 5 );
	
	
	m_scrolledWindowSupports->SetSizer( bSizerScrolledWindowSupports );
	m_scrolledWindowSupports->Layout();
	bSizerScrolledWindowSupports->Fit( m_scrolledWindowSupports );
	bSizerSupports->Add( m_scrolledWindowSupports, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelSupports->SetSizer( bSizerSupports );
	m_panelSupports->Layout();
	bSizerSupports->Fit( m_panelSupports );
	m_notebook->AddPage( m_panelSupports, _("Supports"), false );
	m_panelMachine = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerMachine;
	bSizerMachine = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextMachine = new wxStaticText( m_panelMachine, wxID_ANY, _("Machine description (optional):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMachine->Wrap( -1 );
	bSizerMachine->Add( m_staticTextMachine, 0, wxALL, 5 );
	
	m_filePickerMachine = new wxFilePickerCtrl( m_panelMachine, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_SMALL );
	bSizerMachine->Add( m_filePickerMachine, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelMachine->SetSizer( bSizerMachine );
	m_panelMachine->Layout();
	bSizerMachine->Fit( m_panelMachine );
	m_notebook->AddPage( m_panelMachine, _("Machine"), false );
	
	bSizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIJobSetup::OnXClose ) );
	m_buttonSelectObject->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonAxisX->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonAxisY->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonAxisZ->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_choicebookStock->Connect( wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED, wxChoicebookEventHandler( GUIJobSetup::OnChoicebookPageChanged ), NULL, this );
	m_textCtrlBoxX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIJobSetup::OnTextEnter ), NULL, this );
	m_textCtrlBoxY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIJobSetup::OnTextEnter ), NULL, this );
	m_textCtrlBoxZ->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIJobSetup::OnTextEnter ), NULL, this );
	m_buttonFromObject->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnGetSizeFromObject ), NULL, this );
	m_radioBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( GUIJobSetup::OnRadioBox ), NULL, this );
	m_buttonStockObjectSelect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonOrigin->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_filePickerMachine->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( GUIJobSetup::OnMachineSelected ), NULL, this );
}

GUIJobSetup::~GUIJobSetup()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIJobSetup::OnXClose ) );
	m_buttonSelectObject->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonAxisX->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonAxisY->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonAxisZ->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_choicebookStock->Disconnect( wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED, wxChoicebookEventHandler( GUIJobSetup::OnChoicebookPageChanged ), NULL, this );
	m_textCtrlBoxX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIJobSetup::OnTextEnter ), NULL, this );
	m_textCtrlBoxY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIJobSetup::OnTextEnter ), NULL, this );
	m_textCtrlBoxZ->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIJobSetup::OnTextEnter ), NULL, this );
	m_buttonFromObject->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnGetSizeFromObject ), NULL, this );
	m_radioBox->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( GUIJobSetup::OnRadioBox ), NULL, this );
	m_buttonStockObjectSelect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_buttonOrigin->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIJobSetup::OnSelect ), NULL, this );
	m_filePickerMachine->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( GUIJobSetup::OnMachineSelected ), NULL, this );
	
}

GUIToolpathGenerator::GUIToolpathGenerator( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerScrolled;
	bSizerScrolled = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerGeometry;
	sbSizerGeometry = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Geometry") ), wxVERTICAL );
	
	m_textCtrlGeometry = new wxTextCtrl( sbSizerGeometry->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerGeometry->Add( m_textCtrlGeometry, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonSelectGeometry = new wxButton( sbSizerGeometry->GetStaticBox(), ID_SELECTAREAOBJECT, _("Select ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerGeometry->Add( m_buttonSelectGeometry, 0, wxALL, 5 );
	
	
	bSizerScrolled->Add( sbSizerGeometry, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerTool;
	sbSizerTool = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Tool") ), wxVERTICAL );
	
	wxArrayString m_choiceToolChoices;
	m_choiceTool = new wxChoice( sbSizerTool->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceToolChoices, 0 );
	m_choiceTool->SetSelection( 0 );
	sbSizerTool->Add( m_choiceTool, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonToolSelect = new wxButton( sbSizerTool->GetStaticBox(), ID_TOOLLIBRARYMANAGE, _("Add tool from library..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTool->Add( m_buttonToolSelect, 0, wxALL, 5 );
	
	
	bSizerScrolled->Add( sbSizerTool, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerSpeeds;
	sbSizerSpeeds = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Feeds - Speeds") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerSpeeds;
	fgSizerSpeeds = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizerSpeeds->AddGrowableCol( 1 );
	fgSizerSpeeds->SetFlexibleDirection( wxBOTH );
	fgSizerSpeeds->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSpindle = new wxStaticText( sbSizerSpeeds->GetStaticBox(), wxID_ANY, _("Spindle-speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpindle->Wrap( -1 );
	fgSizerSpeeds->Add( m_staticTextSpindle, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_textCtrlSpindle = new wxTextCtrl( sbSizerSpeeds->GetStaticBox(), ID_SPEED, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeeds->Add( m_textCtrlSpindle, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitSpindle = new wxStaticText( sbSizerSpeeds->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpindle->Wrap( -1 );
	fgSizerSpeeds->Add( m_staticTextUnitSpindle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFeed = new wxStaticText( sbSizerSpeeds->GetStaticBox(), wxID_ANY, _("Feed-rate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFeed->Wrap( -1 );
	fgSizerSpeeds->Add( m_staticTextFeed, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlFeed = new wxTextCtrl( sbSizerSpeeds->GetStaticBox(), ID_FEED, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeeds->Add( m_textCtrlFeed, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitFeed = new wxStaticText( sbSizerSpeeds->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeed->Wrap( -1 );
	fgSizerSpeeds->Add( m_staticTextUnitFeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerSpeeds->Add( fgSizerSpeeds, 1, wxEXPAND, 5 );
	
	
	bSizerScrolled->Add( sbSizerSpeeds, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerMargin;
	sbSizerMargin = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Margin:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerMargin;
	fgSizerMargin = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerMargin->AddGrowableCol( 1 );
	fgSizerMargin->SetFlexibleDirection( wxBOTH );
	fgSizerMargin->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSide = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Side:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSide->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextSide, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMarginSide = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_MARGINSIDE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMargin->Add( m_textCtrlMarginSide, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextUnitMarginSide = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMarginSide->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextUnitMarginSide, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBelow = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Below:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBelow->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlMarginBelow = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_MARGINBELOW, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMargin->Add( m_textCtrlMarginBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextUnitMarginBelow = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMarginBelow->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextUnitMarginBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFreeHeight = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Clearance Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFreeHeight->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFreeHeight = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_CLEARANCEHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMargin->Add( m_textCtrlFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextUnitFreeHeight = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFreeHeight->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextUnitFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerMargin->Add( fgSizerMargin, 0, wxEXPAND, 5 );
	
	
	bSizerScrolled->Add( sbSizerMargin, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerType;
	sbSizerType = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Parameter:") ), wxVERTICAL );
	
	m_panel = new wxPanel( sbSizerType->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sbSizerType->Add( m_panel, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonUpdate = new wxButton( sbSizerType->GetStaticBox(), wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonUpdate->SetToolTip( _("Temporary Button until Command-Event passing is working. (This button will be removed by then.)") );
	
	sbSizerType->Add( m_buttonUpdate, 0, wxALL, 5 );
	
	
	bSizerScrolled->Add( sbSizerType, 0, wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizerScrolled->Add( m_textCtrlInfo, 0, wxALL|wxEXPAND, 5 );
	
	
	m_scrolledWindow->SetSizer( bSizerScrolled );
	m_scrolledWindow->Layout();
	bSizerScrolled->Fit( m_scrolledWindow );
	bSizerMain->Add( m_scrolledWindow, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CHAR, wxKeyEventHandler( GUIToolpathGenerator::OnChar ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolpathGenerator::OnXClose ) );
	m_scrolledWindow->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIToolpathGenerator::OnLeftDown ), NULL, this );
	m_buttonSelectGeometry->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectArea ), NULL, this );
	m_choiceTool->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectTool ), NULL, this );
	m_textCtrlSpindle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlFeed->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlMarginSide->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlMarginBelow->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlFreeHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_buttonUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnUpdate ), NULL, this );
}

GUIToolpathGenerator::~GUIToolpathGenerator()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CHAR, wxKeyEventHandler( GUIToolpathGenerator::OnChar ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolpathGenerator::OnXClose ) );
	m_scrolledWindow->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIToolpathGenerator::OnLeftDown ), NULL, this );
	m_buttonSelectGeometry->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectArea ), NULL, this );
	m_choiceTool->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectTool ), NULL, this );
	m_textCtrlSpindle->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlFeed->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlMarginSide->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlMarginBelow->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_textCtrlFreeHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolpathGenerator::OnTextEnter ), NULL, this );
	m_buttonUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnUpdate ), NULL, this );
	
}

GUIAnimation::GUIAnimation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_sliderTime = new wxSlider( this, wxID_ANY, 0, 0, 2000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer->Add( m_sliderTime, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTime;
	bSizerTime = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTime = new wxStaticText( this, wxID_ANY, _("Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTime->Wrap( -1 );
	bSizerTime->Add( m_staticTextTime, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_READONLY|wxTE_RIGHT );
	bSizerTime->Add( m_textCtrlTime, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextSlash = new wxStaticText( this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSlash->Wrap( -1 );
	bSizerTime->Add( m_staticTextSlash, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlMaxTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	bSizerTime->Add( m_textCtrlMaxTime, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	
	bSizerTime->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_bpButtonFirst = new wxBitmapButton( this, wxID_ANY, wxBitmap( first_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonFirst->SetToolTip( _("First") );
	
	bSizerButtons->Add( m_bpButtonFirst, 0, 0, 5 );
	
	m_bpButtonPrev = new wxBitmapButton( this, wxID_ANY, wxBitmap( prev_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPrev->SetToolTip( _("Previous toolpath") );
	
	bSizerButtons->Add( m_bpButtonPrev, 0, 0, 5 );
	
	m_bpButtonPlayStop = new wxBitmapButton( this, wxID_ANY, wxBitmap( play_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPlayStop->SetToolTip( _("Play / Stop") );
	
	bSizerButtons->Add( m_bpButtonPlayStop, 0, 0, 5 );
	
	m_bpButtonNext = new wxBitmapButton( this, wxID_ANY, wxBitmap( next_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonNext->SetToolTip( _("Next toolpath") );
	
	bSizerButtons->Add( m_bpButtonNext, 0, 0, 5 );
	
	m_bpButtonLast = new wxBitmapButton( this, wxID_ANY, wxBitmap( last_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonLast->SetToolTip( _("Last") );
	
	bSizerButtons->Add( m_bpButtonLast, 0, 0, 5 );
	
	
	bSizerTime->Add( bSizerButtons, 0, 0, 5 );
	
	
	bSizerTime->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_checkBoxSimulateWorkpiece = new wxCheckBox( this, wxID_ANY, _("Simulate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxSimulateWorkpiece->SetValue(true); 
	bSizerTime->Add( m_checkBoxSimulateWorkpiece, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTime->Add( m_buttonClose, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer->Add( bSizerTime, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerDisplayOptions;
	bSizerDisplayOptions = new wxBoxSizer( wxHORIZONTAL );
	
	wxString m_choiceDisplayChoices[] = { _("Workpiece"), _("Workpiece + Tool"), _("Workpiece + Tool + Holder"), _("Workpiece + Tool + Holder + Machine") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 1 );
	bSizerDisplayOptions->Add( m_choiceDisplay, 1, wxALL, 5 );
	
	wxString m_choiceFocusChoices[] = { _("Center Workpiece"), _("Center Tool"), _("Center Machine") };
	int m_choiceFocusNChoices = sizeof( m_choiceFocusChoices ) / sizeof( wxString );
	m_choiceFocus = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceFocusNChoices, m_choiceFocusChoices, 0 );
	m_choiceFocus->SetSelection( 0 );
	bSizerDisplayOptions->Add( m_choiceFocus, 1, wxALL, 5 );
	
	
	bSizer->Add( bSizerDisplayOptions, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIAnimation::OnXClose ) );
	m_sliderTime->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_textCtrlTime->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIAnimation::OnChangeTime ), NULL, this );
	m_bpButtonFirst->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnFirst ), NULL, this );
	m_bpButtonPrev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPrev ), NULL, this );
	m_bpButtonPlayStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPlayStop ), NULL, this );
	m_bpButtonNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnNext ), NULL, this );
	m_bpButtonLast->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnLast ), NULL, this );
	m_checkBoxSimulateWorkpiece->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIAnimation::OnChangeView ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnClose ), NULL, this );
	m_choiceDisplay->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIAnimation::OnChangeView ), NULL, this );
	m_choiceFocus->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIAnimation::OnChangeView ), NULL, this );
}

GUIAnimation::~GUIAnimation()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIAnimation::OnXClose ) );
	m_sliderTime->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_textCtrlTime->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIAnimation::OnChangeTime ), NULL, this );
	m_bpButtonFirst->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnFirst ), NULL, this );
	m_bpButtonPrev->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPrev ), NULL, this );
	m_bpButtonPlayStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPlayStop ), NULL, this );
	m_bpButtonNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnNext ), NULL, this );
	m_bpButtonLast->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnLast ), NULL, this );
	m_checkBoxSimulateWorkpiece->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIAnimation::OnChangeView ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnClose ), NULL, this );
	m_choiceDisplay->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIAnimation::OnChangeView ), NULL, this );
	m_choiceFocus->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIAnimation::OnChangeView ), NULL, this );
	
}

GUIPostProcess::GUIPostProcess( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerOpen;
	bSizerOpen = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_choiceSelectChoices;
	m_choiceSelect = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSelectChoices, 0 );
	m_choiceSelect->SetSelection( 0 );
	bSizerOpen->Add( m_choiceSelect, 1, wxALL, 5 );
	
	m_buttonRefresh = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerOpen->Add( m_buttonRefresh, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizerOpen, 0, wxEXPAND, 5 );
	
	m_propertyGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_HIDE_CATEGORIES|wxPG_HIDE_MARGIN);
	bSizer->Add( m_propertyGrid, 1, wxALL|wxEXPAND, 5 );
	
	m_filePickerExport = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("NC files (*.cnc;*.nc)|*.cnc;*.nc|Text files (*.txt)|*.txt|All files (*.*)|*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	bSizer->Add( m_filePickerExport, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonExport = new wxButton( this, wxID_ANY, _("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonExport, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIPostProcess::OnXClose ) );
	m_choiceSelect->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIPostProcess::OnChoice ), NULL, this );
	m_buttonRefresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPostProcess::OnRefresh ), NULL, this );
	m_propertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( GUIPostProcess::OnPropertyGridChange ), NULL, this );
	m_buttonExport->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPostProcess::OnExport ), NULL, this );
}

GUIPostProcess::~GUIPostProcess()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIPostProcess::OnXClose ) );
	m_choiceSelect->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIPostProcess::OnChoice ), NULL, this );
	m_buttonRefresh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPostProcess::OnRefresh ), NULL, this );
	m_propertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( GUIPostProcess::OnPropertyGridChange ), NULL, this );
	m_buttonExport->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPostProcess::OnExport ), NULL, this );
	
}

GUITestGCode::GUITestGCode( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerPrevious;
	bSizerPrevious = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtnG20 = new wxRadioButton( this, wxID_ANY, _("G20 - inches"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnG20->SetValue( true ); 
	m_radioBtnG20->SetToolTip( _("Assume that in a previous block a G20 command was issued.") );
	
	bSizerPrevious->Add( m_radioBtnG20, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_radioBtnG21 = new wxRadioButton( this, wxID_ANY, _("G21 - mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnG21->SetToolTip( _("Assume that in a previous block a G21 command was issued.") );
	
	bSizerPrevious->Add( m_radioBtnG21, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizerPrevious, 0, 0, 5 );
	
	wxBoxSizer* bSizerInput;
	bSizerInput = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlInput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlInput->SetToolTip( _("G-Code block to analyse.") );
	
	bSizerInput->Add( m_textCtrlInput, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonClear = new wxButton( this, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonClear->SetToolTip( _("Clear text int the input field.") );
	
	bSizerInput->Add( m_buttonClear, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	
	bSizer->Add( bSizerInput, 0, wxEXPAND, 5 );
	
	m_textCtrlOutput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_textCtrlOutput->SetToolTip( _("Interpretation of the G-Code.") );
	
	bSizer->Add( m_textCtrlOutput, 1, wxALL|wxEXPAND, 5 );
	
	m_textCtrlRecreated = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlRecreated->SetToolTip( _("Reconstruction of the G-Code block.") );
	
	bSizer->Add( m_textCtrlRecreated, 0, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	m_radioBtnG20->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUITestGCode::OnText ), NULL, this );
	m_radioBtnG21->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUITestGCode::OnText ), NULL, this );
	m_textCtrlInput->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUITestGCode::OnText ), NULL, this );
	m_buttonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUITestGCode::OnClear ), NULL, this );
}

GUITestGCode::~GUITestGCode()
{
	// Disconnect Events
	m_radioBtnG20->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUITestGCode::OnText ), NULL, this );
	m_radioBtnG21->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUITestGCode::OnText ), NULL, this );
	m_textCtrlInput->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUITestGCode::OnText ), NULL, this );
	m_buttonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUITestGCode::OnClear ), NULL, this );
	
}

GUISetupPaths::GUISetupPaths( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextProject = new wxStaticText( this, wxID_ANY, _("Directory for projects:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProject->Wrap( -1 );
	bSizer->Add( m_staticTextProject, 0, wxALL, 5 );
	
	m_dirPickerProjectDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select project directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerProjectDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextObjectDirectory = new wxStaticText( this, wxID_ANY, _("Objects are imported from:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextObjectDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextObjectDirectory, 0, wxALL, 5 );
	
	m_dirPickerObjectDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select object directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerObjectDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextToolpathDirectory = new wxStaticText( this, wxID_ANY, _("Output directory for exported NC toolpaths:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolpathDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextToolpathDirectory, 0, wxALL, 5 );
	
	m_dirPickerToolpathDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select toolpath output directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerToolpathDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextToolboxDirectory = new wxStaticText( this, wxID_ANY, _("Tool libraries:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolboxDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextToolboxDirectory, 0, wxALL, 5 );
	
	m_dirPickerToolboxDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select toolbox directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerToolboxDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextPostProcessorDirectory = new wxStaticText( this, wxID_ANY, _("Post-Processors:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessorDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextPostProcessorDirectory, 0, wxALL, 5 );
	
	m_dirPickerPostProcessorDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select post-processor directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerPostProcessorDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextMachineDirectory = new wxStaticText( this, wxID_ANY, _("Machine models:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMachineDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextMachineDirectory, 0, wxALL, 5 );
	
	m_dirPickerMachineDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select machine-model directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerMachineDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonClose = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupPaths::OnClose ), NULL, this );
}

GUISetupPaths::~GUISetupPaths()
{
	// Disconnect Events
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupPaths::OnClose ), NULL, this );
	
}

GUIToolbox::GUIToolbox( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_treeListCtrl = new wxTreeListCtrl( this, ID_TOOLBOXLIST, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );
	m_treeListCtrl->AppendColumn( _("Name"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_treeListCtrl->AppendColumn( _("Diameter"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_treeListCtrl->AppendColumn( _("Type"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_treeListCtrl->AppendColumn( _("Number"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );
	
	bSizer->Add( m_treeListCtrl, 1, wxALL|wxEXPAND, 5 );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT );
	m_panelTool = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelTool;
	bSizerPanelTool = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindowTool = new wxScrolledWindow( m_panelTool, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindowTool->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerTool;
	bSizerTool = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextToolType = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolType->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolType, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_choiceToolTypeChoices[] = { _("Flat end mill (cylindric)"), _("Ball end mill (spheric)"), _("Bull nose end mill (mixing ball and flat)"), _("Camfer mill (triangle)"), _("Radius mill"), _("Tool holder"), _("Tool shaft"), _("Probe") };
	int m_choiceToolTypeNChoices = sizeof( m_choiceToolTypeChoices ) / sizeof( wxString );
	m_choiceToolType = new wxChoice( m_scrolledWindowTool, ID_TOOLTYPE, wxDefaultPosition, wxDefaultSize, m_choiceToolTypeNChoices, m_choiceToolTypeChoices, 0 );
	m_choiceToolType->SetSelection( 0 );
	bSizerTool->Add( m_choiceToolType, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextToolDescription = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolDescription->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolDescription, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_textCtrlToolDescription = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLDESCRIPTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizerTool->Add( m_textCtrlToolDescription, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextToolVendor = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("Vendor:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolVendor->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolVendor, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_textCtrlToolVendor = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLVENDOR, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizerTool->Add( m_textCtrlToolVendor, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextToolGUID = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("GUID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolGUID->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolGUID, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_textCtrlToolGUID = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLGUID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlToolGUID->SetToolTip( _("Unique string used to identify tool.\n(In case of doubt, just hit some random keys.)") );
	
	bSizerTool->Add( m_textCtrlToolGUID, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextToolProductID = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("Product ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolProductID->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolProductID, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_textCtrlToolProductID = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLPRODUCTID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizerTool->Add( m_textCtrlToolProductID, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextToolProductLink = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("Product link:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolProductLink->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolProductLink, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_textCtrlToolProductLink = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLPRODUCTLINK, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizerTool->Add( m_textCtrlToolProductLink, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextToolGrade = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("Grade:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolGrade->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolGrade, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlToolGrade = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLGRADE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizerTool->Add( m_textCtrlToolGrade, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextToolBMC = new wxStaticText( m_scrolledWindowTool, wxID_ANY, _("BMC:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolBMC->Wrap( -1 );
	bSizerTool->Add( m_staticTextToolBMC, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlToolBMC = new wxTextCtrl( m_scrolledWindowTool, ID_TOOLBMC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTool->Add( m_textCtrlToolBMC, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxString m_radioBoxToolUnitChoices[] = { _("Metric"), _("Imperial") };
	int m_radioBoxToolUnitNChoices = sizeof( m_radioBoxToolUnitChoices ) / sizeof( wxString );
	m_radioBoxToolUnit = new wxRadioBox( m_scrolledWindowTool, ID_TOOLUNIT, _("Units in file:"), wxDefaultPosition, wxDefaultSize, m_radioBoxToolUnitNChoices, m_radioBoxToolUnitChoices, 2, wxRA_SPECIFY_COLS );
	m_radioBoxToolUnit->SetSelection( 0 );
	m_radioBoxToolUnit->SetToolTip( _("These units are only used, when saving the toolbox to a file.") );
	
	bSizerTool->Add( m_radioBoxToolUnit, 0, wxALL|wxEXPAND, 5 );
	
	
	m_scrolledWindowTool->SetSizer( bSizerTool );
	m_scrolledWindowTool->Layout();
	bSizerTool->Fit( m_scrolledWindowTool );
	bSizerPanelTool->Add( m_scrolledWindowTool, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelTool->SetSizer( bSizerPanelTool );
	m_panelTool->Layout();
	bSizerPanelTool->Fit( m_panelTool );
	m_notebook->AddPage( m_panelTool, _("Tool"), true );
	m_panelGeometry = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelGeometry;
	bSizerPanelGeometry = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindowGeometry = new wxScrolledWindow( m_panelGeometry, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindowGeometry->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizerPanelGeometry;
	fgSizerPanelGeometry = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizerPanelGeometry->AddGrowableCol( 0 );
	fgSizerPanelGeometry->SetFlexibleDirection( wxBOTH );
	fgSizerPanelGeometry->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextDC = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Cutting diameter (DC):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDC->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextDC, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlDC = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLDC, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlDC, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitDC = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDC->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitDC, 0, wxALL, 5 );
	
	m_staticTextLCF = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Length of cutting flutes (LCF):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLCF->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextLCF, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlLCF = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLLCF, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlLCF->SetToolTip( _("Basically the maximum cutting depth.") );
	
	fgSizerPanelGeometry->Add( m_textCtrlLCF, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitLCF = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitLCF->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitLCF, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextLB = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Body length (LB):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLB->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextLB, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlLB = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLLB, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlLB->SetToolTip( _("Length of tool that sticks outside of the chuck.") );
	
	fgSizerPanelGeometry->Add( m_textCtrlLB, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitLB = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitLB->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitLB, 0, wxALL, 5 );
	
	m_staticTextOAL = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Overall length (OAL):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOAL->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextOAL, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlOAL = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLOAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOAL->SetToolTip( _("Total length of tool.") );
	
	fgSizerPanelGeometry->Add( m_textCtrlOAL, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitOAL = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitOAL->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitOAL, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextNOF = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Number of flutes (NOF):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextNOF->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextNOF, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlNOF = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLNOF, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlNOF, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextNT = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Number of teeth (NT):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextNT->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextNT, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlNT = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLNT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlNT, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextRE = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Corner radius (RE):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRE->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextRE, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlRE = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLRE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlRE, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitRE = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRE->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitRE, 0, wxALL, 5 );
	
	m_staticTextSIG = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Point angle (SIG):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSIG->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextSIG, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSIG = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLSIG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlSIG, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSIG = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSIG->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitSIG, 0, wxALL, 5 );
	
	m_staticTextTA = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Taper pitch (TA):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTA->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextTA, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlTA = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLTA, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlTA, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextUnitTA = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitTA->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitTA, 0, wxALL, 5 );
	
	m_staticTextCSP = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Coolant supply property (CSP):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextCSP->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextCSP, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxString m_choiceCSPChoices[] = { _("false"), _("true") };
	int m_choiceCSPNChoices = sizeof( m_choiceCSPChoices ) / sizeof( wxString );
	m_choiceCSP = new wxChoice( m_scrolledWindowGeometry, ID_TOOLCSP, wxDefaultPosition, wxDefaultSize, m_choiceCSPNChoices, m_choiceCSPChoices, 0 );
	m_choiceCSP->SetSelection( 0 );
	fgSizerPanelGeometry->Add( m_choiceCSP, 1, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextHAND = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("HAND:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHAND->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextHAND, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxString m_choiceHANDChoices[] = { _("false"), _("true") };
	int m_choiceHANDNChoices = sizeof( m_choiceHANDChoices ) / sizeof( wxString );
	m_choiceHAND = new wxChoice( m_scrolledWindowGeometry, ID_TOOLHAND, wxDefaultPosition, wxDefaultSize, m_choiceHANDNChoices, m_choiceHANDChoices, 0 );
	m_choiceHAND->SetSelection( 0 );
	fgSizerPanelGeometry->Add( m_choiceHAND, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticTextSFDM = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Shaft diameter (SFDM):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSFDM->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextSFDM, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSFDM = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLSFDM, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlSFDM->SetToolTip( _("The shaft may be wider or smaller than the cutting diameter of the tool.") );
	
	fgSizerPanelGeometry->Add( m_textCtrlSFDM, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSFDM = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSFDM->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitSFDM, 0, wxALL, 5 );
	
	m_staticTextShoulderLength = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Shoulder length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoulderLength->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextShoulderLength, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlShoulderLength = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLSHOULDERLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlShoulderLength, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitShoulderLength = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShoulderLength->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitShoulderLength, 0, wxALL, 5 );
	
	m_staticTextTipDiameter = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Tip diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipDiameter->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextTipDiameter, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlTipDiameter = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLTIPDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlTipDiameter, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitTipDiameter = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitTipDiameter->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitTipDiameter, 0, wxALL, 5 );
	
	m_staticTextTipLength = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Tip length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipLength->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextTipLength, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlTipLength = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlTipLength, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextUnitTipLength = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitTipLength->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitTipLength, 0, wxALL, 5 );
	
	m_staticTextTipOffset = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Tip offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipOffset->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextTipOffset, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlTipOffset = new wxTextCtrl( m_scrolledWindowGeometry, ID_TOOLTIPOFFSET, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlTipOffset, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitTipOffset = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitTipOffset->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitTipOffset, 0, wxALL, 5 );
	
	m_staticTextThreadProfileAngle = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("Thread profile angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextThreadProfileAngle->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextThreadProfileAngle, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerPanelGeometry->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlThreadProfileAngle = new wxTextCtrl( m_scrolledWindowGeometry, ID_THREADPROFILEANGLE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerPanelGeometry->Add( m_textCtrlThreadProfileAngle, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitThreadProfileAngle = new wxStaticText( m_scrolledWindowGeometry, wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitThreadProfileAngle->Wrap( -1 );
	fgSizerPanelGeometry->Add( m_staticTextUnitThreadProfileAngle, 0, wxALL, 5 );
	
	
	m_scrolledWindowGeometry->SetSizer( fgSizerPanelGeometry );
	m_scrolledWindowGeometry->Layout();
	fgSizerPanelGeometry->Fit( m_scrolledWindowGeometry );
	bSizerPanelGeometry->Add( m_scrolledWindowGeometry, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panelGeometry->SetSizer( bSizerPanelGeometry );
	m_panelGeometry->Layout();
	bSizerPanelGeometry->Fit( m_panelGeometry );
	m_notebook->AddPage( m_panelGeometry, _("Geometry"), false );
	m_panelShape = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelShape;
	bSizerPanelShape = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxShapeFromGeometry = new wxCheckBox( m_panelShape, ID_SHAPEFROMGEOMETRY, _("Shape from Geometry"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxShapeFromGeometry->SetValue(true); 
	bSizerPanelShape->Add( m_checkBoxShapeFromGeometry, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerShapeButtons;
	bSizerShapeButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonShapeSegmentAdd = new wxButton( m_panelShape, ID_SHAPESEGMENTADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonShapeSegmentAdd->SetToolTip( _("Add a segment to the tool shape.") );
	
	bSizerShapeButtons->Add( m_buttonShapeSegmentAdd, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonShapeSegmentDelete = new wxButton( m_panelShape, ID_SHAPESEGMENTDELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonShapeSegmentDelete->SetToolTip( _("Delete the selected segment from the tool shape.") );
	
	bSizerShapeButtons->Add( m_buttonShapeSegmentDelete, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizerPanelShape->Add( bSizerShapeButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizerShape;
	sbSizerShape = new wxStaticBoxSizer( new wxStaticBox( m_panelShape, wxID_ANY, _("Segment") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerShape;
	fgSizerShape = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerShape->AddGrowableCol( 1 );
	fgSizerShape->SetFlexibleDirection( wxHORIZONTAL );
	fgSizerShape->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticTextShapeUpperDiameter = new wxStaticText( sbSizerShape->GetStaticBox(), wxID_ANY, _("Upper Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShapeUpperDiameter->Wrap( -1 );
	fgSizerShape->Add( m_staticTextShapeUpperDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShapeUpperDiameter = new wxTextCtrl( sbSizerShape->GetStaticBox(), ID_SHAPEUPPERDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShapeUpperDiameter->SetToolTip( _("Upper diameter of the selected segment.") );
	
	fgSizerShape->Add( m_textCtrlShapeUpperDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitShapeUpperDiameter = new wxStaticText( sbSizerShape->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShapeUpperDiameter->Wrap( -1 );
	fgSizerShape->Add( m_staticTextUnitShapeUpperDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShapeLowerDiameter = new wxStaticText( sbSizerShape->GetStaticBox(), wxID_ANY, _("Lower Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShapeLowerDiameter->Wrap( -1 );
	fgSizerShape->Add( m_staticTextShapeLowerDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShapeLowerDiameter = new wxTextCtrl( sbSizerShape->GetStaticBox(), ID_SHAPELOWERDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShapeLowerDiameter->SetToolTip( _("Lower diameter of the selected segment.") );
	
	fgSizerShape->Add( m_textCtrlShapeLowerDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitShapeLowerDiameter = new wxStaticText( sbSizerShape->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShapeLowerDiameter->Wrap( -1 );
	fgSizerShape->Add( m_staticTextUnitShapeLowerDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShapeHeight = new wxStaticText( sbSizerShape->GetStaticBox(), wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShapeHeight->Wrap( -1 );
	fgSizerShape->Add( m_staticTextShapeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShapeHeight = new wxTextCtrl( sbSizerShape->GetStaticBox(), ID_SHAPEHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShapeHeight->SetToolTip( _("Height of the selected segment.") );
	
	fgSizerShape->Add( m_textCtrlShapeHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitShapeHeight = new wxStaticText( sbSizerShape->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShapeHeight->Wrap( -1 );
	fgSizerShape->Add( m_staticTextUnitShapeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerShape->Add( fgSizerShape, 0, wxEXPAND, 5 );
	
	
	bSizerPanelShape->Add( sbSizerShape, 0, wxEXPAND, 5 );
	
	m_dataViewListCtrlShapeSegments = new wxDataViewListCtrl( m_panelShape, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES|wxDV_ROW_LINES|wxDV_VERT_RULES );
	m_dataViewListColumnShapeUpper = m_dataViewListCtrlShapeSegments->AppendTextColumn( _("Upper") );
	m_dataViewListColumnShapeLower = m_dataViewListCtrlShapeSegments->AppendTextColumn( _("Lower") );
	m_dataViewListColumnShapeHeight = m_dataViewListCtrlShapeSegments->AppendTextColumn( _("Height") );
	bSizerPanelShape->Add( m_dataViewListCtrlShapeSegments, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelShape->SetSizer( bSizerPanelShape );
	m_panelShape->Layout();
	bSizerPanelShape->Fit( m_panelShape );
	m_notebook->AddPage( m_panelShape, _("Shape"), false );
	m_panelHolder = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerHolder;
	bSizerHolder = new wxBoxSizer( wxVERTICAL );
	
	wxString m_choiceHolderChoices[] = { _("None"), _("Holder definition below") };
	int m_choiceHolderNChoices = sizeof( m_choiceHolderChoices ) / sizeof( wxString );
	m_choiceHolder = new wxChoice( m_panelHolder, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceHolderNChoices, m_choiceHolderChoices, 0 );
	m_choiceHolder->SetSelection( 0 );
	bSizerHolder->Add( m_choiceHolder, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerHolderButtons;
	bSizerHolderButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonHolderSegmentAdd = new wxButton( m_panelHolder, ID_HOLDERSEGMENTADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonHolderSegmentAdd->SetToolTip( _("Add a segment to the holder shape.") );
	
	bSizerHolderButtons->Add( m_buttonHolderSegmentAdd, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonHolderSegmentDelete = new wxButton( m_panelHolder, ID_HOLDERSEGMENTDELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonHolderSegmentDelete->SetToolTip( _("Delete the selected segment from the holder shape.") );
	
	bSizerHolderButtons->Add( m_buttonHolderSegmentDelete, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizerHolder->Add( bSizerHolderButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizerHolder;
	sbSizerHolder = new wxStaticBoxSizer( new wxStaticBox( m_panelHolder, wxID_ANY, _("Segment") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerHolder;
	fgSizerHolder = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerHolder->AddGrowableCol( 1 );
	fgSizerHolder->SetFlexibleDirection( wxBOTH );
	fgSizerHolder->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextHolderUpperDiameter = new wxStaticText( sbSizerHolder->GetStaticBox(), wxID_ANY, _("Upper Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHolderUpperDiameter->Wrap( -1 );
	fgSizerHolder->Add( m_staticTextHolderUpperDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHolderUpperDiameter = new wxTextCtrl( sbSizerHolder->GetStaticBox(), ID_UPPERDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlHolderUpperDiameter->SetToolTip( _("Upper diameter of the selected segment.") );
	
	fgSizerHolder->Add( m_textCtrlHolderUpperDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHolderUpperDiameter = new wxStaticText( sbSizerHolder->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHolderUpperDiameter->Wrap( -1 );
	fgSizerHolder->Add( m_staticTextUnitHolderUpperDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextHolderLowerDiameter = new wxStaticText( sbSizerHolder->GetStaticBox(), wxID_ANY, _("Lower Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHolderLowerDiameter->Wrap( -1 );
	fgSizerHolder->Add( m_staticTextHolderLowerDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHolderLowerDiameter = new wxTextCtrl( sbSizerHolder->GetStaticBox(), ID_HOLDERLOWERDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlHolderLowerDiameter->SetToolTip( _("Lower diameter of the selected segment.") );
	
	fgSizerHolder->Add( m_textCtrlHolderLowerDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHolderLowerDiameter = new wxStaticText( sbSizerHolder->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHolderLowerDiameter->Wrap( -1 );
	fgSizerHolder->Add( m_staticTextUnitHolderLowerDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextHolderHeight = new wxStaticText( sbSizerHolder->GetStaticBox(), wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHolderHeight->Wrap( -1 );
	fgSizerHolder->Add( m_staticTextHolderHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHolderHeight = new wxTextCtrl( sbSizerHolder->GetStaticBox(), ID_HOLDERHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlHolderHeight->SetToolTip( _("Height of the selected segment.") );
	
	fgSizerHolder->Add( m_textCtrlHolderHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHolderHeight = new wxStaticText( sbSizerHolder->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHolderHeight->Wrap( -1 );
	fgSizerHolder->Add( m_staticTextUnitHolderHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerHolder->Add( fgSizerHolder, 0, wxEXPAND, 5 );
	
	
	bSizerHolder->Add( sbSizerHolder, 0, wxEXPAND, 5 );
	
	m_dataViewListCtrlHolderSegments = new wxDataViewListCtrl( m_panelHolder, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_dataViewListColumnHolderUpper = m_dataViewListCtrlHolderSegments->AppendTextColumn( _("Upper") );
	m_dataViewListColumnHolderLower = m_dataViewListCtrlHolderSegments->AppendTextColumn( _("Lower") );
	m_dataViewListColumnHolderHeight = m_dataViewListCtrlHolderSegments->AppendTextColumn( _("Height") );
	bSizerHolder->Add( m_dataViewListCtrlHolderSegments, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelHolder->SetSizer( bSizerHolder );
	m_panelHolder->Layout();
	bSizerHolder->Fit( m_panelHolder );
	m_notebook->AddPage( m_panelHolder, _("Holder"), false );
	m_panelShaft = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelShaft;
	bSizerPanelShaft = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxShaftFromGeometry = new wxCheckBox( m_panelShaft, ID_SHAFTFROMGEOMETRY, _("Shaft from Geometry"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxShaftFromGeometry->SetValue(true); 
	bSizerPanelShaft->Add( m_checkBoxShaftFromGeometry, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerShaftButtons;
	bSizerShaftButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonShaftSegmentAdd = new wxButton( m_panelShaft, ID_SHAFTSEGMENTADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonShaftSegmentAdd->SetToolTip( _("Add a segment to the shaft shape.") );
	
	bSizerShaftButtons->Add( m_buttonShaftSegmentAdd, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_buttonShapeDelete = new wxButton( m_panelShaft, ID_SHAFTSEGMENTDELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonShapeDelete->SetToolTip( _("Delete the selected segment from the shaft shape.") );
	
	bSizerShaftButtons->Add( m_buttonShapeDelete, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizerPanelShaft->Add( bSizerShaftButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizerShaft;
	sbSizerShaft = new wxStaticBoxSizer( new wxStaticBox( m_panelShaft, wxID_ANY, _("Segment") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerShaft;
	fgSizerShaft = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerShaft->AddGrowableCol( 1 );
	fgSizerShaft->SetFlexibleDirection( wxBOTH );
	fgSizerShaft->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextShaftUpperDiameter = new wxStaticText( sbSizerShaft->GetStaticBox(), wxID_ANY, _("Upper Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShaftUpperDiameter->Wrap( -1 );
	fgSizerShaft->Add( m_staticTextShaftUpperDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftUpperDiameter = new wxTextCtrl( sbSizerShaft->GetStaticBox(), ID_SHAFTUPPERDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftUpperDiameter->SetToolTip( _("Upper diameter of the selected segment.") );
	
	fgSizerShaft->Add( m_textCtrlShaftUpperDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitShaftUpperDiameter = new wxStaticText( sbSizerShaft->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftUpperDiameter->Wrap( -1 );
	fgSizerShaft->Add( m_staticTextUnitShaftUpperDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShaftLowerDiameter = new wxStaticText( sbSizerShaft->GetStaticBox(), wxID_ANY, _("Lower Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShaftLowerDiameter->Wrap( -1 );
	fgSizerShaft->Add( m_staticTextShaftLowerDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftLowerDiameter = new wxTextCtrl( sbSizerShaft->GetStaticBox(), ID_SHAFTLOWERDIAMETER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftLowerDiameter->SetToolTip( _("Lower diameter of the selected segment.") );
	
	fgSizerShaft->Add( m_textCtrlShaftLowerDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitShaftLowerDiameter = new wxStaticText( sbSizerShaft->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftLowerDiameter->Wrap( -1 );
	fgSizerShaft->Add( m_staticTextUnitShaftLowerDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShaftHeight = new wxStaticText( sbSizerShaft->GetStaticBox(), wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShaftHeight->Wrap( -1 );
	fgSizerShaft->Add( m_staticTextShaftHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftHeight = new wxTextCtrl( sbSizerShaft->GetStaticBox(), ID_SHAFTHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftHeight->SetToolTip( _("Height of the selected segment.") );
	
	fgSizerShaft->Add( m_textCtrlShaftHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitShaftHeight = new wxStaticText( sbSizerShaft->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftHeight->Wrap( -1 );
	fgSizerShaft->Add( m_staticTextUnitShaftHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerShaft->Add( fgSizerShaft, 0, wxEXPAND, 5 );
	
	
	bSizerPanelShaft->Add( sbSizerShaft, 0, wxEXPAND, 5 );
	
	m_dataViewListCtrlShaftSegments = new wxDataViewListCtrl( m_panelShaft, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_dataViewListColumnShaftUpperDiameter = m_dataViewListCtrlShaftSegments->AppendTextColumn( _("Upper") );
	m_dataViewListColumnShaftLowerDiameter = m_dataViewListCtrlShaftSegments->AppendTextColumn( _("Lower") );
	m_dataViewListColumnShaftHeight = m_dataViewListCtrlShaftSegments->AppendTextColumn( _("Height") );
	bSizerPanelShaft->Add( m_dataViewListCtrlShaftSegments, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelShaft->SetSizer( bSizerPanelShaft );
	m_panelShaft->Layout();
	bSizerPanelShaft->Fit( m_panelShaft );
	m_notebook->AddPage( m_panelShaft, _("Shaft"), false );
	m_panelFeedsSpeeds = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelFeedsSpeeds;
	bSizerPanelFeedsSpeeds = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindowFeedsSpeeds = new wxScrolledWindow( m_panelFeedsSpeeds, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindowFeedsSpeeds->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerFeedsSpeeds;
	bSizerFeedsSpeeds = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerSet;
	sbSizerSet = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowFeedsSpeeds, wxID_ANY, _("Set") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerParameterSet;
	fgSizerParameterSet = new wxFlexGridSizer( 8, 1, 0, 0 );
	fgSizerParameterSet->AddGrowableCol( 0 );
	fgSizerParameterSet->SetFlexibleDirection( wxBOTH );
	fgSizerParameterSet->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSetName = new wxStaticText( sbSizerSet->GetStaticBox(), wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSetName->Wrap( -1 );
	fgSizerParameterSet->Add( m_staticTextSetName, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlSetName = new wxTextCtrl( sbSizerSet->GetStaticBox(), ID_SETNAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerParameterSet->Add( m_textCtrlSetName, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextSetGUID = new wxStaticText( sbSizerSet->GetStaticBox(), wxID_ANY, _("GUID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSetGUID->Wrap( -1 );
	fgSizerParameterSet->Add( m_staticTextSetGUID, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlSetGUID = new wxTextCtrl( sbSizerSet->GetStaticBox(), ID_SETGUID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerParameterSet->Add( m_textCtrlSetGUID, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextSetDescription = new wxStaticText( sbSizerSet->GetStaticBox(), wxID_ANY, _("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSetDescription->Wrap( -1 );
	fgSizerParameterSet->Add( m_staticTextSetDescription, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlSetDescription = new wxTextCtrl( sbSizerSet->GetStaticBox(), ID_SETDESCRIPTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerParameterSet->Add( m_textCtrlSetDescription, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextSetToolCoolant = new wxStaticText( sbSizerSet->GetStaticBox(), wxID_ANY, _("Tool coolant:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSetToolCoolant->Wrap( -1 );
	fgSizerParameterSet->Add( m_staticTextSetToolCoolant, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlSetToolCoolant = new wxTextCtrl( sbSizerSet->GetStaticBox(), ID_SETTOOLCOOLANT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerParameterSet->Add( m_textCtrlSetToolCoolant, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	sbSizerSet->Add( fgSizerParameterSet, 0, wxEXPAND, 5 );
	
	
	bSizerFeedsSpeeds->Add( sbSizerSet, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerFeed;
	sbSizerFeed = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowFeedsSpeeds, wxID_ANY, _("Feed") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerFeed;
	fgSizerFeed = new wxFlexGridSizer( 8, 2, 0, 0 );
	fgSizerFeed->AddGrowableCol( 0 );
	fgSizerFeed->SetFlexibleDirection( wxBOTH );
	fgSizerFeed->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextFeedPerRevolution = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("per Revolution:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFeedPerRevolution->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextFeedPerRevolution, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerFeed->Add( 0, 0, 0, 0, 5 );
	
	m_textCtrlFeedPerRevolution = new wxTextCtrl( sbSizerFeed->GetStaticBox(), ID_FEEDPERREVOLUTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFeed->Add( m_textCtrlFeedPerRevolution, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitFeedPerRevolution = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedPerRevolution->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextUnitFeedPerRevolution, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFeedPerTooth = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("per Tooth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFeedPerTooth->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextFeedPerTooth, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerFeed->Add( 0, 0, 0, 0, 5 );
	
	m_textCtrlFeedPerTooth = new wxTextCtrl( sbSizerFeed->GetStaticBox(), ID_FEEDPERTOOTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFeed->Add( m_textCtrlFeedPerTooth, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitFeedPerTooth = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedPerTooth->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextUnitFeedPerTooth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFeedSpindleSpeed = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("Spindle speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFeedSpindleSpeed->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextFeedSpindleSpeed, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerFeed->Add( 0, 0, 0, 0, 5 );
	
	m_textCtrlFeedSpindleSpeed = new wxTextCtrl( sbSizerFeed->GetStaticBox(), ID_SPINDLESPEED, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFeed->Add( m_textCtrlFeedSpindleSpeed, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitFeedSpindleSpeed = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedSpindleSpeed->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextUnitFeedSpindleSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFeedSpindleSpeedRampe = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("Spindle speed-ramp:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFeedSpindleSpeedRampe->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextFeedSpindleSpeedRampe, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerFeed->Add( 0, 0, 0, 0, 5 );
	
	m_textCtrlFeedSpindleSpeedRamp = new wxTextCtrl( sbSizerFeed->GetStaticBox(), ID_SPINDLESPEEDRAMP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFeed->Add( m_textCtrlFeedSpindleSpeedRamp, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitFeedSpindleSpeedRamp = new wxStaticText( sbSizerFeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedSpindleSpeedRamp->Wrap( -1 );
	fgSizerFeed->Add( m_staticTextUnitFeedSpindleSpeedRamp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerFeed->Add( fgSizerFeed, 0, wxEXPAND, 5 );
	
	
	bSizerFeedsSpeeds->Add( sbSizerFeed, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerSpeed;
	sbSizerSpeed = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindowFeedsSpeeds, wxID_ANY, _("Speed") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerSpeed;
	fgSizerSpeed = new wxFlexGridSizer( 14, 2, 0, 0 );
	fgSizerSpeed->AddGrowableCol( 0 );
	fgSizerSpeed->SetFlexibleDirection( wxBOTH );
	fgSizerSpeed->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSpeedCuttingFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Cutting feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedCuttingFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedCuttingFeedrate, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedCuttingFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_CUTTINGFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedCuttingFeedrate, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSpeedCuttingFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedCuttingFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedCuttingFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSpeedAvgFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Avg. feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedAvgFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedAvgFeedrate, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedAvgFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_AVGFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedAvgFeedrate, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSpeedAvgFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedAvgFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedAvgFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSpeedLeadInFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Lead-in feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedLeadInFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedLeadInFeedrate, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedLeadInFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_LEADINFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedLeadInFeedrate, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSpeedLeadInFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedLeadInFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedLeadInFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSpeedLeadOutFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Lead-out feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedLeadOutFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedLeadOutFeedrate, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedLeadOutFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_LEADOUTFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedLeadOutFeedrate, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSpeedLeadOutFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedLeadOutFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedLeadOutFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSpeedPlungeFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Plunge feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedPlungeFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedPlungeFeedrate, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedPlungeFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_PLUNGEFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedPlungeFeedrate, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSpeedPlungeFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedPlungeFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedPlungeFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSpeedRampFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Ramp feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedRampFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedRampFeedrate, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedRampFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_RAMPFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedRampFeedrate, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextUnitSpeedRampFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedRampFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedRampFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSpeedRetractionFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("Retraction feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSpeedRetractionFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextSpeedRetractionFeedrate, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	fgSizerSpeed->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlSpeedRetractionFeedrate = new wxTextCtrl( sbSizerSpeed->GetStaticBox(), ID_RETRACTIONFEEDRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerSpeed->Add( m_textCtrlSpeedRetractionFeedrate, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticTextUnitSpeedRetractionFeedrate = new wxStaticText( sbSizerSpeed->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitSpeedRetractionFeedrate->Wrap( -1 );
	fgSizerSpeed->Add( m_staticTextUnitSpeedRetractionFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerSpeed->Add( fgSizerSpeed, 0, wxEXPAND, 5 );
	
	
	bSizerFeedsSpeeds->Add( sbSizerSpeed, 0, wxEXPAND, 5 );
	
	
	m_scrolledWindowFeedsSpeeds->SetSizer( bSizerFeedsSpeeds );
	m_scrolledWindowFeedsSpeeds->Layout();
	bSizerFeedsSpeeds->Fit( m_scrolledWindowFeedsSpeeds );
	bSizerPanelFeedsSpeeds->Add( m_scrolledWindowFeedsSpeeds, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panelFeedsSpeeds->SetSizer( bSizerPanelFeedsSpeeds );
	m_panelFeedsSpeeds->Layout();
	bSizerPanelFeedsSpeeds->Fit( m_panelFeedsSpeeds );
	m_notebook->AddPage( m_panelFeedsSpeeds, _("Feeds&&\nSpeeds"), false );
	m_panelPostProcess = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelPostProcess;
	bSizerPanelPostProcess = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindowPostProcess = new wxScrolledWindow( m_panelPostProcess, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindowPostProcess->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizerPostProcess;
	bSizerPostProcess = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxLive = new wxCheckBox( m_scrolledWindowPostProcess, ID_POSTPROCESSLIVE, _("Live"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_checkBoxLive, 0, wxALL, 5 );
	
	m_staticTextPostProcessComment = new wxStaticText( m_scrolledWindowPostProcess, wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessComment->Wrap( -1 );
	bSizerPostProcess->Add( m_staticTextPostProcessComment, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlPostProcessComment = new wxTextCtrl( m_scrolledWindowPostProcess, ID_POSTPROCESSCOMMENT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_textCtrlPostProcessComment, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextPostProcessNumber = new wxStaticText( m_scrolledWindowPostProcess, wxID_ANY, _("Number:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessNumber->Wrap( -1 );
	bSizerPostProcess->Add( m_staticTextPostProcessNumber, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlPostProcessNumber = new wxTextCtrl( m_scrolledWindowPostProcess, ID_POSTPROCESSNUMBER, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_textCtrlPostProcessNumber, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_checkBoxManualToolChange = new wxCheckBox( m_scrolledWindowPostProcess, ID_POSTPROCESSMANUALTOOLCHANGE, _("Manual tool change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_checkBoxManualToolChange, 0, wxALL, 5 );
	
	m_checkBoxBreakControl = new wxCheckBox( m_scrolledWindowPostProcess, ID_POSTPROCESSBREAKCONTROL, _("Break control"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_checkBoxBreakControl, 0, wxALL, 5 );
	
	m_staticTextPostProcessDiameterOffset = new wxStaticText( m_scrolledWindowPostProcess, wxID_ANY, _("Diameter offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessDiameterOffset->Wrap( -1 );
	bSizerPostProcess->Add( m_staticTextPostProcessDiameterOffset, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlPostProcessDiameterOffset = new wxTextCtrl( m_scrolledWindowPostProcess, ID_POSTPROCESSDIAMETEROFFSET, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_textCtrlPostProcessDiameterOffset, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextPostProcessLengthOffset = new wxStaticText( m_scrolledWindowPostProcess, wxID_ANY, _("Length offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessLengthOffset->Wrap( -1 );
	bSizerPostProcess->Add( m_staticTextPostProcessLengthOffset, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlPostProcessLengthOffset = new wxTextCtrl( m_scrolledWindowPostProcess, ID_POSTPROCESSLENGTHOFFSET, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_textCtrlPostProcessLengthOffset, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextPostProcessToolCoolant = new wxStaticText( m_scrolledWindowPostProcess, wxID_ANY, _("Tool coolant:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessToolCoolant->Wrap( -1 );
	bSizerPostProcess->Add( m_staticTextPostProcessToolCoolant, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlPostProcessToolCoolant = new wxTextCtrl( m_scrolledWindowPostProcess, ID_POSTPROCESSTOOLCOOLANT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_textCtrlPostProcessToolCoolant, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticTextPostProcessTurret = new wxStaticText( m_scrolledWindowPostProcess, wxID_ANY, _("Turret:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessTurret->Wrap( -1 );
	bSizerPostProcess->Add( m_staticTextPostProcessTurret, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrlPostProcessTurret = new wxTextCtrl( m_scrolledWindowPostProcess, ID_POSTPROCESSTURRET, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerPostProcess->Add( m_textCtrlPostProcessTurret, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	m_scrolledWindowPostProcess->SetSizer( bSizerPostProcess );
	m_scrolledWindowPostProcess->Layout();
	bSizerPostProcess->Fit( m_scrolledWindowPostProcess );
	bSizerPanelPostProcess->Add( m_scrolledWindowPostProcess, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panelPostProcess->SetSizer( bSizerPanelPostProcess );
	m_panelPostProcess->Layout();
	bSizerPanelPostProcess->Fit( m_panelPostProcess );
	m_notebook->AddPage( m_panelPostProcess, _("Post-\nProcess"), false );
	
	bSizer->Add( m_notebook, 1, wxALL|wxEXPAND, 5 );
	
	m_canvastool = new CanvasTool(this);
	bSizer->Add( m_canvastool, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolbox::OnXClose ) );
	m_treeListCtrl->Connect( wxEVT_TREELIST_ITEM_CHECKED, wxTreeListEventHandler( GUIToolbox::OnToolChecked ), NULL, this );
	m_treeListCtrl->Connect( wxEVT_TREELIST_ITEM_CONTEXT_MENU, wxTreeListEventHandler( GUIToolbox::OnToolContextMenu ), NULL, this );
	m_treeListCtrl->Connect( wxEVT_TREELIST_ITEM_EXPANDING, wxTreeListEventHandler( GUIToolbox::OnToolboxExpanding ), NULL, this );
	m_treeListCtrl->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( GUIToolbox::OnToolSelectionChanged ), NULL, this );
	m_choiceToolType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_textCtrlToolDescription->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolVendor->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolGUID->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolProductID->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolProductLink->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolGrade->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolBMC->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_radioBoxToolUnit->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( GUIToolbox::OnRadioBox ), NULL, this );
	m_textCtrlDC->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlLCF->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlLB->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlOAL->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlNOF->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlNT->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlRE->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSIG->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTA->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_choiceCSP->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_choiceHAND->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_textCtrlSFDM->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShoulderLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTipDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTipLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTipOffset->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlThreadProfileAngle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_checkBoxShapeFromGeometry->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_buttonShapeSegmentAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentAdd ), NULL, this );
	m_buttonShapeSegmentDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentDelete ), NULL, this );
	m_textCtrlShapeUpperDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShapeLowerDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShapeHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_dataViewListCtrlShapeSegments->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( GUIToolbox::OnItemBeginDrag ), NULL, this );
	m_dataViewListCtrlShapeSegments->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( GUIToolbox::OnItemDrop ), NULL, this );
	m_dataViewListCtrlShapeSegments->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_choiceHolder->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_buttonHolderSegmentAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentAdd ), NULL, this );
	m_buttonHolderSegmentDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentDelete ), NULL, this );
	m_textCtrlHolderUpperDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlHolderLowerDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlHolderHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_dataViewListCtrlHolderSegments->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( GUIToolbox::OnItemBeginDrag ), NULL, this );
	m_dataViewListCtrlHolderSegments->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( GUIToolbox::OnItemDrop ), NULL, this );
	m_dataViewListCtrlHolderSegments->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_checkBoxShaftFromGeometry->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_buttonShaftSegmentAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentAdd ), NULL, this );
	m_buttonShapeDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentDelete ), NULL, this );
	m_textCtrlShaftUpperDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShaftLowerDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShaftHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_dataViewListCtrlShaftSegments->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( GUIToolbox::OnItemBeginDrag ), NULL, this );
	m_dataViewListCtrlShaftSegments->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( GUIToolbox::OnItemDrop ), NULL, this );
	m_dataViewListCtrlShaftSegments->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_textCtrlSetName->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSetGUID->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSetDescription->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSetToolCoolant->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedPerRevolution->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedPerTooth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedSpindleSpeed->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedSpindleSpeedRamp->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedCuttingFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedAvgFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedLeadInFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedLeadOutFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedPlungeFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedRampFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedRetractionFeedrate->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_checkBoxLive->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_textCtrlPostProcessComment->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessNumber->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_checkBoxManualToolChange->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_checkBoxBreakControl->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_textCtrlPostProcessDiameterOffset->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessLengthOffset->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessToolCoolant->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessTurret->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
}

GUIToolbox::~GUIToolbox()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolbox::OnXClose ) );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_ITEM_CHECKED, wxTreeListEventHandler( GUIToolbox::OnToolChecked ), NULL, this );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_ITEM_CONTEXT_MENU, wxTreeListEventHandler( GUIToolbox::OnToolContextMenu ), NULL, this );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_ITEM_EXPANDING, wxTreeListEventHandler( GUIToolbox::OnToolboxExpanding ), NULL, this );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( GUIToolbox::OnToolSelectionChanged ), NULL, this );
	m_choiceToolType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_textCtrlToolDescription->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolVendor->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolGUID->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolProductID->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolProductLink->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolGrade->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlToolBMC->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_radioBoxToolUnit->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( GUIToolbox::OnRadioBox ), NULL, this );
	m_textCtrlDC->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlLCF->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlLB->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlOAL->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlNOF->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlNT->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlRE->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSIG->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTA->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_choiceCSP->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_choiceHAND->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_textCtrlSFDM->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShoulderLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTipDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTipLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlTipOffset->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlThreadProfileAngle->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_checkBoxShapeFromGeometry->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_buttonShapeSegmentAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentAdd ), NULL, this );
	m_buttonShapeSegmentDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentDelete ), NULL, this );
	m_textCtrlShapeUpperDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShapeLowerDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShapeHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_dataViewListCtrlShapeSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( GUIToolbox::OnItemBeginDrag ), NULL, this );
	m_dataViewListCtrlShapeSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( GUIToolbox::OnItemDrop ), NULL, this );
	m_dataViewListCtrlShapeSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_choiceHolder->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolbox::OnChoice ), NULL, this );
	m_buttonHolderSegmentAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentAdd ), NULL, this );
	m_buttonHolderSegmentDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentDelete ), NULL, this );
	m_textCtrlHolderUpperDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlHolderLowerDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlHolderHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_dataViewListCtrlHolderSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( GUIToolbox::OnItemBeginDrag ), NULL, this );
	m_dataViewListCtrlHolderSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( GUIToolbox::OnItemDrop ), NULL, this );
	m_dataViewListCtrlHolderSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_checkBoxShaftFromGeometry->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_buttonShaftSegmentAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentAdd ), NULL, this );
	m_buttonShapeDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnSegmentDelete ), NULL, this );
	m_textCtrlShaftUpperDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShaftLowerDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShaftHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_dataViewListCtrlShaftSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG, wxDataViewEventHandler( GUIToolbox::OnItemBeginDrag ), NULL, this );
	m_dataViewListCtrlShaftSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_DROP, wxDataViewEventHandler( GUIToolbox::OnItemDrop ), NULL, this );
	m_dataViewListCtrlShaftSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_textCtrlSetName->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSetGUID->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSetDescription->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSetToolCoolant->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedPerRevolution->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedPerTooth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedSpindleSpeed->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedSpindleSpeedRamp->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedCuttingFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedAvgFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedLeadInFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedLeadOutFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedPlungeFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedRampFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlSpeedRetractionFeedrate->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_checkBoxLive->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_textCtrlPostProcessComment->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessNumber->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_checkBoxManualToolChange->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_checkBoxBreakControl->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIToolbox::OnCheckBox ), NULL, this );
	m_textCtrlPostProcessDiameterOffset->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessLengthOffset->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessToolCoolant->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlPostProcessTurret->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	
}

GUIMachineDebugger::GUIMachineDebugger( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_ribbonBar = new wxRibbonBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL );
	m_ribbonBar->SetArtProvider(new wxRibbonMSWArtProvider); 
	m_ribbonPage = new wxRibbonPage( m_ribbonBar, wxID_ANY, _("Menu") , wxNullBitmap , 0 );
	m_ribbonPanelFileOperations = new wxRibbonPanel( m_ribbonPage, wxID_ANY, _("Machine Description") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarScript = new wxRibbonButtonBar( m_ribbonPanelFileOperations, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarScript->AddButton( ID_MACHINEDESCRIPTIONLOAD, _("Load"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarScript->AddButton( ID_MACHINEDESCRIPTIONSAVE, _("Save"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarScript->AddButton( ID_MACHINEDESCRIPTIONEVALUATE, _("Evaluate Script"), wxArtProvider::GetBitmap( wxART_GO_DOWN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelSettings = new wxRibbonPanel( m_ribbonPage, wxID_ANY, _("Settings") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarSettings = new wxRibbonButtonBar( m_ribbonPanelSettings, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarSettings->AddToggleButton( ID_MACHINEDEBUGGERSHOWCONTROLLER, _("Show Controller"), wxBitmap( controller_xpm ), wxEmptyString);
	m_ribbonButtonBarSettings->AddDropdownButton( ID_SHOWPREFERENCES, _("Preferences"), wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarSettings->AddToggleButton( ID_MACHINEDEBUGGERTOGGLESTEREO3D, _("Stereo 3D"), wxBitmap( stereo3D_xpm ), wxEmptyString);
	m_ribbonBar->Realize();
	
	bSizer->Add( m_ribbonBar, 0, wxALL|wxEXPAND, 5 );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter->SetSashGravity( 0.3 );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitterOnIdle ), NULL, this );
	m_splitter->SetMinimumPaneSize( 200 );
	
	m_panel = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter3 = new wxSplitterWindow( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->SetSashGravity( 0.5 );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitter3OnIdle ), NULL, this );
	
	m_panelEditor = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrlScript = new wxTextCtrl( m_panelEditor, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_RICH );
	bSizer40->Add( m_textCtrlScript, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonRestart = new wxButton( m_panelEditor, wxID_ANY, _("Evaluate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_buttonRestart, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelEditor->SetSizer( bSizer40 );
	m_panelEditor->Layout();
	bSizer40->Fit( m_panelEditor );
	m_panelOutput = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrlOutput = new wxTextCtrl( m_panelOutput, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
	bSizer41->Add( m_textCtrlOutput, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelOutput->SetSizer( bSizer41 );
	m_panelOutput->Layout();
	bSizer41->Fit( m_panelOutput );
	m_splitter3->SplitHorizontally( m_panelEditor, m_panelOutput, 409 );
	bSizer39->Add( m_splitter3, 1, wxEXPAND, 5 );
	
	
	m_panel->SetSizer( bSizer39 );
	m_panel->Layout();
	bSizer39->Fit( m_panel );
	m_panelMachineView = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new CanvasMachine(m_panelMachineView);
	bSizer38->Add( m_canvas, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelMachineView->SetSizer( bSizer38 );
	m_panelMachineView->Layout();
	bSizer38->Fit( m_panelMachineView );
	m_splitter->SplitVertically( m_panel, m_panelMachineView, 326 );
	bSizer->Add( m_splitter, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	m_statusBar3 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMachineDebugger::OnXClose ) );
	this->Connect( ID_MACHINEDESCRIPTIONLOAD, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnMachineLoad ) );
	this->Connect( ID_MACHINEDESCRIPTIONSAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnMachineSave ) );
	this->Connect( ID_MACHINEDESCRIPTIONEVALUATE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnScriptEvaluate ) );
	this->Connect( ID_MACHINEDEBUGGERSHOWCONTROLLER, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnShowController ) );
	this->Connect( ID_SHOWPREFERENCES, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnShowPreferencesMenu ) );
	this->Connect( ID_MACHINEDEBUGGERTOGGLESTEREO3D, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnToggleStereo3D ) );
	m_buttonRestart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnScriptEvaluate ), NULL, this );
}

GUIMachineDebugger::~GUIMachineDebugger()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMachineDebugger::OnXClose ) );
	this->Disconnect( ID_MACHINEDESCRIPTIONLOAD, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnMachineLoad ) );
	this->Disconnect( ID_MACHINEDESCRIPTIONSAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnMachineSave ) );
	this->Disconnect( ID_MACHINEDESCRIPTIONEVALUATE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnScriptEvaluate ) );
	this->Disconnect( ID_MACHINEDEBUGGERSHOWCONTROLLER, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnShowController ) );
	this->Disconnect( ID_SHOWPREFERENCES, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIMachineDebugger::OnShowPreferencesMenu ) );
	this->Disconnect( ID_MACHINEDEBUGGERTOGGLESTEREO3D, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnToggleStereo3D ) );
	m_buttonRestart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnScriptEvaluate ), NULL, this );
	
}

GUIMachineControl::GUIMachineControl( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuController = new wxMenu();
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuController, ID_CONTROLLERSHOW, wxString( _("Hide &Controller") ) + wxT('\t') + wxT("CTRL+SHIFT+C"), wxEmptyString, wxITEM_NORMAL );
	m_menuController->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuController, _("&Controller") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerXYZ;
	sbSizerXYZ = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool Tip") ), wxVERTICAL );
	
	wxBoxSizer* bSizerXYZ;
	bSizerXYZ = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerX;
	bSizerX = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextX = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextX->Wrap( -1 );
	bSizerX->Add( m_staticTextX, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderX = new wxSlider( sbSizerXYZ->GetStaticBox(), ID_AXISX, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizerX->Add( m_sliderX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerXYZ->Add( bSizerX, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerY;
	bSizerY = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextY = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextY->Wrap( -1 );
	bSizerY->Add( m_staticTextY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderY = new wxSlider( sbSizerXYZ->GetStaticBox(), ID_AXISY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizerY->Add( m_sliderY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerXYZ->Add( bSizerY, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerZ;
	bSizerZ = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextZ = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextZ->Wrap( -1 );
	bSizerZ->Add( m_staticTextZ, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderZ = new wxSlider( sbSizerXYZ->GetStaticBox(), ID_AXISZ, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizerZ->Add( m_sliderZ, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerXYZ->Add( bSizerZ, 0, wxEXPAND, 5 );
	
	
	sbSizerXYZ->Add( bSizerXYZ, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizerXYZ;
	fgSizerXYZ = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerXYZ->SetFlexibleDirection( wxBOTH );
	fgSizerXYZ->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTexttX = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTexttX->Wrap( -1 );
	fgSizerXYZ->Add( m_staticTexttX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlX = new wxTextCtrl( sbSizerXYZ->GetStaticBox(), ID_TEXTX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerXYZ->Add( m_textCtrlX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	fgSizerXYZ->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTexttY = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTexttY->Wrap( -1 );
	fgSizerXYZ->Add( m_staticTexttY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlY = new wxTextCtrl( sbSizerXYZ->GetStaticBox(), ID_TEXTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerXYZ->Add( m_textCtrlY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	fgSizerXYZ->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTexttZ = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTexttZ->Wrap( -1 );
	fgSizerXYZ->Add( m_staticTexttZ, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlZ = new wxTextCtrl( sbSizerXYZ->GetStaticBox(), ID_TEXTZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerXYZ->Add( m_textCtrlZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( sbSizerXYZ->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	fgSizerXYZ->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerXYZ->Add( fgSizerXYZ, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer->Add( sbSizerXYZ, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerRXRYRZ;
	sbSizerRXRYRZ = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Normal Vector") ), wxVERTICAL );
	
	wxBoxSizer* bSizerRXRYRZ;
	bSizerRXRYRZ = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerRX;
	bSizerRX = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextRX = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("RX:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRX->Wrap( -1 );
	bSizerRX->Add( m_staticTextRX, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderRX = new wxSlider( sbSizerRXRYRZ->GetStaticBox(), ID_AXISRX, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizerRX->Add( m_sliderRX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerRXRYRZ->Add( bSizerRX, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRY;
	bSizerRY = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextRY = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("RY:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRY->Wrap( -1 );
	bSizerRY->Add( m_staticTextRY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderRY = new wxSlider( sbSizerRXRYRZ->GetStaticBox(), ID_AXISRY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizerRY->Add( m_sliderRY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerRXRYRZ->Add( bSizerRY, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRZ;
	bSizerRZ = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextRZ = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("RZ:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRZ->Wrap( -1 );
	bSizerRZ->Add( m_staticTextRZ, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderRZ = new wxSlider( sbSizerRXRYRZ->GetStaticBox(), ID_AXISRZ, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizerRZ->Add( m_sliderRZ, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerRXRYRZ->Add( bSizerRZ, 0, wxEXPAND, 5 );
	
	
	sbSizerRXRYRZ->Add( bSizerRXRYRZ, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizerRXRYRZ;
	fgSizerRXRYRZ = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerRXRYRZ->SetFlexibleDirection( wxBOTH );
	fgSizerRXRYRZ->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextrRX = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("RX:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextrRX->Wrap( -1 );
	fgSizerRXRYRZ->Add( m_staticTextrRX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlRX = new wxTextCtrl( sbSizerRXRYRZ->GetStaticBox(), ID_TEXTRX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerRXRYRZ->Add( m_textCtrlRX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitRX = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRX->Wrap( -1 );
	fgSizerRXRYRZ->Add( m_staticTextUnitRX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextrRY = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("RY:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextrRY->Wrap( -1 );
	fgSizerRXRYRZ->Add( m_staticTextrRY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlRY = new wxTextCtrl( sbSizerRXRYRZ->GetStaticBox(), ID_TEXTRY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerRXRYRZ->Add( m_textCtrlRY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitRY = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRY->Wrap( -1 );
	fgSizerRXRYRZ->Add( m_staticTextUnitRY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextrRZ = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("RZ:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextrRZ->Wrap( -1 );
	fgSizerRXRYRZ->Add( m_staticTextrRZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlRZ = new wxTextCtrl( sbSizerRXRYRZ->GetStaticBox(), ID_TEXTRZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerRXRYRZ->Add( m_textCtrlRZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitRZ = new wxStaticText( sbSizerRXRYRZ->GetStaticBox(), wxID_ANY, _("______"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRZ->Wrap( -1 );
	fgSizerRXRYRZ->Add( m_staticTextUnitRZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerRXRYRZ->Add( fgSizerRXRYRZ, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer->Add( sbSizerRXRYRZ, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMachineControl::OnXClose ) );
	m_sliderX->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderY->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderZ->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlZ->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_sliderRX->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderRY->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderRZ->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlRX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlRY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlRZ->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
}

GUIMachineControl::~GUIMachineControl()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMachineControl::OnXClose ) );
	m_sliderX->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderX->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderY->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderY->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderZ->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlZ->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRX->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRY->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderRZ->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlRX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlRY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlRZ->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	
}

GUISetupUnits::GUISetupUnits( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer;
	sbSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Units ") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer( 7, 2, 0, 0 );
	fgSizer->SetFlexibleDirection( wxBOTH );
	fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText57 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText57->Wrap( -1 );
	fgSizer->Add( m_staticText57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitLengthChoices;
	m_choiceUnitLength = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitLengthChoices, 0 );
	m_choiceUnitLength->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitLength, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText58 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Linear Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText58->Wrap( -1 );
	fgSizer->Add( m_staticText58, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitSpeedLinearChoices;
	m_choiceUnitSpeedLinear = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitSpeedLinearChoices, 0 );
	m_choiceUnitSpeedLinear->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitSpeedLinear, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText59 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Rotational Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	fgSizer->Add( m_staticText59, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitSpeedRotationalChoices;
	m_choiceUnitSpeedRotational = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitSpeedRotationalChoices, 0 );
	m_choiceUnitSpeedRotational->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitSpeedRotational, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText65 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	fgSizer->Add( m_staticText65, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitTimeChoices;
	m_choiceUnitTime = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitTimeChoices, 0 );
	m_choiceUnitTime->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitTime, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticText110 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Small Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText110->Wrap( -1 );
	fgSizer->Add( m_staticText110, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitSmallDistanceChoices;
	m_choiceUnitSmallDistance = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitSmallDistanceChoices, 0 );
	m_choiceUnitSmallDistance->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitSmallDistance, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText111 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Tolerance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	fgSizer->Add( m_staticText111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitToleranceChoices;
	m_choiceUnitTolerance = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitToleranceChoices, 0 );
	m_choiceUnitTolerance->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitTolerance, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText112 = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _("Angle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText112->Wrap( -1 );
	fgSizer->Add( m_staticText112, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitAngleChoices;
	m_choiceUnitAngle = new wxChoice( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitAngleChoices, 0 );
	m_choiceUnitAngle->SetSelection( 0 );
	fgSizer->Add( m_choiceUnitAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	sbSizer->Add( fgSizer, 1, wxEXPAND, 5 );
	
	
	bSizer->Add( sbSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonClose, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText64 = new wxStaticText( this, wxID_ANY, _("Unit conversion is only used for displaying.\nInternally everything is stored in SI base units.\nPlease use Object->Modify to change object sizes."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	bSizer->Add( m_staticText64, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	m_choiceUnitLength->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSpeedLinear->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSpeedRotational->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitTime->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSmallDistance->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitTolerance->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitAngle->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupUnits::OnClose ), NULL, this );
}

GUISetupUnits::~GUISetupUnits()
{
	// Disconnect Events
	m_choiceUnitLength->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSpeedLinear->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSpeedRotational->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitTime->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSmallDistance->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitTolerance->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitAngle->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUISetupUnits::OnChangeUnit ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupUnits::OnClose ), NULL, this );
	
}

GUISetupMidi::GUISetupMidi( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listBoxDevices = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE ); 
	bSizer2->Add( m_listBoxDevices, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonRefresh = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRefresh->SetToolTip( _("Check library for connected devices.") );
	
	bSizer3->Add( m_buttonRefresh, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonCycle = new wxButton( this, wxID_ANY, _("Cycle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCycle->SetToolTip( _("Close all connection and disconnect and reconnect to the underlying library.") );
	
	bSizer3->Add( m_buttonCycle, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer3->Add( 0, 0, 1, 0, 5 );
	
	m_buttonConnect = new wxButton( this, wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonConnect->SetToolTip( _("Connect to selected midi port.") );
	
	bSizer3->Add( m_buttonConnect, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonDisconnect = new wxButton( this, wxID_ANY, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDisconnect->SetToolTip( _("Disconnect from midi port.") );
	
	bSizer3->Add( m_buttonDisconnect, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer3->Add( 0, 0, 1, 0, 5 );
	
	m_buttonClose = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonClose->SetToolTip( _("Close this window.") );
	
	bSizer3->Add( m_buttonClose, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	bSizer->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer;
	sbSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Received Messages") ), wxVERTICAL );
	
	m_textCtrlReceived = new wxTextCtrl( sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_textCtrlReceived->SetToolTip( _("Doubleclick to clear.") );
	
	sbSizer->Add( m_textCtrlReceived, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer->Add( sbSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISetupMidi::OnCloseX ) );
	m_listBoxDevices->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( GUISetupMidi::OnSelect ), NULL, this );
	m_buttonRefresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnRefresh ), NULL, this );
	m_buttonCycle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnCycle ), NULL, this );
	m_buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnConnect ), NULL, this );
	m_buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnDisconnect ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnClose ), NULL, this );
	m_textCtrlReceived->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUISetupMidi::OnClear ), NULL, this );
}

GUISetupMidi::~GUISetupMidi()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISetupMidi::OnCloseX ) );
	m_listBoxDevices->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( GUISetupMidi::OnSelect ), NULL, this );
	m_buttonRefresh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnRefresh ), NULL, this );
	m_buttonCycle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnCycle ), NULL, this );
	m_buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnConnect ), NULL, this );
	m_buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnDisconnect ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupMidi::OnClose ), NULL, this );
	m_textCtrlReceived->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUISetupMidi::OnClear ), NULL, this );
	
}
