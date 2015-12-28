#include "iso8583.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ������������ */
typedef struct rule
{
	int lengthMethods;																		/* ���Ƚ�������*/
	int contentMethods;																		/* ���ݴ���취*/
	int maxLength;																			/* �����򳤶�,���߱䳤����󳤶�(ѹ��֮ǰ)*/
}RULE;

/* ȫ����������*/
RULE const rules[65] = 
{
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 4 },									/* 0  ��Ϣ����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 16 },									/* 1  λͼ*/
	{ ISO8583_LENGTH_2_CHANGE, ISO8583_CONTENT_BCD_LEFT, 19 },								/* 2  ���˺�*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 6 },									/* 3  ���״�����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 12 },									/* 4  ���׽��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 5  ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 6  ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 7  ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 8  ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 9  ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 10 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 6 },									/* 11 �ܿ���ϵͳ���ٺ�*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 6 },									/* 12 �ܿ������ڵ�ʱ��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 4 },									/* 13 �ܿ������ڵ�����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 4 },									/* 14 ����Ч��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 4 },									/* 15 ��������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 16 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 17 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 18 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 19 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 20 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 21 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_LEFT, 3  },									/* 22 ��������뷽ʽ*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 4 },									/* 23 �����к�*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 24 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 2 },									/* 25 �����������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 2 },									/* 26 �����PIN��ȡ��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 27 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 28 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 29 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 30 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 31 ������*/
	{ ISO8583_LENGTH_2_CHANGE, ISO8583_CONTENT_BCD_RIGHT, 11 },								/* 32 ������ʶ��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 33 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 34 ������*/
	{ ISO8583_LENGTH_2_CHANGE, ISO8583_CONTENT_BCD_LEFT, 37 },								/* 35 2�ŵ�����*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_BCD_LEFT, 104 },								/* 36 3�ŵ�����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_NO_BCD, 12 },										/* 37 �����ο���*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_NO_BCD, 6 },										/* 38 ��Ȩ��ʶӦ����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_NO_BCD, 2 },										/* 39 Ӧ����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 40 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_NO_BCD, 8 },										/* 41 �ն˺�*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_NO_BCD, 15 },										/* 42 �̻���*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 43 ������*/
	{ ISO8583_LENGTH_2_CHANGE, ISO8583_CONTENT_NO_BCD, 25 },								/* 44 ������Ӧ����*/
	{ ISO8583_LENGTH_2_CHANGE, ISO8583_CONTENT_NO_BCD, 38 },								/* 45 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 46 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 47 ������*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_BCD_LEFT, 322 },								/* 48 ��������˽��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_NO_BCD, 3 },										/* 49 ���׻��Ҵ���*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 50 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 51 ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_ASC, 8 },						    				/* 52 ���˱�ʶ������*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 16 },									/* 53 ��ȫ������Ϣ*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_NO_BCD, 20 },								/* 54 ���*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_ASC, 255 },									/* 55 IC��������*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_ASC, 999 },									/* 56 �����Ϣ-������Ϣ��*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_ASC, 999 },									/* 57 ΢����ȯ��Ϣ��*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_NO_BCD, 100 },								/* 58 PBOC����Ǯ��*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 0 },									/* 59 ������*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_BCD_LEFT, 17 },								/* 60 �Զ�����*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_BCD_LEFT, 29 },								/* 61 ԭʼ��Ϣ��*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_ASC, 512 },									/* 62 �Զ�����*/
	{ ISO8583_LENGTH_3_CHANGE, ISO8583_CONTENT_NO_BCD, 163 },								/* 63 �Զ�����*/
	{ ISO8583_LENGTH_FIX, ISO8583_CONTENT_BCD_RIGHT, 8 }									/* 64 ���ļ�����*/
};


int ISO_FILEDS_INIT(FILEDS *init)
{
	memset(init, 0, sizeof(FILEDS));
	for (int i = 0; i < 65; i++)
	{
		init->content[i].is_exist = 0;
		init->content[i].dataLen = 0;
	}
	return 0;
}

int ISO_MSG_INIT(MESSAGE *init)
{
	memset(init, 0, sizeof(MESSAGE));
	memcpy(init->tpdu, ISO8583_TPDU, sizeof(init->tpdu));
	memcpy(init->header, ISO8583_HEADER, sizeof(init->header));
	return 0;
}

