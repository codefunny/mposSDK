#ifndef INNERINTERFACE_H
#define INNERINTERFACE_H

#define MAX_LEN 8192
#include "iso8583.h"
// �û������JSON�ַ���ת���ɵĽṹ��
typedef struct userInputStruct
{
  // ��Ϣ����
	char msg_type[4];
  // ���˺�
  char pan[20];
  // ����Ч��
  char exp_time[5];
  // ��������뷽ʽ
  char ent_code[4];
  // ���׽��
  int txn_Amt;
  // ��Ƭ���к�
  char csn[4];
  // ����
  char trk2[38];
  // ����
  char trk3[105];
  // �ն˺�
  char tid[9];
  // �̻���
  char mid[16];
  // ���˱�ʶ��
  char pin_data[17];
  // IC ��������
  char ic_data[256];
  // ���κ�
  char batch_no[7];
  // ��ˮ��
  char systrace[7];
  // �ն��豸��Ϣ(�����)
  char sn_info[51];
  // ��ǿ��ܽ��
  char dc_total_amt[13];
  // ���ǿ��ܽ��
  char cc_total_amt[13];
  //  ���ǿ��ܱ���
  char cc_total_cnt[4];
  // ��ǿ��ܱ���
  char dc_total_cnt[4];
  // IC����������
  char ic_data_item[128];
  // �ܱ���
  int total_cnt;
}INMSG;

// �������ṹ��,���˽ṹ��ת����json�ַ������ظ�caller
typedef struct outputStruct
{
  // ��Ϣ����
  char msg_type[4];
  // ������
  char respCode[4];
  // ����
  char pan[20];
  // ���׽���ʱ��
  char mchTransETime[15];
  // ��ˮ��
  char systrace[7];
  // �����ο���
  char rrn[13];
  // ���׽��
  int txnAmt;
  // ��Ȩ��
  char auth_code[7];
  // �ն˺�
  char tid[9];
  // �̻���
  char mid[15];
  // ������
  char bcode[4];
  // ���ÿ���˾����
  char cre_code[4];
  // ���κ�
  char batch_no[7];
  // �ŵ���Կ����
  char tdk[33];
  // �ŵ���ԿУ��ֵ
  char tdk_check[9];
  // ʶ������Կ����
  char zpk[33];
  // ʶ������ԿУ��ֵ
  char zpk_check[9];
  // ������Կ����
  char zak[33];
  // ������ԿУ��ֵ
  char zak_check[9];
  // ��ǿ��ܽ��
  char dc_total_amt[13];
  // ���ǿ��ܽ��
  char cc_total_amt[13];
  //  ���ǿ��ܱ���
  char cc_total_cnt[4];
  // ��ǿ��ܱ���
  char dc_total_cnt[4];
  // ����Ӧ����
  char acc_st[2];
  // IC�������б�
  char ic_para_list[512];
  // �����Ƿ���Ҫ��������IC������
  char ic_data_que_flag[2];
  // ��Կ�����б�
  char key_para_list[512];
  // �����Ƿ���Ҫ��������Կ������
  char key_data_que_flag[2];
}OUTMSG;


// ����ӿ�-����JOSN�ַ���,������MAC�����BCD�ַ����Լ�����.
int INNER_OUT_SEND_MACSTR_BCD(char const *injson, char *out);
// ����ӿ�-�����MAC�����BCD�ַ���,�Լ�MACֵ,����Ҫ����posp��BCD�ַ����Լ�����
int INNER_OUT_GET_MAC_BCD(char const *SrcStr, char const *macStr, char *out);
// ����ӿ�,�����յ�����Ϣ,����,������������JSON�ַ���
int INNER_OUT_PARSE_BCD(char const *recv, char *jsonout);


int INNER_GET_TRANSTYPE(UNPACKRESULT const *ur);

// ���û������json��ת��Ϊ�ṹ��
int INNER_Json2Struct(char const *json, INMSG *inmsg);
// ���ṹ��ת����json��
int INNER_Struct2Json(OUTMSG *outmsg, char *json);

/* ǩ�� */
int INNER_PACK_SIGNUP(INMSG *inStruct, char *outTemp);
/* ǩ�� */
int INNER_PACK_SIGNOFF(INMSG *inStruct, char *outTemp);

/* ���� */
int INNER_PACK_SETTLE(INMSG *inStruct, char *outTemp);

/* IC��������ѯ */
int INNER_PACK_ICPARA_QUERY(INMSG *inStruct, char *outTemp);

/* ��Կ��ѯ */
int INNER_PACK_KEY_QUERY(INMSG *inStruct, char *outTemp);

/* IC���������� */
int INNER_PACK_ICPARA_DOWM(INMSG *inStruct, char *outTemp);

