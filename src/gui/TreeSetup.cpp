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
#include "../Config.h"
#include <wx/debug.h>

TreeSetup::TreeSetup(FrameMain * parent, wxTreeCtrl * tree)
{
	maxId = 10;

	this->tree = tree;
	this->parent = parent;

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

void TreeSetup::SetSelecton(const Selection &sel)
{
	// Disable the function variable update. This function would otherwise
	// be called by the main window, whenever a selection changes.
	// The function UpdateSelection uses this flag to temporally disable variable update.
//	std::cout << "TreeSetup::SetSelecton(" << sel.ToString() << ")";
	if(loopGuard.TryLock() == wxMUTEX_BUSY){
//		std::cout << " -> wxMUTEX_BUSY;\n";
		return;
	}
//	std::cout << ";\n";
//	std::cout << "TreeSetup::SetSelecton -> loopGuard.Lock();\n";

	// Check if all groups are ok.
	if(!groupObjects.IsOk() || !groupRun.IsOk()){
//		std::cout << "TreeSetup::SetSelecton -> loopGuard.Unlock();\n";
		loopGuard.Unlock();
		return;
	}

	Project * const project = wxStaticCast(parent->GetDocument(), Project);

	// Updates for Objects:
	{
		wxTreeItemIdValue cookie;
		std::vector <size_t> objIDs = project->GetAllObjectIDs();
		std::vector <size_t>::const_iterator objID = objIDs.begin();

//		obj != project->objects.end(); ++obj){
//			SetAtLevel(2, obj->second.name, TreeItem::itemObject, obj->first);
//		}

		wxTreeItemId temp = tree->GetFirstChild(groupObjects, cookie);
		while(temp.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
			if(data != NULL && data->type == TreeItem::itemObject){
//				if(objID == objIDs.end()) break;
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
		std::vector <size_t> runIDs = project->GetAllRunIDs();
		std::vector <size_t>::const_iterator runID = runIDs.begin();

		wxTreeItemId nodeRun = tree->GetFirstChild(groupRun, cookie);
		while(nodeRun.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(nodeRun);
			if(data != NULL && data->type == TreeItem::itemRun){
//				if(runID == runIDs.end()) break;
				const bool flag = tree->IsSelected(nodeRun);
				const bool inSelection = sel.Has(Selection::Run, *runID);
				if(flag != inSelection){
					tree->SelectItem(nodeRun, inSelection);
				}

				wxTreeItemIdValue cookie2;
				std::vector <size_t> generatorIDs = project->GetAllGeneratorIDs(
						*runID);
				std::vector <size_t>::const_iterator generatorID =
						generatorIDs.begin();
				wxTreeItemId temp2 = tree->GetFirstChild(data->GetId(),
						cookie2);
				while(temp2.IsOk()){
					TreeItem * data2 = (TreeItem*) tree->GetItemData(temp2);
					if(data2 != NULL && data2->type == TreeItem::itemGenerator){
//						if(generatorID == generatorIDs.end()) break;
						const bool flag = tree->IsSelected(temp2);
						const bool inSelection = sel.Has(Selection::BaseRun,
								*runID, Selection::Generator, *generatorID);
						if(flag != inSelection){
							tree->SelectItem(temp2, inSelection);
						}
						++generatorID;
					}
					temp2 = tree->GetNextSibling(temp2);
				}
				++runID;
			}
			nodeRun = tree->GetNextSibling(nodeRun);
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
//	std::cout << "TreeSetup::SetSelecton -> loopGuard.Unlock();\n";
	loopGuard.Unlock();
}

Selection TreeSetup::GetSelection(void)
{
	if(!groupObjects.IsOk()){
		return Selection();
	}

	Project * const project = wxStaticCast(parent->GetDocument(), Project);

	Selection sel;

	// Updates for Objects:
	{
		wxTreeItemIdValue cookie;
		std::vector <size_t> objIDs = project->GetAllObjectIDs();
		std::vector <size_t>::const_iterator objID = objIDs.begin();
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

	// Updates for Run:
	{
		wxTreeItemIdValue cookie;
		std::vector <size_t> runIDs = project->GetAllRunIDs();
		std::vector <size_t>::const_iterator runID = runIDs.begin();
		wxTreeItemId temp = tree->GetFirstChild(groupRun, cookie);
		while(temp.IsOk()){
			TreeItem * data = (TreeItem*) tree->GetItemData(temp);
			if(data != NULL && data->type == TreeItem::itemRun){
				if(runID == runIDs.end()) break;
				if(tree->IsSelected(temp)) sel.Add(Selection::Run, *runID);
				wxTreeItemIdValue cookie2;
				std::vector <size_t> generatorIDs = project->GetAllGeneratorIDs(
						*runID);
				std::vector <size_t>::const_iterator generatorID =
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

void TreeSetup::Update(void)
{
	// Note: This function to update the tree is rather complicated, because it keeps the
	// expansion level and the selection if possible.

	if(loopGuard.TryLock() == wxMUTEX_BUSY) return;
	if(DEBUG) std::cout << "TreeSetup::Update -> loopGuard.Lock();\n";

	wxTreeItemId root = tree->GetRootItem();
	if(!root.IsOk()){
		root = tree->AddRoot(_T("root"), -1, -1,
				new TreeItem(TreeItem::itemProject));
	}

	Project * const project = wxStaticCast(parent->GetDocument(), Project);

	wxString tempName = tree->GetItemText(root);
	if(tempName != project->GetTitle()) tree->SetItemText(root,
			project->GetTitle());

	id[0] = root;
	currentLevel = 0;

	SetAtLevel(1, _("Objects"), TreeItem::itemGroupObjects, -1);
	groupObjects = id[1];

	bool foundItem = false;
	std::vector <size_t> objIDs = project->GetAllObjectIDs();
	for(std::vector <size_t>::const_iterator objID = objIDs.begin();
			objID != objIDs.end(); ++objID){
		SetAtLevel(2, project->Get3DObject(*objID)->name, TreeItem::itemObject,
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
	std::vector <size_t> runIDs = project->GetAllRunIDs();
	for(std::vector <size_t>::const_iterator runID = runIDs.begin();
			runID != runIDs.end(); ++runID){
		const Run * run = project->GetRun(*runID);
		SetAtLevel(2, run->name, TreeItem::itemRun, *runID);

		bool foundItem2 = false;
		for(std::vector <Generator*>::const_iterator generator =
				run->generators.begin(); generator != run->generators.end();
				++generator){
			if(DEBUG) std::cout << " => " << (*generator)->GetName() << "\n";

			SetAtLevel(3, (*generator)->GetName(), TreeItem::itemGenerator,
					(*generator)->GetID());
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
	tree->Expand(id[0]);

	if(DEBUG) std::cout << "TreeSetup::Update -> loopGuard.Unlock();\n";
	loopGuard.Unlock();
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

