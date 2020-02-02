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

#include <wx/dir.h>

#include "IDs.h"
#include "../project/ProjectView.h"
#include "FrameMain.h"
#include "FrameParent.h"

DialogToolbox::DialogToolbox(wxWindow* parent) :
		GUIToolbox(parent)

{
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
//	m_menuPreferences->Append(ID_SETUPUNITS,
//	_("Setup &Units") + wxT("\tCtrl+U"));

	wxSize iconSize = wxArtProvider::GetSizeHint(wxART_LIST);
	if(iconSize == wxDefaultSize) iconSize = wxSize(16, 16);
	wxImageList * imagelist = new wxImageList(iconSize.x, iconSize.y);
	imagelist->Add(
			wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_LIST, iconSize));
	imagelist->Add(wxArtProvider::GetIcon(wxART_FOLDER, wxART_LIST, iconSize));
	imagelist->Add(
			wxArtProvider::GetIcon(wxART_FOLDER_OPEN, wxART_LIST, iconSize));
	m_treeListCtrl->AssignImageList(imagelist);

	Update();

	TransferDataToWindow();
}

DialogToolbox::~DialogToolbox()
{
}

void DialogToolbox::Update(void)
{
	if(!toolboxes.empty()) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxDir dir(frame->filepaths.lastToolboxDirectory);
	if(dir.IsOpened()){
		wxString filename;
		bool cont = dir.GetFirst(&filename, _T("*.json"));
		while(cont){
			wxString fullfilename = dir.GetNameWithSep() + filename;
			if(filename.CmpNoCase(_T("local.json")) == 0){
				if(!localtoolbox.IsLoaded()) localtoolbox.Load(
						fullfilename.ToStdString());
			}else{
				ToolBox temp;
				temp.filename = fullfilename.ToStdString();
				toolboxes.push_back(temp);
			}
			cont = dir.GetNext(&filename);
		}
	}

	wxTreeListItem root = m_treeListCtrl->GetRootItem();
	projectfolder = m_treeListCtrl->AppendItem(root, _("Project"), 1, 2);

	const std::vector <Tool> * temptools = project->GetTools();
	for(std::vector <Tool>::const_iterator it = temptools->begin();
			it != temptools->end(); ++it){
		wxTreeListItem item = m_treeListCtrl->AppendItem(root,
				wxString(it->base.description));
		m_treeListCtrl->SetItemText(item, 1,
				wxString::Format(_T("%g"), it->geometry.DC));
		m_treeListCtrl->SetItemText(item, 2,
				wxString::Format(_T("%u"), it->base.type));
		m_treeListCtrl->SetItemText(item, 3,
				wxString::Format(_T("%i"), it->postprocess.number));
	}

	localtoolboxfolder = m_treeListCtrl->AppendItem(root, _("Local toolbox"), 1,
			2);
	m_treeListCtrl->AppendItem(localtoolboxfolder, _T("dummy"), 0, 0);
	m_treeListCtrl->Collapse(localtoolboxfolder);

	for(std::vector <ToolBox>::const_iterator it = toolboxes.begin();
			it != toolboxes.end(); ++it){
		wxTreeListItem temp = m_treeListCtrl->AppendItem(root,
				wxString(it->GetName()), 1, 2);
		m_treeListCtrl->AppendItem(temp, _T("dummy"), 0, 0);
		m_treeListCtrl->Collapse(temp);
		toolboxfolders.push_back(temp);
	}
}

bool DialogToolbox::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	SettingsStereo3D* settings = &(frame->GetParentFrame()->settingsStereo3D);
	CollectionUnits* units = &(frame->GetParentFrame()->units);

	size_t i, j;

//	m_comboBoxToolSelector->Clear();
//	if(view->toolbox.GetToolCount() == 0){
//		m_comboBoxToolSelector->Append(_("No tools in toolbox!"));
//		m_comboBoxToolSelector->Enable(false);
//	}else{
//		for(i = 0; i < view->toolbox.GetToolCount(); i++){
//			m_comboBoxToolSelector->Append(
//					view->toolbox.ToolIndex(i)->toolName);
//		}
//		m_comboBoxToolSelector->SetValue(tempTool.toolName);
//		m_comboBoxToolSelector->Enable(true);
//	}
//
//	tempTool.GenerateContour();
//	m_panel->InsertTool(tempTool);
//	m_canvas->InsertTool(tempTool);
//	settings->WriteToCanvas(m_canvas);
//	m_canvas->Refresh();
//
//	m_textCtrlShaftDiameter->SetValue(
//			units->SmallDistance.TextFromSI(tempTool.shaftDiameter));
//	m_textCtrlShaftLength->SetValue(
//			units->SmallDistance.TextFromSI(tempTool.shaftLength));
//	m_textCtrlMaxSpeed->SetValue(
//			units->RotationalSpeed.TextFromSI(tempTool.maxSpeed));
//	m_textCtrlFeedCoefficient->SetValue(
//			units->SmallDistance.TextFromSI(tempTool.feedCoefficient));
//	m_textCtrlNrOfTeeth->SetValue(
//			wxString::Format(_T("%u"), tempTool.nrOfTeeth));
//	m_textCtrlComment->SetValue(tempTool.comment);

