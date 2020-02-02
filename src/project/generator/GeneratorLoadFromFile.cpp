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

#include <iostream>

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/log.h>

GeneratorLoadFromFile::GeneratorLoadFromFile()
{
	m_filePicker = NULL;
	m_staticTextLoadFile = NULL;
}

void GeneratorLoadFromFile::CopyParameterFrom(const Generator * other)
{
	Generator::CopyParameterFrom(other);

	const GeneratorLoadFromFile * temp =
			dynamic_cast <const GeneratorLoadFromFile*>(other);

	filename = temp->filename;
	wxLogMessage
	(_T("CopyFrom: ") + filename.GetFullName());
}

GeneratorLoadFromFile::~GeneratorLoadFromFile()
{
}

wxString GeneratorLoadFromFile::GetTypeName(void) const
{
	return wxString(_T("Load from File"));
}

wxSizer * GeneratorLoadFromFile::AddToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
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
			wxFLP_DEFAULT_STYLE | wxFLP_USE_TEXTCTRL);
	bSizer2->Add(m_filePicker, 1, wxALL, 5);

	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	m_filePicker->SetPath(_T(""));
	return bSizer1;
}

void GeneratorLoadFromFile::TransferDataToPanel(wxPanel* panel,
		CollectionUnits* settings) const
{
	if(filename.IsOk()) m_filePicker->SetPath(filename.GetFullPath());
}

void GeneratorLoadFromFile::TransferDataFromPanel(CollectionUnits* settings)
{
	filename = m_filePicker->GetPath();
	wxLogMessage
	(_T("Filename: ") + filename.GetFullPath());
}

bool GeneratorLoadFromFile::operator ==(const Generator& b) const
{
	const GeneratorLoadFromFile * temp = dynamic_cast <const GeneratorLoadFromFile*>(&b);
		std::cout << "GeneratorLoadFromFile::operator ==\n";
		if(!(this->Generator::operator ==(b))) return false;
		if(this->filename != temp->filename) return false;
		return true;
}

void GeneratorLoadFromFile::GenerateToolpath(const Run &run,
		const std::map <size_t, Object> &objects, const Tool &tool,
		const DexelTarget &base)
{
	toolpathGenerated = false;
	errorOccured = false;
	if(!filename.IsOk()){
		errorOccured = true;
		output =
		_("Load G-Code: Not a valid file: >")+filename.GetFullName()+_T("<.");
		return;
	}
//	if(!toolpath.ReadGCodeFile(filename)){
//		errorOccured = true;
//		output =
//				_(
//						"Load G-Code: Could not read file: >")+filename.GetFullName()+_T("<.");
//		return;
//	}
//	toolpathGenerated = true;
}
