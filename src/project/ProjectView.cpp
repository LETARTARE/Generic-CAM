/*
 * ProjectView.cpp
 *
 *  Created on: 21.12.2018
 *      Author: toby
 */

#include "ProjectView.h"

#include "../genericcam.h"
#include "../gui/FrameMain.h"
#include "../gui/FrameParent.h"
#include "../gui/IDs.h"

IMPLEMENT_DYNAMIC_CLASS(ProjectView, wxView)

wxBEGIN_EVENT_TABLE(ProjectView, wxView)
EVT_MENU(ID_REFRESHTREEVIEW, ProjectView::OnUpdateTree)
wxEND_EVENT_TABLE()

ProjectView::ProjectView() :
		wxView()
{
}

ProjectView::~ProjectView()
{
	printf("ProjectView: Destructor called...\n");
}

bool ProjectView::OnCreate(wxDocument* doc, long flags)
{
	printf("ProjectView::OnCreate(...) called...\n");

	if(!wxView::OnCreate(doc, flags)) return false;

	wxFrame* frame = wxGetApp().CreateChildFrame(this);
	wxASSERT(frame == GetFrame());

	frame->Show();
	return true;
}

bool ProjectView::OnClose(bool deleteWindow)
{
	printf("ProjectView::OnClose(%s) called...\n",
			deleteWindow? "true" : "false");

	wxDocument* doc = GetDocument();
	wxDocManager* manager = doc->GetDocumentManager();
	wxList tempDocs = manager->GetDocuments();
	wxList tempViews = doc->GetViews();

	printf("ProjectView: %lu docs, %lu views\n", tempDocs.GetCount(),
			tempViews.GetCount());

	if(!wxView::OnClose(deleteWindow)) return false;
	Activate(false);
//	GetDocument()->DeleteContents();
	wxWindow* frame = this->GetFrame();
	if(tempDocs.GetCount() <= 1 && tempViews.GetCount() <= 1 && frame != NULL){
		wxWindow* parent = frame->GetParent();
		printf("ProjectView: Posting wxID_EXIT to parent\n");
		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, wxID_EXIT);
		wxPostEvent(parent, event);
	}

	if(deleteWindow){
		printf("ProjectView: Request destruction of associated Frame\n");
		frame->Destroy();
		SetFrame(NULL);
	}
	return true;
}

void ProjectView::OnDraw(wxDC* dc)
{
	printf("ProjectView::OnDraw(...) called...\n");
}

void ProjectView::OnUpdate(wxView* sender, wxObject* hint)
{
	FrameMain* frame = wxStaticCast(GetFrame(), FrameMain);
	frame->TransferDataToWindow();
	frame->Refresh();
	wxView::OnUpdate(sender, hint);
}

void ProjectView::OnUpdateTree(wxCommandEvent& event)
{
	FrameMain* frame = wxStaticCast(GetFrame(), FrameMain);
	frame->tree->UpdateSelection();
	frame->Refresh();
}

void ProjectView::OnUpdate3D(void)
{
	FrameMain* frame = wxStaticCast(GetFrame(), FrameMain);
	FrameParent* parentframe = wxStaticCast(frame->GetParent(), FrameParent);
	parentframe->settings.WriteToCanvas(frame->m_canvas);
	frame->m_canvas->Refresh();
}
