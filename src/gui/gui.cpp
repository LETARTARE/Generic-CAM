///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "gui.h"

#include "../icon/arrowxn.xpm"
#include "../icon/arrowxp.xpm"
#include "../icon/arrowyd.xpm"
#include "../icon/arrowyn.xpm"
#include "../icon/arrowyp.xpm"
#include "../icon/arrowyu.xpm"
#include "../icon/arrowzn.xpm"
#include "../icon/arrowzp.xpm"
#include "../icon/first.xpm"
#include "../icon/last.xpm"
#include "../icon/next.xpm"
#include "../icon/play.xpm"
#include "../icon/prev.xpm"

///////////////////////////////////////////////////////////////////////////

GUIFrameMain::GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDocChildFrame( doc, view, parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	m_menubar->Append( m_menuFile, _("&Project") ); 
	
	m_menuEdit = new wxMenu();
	m_menubar->Append( m_menuEdit, _("&Edit") ); 
	
	m_menuObject = new wxMenu();
	wxMenuItem* m_menuItemObjectModify;
	m_menuItemObjectModify = new wxMenuItem( m_menuObject, ID_OBJECTMODIFY, wxString( _("&Modify Object") ) + wxT('\t') + wxT("CTRL+M"), wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectModify );
	
	wxMenuItem* m_menuItemObjectFlipNormals;
	m_menuItemObjectFlipNormals = new wxMenuItem( m_menuObject, ID_OBJECTFLIPNORMALS, wxString( _("&Flip Normals") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectFlipNormals );
	
	m_menuObject->AppendSeparator();
	
	wxMenuItem* m_menuItemObjectLoad;
	m_menuItemObjectLoad = new wxMenuItem( m_menuObject, ID_OBJECTLOAD, wxString( _("&Load Object File...") ) + wxT('\t') + wxT("CTRL+O"), wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectLoad );
	
	wxMenuItem* m_menuItemObjectRename;
	m_menuItemObjectRename = new wxMenuItem( m_menuObject, ID_OBJECTRENAME, wxString( _("&Rename Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectRename );
	
	wxMenuItem* m_menuItemObjectDelete;
	m_menuItemObjectDelete = new wxMenuItem( m_menuObject, ID_OBJECTDELETE, wxString( _("&Delete Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectDelete );
	
	m_menubar->Append( m_menuObject, _("&Object") ); 
	
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItemStockOrganize;
	m_menuItemStockOrganize = new wxMenuItem( m_menuStock, ID_STOCKORGANIZE, wxString( _("&Organize Stock") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemStockOrganize );
	
	wxMenuItem* m_menuItemStockToWorkpiece;
	m_menuItemStockToWorkpiece = new wxMenuItem( m_menuStock, ID_WORKPIECEADD, wxString( _("&Add Stock to Project") ) , _("Add stock material to project as workpiece."), wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemStockToWorkpiece );
	
	m_menuStock->AppendSeparator();
	
	wxMenuItem* m_menuItemStockLoad;
	m_menuItemStockLoad = new wxMenuItem( m_menuStock, ID_STOCKLOAD, wxString( _("&Load Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemStockLoad );
	
	wxMenuItem* m_menuItemStockSave;
	m_menuItemStockSave = new wxMenuItem( m_menuStock, ID_STOCKSAVE, wxString( _("&Save Stock...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemStockSave );
	
	m_menubar->Append( m_menuStock, _("&Stock") ); 
	
	m_menuWorkpiece = new wxMenu();
	wxMenuItem* m_menuItemWorkpieceSetup;
	m_menuItemWorkpieceSetup = new wxMenuItem( m_menuWorkpiece, ID_WORKPIECESETUP, wxString( _("&Setup Workpiece") ) + wxT('\t') + wxT("CTRL+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuWorkpiece->Append( m_menuItemWorkpieceSetup );
	
	wxMenuItem* m_menuItemWorkpieceDelete;
	m_menuItemWorkpieceDelete = new wxMenuItem( m_menuWorkpiece, ID_WORKPIECEDELETE, wxString( _("&Delete Workpiece") ) , _("Remove the selected workpiece or workpieces."), wxITEM_NORMAL );
	m_menuWorkpiece->Append( m_menuItemWorkpieceDelete );
	
	wxMenuItem* m_menuItemWorkpieceDeleteUnused;
	m_menuItemWorkpieceDeleteUnused = new wxMenuItem( m_menuWorkpiece, ID_WORKPIECEDELETEUNUSED, wxString( _("Delete &unused Workpieces") ) , _("Remove all workpieces, that have no objects linked to them."), wxITEM_NORMAL );
	m_menuWorkpiece->Append( m_menuItemWorkpieceDeleteUnused );
	
	m_menubar->Append( m_menuWorkpiece, _("&Workpiece") ); 
	
	m_menuMachine = new wxMenu();
	wxMenuItem* m_menuItemMachineLoad;
	m_menuItemMachineLoad = new wxMenuItem( m_menuMachine, ID_MACHINELOAD, wxString( _("&Load Machine...") ) + wxT('\t') + wxT("CTRL+SHIFT+M"), _("Load a machine for the selected run"), wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemMachineLoad );
	
	wxMenuItem* m_menuItemMachineReload;
	m_menuItemMachineReload = new wxMenuItem( m_menuMachine, ID_MACHINERELOAD, wxString( _("&Reload Machine") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemMachineReload );
	
	m_menuMachine->AppendSeparator();
	
	wxMenuItem* m_menuItemMachineDebugger;
	m_menuItemMachineDebugger = new wxMenuItem( m_menuMachine, ID_MACHINEDEBUGGER, wxString( _("&Open Machine Debugger") ) + wxT('\t') + wxT("CTRL+D"), wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemMachineDebugger );
	
	wxMenuItem* m_menuItemFlipDrill;
	m_menuItemFlipDrill = new wxMenuItem( m_menuMachine, wxID_ANY, wxString( _("Setup &Filp Drills") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuMachine->Append( m_menuItemFlipDrill );
	m_menuItemFlipDrill->Enable( false );
	
	m_menubar->Append( m_menuMachine, _("&Machine") ); 
	
	m_menuToolbox = new wxMenu();
	wxMenuItem* m_menuItemToolboxEdit;
	m_menuItemToolboxEdit = new wxMenuItem( m_menuToolbox, ID_TOOLBOXEDIT, wxString( _("&Edit Toolbox") ) + wxT('\t') + wxT("Ctrl+T"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxEdit );
	
	wxMenuItem* m_menuItemToolboxLoad;
	m_menuItemToolboxLoad = new wxMenuItem( m_menuToolbox, ID_TOOLBOXLOAD, wxString( _("&Load Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxLoad );
	
	wxMenuItem* m_menuItemToolboxSave;
	m_menuItemToolboxSave = new wxMenuItem( m_menuToolbox, ID_TOOLBOXSAVE, wxString( _("&Save Toolbox...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxSave );
	
	m_menubar->Append( m_menuToolbox, _("&Toolbox") ); 
	
	m_menuRun = new wxMenu();
	wxMenuItem* m_menuItemRunSetup;
	m_menuItemRunSetup = new wxMenuItem( m_menuRun, ID_RUNEDIT, wxString( _("&Setup Run") ) + wxT('\t') + wxT("CTRL+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuRun->Append( m_menuItemRunSetup );
	
	wxMenuItem* m_menuItemRunAdd;
	m_menuItemRunAdd = new wxMenuItem( m_menuRun, ID_RUNADD, wxString( _("&Add Run") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuRun->Append( m_menuItemRunAdd );
	
	wxMenuItem* m_menuItemRunDelete;
	m_menuItemRunDelete = new wxMenuItem( m_menuRun, ID_RUNDELETE, wxString( _("&Delete Run") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuRun->Append( m_menuItemRunDelete );
	
	m_menubar->Append( m_menuRun, _("&Run") ); 
	
	m_menuToolpath = new wxMenu();
	wxMenuItem* m_menuItemGeneratorSetup;
	m_menuItemGeneratorSetup = new wxMenuItem( m_menuToolpath, ID_GENERATORSETUP, wxString( _("&Setup Generators") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItemGeneratorSetup );
	
	m_menuToolpath->AppendSeparator();
	
	wxMenuItem* m_menuItemGeneratorStart;
	m_menuItemGeneratorStart = new wxMenuItem( m_menuToolpath, ID_GENERATORSTART, wxString( _("Start &Generators") ) + wxT('\t') + wxT("CTRL+G"), _("Start the generation of any ungenerated toolpaths."), wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItemGeneratorStart );
	
	wxMenuItem* m_menuItemGeneratorAutomatic;
	m_menuItemGeneratorAutomatic = new wxMenuItem( m_menuToolpath, ID_GENERATORAUTOMATIC, wxString( _("&Automatic Generation") ) , wxEmptyString, wxITEM_CHECK );
	m_menuToolpath->Append( m_menuItemGeneratorAutomatic );
	m_menuItemGeneratorAutomatic->Enable( false );
	
	wxMenuItem* m_menuItemGeneratorRestart;
	m_menuItemGeneratorRestart = new wxMenuItem( m_menuToolpath, ID_GENERATORRESTART, wxString( _("&Restart Generation") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItemGeneratorRestart );
	m_menuItemGeneratorRestart->Enable( false );
	
	m_menuToolpath->AppendSeparator();
	
	m_menuDialect = new wxMenu();
	wxMenuItem* m_menuDialectItem = new wxMenuItem( m_menuToolpath, wxID_ANY, _("Dialect"), wxEmptyString, wxITEM_NORMAL, m_menuDialect );
	wxMenuItem* m_menuItemDialectRS274NGC;
	m_menuItemDialectRS274NGC = new wxMenuItem( m_menuDialect, ID_DIALECT_RS274NGC, wxString( _("RS274NGC") ) , _("Dialect according to the document \"The NIST RS274NGC Interpreter - Version 3\" by Thomas R. Kramer, Frederick M. Proctor and Elena Messina (NISTIR 6556, August 17, 2000).\n\n"), wxITEM_RADIO );
	m_menuDialect->Append( m_menuItemDialectRS274NGC );
	m_menuItemDialectRS274NGC->Check( true );
	
	wxMenuItem* m_menuItemDialectFanucM;
	m_menuItemDialectFanucM = new wxMenuItem( m_menuDialect, ID_DIALECT_FANUCM, wxString( _("Fanuc-M") ) , _("Dialect used by the Fanuc-M milling simulator."), wxITEM_RADIO );
	m_menuDialect->Append( m_menuItemDialectFanucM );
	
	m_menuToolpath->Append( m_menuDialectItem );
	
	wxMenuItem* m_menuItemGeneratorSaveToolpath;
	m_menuItemGeneratorSaveToolpath = new wxMenuItem( m_menuToolpath, ID_TOOLPATHSAVE, wxString( _("Save &Toolpath") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItemGeneratorSaveToolpath );
	
	m_menuToolpath->AppendSeparator();
	
	wxMenuItem* m_menuItemShowAnimationControl;
	m_menuItemShowAnimationControl = new wxMenuItem( m_menuToolpath, wxID_ANY, wxString( _("Show Animation &Control") ) + wxT('\t') + wxT("Ctrl+A"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolpath->Append( m_menuItemShowAnimationControl );
	
	m_menubar->Append( m_menuToolpath, _("Tool&path") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemActivateStereo3D;
	m_menuItemActivateStereo3D = new wxMenuItem( m_menuView, ID_VIEWSTEREO3D, wxString( _("Stereo &3D") ) + wxT('\t') + wxT("CTRL+3"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemActivateStereo3D );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemCloseAdditionalWindows;
	m_menuItemCloseAdditionalWindows = new wxMenuItem( m_menuView, ID_CLOSEEXTRAWINDOWS, wxString( _("&Close all Extra Windows") ) + wxT('\t') + wxT("CTRL+SHIFT+W"), _("Close all the dialogs. No data is lost."), wxITEM_NORMAL );
	m_menuView->Append( m_menuItemCloseAdditionalWindows );
	
	wxMenuItem* m_menuItemLogShow;
	m_menuItemLogShow = new wxMenuItem( m_menuView, ID_LOGSHOW, wxString( _("Show &Log Window") ) + wxT('\t') + wxT("CTRL+SHIFT+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemLogShow );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemTop;
	m_menuItemTop = new wxMenuItem( m_menuView, ID_VIEWTOP, wxString( _("View from Top") ) + wxT('\t') + wxT("KP_7"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemTop );
	
	wxMenuItem* m_menuItemBottom;
	m_menuItemBottom = new wxMenuItem( m_menuView, ID_VIEWBOTTOM, wxString( _("View from Bottom") ) + wxT('\t') + wxT("CTRL+KP_7"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemBottom );
	
	wxMenuItem* m_menuItemFront;
	m_menuItemFront = new wxMenuItem( m_menuView, ID_VIEWFRONT, wxString( _("View from Front") ) + wxT('\t') + wxT("KP_1"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemFront );
	
	wxMenuItem* m_menuItemBack;
	m_menuItemBack = new wxMenuItem( m_menuView, ID_VIEWBACK, wxString( _("View from Back") ) + wxT('\t') + wxT("CTRL+KP_1"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemBack );
	
	wxMenuItem* m_menuItemRight;
	m_menuItemRight = new wxMenuItem( m_menuView, ID_VIEWRIGHT, wxString( _("View from Right") ) + wxT('\t') + wxT("KP_3"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemRight );
	
	wxMenuItem* m_menuItemLeft;
	m_menuItemLeft = new wxMenuItem( m_menuView, ID_VIEWLEFT, wxString( _("View from Left") ) + wxT('\t') + wxT("CTRL+KP_3"), wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemLeft );
	
	m_menubar->Append( m_menuView, _("&View") ); 
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItemTestGCode;
	m_menuItemTestGCode = new wxMenuItem( m_menuHelp, ID_TESTGCODE, wxString( _("Test G-Code") ) + wxT('\t') + wxT("CTRL+SHIFT+G"), _("Analyse a line (block) of G-Code with the implemented parser."), wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemTestGCode );
	
	m_menubar->Append( m_menuHelp, _("&Help") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrameMain::m_splitterOnIdle ), NULL, this );
	m_splitter->SetMinimumPaneSize( 100 );
	
	m_panelTree = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerTree;
	bSizerTree = new wxBoxSizer( wxVERTICAL );
	
	m_tree = new wxTreeCtrl( m_panelTree, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS|wxTR_FULL_ROW_HIGHLIGHT|wxTR_HAS_BUTTONS|wxTR_MULTIPLE|wxTR_NO_LINES|wxTR_SINGLE );
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
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Connect( m_menuItemObjectModify->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectModify ) );
	this->Connect( m_menuItemObjectFlipNormals->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectFlipNormals ) );
	this->Connect( m_menuItemObjectLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectLoad ) );
	this->Connect( m_menuItemObjectRename->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectRename ) );
	this->Connect( m_menuItemObjectDelete->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectDelete ) );
	this->Connect( m_menuItemStockOrganize->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnStockEdit ) );
	this->Connect( m_menuItemStockToWorkpiece->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceAdd ) );
	this->Connect( m_menuItemWorkpieceSetup->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceSetup ) );
	this->Connect( m_menuItemWorkpieceDelete->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceDelete ) );
	this->Connect( m_menuItemWorkpieceDeleteUnused->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceDeleteUnused ) );
	this->Connect( m_menuItemMachineLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnMachineLoad ) );
	this->Connect( m_menuItemMachineReload->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnMachineReload ) );
	this->Connect( m_menuItemMachineDebugger->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnMachineDebugger ) );
	this->Connect( m_menuItemFlipDrill->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnFlipDrillSetup ) );
	this->Connect( m_menuItemToolboxEdit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToolboxEdit ) );
	this->Connect( m_menuItemToolboxLoad->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToolboxLoad ) );
	this->Connect( m_menuItemToolboxSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToolboxSave ) );
	this->Connect( m_menuItemRunSetup->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRunEdit ) );
	this->Connect( m_menuItemRunAdd->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRunAdd ) );
	this->Connect( m_menuItemRunDelete->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRunDelete ) );
	this->Connect( m_menuItemGeneratorSetup->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorSetup ) );
	this->Connect( m_menuItemGeneratorStart->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorStart ) );
	this->Connect( m_menuItemGeneratorAutomatic->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorAutomatic ) );
	this->Connect( m_menuItemGeneratorRestart->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorRestart ) );
	this->Connect( m_menuItemGeneratorSaveToolpath->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorSaveToolpath ) );
	this->Connect( m_menuItemShowAnimationControl->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnShowAnimationControl ) );
	this->Connect( m_menuItemActivateStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnActivateStereo3D ) );
	this->Connect( m_menuItemCloseAdditionalWindows->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnExtraWindowClose ) );
	this->Connect( m_menuItemLogShow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnShowLogWindow ) );
	this->Connect( m_menuItemTop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Connect( m_menuItemBottom->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Connect( m_menuItemFront->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Connect( m_menuItemBack->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Connect( m_menuItemRight->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Connect( m_menuItemLeft->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Connect( m_menuItemTestGCode->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnTestGCode ) );
	m_tree->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnBeginLabelEdit ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnEndLabelEdit ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( GUIFrameMain::OnActivate ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIFrameMain::OnActivateRightClickMenu ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIFrameMain::OnSelectionChanged ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( GUIFrameMain::OnSelectionChanging ), NULL, this );
	m_canvas->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUIFrameMain::On3DDClick ), NULL, this );
	m_canvas->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIFrameMain::On3DSelect ), NULL, this );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Disconnect( ID_OBJECTMODIFY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectModify ) );
	this->Disconnect( ID_OBJECTFLIPNORMALS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectFlipNormals ) );
	this->Disconnect( ID_OBJECTLOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectLoad ) );
	this->Disconnect( ID_OBJECTRENAME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectRename ) );
	this->Disconnect( ID_OBJECTDELETE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnObjectDelete ) );
	this->Disconnect( ID_STOCKORGANIZE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnStockEdit ) );
	this->Disconnect( ID_WORKPIECEADD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceAdd ) );
	this->Disconnect( ID_WORKPIECESETUP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceSetup ) );
	this->Disconnect( ID_WORKPIECEDELETE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceDelete ) );
	this->Disconnect( ID_WORKPIECEDELETEUNUSED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnWorkpieceDeleteUnused ) );
	this->Disconnect( ID_MACHINELOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnMachineLoad ) );
	this->Disconnect( ID_MACHINERELOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnMachineReload ) );
	this->Disconnect( ID_MACHINEDEBUGGER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnMachineDebugger ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnFlipDrillSetup ) );
	this->Disconnect( ID_TOOLBOXEDIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToolboxEdit ) );
	this->Disconnect( ID_TOOLBOXLOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToolboxLoad ) );
	this->Disconnect( ID_TOOLBOXSAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToolboxSave ) );
	this->Disconnect( ID_RUNEDIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRunEdit ) );
	this->Disconnect( ID_RUNADD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRunAdd ) );
	this->Disconnect( ID_RUNDELETE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRunDelete ) );
	this->Disconnect( ID_GENERATORSETUP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorSetup ) );
	this->Disconnect( ID_GENERATORSTART, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorStart ) );
	this->Disconnect( ID_GENERATORAUTOMATIC, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorAutomatic ) );
	this->Disconnect( ID_GENERATORRESTART, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorRestart ) );
	this->Disconnect( ID_TOOLPATHSAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnGeneratorSaveToolpath ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnShowAnimationControl ) );
	this->Disconnect( ID_VIEWSTEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnActivateStereo3D ) );
	this->Disconnect( ID_CLOSEEXTRAWINDOWS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnExtraWindowClose ) );
	this->Disconnect( ID_LOGSHOW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnShowLogWindow ) );
	this->Disconnect( ID_VIEWTOP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Disconnect( ID_VIEWBOTTOM, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Disconnect( ID_VIEWFRONT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Disconnect( ID_VIEWBACK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Disconnect( ID_VIEWRIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Disconnect( ID_VIEWLEFT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewSet ) );
	this->Disconnect( ID_TESTGCODE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnTestGCode ) );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnBeginLabelEdit ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( GUIFrameMain::OnEndLabelEdit ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( GUIFrameMain::OnActivate ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( GUIFrameMain::OnActivateRightClickMenu ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIFrameMain::OnSelectionChanged ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGING, wxTreeEventHandler( GUIFrameMain::OnSelectionChanging ), NULL, this );
	m_canvas->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUIFrameMain::On3DDClick ), NULL, this );
	m_canvas->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIFrameMain::On3DSelect ), NULL, this );
	
}

