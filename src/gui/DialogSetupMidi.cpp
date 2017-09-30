///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupMidi.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.09.2017
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

#include "DialogSetupMidi.h"

DialogSetupMidi::DialogSetupMidi(wxWindow* parent, MidiPort* midi) :
		GUISetupMidi(parent)
{
	this->midi = midi;
	TransferDataToWindow();

	timer.SetOwner(this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(DialogSetupMidi::OnTimer),
	NULL, this);

}

DialogSetupMidi::~DialogSetupMidi()
{
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(DialogSetupMidi::OnTimer),
	NULL, this);
}

bool DialogSetupMidi::TransferDataToWindow(void)
{
	if(midi == NULL) return false;

	const size_t N = midi->GetDeviceCount();
	m_listBoxDevices->Clear();
	const size_t din = midi->GetDefaultInputDevice();
	const size_t dout = midi->GetDefaultOutputDevice();
	for(size_t n = 0; n < N; n++){
		std::string temp = midi->GetDeviceName(n);
		if(midi->IsDeviceInput(n)) temp += " - Input";
		if(midi->IsDeviceOutput(n)) temp += " - Output";
		if(din == n) temp += " <- Default input device";
		if(dout == n) temp += " <- Default output device";
		if(!midi->IsDeviceAvailable(n)) temp += " (device open)";
		m_listBoxDevices->Append(temp);
	}
	m_listBoxDevices->SetSelection(midi->GetOpenDevice());

	if(this->IsShown() && !timer.IsRunning()) timer.Start(100);

	return true;
}

bool DialogSetupMidi::TransferDataFromWindow(void)
{
	return false;
}

void DialogSetupMidi::OnCloseX(wxCloseEvent& event)
{
	timer.Stop();
	this->Hide();
}

void DialogSetupMidi::OnSelect(wxCommandEvent& event)
{

}

void DialogSetupMidi::OnRefresh(wxCommandEvent& event)
{
	TransferDataToWindow();
}

void DialogSetupMidi::OnCycle(wxCommandEvent& event)
{
	midi->CycleLibrary();
	TransferDataToWindow();
}

void DialogSetupMidi::OnConnect(wxCommandEvent& event)
{
	midi->Open(m_listBoxDevices->GetSelection());
	TransferDataToWindow();
}

void DialogSetupMidi::OnDisconnect(wxCommandEvent& event)
{
	midi->Close();
	TransferDataToWindow();
}

void DialogSetupMidi::OnTimer(wxTimerEvent& event)
{
	uint8_t status, data1, data2;
	uint8_t channel;
	while(midi->PollEvent(&status, &data1, &data2)){
		channel = status & 0xf;
		status >>= 4;
		wxString temp;
		switch(status){
		case 8:
			temp = wxString::Format(
					_T("Channel: %2u Note Off Data: %3u, %3u\n"), channel,
					data1, data2);
			break;
		case 9:
			temp = wxString::Format(_T("Channel: %2u Note On Data: %3u, %3u\n"),
					channel, data1, data2);
			break;
		case 10:
			temp = wxString::Format(
					_T("Channel: %2u Polyphonic-Aftertouch Data: %3u, %3u\n"),
					channel, data1, data2);
			break;
		case 11:
			temp = wxString::Format(
					_T("Channel: %2u Control Change: CC[%3u] = %3u\n"), channel,
					data1, data2);
			break;
		case 12:
			temp = wxString::Format(
					_T("Channel: %2u Program Change Data: %3u, %3u\n"), channel,
					data1, data2);
			break;
		case 13:
			temp = wxString::Format(
					_T("Channel: %2u Mono-Aftertouch Data: %3u, %3u\n"),
					channel, data1, data2);
			break;
		case 14:
			temp = wxString::Format(
					_T("Channel: %2u Pitch Bend Data: %3u, %3u\n"), channel,
					data1, data2);
			break;
		case 15:
			temp = wxString::Format(_T("System Message %2u Data: %3u, %3u\n"),
					channel, data1, data2);
			break;
		default:
			temp = wxString::Format(
					_T("Channel: %2u Status: %2u Data: %3u, %3u\n"), channel,
					status, data1, data2);
			break;
		}

		m_textCtrlReceived->AppendText(temp);
	}
}

void DialogSetupMidi::OnClose(wxCommandEvent& event)
{
	timer.Stop();
	this->Hide();
}

void DialogSetupMidi::OnClear(wxMouseEvent& event)
{
	m_textCtrlReceived->SetValue(_T(""));
}
