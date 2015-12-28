#include <time.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
//#include "config.h"
#include "log.h"
/*
���ܣ�     ��ȡ��ǰϵͳʱ��
����ֵ��    0-�ɹ���-1-ʧ��
out:        ���淵�ص�ϵͳʱ�䣬��ʽ��fmt����
fmt:        0-���أ�yyyy-mm-dd hh24:mi:ss, 1-���أ�yyyy-mm-dd, 2-���أ�hh24:mi:ss
*/
int getTime(char *out, int fmt)                 // ��ȡ��ǰϵͳʱ��
{
	time_t t;
	struct tm *tp;

	if (out == NULL)
		return -1;
	t = time(NULL);

	tp = localtime(&t);
	if (fmt == 0)
		sprintf(out, "%2.2d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
	else if (fmt == 1)
		sprintf(out, "%2.2d-%2.2d-%2.2d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
	else if (fmt == 2)
		sprintf(out, "%2.2d:%2.2d:%2.2d", tp->tm_hour, tp->tm_min, tp->tm_sec);
	return 0;
}

/*
���ܣ�     ��strд�뵽�ļ�
����ֵ��    д�ļ��ɹ�����0,���򷵻�-1
fp:     �ļ�ָ��
str:        ��д����ַ���
bLog:       1-����־�ļ���0-������־�ļ�
˵����     �������־�ļ���������strǰ���ϵ�ǰʱ��(��ʽ�磺2011-04-12 12:10:20)
*/
int writeFile(FILE *fp, const char *str, int bLog)          // д�ַ������ļ�,bLog�����Ƿ�Ϊ��־�ļ�
{
	assert(fp != NULL && str != NULL);
	char curTime[100] = { 0 };
	int ret = -1;
	if (bLog) // ��ȡ��ǰϵͳʱ��
	{
		getTime(curTime, 0);
		ret = fprintf(fp, "[%s] %s\n", curTime, str);
	}
	else
		ret = fprintf(fp, "%s\n", str);

	if (ret >= 0)
	{
		fflush(fp);
		return 0;               // д�ļ��ɹ�
	}
	else
		return -1;
}

int LOG_WriteLog(char const *str)
{
	char fileName[256];
	memset(fileName, 0, sizeof(fileName));
	//CFG_GetProfileString("log", fileName);
	strcpy(fileName, "mposLog.log");
	//strcat(fileName, "testlog.txt");
	FILE *fp = fopen(fileName, "a+");
	if (fp == NULL)
	{
		return 0;
	}
	int ret = 0;
	ret = writeFile(fp, str, 1);
	fclose(fp);
	return ret;
}