GUIObjectTransformation::GUIObjectTransformation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuObject = new wxMenu();
	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menuObject, ID_OBJECTLOAD, wxString( _("&Load Object") ) + wxT('\t') + wxT("Ctrl+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemOpen );
	
	wxMenuItem* m_menuItemObjectRename;
	m_menuItemObjectRename = new wxMenuItem( m_menuObject, ID_OBJECTRENAME, wxString( _("&Rename Object") ) + wxT('\t') + wxT("Ctrl+R"), wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemObjectRename );
	
	wxMenuItem* m_menuItemFlipNormals;
	m_menuItemFlipNormals = new wxMenuItem( m_menuObject, ID_OBJECTFLIPNORMALS, wxString( _("Flip normal vectors") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemFlipNormals );
	
	m_menuObject->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuObject, wxID_CLOSE, wxString( _("&Close Window") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuObject->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuObject, _("&Object") ); 
	
	m_menuEdit = new wxMenu();
	wxMenuItem* m_menuItemUndo;
	m_menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( _("Undo") ) + wxT('\t') + wxT("CTRL+Z"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemUndo );
	
	wxMenuItem* m_menuItemRedo;
	m_menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( _("Redo") ) + wxT('\t') + wxT("CTRL+Y"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemRedo );
	
	m_menubar->Append( m_menuEdit, _("&Edit") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxHORIZONTAL );
	
	m_colourPickerObject = new wxColourPickerCtrl( this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	bSizerTop->Add( m_colourPickerObject, 0, wxALL, 5 );
	
	wxArrayString m_choiceObjectSelectionChoices;
	m_choiceObjectSelection = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceObjectSelectionChoices, 0 );
	m_choiceObjectSelection->SetSelection( 0 );
	bSizerTop->Add( m_choiceObjectSelection, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( bSizerTop, 0, wxEXPAND, 5 );
	
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
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnClose ) );
	m_colourPickerObject->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUIObjectTransformation::OnChangeObjectColor ), NULL, this );
	m_choiceObjectSelection->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnSelectObject ), NULL, this );
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
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnClose ) );
	m_colourPickerObject->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUIObjectTransformation::OnChangeObjectColor ), NULL, this );
	m_choiceObjectSelection->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIObjectTransformation::OnSelectObject ), NULL, this );
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

