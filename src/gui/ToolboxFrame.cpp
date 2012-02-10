///////////////////////////////////////////////////////////////////////////////
// Name               : ToolboxFrame.cpp
// Purpose            : A window to edit tools in the toolbox.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.03.2010
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "ToolboxFrame.h"

ToolboxFrame::ToolboxFrame(wxWindow* parent) :
	GUIToolboxFrame(parent)
{
	linkedProject = NULL;
	selectedTool = 0;
	selectedElement = 0;

	m_menuSettings->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

ToolboxFrame::~ToolboxFrame()
{
}

void ToolboxFrame::OnClose(wxCommandEvent& event)
{
	Close();
}

void ToolboxFrame::SetController(Control3D& control)
{
	m_canvas->SetController(control);
}

void ToolboxFrame::OnChangeStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == 1){
		m_canvas->stereoMode = 0;
	}else{
		m_canvas->stereoMode = 1;
	}
	m_menuSettings->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

void ToolboxFrame::InsertProject(Project *project)
{
	linkedProject = project;
	TransferDataToWindow();
}

bool ToolboxFrame::TransferDataToWindow(void)
{

	if(linkedProject == NULL) return false;

	size_t i, j;

	m_comboBoxToolSelector->Clear();
	if(linkedProject->toolbox.tools.GetCount() == 0){
		m_comboBoxToolSelector->Append(_("No tools in toolbox!"));
		m_comboBoxToolSelector->Enable(false);
	}else{
		for(i = 0; i < linkedProject->toolbox.tools.GetCount(); i++){
			m_comboBoxToolSelector->Append(
					linkedProject->toolbox.tools[i].toolName);
		}
		m_comboBoxToolSelector->Select(selectedTool);
		m_comboBoxToolSelector->Enable(true);
	}

	if(selectedTool < linkedProject->toolbox.tools.GetCount()){
		m_panel->InsertTool(linkedProject->toolbox.tools[selectedTool]);
		m_canvas->InsertTool(linkedProject->toolbox.tools[selectedTool]);
	}

	if(selectedTool < linkedProject->toolbox.tools.GetCount()){

		Tool *temp = &(linkedProject->toolbox.tools[selectedTool]);

		m_textCtrlShaftDiameter->SetValue(wxString::Format(_T("%f"),
				temp->shaftDiameter));
		m_textCtrlShaftLength->SetValue(wxString::Format(_T("%f"),
				temp->shaftLength));
		m_textCtrlMaxSpeed->SetValue(wxString::Format(_T("%.0f"),
				temp->maxSpeed));
		m_textCtrlFeedCoefficient->SetValue(wxString::Format(_T("%f"),
				temp->feedCoefficient));
		m_textCtrlNrOfTeeth->SetValue(wxString::Format(_T("%u"),
				temp->nrOfTeeth));
		m_textCtrlComment->SetValue(temp->comment);

		wxSize sz = m_listCtrl->GetClientSize();
		unsigned int w = sz.x / 14;
		m_listCtrl->ClearAll();
		m_listCtrl->InsertColumn(0, _("Type"), wxLIST_FORMAT_LEFT, 2* w );
		m_listCtrl->InsertColumn(1, _("Diameter"), wxLIST_FORMAT_LEFT, 3* w );
		m_listCtrl->InsertColumn(2, _("Height"), wxLIST_FORMAT_LEFT, 3* w );
		m_listCtrl->InsertColumn(3, _("Radius"), wxLIST_FORMAT_LEFT, 3* w );
		m_listCtrl->InsertColumn(4, _("Cutting"), wxLIST_FORMAT_LEFT, 3* w );

		for(j = 0; j < temp->elements.GetCount(); j++){

			wxLogMessage(wxString::Format(_T("Element: %u Type %u"), j,
					temp->elements[j].t));

			switch(temp->elements[j].t){
			case 0:
				m_listCtrl->InsertItem(j, _T("L"));
				break;
			case 1:
				m_listCtrl->InsertItem(j, _T("CDH"));
				break;
			case 2:
				m_listCtrl->InsertItem(j, _T("CHD"));
				break;
			case 3:
				m_listCtrl->InsertItem(j, _T("SRU"));
				break;
			case 4:
				m_listCtrl->InsertItem(j, _T("SRL"));
				break;
			}

			m_listCtrl->SetItem(j, 1, wxString::Format(_T("%f"),
					temp->elements[j].d));
			m_listCtrl->SetItem(j, 2, wxString::Format(_T("%f"),
					temp->elements[j].h));
			m_listCtrl->SetItem(j, 3, wxString::Format(_T("%f"),
					temp->elements[j].r));

			if(temp->elements[j].cutting){
				m_listCtrl->SetItem(j, 4, _("Yes"));
			}else{
				m_listCtrl->SetItem(j, 4, _("No"));
			}

			m_listCtrl->SetItemState(j, 0, wxLIST_STATE_SELECTED);

			if(selectedElement < temp->elements.GetCount()){

				m_listCtrl->SetItemState(selectedElement,
						wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

				m_choiceType->Select(temp->elements[selectedElement].t);

				m_textCtrlDiameter->SetValue(wxString::Format(_T("%f"),
						temp->elements[selectedElement].d));
				m_textCtrlHeight->SetValue(wxString::Format(_T("%f"),
						temp->elements[selectedElement].h));
				m_textCtrlRadius->SetValue(wxString::Format(_T("%f"),
						temp->elements[selectedElement].r));

				m_checkBoxCutting ->SetValue(
						temp->elements[selectedElement].cutting);

			}
		}
	}
	return true;
}

bool ToolboxFrame::TransferDataFromWindow(void)
{
	return true;
}

void ToolboxFrame::OnNewTool(wxCommandEvent& event)
{
}

void ToolboxFrame::OnUpdateTool(wxCommandEvent& event)
{
}

void ToolboxFrame::OnDeleteTool(wxCommandEvent& event)
{
}

void ToolboxFrame::OnShapeNew(wxCommandEvent& event)
{
}

void ToolboxFrame::OnShapeUpdate(wxCommandEvent& event)
{
}

void ToolboxFrame::OnShapeDelete(wxCommandEvent& event)
{
}

void ToolboxFrame::OnShapeSelect(wxListEvent& event)
{
}
