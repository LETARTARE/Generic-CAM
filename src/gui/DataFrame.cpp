//============================================================================
// Name        : DataFrame.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


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

		if(fileName.GetExt().CmpNoCase(_T("gts")) == 0){
			geometry.ReadGTS(fileName.GetFullPath());
		}else{
			geometry.ReadSTL(fileName.GetFullPath());
		}
		Refresh();
	}
}

