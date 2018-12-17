///////////////////////////////////////////////////////////////////////////////
// Name               : MidiPort.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.09.2017
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

#include "MidiPort.h"

#include <cassert>

size_t MidiPort::instancecounter = 0;

MidiPort::MidiPort() {
#ifdef _USE_MIDI
	midi = NULL;
	info = NULL;
	opendevice = -1;
	status = pmNoError;
	length = pmNoData;
#endif
	for (uint16_t i = 0; i < 256; i++)
		cc[i] = 0;

	instancecounter++;
#ifdef _USE_MIDI
	if(instancecounter == 1) Pm_Initialize();
#endif
}

MidiPort::MidiPort(const MidiPort& other) {
	if (this == &other)
		return;
	++instancecounter;
#ifdef _USE_MIDI
	midi = NULL;
	info = NULL;
	opendevice = -1;
	status = other.status;
	length = other.length;
#endif
	for (uint16_t i = 0; i < 256; i++)
		cc[i] = other.cc[i];
}

MidiPort& MidiPort::operator =(const MidiPort& other) {
#ifdef _USE_MIDI
	midi = NULL;
	info = NULL;
	opendevice = -1;
	status = other.status;
	length = other.length;
#endif
	for (uint16_t i = 0; i < 256; i++)
		cc[i] = other.cc[i];

	return *this;
}

MidiPort::~MidiPort() {
#ifdef _USE_MIDI
	if(midi != NULL) Pm_Close(midi);
	if(instancecounter == 1) Pm_Terminate();
#endif
	assert(instancecounter > 0);
	instancecounter--;
}

bool MidiPort::IsLastInstance(void) const {
	return (instancecounter == 1);
}

void MidiPort::CycleLibrary(void) {
	this->Close();
	if (instancecounter == 1) {
#ifdef _USE_MIDI
		Pm_Terminate();
		Pm_Initialize();
#endif
	} else {
		// More than one instance: This causes problems for the other instances that are unaware of this cycling.
	}
}

int MidiPort::GetDefaultInputDevice(void) const {
#ifdef _USE_MIDI
	return Pm_GetDefaultInputDeviceID();
#else
	return -1;
#endif
}

int MidiPort::GetDefaultOutputDevice(void) const {
#ifdef _USE_MIDI
	return Pm_GetDefaultOutputDeviceID();
#else
	return -1;
#endif
}

int MidiPort::GetDeviceCount(void) const {
	int temp = 0;
#ifdef _USE_MIDI
	while(Pm_GetDeviceInfo(temp) != NULL)
	temp++;
#endif
	return temp;
}

std::string MidiPort::GetDeviceName(int nr) const {
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) {
		return std::string("");
	}
	std::string name = temp->name;
	return name;
#else
	return std::string("");
#endif
}

std::string MidiPort::GetDeviceInterfaceName(int nr) const {
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) {
		return std::string("");
	}
	std::string name = temp->interf;
	return name;
#else
	return std::string("");
#endif
}

bool MidiPort::IsDeviceInput(int nr) const {
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) return false;
	return temp->input;
#else
	return false;
#endif
}

bool MidiPort::IsDeviceOutput(int nr) const {
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) return false;
	return temp->output;
#else
	return false;
#endif
}

bool MidiPort::IsDeviceAvailable(int nr) const {
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) return false;
	return !temp->opened;
#else
	return false;
#endif
}

bool MidiPort::Open(int nr) {
	this->Close();
	if (!IsDeviceInput(nr)) {
		error = "Not an input device.";
		return false;
	}
#ifdef _USE_MIDI
	PmError err = Pm_OpenInput(&midi, nr, NULL, 100, NULL, NULL);
	switch(err) {
		case pmNoError:
		error.clear();
		break;
		case pmHostError:
		error = "Host error.";
		break;
		case pmInvalidDeviceId:
		error = "Invalid device id.";
		break;
		case pmInsufficientMemory:
		error = "Insufficient memory.";
		break;
		case pmBufferTooSmall:
		error = "Buffer too small.";
		break;
		case pmBufferOverflow:
		error = "Buffer overflow.";
		break;
		case pmBadPtr:
		error = "Bad pointer.";
		break;
		case pmInternalError:
		error = "Internal error.";
		break;
		case pmBufferMaxSize:
		error = "Max buffer size.";
		break;
		default:
		error = "Unknown error.";
		break;
	}
	info = Pm_GetDeviceInfo(nr);
	opendevice = nr;
//	Pm_SetFilter(midi, PM_FILT_CONTROL);
	while(Pm_Poll(midi))
	Pm_Read(midi, buffer, 1);
	return (err == pmNoError);
#else
	return false;
#endif
}

bool MidiPort::IsOpen(void) const {
#ifdef _USE_MIDI
	return (midi != NULL);
#else
	return false;
#endif
}

void MidiPort::Close(void) {
#ifdef _USE_MIDI
	info = NULL;
	if(midi != NULL) Pm_Close(midi);
	midi = NULL;
	opendevice = -1;
#endif
}

int MidiPort::GetOpenDevice(void) const {
#ifdef _USE_MIDI
	return opendevice;
#else
	return -1;
#endif
}

std::string MidiPort::GetName(void) const {
#ifdef _USE_MIDI
	if(info == NULL) return std::string("");
	return std::string(info->name);
#else
	return std::string("");
#endif
}

std::string MidiPort::GetInterfaceName(void) const {
#ifdef _USE_MIDI
	if(info == NULL) return std::string("");
	return std::string(info->interf);
#else
	return std::string("");
#endif
}

bool MidiPort::IsInput(void) const {
#ifdef _USE_MIDI
	if(info == NULL) return false;
	return (info->input);
#else
	return false;
#endif
}

bool MidiPort::IsOutput(void) const {
#ifdef _USE_MIDI
	if(info == NULL) return false;
	return (info->output);
#else
	return false;
#endif
}

bool MidiPort::Poll(void) {
#ifdef _USE_MIDI
	if(midi == NULL) return false;
	if(!Pm_Poll(midi)) return false;
	while(Pm_Poll(midi)) {
		if(Pm_Read(midi, buffer, 1) > 0) {
			uint8_t ch = Pm_MessageData1(buffer[0].message);
			uint8_t val = Pm_MessageData2(buffer[0].message);
			cc[ch] = val;
		}
	}
	return true;
#else
	return false;
#endif
}

bool MidiPort::PollEvent(uint8_t* data0, uint8_t* data1, uint8_t* data2) {
#ifdef _USE_MIDI
	if(midi == NULL) return false;
	if(!Pm_Poll(midi)) return false;
	if(Pm_Read(midi, buffer, 1) > 0) {
		*data0 = Pm_MessageStatus(buffer[0].message);
		*data1 = Pm_MessageData1(buffer[0].message);
		*data2 = Pm_MessageData2(buffer[0].message);
		return true;
	}
#endif
	return false;
}
