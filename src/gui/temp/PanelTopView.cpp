///////////////////////////////////////////////////////////////////////////////
// Name               : PanelTopView.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.01.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "PanelTopView.h"

PanelTopView::PanelTopView(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style) :
		wxPanel(parent, id, pos, size, style)
{
	project = NULL;

	// Connect events
	this->Connect(wxEVT_LEFT_DOWN,
			wxMouseEventHandler(PanelTopView::OnLeftDown));
	this->Connect(wxEVT_MOTION, wxMouseEventHandler(PanelTopView::OnMotion));
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(PanelTopView::OnPaint));
	this->Connect(wxEVT_SIZE, wxSizeEventHandler(PanelTopView::OnSize));
}

PanelTopView::~PanelTopView()
{ // Disconnect events
	this->Disconnect(wxEVT_LEFT_DOWN,
			wxMouseEventHandler(PanelTopView::OnLeftDown));
	this->Disconnect(wxEVT_MOTION, wxMouseEventHandler(PanelTopView::OnMotion));
	this->Disconnect(wxEVT_PAINT, wxPaintEventHandler(PanelTopView::OnPaint));
	this->Disconnect(wxEVT_SIZE, wxSizeEventHandler(PanelTopView::OnSize));
}

void PanelTopView::InsertProject(Project* project)
{
	this->project = project;
}

void PanelTopView::OnPaint(wxPaintEvent& event)
{
	int wpNr = GetFirstSelectedWorkpiece();
	if(wpNr < 0) return;
	wxPaintDC dc(this);
	wxSize sz = GetClientSize();

	dc.Clear();

	float scale;
	float x;
	float y;

	if(sz.GetWidth() / project->workpieces[wpNr].GetSizeX()
			< sz.GetHeight() / project->workpieces[wpNr].GetSizeY()){
		scale = (float) sz.GetWidth() / project->workpieces[wpNr].GetSizeX();
		x = 0;
		y = ((float) sz.GetHeight() - project->workpieces[wpNr].GetSizeY() * scale)
				/ 2.0;
	}else{
		scale = (float) sz.GetHeight() / project->workpieces[wpNr].GetSizeY();
		x = ((float) sz.GetWidth() - project->workpieces[wpNr].GetSizeX() * scale)
				/ 2.0;
		y = 0;
	}
	dc.DrawRoundedRectangle(x, y, (int) (project->workpieces[wpNr].GetSizeX()* scale),
			(int) (project->workpieces[wpNr].GetSizeY() * scale), 10);

	size_t N = project->workpieces[wpNr].placements.GetCount();
	size_t n, m, p;
	AffineTransformMatrix temp;
	Vector3 p1, p2, p3;
	for(n = 0; n < N; n++){
		size_t objNr = project->workpieces[wpNr].placements[n].refObject;
		if(objNr < 0) continue;
		for(m = 0; m < project->objects[objNr].geometries.GetCount(); m++){

			//TODO: Rethink this.
			temp = AffineTransformMatrix::Identity();
			temp.TranslateLocal(x, sz.GetHeight() - y, 0);
			temp.ScaleLocal(scale, -scale, scale);
//			temp.TranslateLocal(
//					-project->workpieces[wpNr].placements[n].bbox.xmin,
//					-project->workpieces[wpNr].placements[n].bbox.ymin,
//					-project->workpieces[wpNr].placements[n].bbox.zmin);
//			temp.TranslateLocal(
//					project->workpieces[wpNr].placements[n].matrix.a[12],
//					project->workpieces[wpNr].placements[n].matrix.a[13],
//					project->workpieces[wpNr].placements[n].matrix.a[14]);
			temp *= project->workpieces[wpNr].placements[n].matrix;
			temp *= project->objects[objNr].matrix;
			temp *= project->objects[objNr].geometries[m].matrix;
			for(p = 0;
					p
							< project->objects[objNr].geometries[m].triangles.GetCount();
					p++){
				p1 =
						temp.Transform(
								project->objects[objNr].geometries[m].triangles[p].p[0]);
				p2 =
						temp.Transform(
								project->objects[objNr].geometries[m].triangles[p].p[1]);
				p3 =
						temp.Transform(
								project->objects[objNr].geometries[m].triangles[p].p[2]);
				dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
				dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
				dc.DrawLine(p3.x, p3.y, p1.x, p1.y);

			}
		}
	}

}

void PanelTopView::OnSize(wxSizeEvent& event)
{
}

void PanelTopView::OnMotion(wxMouseEvent& event)
{
}

void PanelTopView::OnLeftDown(wxMouseEvent& event)
{
}

int PanelTopView::GetFirstSelectedWorkpiece()
{
	if(project == NULL) return -1;
	size_t N = project->workpieces.GetCount();
	if(N == 0) return -1;
	size_t n;
	for(n = 0; n < N; n++){
		if(project->workpieces[n].selected) return n;
	}
	return -1;
}
