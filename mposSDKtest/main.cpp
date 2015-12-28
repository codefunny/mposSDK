
#include "cJSON.h"
#include <stdio.h>
#include <Windows.h>
#include "test.h"
#include <iostream>
using namespace std;

char *unionpay_cfg = "union_pay.json";
char *signup_cfg = "signup.json";
char *signoff_cfg = "signoff.json";
char *settle_cfg = "settle.json";
char *icparaquery_cfg = "icparaquery.json";
char *icparadown_cfg = "icparadown.json";
char *icparadownend_cfg = "icparadownend.json";
char *keyquery_cfg = "keyquery.json";
char *keydown_cfg = "keydown.json";
char *keydownend_cfg = "keydownend.json";
char *icscriptup_cfg = "icscriptup.json";
char *settlenotify_cfg = "settlenotify.json";

int printHeader();//ͷ
int testMPOSSdk();//����ѭ��
int main()
{
	//printf("��ʼ������������������������:\n");
	//test_Union_Pay(unionpay_cfg);
	//system("pause");

	//printf("��ʼ����ǩ������������:\n");
	//test_Signup(signup_cfg);
	//system("pause");
	
	testMPOSSdk();
	system("pause");
	return 0;
}

int printHeader()
{
	printf("\n");
	printf("=========MPOS SDK TEST=======\n");
	printf("1.ǩ��\n");
	printf("2.ǩ��\n");
	printf("3.������(����)\n");
	printf("4.IC��������ѯ\n");
	printf("5.IC����������\n");
	printf("6.IC���������ؽ���\n");
	printf("7.��Կ��ѯ\n");
	printf("8.��Կ����\n");
	printf("9.��Կ���ؽ���\n");
	printf("10.IC���ű�����\n");
	printf("11.�����ͽű�֪ͨ\n");
	printf("30.��ͨ����֧��\n");

	printf("=========MPOS SDK TEST=======\n");
	return 0;
}

int testMPOSSdk()
{
	int choice = 0;

	while (true)
	{
		printHeader();
		cin.sync();
		cin >> choice;
		printf("\n");
		printf("=====================Start=====================\n");
		switch (choice)
		{
		case 1:
			test_Signup(signup_cfg);
			break;
		case 2:
			test_Signoff(signoff_cfg);
			break;
		case 3:
			test_Settle(settle_cfg);
			break;
		case 4:
			test_IcparaQuery(icparaquery_cfg);
			break;
		case 5:
			test_IcparaDown(icparadown_cfg);
			break;
		case 6:
			test_IcparaDownEnd(icparadownend_cfg);
			break;
		case 7:
			test_KeyQuery(keyquery_cfg);
			break;
		case 8:
			test_KeyDown(keydown_cfg);
			break;
		case 9:
			test_KeyDownEnd(keydownend_cfg);
			break;
		case 10:
			test_IcScriptUp(icscriptup_cfg);
			break;
		case 11:
			test_SettleNotify(settlenotify_cfg);
			break;
		case 30:
			test_Union_Pay(unionpay_cfg);
			break;
		default:
			continue;
			break;
		}
		printf("\n======================END======================\n");

	}
}
