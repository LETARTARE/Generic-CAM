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
