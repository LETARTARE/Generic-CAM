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

#define _USE_MATH_DEFINES

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

	Update(true);
}

DialogToolbox::~DialogToolbox()
{
}

void DialogToolbox::Update(bool refreshDirectory)
{
	if(!this->IsShown()) return;
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);

	// Initialize toolboxes
	if(toolboxes.empty() || refreshDirectory){
		toolboxes.clear();
		toolboxes.push_back(project->tools);
		toolboxes[0].filename = "/Project.";
		wxDir dir(frame->GetFilePaths()->lastToolboxDirectory);
		if(dir.IsOpened()){
			wxString filename;
			bool cont = dir.GetFirst(&filename, _T("*.json"));
			while(cont){
				wxString fullfilename = dir.GetNameWithSep() + filename;
				ToolBox temp;
				temp.filename = fullfilename.ToStdString();
				if(filename.Lower().StartsWith(_T("local"))){
					temp.Load();
					toolboxes.insert(toolboxes.begin() + 1, temp);
				}else{
					toolboxes.push_back(temp);
				}
				cont = dir.GetNext(&filename);
			}
		}
		toolboxfolders.clear();
		m_treeListCtrl->DeleteAllItems();
	}else{
		toolboxes[0] = project->tools;
		toolboxes[0].filename = "/Project.";
	}

	wxTreeListItem rootFolder = m_treeListCtrl->GetRootItem();
//	if(!projectfolder.IsOk()){
//		projectfolder = m_treeListCtrl->AppendItem(root, _("Project"), 1, 2);
//	}

	wxTreeListItem toolboxFolder = m_treeListCtrl->GetFirstChild(rootFolder);

	size_t toolboxcount = 0;
	for(std::vector <ToolBox>::const_iterator it = toolboxes.begin();
			it != toolboxes.end(); ++it){
		bool expanded = false;
		if(toolboxFolder.IsOk()){
			m_treeListCtrl->SetItemData(toolboxFolder,
					new ToolData(toolboxcount));
			m_treeListCtrl->SetItemText(toolboxFolder, it->GetName());
			expanded = m_treeListCtrl->IsExpanded(toolboxFolder);
		}else{
			toolboxFolder = m_treeListCtrl->AppendItem(rootFolder,
					wxString(it->GetName()), 1, 2,
					new ToolData(toolboxcount, 0, false));
		}

		wxTreeListItem toolItem = m_treeListCtrl->GetFirstChild(toolboxFolder);

		if(it->IsLoaded()){
			size_t toolcount = 0;
			for(std::vector <Tool>::const_iterator tool = it->tools.begin();
					tool != it->tools.end(); ++tool){

				if(toolItem.IsOk()){
					m_treeListCtrl->SetItemData(toolItem,
							new ToolData(toolboxcount, toolcount, true));
					m_treeListCtrl->SetItemText(toolItem,
							tool->base.description);
				}else{
					toolItem = m_treeListCtrl->AppendItem(toolboxFolder,
							wxString(tool->base.description),
							wxTreeListCtrl::NO_IMAGE, wxTreeListCtrl::NO_IMAGE,
							new ToolData(toolboxcount, toolcount, true));
				}
				AddToolToListCtrl(toolItem, *tool);
				toolItem = m_treeListCtrl->GetNextSibling(toolItem);
				++toolcount;
			}

		}else{
			if(toolItem.IsOk()){
				m_treeListCtrl->SetItemData(toolItem, NULL);
				m_treeListCtrl->SetItemText(toolItem, _T("loading..."));
				m_treeListCtrl->SetItemImage(toolItem, wxTreeListCtrl::NO_IMAGE,
						wxTreeListCtrl::NO_IMAGE);
			}else{
				toolItem = m_treeListCtrl->AppendItem(toolboxFolder,
						_T("loading..."), wxTreeListCtrl::NO_IMAGE,
						wxTreeListCtrl::NO_IMAGE);
			}
		}

		if(!expanded) m_treeListCtrl->Collapse(toolboxFolder);
		toolboxfolders.push_back(toolboxFolder);
		toolboxFolder = m_treeListCtrl->GetNextSibling(toolboxFolder);
		++toolboxcount;
	}

	TransferDataToWindow();
}

