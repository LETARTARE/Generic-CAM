///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorLoadFromFile.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.02.2015
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

#include "GeneratorLoadFromFile.h"

#include <wx/sizer.h>
#include <wx/button.h>

#include "../gui/DisplaySettings.h"
#include "../project/ToolPath.h"

GeneratorLoadFromFile::GeneratorLoadFromFile(Project * project, size_t runNr,
		size_t toolpathNr) :
		Generator(project, runNr, toolpathNr)
{
	m_filePicker = NULL;
	m_staticTextLoadFile = NULL;
}

void GeneratorLoadFromFile::CopyFrom(const Generator * other)
{
	Generator::CopyFrom(other);

	const GeneratorLoadFromFile * temp =
			dynamic_cast <const GeneratorLoadFromFile*>(other);

	filename = temp->filename;
	wxLogMessage(_T("CopyFrom: ") + filename.GetFullName());
}

GeneratorLoadFromFile::~GeneratorLoadFromFile()
{
}

wxString GeneratorLoadFromFile::GetName(void) const
{
	return wxString(_T("Load from File"));
}

void GeneratorLoadFromFile::AddToPanel(wxPanel* panel,
		DisplaySettings* settings)
{
	Generator::AddToPanel(panel, settings);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);
	m_staticTextLoadFile = new wxStaticText(panel, wxID_ANY,
			wxT("Load G-Code from file..."), wxDefaultPosition, wxDefaultSize,
			0);
	m_staticTextLoadFile->Wrap(-1);
	bSizer1->Add(m_staticTextLoadFile, 0, wxALL, 5);
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);
	m_filePicker = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString,
			wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize,
			wxFLP_DEFAULT_STYLE);
	bSizer2->Add(m_filePicker, 1, wxALL, 5);
	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);
	panel->SetSizer(bSizer1);
	panel->Layout();
	bSizer1->Fit(panel);

	m_filePicker->SetPath(settings->lastProjectDirectory);
}

void GeneratorLoadFromFile::TransferDataToPanel(void) const
{
	if(filename.IsOk()) m_filePicker->SetPath(filename.GetFullPath());
}

void GeneratorLoadFromFile::TransferDataFromPanel(void)
{
	filename = m_filePicker->GetPath();
	wxLogMessage(_T("Filename: ") + filename.GetFullPath());
}

wxString GeneratorLoadFromFile::ToString(void) const
{
	return _T("");
}

void GeneratorLoadFromFile::FromString(const wxString& text)
{
}

void GeneratorLoadFromFile::GenerateToolpath(void)
{
	toolpathGenerated = false;
	errorOccured = false;
	if(!filename.IsOk()){
		errorOccured = true;
		output =
		_("Load G-Code: Not a valid file: >")+filename.GetFullName()+_T("<.");
		return;
	}
	if(!toolpath->ReadGCodeFile(filename)){
		errorOccured = true;
		output =
				_(
						"Load G-Code: Could not read file: >")+filename.GetFullName()+_T("<.");
		return;
	}
	toolpathGenerated = true;
}