//	m_staticTextUnitShaftDiameter->SetLabel(
//			units->SmallDistance.GetOtherName());
//	m_staticTextUnitShaftLength->SetLabel(units->SmallDistance.GetOtherName());
//	m_staticTextUnitMaxSpeed->SetLabel(units->RotationalSpeed.GetOtherName());
//	m_staticTextUnitFeedCoefficient->SetLabel(
//			units->SmallDistance.GetOtherName());

//	wxSize sz = m_dataViewListCtrlShape->GetClientSize();
//	unsigned int w = sz.x / 6;
//	m_dataViewListCtrlShape->ClearAll();
//	m_dataViewListCtrlShape->AppendTextColumn(_("Upper"));
//	m_dataViewListCtrlShape->AppendTextColumn(_("Lower"));
//	m_dataViewListCtrlShape->AppendTextColumn(_("Height"));

//	m_listCtrl->InsertColumn(3, _("Radius"), wxLIST_FORMAT_LEFT, 3 * w);
//	m_listCtrl->InsertColumn(4, _("Cutting"), wxLIST_FORMAT_LEFT, 3 * w);

//	for(j = 0; j < tempTool.elements.GetCount(); j++){

//			wxLogMessage(
//					wxString::Format(_T("Element: %u Type %u"), j,
//							temp->elements[j].t));

//		switch(tempTool.elements[j].t){
//		case 0:
//			m_listCtrl->InsertItem(j, _T("L"));
//			break;
//		case 1:
//			m_listCtrl->InsertItem(j, _T("CDH"));
//			break;
//		case 2:
//			m_listCtrl->InsertItem(j, _T("CHD"));
//			break;
//		case 3:
//			m_listCtrl->InsertItem(j, _T("SRU"));
//			break;
//		case 4:
//			m_listCtrl->InsertItem(j, _T("SRL"));
//			break;
//		}
//
//		m_listCtrl->SetItem(j, 1,
//				units->SmallDistance.TextFromSI(tempTool.elements[j].d));
//		m_listCtrl->SetItem(j, 2,
//				units->SmallDistance.TextFromSI(tempTool.elements[j].h));
//		m_listCtrl->SetItem(j, 3,
//				units->SmallDistance.TextFromSI(tempTool.elements[j].r));
//
//		if(tempTool.elements[j].cutting){
//			m_listCtrl->SetItem(j, 4, _("Yes"));
//		}else{
//			m_listCtrl->SetItem(j, 4, _("No"));
//		}
//
//		m_listCtrl->SetItemState(j,
//				(j == selectedElement)? wxLIST_STATE_SELECTED : 0,
//				wxLIST_STATE_SELECTED);
//
////		m_listCtrl->SetItemState(selectedElement,
////		wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
//
//	}
//	m_choiceType->Select(tempElement.t);
//
//	m_textCtrlDiameter->SetValue(
//			units->SmallDistance.TextFromSI(tempElement.d));
//	m_textCtrlHeight->SetValue(units->SmallDistance.TextFromSI(tempElement.h));
//	m_textCtrlRadius->SetValue(units->SmallDistance.TextFromSI(tempElement.r));
//
//	m_staticTextUnitDiameter->SetLabel(units->SmallDistance.GetOtherName());
//	m_staticTextUnitHeight->SetLabel(units->SmallDistance.GetOtherName());
//	m_staticTextUnitRadius->SetLabel(units->SmallDistance.GetOtherName());
//
//	m_checkBoxCutting->SetValue(tempElement.cutting);

	return true;
}

bool DialogToolbox::TransferDataFromWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	CollectionUnits* units = &(frame->GetParentFrame()->units);