GUIStockMaterial::GUIStockMaterial( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItemLoadStock;
	m_menuItemLoadStock = new wxMenuItem( m_menuStock, ID_STOCKLOAD, wxString( _("&Load Stocklist...") ) + wxT('\t') + wxT("Ctrl+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemLoadStock );
	
	wxMenuItem* m_menuItemSaveStock;
	m_menuItemSaveStock = new wxMenuItem( m_menuStock, ID_STOCKSAVE, wxString( _("&Save Stocklist...") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemSaveStock );
	
	m_menuStock->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuStock, wxID_CLOSE, wxString( _("&Close Window") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuStock, _("&Stock") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizerTop->Add( 0, 0, 1, 0, 5 );
	
	m_staticText96 = new wxStaticText( this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText96->Wrap( -1 );
	bSizerTop->Add( m_staticText96, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTop->Add( m_textCtrlName, 1, wxALL, 5 );
	
	
	bSizerTop->Add( 0, 0, 1, 0, 5 );
	
	
	bSizerMain->Add( bSizerTop, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerSize;
	bSizerSize = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizerCols;
	fgSizerCols = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizerCols->SetFlexibleDirection( wxBOTH );
	fgSizerCols->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText27 = new wxStaticText( this, wxID_ANY, _("Length (in X):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizerCols->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlX = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizerCols->Add( m_textCtrlX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	fgSizerCols->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText29 = new wxStaticText( this, wxID_ANY, _("Width (in Y):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizerCols->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlY = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizerCols->Add( m_textCtrlY, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	fgSizerCols->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText31 = new wxStaticText( this, wxID_ANY, _("Height (in Z):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizerCols->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlZ = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizerCols->Add( m_textCtrlZ, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	fgSizerCols->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerSize->Add( fgSizerCols, 0, 0, 5 );
	
	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, _("Max speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer13->Add( m_staticText33, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer13->Add( m_textCtrlMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitRotationalSpeed = new wxStaticText( this, wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRotationalSpeed->Wrap( -1 );
	fgSizer13->Add( m_staticTextUnitRotationalSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText35 = new wxStaticText( this, wxID_ANY, _("Max feedrate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer13->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlMaxFeedrate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	fgSizer13->Add( m_textCtrlMaxFeedrate, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitLinearSpeed = new wxStaticText( this, wxID_ANY, _("mm/s"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitLinearSpeed->Wrap( -1 );
	fgSizer13->Add( m_staticTextUnitLinearSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer53->Add( fgSizer13, 0, 0, 5 );
	
	
	bSizerSize->Add( bSizer53, 0, wxALIGN_BOTTOM, 5 );
	
	
	bSizerMain->Add( bSizerSize, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxAvailable = new wxCheckBox( this, wxID_ANY, _("available in workshop"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxAvailable->SetToolTip( _("Pieces of stock material can be set to \"available\". This allows the (not yet written) autosetup function to know what is really available in the workshop. Thus stock that is not available needs not to be deleted.") );
	
	bSizerMain->Add( m_checkBoxAvailable, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonStockAdd = new wxButton( this, wxID_ANY, _("Add / Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonStockAdd, 0, wxALL, 5 );
	
	m_buttonStockDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonStockDelete, 0, wxALL, 5 );
	
	
	bSizerMain->Add( bSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizerMain->Add( m_listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIStockMaterial::OnXClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIStockMaterial::OnSize ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIStockMaterial::OnClose ) );
	m_buttonStockAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIStockMaterial::OnAddUpdate ), NULL, this );
	m_buttonStockDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIStockMaterial::OnDelete ), NULL, this );
	m_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( GUIStockMaterial::OnActivate ), NULL, this );
	m_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIStockMaterial::OnSelected ), NULL, this );
}

GUIStockMaterial::~GUIStockMaterial()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIStockMaterial::OnXClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIStockMaterial::OnSize ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIStockMaterial::OnClose ) );
	m_buttonStockAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIStockMaterial::OnAddUpdate ), NULL, this );
	m_buttonStockDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIStockMaterial::OnDelete ), NULL, this );
	m_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( GUIStockMaterial::OnActivate ), NULL, this );
	m_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( GUIStockMaterial::OnSelected ), NULL, this );
	
}

GUIWorkpiece::GUIWorkpiece( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuStock = new wxMenu();
	wxMenuItem* m_menuItemManageStock;
	m_menuItemManageStock = new wxMenuItem( m_menuStock, ID_STOCKORGANIZE, wxString( _("&Manage Stock") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemManageStock );
	
	m_menuStock->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuStock, wxID_CLOSE, wxString( _("&Close") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuStock->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuStock, _("&Stock") ); 
	
	m_menuEdit = new wxMenu();
	wxMenuItem* m_menuItemUndo;
	m_menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("CTRL+Z"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemUndo );
	
	wxMenuItem* m_menuItemRedo;
	m_menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( _("&Redo") ) + wxT('\t') + wxT("CTRL+Y"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemRedo );
	
	m_menubar->Append( m_menuEdit, _("&Edit") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextStock = new wxStaticText( this, wxID_ANY, _("Stock:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextStock->Wrap( -1 );
	bSizerTop->Add( m_staticTextStock, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceStockChoices;
	m_choiceStock = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStockChoices, 0 );
	m_choiceStock->SetSelection( 0 );
	bSizerTop->Add( m_choiceStock, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonAdd = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTop->Add( m_buttonAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerMain->Add( bSizerTop, 0, wxEXPAND, 5 );
	
	m_grid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_grid->CreateGrid( 2, 2 );
	m_grid->EnableEditing( false );
	m_grid->EnableGridLines( true );
	m_grid->EnableDragGridSize( false );
	m_grid->SetMargins( 0, 0 );
	
	// Columns
	m_grid->EnableDragColMove( false );
	m_grid->EnableDragColSize( true );
	m_grid->SetColLabelSize( 30 );
	m_grid->SetColLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Rows
	m_grid->EnableDragRowSize( true );
	m_grid->SetRowLabelSize( 60 );
	m_grid->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_grid->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	bSizerMain->Add( m_grid, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIWorkpiece::OnXClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIWorkpiece::OnSize ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIWorkpiece::OnClose ) );
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIWorkpiece::OnAddStock ), NULL, this );
	m_grid->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUIWorkpiece::OnDBLClick ), NULL, this );
	m_grid->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIWorkpiece::OnSize ), NULL, this );
}

GUIWorkpiece::~GUIWorkpiece()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIWorkpiece::OnXClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIWorkpiece::OnSize ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIWorkpiece::OnClose ) );
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIWorkpiece::OnAddStock ), NULL, this );
	m_grid->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUIWorkpiece::OnDBLClick ), NULL, this );
	m_grid->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIWorkpiece::OnSize ), NULL, this );
	
}

