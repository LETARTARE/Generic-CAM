///////////////////////////////////////////////////////////////////////////////
// Name               : DialogPostProcess.cpp
// Purpose            : Dialog for exporting toolpaths
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.12.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogPostProcess.h"

#include "FrameParent.h"
#include "FrameMain.h"

DialogPostProcess::DialogPostProcess(wxWindow* parent) :
		GUIPostProcess(parent)
{
	FrameMain * frame = wxStaticCast(parent, FrameMain);
	m_filePickerExport->SetInitialDirectory(
			frame->filepaths.lastToolpathDirectory);
	TransferDataToWindow();
	UpdateParameter();
}

void DialogPostProcess::OnXClose(wxCloseEvent& event)
{
	this->Show(false);
}

void DialogPostProcess::OnRefresh(wxCommandEvent& event)
{
	postprocessors.Refresh();
	TransferDataToWindow();
	UpdateParameter();
}

void DialogPostProcess::SetRunGenerator(size_t runID)
{
	selected = Selection(Selection::Run, runID);
}

void DialogPostProcess::SetRunGenerator(size_t runID, size_t generatorID)
{
	selected = Selection(Selection::BaseRun, runID, Selection::Generator,
			generatorID);
}

void DialogPostProcess::UpdateParameter(void)
{
	int processorID = m_choiceSelect->GetSelection();
	if(processorID >= 0){
		m_propertyGrid->Clear();
		std::map <std::string, std::string> parameter =
				postprocessors[processorID].GetParameter();
		for(std::map <std::string, std::string>::const_iterator it =
				parameter.begin(); it != parameter.end(); ++it){

			wxPGProperty *p = new wxStringProperty(it->first, wxPG_LABEL);
			if(it->second.find_first_of((char) 10) == std::string::npos){
				p = new wxStringProperty(it->first, wxPG_LABEL);
			}else{
				p = new wxLongStringProperty(it->first, wxPG_LABEL);
			}
			p->SetValue(it->second);
			m_propertyGrid->Append(p);
		}
	}
}
void DialogPostProcess::OnChoice(wxCommandEvent& event)
{
	TransferDataToWindow();
	UpdateParameter();
}

void DialogPostProcess::OnPropertyGridChange(wxPropertyGridEvent& event)
{
	int processorID = m_choiceSelect->GetSelection();
	if(processorID < 0) return;
	wxPGProperty* p = event.GetProperty();
	if(!p) return;
	postprocessors[processorID].SetParameter(std::string(p->GetName().mb_str()),
			std::string(p->GetValueAsString().mb_str()));
}

bool DialogPostProcess::TransferDataToWindow(void)
{
	std::vector <std::string> temp = postprocessors.GetNames();

	wxArrayString processornames;
	for(size_t n = 0; n < temp.size(); ++n){
		processornames.Add(wxString(temp[n]));
	}
	wxArrayString oldNames = m_choiceSelect->GetStrings();
	if(oldNames != processornames) m_choiceSelect->Set(processornames);
	if(oldNames.IsEmpty() && !processornames.IsEmpty()) m_choiceSelect->SetSelection(
			0);
	return true;
}

void DialogPostProcess::OnExport(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	Project* project = wxStaticCast(frame->GetDocument(), Project);
	if(!project->Has(selected)) return;

	int processorID = m_choiceSelect->GetSelection();
	if(processorID < 0) return;

	std::vector <CNCPosition> toolpath;
	size_t runID = -1;

	if(selected.IsBaseType(Selection::BaseRun)){
		runID = selected.GetBaseID();
		const Run & run = project->GetRun(runID);
		for(std::set <size_t>::const_iterator generatorID = selected.begin();
				generatorID != selected.end(); ++generatorID){
			const std::vector <CNCPosition> &other = run.generators.at(
					*generatorID)->toolpath;
			toolpath.insert(toolpath.end(), other.begin(), other.end());
		}
		postprocessors[processorID].SetCoordinateSystem(run.origin);
	}
	if(selected.IsType(Selection::Run)){
		assert(selected.Size() == 1);
		runID = selected[0];
		const Run & run = project->GetRun(runID);
		for(std::map <size_t, Generator*>::const_iterator generator =
				run.generators.begin(); generator != run.generators.end();
				++generator){
			const std::vector <CNCPosition> &other =
					(generator->second)->toolpath;
			toolpath.insert(toolpath.end(), other.begin(), other.end());
		}
		postprocessors[processorID].SetCoordinateSystem(run.origin);
	}
	postprocessors[processorID].SetToolPath(&toolpath);
	std::string filename = std::string(
			m_filePickerExport->GetFileName().GetFullPath().mb_str());
	postprocessors[processorID].SaveGCode(filename);
}

