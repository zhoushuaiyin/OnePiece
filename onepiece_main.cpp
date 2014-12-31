#ifndef _OP_MAIN_
#define _OP_MAIN_
using namespace std;
#include<pthread.h>
#include <string>
#include<event.h>
#include<evhttp.h>
#include<queue>
#include "onepiece_application.h"

int main(int argc,char* argv[])
{
	//用于接收函数返回状态，0表示成功，-1表示失败
	int ret = 0;
	
	ret = OPApp::Instance()->InitOPApp();
	if(0 != ret)
	{
		COMMLOG2_ERROR("InitWeatherApp fail.");
		return ret;
	}

	ret = OPApp::Instance()->RunOPApp();
	if(0 != ret)
	{
		COMMLOG2_ERROR("RunWeather fail.");
		return ret;
	}

	ret = OPApp::Instance()->ExitOPApp();
	if(0 != ret)
	{
		COMMLOG2_ERROR("ExitApp fail.");
		return ret;
	}

	COMMLOG2_INFO("Program exited,bye.");
	return 0;	
}



#endif