void DialogToolbox::AddToolToListCtrl(wxTreeListItem & item, const Tool & tool)
{
	m_treeListCtrl->SetItemText(item, 1,
			wxString::Format(_T("%g"), tool.geometry.DC));
	m_treeListCtrl->SetItemText(item, 2,
			wxString::Format(_T("%u"), tool.base.type));
	m_treeListCtrl->SetItemText(item, 3,
			wxString::Format(_T("%i"), tool.postprocess.number));
}

bool DialogToolbox::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	ProjectView* view = wxStaticCast(frame->GetView(), ProjectView);
	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	SettingsStereo3D* settings = &(frame->GetParentFrame()->settingsStereo3D);
	CollectionUnits* units = &(frame->GetParentFrame()->units);

	// Units

	m_staticTextUnitDC->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitLCF->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitLB->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitOAL->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitRE->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitSIG->SetLabel(units->Angle.GetOtherName());
	m_staticTextUnitTA->SetLabel(units->Angle.GetOtherName());
	m_staticTextUnitSFDM->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitShoulderLength->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitTipDiameter->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitTipLength->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitTipOffset->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitThreadProfileAngle->SetLabel(units->Angle.GetOtherName());
	m_staticTextUnitShapeUpperDiameter->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitShapeLowerDiameter->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitShapeHeight->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitHolderUpperDiameter->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitHolderLowerDiameter->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitHolderHeight->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitShaftUpperDiameter->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitShaftLowerDiameter->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitShaftHeight->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitFeedPerRevolution->SetLabel(
			units->SmallDistance.GetOtherName());
	m_staticTextUnitFeedPerTooth->SetLabel(units->SmallDistance.GetOtherName());
	m_staticTextUnitFeedSpindleSpeed->SetLabel(
			units->RotationalSpeed.GetOtherName());
	m_staticTextUnitFeedSpindleSpeedRamp->SetLabel(
			units->RotationalSpeed.GetOtherName());
	m_staticTextUnitSpeedCuttingFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());
	m_staticTextUnitSpeedAvgFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());
	m_staticTextUnitSpeedLeadInFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());
	m_staticTextUnitSpeedLeadOutFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());
	m_staticTextUnitSpeedPlungeFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());
	m_staticTextUnitSpeedRampFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());
	m_staticTextUnitSpeedRetractionFeedrate->SetLabel(
			units->LinearSpeed.GetOtherName());

	// Values from tool
	m_canvastool->InsertTool(tempTool);
	// Tool
	switch(tempTool.base.type){
	case Tool::flat_end_mill:
		m_choiceToolType->SetSelection(0);
		break;
	case Tool::ball_end_mill:
		m_choiceToolType->SetSelection(1);
		break;
	case Tool::bull_nose_end_mill:
		m_choiceToolType->SetSelection(2);
		break;
	case Tool::camfer_mill:
		m_choiceToolType->SetSelection(3);
		break;
	case Tool::radius_mill:
		m_choiceToolType->SetSelection(4);
		break;
	case Tool::tool_holder:
		m_choiceToolType->SetSelection(5);
		break;
	case Tool::tool_shaft:
		m_choiceToolType->SetSelection(6);
		break;
	case Tool::probe:
		m_choiceToolType->SetSelection(7);
		break;
	}
	m_textCtrlToolDescription->SetValue(tempTool.base.description);
	m_textCtrlToolVendor->SetValue(tempTool.base.vendor);
	m_textCtrlToolGUID->SetValue(tempTool.base.guid);
	m_textCtrlToolProductID->SetValue(tempTool.base.productid);
	m_textCtrlToolProductLink->SetValue(tempTool.base.productlink);
	m_textCtrlToolGrade->SetValue(tempTool.GRADE);
	m_textCtrlToolBMC->SetValue(tempTool.BMC);

	if(tempTool.unitinfile == Tool::unit_inch){
		m_radioBoxToolUnit->SetSelection(1);
	}else{
		m_radioBoxToolUnit->SetSelection(0);
	}

	m_textCtrlDC->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.DC));
	m_textCtrlLCF->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.LCF));
	m_textCtrlLB->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.LB));
	m_textCtrlOAL->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.OAL));
	m_textCtrlRE->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.RE));

	m_textCtrlNOF->SetValue(wxString::Format(_T("%lu"), tempTool.geometry.NOF));
	m_textCtrlNT->SetValue(wxString::Format(_T("%lu"), tempTool.geometry.NT));

	m_textCtrlSIG->SetValue(units->Angle.TextFromSI(tempTool.geometry.SIG));
	m_textCtrlTA->SetValue(units->Angle.TextFromSI(tempTool.geometry.TA));

	m_choiceCSP->SetSelection(tempTool.geometry.CSP? 1 : 0);
	m_choiceHAND->SetSelection(tempTool.geometry.HAND? 1 : 0);

	m_textCtrlSFDM->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.SFDM));
	m_textCtrlShoulderLength->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.shoulderlength));
	m_textCtrlTipDiameter->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.tipdiameter));
	m_textCtrlTipLength->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.tiplength));
	m_textCtrlTipOffset->SetValue(
			units->SmallDistance.TextFromSI(tempTool.geometry.tipoffset));
	m_textCtrlThreadProfileAngle->SetValue(
			units->Angle.TextFromSI(tempTool.geometry.threadprofileangle));

	m_checkBoxShapeFromGeometry->SetValue(tempTool.hasGeometry);

	m_dataViewListCtrlShapeSegments->DeleteAllItems();
	if(tempTool.base.hasSegments){
		for(std::vector <Tool::Segment>::iterator it =
				tempTool.base.segments.begin();
				it != tempTool.base.segments.end(); ++it){

			wxVector <wxVariant> data;
			data.push_back(
					wxVariant(
							units->SmallDistance.TextFromSI(
									it->upperdiameter)));
			data.push_back(
					wxVariant(
							units->SmallDistance.TextFromSI(
									it->lowerdiameter)));
			data.push_back(
					wxVariant(units->SmallDistance.TextFromSI(it->height)));
			m_dataViewListCtrlShapeSegments->AppendItem(data);
		}
	}
	m_choiceHolder->SetSelection(tempTool.hasHolder? 1 : 0);
	m_dataViewListCtrlHolderSegments->DeleteAllItems();
	if(tempTool.holder.hasSegments){
		for(std::vector <Tool::Segment>::iterator it =
				tempTool.holder.segments.begin();
				it != tempTool.holder.segments.end(); ++it){

			wxVector <wxVariant> data;
			data.push_back(
					wxVariant(
							units->SmallDistance.TextFromSI(
									it->upperdiameter)));
			data.push_back(
					wxVariant(
							units->SmallDistance.TextFromSI(
									it->lowerdiameter)));
			data.push_back(
					wxVariant(units->SmallDistance.TextFromSI(it->height)));
			m_dataViewListCtrlHolderSegments->AppendItem(data);
		}
	}

	m_checkBoxShaftFromGeometry->SetValue(!tempTool.hasShaft);
	m_dataViewListCtrlShaftSegments->DeleteAllItems();
	if(tempTool.shaft.hasSegments){
		for(std::vector <Tool::Segment>::iterator it =
				tempTool.shaft.segments.begin();
				it != tempTool.shaft.segments.end(); ++it){

			wxVector <wxVariant> data;
			data.push_back(
					wxVariant(
							units->SmallDistance.TextFromSI(
									it->upperdiameter)));
			data.push_back(
					wxVariant(
							units->SmallDistance.TextFromSI(
									it->lowerdiameter)));
			data.push_back(
					wxVariant(units->SmallDistance.TextFromSI(it->height)));
			m_dataViewListCtrlShaftSegments->AppendItem(data);
		}
	}

	if(!tempTool.startvalues.empty()){
		const Tool::StartValues & startvalues = tempTool.startvalues[0];

		m_textCtrlSetName->SetValue(startvalues.name);
		m_textCtrlSetGUID->SetValue(startvalues.guid);
		m_textCtrlSetDescription->SetValue(startvalues.description);
		m_textCtrlSetToolCoolant->SetValue(startvalues.toolcoolant);

		m_textCtrlFeedPerRevolution->SetValue(
				units->SmallDistance.TextFromSI(startvalues.fn));
		m_textCtrlFeedPerTooth->SetValue(
				units->SmallDistance.TextFromSI(startvalues.fz));
		m_textCtrlFeedSpindleSpeed->SetValue(
				units->RotationalSpeed.TextFromSI(startvalues.n));
		m_textCtrlFeedSpindleSpeedRamp->SetValue(
				units->RotationalSpeed.TextFromSI(startvalues.nramp));
		m_textCtrlSpeedCuttingFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vc));
		m_textCtrlSpeedAvgFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vf));
		m_textCtrlSpeedLeadInFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vfleadin));
		m_textCtrlSpeedLeadOutFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vfleadout));
		m_textCtrlSpeedPlungeFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vfplunge));
		m_textCtrlSpeedRampFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vframp));
		m_textCtrlSpeedRetractionFeedrate->SetValue(
				units->LinearSpeed.TextFromSI(startvalues.vfretract));
	}else{
		m_textCtrlSetName->SetValue(_T(""));
		m_textCtrlSetGUID->SetValue(_T(""));
		m_textCtrlSetDescription->SetValue(_T(""));
		m_textCtrlSetToolCoolant->SetValue(_T(""));
		m_textCtrlFeedPerRevolution->SetValue(_T(""));
		m_textCtrlFeedPerTooth->SetValue(_T(""));
		m_textCtrlFeedSpindleSpeed->SetValue(_T(""));
		m_textCtrlFeedSpindleSpeedRamp->SetValue(_T(""));
		m_textCtrlSpeedCuttingFeedrate->SetValue(_T(""));
		m_textCtrlSpeedAvgFeedrate->SetValue(_T(""));
		m_textCtrlSpeedLeadInFeedrate->SetValue(_T(""));
		m_textCtrlSpeedLeadOutFeedrate->SetValue(_T(""));
		m_textCtrlSpeedPlungeFeedrate->SetValue(_T(""));
		m_textCtrlSpeedRampFeedrate->SetValue(_T(""));
		m_textCtrlSpeedRetractionFeedrate->SetValue(_T(""));
	}

	m_checkBoxLive->SetValue(tempTool.postprocess.live);
	m_textCtrlPostProcessComment->SetValue(tempTool.postprocess.comment);
	m_textCtrlPostProcessNumber->SetValue(
			wxString::Format(_T("%i"), tempTool.postprocess.number));
	m_checkBoxManualToolChange->SetValue(
			!tempTool.postprocess.manualtoolchange);
	m_checkBoxBreakControl->SetValue(!tempTool.postprocess.breakcontrol);
	m_textCtrlPostProcessDiameterOffset->SetValue(
			wxString::Format(_T("%lu"), tempTool.postprocess.diameteroffset));
	m_textCtrlPostProcessLengthOffset->SetValue(
			wxString::Format(_T("%lu"), tempTool.postprocess.lengthoffset));
	m_textCtrlPostProcessToolCoolant->SetValue(
			tempTool.postprocess.toolcoolant);
	m_textCtrlPostProcessTurret->SetValue(
			wxString::Format(_T("%lu"), tempTool.postprocess.turret));

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

