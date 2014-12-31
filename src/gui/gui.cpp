///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

#include "../icon/first.xpm"
#include "../icon/last.xpm"
#include "../icon/machine.xpm"
#include "../icon/material.xpm"
#include "../icon/next.xpm"
#include "../icon/play.xpm"
#include "../icon/prev.xpm"
#include "../icon/redo.xpm"
#include "../icon/undo.xpm"

///////////////////////////////////////////////////////////////////////////

GUIMainFrame::GUIMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuProject = new wxMenu();
	wxMenuItem* m_menuItemProjectCreate;
	m_menuItemProjectCreate = new wxMenuItem( m_menuProject, wxID_NEW, wxString( _("&Create new project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItemProjectCreate );
	
	wxMenuItem* m_menuItemProjectLoad;
	m_menuItemProjectLoad = new wxMenuItem( m_menuProject, wxID_OPEN, wxString( _("&Load Project...") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItemProjectLoad );
	
	wxMenuItem* m_menuItemProjectSave;
	m_menuItemProjectSave = new wxMenuItem( m_menuProject, wxID_SAVE, wxString( _("&Save Project") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItemProjectSave );
	
	wxMenuItem* m_menuItemProjectSaveAs;
	m_menuItemProjectSaveAs = new wxMenuItem( m_menuProject, wxID_SAVEAS, wxString( _("Save Project &as...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuProject->Append( m_menuItemProjectSaveAs );
	
	wxMenuItem* m_separator4;
	m_separator4 = m_menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItemQuit;
	m_menuItemQuit = new wxMenuItem( m_menuProject, wxID_EXIT, wxString( _("&Quit") ) + wxT('\t') + wxT("CTRL+Q"), _("Exit the program"), wxITEM_NORMAL );
	m_menuProject->Append( m_menuItemQuit );
	
	m_menubar->Append( m_menuProject, _("&Project") );
	
	m_menuEdit = new wxMenu();
	wxMenuItem* m_menuItemUndo;
	m_menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("CTRL+Z"), _("Undo last command"), wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemUndo );
	
	wxMenuItem* m_menuItemRedo;
	m_menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( _("&Redo") ) + wxT('\t') + wxT("CTRL+Y"), _("Redo last undone command"), wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemRedo );
	
	m_menubar->Append( m_menuEdit, _("&Edit") );
	
	m_menuObject = new wxMenu();
	wxMenuItem* m_menuItemObjectLoad;
	m_menuItemObjectLoad = new wxMenuItem( m_menuObject, wxID_ANY, wxString( _("&Load Object File") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectLoad );
	
	wxMenuItem* m_menuItemObjectModify;
	m_menuItemObjectModify = new wxMenuItem( m_menuObject, wxID_ANY, wxString( _("&Modify Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectModify );
	
	m_menubar->Append( m_menuObject, _("&Object") );
	
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItemMachineLoad;
	m_menuItemMachineLoad = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Load Machine...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemMachineLoad );
	
	wxMenuItem* m_menuItemMachineReload;
	m_menuItemMachineReload = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("&Reload machine") ) + wxT('\t') + wxT("CTRL+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemMachineReload );
	
	m_menubar->Append( m_menuMachine, _("&Machine") );
	
	m_menuToolbox = new wxMenu();
	wxMenuItem* m_menuItemToolboxEdit;
	m_menuItemToolboxEdit = new wxMenuItem( m_menuToolbox, wxID_ANY, wxString( _("&Edit Toolbox") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxEdit );
	
	wxMenuItem* m_menuItemToolboxLoad;
	m_menuItemToolboxLoad = new wxMenuItem( m_menuToolbox, wxID_ANY, wxString( _("&Load Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxLoad );
	
	wxMenuItem* m_menuItemToolboxSave;
	m_menuItemToolboxSave = new wxMenuItem( m_menuToolbox, wxID_ANY, wxString( _("&Save Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxSave );
	
	m_menubar->Append( m_menuToolbox, _("&Toolbox") );
	
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItem44;
	m_menuItem44 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Organize Stock") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem44 );
	
	wxMenuItem* m_menuItem43;
	m_menuItem43 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Load Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem43 );
	
	wxMenuItem* m_menuItem42;
	m_menuItem42 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Save Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem42 );
	
	m_menubar->Append( m_menuStock, _("&Stock") );
	
	m_menuToolpath = new wxMenu();
	wxMenuItem* m_menuItem47;
	m_menuItem47 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Generate Toolpaths") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem47 );
	
	wxMenuItem* m_menuItem471;
	m_menuItem471 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("Recollect Toolpaths") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem471 );
	
	wxMenuItem* m_menuItem472;
	m_menuItem472 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("Clean Toolpaths") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem472 );
	
	wxMenuItem* m_menuItem48;
	m_menuItem48 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Flip Run") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem48 );
	
	wxMenuItem* m_separator7;
	m_separator7 = m_menuToolpath->AppendSeparator();
	
	wxMenuItem* m_menuItem491;
	m_menuItem491 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Prepare Machinebed") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem491 );
	
	wxMenuItem* m_separator5;
	m_separator5 = m_menuToolpath->AppendSeparator();
	
	wxMenuItem* m_menuItem16;
	m_menuItem16 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("L&oad G-Codes") ) + wxT('\t') + wxT("CTRL+G"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem16 );
	
	wxMenuItem* m_menuItem441;
	m_menuItem441 = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("&Save G-Codes") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItem441 );
	
	m_menubar->Append( m_menuToolpath, _("Tool&path") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem51;
	m_menuItem51 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( _("Change Language") ) , _("Change the programs language."), wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem51 );
	
	wxMenuItem* m_separator71;
	m_separator71 = m_menuSettings->AppendSeparator();
	
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menuSettings, wxID_SETUPCONTROLLER, wxString( _("Setup 6DOF &Controller") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem22;
	m_menuItem22 = new wxMenuItem( m_menuSettings, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem22 );
	
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	wxMenuItem* m_menuItem46;
	m_menuItem46 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( _("Show &Animation Control") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem46 );
	
	m_menubar->Append( m_menuSettings, _("S&ettings") );
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemTop;
	m_menuItemTop = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Top") ) + wxT('\t') + wxT("CTRL+8"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemTop );
	
	wxMenuItem* m_menuItemBottom;
	m_menuItemBottom = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Bottom") ) + wxT('\t') + wxT("CTRL+2"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemBottom );
	
	wxMenuItem* m_menuItemFront;
	m_menuItemFront = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Front") ) + wxT('\t') + wxT("CTRL+5"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemFront );
	
	wxMenuItem* m_menuItemBack;
	m_menuItemBack = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Back") ) + wxT('\t') + wxT("CTRL+0"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemBack );
	
	wxMenuItem* m_menuItemLeft;
	m_menuItemLeft = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Left") ) + wxT('\t') + wxT("CTRL+4"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemLeft );
	
	wxMenuItem* m_menuItemRight;
	m_menuItemRight = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("View from Right") ) + wxT('\t') + wxT("CTRL+6"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemRight );
	
	m_menubar->Append( m_menuView, _("&View") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItem49;
	m_menuItem49 = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( _("&About") ) + wxT('\t') + wxT("CTRL+A"), _("About the program"), wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItem49 );
	
	m_menubar->Append( m_menuHelp, _("&Help") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE );
	m_splitter->SetMinimumPaneSize( 100 );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIMainFrame::m_splitterOnIdle ), NULL, this );
	m_panel1 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	tree = new wxTreeCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS|wxTR_FULL_ROW_HIGHLIGHT|wxTR_HAS_BUTTONS|wxTR_HIDE_ROOT|wxTR_NO_LINES|wxTR_SINGLE );
	bSizer19->Add( tree, 1, wxALL|wxEXPAND, 5 );
	
	m_panel1->SetSizer( bSizer19 );
	m_panel1->Layout();
	bSizer19->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerMainCanvas;
	bSizerMainCanvas = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new MainCanvas(m_panel2);
	bSizerMainCanvas->Add( m_canvas, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel2->SetSizer( bSizerMainCanvas );
	m_panel2->Layout();
	bSizerMainCanvas->Fit( m_panel2 );
	m_splitter->SplitVertically( m_panel1, m_panel2, 144 );
	bSizer1->Add( m_splitter, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	m_toolBar->AddTool( wxID_UNDO, _("tool"), wxBitmap( undo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Undo"), _("Undo") );
	m_toolBar->AddTool( wxID_REDO, _("tool"), wxBitmap( redo_xpm ), wxNullBitmap, wxITEM_NORMAL, _("Redo"), _("Redo") );
	m_toolBar->AddSeparator();
	m_toolBar->AddTool( wxID_DISPLAYMACHINE, _("tool"), wxBitmap( machine_xpm ), wxNullBitmap, wxITEM_CHECK, _("Display machine"), _("Display machine") );
	m_toolBar->AddTool( wxID_DISPLAYMATERIAL, _("tool"), wxBitmap( material_xpm ), wxNullBitmap, wxITEM_CHECK, _("Display material"), _("Display material") );
	m_toolBar->Realize();
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItemProjectCreate->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnCreateProject ) );
	this->Connect( m_menuItemProjectLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadProject ) );
	this->Connect( m_menuItemProjectSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProject ) );
	this->Connect( m_menuItemProjectSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProjectAs ) );
	this->Connect( m_menuItemQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Connect( m_menuItemUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnUndo ) );
	this->Connect( m_menuItemRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnRedo ) );
	this->Connect( m_menuItemObjectLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadObject ) );
	this->Connect( m_menuItemObjectModify->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnModifyObject ) );
	this->Connect( m_menuItemMachineLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadMachine ) );
	this->Connect( m_menuItemMachineReload->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnReloadMachine ) );
	this->Connect( m_menuItemToolboxEdit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditToolbox ) );
	this->Connect( m_menuItemToolboxLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadToolbox ) );
	this->Connect( m_menuItemToolboxSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveToolbox ) );
	this->Connect( m_menuItem44->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditStock ) );
	this->Connect( m_menuItem47->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnGenerateToolpath ) );
	this->Connect( m_menuItem471->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnRecollectToolpath ) );
	this->Connect( m_menuItem472->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnCleanToolpath ) );
	this->Connect( m_menuItem48->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnFlipRun ) );
	this->Connect( m_menuItem491->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnPrepareMachinebed ) );
	this->Connect( m_menuItem16->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadGCodes ) );
	this->Connect( m_menuItem441->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveGCodes ) );
	this->Connect( m_menuItem51->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeLanguage ) );
	this->Connect( m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupController ) );
	this->Connect( m_menuItem22->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeStereo3D ) );
	this->Connect( m_menuItem23->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupUnits ) );
	this->Connect( m_menuItem46->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnShowAnimationControl ) );
	this->Connect( m_menuItem49->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
	tree->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnBeginLabelEdit ), NULL, this );
	tree->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnEndLabelEdit ), NULL, this );
	tree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIMainFrame::OnActivateRightClickMenu ), NULL, this );
	tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIMainFrame::OnSelectionChanged ), NULL, this );
	this->Connect( wxID_UNDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnUndo ) );
	this->Connect( wxID_REDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnRedo ) );
	this->Connect( wxID_DISPLAYMACHINE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnUpdateVisibility ) );
	this->Connect( wxID_DISPLAYMATERIAL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnUpdateVisibility ) );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnCreateProject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadProject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveProjectAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnUndo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnRedo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadObject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnModifyObject ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadMachine ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnReloadMachine ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveToolbox ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnEditStock ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnGenerateToolpath ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnRecollectToolpath ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnCleanToolpath ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnFlipRun ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnPrepareMachinebed ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnLoadGCodes ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSaveGCodes ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeLanguage ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupController ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupUnits ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnShowAnimationControl ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
	tree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnBeginLabelEdit ), NULL, this );
	tree->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIMainFrame::OnEndLabelEdit ), NULL, this );
	tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIMainFrame::OnActivateRightClickMenu ), NULL, this );
	tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIMainFrame::OnSelectionChanged ), NULL, this );
	this->Disconnect( wxID_UNDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnUndo ) );
	this->Disconnect( wxID_REDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnRedo ) );
	this->Disconnect( wxID_DISPLAYMACHINE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnUpdateVisibility ) );
	this->Disconnect( wxID_DISPLAYMATERIAL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIMainFrame::OnUpdateVisibility ) );
}

