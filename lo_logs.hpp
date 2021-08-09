#ifndef _LO_LOGS_HPP_
#define _LO_LOGS_HPP_

#include <stdio.h>
#include <iostream>



// Macro define region
#define FILESTATUS_CLOSE			0
#define FILESTATUS_OPEN				1

#define MAXSIZE_TIMESTRING			64
#define MAXSIZE_CURTIME				64
#define MAXSIZE_PATHNAME			512
#define MAXSIZE_MSGBUF				(1024*8)
#ifdef _WIN32
#define SUBDIRNAME_LOG				"logs\\"
#else
#define SUBDIRNAME_LOG				"./logs/"
#endif
#define SERVERLOG_SKIP				" -> "
#define SERVERLOG_ENTER				"\r\n"

#define LOGTYPE_WARNING			0
#define LOGTYPE_INFO			1
#define LOGTYPE_DEBUG			2
#define LOGTYPE_FATAL			3
#define LOGTYPE_TRACE			4


class LoLogs
{
public:
	LoLogs();
	virtual ~LoLogs();

	static void WriteLog(int logType,const char *format, ...);
private:
	static FILE *m_fileSvrLog;
	static int m_nFileStatus;

	static void WriteLogInner(const char *pcLogMsg, int logType, unsigned char bKeepOpen = 0, unsigned char bNeedSeparator = 0);
	static void CloseLog();

	static int OpenLog(const char *pcLogLead);
	static void WriteData(const char *pcLogMsg);
	static const char *GetCurDateTimeWithString(char *pStringBuf);

	const static char *filename[5];

};

#endif // _LO_LOGS_HPP_
