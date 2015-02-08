///////////////////////////////////////////////////////////////////////////////
// Name               : TreeSetup.cpp
// Purpose            : Takes care of the treeview in the mainframe
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.01.2015
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

#include "TreeSetup.h"

#include <wx/debug.h>

#include "TreeItem.h"

TreeSetup::TreeSetup(wxTreeCtrl * tree, Project * project)
{
	maxId = 10;

	this->project = project;
	this->tree = tree;

	this->id = new wxTreeItemId[maxId];
	this->currentLevel = -1;

	this->cookie = project;

	long style = this->tree->GetWindowStyle() ^ wxTR_NO_LINES;
	this->tree->SetWindowStyle(style);

	this->prohibitVariableUpdate = false;
	this->levelModified = false;

	tree->DeleteAllItems();
}

TreeSetup::~TreeSetup()
{
	delete[] id;
}

void TreeSetup::Reset(void)
{
	tree->DeleteAllItems();
}

void TreeSetup::SetAtLevel(int level, const wxString& name, ItemDataType type,
		int nr)
{
	wxTreeItemId temp;

	if(level == currentLevel){
		temp = tree->GetNextSibling(id[currentLevel]);
		if(!temp.IsOk()){
			temp = tree->AppendItem(id[currentLevel - 1], name, -1, -1,
					new TreeItem(type, nr));
			levelModified = true;
		}
		id[currentLevel] = temp;
	}
	if(level < currentLevel){
		FinishLevel(currentLevel);
		currentLevel = level;
		temp = tree->GetNextSibling(id[currentLevel]);
		if(!temp.IsOk()){
			temp = tree->AppendItem(id[currentLevel - 1], name, -1, -1,
					new TreeItem(type, nr));
			levelModified = true;
		}
		id[currentLevel] = temp;
	}
	if(level > currentLevel){
		currentLevel = level;
		levelModified = false;
		temp = tree->GetFirstChild(id[currentLevel - 1], cookie);
		if(!temp.IsOk()){
			temp = tree->AppendItem(id[currentLevel - 1], name, -1, -1,
					new TreeItem(type, nr));
			levelModified = true;
		}
		id[currentLevel] = temp;
	}

	wxString tempName = tree->GetItemText(temp);
	if(tempName != name) tree->SetItemText(temp, name);

	TreeItem * data = (TreeItem*) tree->GetItemData(temp);
	assert(data!=NULL);
	data->dataType = type;
	data->nr = nr;
}

void TreeSetup::FinishLevel(int level, bool autoExpand)
{
	wxTreeItemId temp = tree->GetNextSibling(id[level]);
	while(temp.IsOk()){
		tree->Delete(temp);
		temp = tree->GetNextSibling(id[level]);
	}
	if(levelModified && autoExpand) tree->Expand(id[level - 1]);
}

bool TreeSetup::GetSelection(void)
{
	return tree->IsSelected(id[currentLevel]);
}

int TreeSetup::GetFirstSelectedObject(void)
{
	wxTreeItemId temp;
	TreeItem * data;

	// Check if all groups are OK.
	if(!groupObjects.IsOk()) return -1;

	temp = tree->GetFirstChild(groupObjects, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemObject
				&& tree->IsSelected(temp)) return data->nr;
		temp = tree->GetNextSibling(temp);
	}
	return -1;
}

int TreeSetup::GetFirstSelectedWorkpiece(void)
{
	wxTreeItemId temp;
	TreeItem * data;

	// Check if all groups are OK.
	if(!groupWorkpieces.IsOk()) return -1;

	temp = tree->GetFirstChild(groupWorkpieces, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemWorkpiece
				&& tree->IsSelected(temp)) return data->nr;
		temp = tree->GetNextSibling(temp);
	}
	return -1;
}

int TreeSetup::GetFirstSelectedRun(void)
{
	wxTreeItemId temp;
	TreeItem * data;

	// Check if all groups are OK.
	if(!groupRun.IsOk()) return -1;

	temp = tree->GetFirstChild(groupRun, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemRun && tree->IsSelected(temp)) return data->nr;
		temp = tree->GetNextSibling(temp);
	}
	return -1;
}

int TreeSetup::GetWorkpieceFromLink(int linkNr)
{
	int n, m;
	int linkCounter = 0;
	for(n = 0; n < project->workpieces.GetCount(); n++){
		for(m = 0; m < project->workpieces[n].placements.GetCount(); m++){
			if(linkCounter == linkNr) return n;
			linkCounter++;
		}
	}
	return -1;
}

int TreeSetup::GetObjectFromLink(int linkNr)
{
	int n, m;
	int linkCounter = 0;
	for(n = 0; n < project->workpieces.GetCount(); n++){
		for(m = 0; m < project->workpieces[n].placements.GetCount(); m++){
			if(linkCounter == linkNr) return m;
			linkCounter++;
		}
	}
	return -1;
}

void TreeSetup::SetSelection(bool selection)
{
	bool temp = tree->IsSelected(id[currentLevel]);
	if(temp != selection) tree->SelectItem(id[currentLevel], selection);
}

