// SerialPort.cpp

#include "SerialPort.h"

Serial::Serial()
{
#ifdef __WIN
	memset( &m_OverlappedRead, 0, sizeof( OVERLAPPED ) );
	memset( &m_OverlappedWrite, 0, sizeof( OVERLAPPED ) );
	m_hIDComDev = NULL;
#endif


#ifdef __LINUX
	buffer_RD = 0;
	buffer_WR = 0;
#endif
	Error[0] = 0;
	Opened = false;
}

Serial::~Serial()
{
	Close();
}

bool Serial::Open(int nPort, int nBaud)
{
	if(Opened) return (true);

#ifdef __WIN

	char szPort[15];
	wsprintf( szPort, "COM%d", nPort );

#endif


#ifdef __LINUX
	char szPort[15];

	if(nPort < 1) return false;
	sprintf(szPort, "/dev/ttyS%1i", nPort - 1);
	//  sprintf (szPort, "/dev/ttyUSB0");
#endif

	return Open(szPort, nBaud);
}

bool Serial::Open(const char *Port, int nBaud)
{
	if(Port == NULL) return false;
	if(Opened) return true;

#ifdef __WIN

	char szPort[15];
	char szComParams[50];
	DCB dcb;

	wsprintf( szPort, "%s", Port );
	m_hIDComDev = CreateFile( szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );
	if( m_hIDComDev == NULL ) return( FALSE );

	memset( &m_OverlappedRead, 0, sizeof( OVERLAPPED ) );
	memset( &m_OverlappedWrite, 0, sizeof( OVERLAPPED ) );

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 5000;
	SetCommTimeouts( m_hIDComDev, &CommTimeOuts );

	wsprintf( szComParams, "%s:%d,n,8,1", Port, nBaud );

	m_OverlappedRead.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	m_OverlappedWrite.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

	dcb.DCBlength = sizeof( DCB );
	GetCommState( m_hIDComDev, &dcb );
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;
	unsigned char ucSet;
	ucSet = (unsigned char) ( ( FC_RTSCTS & FC_DTRDSR ) != 0 );
	ucSet = (unsigned char) ( ( FC_RTSCTS & FC_RTSCTS ) != 0 );
	ucSet = (unsigned char) ( ( FC_RTSCTS & FC_XONXOFF ) != 0 );
	if( !SetCommState( m_hIDComDev, &dcb ) ||
			!SetupComm( m_hIDComDev, 10000, 10000 ) ||
			m_OverlappedRead.hEvent == NULL ||
			m_OverlappedWrite.hEvent == NULL ){
		DWORD dwError = GetLastError();
		if( m_OverlappedRead.hEvent != NULL ) CloseHandle( m_OverlappedRead.hEvent );
		if( m_OverlappedWrite.hEvent != NULL ) CloseHandle( m_OverlappedWrite.hEvent );
		CloseHandle( m_hIDComDev );
		return( FALSE );
	}

#endif


#ifdef __LINUX
	char szPort[15];


	//  if (nPort < 1)  return false;
	//if(!spezial)
	sprintf(szPort, "%s", Port);
	//else
	//  sprintf (szPort, "/dev/ttyUSB0");

	fd = open(szPort, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);
	if(fd < 0) return false;

	fcntl(fd, F_SETFL, FNDELAY);

	tcgetattr(fd, &oldtio);
	bzero(&newtio, sizeof(newtio));

	newtio.c_cflag = CLOCAL | CREAD;
	newtio.c_cflag |= CS8 | HUPCL;
	//newtio.c_cflag |= CRTSCTS; // Hardware flow control
	newtio.c_iflag = IGNPAR;


	//  newtio.c_oflag &= ~OPOST;

	// Baudrate setzen

	bool flag = false;
	if(nBaud == 50){
		cfsetispeed(&newtio, B50);
		cfsetospeed(&newtio, B50);
		flag = true;
	}
	if(nBaud == 75){
		cfsetispeed(&newtio, B75);
		cfsetospeed(&newtio, B75);
		flag = true;
	}
	if(nBaud == 110){
		cfsetispeed(&newtio, B110);
		cfsetospeed(&newtio, B110);
		flag = true;
	}
	if(nBaud == 134){
		cfsetispeed(&newtio, B134);
		cfsetospeed(&newtio, B134);
		flag = true;
	}
	if(nBaud == 150){
		cfsetispeed(&newtio, B150);
		cfsetospeed(&newtio, B150);
		flag = true;
	}
	if(nBaud == 200){
		cfsetispeed(&newtio, B200);
		cfsetospeed(&newtio, B200);
		flag = true;
	}
	if(nBaud == 300){
		cfsetispeed(&newtio, B300);
		cfsetospeed(&newtio, B300);
		flag = true;
	}
	if(nBaud == 600){
		cfsetispeed(&newtio, B600);
		cfsetospeed(&newtio, B600);
		flag = true;
	}
	if(nBaud == 1200){
		cfsetispeed(&newtio, B1200);
		cfsetospeed(&newtio, B1200);
		flag = true;
	}
	if(nBaud == 1800){
		cfsetispeed(&newtio, B1800);
		cfsetospeed(&newtio, B1800);
		flag = true;
	}
	if(nBaud == 2400){
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		flag = true;
	}
	if(nBaud == 4800){
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		flag = true;
	}
	if(nBaud == 9600){
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		flag = true;
	}
	if(nBaud == 19200){
		cfsetispeed(&newtio, B19200);
		cfsetospeed(&newtio, B19200);
		flag = true;
	}
	if(nBaud == 38400){
		cfsetispeed(&newtio, B38400);
		cfsetospeed(&newtio, B38400);
		flag = true;
	}
	if(nBaud == 57600){
		cfsetispeed(&newtio, B57600);
		cfsetospeed(&newtio, B57600);
		flag = true;
	}
	if(nBaud == 115200){
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		flag = true;
	}
	if(!flag) return false;

	tcsetattr(fd, TCSAFLUSH, &newtio);


#endif

	Opened = true;
	return (Opened);
}

