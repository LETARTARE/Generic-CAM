///////////////////////////////////////////////////////////////////////////////
// Name               : DialogMachineControl.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.01.2015
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

#include "DialogMachineControl.h"
#include "DialogMachineDebugger.h"

#include "IDs.h"
#include "FrameMain.h"
#include "FrameParent.h"
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

DialogMachineControl::DialogMachineControl(wxWindow* parent) :
		GUIMachineControl(parent)
{
	m_menuPreferences->Append(ID_SETUPMIDI, _("Setup &MIDI"));
	m_menuPreferences->Append(ID_SETUPUNITS,
	_("Setup &Units") + wxT("\tCtrl+U"));
	X = Y = Z = 0.0;
	RX = RY = RZ = 0.0;

	groupXYZLimit = 1.0;
	groupRXRYRZLimit = M_PI;

	sliderSteps = 201;
	pageSize = 20;
	lineSize = 1;

#ifdef _USE_MIDI
	this->midi = NULL;
	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER,
			wxTimerEventHandler(DialogMachineControl::OnTimer),
			NULL, this);
	timer.Start(50);
#endif
}

DialogMachineControl::~DialogMachineControl()
{
#ifdef _USE_MIDI
	timer.Stop();
	this->Disconnect(wxEVT_TIMER,
			wxTimerEventHandler(DialogMachineControl::OnTimer),
			NULL, this);
#endif
}
#ifdef _USE_MIDI
void DialogMachineControl::SetMidiPort(MidiPort& midi)
{
	this->midi = &midi;
	for(uint8_t n = 0; n < 10; n++)
	this->midi->cc[n] = 64;
}
#endif

void DialogMachineControl::OnXClose(wxCloseEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}
void DialogMachineControl::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	this->Show(false);
}

void DialogMachineControl::OnScroll(wxScrollEvent& event)
{
	TransferDataFromWindowSliders();
	TransferDataToWindowTextbox();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_UPDATEMACHINESIMULATION);
	ProcessEvent(selectEvent);
}

void DialogMachineControl::OnTrack(wxScrollEvent& event)
{
	TransferDataFromWindowSliders();
	TransferDataToWindowTextbox();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_UPDATEMACHINESIMULATION);
	ProcessEvent(selectEvent);
}

bool DialogMachineControl::TransferDataToWindow(void)
{
	return TransferDataToWindowSliders() & TransferDataToWindowTextbox();
}

bool DialogMachineControl::TransferDataFromWindow(void)
{
	return TransferDataFromWindowSliders();
}

bool DialogMachineControl::TransferDataToWindowSliders(void)
{
	m_sliderX->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderY->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderZ->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderRX->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderRY->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);
	m_sliderRZ->SetRange(-((sliderSteps - 1) / 2), (sliderSteps - 1) / 2);

	m_sliderX->SetPageSize(pageSize);
	m_sliderY->SetPageSize(pageSize);
	m_sliderZ->SetPageSize(pageSize);
	m_sliderRX->SetPageSize(pageSize);
	m_sliderRY->SetPageSize(pageSize);
	m_sliderRZ->SetPageSize(pageSize);

	m_sliderX->SetLineSize(lineSize);
	m_sliderY->SetLineSize(lineSize);
	m_sliderZ->SetLineSize(lineSize);
	m_sliderRX->SetLineSize(lineSize);
	m_sliderRY->SetLineSize(lineSize);
	m_sliderRZ->SetLineSize(lineSize);

	m_sliderX->SetValue(round((X / groupXYZLimit) * (sliderSteps - 1) / 2));
	m_sliderY->SetValue(round((Y / groupXYZLimit) * (sliderSteps - 1) / 2));
	m_sliderZ->SetValue(round((Z / groupXYZLimit) * (sliderSteps - 1) / 2));
	m_sliderRX->SetValue(
			round((RX / groupRXRYRZLimit) * (sliderSteps - 1) / 2));
	m_sliderRY->SetValue(
			round((RY / groupRXRYRZLimit) * (sliderSteps - 1) / 2));
	m_sliderRZ->SetValue(
			round((RZ / groupRXRYRZLimit) * (sliderSteps - 1) / 2));
	return true;
}

bool DialogMachineControl::TransferDataFromWindowSliders(void)
{
	X = (float) m_sliderX->GetValue() / ((sliderSteps - 1) / 2) * groupXYZLimit;
	Y = (float) m_sliderY->GetValue() / ((sliderSteps - 1) / 2) * groupXYZLimit;
	Z = (float) m_sliderZ->GetValue() / ((sliderSteps - 1) / 2) * groupXYZLimit;

	RX = (float) m_sliderRX->GetValue() / ((sliderSteps - 1) / 2)
			* groupRXRYRZLimit;
	RY = (float) m_sliderRY->GetValue() / ((sliderSteps - 1) / 2)
			* groupRXRYRZLimit;
	RZ = (float) m_sliderRZ->GetValue() / ((sliderSteps - 1) / 2)
			* groupRXRYRZLimit;

	return true;
}

