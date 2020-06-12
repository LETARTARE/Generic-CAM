///////////////////////////////////////////////////////////////////////////////
// Name               : DialogToolbox.h
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

#ifndef TOOLBOXFRAME_H_
#define TOOLBOXFRAME_H_

#include "../StdInclude.h"
#include "../project/ToolBox.h"
#include "../project/Project.h"
#include "gui.h"

class DialogToolbox:public GUIToolbox {
private:
	class ToolData:public wxClientData {
	public:
		ToolData(size_t toolbox, size_t tool = 0, bool isTool = false) :
				toolbox(toolbox), tool(tool), isTool(isTool)
		{
		}
		size_t toolbox;
		size_t tool;
		bool isTool;
	};

public:
	DialogToolbox(wxWindow* parent);
	virtual ~DialogToolbox();

	void Update(bool refreshDirectory = false);

protected:
	size_t selectedToolBox;
	size_t selectedTool;
	size_t selectedElement;

	Tool tempTool;
	wxTreeListItem projectfolder;
	std::vector <ToolBox> toolboxes;
	std::vector <wxTreeListItem> toolboxfolders;

private:

	void AddToolToListCtrl(wxTreeListItem & item, const Tool & tool);

public:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

	void OnXClose(wxCloseEvent& event);
	void OnToolChecked(wxTreeListEvent& event) wxOVERRIDE;;
	void OnToolContextMenu(wxTreeListEvent& event) wxOVERRIDE;
	void OnToolboxExpanding(wxTreeListEvent& event) wxOVERRIDE;
	void OnToolSelectionChanged(wxTreeListEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnRadioBox(wxCommandEvent& event);
	void OnCheckBox(wxCommandEvent& event);
	void OnSegmentAdd(wxCommandEvent& event);
	void OnSegmentDelete(wxCommandEvent& event);
	void OnItemBeginDrag(wxDataViewEvent& event);
	void OnItemDrop(wxDataViewEvent& event);
	void OnSelectionChanged(wxDataViewEvent& event);
};

#endif /* TOOLBOXFRAME_H_ */
