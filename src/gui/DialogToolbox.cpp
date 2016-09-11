///////////////////////////////////////////////////////////////////////////////
// Name               : DialogToolbox.cpp
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
///////////////////////////////////////////////////////////////////////////////

#include "DialogToolbox.h"

DialogToolbox::DialogToolbox(wxWindow* parent, Project * project,
		ToolBox * toolbox, DisplaySettings * settings) :
		GUIToolbox(parent)
{
	this->project = project;
	this->toolbox = toolbox;
	this->settings = settings;

	selectedTool = 0;
	selectedElement = 0;
	if(selectedTool < toolbox->tools.GetCount()){
		tempTool = toolbox->tools[selectedTool];
		if(selectedElement < tempTool.elements.GetCount()) tempElement =
				tempTool.elements[selectedElement];
	}
	m_menuSettings->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	TransferDataToWindow();
}

DialogToolbox::~DialogToolbox()
{
}

bool DialogToolbox::TransferDataToWindow(void)
{
	if(toolbox == NULL) return false;

	size_t i, j;

	m_comboBoxToolSelector->Clear();
	if(toolbox->tools.GetCount() == 0){
		m_comboBoxToolSelector->Append(_("No tools in toolbox!"));
		m_comboBoxToolSelector->Enable(false);
	}else{
		for(i = 0; i < toolbox->tools.GetCount(); i++){
			m_comboBoxToolSelector->Append(toolbox->tools[i].toolName);
		}
		m_comboBoxToolSelector->SetValue(tempTool.toolName);
		m_comboBoxToolSelector->Enable(true);
	}

	tempTool.GenerateContour();
	m_panel->InsertTool(tempTool);
	m_canvas->InsertTool(tempTool);
	settings->WriteToCanvas(m_canvas);
	m_canvas->Refresh();

	m_textCtrlShaftDiameter->SetValue(
			settings->SmallDistance.TextFromSI(tempTool.shaftDiameter));
	m_textCtrlShaftLength->SetValue(
			settings->SmallDistance.TextFromSI(tempTool.shaftLength));
	m_textCtrlMaxSpeed->SetValue(
			settings->RotationalSpeed.TextFromSI(tempTool.maxSpeed, 0));
	m_textCtrlFeedCoefficient->SetValue(
			settings->SmallDistance.TextFromSI(tempTool.feedCoefficient));
	m_textCtrlNrOfTeeth->SetValue(
			wxString::Format(_T("%u"), tempTool.nrOfTeeth));
	m_textCtrlComment->SetValue(tempTool.comment);

	m_staticTextUnitShaftDiameter->SetLabel(
			settings->SmallDistance.GetOtherName());
	m_staticTextUnitShaftLength->SetLabel(
			settings->SmallDistance.GetOtherName());
	m_staticTextUnitMaxSpeed->SetLabel(
			settings->RotationalSpeed.GetOtherName());
	m_staticTextUnitFeedCoefficient->SetLabel(
			settings->SmallDistance.GetOtherName());

	wxSize sz = m_listCtrl->GetClientSize();
	unsigned int w = sz.x / 14;
	m_listCtrl->ClearAll();
	m_listCtrl->InsertColumn(0, _("Type"), wxLIST_FORMAT_LEFT, 2 * w);
	m_listCtrl->InsertColumn(1, _("Diameter"), wxLIST_FORMAT_LEFT, 3 * w);
	m_listCtrl->InsertColumn(2, _("Height"), wxLIST_FORMAT_LEFT, 3 * w);
	m_listCtrl->InsertColumn(3, _("Radius"), wxLIST_FORMAT_LEFT, 3 * w);
	m_listCtrl->InsertColumn(4, _("Cutting"), wxLIST_FORMAT_LEFT, 3 * w);

	for(j = 0; j < tempTool.elements.GetCount(); j++){

//			wxLogMessage(
//					wxString::Format(_T("Element: %u Type %u"), j,
//							temp->elements[j].t));

		switch(tempTool.elements[j].t){
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

		m_listCtrl->SetItem(j, 1,
				settings->SmallDistance.TextFromSI(tempTool.elements[j].d));
		m_listCtrl->SetItem(j, 2,
				settings->SmallDistance.TextFromSI(tempTool.elements[j].h));
		m_listCtrl->SetItem(j, 3,
				settings->SmallDistance.TextFromSI(tempTool.elements[j].r));

		if(tempTool.elements[j].cutting){
			m_listCtrl->SetItem(j, 4, _("Yes"));
		}else{
			m_listCtrl->SetItem(j, 4, _("No"));
		}

		m_listCtrl->SetItemState(j,
				(j == selectedElement)? wxLIST_STATE_SELECTED : 0,
				wxLIST_STATE_SELECTED);

//		m_listCtrl->SetItemState(selectedElement,
//		wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

	}
	m_choiceType->Select(tempElement.t);

	m_textCtrlDiameter->SetValue(
			settings->SmallDistance.TextFromSI(tempElement.d));
	m_textCtrlHeight->SetValue(
			settings->SmallDistance.TextFromSI(tempElement.h));
	m_textCtrlRadius->SetValue(
			settings->SmallDistance.TextFromSI(tempElement.r));

	m_staticTextUnitDiameter->SetLabel(settings->SmallDistance.GetOtherName());
	m_staticTextUnitHeight->SetLabel(settings->SmallDistance.GetOtherName());
	m_staticTextUnitRadius->SetLabel(settings->SmallDistance.GetOtherName());

	m_checkBoxCutting->SetValue(tempElement.cutting);

	return true;
}

bool DialogToolbox::TransferDataFromWindow(void)
{
	tempTool.toolName = m_comboBoxToolSelector->GetValue();
	tempTool.shaftDiameter = settings->SmallDistance.SIFromString(
			m_textCtrlShaftDiameter->GetValue());
	tempTool.shaftLength = settings->SmallDistance.SIFromString(
			m_textCtrlShaftLength->GetValue());
	tempTool.maxSpeed = settings->RotationalSpeed.SIFromString(
			m_textCtrlMaxSpeed->GetValue());
	tempTool.feedCoefficient = settings->SmallDistance.SIFromString(
			m_textCtrlFeedCoefficient->GetValue());
	tempTool.nrOfTeeth = settings->SmallDistance.SIFromString(
			m_textCtrlNrOfTeeth->GetValue());
	tempTool.comment = m_textCtrlComment->GetValue();

	tempElement.t = m_choiceType->GetSelection();
	tempElement.d = settings->SmallDistance.SIFromString(
			m_textCtrlDiameter->GetValue());
	tempElement.h = settings->SmallDistance.SIFromString(
			m_textCtrlHeight->GetValue());
	tempElement.r = settings->SmallDistance.SIFromString(
			m_textCtrlRadius->GetValue());

	tempElement.cutting = m_checkBoxCutting->GetValue();

	return true;
}

void DialogToolbox::OnEnter(wxCommandEvent& event)
{
	TransferDataFromWindow();
	TransferDataToWindow();
}

void DialogToolbox::OnClose(wxCommandEvent& event)
{
	this->Show(false);
}

void DialogToolbox::OnXClose(wxCloseEvent& event)
{
	this->Show(false);
}

void DialogToolbox::SetController(Control3D& control)
{
	m_canvas->SetController(control);
}

void DialogToolbox::OnChangeStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode != stereoOff){
		m_canvas->stereoMode = stereoOff;
	}else{
		m_canvas->stereoMode = stereoAnaglyph;
	}
	m_menuSettings->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	settings->WriteToCanvas(m_canvas);
	m_canvas->Refresh();
}

