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

#include "TreeItem.h"
#include "FrameMain.h"
#include "../project/Project.h"
#include "../project/ProjectView.h"

#include <wx/debug.h>

TreeSetup::TreeSetup(FrameMain * parent, wxTreeCtrl * tree)
{
	maxId = 10;

	this->tree = tree;
	this->parent = parent;
	Project * const project = wxStaticCast(parent->GetDocument(), Project);

	this->id = new wxTreeItemId[maxId];
	this->currentLevel = -1;

	long style = this->tree->GetWindowStyle() ^ wxTR_NO_LINES;
	this->tree->SetWindowStyle(style);

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

void TreeSetup::SetSelection(bool selection)
{
	const bool temp = tree->IsSelected(id[currentLevel]);
	if(temp != selection) tree->SelectItem(id[currentLevel], selection);
}

bool TreeSetup::GetSelection(void)
{
	return tree->IsSelected(id[currentLevel]);
}

void TreeSetup::SetAtLevel(int level, const wxString& name,
		TreeItem::itemtype type, size_t ID)
{
	wxTreeItemId temp;
	wxTreeItemIdValue cookie;
	if(level < currentLevel){
		FinishLevel(currentLevel);
		currentLevel = level;
	}
	if(level == currentLevel){
		temp = tree->GetNextSibling(id[currentLevel]);
	}else{
		currentLevel = level;
		levelModified = false;
		temp = tree->GetFirstChild(id[currentLevel - 1], cookie);
	}

	if(!temp.IsOk()){
		temp = tree->AppendItem(id[currentLevel - 1], name, -1, -1,
				new TreeItem(type, ID));
		levelModified = true;
	}
	id[currentLevel] = temp;

	bool selected = tree->IsSelected(temp);
	wxString tempName = tree->GetItemText(temp);
	if(tempName != name){
		tree->SetItemText(temp, name);
		selected = false;
	}

	TreeItem * data = (TreeItem*) tree->GetItemData(temp);
	assert(data!=NULL);
	if(data->type != type || data->ID != ID) selected = false;
	data->type = type;
	data->ID = ID;
	if(tree->IsSelected(temp) && !selected) tree->SelectItem(temp, false);
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

//int TreeSetup::GetFirstSelectedObject(void)
//{
//	wxTreeItemId temp;
//	TreeItem * data;
//
//	// Check if all groups are OK.
//	if(!groupObjects.IsOk()) return -1;
//
//	temp = tree->GetFirstChild(groupObjects, cookie);
//	while(temp.IsOk()){
//		data = (TreeItem*) tree->GetItemData(temp);
//		if(data != NULL && data->dataType == itemObject
//				&& tree->IsSelected(temp)) return data->nr;
//		temp = tree->GetNextSibling(temp);
//	}
//	return -1;
//}
//
//int TreeSetup::GetFirstSelectedWorkpiece(void)
//{
//	wxTreeItemId temp;
//	TreeItem * data;
//
//	// Check if all groups are OK.
//	if(!groupWorkpieces.IsOk()) return -1;
//
//	temp = tree->GetFirstChild(groupWorkpieces, cookie);
//	while(temp.IsOk()){
//		data = (TreeItem*) tree->GetItemData(temp);
//		if(data != NULL && data->dataType == itemWorkpiece
//				&& tree->IsSelected(temp)) return data->nr;
//		temp = tree->GetNextSibling(temp);
//	}
//	return -1;
//}
//
//int TreeSetup::GetFirstSelectedRun(void)
//{
//	wxTreeItemId temprun;
//	wxTreeItemId temp;
//	TreeItem * data;
//
//	// Check if all groups are OK.
//	if(!groupRun.IsOk()) return -1;
//
//	temprun = tree->GetFirstChild(groupRun, cookie);
//	while(temprun.IsOk()){
//		data = (TreeItem*) tree->GetItemData(temprun);
//		if(tree->IsSelected(temprun)) return data->nr;
//		temp = tree->GetFirstChild(temprun, cookie);
//		if(data != NULL && data->dataType == itemRun){
//			while(temp.IsOk()){
//				if(tree->IsSelected(temp)) return data->nr;
//				temp = tree->GetNextSibling(temp);
//			}
//		}
//		temprun = tree->GetNextSibling(temprun);
//	}
//	return -1;
//}
//
//int TreeSetup::GetFirstSelectedToolpath(void)
//{
//	wxTreeItemId temprun;
//	wxTreeItemId temp;
//	TreeItem * data;
//
//	// Check if all groups are OK.
//	if(!groupRun.IsOk()) return -1;
//
//	temprun = tree->GetFirstChild(groupRun, cookie);
//	while(temprun.IsOk()){
//		temp = tree->GetFirstChild(temprun, cookie);
//		while(temp.IsOk()){
//			data = (TreeItem*) tree->GetItemData(temp);
//			if(data != NULL && data->dataType == itemToolpath
//					&& tree->IsSelected(temp)) return data->nr;
//			temp = tree->GetNextSibling(temp);
//		}
//		temprun = tree->GetNextSibling(temprun);
//	}
//	return -1;
//}
//
//int TreeSetup::GetWorkpieceFromLink(int linkNr)
//{
//	int linkCounter = 0;
//	for(int n = 0; n < project->workpieces.GetCount(); n++){
//		for(int m = 0; m < project->workpieces[n].placements.GetCount(); m++){
//			if(linkCounter == linkNr) return n;
//			linkCounter++;
//		}
//	}
//	return -1;
//}
//
//int TreeSetup::GetObjectFromLink(int linkNr)
//{
//	int linkCounter = 0;
//	for(int n = 0; n < project->workpieces.GetCount(); n++){
//		for(int m = 0; m < project->workpieces[n].placements.GetCount(); m++){
//			if(linkCounter == linkNr) return m;
//			linkCounter++;
//		}
//	}
//	return -1;
//}

void TreeSetup::Update(void)
{
	// Note: This function to update the tree is rather complicated, because it keeps the
	// expansion level and the selection if possible.

	// The function UpdateSelection uses this flag to temporally disable variable update.
	if(loopGuard.TryLock() == wxMUTEX_BUSY) return;
	std::cout << "TreeSetup::Update -> loopGuard.Lock();\n";

	wxTreeItemId root = tree->GetRootItem();
	if(!root.IsOk()){
		root = tree->AddRoot(_T("root"), -1, -1,
				new TreeItem(TreeItem::itemProject));
	}

	Project * const project = wxStaticCast(parent->GetDocument(), Project);
	ProjectView * const view = wxStaticCast(parent->GetView(), ProjectView);

	wxString tempName = tree->GetItemText(root);
	if(tempName != project->GetTitle()) tree->SetItemText(root,
			project->GetTitle());

	id[0] = root;
	currentLevel = 0;

	SetAtLevel(1, _("Objects"), TreeItem::itemGroupObjects, -1);
	groupObjects = id[1];

	bool foundItem = false;
	std::set <size_t> objIDs = project->GetAllObjectIDs();
	for(std::set <size_t>::const_iterator objID = objIDs.begin();
			objID != objIDs.end(); ++objID){
		SetAtLevel(2, project->Get3DObject(*objID).name, TreeItem::itemObject,
				*objID);
		foundItem = true;
	}
	if(foundItem){
		FinishLevel(2, true);
	}else{
		tree->DeleteChildren(id[1]);
	}
	tree->Expand(id[1]);

	SetAtLevel(1, _("Run"), TreeItem::itemGroupRun, -1);
	groupRun = id[1];

	foundItem = false;
	std::set <size_t> runIDs = project->GetAllRunIDs();
	for(std::set <size_t>::const_iterator runID = runIDs.begin();
			runID != runIDs.end(); ++runID){
		const Run & run = project->GetRun(*runID);
		SetAtLevel(2, run.name, TreeItem::itemRun, *runID);

		bool foundItem2 = false;
		for(std::map <size_t, Generator*>::const_iterator generator =
				run.generators.begin(); generator != run.generators.end();
				++generator){
			std::cout << " => " << generator->second->GetName() << "\n";
			SetAtLevel(3, generator->second->GetName(), TreeItem::itemGenerator,
					generator->first);
			foundItem2 = true;
		}
		if(foundItem2){
			FinishLevel(3, true);
		}else{
			tree->DeleteChildren(id[2]);
		}
		foundItem = true;
	}
	if(foundItem){
		FinishLevel(2, true);
	}else{
		tree->DeleteChildren(id[1]);
	}
	tree->Expand(id[1]);

//	int objectNr;
//	int linkNr = 0;
//	for(n = 0; n < project->workpieces.GetCount(); n++){
//		SetAtLevel(2, project->workpieces[n].name, itemWorkpiece, n);
//	}
//
//	if(n == 0){
//		tree->DeleteChildren(id[1]);
//	}else{
//		FinishLevel(2, true);
//	}
//

//	int workpieceNr;
//	for(n = 0; n < project->run.GetCount(); n++){
//		SetAtLevel(2, project->run[n].name, itemRun, n);
//
//		if(project->run[n].machine.IsInitialized()){
//			SetAtLevel(3,
//			_("Machine: ") + project->run[n].machine.fileName.GetName(),
//					itemMachine, n);
//		}else{
//			SetAtLevel(3, _("Machine: -"), itemMachine, n);
//		}
//
//		workpieceNr = project->run[n].refWorkpiece;
//		if(workpieceNr >= 0)
//			SetAtLevel(3,
//			_("Workpiece: ") + project->workpieces[workpieceNr].name,
//					itemRunWorkpiece, n);
//		else
//			SetAtLevel(3, wxString(_("Workpiece: ")) + _T("-"),
//					itemRunWorkpiece, n);
//
//		for(m = 0; m < project->run[n].generators.GetCount(); m++){
//			wxString temp;
//
//			if(project->run[n].generators[m] != NULL){
//				temp =
//				_("Toolpath - ")
//						+ project->run[n].generators[m]->GetName();
//
////				if(project->processToolpath){
////					if(!project->run[n].toolpaths[m].generator->toolpathGenerated) temp +=
////							_(" - waiting");
////				}
////				if(project->run[n].toolpaths[m].generator->toolpathGenerated) temp +=
////						_(" - generated");
////				if(project->run[n].toolpaths[m].generator->errorOccured) temp +=
////						_(" - Error");
//			}else{
//				temp = _("Toolpath - ?");
//			}
//
//			SetAtLevel(3, temp, itemToolpath, m);
//		}
//		FinishLevel(3, true);
//	}

	tree->Expand(id[0]);

	std::cout << "TreeSetup::Update -> loopGuard.Unlock();\n";
	loopGuard.Unlock();
}

void TreeSetup::SelectonToTree(const Selection &sel)
{
	// Disable the function variable update. This function would otherwise
	// be called by the main window, whenever a selection changes.
	// The function UpdateSelection uses this flag to temporally disable variable update.
//	std::cout << "TreeSetup::SelectonToTree(" << sel.ToString() << ")";
	if(loopGuard.TryLock() == wxMUTEX_BUSY){
//		std::cout << " -> wxMUTEX_BUSY;\n";
		return;
	}
//	std::cout << ";\n";
//	std::cout << "TreeSetup::SelectonToTree -> loopGuard.Lock();\n";

	// Check if all groups are ok.
	if(!groupObjects.IsOk() || !groupRun.IsOk()){
//		std::cout << "TreeSetup::SelectonToTree -> loopGuard.Unlock();\n";
		loopGuard.Unlock();
		return;
	}

	Project * const project = wxStaticCast(parent->GetDocument(), Project);

	// Updates for Objects:
	{
		wxTreeItemIdValue cookie;
		std::set <size_t> objIDs = project->GetAllObjectIDs();
		std::set <size_t>::const_iterator objID = objIDs.begin();

//		obj != project->objects.end(); ++obj){
//			SetAtLevel(2, obj->second.name, TreeItem::itemObject, obj->first);
//		}

		wxTreeItemId temp = tree->GetFirstChild(groupObjects, cookie);
		while(temp.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
			if(data != NULL && data->type == TreeItem::itemObject){
				if(objID == objIDs.end()) break;
				const bool flag = tree->IsSelected(temp);
				const bool inSelection = sel.Has(Selection::Object, *objID);
				if(flag != inSelection){
					tree->SelectItem(temp, inSelection);
				}
				++objID;
			}
			temp = tree->GetNextSibling(temp);
		}
	}

	// Updates for Workpieces:
	{
//		const unsigned int N = project->workpieces.GetCount();
//
//		wxTreeItemId temp = tree->GetFirstChild(groupWorkpieces, cookie);
//		while(temp.IsOk()){
//			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
//			if(data != NULL && data->dataType == itemWorkpiece){
//				if(data->nr >= 0 && data->nr < N){
//					const bool flag = tree->IsSelected(temp);
//					if(flag != project->workpieces[data->nr].selected){
//						tree->SelectItem(temp,
//								project->workpieces[data->nr].selected);
//					}
//				}
//			}
//			temp = tree->GetNextSibling(temp);
//		}
	}

	// Updates for Run:
	{
		wxTreeItemIdValue cookie;
		std::set <size_t> runIDs = project->GetAllRunIDs();
		std::set <size_t>::const_iterator runID = runIDs.begin();

		wxTreeItemId temp = tree->GetFirstChild(groupRun, cookie);
		while(temp.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
			if(data != NULL && data->type == TreeItem::itemRun){
				if(runID == runIDs.end()) break;
				const bool flag = tree->IsSelected(temp);
				const bool inSelection = sel.Has(Selection::Run, *runID);
				if(flag != inSelection){
					tree->SelectItem(temp, inSelection);
				}
				++runID;
			}
			temp = tree->GetNextSibling(temp);
		}

//		const unsigned int N = project->run.GetCount();
//
//		wxTreeItemId temp = tree->GetFirstChild(groupRun, cookie);
//		while(temp.IsOk()){
//			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
//			if(data != NULL && data->dataType == itemRun){
//				if(data->nr >= 0 && data->nr < N){
//					const bool flag = tree->IsSelected(temp);
//					if(flag != project->run[data->nr].selected){
//						tree->SelectItem(temp, project->run[data->nr].selected);
//					}
//					const unsigned int N2 =
//							project->run[data->nr].generators.GetCount();
//					wxTreeItemIdValue cookie2;
//					wxTreeItemId temp2 = tree->GetFirstChild(temp, cookie2);
//					while(temp2.IsOk()){
//						TreeItem * data2 = (TreeItem*) tree->GetItemData(temp2);
//						if(data2 != NULL && data2->dataType == itemToolpath){
//							if(data2->nr >= 0 && data2->nr < N2){
//								const bool flag2 = tree->IsSelected(temp2);
//								if(flag2
//										!= project->run[data->nr].generators[data2->nr]->selected){
//									tree->SelectItem(temp2,
//											project->run[data->nr].generators[data2->nr]->selected);
//								}
//							}
//						}
//						temp2 = tree->GetNextSibling(temp2);
//					}
//				}
//			}
//			temp = tree->GetNextSibling(temp);
//		}
	}
//	std::cout << "TreeSetup::SelectonToTree -> loopGuard.Unlock();\n";
	loopGuard.Unlock();
//	TreeToProject();
}

Selection TreeSetup::TreeToSelection(void)
{
	if(!groupObjects.IsOk()){
		return Selection();
	}

	Project * const project = wxStaticCast(parent->GetDocument(), Project);

	Selection sel;

	// Updates for Objects:
	{
		wxTreeItemIdValue cookie;
		std::set <size_t> objIDs = project->GetAllObjectIDs();
		std::set <size_t>::const_iterator objID = objIDs.begin();
		wxTreeItemId temp = tree->GetFirstChild(groupObjects, cookie);
		while(temp.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
			if(data != NULL && data->type == TreeItem::itemObject){
				if(objID == objIDs.end()) break;
				if(tree->IsSelected(temp)) sel.Add(Selection::Object, *objID);
				++objID;
			}
			temp = tree->GetNextSibling(temp);
		}
		if(!sel.IsSetEmpty()) return sel;
	}

	// Updates for Workpieces:
	{
//		const unsigned int N = project->workpieces.GetCount();
//		wxTreeItemId temp = tree->GetFirstChild(groupWorkpieces, cookie);
//		while(temp.IsOk()){
//			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
//			if(data != NULL && data->dataType == itemWorkpiece){
//				if(data->nr >= 0 && data->nr < N){
//					project->workpieces[data->nr].selected = tree->IsSelected(
//							temp);
//				}
//			}
//			temp = tree->GetNextSibling(temp);
//		}
	}

	// Updates for Run:
	{
		wxTreeItemIdValue cookie;
		wxTreeItemIdValue cookie2;
		std::set <size_t> runIDs = project->GetAllRunIDs();
		std::set <size_t>::const_iterator runID = runIDs.begin();
		wxTreeItemId temp = tree->GetFirstChild(groupRun, cookie);
		while(temp.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
			if(data != NULL && data->type == TreeItem::itemRun){
				if(runID == runIDs.end()) break;
				if(tree->IsSelected(temp)) sel.Add(Selection::Run, *runID);
				std::set <size_t> generatorIDs = project->GetAllGeneratorIDs(
						*runID);
				std::set <size_t>::const_iterator generatorID =
						generatorIDs.begin();
				wxTreeItemId temp2 = tree->GetFirstChild(data->GetId(),
						cookie2);
				while(temp2.IsOk()){
					TreeItem * data2 = (TreeItem*) tree->GetItemData(temp2);
					if(data2 != NULL && data2->type == TreeItem::itemGenerator){
						if(generatorID == generatorIDs.end()) break;

						if(tree->IsSelected(temp2)) sel.Add(Selection::BaseRun,
								*runID, Selection::Generator, *generatorID);
						++generatorID;
					}
					temp2 = tree->GetNextSibling(temp2);
				}
				++runID;
			}
			temp = tree->GetNextSibling(temp);
		}
		if(!sel.IsSetEmpty()) return sel;

//		const unsigned int N = project->run.GetCount();
//		wxTreeItemId temp = tree->GetFirstChild(groupRun, cookie);
//		while(temp.IsOk()){
//			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
//			if(data != NULL && data->dataType == itemRun){
//				bool toolpathSelected = false;
//				const unsigned int N2 =
//						project->run[data->nr].generators.GetCount();
//				wxTreeItemIdValue cookie2;
//				wxTreeItemId temp2 = tree->GetFirstChild(temp, cookie2);
//				while(temp2.IsOk()){
//					TreeItem * data2 = (TreeItem*) tree->GetItemData(temp2);
//					if(data2 != NULL && data2->dataType == itemToolpath){
//						if(data2->nr >= 0 && data2->nr < N2){
//							project->run[data->nr].generators[data2->nr]->selected =
//									tree->IsSelected(temp2);
//							if(tree->IsSelected(temp2)) toolpathSelected = true;
//						}
//					}
//					temp2 = tree->GetNextSibling(temp2);
//				}
//
//				if(data->nr >= 0 && data->nr < N){
//					project->run[data->nr].Select (tree->IsSelected(temp)
//							| toolpathSelected);
//					if(toolpathSelected){
//						loopGuard = true;
//						tree->SelectItem(temp, toolpathSelected);
//						loopGuard = false;
//					}
//				}
//
//			}
//			temp = tree->GetNextSibling(temp);
//		}
	}

	return sel;
}

