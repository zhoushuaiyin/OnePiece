using namespace std;
/*
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
//#include <log4cplus/fileappender.h>
#include <log4cplus/helpers/appenderattachableimpl.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/pointer.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/loggingmacros.h>
#include <string>
#include "simple_ini.h"
*/
#include "onepiece_logger.h"

OPLogger* OPLogger::instance_ = NULL;

OPLogger::OPLogger()
{
	
}

OPLogger::~OPLogger()
{

}

OPLogger* OPLogger::Instance()
{
	if(instance_ == NULL)
	{
		instance_ = new OPLogger();
	}
	return instance_;

}

void OPLogger::UnInstance()
{
	if(instance_ != NULL)
	{
		delete instance_;
		instance_ = NULL;
	}
}

void OPLogger::InitLogConfig(CSimpleIni &ini)
{
	const char* pszVal = 0;
	bool bHasMulti = false;
	pszVal = ini.GetValue("LOG", "LEVEL", 0, &bHasMulti);
	assert(pszVal != NULL);
	int log_level = atoi(pszVal);

	pszVal = ini.GetValue("LOG", "PROCNAME", 0, &bHasMulti);
	assert(pszVal != NULL);
	string appender_name_ = pszVal;

	pszVal = ini.GetValue("LOG", "CUTE_TYPE", 0, &bHasMulti);
	assert(pszVal != NULL);
	int cute_type = atoi(pszVal);

    pszVal = ini.GetValue("LOG", "FILE_SIZE", 0, &bHasMulti);
	assert(pszVal != NULL);
	long file_size = atol(pszVal);

	pszVal = ini.GetValue("LOG", "DATE_CUTE_TYPE", 0, &bHasMulti);
	assert(pszVal != NULL);
	int date_cute_type = atoi(pszVal);

	pszVal = ini.GetValue("LOG", "PATH_FILE", 0, &bHasMulti);
	assert(pszVal != NULL);
	const char *log_filename = pszVal;  
															
	pszVal = ini.GetValue("LOG", "TTY_OPEN", 0, &bHasMulti);
	assert(pszVal != NULL);
	int tty_open = atoi(pszVal);

	string log_pattern_ = "[%D{%Y-%m-%d %H:%M:%S,%Q}] [%t] [%-5p] [%c{2}] %%%x%% - %m [%l]%n";
	LogLog::getLogLog()->setInternalDebugging(true);
	//按大小切割日志
	if( 1 == cute_type )
	{
		SharedAppenderPtr append_1(new RollingFileAppender(LOG4CPLUS_TEXT(log_filename),file_size, 30, true));
		append_1->setName(LOG4CPLUS_TEXT(appender_name_.c_str()));
		append_1->setLayout( std::auto_ptr<Layout>(new PatternLayout(log_pattern_.c_str())));
		Logger::getRoot().addAppender(append_1);
	}

	else if( 2 == cute_type)
    {
        //按日期的方式
		DailyRollingFileSchedule file_schedule_ = (DailyRollingFileSchedule)date_cute_type;
        SharedAppenderPtr append_2(new DailyRollingFileAppender(LOG4CPLUS_TEXT(log_filename),file_schedule_, 30, true));
        append_2->setName(LOG4CPLUS_TEXT(appender_name_.c_str()));
        append_2->setLayout( std::auto_ptr<Layout>(new PatternLayout(log_pattern_.c_str())) );
        Logger::getRoot().addAppender(append_2);
    }
	else
	{
		//TODO: 一般来说，上面两种方式已经能够满足需求了。	
	}
	if( tty_open ){
		SharedObjectPtr<Appender> append_3(new ConsoleAppender());
		append_3->setName(LOG4CPLUS_TEXT(appender_name_.c_str()));
		append_3->setLayout( std::auto_ptr<Layout>(new PatternLayout(log_pattern_.c_str())));
		Logger::getRoot().addAppender(append_3);
		
	}
	Logger root = Logger::getRoot();
	logger_ = Logger::getInstance(LOG4CPLUS_TEXT(appender_name_.c_str()));
	logger_.setLogLevel(log_level);
	NDCContextCreator _context(LOG4CPLUS_TEXT("InitConfig"));
	LOG4CPLUS_DEBUG(logger_, "InitConfig Successfully!");
}
