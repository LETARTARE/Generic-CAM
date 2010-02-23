// SerialPort.h

#ifndef __SERIAL_H__
#define __SERIAL_H__

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define BUFFER_LEN	2100


#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
#define __WIN
#elif defined(linux) || defined(__linux)
#define __LINUX
#else
#error "Weder Linux noch Windows gefunden!"
#endif

#ifdef __WIN
#include <windows.h>
#endif

#ifdef __LINUX
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

#define _POSIX_SOURCE 1
#endif

class Serial {

public:
	Serial();
	virtual ~Serial();

	bool Open(int nPort = 2, int nBaud = 19200);
	bool Open(const char *Port, int nBaud = 19200);
	bool Close(void);

	int ReadData(char *, unsigned int);
	int SendData(char *, unsigned int);
	int ReadDataWaiting(void);
	void FlushData(void);
	bool IsOpen(void)
	{
		return (Opened);
	}

protected:
	bool Opened;

#ifdef __WIN
	bool WriteCommByte( unsigned char );
	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
#endif


#ifdef __LINUX
	int fd, c, res;
	unsigned int buffer_RD, buffer_WR;
	char m_buffer[BUFFER_LEN];
	struct termios oldtio, newtio;

#endif

public:
	char Error[200];

};

#endif
