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
	if(levelModified) tree->Expand(id[level - 1]);
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
}

void TreeSetup::Update(void)
{
	wxTreeItemId root = tree->GetRootItem();
	if(!root.IsOk()){
		root = tree->AddRoot(project->name, -1, -1, new TreeItem(itemProject));
	}
	wxString tempName = tree->GetItemText(root);
	if(tempName != project->name) tree->SetItemText(root, project->name);

	unsigned int n;
	id[0] = root;
	currentLevel = 0;

	SetAtLevel(1, _("Objects"), itemGroupObject, -1);
	groupObjects = id[1];
	for(n = 0; n < project->objects.GetCount(); n++){
		SetAtLevel(2, project->objects[n].name, itemObject, n);
	}

	if(n == 0){
		tree->DeleteChildren(id[1]);
	}else{
		FinishLevel(2, true);
	}

	SetAtLevel(1, _("Stock"), itemGroupStock, -1);

	SetAtLevel(1, _("Run"), itemGroupRun, -1);

	tree->Expand(id[0]);

	//	wxTreeItemId rootId = tree->AddRoot(_T("TreeRoot"));
//
//	wxTreeItemId treeIdProject;
//
//	wxTreeItemId treeIdObject;
//	wxTreeItemId treeIdGeometry;
//	wxTreeItemId treeIdStock;
//	wxTreeItemId treeIdMachine;
//	wxTreeItemId treeIdToolbox;
//	wxTreeItemId treeIdRun;
//	wxTreeItemId treeIdRun2;
//
//	wxTreeItemId treeIdToolpath;
//
//	size_t i, j, k;
//	for(i = 0; i < project.GetCount(); i++){
//		treeIdProject = tree->AppendItem(rootId,
//		_("Project: ") + project[i].name);
//
//		treeIdStock = tree->AppendItem(treeIdProject,
//		_("Stock material: ") + project[i].stock.name);
//
//		for(j = 0; j < project[i].stock.stockMaterials.GetCount(); j++){
//			tree->AppendItem(treeIdStock,
//					project[i].stock.stockMaterials[j].materialName);
//		}
//
//		for(j = 0; j < project[i].objects.GetCount(); j++){
//			treeIdObject = tree->AppendItem(treeIdProject,
//			_("Object: ") + project[i].objects[j].fileName.GetName());
//			for(k = 0; k < project[i].objects[j].geometries.GetCount(); k++){
//				{
//					tree->AppendItem(treeIdObject,
//							project[i].objects[j].geometries[k].objectName);
//				}
//			}
//		}
//
//		treeIdMachine = tree->AppendItem(treeIdProject,
//		_("Machine: ") + project[i].machine.fileName.GetName());
//
//		treeIdToolbox = tree->AppendItem(treeIdProject,
//		_("Toolbox: ") + project[i].toolbox.fileName.GetName());
//		for(j = 0; j < project[i].toolbox.tools.GetCount(); j++){
//			tree->AppendItem(treeIdToolbox,
//					project[i].toolbox.tools[j].toolName);
//		}
//
//		treeIdRun = tree->AppendItem(treeIdProject, _("Run:"));
//		for(j = 0; j < project[i].runs.GetCount(); j++){
//			treeIdRun2 = tree->AppendItem(treeIdRun,
//					project[i].runs[j].runName);
//
//			tree->AppendItem(treeIdRun2, _("Stock material"));
//			tree->AppendItem(treeIdRun2, _("Target"));
//			treeIdToolpath = tree->AppendItem(treeIdRun2, _("Toolpath"));
//		}
//
//	}
//
//	//	for(i = 0; i < doc->geometry.Count(); i++){
//	//		tid = new TreeItemData;
//	//		tid->nr = i;
//	//		tid->dataType = TreeItemData::geometry;
//	//		tree->AppendItem(treeIdGeometry, doc->geometry[i].objectName, -1, -1,
//	//				tid);
//	//	}
//
//	tree->ExpandAll();
}

