/*
 _
(_)  _ __     __ _   _   _   _ __     ___   __      __
| | | '_ \   / _` | | | | | | '_ \   / _ \  \ \ /\ / /
| | | |_) | | (_| | | |_| | | | | | | (_) |  \ V  V /
|_| | .__/   \__,_|  \__, | |_| |_|  \___/    \_/\_/
	|_|              |___/

����ISO8583��������ز���
author  : nxd
time	: 2015.8.5
changed : 2015.8.21  
change content : changed for mpos sdk .  removed decrypt function and mac calculate function.

*/

#ifndef ISO8583_H
#define ISO8583_H


/*
	���ó��ȶ���
*/
#define ISO8583_FILED_DATA_LENGTH		 	2048											/* ������Ϣ����*/
#define ISO8583_MAX_DATA_LENGTH				8192											/* �����Ϣ����*/

/*
	��������ʽ �궨�弯��
*/
#define ISO8583_LENGTH_FIX					0												/* ���� */
#define ISO8583_LENGTH_2_CHANGE				1												/* ��λ�䳤, �ҿ�BCD 1�ֽ�*/
#define ISO8583_LENGTH_3_CHANGE				2												/* ��λ�䳤, �ҿ�BCD 2�ֽ�*/  
#define ISO8583_LENGTH_4_CHANGE				3												/* ��λ�䳤, �ҿ�BCD 2�ֽ� ֻ���ڱ����ܳ������*/
     
#define ISO8583_CONTENT_BCD_RIGHT			0												/* ����Ϊ�ҿ�BCD��ʽ,�����仯,�������ʱ����ת��--��������Ҳʹ�����*/
#define ISO8583_CONTENT_BCD_LEFT			1												/* ����Ϊ��BCD��ʽ,�����仯,�������ʱ����ת��*/
#define ISO8583_CONTENT_NO_BCD				2												/* ����Ϊ��BCD��ʽ,  "3"->"31"  "A"->"65"  */
#define ISO8583_CONTENT_ASC					3												/* ԭ��������� ��ת�� ����56��,57����� */
/* ����д���ֶ� */
#define ISO8583_TPDU						"6000020000"								    /* д��TPDUͷ*/
#define ISO8583_HEADER						"613100310030"									/* д������ͷ*/

/* �����������(���)�ṹ */
typedef struct filed
{
	char data[ISO8583_FILED_DATA_LENGTH];													/* ������Ϣ����*/
	int	 dataLen;																			/* ��Ϣ���ݳ��� ��Ч��Ϣ,�� "3132" ����"12" */
	int  is_exist;																			/* ���Ƿ���� 0:������  1:���� */
}FILED;

typedef struct fileds
{
	FILED content[65];
}FILEDS, PACKSOURCE, UNPACKRESULT;

/* ��ʼ���������(���)�ṹ */
int ISO_FILEDS_INIT(FILEDS *init);

/* ���� ���� ���� ���� �ṹ��*/
typedef struct message
{
	int length;																				/* ������Ϣ�ܳ���*/
	char tpdu[10];																			/* tpduͷ*/
	char header[12];																		/* ����ͷ˵��*/
	char content[ISO8583_MAX_DATA_LENGTH];													/* ������*/
}MESSAGE, MSGSEND, MSGRECV;

/* ��ʼ��Message�ṹ�� */
int ISO_MSG_INIT(MESSAGE *init);

/* �齨8583��*/
int ISO8583_PackToStream(PACKSOURCE *packsource, char *output, int *outputLen);

/* ����8583��*/
int ISO8583_StreamToPack(char *input, int inputLen, UNPACKRESULT *ur);

/* �齨8583���� ���Ҫѹ�����͵Ľṹ��*/
int ISO8583_pack8583(PACKSOURCE *packsource, MSGSEND *msgsend);
/* ����8583���� ���������ĸ���*/
int ISO8583_unpack8583(MSGRECV const *msgrecv, UNPACKRESULT *result);

/* ��MSGSENDѹ��Ϊ�����ֽ���*/
int ISO8583_MSGSEND2bytes(MSGSEND const *msgsend, char* outbuf, int *outbufLen);
/* �������ֽ�������ΪMSGRECV*/
int ISO8583_bytes2MSGRECV(char const *recvbuf, int recvbufLen, MSGRECV *msgrecv);

/* ���������������ϵ���*/
int ISO8583_COMBINE_FILED(FILED const *filed, int filedNum, char *outbuf);
/* ���ݽ������������� �������ܳ���(����������Ϣ��������Ϣ)*/
int ISO8583_PRASE_FILED(FILED *filed, int filedNum, char const *inbuf);
/* ��ϳ����ַ���*/
int ISO8583_COMBINE_LENGTH(int len, int lengthRule, char *outbuf);
/* "123" -> "313233" */
int ISO8583_Str2BcdStr(char const* input, int inputLen, char* output);
/* "313233" -> "123" */
int ISO8583_BcdStr2Str(char const* input, int inputLen, char* output);
/* 16�����ַ�תint   'a' => 10 */
int ISO8583_Hex2Int(char ch);
/* ����λͼ ���ݶ�����ڱ�ʶѡ�� ������� or �������*/
int ISO8583_CALCBITMAT(FILEDS *fileds, char *bitmap);

int ISO8583_HEXStrToInt(char *hex);
#endif // !ISO8583_H