void DialogToolbox::OnXClose(wxCloseEvent& event)
{
	this->Show(false);
}

void DialogToolbox::OnToolChecked(wxTreeListEvent& event)
{
}

void DialogToolbox::OnToolContextMenu(wxTreeListEvent& event)
{
}

void DialogToolbox::OnToolboxExpanding(wxTreeListEvent& event)
{
	wxTreeListItem item = event.GetItem();
	ToolData* info = (ToolData*) m_treeListCtrl->GetItemData(item);
	if(info == NULL) return;
	if(info->toolbox == 0) return;
	bool flag = toolboxes[info->toolbox].Load();
	if(DEBUG) std::cout << "DialogToolbox::OnToolboxExpanding - Toolbox #"
			<< info->toolbox << " - .Load() = " << (flag? "true" : "false")
			<< "\n";

	Update(false);
}

void DialogToolbox::OnToolSelectionChanged(wxTreeListEvent& event)
{
	wxTreeListItem item = event.GetItem();
	ToolData* info = (ToolData*) m_treeListCtrl->GetItemData(item);
	if(info == NULL) return;
	if(!info->isTool) return;
	if(DEBUG) std::cout
			<< "DialogToolbox::OnToolSelectionChanged - Selecting toolbox #"
			<< info->toolbox << ", tool #" << info->tool << ".\n";
	tempTool = toolboxes[info->toolbox].tools[info->tool];
	if(DEBUG) std::cout << "\tOK.\n";
	TransferDataToWindow();
	Refresh();
}