GUIObjectTransformation::GUIObjectTransformation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuObject = new wxMenu();
	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menuObject, wxID_OPEN, wxString( _("&Load Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemOpen );
	
	wxMenuItem* m_menuItemReLoad;
	m_menuItemReLoad = new wxMenuItem( m_menuObject, wxID_REVERT_TO_SAVED, wxString( _("&Reload Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemReLoad );
	
	wxMenuItem* m_menuItemSaveAs;
	m_menuItemSaveAs = new wxMenuItem( m_menuObject, wxID_SAVEAS, wxString( _("&Save Object As...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemSaveAs );
	
	wxMenuItem* m_separator;
	m_separator = m_menuObject->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuObject, wxID_CLOSE, wxString( _("&Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuObject, _("&Object") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	m_menubar->Append( m_menuSettings, _("&Settings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBox = new wxComboBox( this, wxID_ANY, _(" No objects in project!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY ); 
	bSizer22->Add( m_comboBox, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer21->Add( bSizer22, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelScale = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panelScale, wxID_ANY, _("Size of object") ), wxHORIZONTAL );
	
	m_staticText37 = new wxStaticText( m_panelScale, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	sbSizer3->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeX = new wxTextCtrl( m_panelScale, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer3->Add( m_textCtrlSizeX, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( m_panelScale, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	sbSizer3->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText38 = new wxStaticText( m_panelScale, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	sbSizer3->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeY = new wxTextCtrl( m_panelScale, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer3->Add( m_textCtrlSizeY, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( m_panelScale, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	sbSizer3->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText39 = new wxStaticText( m_panelScale, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	sbSizer3->Add( m_staticText39, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSizeZ = new wxTextCtrl( m_panelScale, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer3->Add( m_textCtrlSizeZ, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( m_panelScale, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	sbSizer3->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer29->Add( sbSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panelScale, wxID_ANY, _("Rescale") ), wxVERTICAL );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxScaleProportionally = new wxCheckBox( m_panelScale, wxID_ANY, _("Scale proportionally"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxScaleProportionally->SetValue(true); 
	bSizer24->Add( m_checkBoxScaleProportionally, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonMultTen = new wxButton( m_panelScale, wxID_ANY, _("XYZ * 10"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_buttonMultTen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDivTen = new wxButton( m_panelScale, wxID_ANY, _("XYZ / 10"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_buttonDivTen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrlPercent = new wxTextCtrl( m_panelScale, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_textCtrlPercent, 0, wxALL, 5 );
	
	m_staticText43 = new wxStaticText( m_panelScale, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer24->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button15 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( m_button15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer4->Add( bSizer24, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 3, 9, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText44 = new wxStaticText( m_panelScale, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	fgSizer6->Add( m_staticText44, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitX = new wxTextCtrl( m_panelScale, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScaleUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX2 = new wxStaticText( m_panelScale, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX2->Wrap( -1 );
	fgSizer6->Add( m_staticTextUnitX2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button19 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer6->Add( 30, 0, 1, wxEXPAND, 5 );
	
	m_staticText50 = new wxStaticText( m_panelScale, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	fgSizer6->Add( m_staticText50, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercentX = new wxTextCtrl( m_panelScale, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScalePercentX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText51 = new wxStaticText( m_panelScale, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer6->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button20 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText46 = new wxStaticText( m_panelScale, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer6->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitY = new wxTextCtrl( m_panelScale, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScaleUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY2 = new wxStaticText( m_panelScale, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY2->Wrap( -1 );
	fgSizer6->Add( m_staticTextUnitY2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button21 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button21, 0, wxALL, 5 );
	
	
	fgSizer6->Add( 30, 0, 1, wxEXPAND, 5 );
	
	m_staticText48 = new wxStaticText( m_panelScale, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer6->Add( m_staticText48, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercentY = new wxTextCtrl( m_panelScale, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScalePercentY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText49 = new wxStaticText( m_panelScale, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer6->Add( m_staticText49, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button22 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText52 = new wxStaticText( m_panelScale, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	fgSizer6->Add( m_staticText52, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScaleUnitZ = new wxTextCtrl( m_panelScale, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScaleUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ2 = new wxStaticText( m_panelScale, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ2->Wrap( -1 );
	fgSizer6->Add( m_staticTextUnitZ2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button23 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer6->Add( 30, 0, 1, wxEXPAND, 5 );
	
	m_staticText54 = new wxStaticText( m_panelScale, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	fgSizer6->Add( m_staticText54, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlScalePercentZ = new wxTextCtrl( m_panelScale, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_textCtrlScalePercentZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText55 = new wxStaticText( m_panelScale, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	fgSizer6->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button24 = new wxButton( m_panelScale, wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_button24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer4->Add( fgSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer29->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	m_panelScale->SetSizer( bSizer29 );
	m_panelScale->Layout();
	bSizer29->Fit( m_panelScale );
	m_notebook->AddPage( m_panelScale, _("Scale"), false );
	m_panelMirror = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_panelMirror, wxID_ANY, _("Direction") ), wxVERTICAL );
	
	m_button39 = new wxButton( m_panelMirror, wxID_ANY, _("Flip X"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button39, 0, wxALL, 5 );
	
	m_button40 = new wxButton( m_panelMirror, wxID_ANY, _("Flip Y"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button40, 0, wxALL, 5 );
	
	m_button41 = new wxButton( m_panelMirror, wxID_ANY, _("Flip Z"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_button41, 0, wxALL, 5 );
	
	bSizer36->Add( sbSizer10, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelMirror->SetSizer( bSizer36 );
	m_panelMirror->Layout();
	bSizer36->Fit( m_panelMirror );
	m_notebook->AddPage( m_panelMirror, _("Mirror"), false );
	m_panelMove = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panelMove, wxID_ANY, _("Position") ), wxVERTICAL );
	
	m_button18 = new wxButton( m_panelMove, wxID_ANY, _("Align with top of stock"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button18, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_button17 = new wxButton( m_panelMove, wxID_ANY, _("Align with middle of stock"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button17, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_button16 = new wxButton( m_panelMove, wxID_ANY, _("Align with stock origin"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button16, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer34->Add( sbSizer5, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelMove->SetSizer( bSizer34 );
	m_panelMove->Layout();
	bSizer34->Fit( m_panelMove );
	m_notebook->AddPage( m_panelMove, _("Move"), true );
	m_panelRotate = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panelRotate, wxID_ANY, _("Rotate stepwise") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_button32 = new wxButton( m_panelRotate, wxID_ANY, _("Y -90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button32, 0, wxALL, 5 );
	
	m_button33 = new wxButton( m_panelRotate, wxID_ANY, _("X -90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button33, 0, wxALL, 5 );
	
	m_button28 = new wxButton( m_panelRotate, wxID_ANY, _("Y +90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button28, 0, wxALL, 5 );
	
	m_button29 = new wxButton( m_panelRotate, wxID_ANY, _("Z -90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button29, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button30 = new wxButton( m_panelRotate, wxID_ANY, _("Z +90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button30, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button31 = new wxButton( m_panelRotate, wxID_ANY, _("X +90"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button31, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	sbSizer8->Add( fgSizer9, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer291->Add( sbSizer8, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelRotate->SetSizer( bSizer291 );
	m_panelRotate->Layout();
	bSizer291->Fit( m_panelRotate );
	m_notebook->AddPage( m_panelRotate, _("Rotate"), false );
	
	bSizer21->Add( m_notebook, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer21 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( m_menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnOpen ) );
	this->Connect( m_menuItemReLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnReLoad ) );
	this->Connect( m_menuItemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnSaveAs ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnClose ) );
	m_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnSelectObject ), NULL, this );
	m_buttonMultTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnMultiplyByTen ), NULL, this );
	m_buttonDivTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnDivideByTen ), NULL, this );
	m_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercent ), NULL, this );
	m_button19->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::ScaleUnitX ), NULL, this );
	m_button20->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercentX ), NULL, this );
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScaleUnitY ), NULL, this );
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercentY ), NULL, this );
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScaleUnitZ ), NULL, this );
	m_button24->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercentZ ), NULL, this );
	m_button39->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipX ), NULL, this );
	m_button40->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipY ), NULL, this );
	m_button41->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipZ ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnAlignWithTop ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnAlignWithMiddle ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnAlignWithStock ), NULL, this );
	m_button32->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnYMinus ), NULL, this );
	m_button33->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnXMinus ), NULL, this );
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnYPlus ), NULL, this );
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnZMinus ), NULL, this );
	m_button30->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnZPlus ), NULL, this );
	m_button31->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnXPlus ), NULL, this );
}

GUIObjectTransformation::~GUIObjectTransformation()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnReLoad ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnClose ) );
	m_comboBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnSelectObject ), NULL, this );
	m_buttonMultTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnMultiplyByTen ), NULL, this );
	m_buttonDivTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnDivideByTen ), NULL, this );
	m_button15->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercent ), NULL, this );
	m_button19->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::ScaleUnitX ), NULL, this );
	m_button20->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercentX ), NULL, this );
	m_button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScaleUnitY ), NULL, this );
	m_button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercentY ), NULL, this );
	m_button23->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScaleUnitZ ), NULL, this );
	m_button24->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnScalePercentZ ), NULL, this );
	m_button39->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipX ), NULL, this );
	m_button40->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipY ), NULL, this );
	m_button41->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnFlipZ ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnAlignWithTop ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnAlignWithMiddle ), NULL, this );
	m_button16->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnAlignWithStock ), NULL, this );
	m_button32->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnYMinus ), NULL, this );
	m_button33->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnXMinus ), NULL, this );
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnYPlus ), NULL, this );
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnZMinus ), NULL, this );
	m_button30->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnZPlus ), NULL, this );
	m_button31->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIObjectTransformation::OnXPlus ), NULL, this );
}