void TreeSetup::UpdateSelection(void)
{
	wxTreeItemId temp;
	bool flag;
	TreeItem * data;
	unsigned int N;

	// Check if all groups are ok.
	if(!groupObjects.IsOk()) return;

	// Disable the function variable update. This function would otherwise
	// be called by the main window, whenever a selection changes.
	prohibitVariableUpdate = true;

	// Updates for Objects:
	N = project->objects.GetCount();

	temp = tree->GetFirstChild(groupObjects, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemObject){
			if(data->nr >= 0 && data->nr < N){
				flag = tree->IsSelected(temp);
				if(flag != project->objects[data->nr].selected){
					tree->SelectItem(temp, project->objects[data->nr].selected);
				}
			}
		}
		temp = tree->GetNextSibling(temp);
	}

	// Updates for Workpieces:
	N = project->workpieces.GetCount();

	temp = tree->GetFirstChild(groupWorkpieces, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemWorkpiece){
			if(data->nr >= 0 && data->nr < N){
				flag = tree->IsSelected(temp);
				if(flag != project->workpieces[data->nr].selected){
					tree->SelectItem(temp,
							project->workpieces[data->nr].selected);
				}
			}
		}
		temp = tree->GetNextSibling(temp);
	}

	// Updates for Run:
	N = project->run.GetCount();

	temp = tree->GetFirstChild(groupRun, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemRun){
			if(data->nr >= 0 && data->nr < N){
				flag = tree->IsSelected(temp);
				if(flag != project->run[data->nr].selected){
					tree->SelectItem(temp, project->run[data->nr].selected);
				}
			}
		}
		temp = tree->GetNextSibling(temp);
	}

	prohibitVariableUpdate = false;
	UpdateVariables();
}

void TreeSetup::UpdateVariables(void)
{
	wxTreeItemId temp;
	TreeItem * data;
	unsigned int N;

	// The function UpdateSelection uses this flag to temporally disable variable update.
	if(prohibitVariableUpdate) return;

	if(!groupObjects.IsOk()) return;

	// Updates for Objects:
	N = project->objects.GetCount();
	temp = tree->GetFirstChild(groupObjects, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemObject){
			if(data->nr >= 0 && data->nr < N){
				project->objects[data->nr].selected = tree->IsSelected(temp);
			}
		}
		temp = tree->GetNextSibling(temp);
	}

	// Updates for Workpieces:
	N = project->workpieces.GetCount();
	temp = tree->GetFirstChild(groupWorkpieces, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemWorkpiece){
			if(data->nr >= 0 && data->nr < N){
				project->workpieces[data->nr].selected = tree->IsSelected(temp);
			}
		}
		temp = tree->GetNextSibling(temp);
	}

	// Updates for Run:
	N = project->run.GetCount();
	temp = tree->GetFirstChild(groupRun, cookie);
	while(temp.IsOk()){
		data = (TreeItem*) tree->GetItemData(temp);
		if(data != NULL && data->dataType == itemRun){
			if(data->nr >= 0 && data->nr < N){
				project->run[data->nr].selected = tree->IsSelected(temp);
			}
		}
		temp = tree->GetNextSibling(temp);
	}

}

void TreeSetup::Update(void)
{
	wxTreeItemId root = tree->GetRootItem();
	if(!root.IsOk()){
		root = tree->AddRoot(project->name, -1, -1, new TreeItem(itemProject));
	}
	wxString tempName = tree->GetItemText(root);
	if(tempName != project->name) tree->SetItemText(root, project->name);

	unsigned int n, m;
	id[0] = root;
	currentLevel = 0;

	SetAtLevel(1, _("Objects"), itemGroupObject, -1);
	groupObjects = id[1];
	for(n = 0; n < project->objects.GetCount(); n++){
		SetAtLevel(2, project->objects[n].name, itemObject, n);
		if(project->objects[n].geometries.GetCount() > 1){
			for(m = 0; m < project->objects[n].geometries.GetCount(); m++){
				SetAtLevel(3, project->objects[n].geometries[m].objectName,
						itemSubObject, n);
			}
			FinishLevel(3, false);
		}else{
			tree->DeleteChildren(id[2]);
		}
	}
	if(n == 0){
		tree->DeleteChildren(id[1]);
	}else{
		FinishLevel(2, true);
	}

	SetAtLevel(1, _("Workpiece"), itemGroupWorkpiece, -1);
	groupWorkpieces = id[1];
	int objectNr;
	int linkNr = 0;
	for(n = 0; n < project->workpieces.GetCount(); n++){
		SetAtLevel(2, project->workpieces[n].name, itemWorkpiece, n);
		for(m = 0; m < project->workpieces[n].placements.GetCount(); m++){
			objectNr = project->workpieces[n].placements[m].objectNr;
			SetAtLevel(3, project->objects[objectNr].name, itemObjectLink,
					linkNr);
			linkNr++;
		}
		if(m == 0){
			tree->DeleteChildren(id[2]);
		}else{
			FinishLevel(3, false);
		}
	}

	if(n == 0){
		tree->DeleteChildren(id[1]);
	}else{
		FinishLevel(2, true);
	}

	SetAtLevel(1, _("Run"), itemGroupRun, -1);
	groupRun = id[1];
	int workpieceNr;
	for(n = 0; n < project->run.GetCount(); n++){
		SetAtLevel(2, project->run[n].name, itemRun, n);

		if(project->run[n].machine.IsInitialized()){
			SetAtLevel(3,
			_("Machine: ") + project->run[n].machine.fileName.GetName(),
					itemMachine, 0);
		}else{
			SetAtLevel(3, _("Machine: -"), itemMachine, 0);
		}

		workpieceNr = project->run[n].workpieceNr;
		if(workpieceNr >= 0)
			SetAtLevel(3,
			_("Workpiece: ") + project->workpieces[workpieceNr].name,
					itemUnknown, workpieceNr);
		else
			SetAtLevel(3, wxString(_("Workpiece: ")) + _T("-"), itemUnknown,
					-1);

	}

	if(n == 0){
		tree->DeleteChildren(id[1]);
	}else{
		FinishLevel(2, true);
	}

	tree->Expand(id[0]);

}

