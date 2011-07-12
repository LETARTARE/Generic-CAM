///////////////////////////////////////////////////////////////////////////////
// Name               : AnimationFrame.cpp
// Purpose            : A window displaying the animation controls.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.07.2011
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: 2010-05-22 01:40:18 +0200 (Sa, 22. Mai 2010) $
//$Revision: 45 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(wxWindow* parent) :
	GUIAnimationFrame(parent)
{
}

AnimationFrame::~AnimationFrame()
{
}

void AnimationFrame::InsertProject(Project *project)
{
	linkedProject = project;
	TransferDataToWindow();
}

void AnimationFrame::OnClose(wxCommandEvent &event)
{
	Close();
}

bool AnimationFrame::TransferDataToWindow(void)
{
	return true;
}
bool AnimationFrame::TransferDataFromWindow(void)
{
	return true;
}

void AnimationFrame::OnLast(wxCommandEvent& event)
{
}
void AnimationFrame::OnBegin(wxCommandEvent& event)
{
}
void AnimationFrame::OnPlayStop(wxCommandEvent& event)
{
}
void AnimationFrame::OnEnd(wxCommandEvent& event)
{
}
void AnimationFrame::OnNext(wxCommandEvent& event)
{
}