/* �齨8583��*/
int ISO8583_PackToStream(PACKSOURCE *packsource, char *output, int *outputLen)
{
	MSGSEND ms;
	ISO_MSG_INIT(&ms);
	ISO8583_pack8583(packsource, &ms);
	ISO8583_MSGSEND2bytes(&ms, output, outputLen);
	return *outputLen;
}

/* ����8583��*/
int ISO8583_StreamToPack(char *input, int inputLen, UNPACKRESULT *ur)
{
	MSGRECV mr;
	memset(&mr, 0, sizeof(MSGSEND));
	ISO8583_bytes2MSGRECV(input, inputLen, &mr);
	ISO_FILEDS_INIT(ur);
	ISO8583_unpack8583(&mr, ur);
	return 0;
}

/* �齨8583���� ���Ҫѹ�����͵Ľṹ��*/
int ISO8583_pack8583(PACKSOURCE *packsource, MSGSEND *msgsend)
{
	ISO_MSG_INIT(msgsend);																	/* ��ʼ������ṹ�� TPDU HEADER */
	int contentFlag = 0;																	/* ����ƫ����,��¼��ǰд��λ��*/
	char temp[ISO8583_FILED_DATA_LENGTH];													/* ��ʱ������������*/
	int	 filedLen = 0;																		/* ��ʱ�򳤶�*/
	/* ����λͼ �������*/
	ISO8583_CALCBITMAT(packsource, NULL);
	/* �齨������*/
	for ( int  i = 0; i < 64; ++i)
	{
		memset(temp, 0, sizeof(temp));
		if (packsource->content[i].is_exist == 0) continue;									/* ����򲻴���,�������˴δ���*/
		filedLen = ISO8583_COMBINE_FILED(&(packsource->content[i]), i, temp);				/* ��Ͻ������temp*/
		memcpy(msgsend->content + contentFlag, temp, filedLen);
		contentFlag += filedLen;															/* ���н���ʱ,contentFlagΪ�ܳ���*/
	}
	/* �����ܳ��� �������д����*/
	msgsend->length = sizeof(msgsend->tpdu) + sizeof(msgsend->header) + contentFlag;
	return 0;
}

/* ����8583���� ���������ĸ���*/
int ISO8583_unpack8583(MSGRECV const *msgrecv, UNPACKRESULT *result)
{
	ISO_FILEDS_INIT(result);
	int startPoint = 0;																		/* ��ǰ�����ʼλ��*/
	int shiftLength = 0;																	/* ƫ������*/
	char input[ISO8583_MAX_DATA_LENGTH];													/* ����յ�����������*/
	memset(input, 0, sizeof(input));
	memcpy(input, msgrecv->content, sizeof(msgrecv->content));
	/* ǰ���ֽ�Ϊ��Ϣ���� */
	shiftLength += rules[0].maxLength;
	memcpy(result->content[0].data, input + startPoint, shiftLength);						/* ������Ϣ����*/
	result->content[0].dataLen = rules[0].maxLength;
	result->content[0].is_exist = 1;
	startPoint += shiftLength;
	/* ��ʼ����λͼ��Ϣ �����ô������־*/
	char bitmap[33];																		/* ��Ȼֻ��64��,���ǿ���128�����*/
	memset(bitmap, 0, sizeof(bitmap));
	shiftLength = rules[1].maxLength;														/* ��2 ����Ϊ���Ϊ8�ֽ� 16λ ��BCD*/
	memcpy(bitmap, input+startPoint, shiftLength);
	ISO8583_CALCBITMAT(result, bitmap);
	startPoint += shiftLength;
	/* ��ʼ����������*/
	for (int i = 2; i < 65; i++)
	{
		if (result->content[i].is_exist == 0) continue;
		shiftLength = ISO8583_PRASE_FILED(&result->content[i], i, input + startPoint);
		startPoint += shiftLength;
	}
	// TODO: mac У��
	/* �������,���� */
	return 0;
}

