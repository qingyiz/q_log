#include <stdarg.h>

#ifndef WIN32
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "lo_logs.hpp"
#include "lo_utilities.hpp"
#include <time.h>

static Mutex m_gLogMutex(0);

FILE *LoLogs::m_fileSvrLog = NULL;
int LoLogs::m_nFileStatus = FILESTATUS_CLOSE;

const char * LoLogs::filename[5] = {"warning","info","debug","fatal","trace"};


LoLogs::LoLogs()
{
}

LoLogs::~LoLogs()
{
}


/*==================================================================
* Function    : GetCurDateTimeWithString
* Description : gets the current time 
* Input Para  : empty string
* Output Para : a string containing time data
* Return Value: 
==================================================================*/
const char *LoLogs::GetCurDateTimeWithString(char *pStringBuf)
{
	time_t	tCurDateTime;
	tm		*ptagCurDataTime;
	char	szTimeStringBuf[MAXSIZE_TIMESTRING] = { 0 };

	char *pWriteStringBuf = pStringBuf;
	if (NULL == pWriteStringBuf)
	{
		pWriteStringBuf = szTimeStringBuf;
	}

	time(&tCurDateTime);
	ptagCurDataTime = localtime(&tCurDateTime);

	sprintf(pWriteStringBuf, "%d-%02d-%02d %02d:%02d:%02d",
		ptagCurDataTime->tm_year + 1900,
		ptagCurDataTime->tm_mon + 1,
		ptagCurDataTime->tm_mday,
		ptagCurDataTime->tm_hour,
		ptagCurDataTime->tm_min,
		ptagCurDataTime->tm_sec);

	return pWriteStringBuf;
}

/*==================================================================
* Function    : WriteLogInner
* Description : write log data to file 
* Input Para  : pcLogMsg->data string
*				logType-> log file type
*				bKeepOpen->Whether to always open the log file
*				bNeedSeparator->Whether a row is required
* Output Para : a string containing time data
* Return Value: 
==================================================================*/
void LoLogs::WriteLogInner(const char *pcLogMsg,int logType,unsigned char bKeepOpen/* = 0*/,unsigned char bNeedSeparator/* = 0*/)
{
	if (pcLogMsg == NULL)
	{
		return;
	}

	m_gLogMutex.lock();

	int nStatus = OpenLog(filename[logType]);
	if (nStatus != -1)
	{
		char szCurTime[MAXSIZE_CURTIME] = { 0 };
		GetCurDateTimeWithString(szCurTime);
		strcat(szCurTime, SERVERLOG_SKIP);
		WriteData(szCurTime);
		WriteData(pcLogMsg);
		if (bNeedSeparator)
		{
			WriteData(SERVERLOG_ENTER);
		}
		if (!bKeepOpen)
		{
			CloseLog();
		}
	}

	m_gLogMutex.unlock();
}
/*==================================================================
* Function    : OpenLog
* Description : create and open log file  
* Input Para  : logType-> log file type
* 				format-> need wreite data to log file 
* Output Para : 
* Return Value: 
==================================================================*/

void LoLogs::WriteLog(int logType,const char *format, ...)
{
	char szMsgBuf[MAXSIZE_MSGBUF] = { 0 };
	va_list va;
	va_start(va, format);
	vsprintf(szMsgBuf, format, va);
#ifdef WIN32
	printf(szMsgBuf);
#endif
	va_end(va);
	WriteLogInner(szMsgBuf, logType);
}
/*==================================================================
* Function    : OpenLog
* Description : create and open log file  
* Input Para  : pcLogLead-> subdirectory path
* Output Para : 
* Return Value: -1 create and open error 
* 				 0 create and open  success
==================================================================*/
int LoLogs::OpenLog(const char *pcLogLead)
{
	int nRet = 0;
	
	if (m_nFileStatus == FILESTATUS_CLOSE)
	{
		char szOpenPathName[MAXSIZE_PATHNAME] = { 0 };
		//char szOpenPathName[MAXSIZE_PATHNAME] = { 0 };
		time_t	ltime;
		tm		tmStruct;
		time(&ltime);
		tmStruct = *localtime(&ltime);

		strcat(szOpenPathName, SUBDIRNAME_LOG);
		strcat(szOpenPathName, pcLogLead);
		strcat(szOpenPathName, "/");
#ifdef WIN32
		CreateDirectory(szOpenPathName, NULL);
#else /* LINUX */
		mkdir(SUBDIRNAME_LOG, 0700);	//mkdir ./logs/
		mkdir(szOpenPathName, 0700);	//mkdir ./logs/xxxx/
#endif
		sprintf(szOpenPathName + strlen(szOpenPathName), "%s%04d-%02d-%02d.log",pcLogLead ,tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday);
		m_fileSvrLog = fopen(szOpenPathName, "a+");
		if (m_fileSvrLog)
		{
			m_nFileStatus = FILESTATUS_OPEN;
		}
		else
		{
			nRet = -1;
		}
	}

	return nRet;
}
/*==================================================================
* Function    : CloseLog
* Description : close log file  
* Input Para  : 
* Output Para : 
* Return Value:
==================================================================*/
void LoLogs::CloseLog()
{
	if (m_nFileStatus == FILESTATUS_OPEN)
	{
		fclose(m_fileSvrLog);
		m_fileSvrLog = NULL;
		m_nFileStatus = FILESTATUS_CLOSE;
	}
}
/*==================================================================
* Function    : WriteData
* Description : write data log file  
* Input Para  : pcLogMsg-> need write data
* Output Para : 
* Return Value:
==================================================================*/
void LoLogs::WriteData(const char *pcLogMsg)
{
	if (pcLogMsg == NULL)
	{
		return;
	}

	if (m_nFileStatus == FILESTATUS_OPEN)
	{
		fwrite(pcLogMsg, 1, strlen(pcLogMsg), m_fileSvrLog);
	}
}