void DialogToolbox::OnChoice(wxCommandEvent& event)
{
}

void DialogToolbox::OnEnter(wxCommandEvent& event)
{
	TransferDataFromWindow();
	TransferDataToWindow();
}

void DialogToolbox::OnRadioBox(wxCommandEvent& event)
{
}

void DialogToolbox::OnCheckBox(wxCommandEvent& event)
{
}

void DialogToolbox::OnSegmentAdd(wxCommandEvent& event)
{
}

void DialogToolbox::OnSegmentDelete(wxCommandEvent& event)
{
}

void DialogToolbox::OnItemBeginDrag(wxDataViewEvent& event)
{
}

void DialogToolbox::OnItemDrop(wxDataViewEvent& event)
{
}

void DialogToolbox::OnSelectionChanged(wxDataViewEvent& event)
{
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

//void DialogToolbox::OnShapeSelect(wxListEvent& event)
//{
//	if(event.GetIndex() == selectedElement) return;
//	TransferDataFromWindow();
//	selectedElement = event.GetIndex();
//	if(selectedElement < tempTool.elements.GetCount()){
//		tempElement = tempTool.elements[selectedElement];
//	}
//	TransferDataToWindow();
//}

//void DialogToolbox::OnShapeNew(wxCommandEvent& event)
//{
//	TransferDataFromWindow();
//	if(selectedElement < tempTool.elements.GetCount() - 1){
//		tempTool.elements.Insert(tempElement, selectedElement + 1);
//	}else{
//		tempTool.elements.Add(tempElement);
//	}
//	selectedElement++;
//	TransferDataToWindow();
//}
//
//void DialogToolbox::OnShapeUpdate(wxCommandEvent& event)
//{
//	TransferDataFromWindow();
//	tempTool.elements[selectedElement] = tempElement;
//	TransferDataToWindow();
//}
//
//void DialogToolbox::OnShapeDelete(wxCommandEvent& event)
//{
//	if(selectedElement < 0) return;
//	if(selectedElement >= tempTool.elements.GetCount()) return;
//	TransferDataFromWindow();
//	tempTool.elements.RemoveAt(selectedElement, 1);
//	selectedElement--;
//	if(selectedElement < 0) selectedElement = 0;
//	if(selectedElement < tempTool.elements.GetCount()) tempElement =
//			tempTool.elements[selectedElement];
//	TransferDataToWindow();
//}
