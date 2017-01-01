#ifndef __SGC_TIMEUTILS_H__
#define __SGC_TIMEUTILS_H__
#include <iostream>
#include <stdlib.h>

int IsToday(time_t stamp){
	char buf[32], nowBuf[32];
	time_t now = time(0);	
	struct tm *ptr = localtime(&stamp);
	strftime(buf, sizeof(buf), "%F", ptr);
	struct tm *nowPtr = localtime(&now);
	strftime(nowBuf, sizeof(nowBuf), "%F", nowPtr);
	return strcmp(buf, nowBuf) == 0;
}

uint32_t GetTimeSpan(const timeval& start)
{
    timeval end;
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}

#endif
