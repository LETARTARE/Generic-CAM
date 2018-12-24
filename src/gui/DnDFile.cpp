///////////////////////////////////////////////////////////////////////////////
// Name               : DnDFile.cpp
// Purpose            : Drag&Drop target for files
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.06.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DnDFile.h"

#include "IDs.h"
#include "../project/command/CommandObjectLoad.h"

DnDFile::DnDFile(Project* project, FrameMain* parent)
{
	this->parent = parent;
	this->project = project;
}

bool DnDFile::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
	wxCommandProcessor* cmdProc = parent->GetDocument()->GetCommandProcessor();
	for(size_t n = 0; n < filenames.GetCount(); n++){
		wxFileName filename(filenames[n]);
		if(!filename.IsOk()){
			wxLogMessage
			(_("File is invalid: ") + filename.GetFullPath());
			return false;
		}

		if(filename.GetExt().CmpNoCase(_T("stl")) == 0
				|| filename.GetExt().CmpNoCase(_T("dxf")) == 0
				|| filename.GetExt().CmpNoCase(_T("gts")) == 0){
			cmdProc->Submit(
					new CommandObjectLoad(
							(_("Load Object: ") + filename.GetName()),
							project, filename.GetFullPath()));
			parent->TransferDataToWindow();
		}else{
			if(filename.GetExt().CmpNoCase(_T("zip")) == 0
					|| filename.GetExt().CmpNoCase(_T("prj")) == 0){
				if(!project->Load(filename)){
					wxLogMessage
					(
							_("Not a valid project file: ")
									+ filename.GetFullPath());
					return false;
				}
				cmdProc->ClearCommands();
				cmdProc->MarkAsSaved();
				parent->TransferDataToWindow();

			}else{
				wxLogMessage
				(
				_("Unknown file extension: ") + filename.GetFullPath());
				return false;
			}
		}
	}
	return true;
}
