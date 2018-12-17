///////////////////////////////////////////////////////////////////////////////
// Name               : MidiPort.h
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

#ifndef SRC_CONTROLLER_MIDIPORT_H_
#define SRC_CONTROLLER_MIDIPORT_H_

/*!\class MidiPort
 * \brief Connection to MIDI Instruments
 *
 * This class encapsulates the library portmidi to connect to MIDI inputs.
 * Latency compensation is not used.
 */

#if !(defined(linux) || defined(__linux))
#undef _USE_MIDI
#endif

#ifdef _USE_MIDI
#include "portmidi.h"
#endif
#include <cstddef>
#include <string>
#include <stdint.h>

#include <vector>

class MidiPort {
public:
	MidiPort();
	MidiPort(const MidiPort& other); //!< Copy constructor
	MidiPort& operator=(const MidiPort& other); ///< Assignment operator

	virtual ~MidiPort();
	void CycleLibrary(void); //!< Closes all open connections and cycles the portmidi library. Needed when a new device is connected, while the software is running.

	int GetDefaultInputDevice(void) const;
	int GetDefaultOutputDevice(void) const;
	int GetDeviceCount(void) const;
	std::string GetDeviceName(int nr) const;
	std::string GetDeviceInterfaceName(int nr) const;
	bool IsDeviceInput(int nr) const;
	bool IsDeviceOutput(int nr) const;
	bool IsDeviceAvailable(int nr) const; //!< i.e. not used by this class or somebody else.

	bool Open(int nr);
	bool IsOpen(void) const; //!< Has this instance an open connection to a device?
	void Close(void);

	bool IsInput(void) const;
	bool IsOutput(void) const;
	std::string GetName(void) const;
	std::string GetInterfaceName(void) const;
	int GetOpenDevice(void) const;

	bool Poll(void);
	bool PollEvent(uint8_t *data0, uint8_t *data1, uint8_t *data2);
	uint8_t cc[256]; // Returned CC values

	std::string error;
	bool IsLastInstance(void) const;

private:
#ifdef _USE_MIDI
	PortMidiStream *midi;
	const PmDeviceInfo* info;
	int opendevice;
	PmError status;
	PmError length;
	PmEvent buffer[1];
#endif

private:
	// The instance counter is needed, because the Pm_Initialize() and Pm_Terminate() functions are global.
	static size_t instancecounter;
};

#endif /* SRC_CONTROLLER_MIDIPORT_H_ */