void DialogToolbox::OnToolSelect(wxCommandEvent& event)
{
//	if(selectedTool == event.GetSelection()) return;
	TransferDataFromWindow();
	selectedTool = event.GetSelection();
	if(selectedTool < toolbox->tools.GetCount()){
		tempTool = toolbox->tools[selectedTool];
		selectedElement = 0;
		if(tempTool.elements.GetCount() > 0) tempElement = tempTool.elements[0];
	}
	TransferDataToWindow();
}

void DialogToolbox::OnToolRename(wxCommandEvent& event)
{
	TransferDataFromWindow();
	tempTool.toolName = event.GetString();
	TransferDataToWindow();
}

void DialogToolbox::OnToolNew(wxCommandEvent& event)
{
	TransferDataFromWindow();
	if(!tempTool.toolName.IsEmpty()){
		tempTool.toolName = _("Copy of ") + tempTool.toolName;
	}
	toolbox->tools.Add(tempTool);
	selectedTool = toolbox->tools.GetCount() - 1;
	TransferDataToWindow();
}

void DialogToolbox::OnToolUpdate(wxCommandEvent& event)
{
	TransferDataFromWindow();
	if(selectedTool >= toolbox->tools.GetCount()) return;
	toolbox->tools[selectedTool] = tempTool;
	TransferDataToWindow();
}

void DialogToolbox::OnToolDelete(wxCommandEvent& event)
{
	if(selectedTool < 0) return;
	if(selectedTool >= toolbox->tools.GetCount()) return;
	toolbox->tools.RemoveAt(selectedTool, 1);
	selectedTool--;
	if(selectedTool < 0) selectedTool = 0;
	if(selectedTool < toolbox->tools.GetCount()){
		tempTool = toolbox->tools[selectedTool];
		selectedElement = 0;
		if(tempTool.elements.GetCount() > 0) tempElement = tempTool.elements[0];
	}
	TransferDataToWindow();
}

void DialogToolbox::OnShapeSelect(wxListEvent& event)
{
	if(event.GetIndex() == selectedElement) return;
	TransferDataFromWindow();
	selectedElement = event.GetIndex();
	if(selectedElement < tempTool.elements.GetCount()){
		tempElement = tempTool.elements[selectedElement];
	}
	TransferDataToWindow();
}

void DialogToolbox::OnShapeNew(wxCommandEvent& event)
{
	TransferDataFromWindow();
	if(selectedElement < tempTool.elements.GetCount() - 1){
		tempTool.elements.Insert(tempElement, selectedElement + 1);
	}else{
		tempTool.elements.Add(tempElement);
	}
	selectedElement++;
	TransferDataToWindow();
}

void DialogToolbox::OnShapeUpdate(wxCommandEvent& event)
{
	TransferDataFromWindow();
	tempTool.elements[selectedElement] = tempElement;
	TransferDataToWindow();
}

void DialogToolbox::OnShapeDelete(wxCommandEvent& event)
{
	if(selectedElement < 0) return;
	if(selectedElement >= tempTool.elements.GetCount()) return;
	TransferDataFromWindow();
	tempTool.elements.RemoveAt(selectedElement, 1);
	selectedElement--;
	if(selectedElement < 0) selectedElement = 0;
	if(selectedElement < tempTool.elements.GetCount()) tempElement =
			tempTool.elements[selectedElement];
	TransferDataToWindow();
}