GUIMachineDebugger::GUIMachineDebugger( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter2 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->SetMinimumPaneSize( 200 );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitter2OnIdle ), NULL, this );
	m_panel = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter3 = new wxSplitterWindow( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->SetSashGravity( 200 );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIMachineDebugger::m_splitter3OnIdle ), NULL, this );
	m_panelEditor = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl37 = new wxTextCtrl( m_panelEditor, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer40->Add( m_textCtrl37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonRestart = new wxButton( m_panelEditor, wxID_ANY, _("Restart Machine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_buttonRestart, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_panelEditor->SetSizer( bSizer40 );
	m_panelEditor->Layout();
	bSizer40->Fit( m_panelEditor );
	m_panelOutput = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl38 = new wxTextCtrl( m_panelOutput, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer41->Add( m_textCtrl38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_panelOutput->SetSizer( bSizer41 );
	m_panelOutput->Layout();
	bSizer41->Fit( m_panelOutput );
	m_splitter3->SplitHorizontally( m_panelEditor, m_panelOutput, 222 );
	bSizer39->Add( m_splitter3, 1, wxEXPAND, 5 );
	
	m_panel->SetSizer( bSizer39 );
	m_panel->Layout();
	bSizer39->Fit( m_panel );
	m_panelMachineView = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new MainCanvas(m_panelMachineView);
	bSizer38->Add( m_canvas, 0, wxALL, 5 );
	
	m_panelMachineView->SetSizer( bSizer38 );
	m_panelMachineView->Layout();
	bSizer38->Fit( m_panelMachineView );
	m_splitter2->SplitVertically( m_panel, m_panelMachineView, 325 );
	bSizer37->Add( m_splitter2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer37 );
	this->Layout();
	m_statusBar3 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemLoad;
	m_menuItemLoad = new wxMenuItem( m_menuFile, wxID_ANY, wxString( _("&Load Machine Description") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemLoad );
	
	wxMenuItem* m_menuItemSave;
	m_menuItemSave = new wxMenuItem( m_menuFile, wxID_ANY, wxString( _("&Save Machine Description") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemSave );
	
	m_menubar->Append( m_menuFile, _("&File") );
	
	this->SetMenuBar( m_menubar );
	
	
	// Connect Events
	m_buttonRestart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnRestart ), NULL, this );
}

GUIMachineDebugger::~GUIMachineDebugger()
{
	// Disconnect Events
	m_buttonRestart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMachineDebugger::OnRestart ), NULL, this );
}

GUIToolbox::GUIToolbox( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuTools = new wxMenu();
	wxMenuItem* m_menuItem15;
	m_menuItem15 = new wxMenuItem( m_menuTools, wxID_ANY, wxString( _("&Load Toolbox") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem15 );
	m_menuItem15->Enable( false );
	
	wxMenuItem* m_menuItem16;
	m_menuItem16 = new wxMenuItem( m_menuTools, wxID_ANY, wxString( _("&Save Toolbox") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem16 );
	m_menuItem16->Enable( false );
	
	wxMenuItem* m_separator3;
	m_separator3 = m_menuTools->AppendSeparator();
	
	wxMenuItem* m_menuItem17;
	m_menuItem17 = new wxMenuItem( m_menuTools, wxID_CLOSE, wxString( _("&Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem17 );
	
	m_menubar->Append( m_menuTools, _("&Tools") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem22;
	m_menuItem22 = new wxMenuItem( m_menuSettings, wxID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem22 );
	
	m_menubar->Append( m_menuSettings, _("&Settings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBoxToolSelector = new wxComboBox( this, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer14->Add( m_comboBoxToolSelector, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonToolNew = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonToolNew, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonToolUpdate = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonToolUpdate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonToolDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonToolDelete, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer13->Add( bSizer14, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->AddGrowableRow( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool definition") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 5, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Shaft diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftDiameter = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlShaftDiameter->SetToolTip( _("Diameter of the part that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftDiameter, 0, wxALL, 5 );
	
	m_staticTextUnitShaftDiameter = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftDiameter->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitShaftDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Shaft length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftLength = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlShaftLength->SetToolTip( _("This is the length of the that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftLength, 0, wxALL, 5 );
	
	m_staticTextUnitShaftLength = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftLength->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitShaftLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("Maximum speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer1->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlMaxSpeed->SetToolTip( _("Max. speed: Look at label on box you got the tools shipped in.") );
	
	fgSizer1->Add( m_textCtrlMaxSpeed, 0, wxALL, 5 );
	
	m_staticTextUnitMaxSpeed = new wxStaticText( this, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMaxSpeed->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Feed coefficient:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFeedCoefficient = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlFeedCoefficient->SetToolTip( _("Feed per tooth: How deep can a tooth cut per revolution. Usually in the range of 0.02 mm to 0.05 mm.") );
	
	fgSizer1->Add( m_textCtrlFeedCoefficient, 0, wxALL, 5 );
	
	m_staticTextUnitFeedCoefficient = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedCoefficient->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitFeedCoefficient, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Number of teeth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer1->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlNrOfTeeth = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlNrOfTeeth->SetToolTip( _("Number of teeth around the cutter.") );
	
	fgSizer1->Add( m_textCtrlNrOfTeeth, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer1->Add( m_staticText17, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( fgSizer1, 0, 0, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	sbSizer1->Add( m_staticText26, 0, wxALL, 5 );
	
	m_textCtrlComment = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	sbSizer1->Add( m_textCtrlComment, 1, wxALL|wxEXPAND, 5 );
	
	fgSizer3->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	m_panel=new ToolPanel(this);
	fgSizer3->Add( m_panel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool shape") ), wxVERTICAL );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonShapeNew = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_buttonShapeNew, 0, wxALL, 5 );
	
	m_buttonShapeUpdate = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_buttonShapeUpdate, 0, wxALL, 5 );
	
	m_buttonShapeDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( m_buttonShapeDelete, 0, wxALL, 5 );
	
	bSizer16->Add( bSizer17, 0, 0, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Linear or bend line"), _("Corner: first diameter change, then height change"), _("Corner: first height change, then diameter change"), _("Sphere: radius at upper limit, calculate height"), _("Sphere: radius at lower limit, calculate height") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 4 );
	bSizer16->Add( m_choiceType, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, _("Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDiameter = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlDiameter->SetToolTip( _("Diameter of the tool at the end of this segment.") );
	
	fgSizer2->Add( m_textCtrlDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitDiameter = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlHeight->SetToolTip( _("Height of this segment.") );
	
	fgSizer2->Add( m_textCtrlHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHeight = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHeight->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRadius = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlRadius->SetToolTip( _("Radius of curvature:\nPositive radius = convex surface = bulged to the outside.\nNegative radius = concave surface = bulged to the inside.\nRadius of 0 = straight line. ") );
	
	fgSizer2->Add( m_textCtrlRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitRadius = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRadius->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitRadius, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText24 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer2->Add( m_staticText24, 0, wxALL, 5 );
	
	m_checkBoxCutting = new wxCheckBox( this, wxID_ANY, _("surface is cutting"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_checkBoxCutting, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer2->Add( m_staticText25, 0, wxALL, 5 );
	
	bSizer16->Add( fgSizer2, 0, 0, 5 );
	
	bSizer15->Add( bSizer16, 0, 0, 5 );
	
	m_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer15->Add( m_listCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	sbSizer2->Add( bSizer15, 1, wxEXPAND, 5 );
	
	fgSizer3->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	m_canvas = new ToolCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	fgSizer3->Add( m_canvas, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer13->Add( fgSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer13 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItem17->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnClose ) );
	this->Connect( m_menuItem22->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnChangeStereo3D ) );
	m_buttonToolNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnNewTool ), NULL, this );
	m_buttonToolUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnUpdateTool ), NULL, this );
	m_buttonToolDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnDeleteTool ), NULL, this );
	m_buttonShapeNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeNew ), NULL, this );
	m_buttonShapeUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeUpdate ), NULL, this );
	m_buttonShapeDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeDelete ), NULL, this );
	m_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIToolbox::OnShapeSelect ), NULL, this );
}

GUIToolbox::~GUIToolbox()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnChangeStereo3D ) );
	m_buttonToolNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnNewTool ), NULL, this );
	m_buttonToolUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnUpdateTool ), NULL, this );
	m_buttonToolDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnDeleteTool ), NULL, this );
	m_buttonShapeNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeNew ), NULL, this );
	m_buttonShapeUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeUpdate ), NULL, this );
	m_buttonShapeDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnShapeDelete ), NULL, this );
	m_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIToolbox::OnShapeSelect ), NULL, this );
}