GUIPlacement::GUIPlacement( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuPlacement = new wxMenu();
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuPlacement, wxID_CLOSE, wxString( _("&Close") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuPlacement->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuPlacement, _("&Placement") ); 
	
	m_menuEdit = new wxMenu();
	wxMenuItem* m_menuItemUndo;
	m_menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("CTRL+Z"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemUndo );
	
	wxMenuItem* m_menuItemRedo;
	m_menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( _("&Redo") ) + wxT('\t') + wxT("CTRL+Y"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemRedo );
	
	m_menubar->Append( m_menuEdit, _("&Edit") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxVERTICAL );
	
	wxArrayString m_choiceWorkpieceChoices;
	m_choiceWorkpiece = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceWorkpieceChoices, 0 );
	m_choiceWorkpiece->SetSelection( 0 );
	bSizer68->Add( m_choiceWorkpiece, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_choicePlacementChoices;
	m_choicePlacement = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choicePlacementChoices, 0 );
	m_choicePlacement->SetSelection( 0 );
	bSizer68->Add( m_choicePlacement, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer68->Add( 0, 0, 1, 0, 5 );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText100 = new wxStaticText( this, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText100->Wrap( -1 );
	bSizer69->Add( m_staticText100, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlX = new wxTextCtrl( this, ID_POSX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer69->Add( m_textCtrlX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitX = new wxStaticText( this, wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX->Wrap( -1 );
	bSizer69->Add( m_staticTextUnitX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText102 = new wxStaticText( this, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText102->Wrap( -1 );
	bSizer69->Add( m_staticText102, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlY = new wxTextCtrl( this, ID_POSY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer69->Add( m_textCtrlY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitY = new wxStaticText( this, wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY->Wrap( -1 );
	bSizer69->Add( m_staticTextUnitY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText104 = new wxStaticText( this, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText104->Wrap( -1 );
	bSizer69->Add( m_staticText104, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlZ = new wxTextCtrl( this, ID_POSZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer69->Add( m_textCtrlZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitZ = new wxStaticText( this, wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ->Wrap( -1 );
	bSizer69->Add( m_staticTextUnitZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer68->Add( bSizer69, 0, 0, 5 );
	
	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText106 = new wxStaticText( this, wxID_ANY, _("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText106->Wrap( -1 );
	bSizer70->Add( m_staticText106, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAngle = new wxTextCtrl( this, ID_ANGLE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer70->Add( m_textCtrlAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextunitAngle = new wxStaticText( this, wxID_ANY, _("deg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextunitAngle->Wrap( -1 );
	bSizer70->Add( m_staticTextunitAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sliderAngle = new wxSlider( this, wxID_ANY, 0, -180, 180, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer70->Add( m_sliderAngle, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer68->Add( bSizer70, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxContour = new wxCheckBox( this, ID_FORMCONTOUR, _("Contour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxContour->SetValue(true); 
	m_checkBoxContour->SetToolTip( _("Only remove the material in the close vincinity of the object.") );
	
	bSizer71->Add( m_checkBoxContour, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText108 = new wxStaticText( this, wxID_ANY, _("Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText108->Wrap( -1 );
	bSizer71->Add( m_staticText108, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDistance = new wxTextCtrl( this, ID_DISTANCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer71->Add( m_textCtrlDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitDistance = new wxStaticText( this, wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDistance->Wrap( -1 );
	bSizer71->Add( m_staticTextUnitDistance, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer71->Add( 0, 0, 1, 0, 5 );
	
	
	bSizer68->Add( bSizer71, 0, wxEXPAND, 5 );
	
	
	bSizer66->Add( bSizer68, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 3, 0, 0 );
	
	
	gSizer1->Add( 0, 0, 1, 0, 5 );
	
	m_bpButtonYP = new wxBitmapButton( this, ID_MOVEYP, wxBitmap( arrowyu_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButtonYP, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	gSizer1->Add( 0, 0, 1, 0, 5 );
	
	m_bpButtonXN = new wxBitmapButton( this, ID_MOVEXN, wxBitmap( arrowxn_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButtonXN, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	gSizer1->Add( 0, 0, 1, 0, 5 );
	
	m_bpButtonXP = new wxBitmapButton( this, ID_MOVEXP, wxBitmap( arrowxp_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButtonXP, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	gSizer1->Add( 0, 0, 1, 0, 5 );
	
	m_bpButtonYM = new wxBitmapButton( this, ID_MOVEYN, wxBitmap( arrowyd_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButtonYM, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	gSizer1->Add( 0, 0, 1, 0, 5 );
	
	
	bSizer66->Add( gSizer1, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonAlignTop = new wxButton( this, ID_ALIGNTOP, _("Align with Top"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer67->Add( m_buttonAlignTop, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonAlignMiddle = new wxButton( this, ID_ALIGNMIDDLE, _("Align with Middle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer67->Add( m_buttonAlignMiddle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonAlignBottom = new wxButton( this, ID_ALIGNBOTTOM, _("Align with Bottom"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer67->Add( m_buttonAlignBottom, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer66->Add( bSizer67, 0, wxALIGN_BOTTOM, 5 );
	
	
	bSizerMain->Add( bSizer66, 0, wxEXPAND, 5 );
	
	m_topview = new PanelTopView(this);
	bSizerMain->Add( m_topview, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIPlacement::OnXClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIPlacement::OnSize ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIPlacement::OnClose ) );
	m_choiceWorkpiece->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIPlacement::OnSelectWorkpiece ), NULL, this );
	m_choicePlacement->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIPlacement::OnSelectObject ), NULL, this );
	m_textCtrlX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlZ->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlAngle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_sliderAngle->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIPlacement::OnChangeSlider ), NULL, this );
	m_checkBoxContour->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlDistance->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_bpButtonYP->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_bpButtonXN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_bpButtonXP->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_bpButtonYM->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_buttonAlignTop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_buttonAlignMiddle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_buttonAlignBottom->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
}

GUIPlacement::~GUIPlacement()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIPlacement::OnXClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIPlacement::OnSize ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIPlacement::OnClose ) );
	m_choiceWorkpiece->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIPlacement::OnSelectWorkpiece ), NULL, this );
	m_choicePlacement->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIPlacement::OnSelectObject ), NULL, this );
	m_textCtrlX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlZ->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlAngle->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_sliderAngle->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIPlacement::OnChangeSlider ), NULL, this );
	m_checkBoxContour->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_textCtrlDistance->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPlacement::OnChange ), NULL, this );
	m_bpButtonYP->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_bpButtonXN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_bpButtonXP->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_bpButtonYM->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_buttonAlignTop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_buttonAlignMiddle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	m_buttonAlignBottom->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPlacement::OnTransform ), NULL, this );
	
}

GUIRun::GUIRun( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuToolbox = new wxMenu();
	wxMenuItem* m_menuItemToolboxLoad;
	m_menuItemToolboxLoad = new wxMenuItem( m_menuToolbox, ID_TOOLBOXLOAD, wxString( _("&Load Toolbox") ) + wxT('\t') + wxT("Ctrl+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemToolboxLoad );
	
	m_menuToolbox->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuToolbox, wxID_CLOSE, wxString( _("&Close Window") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuToolbox->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuToolbox, _("&Toolbox") ); 
	
	m_menuEdit = new wxMenu();
	wxMenuItem* m_menuItemUndo;
	m_menuItemUndo = new wxMenuItem( m_menuEdit, wxID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("CTRL+Z"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemUndo );
	
	wxMenuItem* m_menuItemRedo;
	m_menuItemRedo = new wxMenuItem( m_menuEdit, wxID_REDO, wxString( _("&Redo") ) + wxT('\t') + wxT("CTRL+Y"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemRedo );
	
	m_menubar->Append( m_menuEdit, _("Edit") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxArrayString m_choiceRunChoices;
	m_choiceRun = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceRunChoices, 0 );
	m_choiceRun->SetSelection( 0 );
	bSizer->Add( m_choiceRun, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerStock;
	sbSizerStock = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Workpiece") ), wxVERTICAL );
	
	wxArrayString m_choiceWorkpieceChoices;
	m_choiceWorkpiece = new wxChoice( sbSizerStock->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceWorkpieceChoices, 0 );
	m_choiceWorkpiece->SetSelection( 0 );
	sbSizerStock->Add( m_choiceWorkpiece, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRotateButtons;
	bSizerRotateButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonRotX90 = new wxButton( sbSizerStock->GetStaticBox(), ID_WORKPIECEROTATEX, _("rotate X"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerRotateButtons->Add( m_buttonRotX90, 0, wxALL, 5 );
	
	m_buttonRotY90 = new wxButton( sbSizerStock->GetStaticBox(), ID_WORKPIECEROTATEY, _("rotate Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRotY90->Enable( false );
	
	bSizerRotateButtons->Add( m_buttonRotY90, 0, wxALL, 5 );
	
	m_buttonRotZ90 = new wxButton( sbSizerStock->GetStaticBox(), ID_WORKPIECEROTATEZ, _("rotate Z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRotZ90->Enable( false );
	
	bSizerRotateButtons->Add( m_buttonRotZ90, 0, wxALL, 5 );
	
	
	sbSizerStock->Add( bSizerRotateButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer->Add( sbSizerStock, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerMachine;
	sbSizerMachine = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Machine") ), wxVERTICAL );
	
	wxBoxSizer* bSizerMachine;
	bSizerMachine = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlMachineName = new wxTextCtrl( sbSizerMachine->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizerMachine->Add( m_textCtrlMachineName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonLoadMachine = new wxButton( sbSizerMachine->GetStaticBox(), wxID_ANY, _("Load Machine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMachine->Add( m_buttonLoadMachine, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	sbSizerMachine->Add( bSizerMachine, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerToolslots;
	bSizerToolslots = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerToolsAvailable;
	bSizerToolsAvailable = new wxBoxSizer( wxVERTICAL );
	
	m_statiTextToolsAvailable = new wxStaticText( sbSizerMachine->GetStaticBox(), wxID_ANY, _("Tools available"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiTextToolsAvailable->Wrap( -1 );
	bSizerToolsAvailable->Add( m_statiTextToolsAvailable, 0, wxALL, 5 );
	
	m_listBoxTool = new wxListBox( sbSizerMachine->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SINGLE ); 
	bSizerToolsAvailable->Add( m_listBoxTool, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerAddTool;
	bSizerAddTool = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextToolSlot = new wxStaticText( sbSizerMachine->GetStaticBox(), wxID_ANY, _("Into toolslot:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolSlot->Wrap( -1 );
	bSizerAddTool->Add( m_staticTextToolSlot, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrlToolSlot = new wxSpinCtrl( sbSizerMachine->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1 );
	bSizerAddTool->Add( m_spinCtrlToolSlot, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonToolAdd = new wxButton( sbSizerMachine->GetStaticBox(), wxID_ANY, _("Add to Machine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAddTool->Add( m_buttonToolAdd, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerToolsAvailable->Add( bSizerAddTool, 0, wxEXPAND, 5 );
	
	
	bSizerToolslots->Add( bSizerToolsAvailable, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerToolsInMachine;
	bSizerToolsInMachine = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextToolsInMachine = new wxStaticText( sbSizerMachine->GetStaticBox(), wxID_ANY, _("Tools in machine"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToolsInMachine->Wrap( -1 );
	bSizerToolsInMachine->Add( m_staticTextToolsInMachine, 0, wxALL, 5 );
	
	m_listCtrlTools = new wxListCtrl( sbSizerMachine->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizerToolsInMachine->Add( m_listCtrlTools, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonToolDelete = new wxButton( sbSizerMachine->GetStaticBox(), wxID_ANY, _("Remove from Machine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerToolsInMachine->Add( m_buttonToolDelete, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	bSizerToolslots->Add( bSizerToolsInMachine, 1, wxEXPAND, 5 );
	
	
	sbSizerMachine->Add( bSizerToolslots, 1, wxEXPAND, 5 );
	
	
	bSizer->Add( sbSizerMachine, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIRun::OnXClose ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIRun::OnClose ) );
	m_choiceRun->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIRun::OnRunSelect ), NULL, this );
	m_choiceWorkpiece->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIRun::OnWorkpieceSelect ), NULL, this );
	m_buttonRotX90->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnRotate ), NULL, this );
	m_buttonRotY90->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnRotate ), NULL, this );
	m_buttonRotZ90->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnRotate ), NULL, this );
	m_buttonLoadMachine->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnMachineLoad ), NULL, this );
	m_buttonToolAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnToolAdd ), NULL, this );
	m_buttonToolDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnToolRemove ), NULL, this );
}

GUIRun::~GUIRun()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIRun::OnXClose ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIRun::OnClose ) );
	m_choiceRun->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIRun::OnRunSelect ), NULL, this );
	m_choiceWorkpiece->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIRun::OnWorkpieceSelect ), NULL, this );
	m_buttonRotX90->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnRotate ), NULL, this );
	m_buttonRotY90->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnRotate ), NULL, this );
	m_buttonRotZ90->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnRotate ), NULL, this );
	m_buttonLoadMachine->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnMachineLoad ), NULL, this );
	m_buttonToolAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnToolAdd ), NULL, this );
	m_buttonToolDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRun::OnToolRemove ), NULL, this );
	
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

GUIToolbox::GUIToolbox( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuTools = new wxMenu();
	wxMenuItem* m_menuItemToolboxLoad;
	m_menuItemToolboxLoad = new wxMenuItem( m_menuTools, ID_TOOLBOXLOAD, wxString( _("&Load Toolbox") ) + wxT('\t') + wxT("CTRL+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItemToolboxLoad );
	
	wxMenuItem* m_menuItemToolboxSave;
	m_menuItemToolboxSave = new wxMenuItem( m_menuTools, ID_TOOLBOXSAVE, wxString( _("&Save Toolbox") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItemToolboxSave );
	
	m_menuTools->AppendSeparator();
	
	wxMenuItem* m_menuItemWizard;
	m_menuItemWizard = new wxMenuItem( m_menuTools, wxID_ANY, wxString( _("Shape &Wizard") ) + wxT('\t') + wxT("Ctrl+Shift+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItemWizard );
	
	m_menuTools->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuTools, wxID_CLOSE, wxString( _("&Close Window") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuTools, _("&Tools") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("&Preferences") ); 
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemStereo3D;
	m_menuItemStereo3D = new wxMenuItem( m_menuView, ID_VIEWSTEREO3D, wxString( _("&Stereo 3D") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemStereo3D );
	m_menuItemStereo3D->Enable( false );
	
	m_menubar->Append( m_menuView, _("&View") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBoxToolSelector = new wxComboBox( this, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER ); 
	bSizerTop->Add( m_comboBoxToolSelector, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonToolNew = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTop->Add( m_buttonToolNew, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_buttonToolUpdate = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTop->Add( m_buttonToolUpdate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonToolDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTop->Add( m_buttonToolDelete, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizerTop, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizerMain;
	fgSizerMain = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerMain->AddGrowableCol( 1 );
	fgSizerMain->AddGrowableRow( 0 );
	fgSizerMain->AddGrowableRow( 1 );
	fgSizerMain->SetFlexibleDirection( wxBOTH );
	fgSizerMain->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool definition") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 5, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Shaft diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftDiameter = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftDiameter->SetToolTip( _("Diameter of the part that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftDiameter, 0, wxALL, 5 );
	
	m_staticTextUnitShaftDiameter = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftDiameter->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitShaftDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText10 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Shaft length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShaftLength = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlShaftLength->SetToolTip( _("This is the length of the that disappears inside the chuck.") );
	
	fgSizer1->Add( m_textCtrlShaftLength, 0, wxALL, 5 );
	
	m_staticTextUnitShaftLength = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitShaftLength->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitShaftLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText13 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Maximum speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer1->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMaxSpeed = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMaxSpeed->SetToolTip( _("Max. speed: Look at label on box you got the tools shipped in.") );
	
	fgSizer1->Add( m_textCtrlMaxSpeed, 0, wxALL, 5 );
	
	m_staticTextUnitMaxSpeed = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("rpm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMaxSpeed->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitMaxSpeed, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText14 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Feed coefficient:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFeedCoefficient = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlFeedCoefficient->SetToolTip( _("Feed per tooth: How deep can a tooth cut per revolution. Usually in the range of 0.02 mm to 0.05 mm.") );
	
	fgSizer1->Add( m_textCtrlFeedCoefficient, 0, wxALL, 5 );
	
	m_staticTextUnitFeedCoefficient = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFeedCoefficient->Wrap( -1 );
	fgSizer1->Add( m_staticTextUnitFeedCoefficient, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextFlutes = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Number of flutes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFlutes->Wrap( -1 );
	fgSizer1->Add( m_staticTextFlutes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlNrOfTeeth = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlNrOfTeeth->SetToolTip( _("Number of teeth around the cutter.") );
	
	fgSizer1->Add( m_textCtrlNrOfTeeth, 0, wxALL, 5 );
	
	
	fgSizer1->Add( 0, 0, 1, 0, 5 );
	
	
	sbSizer1->Add( fgSizer1, 0, 0, 5 );
	
	m_staticText26 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Comment:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	sbSizer1->Add( m_staticText26, 0, wxALL, 5 );
	
	m_textCtrlComment = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_ENTER|wxTE_WORDWRAP );
	sbSizer1->Add( m_textCtrlComment, 1, wxALL|wxEXPAND, 5 );
	
	
	fgSizerMain->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	m_panel=new PanelTool(this);
	fgSizerMain->Add( m_panel, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool shape") ), wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonShapeNew = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonShapeNew, 0, wxALL, 5 );
	
	m_buttonShapeUpdate = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonShapeUpdate, 0, wxALL, 5 );
	
	m_buttonShapeDelete = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonShapeDelete, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 0, 0, 5 );
	
	wxString m_choiceTypeChoices[] = { _("Linear or bend line"), _("Corner: first diameter change, then height change"), _("Corner: first height change, then diameter change"), _("Sphere: radius at upper limit, calculate height"), _("Sphere: radius at lower limit, calculate height") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	bSizer3->Add( m_choiceType, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 4, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlDiameter = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlDiameter->SetToolTip( _("Diameter of the tool at the end of this segment.") );
	
	fgSizer2->Add( m_textCtrlDiameter, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitDiameter = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer2->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHeight = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlHeight->SetToolTip( _("Height of this segment.") );
	
	fgSizer2->Add( m_textCtrlHeight, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitHeight = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitHeight->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRadius = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlRadius->SetToolTip( _("Radius of curvature:\nPositive radius = convex surface = bulged to the outside.\nNegative radius = concave surface = bulged to the inside.\nRadius of 0 = straight line. ") );
	
	fgSizer2->Add( m_textCtrlRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitRadius = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitRadius->Wrap( -1 );
	fgSizer2->Add( m_staticTextUnitRadius, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, 0, 5 );
	
	m_checkBoxCutting = new wxCheckBox( sbSizer2->GetStaticBox(), wxID_ANY, _("surface is cutting"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_checkBoxCutting, 0, wxALL, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, 0, 5 );
	
	
	bSizer3->Add( fgSizer2, 0, 0, 5 );
	
	
	bSizer2->Add( bSizer3, 0, 0, 5 );
	
	m_listCtrl = new wxListCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_NO_SORT_HEADER|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer2->Add( m_listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	
	sbSizer2->Add( bSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizerMain->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	m_canvas = new CanvasTool(this);
	fgSizerMain->Add( m_canvas, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer->Add( fgSizerMain, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolbox::OnXClose ) );
	this->Connect( m_menuItemWizard->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnShapeWizard ) );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnClose ) );
	this->Connect( m_menuItemStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnChangeStereo3D ) );
	m_comboBoxToolSelector->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUIToolbox::OnToolSelect ), NULL, this );
	m_comboBoxToolSelector->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnToolRename ), NULL, this );
	m_buttonToolNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnToolNew ), NULL, this );
	m_buttonToolUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnToolUpdate ), NULL, this );
	m_buttonToolDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnToolDelete ), NULL, this );
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
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnShapeWizard ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnClose ) );
	this->Disconnect( ID_VIEWSTEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIToolbox::OnChangeStereo3D ) );
	m_comboBoxToolSelector->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUIToolbox::OnToolSelect ), NULL, this );
	m_comboBoxToolSelector->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIToolbox::OnToolRename ), NULL, this );
	m_buttonToolNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnToolNew ), NULL, this );
	m_buttonToolUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnToolUpdate ), NULL, this );
	m_buttonToolDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolbox::OnToolDelete ), NULL, this );
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

GUIToolWizard::GUIToolWizard( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxToolTypeChoices[] = { _("Flat nose (cylindric)"), _("Ball nose (spheric)"), _("Bull nose (mixing ball and flat)"), _("Camfer (triangle)") };
	int m_radioBoxToolTypeNChoices = sizeof( m_radioBoxToolTypeChoices ) / sizeof( wxString );
	m_radioBoxToolType = new wxRadioBox( this, wxID_ANY, _("Type"), wxDefaultPosition, wxDefaultSize, m_radioBoxToolTypeNChoices, m_radioBoxToolTypeChoices, 2, wxRA_SPECIFY_ROWS );
	m_radioBoxToolType->SetSelection( 0 );
	bSizer87->Add( m_radioBoxToolType, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxStaticBoxSizer* sbSizer25;
	sbSizer25 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Parameter") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText128 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText128->Wrap( -1 );
	fgSizer16->Add( m_staticText128, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl68 = new wxTextCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer16->Add( m_textCtrl68, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText129 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText129->Wrap( -1 );
	fgSizer16->Add( m_staticText129, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText134 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("Tip diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText134->Wrap( -1 );
	m_staticText134->Enable( false );
	
	fgSizer16->Add( m_staticText134, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl71 = new wxTextCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl71->Enable( false );
	
	fgSizer16->Add( m_textCtrl71, 0, wxALL, 5 );
	
	m_staticText135 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText135->Wrap( -1 );
	m_staticText135->Enable( false );
	
	fgSizer16->Add( m_staticText135, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText138 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("Shaft Diameter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText138->Wrap( -1 );
	fgSizer16->Add( m_staticText138, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl73 = new wxTextCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer16->Add( m_textCtrl73, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText139 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText139->Wrap( -1 );
	fgSizer16->Add( m_staticText139, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline1 = new wxStaticLine( sbSizer25->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer16->Add( m_staticline1, 0, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_staticline2 = new wxStaticLine( sbSizer25->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer16->Add( m_staticline2, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_staticline3 = new wxStaticLine( sbSizer25->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer16->Add( m_staticline3, 0, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_staticText130 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("Length outside chuck:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText130->Wrap( -1 );
	fgSizer16->Add( m_staticText130, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl69 = new wxTextCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer16->Add( m_textCtrl69, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText131 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	fgSizer16->Add( m_staticText131, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText136 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("Length cutting:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText136->Wrap( -1 );
	fgSizer16->Add( m_staticText136, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl72 = new wxTextCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer16->Add( m_textCtrl72, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText137 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText137->Wrap( -1 );
	fgSizer16->Add( m_staticText137, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText132 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("Total tool length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText132->Wrap( -1 );
	fgSizer16->Add( m_staticText132, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl70 = new wxTextCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer16->Add( m_textCtrl70, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText133 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText133->Wrap( -1 );
	fgSizer16->Add( m_staticText133, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer25->Add( fgSizer16, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer87->Add( sbSizer25, 1, wxEXPAND, 5 );
	
	
	bSizer->Add( bSizer87, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAdd = new wxButton( this, wxID_ANY, _("Add new tool"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonAdd->SetToolTip( _("Add a new tool to the toolbox.") );
	
	bSizerButtons->Add( m_buttonAdd, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonSetShape = new wxButton( this, wxID_ANY, _("Update shape of current tool"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonSetShape->SetToolTip( _("Overwrite the shape of the current tool.") );
	
	bSizerButtons->Add( m_buttonSetShape, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonClose, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizerButtons, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolWizard::OnAddTool ), NULL, this );
	m_buttonSetShape->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolWizard::OnSetShape ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolWizard::OnClose ), NULL, this );
}

GUIToolWizard::~GUIToolWizard()
{
	// Disconnect Events
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolWizard::OnAddTool ), NULL, this );
	m_buttonSetShape->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolWizard::OnSetShape ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolWizard::OnClose ), NULL, this );
	
}

GUIToolpathGenerator::GUIToolpathGenerator( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerRun;
	bSizerRun = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText125 = new wxStaticText( this, wxID_ANY, _("Run:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText125->Wrap( -1 );
	bSizerRun->Add( m_staticText125, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceRunChoices;
	m_choiceRun = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceRunChoices, 0 );
	m_choiceRun->SetSelection( 0 );
	bSizerRun->Add( m_choiceRun, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( bSizerRun, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerGenerator;
	bSizerGenerator = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText145 = new wxStaticText( this, wxID_ANY, _("Generator:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText145->Wrap( -1 );
	bSizerGenerator->Add( m_staticText145, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceToolpathChoices;
	m_choiceToolpath = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceToolpathChoices, 0 );
	m_choiceToolpath->SetSelection( 0 );
	bSizerGenerator->Add( m_choiceToolpath, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonAddNew = new wxButton( this, wxID_ANY, _("Add New"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonAddNew->SetToolTip( _("Add a new empty generator below the current one.") );
	
	bSizerGenerator->Add( m_buttonAddNew, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( bSizerGenerator, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer851;
	bSizer851 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerArea;
	sbSizerArea = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Area:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerAreaCorrdinates;
	fgSizerAreaCorrdinates = new wxFlexGridSizer( 3, 6, 0, 0 );
	fgSizerAreaCorrdinates->AddGrowableCol( 1 );
	fgSizerAreaCorrdinates->AddGrowableCol( 4 );
	fgSizerAreaCorrdinates->SetFlexibleDirection( wxBOTH );
	fgSizerAreaCorrdinates->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextX = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("X start:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextX->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextX, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlX1 = new wxTextCtrl( sbSizerArea->GetStaticBox(), ID_XSTART, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerAreaCorrdinates->Add( m_textCtrlX1, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitX1 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX1->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextUnitX1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText130 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("end:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText130->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticText130, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlX2 = new wxTextCtrl( sbSizerArea->GetStaticBox(), ID_XEND, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerAreaCorrdinates->Add( m_textCtrlX2, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitX2 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitX2->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextUnitX2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextY = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("Y start:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextY->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextY, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlY1 = new wxTextCtrl( sbSizerArea->GetStaticBox(), ID_YSTART, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerAreaCorrdinates->Add( m_textCtrlY1, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitY1 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY1->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextUnitY1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText132 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("end:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText132->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticText132, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlY2 = new wxTextCtrl( sbSizerArea->GetStaticBox(), ID_YEND, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerAreaCorrdinates->Add( m_textCtrlY2, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitY2 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitY2->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextUnitY2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextZ = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("Z start:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextZ->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextZ, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlZ1 = new wxTextCtrl( sbSizerArea->GetStaticBox(), ID_ZSTART, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerAreaCorrdinates->Add( m_textCtrlZ1, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitZ1 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ1->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextUnitZ1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText1312 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("end:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1312->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticText1312, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlZ2 = new wxTextCtrl( sbSizerArea->GetStaticBox(), ID_ZEND, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizerAreaCorrdinates->Add( m_textCtrlZ2, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextUnitZ2 = new wxStaticText( sbSizerArea->GetStaticBox(), wxID_ANY, _("cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitZ2->Wrap( -1 );
	fgSizerAreaCorrdinates->Add( m_staticTextUnitZ2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerArea->Add( fgSizerAreaCorrdinates, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerAreaSelect;
	bSizerAreaSelect = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonSelectAreaFromObject = new wxButton( sbSizerArea->GetStaticBox(), ID_SELECTAREAOBJECT, _("from Object ..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAreaSelect->Add( m_buttonSelectAreaFromObject, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerArea->Add( bSizerAreaSelect, 0, 0, 5 );
	
	
	bSizer851->Add( sbSizerArea, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerMargin;
	sbSizerMargin = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Margin:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextSide = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Side:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSide->Wrap( -1 );
	fgSizer18->Add( m_staticTextSide, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlMarginSide = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_MARGINSIDE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer18->Add( m_textCtrlMarginSide, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitMarginSide = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMarginSide->Wrap( -1 );
	fgSizer18->Add( m_staticTextUnitMarginSide, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBelow = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("Below:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBelow->Wrap( -1 );
	fgSizer18->Add( m_staticTextBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlMarginBelow = new wxTextCtrl( sbSizerMargin->GetStaticBox(), ID_MARGINBELOW, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer18->Add( m_textCtrlMarginBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextUnitMarginBelow = new wxStaticText( sbSizerMargin->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitMarginBelow->Wrap( -1 );
	fgSizer18->Add( m_staticTextUnitMarginBelow, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerMargin->Add( fgSizer18, 1, wxEXPAND, 5 );
	
	
	bSizer87->Add( sbSizerMargin, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerTool;
	sbSizerTool = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tool") ), wxVERTICAL );
	
	wxArrayString m_choiceToolChoices;
	m_choiceTool = new wxChoice( sbSizerTool->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceToolChoices, 0 );
	m_choiceTool->SetSelection( 0 );
	sbSizerTool->Add( m_choiceTool, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextDiameter = new wxStaticText( sbSizerTool->GetStaticBox(), wxID_ANY, _("Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDiameter->Wrap( -1 );
	bSizer86->Add( m_staticTextDiameter, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrlToolDiameter = new wxTextCtrl( sbSizerTool->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_READONLY );
	bSizer86->Add( m_textCtrlToolDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitDiameter = new wxStaticText( sbSizerTool->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitDiameter->Wrap( -1 );
	bSizer86->Add( m_staticTextUnitDiameter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerTool->Add( bSizer86, 0, 0, 5 );
	
	
	bSizer87->Add( sbSizerTool, 0, wxEXPAND, 5 );
	
	
	bSizer88->Add( bSizer87, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizerFreeLevel;
	sbSizerFreeLevel = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Safety distance:") ), wxVERTICAL );
	
	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextFreeHeight = new wxStaticText( sbSizerFreeLevel->GetStaticBox(), wxID_ANY, _("Free Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFreeHeight->Wrap( -1 );
	bSizer89->Add( m_staticTextFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFreeHeight = new wxTextCtrl( sbSizerFreeLevel->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer89->Add( m_textCtrlFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextUnitFreeHeight = new wxStaticText( sbSizerFreeLevel->GetStaticBox(), wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUnitFreeHeight->Wrap( -1 );
	bSizer89->Add( m_staticTextUnitFreeHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerFreeLevel->Add( bSizer89, 0, 0, 5 );
	
	
	bSizer88->Add( sbSizerFreeLevel, 1, wxEXPAND, 5 );
	
	
	bSizer851->Add( bSizer88, 0, wxEXPAND, 5 );
	
	
	bSizerMain->Add( bSizer851, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer18;
	sbSizer18 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Generator Type:") ), wxVERTICAL );
	
	m_choicebookGenerator = new wxChoicebook( sbSizer18->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
	sbSizer18->Add( m_choicebookGenerator, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizerMain->Add( sbSizer18, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonUpdate = new wxButton( this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonUpdate->SetToolTip( _("Update changes for the current generator.") );
	
	bSizerButtons->Add( m_buttonUpdate, 1, wxALL, 5 );
	
	m_buttonReset = new wxButton( this, wxID_ANY, _("Reset changes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonReset->SetToolTip( _("Reset the changes for this generator to the state of the last update.") );
	
	bSizerButtons->Add( m_buttonReset, 1, wxALL, 5 );
	
	m_buttonDelete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDelete->SetToolTip( _("Delete the current generator.") );
	
	bSizerButtons->Add( m_buttonDelete, 1, wxALL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonClose->SetToolTip( _("Close window.") );
	
	bSizerButtons->Add( m_buttonClose, 1, wxALL, 5 );
	
	
	bSizerMain->Add( bSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizerMain->Add( m_textCtrlInfo, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolpathGenerator::OnXClose ) );
	m_choiceRun->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectRun ), NULL, this );
	m_choiceToolpath->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectToolpath ), NULL, this );
	m_buttonAddNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnAdd ), NULL, this );
	m_textCtrlX1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlX2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlY1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlY2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlZ1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlZ2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_buttonSelectAreaFromObject->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectArea ), NULL, this );
	m_textCtrlMarginSide->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlMarginBelow->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_choiceTool->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectTool ), NULL, this );
	m_choicebookGenerator->Connect( wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED, wxChoicebookEventHandler( GUIToolpathGenerator::OnPageChanged ), NULL, this );
	m_buttonUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnUpdate ), NULL, this );
	m_buttonReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnResetChanges ), NULL, this );
	m_buttonDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnDelete ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnClose ), NULL, this );
}

GUIToolpathGenerator::~GUIToolpathGenerator()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIToolpathGenerator::OnXClose ) );
	m_choiceRun->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectRun ), NULL, this );
	m_choiceToolpath->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectToolpath ), NULL, this );
	m_buttonAddNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnAdd ), NULL, this );
	m_textCtrlX1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlX2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlY1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlY2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlZ1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlZ2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_buttonSelectAreaFromObject->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectArea ), NULL, this );
	m_textCtrlMarginSide->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_textCtrlMarginBelow->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIToolpathGenerator::OnChangeText ), NULL, this );
	m_choiceTool->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIToolpathGenerator::OnSelectTool ), NULL, this );
	m_choicebookGenerator->Disconnect( wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED, wxChoicebookEventHandler( GUIToolpathGenerator::OnPageChanged ), NULL, this );
	m_buttonUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnUpdate ), NULL, this );
	m_buttonReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnResetChanges ), NULL, this );
	m_buttonDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnDelete ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIToolpathGenerator::OnClose ), NULL, this );
	
}

GUIAnimation::GUIAnimation( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerRunSelect;
	bSizerRunSelect = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextRun = new wxStaticText( this, wxID_ANY, _("Run:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRun->Wrap( -1 );
	bSizerRunSelect->Add( m_staticTextRun, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceToolpathChoices[] = { _("No machine run available.") };
	int m_choiceToolpathNChoices = sizeof( m_choiceToolpathChoices ) / sizeof( wxString );
	m_choiceToolpath = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceToolpathNChoices, m_choiceToolpathChoices, 0 );
	m_choiceToolpath->SetSelection( 0 );
	bSizerRunSelect->Add( m_choiceToolpath, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer->Add( bSizerRunSelect, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerGCode;
	sbSizerGCode = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("G-Codes") ), wxVERTICAL );
	
	m_textCtrl0 = new wxTextCtrl( sbSizerGCode->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );
	sbSizerGCode->Add( m_textCtrl0, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl1 = new wxTextCtrl( sbSizerGCode->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );
	sbSizerGCode->Add( m_textCtrl1, 0, wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_textCtrl2 = new wxTextCtrl( sbSizerGCode->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );
	m_textCtrl2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNSHADOW ) );
	
	sbSizerGCode->Add( m_textCtrl2, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl3 = new wxTextCtrl( sbSizerGCode->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );
	sbSizerGCode->Add( m_textCtrl3, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl4 = new wxTextCtrl( sbSizerGCode->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );
	sbSizerGCode->Add( m_textCtrl4, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer->Add( sbSizerGCode, 0, wxEXPAND, 5 );
	
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
	
	
	bSizer->Add( 0, 0, 1, 0, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIAnimation::OnXClose ) );
	m_choiceToolpath->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIAnimation::OnSelectToolpath ), NULL, this );
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
	m_choiceToolpath->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIAnimation::OnSelectToolpath ), NULL, this );
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
	
	this->Centre( wxBOTH );
	
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