/* ��MSGSENDѹ��Ϊ�����ֽ���*/
int ISO8583_MSGSEND2bytes(MSGSEND const *msgsend, char* outbuf, int *outbufLen)
{
	char temp[ISO8583_MAX_DATA_LENGTH];														/* ��ʱ���Դ*/	
	memset(temp, 0, sizeof(temp));
	int shift = 0;																			/* д��ƫ��*/
	//int msgLen = 0;																		/* ��msgsend->length ��ȡ*/
	char len[5];
	memset(len, 0, sizeof(len));
	sprintf(len, "%04x", msgsend->length/2);
	memcpy(temp + shift, len, 4);															/* ���Ƴ�������Ϣ*/
	shift += 4;
	memcpy(temp + shift, msgsend->tpdu, sizeof(msgsend->tpdu));								
	shift += sizeof(msgsend->tpdu);
	memcpy(temp + shift, msgsend->header, sizeof(msgsend->header));
	shift += sizeof(msgsend->header);
	memcpy(temp + shift, msgsend->content, msgsend->length - sizeof(msgsend->tpdu) - sizeof(msgsend->header));			
	/* ��ʱtemp��Ч����ĳ���Ӧ�õ��� msgLen + 4 */
	char resultTemp[ISO8583_MAX_DATA_LENGTH];												/* �����*/
	memset(resultTemp, 0, sizeof(resultTemp));	
	*outbufLen = ISO8583_BcdStr2Str(temp, msgsend->length + 4, resultTemp);
	memcpy(outbuf, resultTemp, *outbufLen);
	return *outbufLen;
}

/* �������ֽ�������ΪMSGRECV*/
int ISO8583_bytes2MSGRECV(char const *recvbuf, int recvbufLen, MSGRECV *msgrecv)
{
	char recv[ISO8583_MAX_DATA_LENGTH];
	memset(recv, 0, sizeof(recv));
	int totalLen = 0;																		/* �ܳ���*/
	totalLen = ISO8583_Str2BcdStr(recvbuf, recvbufLen, recv);
	if (totalLen <= 26) return -1;
	int shift = 0;																			/* ��Ϣƫ�� */
	char lenStr[5];																			/* ����*/
	memset(lenStr, 0, sizeof(lenStr));
	memcpy(lenStr, recv + shift, sizeof(msgrecv->length));	
	msgrecv->length = ISO8583_HEXStrToInt(lenStr) * 2;										
	shift += 4;
	memcpy(msgrecv->tpdu, recv + shift, sizeof(msgrecv->tpdu));
	shift += sizeof(msgrecv->tpdu);
	memcpy(msgrecv->header, recv + shift, sizeof(msgrecv->header));
	shift += sizeof(msgrecv->header);
	memcpy(msgrecv->content, recv + shift, totalLen - shift);
	return 0;
}


