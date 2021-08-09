#include <iostream>
#include "lo_logs.hpp"

using namespace std;

int main()
{
	int i = 0;
	LoLogs::WriteLog(LOGTYPE_WARNING,"%s,%s,%s,%d\n","author : qingyizhg","this is warning log test",__FILE__,__LINE__);
	LoLogs::WriteLog(LOGTYPE_WARNING,"editor : first log sys\n");
	LoLogs::WriteLog(LOGTYPE_WARNING,"email  : qingyizhu12138@163.com\n");

	LoLogs::WriteLog(LOGTYPE_INFO,"%s,%s,%s,%d\n","author : qingyizhg","this is info log test",__FILE__,__LINE__);
	LoLogs::WriteLog(LOGTYPE_INFO,"editor : first log sys\n");
	LoLogs::WriteLog(LOGTYPE_INFO,"email  : qingyizhu12138@163.com\n");

	LoLogs::WriteLog(LOGTYPE_DEBUG,"%s,%s,%s,%d\n","author : qingyizhg","this is debug log test",__FILE__,__LINE__);
	LoLogs::WriteLog(LOGTYPE_DEBUG,"editor : first log sys\n");
	LoLogs::WriteLog(LOGTYPE_DEBUG,"email  : qingyizhu12138@163.com\n");

	LoLogs::WriteLog(LOGTYPE_TRACE,"%s,%s,%s,%d\n","author : qingyizhg","this is trace log test",__FILE__,__LINE__);
	LoLogs::WriteLog(LOGTYPE_TRACE,"editor : first log sys\n");
	LoLogs::WriteLog(LOGTYPE_TRACE,"email  : qingyizhu12138@163.com\n");
	
	LoLogs::WriteLog(LOGTYPE_FATAL,"%s,%s,%s,%d\n","author : qingyizhg","this is fatal log test",__FILE__,__LINE__);
	LoLogs::WriteLog(LOGTYPE_FATAL,"editor : first log sys\n");
	LoLogs::WriteLog(LOGTYPE_FATAL,"email  : qingyizhu12138@163.com\n");
	while(1);
#ifdef WIN32
	system("pause");
#endif
	return 0;
}
