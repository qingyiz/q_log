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

#define COLOR_NONE          "\033[0m"
#define COLOR_BLACK         "\033[0;30m"
#define COLOR_BLUE          "\033[0;34m"
#define COLOR_GREEN         "\033[0;32m"
#define COLOR_CYAN          "\033[0;36m"
#define COLOR_RED           "\033[0;31m"
#define COLOR_YELLOW        "\033[1;33m"
#define COLOR_WHITE         "\033[1;37m"

#define LOGTYPE_WARNING			0
#define LOGTYPE_INFO			1
#define LOGTYPE_DEBUG			2
#define LOGTYPE_ERROR			3
#define LOGTYPE_TRACE			4

#define Q_WAR(fmt, args...) ({printf(COLOR_YELLOW"[WAR]:%s[%d]: "COLOR_NONE, __FUNCTION__,__LINE__);printf(fmt, ##args);\
								LoLogs::WriteLog(LOGTYPE_WARNING,fmt,##args);\
								})
#define Q_INF(fmt, args...) ({printf(COLOR_BLUE"[INF]:%s[%d]: "COLOR_NONE, __FUNCTION__,__LINE__);printf(fmt, ##args);\
								LoLogs::WriteLog(LOGTYPE_INFO,fmt,##args);\
								})
#define Q_DEB(fmt, args...) ({printf(COLOR_GREEN"[DEB]:%s[%d]: "COLOR_NONE, __FUNCTION__,__LINE__);printf(fmt, ##args);\
								LoLogs::WriteLog(LOGTYPE_DEBUG,fmt,##args);\
								})
#define Q_ERR(fmt, args...) ({printf(COLOR_RED"[ERR]]:%s[%d]: "COLOR_NONE, __FUNCTION__,__LINE__);printf(fmt, ##args);\
								LoLogs::WriteLog(LOGTYPE_ERROR,fmt,##args);\
								})
#define Q_TRA(fmt, args...) ({printf(COLOR_CYAN"[TRA]:%s[%d]: "COLOR_NONE, __FUNCTION__,__LINE__);printf(fmt, ##args);\
								LoLogs::WriteLog(LOGTYPE_TRACE,fmt,##args);\
								})
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
