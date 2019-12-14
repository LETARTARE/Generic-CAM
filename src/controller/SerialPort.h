///////////////////////////////////////////////////////////////////////////////
// Name               : SerialPort.h
// Purpose            : A serial port class for Linux and Windows
// Thread Safe        : No
// Platform dependent : Yes
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 08.09.2002
// Copyright          : (C) 2002 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

/*!\class SerialPort
 * \brief Serial port class for Linux and Windows
 *
 * Encapsulates the intricacies of the serial port on different systems.
 */

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
#define __WIN
#elif defined(linux) || defined(__linux)
#define __LINUX
#else
#error "Neither a Linux nor a Windows system was found!"
#endif

#ifdef __WIN
#include <windows.h>
#endif
#ifdef __LINUX
#include <termios.h>
#include <stdlib.h>
#endif
#include <string>

class SerialPort {

public:
	SerialPort();
	virtual ~SerialPort();

	bool Open(int nPort = 2, int nBaud = 19200);
	bool Open(const char *Port = NULL, int nBaud = 19200);
	bool Open(const std::string &Port = NULL, int nBaud = 19200);
	bool Close(void);

	int ReadData(char *buffer, size_t limit);
	int SendData(const char *buffer, size_t size);
	int SendData(std::string data);
	int ReadDataWaiting(void);
	void FlushData(void);
	inline bool IsOpen(void) const
	{
		return (Opened);
	}
	const char* GetName(void) const
	{
		return (szPort);
	}
	int GetHandle(void) const;

	void SetDTR(bool activate);
	void SetRTS(bool activate);
	void WaitTXFinish(void);

public:
	char Error[200];

private:
	bool Opened;
	char szPort[256]; ///< Name of the open port. //TODO: Use std::string ASAP.

private:

#ifdef __WIN
	bool WriteCommByte( unsigned char );
	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
#endif
#ifdef __LINUX
	static const unsigned int BUFFER_LEN = 2100;
	int fd, res;
	unsigned int buffer_RD, buffer_WR;
	char m_buffer[BUFFER_LEN];
	struct termios oldtio, newtio;
#endif

#ifdef __WIN
//#include <wx/msw/winundef.h>
#endif
};

#endif // __SERIALPORT_H__
