///////////////////////////////////////////////////////////////////////////////
// Name               : DataFrame.cpp
// Purpose            : 3D view of geometry.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.02.2010
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


#include "DataFrame.h"
#include <wx/log.h>

DataFrame::DataFrame(wxWindow* parent) :
	GUIDataFrame(parent)
{
	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);

	m_canvas->InsertData(&geometry);
}

DataFrame::~DataFrame()
{

}

void DataFrame::SetController(Control3D& control)
{
	m_canvas->SetController(control);
}

void DataFrame::OnChangeStereo3D(wxCommandEvent &event)
{
	if(m_canvas->stereoMode == 1){
		m_canvas->stereoMode = 0;
	}else{
		m_canvas->stereoMode = 1;
	}
	m_menuView->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

void DataFrame::OnClose(wxCommandEvent &event)
{
	Close();
}

void DataFrame::OnLoadSTLData(wxCommandEvent &event)
{
	wxFileDialog
			dialog(
					this,
					_("Open..."),
					_T(""),
					_T(""),
					_("All supported files (*.stl; *.gts)|*.stl;*.gts|Stereolithography files (STL files) (*.stl)|*.stl|GTS files (*.gts)|*.gts|All files|*.*"),
					wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(fileName.IsOk()) dialog.SetFilename(fileName.GetFullPath());
	if(dialog.ShowModal() == wxID_OK){
		fileName = dialog.GetPath();
		//wxLogMessage(_T("File Extension: ")+fileName.GetExt());
		AffineTransformMatrix identityMatrix;

		if(fileName.GetExt().CmpNoCase(_T("gts")) == 0){
			geometry.ReadGTS(fileName.GetFullPath(), identityMatrix);
		}else{
			geometry.ReadSTL(fileName.GetFullPath(), identityMatrix);
		}
		Refresh();
	}
}

