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
#include "../icon/first.xpm"
#include "../icon/last.xpm"
#include "../icon/next.xpm"
#include "../icon/play.xpm"
#include "../icon/prev.xpm"
#include "../icon/tool_drilling.xpm"

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
	m_ribbonButtonBarProject->AddButton( wxID_NEW, _("New"), wxArtProvider::GetBitmap( wxART_NEW_DIR, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarProject->AddHybridButton( wxID_OPEN, _("Open"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarProject->AddHybridButton( wxID_SAVE, _("Save"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelView = new wxRibbonPanel( m_ribbonPageViewEdit, wxID_ANY, _("View") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarView = new wxRibbonButtonBar( m_ribbonPanelView, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarView->AddDropdownButton( ID_VIEWPREFERENCES, _("Preferences"), wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarView->AddToggleButton( ID_TOGGLESTEREO3D, _("Stereo 3D"), wxArtProvider::GetBitmap( wxART_ADD_BOOKMARK, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelEdit = new wxRibbonPanel( m_ribbonPageViewEdit, wxID_ANY, _("Edit") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarEdit = new wxRibbonButtonBar( m_ribbonPanelEdit, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarEdit->AddButton( wxID_UNDO, _("Undo"), wxArtProvider::GetBitmap( wxART_UNDO, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarEdit->AddButton( wxID_REDO, _("Redo"), wxArtProvider::GetBitmap( wxART_REDO, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonBarProjectViewEdit->Realize();
	
	bSizerRibbon->Add( m_ribbonBarProjectViewEdit, 0, wxEXPAND, 5 );
	
	m_ribbonBarCANCAM = new wxRibbonBar( this, wxID_HELP, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL|wxRIBBON_BAR_SHOW_HELP_BUTTON|wxRIBBON_BAR_SHOW_PAGE_LABELS );
	m_ribbonBarCANCAM->SetArtProvider(new wxRibbonMSWArtProvider); 
	m_ribbonPageCAD = new wxRibbonPage( m_ribbonBarCANCAM, wxID_ANY, _("CAD") , wxNullBitmap , 0 );
	m_ribbonBarCANCAM->SetActivePage( m_ribbonPageCAD ); 
	m_ribbonPanelObject = new wxRibbonPanel( m_ribbonPageCAD, wxID_ANY, _("Object") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarObject = new wxRibbonButtonBar( m_ribbonPanelObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarObject->AddButton( ID_OBJECTLOAD, _("Load"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarObject->AddButton( ID_OBJECTFLIPNORMALS, _("Flip Normals"), wxArtProvider::GetBitmap( wxART_GO_BACK, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarObject->AddButton( ID_OBJECTMODIFY, _("Modify"), wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPageCAM = new wxRibbonPage( m_ribbonBarCANCAM, wxID_ANY, _("CAM") , wxNullBitmap , 0 );
	m_ribbonPanelSetup = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Setup") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarSetup = new wxRibbonButtonBar( m_ribbonPanelSetup, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarSetup->AddButton( ID_RUNMODIFY, _("Setup"), wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelToolpath = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Toolpath") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarToolpath = new wxRibbonButtonBar( m_ribbonPanelToolpath, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarToolpath->AddDropdownButton( ID_2D, _("2D"), wxArtProvider::GetBitmap( wxART_GO_DOWN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarToolpath->AddDropdownButton( ID_3D, _("3D"), wxArtProvider::GetBitmap( wxART_GO_DOWN, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarToolpath->AddButton( ID_DRILLING, _("Drilling"), wxBitmap( tool_drilling_xpm ), wxEmptyString);
	m_ribbonButtonBarToolpath->AddDropdownButton( ID_MULTIAXIS, _("Multi-Axis"), wxArtProvider::GetBitmap( wxART_CDROM, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelPostProcess = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Post-Process") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarPostProcess = new wxRibbonButtonBar( m_ribbonPanelPostProcess, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarPostProcess->AddButton( ID_SIMULATE, _("Simulate"), wxArtProvider::GetBitmap( wxART_INFORMATION, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarPostProcess->AddButton( ID_TOOLPATHEXPORT, _("Export"), wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelManage = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Manage") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarManageCam = new wxRibbonButtonBar( m_ribbonPanelManage, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarManageCam->AddButton( ID_MANAGETOOLS, _("Tool- Library"), wxArtProvider::GetBitmap( wxART_FIND_AND_REPLACE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarManageCam->AddButton( ID_MANAGEPOSTPROCESS, _("Post- Processes"), wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarManageCam->AddButton( ID_MANAGEMACHINES, _("Machines"), wxArtProvider::GetBitmap( wxART_TIP, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonPanelTools = new wxRibbonPanel( m_ribbonPageCAM, wxID_ANY, _("Tools") , wxNullBitmap , wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE );
	m_ribbonButtonBarTools = new wxRibbonButtonBar( m_ribbonPanelTools, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_ribbonButtonBarTools->AddButton( ID_TOOLMEASURE, _("Measure"), wxArtProvider::GetBitmap( wxART_FIND, wxART_CMN_DIALOG ), wxEmptyString);
	m_ribbonButtonBarTools->AddButton( ID_GCODETEST, _("Test G-Code"), wxArtProvider::GetBitmap( wxART_QUESTION, wxART_CMN_DIALOG ), wxEmptyString);
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
	this->Connect( ID_OBJECTFLIPNORMALS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectFlipNormals ) );
	this->Connect( ID_OBJECTMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectModify ) );
	this->Connect( ID_RUNMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMSetup ) );
	this->Connect( ID_2D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM2DMenu ) );
	this->Connect( ID_3D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM3DMenu ) );
	this->Connect( ID_DRILLING, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMDrilling ) );
	this->Connect( ID_MULTIAXIS, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMMultiAxisMenu ) );
	this->Connect( ID_SIMULATE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessSimulate ) );
	this->Connect( ID_TOOLPATHEXPORT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessExport ) );
	this->Connect( ID_MANAGETOOLS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageTools ) );
	this->Connect( ID_MANAGEPOSTPROCESS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManagePostProcesses ) );
	this->Connect( ID_MANAGEMACHINES, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageMachines ) );
	this->Connect( ID_TOOLMEASURE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMToolsMeasure ) );
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
	this->Disconnect( ID_OBJECTFLIPNORMALS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectFlipNormals ) );
	this->Disconnect( ID_OBJECTMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnObjectModify ) );
	this->Disconnect( ID_RUNMODIFY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMSetup ) );
	this->Disconnect( ID_2D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM2DMenu ) );
	this->Disconnect( ID_3D, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAM3DMenu ) );
	this->Disconnect( ID_DRILLING, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMDrilling ) );
	this->Disconnect( ID_MULTIAXIS, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMMultiAxisMenu ) );
	this->Disconnect( ID_SIMULATE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessSimulate ) );
	this->Disconnect( ID_TOOLPATHEXPORT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMPostProcessExport ) );
	this->Disconnect( ID_MANAGETOOLS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageTools ) );
	this->Disconnect( ID_MANAGEPOSTPROCESS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManagePostProcesses ) );
	this->Disconnect( ID_MANAGEMACHINES, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMManageMachines ) );
	this->Disconnect( ID_TOOLMEASURE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler( GUIFrameMain::OnCAMToolsMeasure ) );
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
	
	m_staticTextUnitX = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	sbSizerSize->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText38 = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	sbSizerSize->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeY = new wxTextCtrl( sbSizerSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	sbSizerSize->Add( m_textCtrlSizeY, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	sbSizerSize->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText39 = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	sbSizerSize->Add( m_staticText39, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeZ = new wxTextCtrl( sbSizerSize->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	sbSizerSize->Add( m_textCtrlSizeZ, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( sbSizerSize->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	m_staticTextUnitX2 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX2->Wrap( -1 );
	fgSizer91->Add( m_staticTextUnitX2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button19 = new wxButton( sbSizer101->GetStaticBox(), ID_SCALEUNITX, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer91->Add( m_button19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText46 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("Y ="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer91->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitY = new wxTextCtrl( sbSizer101->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer91->Add( m_textCtrlScaleUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY2 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY2->Wrap( -1 );
	fgSizer91->Add( m_staticTextUnitY2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button21 = new wxButton( sbSizer101->GetStaticBox(), ID_SCALEUNITY, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer91->Add( m_button21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText52 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("Z ="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	fgSizer91->Add( m_staticText52, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitZ = new wxTextCtrl( sbSizer101->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer91->Add( m_textCtrlScaleUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ2 = new wxStaticText( sbSizer101->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ2->Wrap( -1 );
	fgSizer91->Add( m_staticTextUnitZ2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button23 = new wxButton( sbSizer101->GetStaticBox(), ID_SCALEUNITZ, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer91->Add( m_button23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	m_button20 = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENTX, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText48 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer6->Add( m_staticText48, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlScalePercentY = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercentY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText55 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	fgSizer6->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button22 = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENTY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText54 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	fgSizer6->Add( m_staticText54, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlScalePercentZ = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercentZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText43 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	fgSizer6->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button24 = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENTZ, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText68 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Proportional:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText68->Wrap( -1 );
	fgSizer6->Add( m_staticText68, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercent = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer6->Add( m_textCtrlScalePercent, 0, wxALL, 5 );
	
	m_staticText49 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer6->Add( m_staticText49, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button15 = new wxButton( sbSizer4->GetStaticBox(), ID_SCALEPERCENT, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer4->Add( fgSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer24->Add( sbSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer29->Add( bSizer24, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelScale->SetSizer( bSizer29 );
	m_panelScale->Layout();
	bSizer29->Fit( m_panelScale );
	m_notebook->AddPage( m_panelScale, _("Scale"), true );
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
	
	m_staticTextUnitMove = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
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
	m_notebook->AddPage( m_panelMove, _("Move"), false );
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
	
	m_staticTextUnitAngle = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, _("deg"), wxDefaultPosition, wxDefaultSize, 0 );
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
	m_button19->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_button20->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button24->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
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
	m_button19->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_button23->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnSetFactors ), NULL, this );
	m_button20->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button24->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
	m_button15->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnTransform ), NULL, this );
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
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
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
	
	m_textCtrlAxisX = new wxTextCtrl( sbSizerCoordinates->GetStaticBox(), wxID_ANY, _("automatic"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerCoordinates->Add( m_textCtrlAxisX, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonAxisY = new wxButton( sbSizerCoordinates->GetStaticBox(), ID_SELECTAXISY, _("Select Y..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCoordinates->Add( m_buttonAxisY, 0, wxALL, 5 );
	
	m_textCtrlAxisY = new wxTextCtrl( sbSizerCoordinates->GetStaticBox(), wxID_ANY, _("automatic"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizerCoordinates->Add( m_textCtrlAxisY, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonAxisZ = new wxButton( sbSizerCoordinates->GetStaticBox(), ID_SELECTAXISZ, _("Select Z..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCoordinates->Add( m_buttonAxisZ, 0, wxALL, 5 );
	
	m_textCtrlAxisZ = new wxTextCtrl( sbSizerCoordinates->GetStaticBox(), wxID_ANY, _("automatic"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
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
	
	m_staticTextUnitBoxX = new wxStaticText( m_panelStockBox, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitBoxX->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextUnitBoxX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBoxY = new wxStaticText( m_panelStockBox, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoxY->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextBoxY, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBoxY = new wxTextCtrl( m_panelStockBox, ID_SETSIZEY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerStockBox->Add( m_textCtrlBoxY, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitBoxY = new wxStaticText( m_panelStockBox, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitBoxY->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextUnitBoxY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBoxZ = new wxStaticText( m_panelStockBox, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBoxZ->Wrap( -1 );
	fgSizerStockBox->Add( m_staticTextBoxZ, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBoxZ = new wxTextCtrl( m_panelStockBox, ID_SETSIZEZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerStockBox->Add( m_textCtrlBoxZ, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitBoxZ = new wxStaticText( m_panelStockBox, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	bSizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
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
	sbSizerGeometry->Add( m_buttonSelectGeometry, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerScrolled->Add( sbSizerGeometry, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerTool;
	sbSizerTool = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Tool") ), wxVERTICAL );
	
	wxArrayString m_choiceToolChoices;
	m_choiceTool = new wxChoice( sbSizerTool->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceToolChoices, 0 );
	m_choiceTool->SetSelection( 0 );
	sbSizerTool->Add( m_choiceTool, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonToolSelect = new wxButton( sbSizerTool->GetStaticBox(), wxID_ANY, _("Select ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTool->Add( m_buttonToolSelect, 0, wxALL, 5 );
	
	
	bSizerScrolled->Add( sbSizerTool, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerSpeeds;
	sbSizerSpeeds = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Feeds - Speeds") ), wxVERTICAL );
	
	
	bSizerScrolled->Add( sbSizerSpeeds, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerMargin;
	sbSizerMargin = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Margin:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerMargin;
	fgSizerMargin = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerMargin->SetFlexibleDirection( wxBOTH );
	fgSizerMargin->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSide = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Side:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSide->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextSide, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMarginSide = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_MARGINSIDE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMargin->Add( m_textCtrlMarginSide, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitMarginSide = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMarginSide->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextUnitMarginSide, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBelow = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Below:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBelow->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlMarginBelow = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_MARGINBELOW, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMargin->Add( m_textCtrlMarginBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitMarginBelow = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMarginBelow->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextUnitMarginBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFreeHeight = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Clearance Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFreeHeight->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFreeHeight = new wxTextCtrl( sbSizerMargin->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMargin->Add( m_textCtrlFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitFreeHeight = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFreeHeight->Wrap( -1 );
	fgSizerMargin->Add( m_staticTextUnitFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerMargin->Add( fgSizerMargin, 1, wxEXPAND, 5 );
	
	
	bSizerScrolled->Add( sbSizerMargin, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerType;
	sbSizerType = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, _("Generator Type:") ), wxVERTICAL );
	
	m_choicebookGenerator = new wxChoicebook( sbSizerType->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
	sbSizerType->Add( m_choicebookGenerator, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizerScrolled->Add( sbSizerType, 1, wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( m_scrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizerScrolled->Add( m_textCtrlInfo, 0, wxALL|wxEXPAND, 5 );
	
	
	m_scrolledWindow->SetSizer( bSizerScrolled );
	m_scrolledWindow->Layout();
	bSizerScrolled->Fit( m_scrolledWindow );
	bSizerMain->Add( m_scrolledWindow, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolpathGenerator::OnXClose ) );
	m_buttonSelectGeometry->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectArea ), NULL, this );
	m_choiceTool->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectTool ), NULL, this );
	m_textCtrlMarginSide->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlMarginBelow->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_choicebookGenerator->Connect( wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED, wxChoicebookEventHandler( GUIToolpathGenerator::OnPageChanged ), NULL, this );
}

GUIToolpathGenerator::~GUIToolpathGenerator()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolpathGenerator::OnXClose ) );
	m_buttonSelectGeometry->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectArea ), NULL, this );
	m_choiceTool->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectTool ), NULL, this );
	m_textCtrlMarginSide->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlMarginBelow->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_choicebookGenerator->Disconnect( wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED, wxChoicebookEventHandler( GUIToolpathGenerator::OnPageChanged ), NULL, this );
	
}

GUIAnimation::GUIAnimation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTime;
	bSizerTime = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTime = new wxStaticText( this, wxID_ANY, _("Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTime->Wrap( -1 );
	bSizerTime->Add( m_staticTextTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_READONLY|wxTE_RIGHT );
	bSizerTime->Add( m_textCtrlTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextSlash = new wxStaticText( this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSlash->Wrap( -1 );
	bSizerTime->Add( m_staticTextSlash, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	bSizerTime->Add( m_textCtrlMaxTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer->Add( bSizerTime, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderTime = new wxSlider( this, wxID_ANY, 0, 0, 2000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer->Add( m_sliderTime, 0, wxALL|wxEXPAND, 5 );
	
	m_checkBoxSimulateWorkpiece = new wxCheckBox( this, wxID_ANY, _("Simulate workpiece"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxSimulateWorkpiece->SetValue(true); 
	bSizer->Add( m_checkBoxSimulateWorkpiece, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_bpButtonFirst = new wxBitmapButton( this, wxID_ANY, wxBitmap( first_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonFirst->SetToolTip( _("First") );
	
	bSizerButtons->Add( m_bpButtonFirst, 0, wxALL, 5 );
	
	m_bpButtonPrev = new wxBitmapButton( this, wxID_ANY, wxBitmap( prev_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPrev->SetToolTip( _("Step back") );
	
	bSizerButtons->Add( m_bpButtonPrev, 0, wxALL, 5 );
	
	m_bpButtonPlayStop = new wxBitmapButton( this, wxID_ANY, wxBitmap( play_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPlayStop->SetToolTip( _("Play / Stop") );
	
	bSizerButtons->Add( m_bpButtonPlayStop, 0, wxALL, 5 );
	
	m_bpButtonNext = new wxBitmapButton( this, wxID_ANY, wxBitmap( next_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonNext->SetToolTip( _("Step forward") );
	
	bSizerButtons->Add( m_bpButtonNext, 0, wxALL, 5 );
	
	m_bpButtonLast = new wxBitmapButton( this, wxID_ANY, wxBitmap( last_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonLast->SetToolTip( _("Last") );
	
	bSizerButtons->Add( m_bpButtonLast, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIAnimation::OnXClose ) );
	m_textCtrlTime->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIAnimation::OnChangeTime ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_checkBoxSimulateWorkpiece->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIAnimation::OnChangeSimulation ), NULL, this );
	m_bpButtonFirst->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnFirst ), NULL, this );
	m_bpButtonPrev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPrev ), NULL, this );
	m_bpButtonPlayStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPlayStop ), NULL, this );
	m_bpButtonNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnNext ), NULL, this );
	m_bpButtonLast->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnLast ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnClose ), NULL, this );
}

GUIAnimation::~GUIAnimation()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIAnimation::OnXClose ) );
	m_textCtrlTime->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIAnimation::OnChangeTime ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_sliderTime->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIAnimation::OnScroll ), NULL, this );
	m_checkBoxSimulateWorkpiece->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIAnimation::OnChangeSimulation ), NULL, this );
	m_bpButtonFirst->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnFirst ), NULL, this );
	m_bpButtonPrev->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPrev ), NULL, this );
	m_bpButtonPlayStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPlayStop ), NULL, this );
	m_bpButtonNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnNext ), NULL, this );
	m_bpButtonLast->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnLast ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnClose ), NULL, this );
	
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
	
	m_buttonOpen = new wxButton( this, wxID_ANY, _("Open"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerOpen->Add( m_buttonOpen, 0, wxALL, 5 );
	
	
	bSizer->Add( bSizerOpen, 0, wxEXPAND, 5 );
	
	m_propertyGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer->Add( m_propertyGrid, 1, wxALL|wxEXPAND, 5 );
	
	m_filePickerExport = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer->Add( m_filePickerExport, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonExport = new wxButton( this, wxID_ANY, _("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonExport, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
}

GUIPostProcess::~GUIPostProcess()
{
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
	
	m_dirPickerProjectDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerProjectDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextObjectDirectory = new wxStaticText( this, wxID_ANY, _("Objects are imported from:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextObjectDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextObjectDirectory, 0, wxALL, 5 );
	
	m_dirPickerObjectDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerObjectDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextToolpathDirectory = new wxStaticText( this, wxID_ANY, _("Output directory for exported NC toolpaths:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolpathDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextToolpathDirectory, 0, wxALL, 5 );
	
	m_dirPickerToolpathDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerToolpathDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextToolboxDirectory = new wxStaticText( this, wxID_ANY, _("Tool libraries:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolboxDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextToolboxDirectory, 0, wxALL, 5 );
	
	m_dirPickerToolboxDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerToolboxDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextPostProcessorDirectory = new wxStaticText( this, wxID_ANY, _("Post-Processors:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPostProcessorDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextPostProcessorDirectory, 0, wxALL, 5 );
	
	m_dirPickerPostProcessorDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	bSizer->Add( m_dirPickerPostProcessorDirectory, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextMachineDirectory = new wxStaticText( this, wxID_ANY, _("Machine models:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMachineDirectory->Wrap( -1 );
	bSizer->Add( m_staticTextMachineDirectory, 0, wxALL, 5 );
	
	m_dirPickerMachineDirectory = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
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
	
	m_treeListCtrl = new wxTreeListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_CHECKBOX|wxTL_DEFAULT_STYLE|wxTL_USER_3STATE );
	m_treeListCtrl->AppendColumn( _("Name"), wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_treeListCtrl->AppendColumn( _("Type"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_treeListCtrl->AppendColumn( _("Diameter"), wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_treeListCtrl->AppendColumn( _("Number"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );
	
	bSizer->Add( m_treeListCtrl, 1, wxALL|wxEXPAND, 5 );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelTool = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerPanelTool;
	bSizerPanelTool = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxToolTypeChoices[] = { _("Flat nose (cylindric)"), _("Ball nose (spheric)"), _("Bull nose (mixing ball and flat)"), _("Camfer (triangle)") };
	int m_radioBoxToolTypeNChoices = sizeof( m_radioBoxToolTypeChoices ) / sizeof( wxString );
	m_radioBoxToolType = new wxRadioBox( m_panelTool, wxID_ANY, _("Type"), wxDefaultPosition, wxDefaultSize, m_radioBoxToolTypeNChoices, m_radioBoxToolTypeChoices, 2, wxRA_SPECIFY_ROWS );
	m_radioBoxToolType->SetSelection( 0 );
	bSizerPanelTool->Add( m_radioBoxToolType, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxFlexGridSizer* fgSizerPanelTool;
	fgSizerPanelTool = new wxFlexGridSizer( 5, 3, 0, 0 );
	fgSizerPanelTool->SetFlexibleDirection( wxBOTH );
	fgSizerPanelTool->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( m_panelTool, wxID_ANY, _("Shaft diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftDiameter = new wxTextCtrl( m_panelTool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftDiameter->SetToolTip( _("Diameter of the part that disappears inside the chuck.") );
	
	fgSizerPanelTool->Add( m_textCtrlShaftDiameter, 0, wxALL, 5 );
	
	m_staticTextUnitShaftDiameter = new wxStaticText( m_panelTool, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftDiameter->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticTextUnitShaftDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText10 = new wxStaticText( m_panelTool, wxID_ANY, _("Shaft length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftLength = new wxTextCtrl( m_panelTool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftLength->SetToolTip( _("This is the length of the that disappears inside the chuck.") );
	
	fgSizerPanelTool->Add( m_textCtrlShaftLength, 0, wxALL, 5 );
	
	m_staticTextUnitShaftLength = new wxStaticText( m_panelTool, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftLength->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticTextUnitShaftLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( m_panelTool, wxID_ANY, _("Maximum speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( m_panelTool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMaxSpeed->SetToolTip( _("Max. speed: Look at label on box you got the tools shipped in.") );
	
	fgSizerPanelTool->Add( m_textCtrlMaxSpeed, 0, wxALL, 5 );
	
	m_staticTextUnitMaxSpeed = new wxStaticText( m_panelTool, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMaxSpeed->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticTextUnitMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( m_panelTool, wxID_ANY, _("Feed coefficient:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFeedCoefficient = new wxTextCtrl( m_panelTool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlFeedCoefficient->SetToolTip( _("Feed per tooth: How deep can a tooth cut per revolution. Usually in the range of 0.02 mm to 0.05 mm.") );
	
	fgSizerPanelTool->Add( m_textCtrlFeedCoefficient, 0, wxALL, 5 );
	
	m_staticTextUnitFeedCoefficient = new wxStaticText( m_panelTool, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedCoefficient->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticTextUnitFeedCoefficient, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFlutes = new wxStaticText( m_panelTool, wxID_ANY, _("Number of flutes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFlutes->Wrap( -1 );
	fgSizerPanelTool->Add( m_staticTextFlutes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlNrOfTeeth = new wxTextCtrl( m_panelTool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlNrOfTeeth->SetToolTip( _("Number of teeth around the cutter.") );
	
	fgSizerPanelTool->Add( m_textCtrlNrOfTeeth, 0, wxALL, 5 );
	
	
	fgSizerPanelTool->Add( 0, 0, 1, 0, 5 );
	
	
	bSizerPanelTool->Add( fgSizerPanelTool, 0, 0, 5 );
	
	wxFlexGridSizer* fgSizerPanelTool2;
	fgSizerPanelTool2 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizerPanelTool2->AddGrowableCol( 1 );
	fgSizerPanelTool2->SetFlexibleDirection( wxBOTH );
	fgSizerPanelTool2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText26 = new wxStaticText( m_panelTool, wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizerPanelTool2->Add( m_staticText26, 0, wxALL, 5 );
	
	m_textCtrlComment = new wxTextCtrl( m_panelTool, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_ENTER|wxTE_WORDWRAP );
	fgSizerPanelTool2->Add( m_textCtrlComment, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizerPanelTool->Add( fgSizerPanelTool2, 0, wxEXPAND, 5 );
	
	m_paneltool=new PanelTool(this);
	bSizerPanelTool->Add( m_paneltool, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panelTool->SetSizer( bSizerPanelTool );
	m_panelTool->Layout();
	bSizerPanelTool->Fit( m_panelTool );
	m_notebook->AddPage( m_panelTool, _("Tool"), true );
	m_panelShaft = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonShapeNew = new wxButton( m_panelShaft, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonShapeNew, 0, wxALL, 5 );
	
	m_buttonShapeUpdate = new wxButton( m_panelShaft, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonShapeUpdate, 0, wxALL, 5 );
	
	m_buttonShapeDelete = new wxButton( m_panelShaft, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonShapeDelete, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 0, 0, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Linear or bend line"), _("Corner: first diameter change, then height change"), _("Corner: first height change, then diameter change"), _("Sphere: radius at upper limit, calculate height"), _("Sphere: radius at lower limit, calculate height") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( m_panelShaft, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	bSizer3->Add( m_choiceType, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 4, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( m_panelShaft, wxID_ANY, _("Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDiameter = new wxTextCtrl( m_panelShaft, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlDiameter->SetToolTip( _("Diameter of the tool at the end of this segment.") );
	
	fgSizer2->Add( m_textCtrlDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitDiameter = new wxStaticText( m_panelShaft, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( m_panelShaft, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHeight = new wxTextCtrl( m_panelShaft, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlHeight->SetToolTip( _("Height of this segment.") );
	
	fgSizer2->Add( m_textCtrlHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHeight = new wxStaticText( m_panelShaft, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHeight->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( m_panelShaft, wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRadius = new wxTextCtrl( m_panelShaft, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlRadius->SetToolTip( _("Radius of curvature:\nPositive radius = convex surface = bulged to the outside.\nNegative radius = concave surface = bulged to the inside.\nRadius of 0 = straight line. ") );
	
	fgSizer2->Add( m_textCtrlRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitRadius = new wxStaticText( m_panelShaft, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRadius->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitRadius, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, 0, 5 );
	
	m_checkBoxCutting = new wxCheckBox( m_panelShaft, wxID_ANY, _("surface is cutting"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_checkBoxCutting, 0, wxALL, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, 0, 5 );
	
	
	bSizer3->Add( fgSizer2, 0, 0, 5 );
	
	
	bSizer2->Add( bSizer3, 0, 0, 5 );
	
	m_listCtrl = new wxListCtrl( m_panelShaft, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer2->Add( m_listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer65->Add( bSizer2, 1, wxEXPAND, 5 );
	
	m_canvasshaft = new CanvasTool(this);
	bSizer65->Add( m_canvasshaft, 0, wxALL, 5 );
	
	
	m_panelShaft->SetSizer( bSizer65 );
	m_panelShaft->Layout();
	bSizer65->Fit( m_panelShaft );
	m_notebook->AddPage( m_panelShaft, _("Shaft"), false );
	m_panelHolder = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxVERTICAL );
	
	m_canvasholder = new CanvasTool(this);
	bSizer63->Add( m_canvasholder, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelHolder->SetSizer( bSizer63 );
	m_panelHolder->Layout();
	bSizer63->Fit( m_panelHolder );
	m_notebook->AddPage( m_panelHolder, _("Holder"), false );
	m_panelFeedsSpeeds = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerParameter;
	sbSizerParameter = new wxStaticBoxSizer( new wxStaticBox( m_panelFeedsSpeeds, wxID_ANY, _("Parameter") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerParameter;
	fgSizerParameter = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizerParameter->SetFlexibleDirection( wxBOTH );
	fgSizerParameter->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextDiameter = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDiameter->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlDiameter1 = new wxTextCtrl( sbSizerParameter->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerParameter->Add( m_textCtrlDiameter1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitDiameter1 = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter1->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextUnitDiameter1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextTipDiameter = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("Tip diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipDiameter->Wrap( -1 );
	m_staticTextTipDiameter->Enable( false );
	
	fgSizerParameter->Add( m_staticTextTipDiameter, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTipDiameter = new wxTextCtrl( sbSizerParameter->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlTipDiameter->Enable( false );
	
	fgSizerParameter->Add( m_textCtrlTipDiameter, 0, wxALL, 5 );
	
	m_staticTextUnitTipDiameter = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitTipDiameter->Wrap( -1 );
	m_staticTextUnitTipDiameter->Enable( false );
	
	fgSizerParameter->Add( m_staticTextUnitTipDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShaftDiameter = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("Shaft Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShaftDiameter->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextShaftDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShaftDiameter1 = new wxTextCtrl( sbSizerParameter->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerParameter->Add( m_textCtrlShaftDiameter1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitShaftDiameter1 = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftDiameter1->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextUnitShaftDiameter1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline1 = new wxStaticLine( sbSizerParameter->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizerParameter->Add( m_staticline1, 0, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_staticline2 = new wxStaticLine( sbSizerParameter->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizerParameter->Add( m_staticline2, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_staticline3 = new wxStaticLine( sbSizerParameter->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizerParameter->Add( m_staticline3, 0, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_staticTextLengthOutside = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("Length outside chuck:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLengthOutside->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextLengthOutside, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlLengthOutside = new wxTextCtrl( sbSizerParameter->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerParameter->Add( m_textCtrlLengthOutside, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitLengthOutside = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitLengthOutside->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextUnitLengthOutside, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextLengthCutting = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("Length cutting:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLengthCutting->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextLengthCutting, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlLengthCutting = new wxTextCtrl( sbSizerParameter->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerParameter->Add( m_textCtrlLengthCutting, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitLengthCutting = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitLengthCutting->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextUnitLengthCutting, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextToolLength = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("Total tool length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolLength->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextToolLength, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlToolLength = new wxTextCtrl( sbSizerParameter->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerParameter->Add( m_textCtrlToolLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitToolLength = new wxStaticText( sbSizerParameter->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitToolLength->Wrap( -1 );
	fgSizerParameter->Add( m_staticTextUnitToolLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerParameter->Add( fgSizerParameter, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerMain->Add( sbSizerParameter, 1, wxEXPAND, 5 );
	
	
	bSizer66->Add( bSizerMain, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelFeedsSpeeds->SetSizer( bSizer66 );
	m_panelFeedsSpeeds->Layout();
	bSizer66->Fit( m_panelFeedsSpeeds );
	m_notebook->AddPage( m_panelFeedsSpeeds, _("Feeds && Speeds"), false );
	
	bSizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolbox::OnXClose ) );
	m_treeListCtrl->Connect( wxEVT_TREELIST_ITEM_CHECKED, wxTreeListEventHandler( GUIToolbox::OnItemChecked ), NULL, this );
	m_treeListCtrl->Connect( wxEVT_TREELIST_ITEM_CONTEXT_MENU, wxTreeListEventHandler( GUIToolbox::OnItemContextMenu ), NULL, this );
	m_treeListCtrl->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_textCtrlShaftDiameter->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShaftLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlMaxSpeed->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedCoefficient->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlNrOfTeeth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlComment->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_buttonShapeNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeNew ), NULL, this );
	m_buttonShapeUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeUpdate ), NULL, this );
	m_buttonShapeDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeDelete ), NULL, this );
	m_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIToolbox::OnShapeSelect ), NULL, this );
}

GUIToolbox::~GUIToolbox()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolbox::OnXClose ) );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_ITEM_CHECKED, wxTreeListEventHandler( GUIToolbox::OnItemChecked ), NULL, this );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_ITEM_CONTEXT_MENU, wxTreeListEventHandler( GUIToolbox::OnItemContextMenu ), NULL, this );
	m_treeListCtrl->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( GUIToolbox::OnSelectionChanged ), NULL, this );
	m_textCtrlShaftDiameter->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlShaftLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlMaxSpeed->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlFeedCoefficient->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlNrOfTeeth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_textCtrlComment->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnEnter ), NULL, this );
	m_buttonShapeNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeNew ), NULL, this );
	m_buttonShapeUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeUpdate ), NULL, this );
	m_buttonShapeDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeDelete ), NULL, this );
	m_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIToolbox::OnShapeSelect ), NULL, this );
	
}

GUIMachineDebugger::GUIMachineDebugger( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItemLoad;
	m_menuItemLoad = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Load Machine Description") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemLoad );
	
	wxMenuItem* m_menuItemSave;
	m_menuItemSave = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Save Machine Description") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemSave );
	
	m_menuMachine->AppendSeparator();
	
	wxMenuItem* m_menuItemMachineReevaluateScript;
	m_menuItemMachineReevaluateScript = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Evaluate Script") ) + wxT('\t') + wxT("CTRL+E"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemMachineReevaluateScript );
	
	wxMenuItem* m_menuItemShowControl;
	m_menuItemShowControl = new wxMenuItem( m_menuMachine, ID_CONTROLLERSHOW, wxString( _("&Show Controller") ) + wxT('\t') + wxT("CTRL+SHIFT+C"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemShowControl );
	
	m_menuMachine->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuMachine, wxID_CLOSE, wxString( _("Close Window") ) + wxT('\t') + wxT("CTRL+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuMachine, _("&Machine") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemEnable3D;
	m_menuItemEnable3D = new wxMenuItem( m_menuView, ID_VIEWSTEREO3D, wxString( _("Enable &3D") ) + wxT('\t') + wxT("CTRL+3"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemEnable3D );
	
	m_menubar->Append( m_menuView, _("&View") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
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
	this->Connect( m_menuItemLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnMachineLoad ) );
	this->Connect( m_menuItemSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnMachineSave ) );
	this->Connect( m_menuItemMachineReevaluateScript->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnScriptEvaluate ) );
	this->Connect( m_menuItemShowControl->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnShowController ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnClose ) );
	this->Connect( m_menuItemEnable3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnChangeStereo3D ) );
	m_buttonRestart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnScriptEvaluate ), NULL, this );
}

GUIMachineDebugger::~GUIMachineDebugger()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIMachineDebugger::OnXClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnMachineLoad ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnMachineSave ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnScriptEvaluate ) );
	this->Disconnect( ID_CONTROLLERSHOW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnShowController ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnClose ) );
	this->Disconnect( ID_VIEWSTEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMachineDebugger::OnChangeStereo3D ) );
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
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Main Axis") ), wxVERTICAL );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText69 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText69->Wrap( -1 );
	bSizer42->Add( m_staticText69, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderX = new wxSlider( sbSizer12->GetStaticBox(), ID_AXISX, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer42->Add( m_sliderX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer41->Add( bSizer42, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText70 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	bSizer43->Add( m_staticText70, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderY = new wxSlider( sbSizer12->GetStaticBox(), ID_AXISY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer43->Add( m_sliderY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer41->Add( bSizer43, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText71 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	bSizer44->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderZ = new wxSlider( sbSizer12->GetStaticBox(), ID_AXISZ, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer44->Add( m_sliderZ, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer41->Add( bSizer44, 0, wxEXPAND, 5 );
	
	
	sbSizer12->Add( bSizer41, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText73 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText73->Wrap( -1 );
	fgSizer10->Add( m_staticText73, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlX = new wxTextCtrl( sbSizer12->GetStaticBox(), ID_TEXTX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer10->Add( m_textCtrlX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	fgSizer10->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText75 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText75->Wrap( -1 );
	fgSizer10->Add( m_staticText75, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlY = new wxTextCtrl( sbSizer12->GetStaticBox(), ID_TEXTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer10->Add( m_textCtrlY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	fgSizer10->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText77 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText77->Wrap( -1 );
	fgSizer10->Add( m_staticText77, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlZ = new wxTextCtrl( sbSizer12->GetStaticBox(), ID_TEXTZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer10->Add( m_textCtrlZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	fgSizer10->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer12->Add( fgSizer10, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer38->Add( sbSizer12, 0, wxEXPAND, 5 );
	
	
	bSizer38->Add( 0, 0, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Main Angles") ), wxVERTICAL );
	
	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText78 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("A:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText78->Wrap( -1 );
	bSizer46->Add( m_staticText78, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderA = new wxSlider( sbSizer14->GetStaticBox(), ID_AXISA, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer46->Add( m_sliderA, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer45->Add( bSizer46, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText79 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText79->Wrap( -1 );
	bSizer47->Add( m_staticText79, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderB = new wxSlider( sbSizer14->GetStaticBox(), ID_AXISB, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer47->Add( m_sliderB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer45->Add( bSizer47, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText80 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("C:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText80->Wrap( -1 );
	bSizer48->Add( m_staticText80, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderC = new wxSlider( sbSizer14->GetStaticBox(), ID_AXISC, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer48->Add( m_sliderC, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer45->Add( bSizer48, 0, wxEXPAND, 5 );
	
	
	sbSizer14->Add( bSizer45, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer101;
	fgSizer101 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer101->SetFlexibleDirection( wxBOTH );
	fgSizer101->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText731 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("A:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText731->Wrap( -1 );
	fgSizer101->Add( m_staticText731, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlA = new wxTextCtrl( sbSizer14->GetStaticBox(), ID_TEXTA, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer101->Add( m_textCtrlA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitA = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("deg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitA->Wrap( -1 );
	fgSizer101->Add( m_staticTextUnitA, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText751 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText751->Wrap( -1 );
	fgSizer101->Add( m_staticText751, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlB = new wxTextCtrl( sbSizer14->GetStaticBox(), ID_TEXTB, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer101->Add( m_textCtrlB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitB = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("deg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitB->Wrap( -1 );
	fgSizer101->Add( m_staticTextUnitB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText771 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("C:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText771->Wrap( -1 );
	fgSizer101->Add( m_staticText771, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlC = new wxTextCtrl( sbSizer14->GetStaticBox(), ID_TEXTC, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer101->Add( m_textCtrlC, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitC = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, _("deg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitC->Wrap( -1 );
	fgSizer101->Add( m_staticTextUnitC, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer14->Add( fgSizer101, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer38->Add( sbSizer14, 0, wxEXPAND, 5 );
	
	
	bSizer38->Add( 0, 0, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Additional Axis") ), wxVERTICAL );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText81 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("U:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	bSizer50->Add( m_staticText81, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderU = new wxSlider( sbSizer13->GetStaticBox(), ID_AXISU, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer50->Add( m_sliderU, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer49->Add( bSizer50, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText82 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("V:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	bSizer51->Add( m_staticText82, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderV = new wxSlider( sbSizer13->GetStaticBox(), ID_AXISV, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer51->Add( m_sliderV, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer49->Add( bSizer51, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText83 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("W:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText83->Wrap( -1 );
	bSizer52->Add( m_staticText83, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderW = new wxSlider( sbSizer13->GetStaticBox(), ID_AXISW, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer52->Add( m_sliderW, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer49->Add( bSizer52, 0, wxEXPAND, 5 );
	
	
	sbSizer13->Add( bSizer49, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer102;
	fgSizer102 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer102->SetFlexibleDirection( wxBOTH );
	fgSizer102->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText732 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("U:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText732->Wrap( -1 );
	fgSizer102->Add( m_staticText732, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlU = new wxTextCtrl( sbSizer13->GetStaticBox(), ID_TEXTU, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer102->Add( m_textCtrlU, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitU = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitU->Wrap( -1 );
	fgSizer102->Add( m_staticTextUnitU, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText752 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("V:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText752->Wrap( -1 );
	fgSizer102->Add( m_staticText752, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlV = new wxTextCtrl( sbSizer13->GetStaticBox(), ID_TEXTV, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer102->Add( m_textCtrlV, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitV = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitV->Wrap( -1 );
	fgSizer102->Add( m_staticTextUnitV, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText772 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("W:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText772->Wrap( -1 );
	fgSizer102->Add( m_staticText772, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlW = new wxTextCtrl( sbSizer13->GetStaticBox(), ID_TEXTW, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer102->Add( m_textCtrlW, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitW = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitW->Wrap( -1 );
	fgSizer102->Add( m_staticTextUnitW, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer13->Add( fgSizer102, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer38->Add( sbSizer13, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer38 );
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
	m_sliderA->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderB->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderC->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlA->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlB->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlC->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_sliderU->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderV->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderW->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlU->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlV->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlW->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
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
	m_sliderA->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderA->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderB->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderB->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderC->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderC->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlA->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlB->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlC->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_sliderU->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderU->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderV->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderV->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_sliderW->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIMachineControl::OnZero ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIMachineControl::OnScroll ), NULL, this );
	m_sliderW->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIMachineControl::OnTrack ), NULL, this );
	m_textCtrlU->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlV->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	m_textCtrlW->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIMachineControl::OnTextChanged ), NULL, this );
	
}

GUISetupUnits::GUISetupUnits( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	
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

GUIDialogAbout::GUIDialogAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl = new wxTextCtrl( this, wxID_ANY, _("Generic CAM  Copyright (C) 2010 - 2017 Tobias Schaefer\n\nFrench translation & additional debugging: Jacques-Louis Tartarin\nItalian Translation: Sandro Dalle Nogare\n\nLicence for Generic CAM:\nGNU General Public License version 3.0 (GPLv3)\n\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\n\nYou should have received a copy of the GNU General Public License along with this program.\nIf not, see <http://www.gnu.org/licenses/>."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	bSizer->Add( m_textCtrl, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonClose = new wxButton( this, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

GUIDialogAbout::~GUIDialogAbout()
{
}

StartupText::StartupText( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_richText = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer->Add( m_richText, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
}

StartupText::~StartupText()
{
}