bool Serial::Close(void)
{
	//	printf("Port ist %s! \n",Opened?"offen":"geschlossen");

	if(!Opened) return true;

#ifdef __WIN
	if(m_hIDComDev == NULL ) return( TRUE );

	if( m_OverlappedRead.hEvent != NULL ) CloseHandle( m_OverlappedRead.hEvent );
	if( m_OverlappedWrite.hEvent != NULL ) CloseHandle( m_OverlappedWrite.hEvent );
	CloseHandle( m_hIDComDev );
	m_hIDComDev = NULL;
#endif


#ifdef __LINUX

	oldtio.c_cflag = CLOCAL | CREAD;
	oldtio.c_cflag |= B0; // sideeffect: DTR turned off

	tcsetattr(fd, TCSANOW, &oldtio);
	close(fd);
#endif

	Opened = false;
	//	printf("Port wurde geschlossen!\n");
	return (true);
}

#ifdef __WIN
bool Serial::WriteCommByte( unsigned char ucByte )
{

	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile( m_hIDComDev, (LPSTR) &ucByte, 1, &dwBytesWritten, &m_OverlappedWrite );
	if( !bWriteStat && ( GetLastError() == ERROR_IO_PENDING ) ){
		if( WaitForSingleObject( m_OverlappedWrite.hEvent, 1000 ) ) dwBytesWritten = 0;
		else{
			GetOverlappedResult( m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, FALSE );
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}
	return( true );
}
#endif

int Serial::SendData(char *buffer, unsigned int size)
{
#ifdef __WIN
	if(m_hIDComDev == NULL) return (0);

	DWORD dwBytesWritten = 0;
	unsigned int i;
	for(i = 0; i < size; i++){
		WriteCommByte(buffer[i]);
		dwBytesWritten++;
	}

	return ((int) dwBytesWritten);
#endif
#ifdef __LINUX
	if(!Opened) return 0;
	int dwBytesWritten = 0;

	dwBytesWritten = write(fd, buffer, size);
	return ((int) dwBytesWritten);
#endif
}

int Serial::ReadDataWaiting(void)
{
#ifdef __WIN
	if(m_hIDComDev == NULL ) return( 0 );

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError( m_hIDComDev, &dwErrorFlags, &ComStat );

	return( (int) ComStat.cbInQue );
#endif
#ifdef __LINUX
	if(!Opened) return 0;
	//	tcflush(fd,TCIOFLUSH);
	while((buffer_WR + 1) % BUFFER_LEN != buffer_RD){
		if(1 != read(fd, m_buffer + buffer_WR, 1)) break;
		buffer_WR++;
		buffer_WR %= BUFFER_LEN;
	}
	//	sprintf(Error,"%d  %d",buffer_WR,buffer_RD);
	return (buffer_WR - buffer_RD + BUFFER_LEN) % BUFFER_LEN;
#endif
}

int Serial::ReadData(char *buffer, unsigned int limit)
{
#ifdef __WIN

	if( m_hIDComDev == NULL ) return( 0 );

	BOOL bReadStatus;
	DWORD dwBytesRead, dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError( m_hIDComDev, &dwErrorFlags, &ComStat );
	if( !ComStat.cbInQue ) return( 0 );

	dwBytesRead = (DWORD) ComStat.cbInQue;
	if( limit < (int) dwBytesRead ) dwBytesRead = (DWORD) limit;

	bReadStatus = ReadFile( m_hIDComDev, buffer, dwBytesRead, &dwBytesRead, &m_OverlappedRead );
	if( !bReadStatus ){
		if( GetLastError() == ERROR_IO_PENDING ){
			WaitForSingleObject( m_OverlappedRead.hEvent, 2000 );
			return( (int) dwBytesRead );
		}
		return( 0 );
	}

	return( (int) dwBytesRead );
#endif
#ifdef __LINUX

	if(!Opened) return 0;

	unsigned int i = ReadDataWaiting();
	unsigned int j;
	if(i > limit) i = limit;
	for(j = 0; j < i; j++)
		buffer[j] = m_buffer[(buffer_RD + j) % BUFFER_LEN];
	buffer_RD += i;
	buffer_RD %= BUFFER_LEN;
	return i;
#endif
}

void Serial::FlushData()
{
	char Dummy[128];
	unsigned int i = ReadDataWaiting();
	unsigned int j, k;
	while(i != 0){
		j = i;
		if(j > 128) j = 128;
		k = ReadData(Dummy, j);
		i -= k;
	}
}