/* ��Կ���� */
int INNER_PACK_KEY_DOWN(INMSG *inStruct, char *outTemp);

/* IC���������ؽ��� */
int INNER_PACK_ICPARADOWN_END(INMSG *inStruct, char *outTemp);

/* ��Կ���ؽ��� */
int INNER_PACK_KEYDOWN_END(INMSG *inStruct, char *outTemp);

/* IC���ű����� */
int INNER_PACK_ICSCRIPTUP(INMSG *inStruct, char *outTemp);

/* �����ͽű�֪ͨ */
int INNER_PACK_SETTLE_NOTIFY(INMSG *inStruct, char *outTemp);


/* ֧�������� */
int INNER_PACK_ALIPAY_PAY(INMSG *inStruct, char *outTemp);
/* ֧�������ײ�ѯ */
int INNER_PACK_ALIPAY_PAY_QUERY(INMSG *inStruct, char *outTemp);
/* ֧�������� */
int INNER_PACK_ALIPAY_FLUSH(INMSG *inStruct, char *outTemp);
/* ֧�����˻� */
int INNER_PACK_ALIPAY_REFUND(INMSG *inStruct, char *outTemp);

/* ΢�Ž���*/
int INNER_PACK_WX_PAY(INMSG *inStruct, char *outTemp);
/* ΢�Ž��ײ�ѯ*/
int INNER_PACK_WX_PAY_QUERY(INMSG *inStruct, char *outTemp);
/* ΢�ų���*/
int INNER_PACK_WX_FLUSH(INMSG *inStruct, char *outTemp);
/* ΢���˻�*/
int INNER_PACK_WX_REFUND(INMSG *inStruct, char *outTemp);

/* ��������*/
int INNER_PACK_UNION_PAY(INMSG *inStruct, char *outTemp);
/* �������ѳ���*/
int INNER_PACK_UNION_FLUSH(INMSG *inStruct, char *outTemp);
/* ���������˻�*/
int INNER_PACK_UNION_REFUND(INMSG *inStruct, char *outTemp);
/* �������ѳ���*/
int INNER_PACK_UNION_REVOKE(INMSG *inStruct, char *outTemp);
/* ����������ѯ*/
int INNER_PACK_UNION_QUERY(INMSG *inStruct, char *outTemp);

/* ������Ԥ��Ȩ*/
int INNER_PACK_UNION_PRE_PAY(INMSG *inStruct, char *outTemp);
/* ������Ԥ��Ȩ����*/
int INNER_PACK_UNION_PRE_PAY_FLUSH(INMSG *inStruct, char *outTemp);
/* ������Ԥ��Ȩ����*/
int INNER_PACK_UNION_PRE_PAY_REVOKE(INMSG *inStruct, char *outTemp);
/* ������Ԥ��Ȩ���*/
int INNER_PACK_UNION_PRE_PAY_FINISH(INMSG *inStruct, char *outTemp);
/* ������Ԥ��Ȩ��ɳ���*/
int INNER_PACK_UNION_PRE_PAY_FINSHI_REVOKE(INMSG *inStruct, char *outTemp);

/* �⿨����*/
int INNER_PACK_OUTSIDE_PAY(INMSG *inStruct, char *outTemp);
/* �⿨���ѳ���*/
int INNER_PACK_OUTSIDE_FLUSH(INMSG *inStruct, char *outTemp);
/* �⿨���ѳ���*/
int INNER_PACK_OUTSIDE_REVOKE(INMSG *inStruct, char *outTemp);
/* �⿨�����˻�*/
int INNER_PACK_OUTSIDE_REFUND(INMSG *inStruct, char *outTemp);

/* �������׷��ر��� */
int INNER_PARSE_TRANS(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ����ǩ�����ر��� */
int INNER_PARSE_SIGNUP(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ����ǩ�˷��ر��� */
int INNER_PARSE_SIGNOFF(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ���������㷵�ر��� */
int INNER_PARSE_SETTLE(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ����IC��������ѯ���ر���*/
int INNER_PARSE_ICPARA_QUERY(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ������Կ��ѯ���ر��� */
int INNER_PARSE_KEY_QUERY(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ����IC���������ط��ر��� */
int INNER_PARSE_ICPARA_DOWNLOAD(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ������Կ���ط��ر��� */
int INNER_PARSE_KEY_DOWNLOAD(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ����IC���������ؽ������� */
int INNER_PARSE_PARADOWM_END(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ������Կ���ؽ������� */
int INNER_PARSE_KEYDOWN_END(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ����IC���ű����� */
int INNER_PARSE_ICSCRIPT_UP(UNPACKRESULT *ur, char* msgType, char *jsonout);
/* ���������ͽű�֪ͨ */
int INNER_PARSE_SETTLEUP_NOTIFY(UNPACKRESULT *ur, char* msgType, char *jsonout);

#endif