//	tempTool.toolName = m_comboBoxToolSelector->GetValue();
//	tempTool.shaftDiameter = units->SmallDistance.SIFromString(
//			m_textCtrlShaftDiameter->GetValue());
//	tempTool.shaftLength = units->SmallDistance.SIFromString(
//			m_textCtrlShaftLength->GetValue());
//	tempTool.maxSpeed = units->RotationalSpeed.SIFromString(
//			m_textCtrlMaxSpeed->GetValue());
//	tempTool.feedCoefficient = units->SmallDistance.SIFromString(
//			m_textCtrlFeedCoefficient->GetValue());
//	tempTool.nrOfTeeth = units->SmallDistance.SIFromString(
//			m_textCtrlNrOfTeeth->GetValue());
//	tempTool.comment = m_textCtrlComment->GetValue();
//
//	tempElement.t = m_choiceType->GetSelection();
//	tempElement.d = units->SmallDistance.SIFromString(
//			m_textCtrlDiameter->GetValue());
//	tempElement.h = units->SmallDistance.SIFromString(
//			m_textCtrlHeight->GetValue());
//	tempElement.r = units->SmallDistance.SIFromString(
//			m_textCtrlRadius->GetValue());
//
//	tempElement.cutting = m_checkBoxCutting->GetValue();

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

//void DialogToolbox::OnToolSelect(wxCommandEvent& event)
//{
////	if(selectedTool == event.GetSelection()) return;
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
//	TransferDataFromWindow();
//
//
//
//
//	TransferDataToWindow();
//}
//
//void DialogToolbox::OnToolRename(wxCommandEvent& event)
//{
//	TransferDataFromWindow();
////	tempTool.description = event.GetString();
//	TransferDataToWindow();
//}
//
//void DialogToolbox::OnToolNew(wxCommandEvent& event)
//{
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
//	TransferDataFromWindow();
////	if(!tempTool.toolName.IsEmpty()){
////		tempTool.toolName = _("Copy of ") + tempTool.toolName;
////	}
////	selectedTool = view->toolbox.AddTool(tempTool);
//	TransferDataToWindow();
//}
//
//void DialogToolbox::OnToolUpdate(wxCommandEvent& event)
//{
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
//	TransferDataFromWindow();
////	if(selectedTool >= view->toolbox.GetToolCount()) return;
////	*(view->toolbox.ToolIndex(selectedTool)) = tempTool;
//	TransferDataToWindow();
//}
//
//void DialogToolbox::OnToolDelete(wxCommandEvent& event)
//{
//	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
////	if(selectedTool < 0) return;
////	if(selectedTool >= view->toolbox.GetToolCount()) return;
////	view->toolbox.RemoveToolIndex(selectedTool);
////	selectedTool--;
////	if(selectedTool < 0) selectedTool = 0;
////	if(selectedTool < view->toolbox.GetToolCount()){
////		tempTool = *(view->toolbox.ToolIndex(selectedTool));
////		selectedElement = 0;
////		if(tempTool.elements.GetCount() > 0) tempElement = tempTool.elements[0];
////	}
//	TransferDataToWindow();
//}

void DialogToolbox::OnShapeSelect(wxListEvent& event)
{
//	if(event.GetIndex() == selectedElement) return;
	TransferDataFromWindow();
//	selectedElement = event.GetIndex();
//	if(selectedElement < tempTool.elements.GetCount()){
//		tempElement = tempTool.elements[selectedElement];
//	}
	TransferDataToWindow();
}

void DialogToolbox::OnShapeNew(wxCommandEvent& event)
{
	TransferDataFromWindow();
//	if(selectedElement < tempTool.elements.GetCount() - 1){
//		tempTool.elements.Insert(tempElement, selectedElement + 1);
//	}else{
//		tempTool.elements.Add(tempElement);
//	}
//	selectedElement++;
	TransferDataToWindow();
}

void DialogToolbox::OnShapeUpdate(wxCommandEvent& event)
{
	TransferDataFromWindow();
//	tempTool.elements[selectedElement] = tempElement;
	TransferDataToWindow();
}

void DialogToolbox::OnShapeDelete(wxCommandEvent& event)
{
//	if(selectedElement < 0) return;
//	if(selectedElement >= tempTool.elements.GetCount()) return;
//	TransferDataFromWindow();
//	tempTool.elements.RemoveAt(selectedElement, 1);
//	selectedElement--;
//	if(selectedElement < 0) selectedElement = 0;
//	if(selectedElement < tempTool.elements.GetCount()) tempElement =
//			tempTool.elements[selectedElement];
	TransferDataToWindow();
}

void DialogToolbox::OnShapeWizard(wxCommandEvent& event)
{
//	DialogToolWizard dialog(this);
//	dialog.ShowModal();
}

void DialogToolbox::OnItemChecked(wxTreeListEvent& event)
{
}

void DialogToolbox::OnItemContextMenu(wxTreeListEvent& event)
{
}

void DialogToolbox::OnSelectionChanged(wxTreeListEvent& event)
{
}

