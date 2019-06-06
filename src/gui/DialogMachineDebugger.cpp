///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineDebugger.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.01.2015
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

#include "../StdInclude.h"

#include "DialogMachineDebugger.h"

#include "IDs.h"
#include <wx/textfile.h>
#include <wx/dir.h>

#include "FrameMain.h"
#include "FrameParent.h"
#include "SettingsStereo3D.h"

DialogMachineDebugger::DialogMachineDebugger(wxWindow * parent) :
		GUIMachineDebugger(parent)
{
	m_menuPreferences->Append(ID_SETUPCONTROLLER, _("Setup 6DOF &Controller"));
	m_menuPreferences->Append(ID_SETUPSTEREO3D, _("Setup &Stereo 3D"));
	m_menuPreferences->Append(ID_SETUPMIDI, _("Setup &MIDI"));
	m_menuPreferences->Append(ID_SETUPUNITS,
	_("Setup &Units") + wxT("\tCtrl+U"));

	this->Connect(ID_UPDATEMACHINESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(DialogMachineDebugger::Update));

	machineControl = new DialogMachineControl(this);
#ifdef _USE_MIDI
	this->midi = NULL;
#endif

	m_canvas->InsertMachine(&machine);
//	machine.Load(wxFileName(_T("machines/testmachine.lua")));
	machine.EvaluateDescription();
	m_textCtrlScript->SetValue(machine.machineDescription);

	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	TransferDataToWindow();
}

DialogMachineDebugger::~DialogMachineDebugger()
{
	this->Disconnect(ID_UPDATEMACHINESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(DialogMachineDebugger::Update));
}

void DialogMachineDebugger::SetMidiPort(MidiPort& midi)
{
	this->midi = &midi;
	if(machineControl != NULL) machineControl->SetMidiPort(midi);
}

void DialogMachineDebugger::Update(wxCommandEvent& event)
{
	machine.currentpos.X = machineControl->X;
	machine.currentpos.Y = machineControl->Y;
	machine.currentpos.Z = machineControl->Z;
	machine.currentpos.A = machineControl->A;
	machine.currentpos.B = machineControl->B;
	machine.currentpos.C = machineControl->C;
	machine.currentpos.U = machineControl->U;
	machine.currentpos.V = machineControl->V;
	machine.currentpos.W = machineControl->W;
	machine.Assemble();
	TransferDataToWindow();
	this->Refresh();
}

bool DialogMachineDebugger::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	SettingsStereo3D * settings = &(frame->GetParentFrame()->settingsStereo3D);
	settings->WriteToCanvas(m_canvas);
	if(!this->IsShown()){
		if(machineControl->IsShown()) machineControl->Show(false);
		return false;
	}
	m_textCtrlOutput->SetValue(machine.textOut);
	if(machineControl->IsShown()) machineControl->TransferDataToWindow();
	this->Refresh();
	return true;
}

bool DialogMachineDebugger::TransferDataFromWindow(void)
{
	machine.machineDescription = m_textCtrlScript->GetValue();
	return true;
}

void DialogMachineDebugger::OnXClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	machineControl->Show(false);
	this->Show(false);
}

void DialogMachineDebugger::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	machineControl->Show(false);
	this->Show(false);
}

void DialogMachineDebugger::OnScriptEvaluate(wxCommandEvent& event)
{
	TransferDataFromWindow();
	machine.EvaluateDescription();
	machine.Reset();
	machine.currentpos.X = machineControl->X;
	machine.currentpos.Y = machineControl->Y;
	machine.currentpos.Z = machineControl->Z;
	machine.currentpos.A = machineControl->A;
	machine.currentpos.B = machineControl->B;
	machine.currentpos.C = machineControl->C;
	machine.currentpos.U = machineControl->U;
	machine.currentpos.V = machineControl->V;
	machine.currentpos.W = machineControl->W;
	machine.Assemble();
	TransferDataToWindow();
}

void DialogMachineDebugger::OnMachineLoad(wxCommandEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionFilepaths * settings = &(frame->filepaths);
	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
			_(
					"All machine descriptions  (*.lua;*.zip)|*.lua;*.zip|Machine descriptions (LUA Files)  (*.lua)|*.lua|Packed Machine descriptions  (*.zip)|*.zip|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(settings->lastMachineDirectory)){
		dialog.SetDirectory(settings->lastMachineDirectory);
	}else{
		if(wxDir::Exists(settings->lastProjectDirectory)){
			dialog.SetDirectory(settings->lastProjectDirectory);
		}
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName file(dialog.GetPath());
		machine.Load(file);
		m_textCtrlScript->SetValue(machine.machineDescription);
		m_textCtrlScript->SetModified(false);
		machine.EvaluateDescription();
		TransferDataToWindow();
	}
}

void DialogMachineDebugger::OnMachineSave(wxCommandEvent& event)
{

	wxFileName fileName;
	wxFileDialog dialog(this, _("Save machine description..."), _T(""), _T(""),
			_(
					"Machine descriptions (LUA Files)  (*.lua)|*.lua|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(machine.fileName.IsOk()) dialog.SetPath(machine.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		TransferDataFromWindow();
		wxString fileName = dialog.GetPath();
		wxTextFile file(fileName);
		if(file.Exists())
			file.Open();
		else
			file.Create();
		file.Clear();
		file.AddLine(machine.machineDescription, wxTextFileType_None);
		file.Write();
		file.Close();
		TransferDataToWindow();
	}
}

void DialogMachineDebugger::OnShowController(wxCommandEvent& event)
{
	machineControl->Show(!machineControl->IsShown());
	machineControl->TransferDataToWindow();
}

void DialogMachineDebugger::OnChangeStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode != stereoOff){
		m_canvas->stereoMode = stereoOff;
	}else{
		m_canvas->stereoMode = stereoAnaglyph;
	}
	m_menuView->Check(ID_VIEWSTEREO3D, m_canvas->stereoMode != stereoOff);
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	SettingsStereo3D * settings = &(frame->GetParentFrame()->settingsStereo3D);
	settings->WriteToCanvas(m_canvas);
	m_canvas->Refresh();
}
