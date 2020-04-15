///////////////////////////////////////////////////////////////////////////////
// Name               : ProjectView.cpp
// Purpose            : View for a Project
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.12.2018
// Copyright          : (C) 2018 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#include "ProjectView.h"

//#include "../StdInclude.h"

#include "Project.h"
#include "../genericcam.h"
#include "../gui/FrameMain.h"
#include "../gui/FrameParent.h"
#include "../gui/IDs.h"
#include "../3D/OpenGLMaterial.h"
#include <map>

IMPLEMENT_DYNAMIC_CLASS(ProjectView, wxView);

wxBEGIN_EVENT_TABLE(ProjectView, wxView) EVT_MENU(ID_REFRESHTREEVIEW, ProjectView::OnUpdateTree)
wxEND_EVENT_TABLE()

ProjectView::ProjectView() :
		wxView()
{

	type = vObject;

//	displayCoordinateSystem = true;
//	displayGeometry = true;
//	displayBoundingBox = false;
//	displayMachine = false;
//	displayStock = false;
//	displayTargets = false;
//	displayToolpath = false;
//	displayOutLines = false;
//	displayAnimation = false;
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

	printf("ProjectView: %zu docs, %zu views\n", tempDocs.GetCount(),
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
	frame->TransferDataToWindow(true);
	frame->Refresh();
	wxView::OnUpdate(sender, hint);
}

void ProjectView::OnUpdateTree(wxCommandEvent& event)
{
	FrameMain* frame = wxStaticCast(GetFrame(), FrameMain);
	frame->tree->Update();
	frame->Refresh();
}

void ProjectView::OnUpdate3D(void)
{
	FrameMain* frame = wxStaticCast(GetFrame(), FrameMain);
	FrameParent* parentframe = wxStaticCast(frame->GetParent(), FrameParent);
	parentframe->settingsStereo3D.WriteToCanvas(frame->m_canvas);
	frame->m_canvas->Refresh();
}

void ProjectView::SetSelection(const Selection& selected)
{
	//	type = vIdle;
	if(selected.IsType(Selection::Object)) type = vObject;
	if(selected.IsType(Selection::Axis)) type = vObject;
	if(selected.IsType(Selection::Run)) type = vRun;
	if(selected.IsType(Selection::Generator)) type = ProjectView::vGenerator;
//	if(DEBUG) std::cout << "ProjectView::SetSelection - type = " << (int) type
//			<< ";\n";
	bool update = (this->selection != selected);
	this->selection = selected;
	if(update) OnUpdate3D();
}

void ProjectView::SetHover(const Selection& hover)
{
	bool update = (this->hover != hover);
	this->hover = hover;
	if(update) OnUpdate3D();

}

void ProjectView::Render(void) const
{
	const Project* project = wxStaticCast(GetDocument(), Project);

	if(type == vObject || type == vOrigin){
		RenderCoordinateSystem();
	}

	PaintObjects(Selection(true), OpenGLMaterial(0.3, 0.3, 1.0),
			OpenGLMaterial(0, 0, 0));

//	if(project->GetToolCount() > 0){
//		glPushMatrix();
//		glTranslatef(0.3, 0, 0);
//		project->GetTool(0).Paint();
//		glPopMatrix();
//	}

	if(type == vOrigin){
		for(std::vector <Run>::const_iterator run = project->run.begin();
				run != project->run.end(); ++run){
			run->PaintVertices();
		}
	}

	if(type == vRun || type == vGenerator){
		glPushName(Selection::BaseRun);
		for(std::vector <Run>::const_iterator run = project->run.begin();
				run != project->run.end(); ++run){
			//			if(!selection.IsBase(Selection::BaseRun, run->GetID())
			//					|| !selection.IsType(Selection::Generator)) continue;

			for(std::vector <Generator*>::const_iterator generator =
					run->generators.begin(); generator != run->generators.end();
					++generator){

//				if(!selection.Has(generator->GetID())) continue;

				(*generator)->Paint();
			}
		}
		glPopName();
	}

	if(type == vRun || type == vOrigin){
		PaintRun(Selection(true));
	}

	if(false){
		Selection both = selection + hover;
		both.Invert();
		OpenGLMaterial::EnableColors();
		PaintObjects(both, OpenGLMaterial(0.3, 0.3, 1.0),
				OpenGLMaterial(0, 0, 0));
		PaintObjects(selection, OpenGLMaterial(0.8, 0.8, 1.0),
				OpenGLMaterial(0.8, 0.8, 0.8));
		PaintObjects(hover, OpenGLMaterial(0.5, 0.5, 1.0),
				OpenGLMaterial(0.5, 0.5, 0.5));
	}
}

void ProjectView::RenderPick(void) const
{
	Project* project = wxStaticCast(GetDocument(), Project);
	if(type == vObject || type == vOrigin){
		glPushName((unsigned int) Selection::BaseAnything);
		glPushName(0);
		RenderCoordinateSystem();
		glPopName();
		glPopName();
	}
	glPushName(Selection::BaseObject);
	for(std::vector <Object>::const_iterator obj = project->objects.begin();
			obj != project->objects.end(); ++obj){
		glPushName(obj->GetID());
		obj->PaintPick();
		glPopName();
	}
	glPopName();

	if(type == vRun){
		glPushName(Selection::BaseRun);
		for(std::vector <Run>::const_iterator run = project->run.begin();
				run != project->run.end(); ++run){
			glPushName(run->GetID());
			run->Paint();
			glPopName();
		}
		glPopName();
	}
	if(type == vOrigin){
		glPushName(Selection::BaseRun);
		for(std::vector <Run>::const_iterator run = project->run.begin();
				run != project->run.end(); ++run){
			glPushName(run->GetID());
			run->PaintVertices();
			glPopName();
		}
		glPopName();
	}

	if(type == vGenerator){

		glPushName(Selection::BaseObject);
		for(std::vector <Object>::const_iterator obj = project->objects.begin();
				obj != project->objects.end(); ++obj){

			for(std::vector <Run>::const_iterator run = project->run.begin();
					run != project->run.end(); ++run){

				//			if(!selection.IsBase(Selection::BaseRun, run->GetID())
				//					|| !selection.IsType(Selection::Generator)) continue;

				if(!run->object.Has(Selection::Object, obj->GetID())) continue;
				glPushName(obj->GetID());
				obj->PaintPick();
				glPopName();
			}
		}
		glPopName();

	}
}

void ProjectView::PaintObjects(const Selection& sel, const OpenGLMaterial &face,
		const OpenGLMaterial &edge) const
{
	const Project* project = wxStaticCast(GetDocument(), Project);
	for(std::vector <Object>::const_iterator obj = project->objects.begin();
			obj != project->objects.end(); ++obj){
		if(sel.IsBase(Selection::BaseObject, obj->GetID())){
			obj->Paint(face, edge, sel);
		}else{
			if(sel.IsInverted()) obj->Paint(face, edge, Selection(true));
		}
	}

}

void ProjectView::PaintRun(const Selection& sel) const
{
	const Project* project = wxStaticCast(GetDocument(), Project);
	for(std::vector <Run>::const_iterator run = project->run.begin();
			run != project->run.end(); ++run){
		if(sel.IsBase(Selection::BaseRun, run->GetID())){
			run->Paint();

			for(std::vector <Generator*>::const_iterator it =
					run->generators.begin(); it != run->generators.end(); ++it){
				(*it)->Paint();
			}

		}else{
			if(sel.IsInverted()) run->Paint();
		}
	}

}

void ProjectView::PaintGenerators(const Selection& sel) const
{
	const Project* project = wxStaticCast(GetDocument(), Project);
	for(std::vector <Run>::const_iterator run = project->run.begin();
			run != project->run.end(); ++run){
		if(!sel.IsBase(Selection::BaseRun, run->GetID())
				&& !sel.IsType(Selection::Run)) continue;

		glPushMatrix();
		//		glTranslatef(run->stock.xmin, run->stock.ymin,
		//				run->stock.zmin);
		for(std::vector <Generator*>::const_iterator it =
				run->generators.begin(); it != run->generators.end(); ++it){
			(*it)->Paint();
		}
		glPopMatrix();
	}
}
void ProjectView::RenderCoordinateSystem(void) const
{
	GLfloat s = 0.1;
	GLfloat n = sqrt(2.0);
	GLfloat d = s / 10;

	OpenGLMaterial matX(0.8, 0.0, 0.0, 0.8);
	OpenGLMaterial matY(0.0, 0.8, 0.0, 0.8);
	OpenGLMaterial matZ(0.0, 0.0, 0.8, 0.8);

	glPushName(Selection::Axis);
	glPushName(0);

	matX.UseMaterial();
	glBegin(GL_LINES);
	glNormal3f(-s, 0, 0);
	glVertex3f(-s, 0, 0);
	glNormal3f(s, 0, 0);
	glVertex3f(s, 0, 0);

	glNormal3f(n, n, 0);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, d, 0);
	glNormal3f(n, -n, 0);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, -d, 0);
	glNormal3f(n, 0, n);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, 0, d);
	glNormal3f(n, 0, -n);
	glVertex3f(s, 0, 0);
	glVertex3f(s - d, 0, -d);

	glEnd();
	glLoadName(1);

	matY.UseMaterial();
	glBegin(GL_LINES);
	glNormal3f(0, -s, 0);
	glVertex3f(0, -s, 0);
	glNormal3f(0, s, 0);
	glVertex3f(0, s, 0);

	glNormal3f(n, n, 0);
	glVertex3f(0, s, 0);
	glVertex3f(d, s - d, 0);
	glNormal3f(-n, n, 0);
	glVertex3f(0, s, 0);
	glVertex3f(-d, s - d, 0);
	glNormal3f(0, n, n);
	glVertex3f(0, s, 0);
	glVertex3f(0, s - d, d);
	glNormal3f(0, n, -n);
	glVertex3f(0, s, 0);
	glVertex3f(0, s - d, -d);

	glEnd();
	glLoadName(2);

	matZ.UseMaterial();
	glBegin(GL_LINES);
	glNormal3f(0, 0, -s);
	glVertex3f(0, 0, -s);
	glNormal3f(0, 0, s);
	glVertex3f(0, 0, s);

	glNormal3f(n, 0, n);
	glVertex3f(0, 0, s);
	glVertex3f(d, 0, s - d);
	glNormal3f(-n, 0, n);
	glVertex3f(0, 0, s);
	glVertex3f(-d, 0, s - d);
	glNormal3f(0, n, n);
	glVertex3f(0, 0, s);
	glVertex3f(0, d, s - d);
	glNormal3f(0, -n, n);
	glVertex3f(0, 0, s);
	glVertex3f(0, -d, s - d);

	glEnd();
	glPopName();
	glPopName();
}