int ISO8583_COMBINE_FILED(FILED const *filed, int filedNum, char *outbuf)
{
	char temp[ISO8583_FILED_DATA_LENGTH];													/* ��ʱ�������Ϣ*/
	memset(temp, 0, sizeof(temp));
	int ret = 0;																			/* �����ܳ���,  Length + Content*/
	RULE rule = rules[filedNum];															/* �õ�������������*/
	int lengthFiledShift = 0;																/* ����Ƭ�α��� ȡֵ 0 2 4*/
	// ��ȡ���Ȳ���ƫ��
	switch (rule.lengthMethods)
	{
	case ISO8583_LENGTH_FIX:
		lengthFiledShift = 0;
		break;
	case ISO8583_LENGTH_2_CHANGE:
		lengthFiledShift = 2;
		break;
	case ISO8583_LENGTH_3_CHANGE:
		lengthFiledShift = 4;
		break;
	default:
		lengthFiledShift = 0;
		break;
	}
	// �齨���Ȳ���
	ISO8583_COMBINE_LENGTH(filed->dataLen, rule.lengthMethods, temp);
	// �齨content����
	char format[12];																		/* ��ʽ���ַ���*/
	memset(format, 0, sizeof(format));
	switch (rule.contentMethods)
	{
	case ISO8583_CONTENT_BCD_RIGHT:
		sprintf(format, "%%0%ds", rule.maxLength);
		sprintf(temp + lengthFiledShift, format, filed->data);
		ret = lengthFiledShift + rule.maxLength;
		break;
	case ISO8583_CONTENT_BCD_LEFT:
		if (filed->dataLen % 2 == 0)															/* ����Ϊż�� ֱ�Ӹ���*/
		{
			sprintf(temp + lengthFiledShift, "%s", filed->data);
			ret = lengthFiledShift + filed->dataLen;
		}
		else																				/* ����Ϊ���� ���ƺ��Ҳ� '0' */
		{
			sprintf(temp + lengthFiledShift, "%s0", filed->data);
			ret = lengthFiledShift + filed->dataLen + 1;
		}
		break;
	case ISO8583_CONTENT_NO_BCD:
		ret = lengthFiledShift + ISO8583_Str2BcdStr(filed->data, filed->dataLen, temp + lengthFiledShift);
		break;
	case ISO8583_CONTENT_ASC:
		memcpy(temp + lengthFiledShift, filed->data, filed->dataLen * 2);
		ret = lengthFiledShift + filed->dataLen*2;
		break;
	default:
		break;
	}
	memcpy(outbuf, temp, ret);
	return ret;
}
int ISO8583_PRASE_FILED(FILED *filed, int filedNum, char const *inbuf)
{
	/* ȡ������Ľ������ */
	RULE rule = rules[filedNum];
	/* ���ݳ��ȹ���ȡ�����ĳ��� */
	int contLen = 0;
	int contLenLen = 0;																		/* ���ȵĳ��� */
	char lenChar[5]; memset(lenChar, 0, sizeof(lenChar));									/* ��ʶ���ȵ��ֽ�*/
	int filedLength = 0;																	/* ���ܳ���*/
	switch (rule.lengthMethods)
	{
	case ISO8583_LENGTH_FIX:
		contLenLen = 0;									
		contLen = rule.maxLength;
		filed->dataLen = contLen;
		break;
	case ISO8583_LENGTH_2_CHANGE:
		contLenLen = 2;
		memcpy(lenChar, inbuf, contLenLen);
		contLen = atoi(lenChar);
		filed->dataLen = contLen;
		break;
	case ISO8583_LENGTH_3_CHANGE:
		contLenLen = 4;
		memcpy(lenChar, inbuf, contLenLen);
		contLen = atoi(lenChar);
		filed->dataLen = contLen;
		break;
	default:
		contLenLen = 0;
		break;
	}
	/* �������Ĺ����ȡ����*/
	filedLength += contLenLen;
	char temp[ISO8583_FILED_DATA_LENGTH]; memset(temp, 0, sizeof(temp));					/* ��ʱ��Ž�ȡ������Ϣ*/
	switch (rule.contentMethods)
	{
	case ISO8583_CONTENT_BCD_RIGHT:
			memcpy(temp, inbuf + contLenLen, filed->dataLen);
			filedLength += filed->dataLen;
			memcpy(filed->data, temp, filedLength);
	
		break;
	case ISO8583_CONTENT_BCD_LEFT:
		if (filed->dataLen % 2 == 0)															/* λ��Ϊż��*/
		{
			memcpy(temp, inbuf + contLenLen, filed->dataLen);
			filedLength += filed->dataLen;
			memcpy(filed->data, temp, filedLength);
		}
		else																				/* λ��Ϊ����*/
		{
			memcpy(temp, inbuf + contLenLen, filed->dataLen);
			filedLength += filed->dataLen + 1;
			memcpy(filed->data, temp, filedLength);
		}
		break;
	case ISO8583_CONTENT_NO_BCD:
		memcpy(temp, inbuf + contLenLen, filed->dataLen * 2);								/* ���ȳ˶� */
		filedLength += filed->dataLen * 2;	
		ISO8583_BcdStr2Str(temp, filed->dataLen * 2, filed->data);
		//memcpy(filed->data, temp, filedLength);
		break;
	case ISO8583_CONTENT_ASC:
		memcpy(temp, inbuf + contLenLen, filed->dataLen * 2);
		filedLength += filed->dataLen * 2;
		memcpy(filed->data, temp, filedLength);
		break;
	default:
		break;
	}
	return filedLength;
}

