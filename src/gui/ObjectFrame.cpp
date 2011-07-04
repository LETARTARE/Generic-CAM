///////////////////////////////////////////////////////////////////////////////
// Name               : ObjectFrame.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "ObjectFrame.h"

ObjectFrame::ObjectFrame(wxWindow* parent) :
	GUIObjectFrame(parent)
{
	linkedProject = NULL;

}

ObjectFrame::~ObjectFrame()
{
}

void ObjectFrame::InsertProject(Project *project)
{
	linkedProject = project;
}

bool ObjectFrame::TransferDataToWindow(void)
{
	if(linkedProject == NULL) return false;

	size_t i;
	m_comboBox->Clear();
	if(linkedProject->objects.GetCount()>0)
	{
		for(i=0;i<linkedProject->objects.GetCount();i++)
			m_comboBox->Append(linkedProject->objects[i].fileName.GetName());
		m_comboBox->Enable();
	}else{
		m_comboBox->Append(_("No objects in project!"));
		m_comboBox->Enable(false);
	}
	m_comboBox->SetSelection(linkedProject->selectedObject);
	m_textCtrlSizeX->SetValue(wxString::Format(_T("%.3f"),linkedProject->objects[linkedProject->selectedObject].bbox.GetSizeX()));



	return true;
}
bool ObjectFrame::TransferDataFromWindow(void)
{

	return true;
}

void ObjectFrame::OnClose(wxCommandEvent& event)
{
	Close();
}