bool DialogMachineControl::TransferDataToWindowTextbox(void)
{
	DialogMachineDebugger * framemd = wxStaticCast(GetParent(),
			DialogMachineDebugger);
	FrameParent * frame =
	wxStaticCast(framemd->GetParent(), FrameMain)->GetParentFrame();
	CollectionUnits * settings = &(frame->units);

	m_staticTextUnitX->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitY->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitZ->SetLabel(settings->Distance.GetOtherName());
	m_staticTextUnitRX->SetLabel(settings->Angle.GetOtherName());
	m_staticTextUnitRY->SetLabel(settings->Angle.GetOtherName());
	m_staticTextUnitRZ->SetLabel(settings->Angle.GetOtherName());

	m_textCtrlX->SetValue(settings->Distance.TextFromSI(X));
	m_textCtrlY->SetValue(settings->Distance.TextFromSI(Y));
	m_textCtrlZ->SetValue(settings->Distance.TextFromSI(Z));
	m_textCtrlRX->SetValue(settings->Angle.TextFromSI(RX, 1));
	m_textCtrlRY->SetValue(settings->Angle.TextFromSI(RY, 1));
	m_textCtrlRZ->SetValue(settings->Angle.TextFromSI(RZ, 1));
	return true;
}

void DialogMachineControl::OnZero(wxMouseEvent& event)
{
	switch(event.GetId()){
	case ID_AXISX:
		X = 0.0;
		break;
	case ID_AXISY:
		Y = 0.0;
		break;
	case ID_AXISZ:
		Z = 0.0;
		break;
	case ID_AXISRX:
		RX = 0.0;
		break;
	case ID_AXISRY:
		RY = 0.0;
		break;
	case ID_AXISRZ:
		RZ = 0.0;
		break;
	}
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_UPDATEMACHINESIMULATION);
	ProcessEvent(selectEvent);
}

void DialogMachineControl::OnTextChanged(wxCommandEvent& event)
{
	DialogMachineDebugger * framemd = wxStaticCast(GetParent(),
			DialogMachineDebugger);
	FrameParent * frame = wxStaticCast(framemd->GetParent()->GetParent(),
			FrameParent);
	CollectionUnits * settings = &(frame->units);
	switch(event.GetId()){
	case ID_TEXTX:
		m_textCtrlX->GetValue().ToDouble(&X);
		X = settings->Distance.ToSI(X);
		break;
	case ID_TEXTY:
		m_textCtrlY->GetValue().ToDouble(&Y);
		Y = settings->Distance.ToSI(Y);
		break;
	case ID_TEXTZ:
		m_textCtrlZ->GetValue().ToDouble(&Z);
		Z = settings->Distance.ToSI(Z);
		break;
	case ID_TEXTRX:
		m_textCtrlRX->GetValue().ToDouble(&RX);
		RX = settings->Angle.ToSI(RX);
		break;
	case ID_TEXTRY:
		m_textCtrlRY->GetValue().ToDouble(&RY);
		RY = settings->Angle.ToSI(RY);
		break;
	case ID_TEXTRZ:
		m_textCtrlRZ->GetValue().ToDouble(&RZ);
		RZ = settings->Angle.ToSI(RZ);
		break;
	}
	TransferDataToWindowSliders();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_UPDATEMACHINESIMULATION);
	ProcessEvent(selectEvent);
}

Project* DialogMachineControl::GetProject(void)
{
	DialogMachineDebugger * framemd = wxStaticCast(GetParent(),
			DialogMachineDebugger);
	FrameMain * frame = wxStaticCast(framemd->GetParent(), FrameMain);
	Project * project = wxStaticCast(frame->GetDocument(), Project);
	return project;
}
#ifdef _USE_MIDI
void DialogMachineControl::OnTimer(wxTimerEvent& event)
{
	if(midi == NULL) return;
	if(!IsShown()) return;
	if(!midi->Poll()) return;

	X = ((double) midi->cc[1] - 64.0) / 64.0;
	Y = ((double) midi->cc[2] - 64.0) / 64.0;
	Z = ((double) midi->cc[3] - 64.0) / 64.0;
	RX = ((double) midi->cc[4] - 64.0) / 64.0 * M_PI;
	RY = ((double) midi->cc[5] - 64.0) / 64.0 * M_PI;
	RZ = ((double) midi->cc[6] - 64.0) / 64.0 * M_PI;

	TransferDataToWindowSliders();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
			ID_UPDATEMACHINESIMULATION);
	ProcessEvent(selectEvent);

}
#endif
