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

	m_ribbonButtonBarSettings->ToggleButton(ID_MACHINEDEBUGGERSHOWCONTROLLER,
			machineControl->IsShown());

	m_ribbonButtonBarSettings->ToggleButton(ID_MACHINEDEBUGGERTOGGLESTEREO3D,
			m_canvas->stereoMode != stereoOff);
	FrameMain * frame = wxStaticCast(parent, FrameMain);
	SettingsStereo3D * settings = &(frame->GetParentFrame()->settingsStereo3D);
	settings->WriteToCanvas(m_canvas);
	TransferDataToWindow();
}

DialogMachineDebugger::~DialogMachineDebugger()
{
	this->Disconnect(ID_UPDATEMACHINESIMULATION, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(DialogMachineDebugger::Update));
}
#ifdef _USE_MIDI
void DialogMachineDebugger::SetMidiPort(MidiPort& midi)
{
	this->midi = &midi;
	if(machineControl != NULL) machineControl->SetMidiPort(midi);
}
#endif

void DialogMachineDebugger::Update(wxCommandEvent& event)
{
	CNCPosition pos;
	pos.Set(machineControl->X, machineControl->Y, machineControl->Z);
	const double six = sin(machineControl->RX);
	const double siy = sin(machineControl->RY);
	const double siz = sin(machineControl->RZ);
	const double cox = cos(machineControl->RX);
	const double coy = cos(machineControl->RY);
	const double coz = cos(machineControl->RZ);
	pos.normal.x = six * siz + cox * coz * siy;
	pos.normal.y = cox * siy * siz - coz * six;
	pos.normal.z = cox * coy;
	machine.SetPosition(pos);
	machine.Assemble();
	TransferDataToWindow();
	this->Refresh();
}

bool DialogMachineDebugger::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	SettingsStereo3D * settings = &(frame->GetParentFrame()->settingsStereo3D);
	settings->WriteToCanvas(m_canvas);
	m_ribbonButtonBarSettings->ToggleButton(ID_MACHINEDEBUGGERSHOWCONTROLLER,
			machineControl->IsShown());
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

void DialogMachineDebugger::OnScriptEvaluate(wxRibbonButtonBarEvent& event)
{
	wxCommandEvent temp(event);
	OnScriptEvaluate(temp);
}

void DialogMachineDebugger::OnScriptEvaluate(wxCommandEvent& event)
{
	TransferDataFromWindow();
	machine.EvaluateDescription();
	machine.MoveToGlobalZero();
	Update(event);
}

void DialogMachineDebugger::OnMachineLoad(wxRibbonButtonBarEvent& event)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionFilepaths * filepaths = frame->GetFilePaths();
	wxFileDialog dialog(this, _("Open machine description..."), _T(""), _T(""),
			_(
					"All machine descriptions  (*.lua;*.zip)|*.lua;*.zip|Machine descriptions (LUA Files)  (*.lua)|*.lua|Packed Machine descriptions  (*.zip)|*.zip|Text files  (*.txt)|*.txt|All files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(filepaths->lastMachineDirectory)){
		dialog.SetDirectory(filepaths->lastMachineDirectory);
	}else{
		if(wxDir::Exists(filepaths->lastProjectDirectory)){
			dialog.SetDirectory(filepaths->lastProjectDirectory);
		}
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName file(dialog.GetPath());
		if(machine.Load(file)){
			SetTitle(file.GetName());
			m_textCtrlScript->SetValue(machine.machineDescription);
			m_textCtrlScript->SetModified(false);
			machine.EvaluateDescription();
		}
		TransferDataToWindow();
	}
}

void DialogMachineDebugger::OnMachineSave(wxRibbonButtonBarEvent& event)
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

void DialogMachineDebugger::OnToggleStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == stereoOff){
		m_canvas->stereoMode = stereoAnaglyph;
	}else{
		m_canvas->stereoMode = stereoOff;
	}
	m_ribbonButtonBarSettings->ToggleButton(ID_MACHINEDEBUGGERTOGGLESTEREO3D,
			m_canvas->stereoMode != stereoOff);
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	SettingsStereo3D * settings = &(frame->GetParentFrame()->settingsStereo3D);
	settings->WriteToCanvas(m_canvas);
	m_canvas->Refresh();
}

void DialogMachineDebugger::OnShowPreferencesMenu(wxRibbonButtonBarEvent& event)
{
	wxMenu menu;
	menu.Append(ID_SETUPUNITS, _("Setup &Units") + wxT("\tCtrl+U"));
	menu.Append(ID_SETUPSTEREO3D, _("Setup &Stereo 3D"));
	menu.Append(ID_SETUPCONTROLLER, _("Setup 6DOF &Controller"));
#ifdef _USE_MIDI
	menu.Append(ID_SETUPMIDI, _("Setup &MIDI"));
#endif
	event.PopupMenu(&menu);
}