GUIStockMaterial::GUIStockMaterial( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItem43;
	m_menuItem43 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Load Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem43 );
	
	wxMenuItem* m_menuItem42;
	m_menuItem42 = new wxMenuItem( m_menuStock, wxID_ANY, wxString( _("&Save Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem42 );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menuStock->AppendSeparator();
	
	wxMenuItem* m_menuItem34;
	m_menuItem34 = new wxMenuItem( m_menuStock, wxID_CLOSE, wxString( _("&Close Window") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItem34 );
	
	m_menubar->Append( m_menuStock, _("&Stock") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, wxID_SETUPUNITS, wxString( _("Setup &Units") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	m_menubar->Append( m_menuSettings, _("S&ettings") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer20->Add( m_listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText27 = new wxStaticText( this, wxID_ANY, _("Size X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer4->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlX = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText28 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer4->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText29 = new wxStaticText( this, wxID_ANY, _("Size Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer4->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlY = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText30 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer4->Add( m_staticText30, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText31 = new wxStaticText( this, wxID_ANY, _("Size Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer4->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlZ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText32 = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer4->Add( m_staticText32, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, _("Max speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer4->Add( m_staticText33, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText34 = new wxStaticText( this, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer4->Add( m_staticText34, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText35 = new wxStaticText( this, wxID_ANY, _("Max feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer4->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlMaxFeedrate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_textCtrlMaxFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText36 = new wxStaticText( this, wxID_ANY, _("mm/s"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer4->Add( m_staticText36, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer20->Add( fgSizer4, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer20 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItem34->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIStockMaterial::OnClose ) );
}

GUIStockMaterial::~GUIStockMaterial()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIStockMaterial::OnClose ) );
}

GUIAnimation::GUIAnimation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText70 = new wxStaticText( this, wxID_ANY, _("Toolpath:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	bSizer30->Add( m_staticText70, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceToolpathChoices[] = { _("No toolpath available.") };
	int m_choiceToolpathNChoices = sizeof( m_choiceToolpathChoices ) / sizeof( wxString );
	m_choiceToolpath = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceToolpathNChoices, m_choiceToolpathChoices, 0 );
	m_choiceToolpath->SetSelection( 0 );
	bSizer30->Add( m_choiceToolpath, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer29->Add( bSizer30, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText71 = new wxStaticText( this, wxID_ANY, _("Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	bSizer31->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_textCtrlTime, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText72 = new wxStaticText( this, wxID_ANY, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText72->Wrap( -1 );
	bSizer31->Add( m_staticText72, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxTime = new wxTextCtrl( this, wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer31->Add( m_textCtrlMaxTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer29->Add( bSizer31, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderTime = new wxSlider( this, wxID_ANY, 0, 0, 2000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer29->Add( m_sliderTime, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bpButtonFirst = new wxBitmapButton( this, wxID_ANY, wxBitmap( first_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonFirst->SetToolTip( _("First") );
	
	m_bpButtonFirst->SetToolTip( _("First") );
	
	bSizer32->Add( m_bpButtonFirst, 0, wxALL, 5 );
	
	m_bpButtonPrev = new wxBitmapButton( this, wxID_ANY, wxBitmap( prev_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPrev->SetToolTip( _("Step back") );
	
	m_bpButtonPrev->SetToolTip( _("Step back") );
	
	bSizer32->Add( m_bpButtonPrev, 0, wxALL, 5 );
	
	m_bpButtonPlayStop = new wxBitmapButton( this, wxID_ANY, wxBitmap( play_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonPlayStop->SetToolTip( _("Play / Stop") );
	
	m_bpButtonPlayStop->SetToolTip( _("Play / Stop") );
	
	bSizer32->Add( m_bpButtonPlayStop, 0, wxALL, 5 );
	
	m_bpButtonNext = new wxBitmapButton( this, wxID_ANY, wxBitmap( next_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonNext->SetToolTip( _("Step forward") );
	
	m_bpButtonNext->SetToolTip( _("Step forward") );
	
	bSizer32->Add( m_bpButtonNext, 0, wxALL, 5 );
	
	m_bpButtonLast = new wxBitmapButton( this, wxID_ANY, wxBitmap( last_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_bpButtonLast->SetToolTip( _("Last") );
	
	m_bpButtonLast->SetToolTip( _("Last") );
	
	bSizer32->Add( m_bpButtonLast, 0, wxALL, 5 );
	
	bSizer29->Add( bSizer32, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer29 );
	this->Layout();
	
	// Connect Events
	m_bpButtonFirst->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnFirst ), NULL, this );
	m_bpButtonPrev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPrev ), NULL, this );
	m_bpButtonPlayStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPlayStop ), NULL, this );
	m_bpButtonNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnNext ), NULL, this );
	m_bpButtonLast->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnLast ), NULL, this );
}

GUIAnimation::~GUIAnimation()
{
	// Disconnect Events
	m_bpButtonFirst->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnFirst ), NULL, this );
	m_bpButtonPrev->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPrev ), NULL, this );
	m_bpButtonPlayStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnPlayStop ), NULL, this );
	m_bpButtonNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnNext ), NULL, this );
	m_bpButtonLast->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAnimation::OnLast ), NULL, this );
}

GUISetup6DOFController::GUISetup6DOFController( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,-1 ), wxSize( -1,-1 ) );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText = new wxStaticText( this, wxID_ANY, _("Serial port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	bSizer1->Add( m_staticText, 0, wxALL, 5 );
	
	textPort = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( textPort, 0, wxALL|wxEXPAND, 5 );
	
	wxString radioDeviceSelectChoices[] = { _("SpaceBall"), _("SpaceOrb"), _("SpaceMouse") };
	int radioDeviceSelectNChoices = sizeof( radioDeviceSelectChoices ) / sizeof( wxString );
	radioDeviceSelect = new wxRadioBox( this, wxID_ANY, _("Type of controller"), wxDefaultPosition, wxDefaultSize, radioDeviceSelectNChoices, radioDeviceSelectChoices, 1, wxRA_SPECIFY_COLS );
	radioDeviceSelect->SetSelection( 2 );
	bSizer1->Add( radioDeviceSelect, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTx;
	bSizerTx = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTx = new wxStaticText( this, wxID_ANY, _("Tx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTx->Wrap( -1 );
	bSizerTx->Add( m_staticTextTx, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_sliderTx = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTx->Enable( false );
	
	bSizerTx->Add( m_sliderTx, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizerTx, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTy;
	bSizerTy = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTy = new wxStaticText( this, wxID_ANY, _("Ty"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTy->Wrap( -1 );
	bSizerTy->Add( m_staticTextTy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderTy = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTy->Enable( false );
	
	bSizerTy->Add( m_sliderTy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerTy, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerTz;
	bSizerTz = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextTz = new wxStaticText( this, wxID_ANY, _("Tz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTz->Wrap( -1 );
	bSizerTz->Add( m_staticTextTz, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_sliderTz = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderTz->Enable( false );
	
	bSizerTz->Add( m_sliderTz, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerTz, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRx;
	bSizerRx = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRx = new wxStaticText( this, wxID_ANY, _("Rx"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRx->Wrap( -1 );
	bSizerRx->Add( m_staticTextRx, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRx = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRx->Enable( false );
	
	bSizerRx->Add( m_sliderRx, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerRx, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRy;
	bSizerRy = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRy = new wxStaticText( this, wxID_ANY, _("Ry"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRy->Wrap( -1 );
	bSizerRy->Add( m_staticTextRy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRy = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRy->Enable( false );
	
	bSizerRy->Add( m_sliderRy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerRy, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRz;
	bSizerRz = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRz = new wxStaticText( this, wxID_ANY, _("Rz"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRz->Wrap( -1 );
	bSizerRz->Add( m_staticTextRz, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderRz = new wxSlider( this, wxID_ANY, 0, -1024, 1023, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	m_sliderRz->Enable( false );
	
	bSizerRz->Add( m_sliderRz, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizerRz, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	buttonConnect = new wxButton( this, ID_BUTTONCONNECT, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( buttonConnect, 1, wxALL|wxEXPAND, 5 );
	
	buttonDisconnect = new wxButton( this, ID_BUTTONDISCONNECT, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonDisconnect->Enable( false );
	
	bSizer2->Add( buttonDisconnect, 1, wxALL|wxEXPAND, 5 );
	
	buttonClose = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( buttonClose, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnConnect ), NULL, this );
	buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnDisconnect ), NULL, this );
	buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnClose ), NULL, this );
}

GUISetup6DOFController::~GUISetup6DOFController()
{
	// Disconnect Events
	buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnConnect ), NULL, this );
	buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnDisconnect ), NULL, this );
	buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetup6DOFController::OnClose ), NULL, this );
}

GUISetupUnits::GUISetupUnits( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Units ") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText57 = new wxStaticText( this, wxID_ANY, _("Length Units"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText57->Wrap( -1 );
	fgSizer6->Add( m_staticText57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitLengthChoices[] = { _("um"), _("mm"), _("cm"), _("m"), _("inch"), _("mil") };
	int m_choiceUnitLengthNChoices = sizeof( m_choiceUnitLengthChoices ) / sizeof( wxString );
	m_choiceUnitLength = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitLengthNChoices, m_choiceUnitLengthChoices, 0 );
	m_choiceUnitLength->SetSelection( 1 );
	fgSizer6->Add( m_choiceUnitLength, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText58 = new wxStaticText( this, wxID_ANY, _("Tolerances"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText58->Wrap( -1 );
	fgSizer6->Add( m_staticText58, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitTolerancesChoices[] = { _("um"), _("mm"), _("cm"), _("m"), _("inch"), _("mil") };
	int m_choiceUnitTolerancesNChoices = sizeof( m_choiceUnitTolerancesChoices ) / sizeof( wxString );
	m_choiceUnitTolerances = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitTolerancesNChoices, m_choiceUnitTolerancesChoices, 0 );
	m_choiceUnitTolerances->SetSelection( 1 );
	fgSizer6->Add( m_choiceUnitTolerances, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText59 = new wxStaticText( this, wxID_ANY, _("Rotational Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	fgSizer6->Add( m_staticText59, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceRotationalSpeedChoices[] = { _("rpm"), _("1/s"), _("1/min"), _("rad/s") };
	int m_choiceRotationalSpeedNChoices = sizeof( m_choiceRotationalSpeedChoices ) / sizeof( wxString );
	m_choiceRotationalSpeed = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceRotationalSpeedNChoices, m_choiceRotationalSpeedChoices, 0 );
	m_choiceRotationalSpeed->SetSelection( 2 );
	fgSizer6->Add( m_choiceRotationalSpeed, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer6->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	bSizer25->Add( sbSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer25 );
	this->Layout();
	bSizer25->Fit( this );
	
	// Connect Events
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupUnits::OnClose ), NULL, this );
}

GUISetupUnits::~GUISetupUnits()
{
	// Disconnect Events
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISetupUnits::OnClose ), NULL, this );
}

GUIAbout::GUIAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl12 = new wxTextCtrl( this, wxID_ANY, _("Generic CAM  Copyright (C) 2010  Tobias Schaefer\n\nFrench translation & additional debugging: Jacques-Louis Tartarin\nItalian Translation: Sandro Dalle Nogare\n\nLicence for Generic CAM:\nGNU General Public License version 3.0 (GPLv3)\n\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\n\nYou should have received a copy of the GNU General Public License along with this program.\nIf not, see <http://www.gnu.org/licenses/>."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	bSizer3->Add( m_textCtrl12, 1, wxALL|wxEXPAND, 5 );
	
	m_button1 = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAbout::OnClose ), NULL, this );
}

GUIAbout::~GUIAbout()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIAbout::OnClose ), NULL, this );
}
