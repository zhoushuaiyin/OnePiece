/**
 * FILE: weather_main.cpp
 *
 * AUTHOR:zhoushuaiyin
 *
 * CREATE_DATE:2014-04-23
 *
 * DESCRIPTION:The main function of the weather system's Query Server.
 */
//using namespace std;
#ifndef _WEATHER_MAIN_
#define _WEATHER_MAIN_
using namespace std;
#include<pthread.h>
#include <string>
#include<event.h>
#include<evhttp.h>
#include<queue>
#include "weather_application.h"

int main(int argc,char* argv[])
{
	//用于接收函数返回状态，0表示成功，-1表示失败
	int ret = 0;
	
	ret = WeatherApp::Instance()->InitWeatherApp();
	if(0 != ret)
	{
		COMMLOG2_ERROR("InitWeatherApp fail.");
		return ret;
	}

	ret = WeatherApp::Instance()->RunWeatherApp();
	if(0 != ret)
	{
		COMMLOG2_ERROR("RunWeather fail.");
		return ret;
	}

	ret = WeatherApp::Instance()->ExitWeatherApp();
	if(0 != ret)
	{
		COMMLOG2_ERROR("ExitApp fail.");
		return ret;
	}

	COMMLOG2_INFO("Program exited,bye.");
	return 0;	
}



#endif