int ISO8583_COMBINE_LENGTH(int len, int lengthRule, char *outbuf)
{
	char temp[5];																			/* �������ռ4�ֽ� "0123" ����ȫ��Ϊ�ҿ�*/
	int ret = 0;																			/* ���س��ȵ�λ��(ѹ��ǰ,ֻ��0,2,4)*/
	memset(temp, 0, sizeof(temp));
	sprintf(temp, "%04d", len);																/* ��������Ϣд��temp*/
	switch (lengthRule)
	{
	case ISO8583_LENGTH_FIX:
		ret = 0;
		break;
	case ISO8583_LENGTH_2_CHANGE:
		ret = 2;
		memcpy(outbuf, temp + 2, 2);
		break;
	case ISO8583_LENGTH_3_CHANGE:
		ret = 4;
		memcpy(outbuf, temp, 4);
		break;
	case ISO8583_LENGTH_4_CHANGE:
		ret = 4;
		memcpy(outbuf, temp, 4);
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}
/* "123"->"313233" */
int ISO8583_Str2BcdStr(char const* input, int inputLen, char* output)
{
	char temp[ISO8583_FILED_DATA_LENGTH];													/* ��ʱ���ת�����*/
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i < inputLen; i++)
		sprintf(temp + 2 * i, "%02X", (unsigned char)input[i]);
	int retLen = strlen(temp);
	memcpy(output, temp, retLen);
	return retLen;
}

/* "313233" -> "123" */
int ISO8583_BcdStr2Str(char const* input, int inputLen, char* output)
{
	for (int i = 0; i < inputLen/2; i += 1)
	{
		output[i] = (ISO8583_Hex2Int(input[2 * i]) << 4) | (ISO8583_Hex2Int(input[2 * i + 1]));
	}
	return inputLen / 2;
}

/* 16�����ַ�תint   'a' => 10 */
int ISO8583_Hex2Int(char ch)
{
	if (ch >= '0' && ch <= '9') return ch - '0';
	if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
	return 0;																				/* ��������ﷵ�ؾ��군�� */
}

int ISO8583_CALCBITMAT(FILEDS *fileds, char *bitmap)
{
	int ret = 0;
	char bit_map[8];																		/* ��ʱ���bitmap*/
	memset(bit_map, 0, sizeof(bit_map));
	if (fileds->content[1].is_exist == 1)													/* �������bitmap ����д��2���Լ�bitmap*/
	{
		int flag = 0;																		/* flag ��ʶλƫ��*/
		int index = 7;																		/* �����±�*/
		for (int i = 64; i >= 2; i--)
		{
			if (flag > 7)
			{
				flag = 0;
				index--;
			}
			if (fileds->content[i].is_exist == 1)
			{
				bit_map[index] = (bit_map[index]) | (0x01 << flag);
			}
			flag++;
		}
		int retLen = ISO8583_Str2BcdStr(bit_map, sizeof(bit_map), fileds->content[1].data);
		fileds->content[1].dataLen = retLen;
		if (bitmap != NULL)
		{
			memcpy(bitmap, bit_map, sizeof(bit_map));
		}
		ret = retLen;
	}
	else																					/* �������,����bitmap���fileds*/
	{
		/* ����BCD�ַ�����ʽ��bitmap,��Ҫѹ�����ֽ�����*/
		ISO8583_BcdStr2Str(bitmap, strlen(bitmap), bit_map);
		memcpy(fileds->content[1].data, bitmap, strlen(bitmap));
		fileds->content[1].is_exist = 1;
		for (int i = 0; i < 8; i++)
		{
			for (int shift = 0; shift < 8; shift++)
			{
				if ((bit_map[i] << shift & 0x80) == 0x80)
					fileds->content[i * 8 + shift + 1].is_exist = 1;
			}
		}
		ret = 0;
	}
	return ret;
}


/* HEX�ַ���תint */
int ISO8583_HEXStrToInt(char *hex)
{
	int len;
	int num = 0;
	int bits;
	len = strlen(hex);
	for (int i = 0, temp = 0; i<len; i++, temp = 0)
	{
		temp = ISO8583_Hex2Int(*(hex + i));
		bits = (len - i - 1) * 4;
		temp = temp << bits;
		num = num | temp;
	}
	return num;
}

/*���ַ������м��ȡn���ַ�  nΪ���ȣ�mΪλ�� */
char *ISO8583_strMid(char *dst, char const *src, int n, int m)
{
	char const *p = src;
	char *q = dst;
	int len = strlen(src);
	if (n > len) n = len - m;   
	if (m < 0) m = 0;   
	if (m > len) return NULL;
	p += m;
	while (n--) *(q++) = *(p++);
	*(q++) = '\0'; 
	return dst;
}
