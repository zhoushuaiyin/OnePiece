#ifndef _OP_LOG_H_
#define _OP_LOG_H_ 

#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/helpers/appenderattachableimpl.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/pointer.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/loggingmacros.h>

#include <string>
#include "simple_ini.h"
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

class OPLogger
{
private:
	OPLogger();
	static OPLogger* instance_;
	

public:
	Logger logger_;
	static OPLogger* Instance();
	static void UnInstance();
	void init_log_config(CSimpleIni &ini);
	
	~OPLogger();

};
static const size_t LOG_BUFF_SIZE = 100*1024;

#ifndef COMMLOG_TRACE
#define COMMLOG_TRACE(msg) LOG4CPLUS_TRACE(OPLogger::Instance()->logger_, msg);
#endif

#ifndef COMMLOG_DEBUG
#define COMMLOG_DEBUG(msg) LOG4CPLUS_DEBUG(OPLogger::Instance()->logger_, msg);
#endif

#ifndef COMMLOG_INFO
#define COMMLOG_INFO(msg, ...) LOG4CPLUS_INFO(OPLogger::Instance()->logger_, msg);
#endif


#ifndef COMMLOG_WARN
#define COMMLOG_WARN(msg) LOG4CPLUS_WARN(OPLogger::Instance()->logger_, msg);
#endif

#ifndef COMMLOG_ERROR
#define COMMLOG_ERROR(msg) LOG4CPLUS_ERROR(OPLogger::Instance()->logger_,msg);
#endif

#ifndef COMMLOG_FATAL
#define COMMLOG_FATAL(msg) LOG4CPLUS_FATAL(OPLogger::Instance()->logger_,msg);
#endif


#ifndef COMMLOG2_TRACE
#define COMMLOG2_TRACE(msg, ...) do{ char log_buff[LOG_BUFF_SIZE]={0}; \
	snprintf(log_buff, sizeof(log_buff), msg, ##__VA_ARGS__);\
    COMMLOG_TRACE (log_buff)\
    }while(false)
#endif

#ifndef COMMLOG2_DEBUG
#define COMMLOG2_DEBUG(msg, ...) do{ char log_buff[LOG_BUFF_SIZE]={0}; \
    snprintf(log_buff, sizeof(log_buff), msg, ##__VA_ARGS__);\
    COMMLOG_DEBUG(log_buff)\
}while(false)
#endif

#ifndef COMMLOG2_INFO
#define COMMLOG2_INFO(msg, ...) do{ char log_buff[LOG_BUFF_SIZE]={0}; \
    snprintf(log_buff, sizeof(log_buff), msg, ##__VA_ARGS__);\
	COMMLOG_INFO(log_buff)\
}while(false)
#endif

#ifndef COMMLOG2_WARN
#define COMMLOG2_WARN(msg, ...) do{ char log_buff[LOG_BUFF_SIZE]={0}; \
    snprintf(log_buff, sizeof(log_buff), msg, ##__VA_ARGS__);\
	COMMLOG_WARN(log_buff)\
}while(false)
#endif

#ifndef COMMLOG2_ERROR
#define COMMLOG2_ERROR(msg, ...) do{ char log_buff[LOG_BUFF_SIZE]={0}; \
	snprintf(log_buff, sizeof(log_buff), msg, ##__VA_ARGS__);\
    COMMLOG_ERROR(log_buff)\
}while(false)
#endif

#ifndef COMMLOG2_FATAL
#define COMMLOG2_FATAL(msg, ...) do{ char log_buff[LOG_BUFF_SIZE]={0}; \
    snprintf(log_buff, sizeof(log_buff), msg, ##__VA_ARGS__);\
    COMMLOG_FATAL(log_buff)\
}while(false)
#endif

#endif
