/*---------------------------------------------------------------------------
* Copyright (c) 2019 �Ϻ�껲�Ӱ��Ƽ����޹�˾
* All rights reserved.
*
* �ļ�����: HbiFpd.h
* �ļ���ʶ:
* ժ    Ҫ: ƽ��̽������������ͷ�ļ�
*
* ��ǰ�汾: 3.0
* ��    ��: mhyang
* �������: 2020/11/20
* �޸�����: 2021/11/05
----------------------------------------------------------------------------*/
#pragma once
#ifndef __HBI_FPD_H_
#define __HBI_FPD_H_
#include "HbiType.h"
#include "HbiError.h"

#define _DLL_EX_IM
#ifdef _DLL_EX_IM
#define HBI_FPD_DLL __declspec(dllexport)
#else
#define HBI_FPD_DLL __declspec(dllimport)
#endif

#ifdef _cplusplus
extern ��C��{
#endif

////////////////////////////////////////////////////////////////////////////////////////
// ��˫�塱�򡰶�塱��������ӿ� ADD BY MHYANG 20211009
////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* ��    ��: No0001
* �� �� ��: HBI_InitDual
* ��������: ��ʼ����̬��
* ����˵��: ����Ϊ�زΣ�������ƽ��ľ��
			In/Out:void **handle1 - ƽ��A��ʵ���޷��Ŷ���ָ��
			In/Out:void **handle1 - ƽ��B��ʵ���޷��Ŷ���ָ��
* �� �� ֵ��
			0   - �ɹ�
			��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitDual(void **handle1, void **handle2);

/*********************************************************
* ��    ��: No0002
* �� �� ��: HBI_InitEx
* ��������: ��ʼ��˫����嶯̬��ʵ��������Ϊ�زΣ���ƽ��ľ����ID
* ����˵��: ����Ϊ�زΣ���ƽ��ľ����ID
			In/Out:HBI_HANDLE *pHandArr - ������󣬼���HbiType.h��
			In:int nArrSize - ����ĸ�������= DETECTOR_MAX_NUMBER
* �� �� ֵ��
			0   - �ɹ�
			��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitEx(HBI_HANDLE *pHandArr, int nArrSize);

/*********************************************************
* ��    ��: No0003
* �� �� ��: HBI_DestroyEx
* ��������: ��������DLL��Դ
* ����˵��: ��
* �� �� ֵ��
			��
* ��    ע:
*********************************************************/
HBI_FPD_DLL void __stdcall HBI_DestroyEx();

/*********************************************************
* ��    ��: No0004
* �� �� ��: HBI_GetDetectorHandle
* ��������: ����ƽ��id��ȡ��ȡ���
* ����˵��:
			In��int fpdid - ƽ��id��0 �� ƽ��id �� DETECTOR_MAX_NUMBER
* �� �� ֵ��
			void * - �޷��Ŷ���ָ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL void *__stdcall HBI_GetDetectorHandle(int fpdid = 0);

/*********************************************************
* ��    ��: No0005
* �� �� ��: HBI_GetDetectorId
* ��������: ���ݾ����ȡ��ȡƽ��id
* ����˵��:
			In��void *handle - ƽ����
* �� �� ֵ��
			int - ƽ��id
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetDetectorId(void *handle);

/*********************************************************
* ��    ��: No0006
* �� �� ��: HBI_ActivateDetector
* ��������: ����ƽ�壬ĿǰSDK֧��˫��ͬʱ��ͼ������Ҫ�л�
* ����˵��:
			In��void *handle - ƽ����
* �� �� ֵ��
			0   - �ɹ����ص����������̼�����
			��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ActivateDetector(void *handle);
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/*********************************************************
* ��    ��: No001
* �� �� ��: HBI_Init
* ��������: ��ʼ����̬��
* ����˵��:
* �� �� ֵ��void * - �޷��Ŷ���ָ��
			ʧ�ܣ�NULL
			�ɹ����ǿ�
* ��    ע:
*********************************************************/
HBI_FPD_DLL void* __stdcall HBI_Init(int fpdid=0);

/*********************************************************
* ��    ��: No002
* �� �� ��: HBI_Destroy
* ��������: �ͷŶ�̬����Դ
* ����˵��:
		In: void *handle - ���
		Out: ��
* �� �� ֵ��void
* ��    ע:
*********************************************************/
HBI_FPD_DLL void __stdcall HBI_Destroy(void *handle);

/*********************************************************
* ��    ��: No003
* �� �� ��: HBI_ConnectDetector
* ��������: ��������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			COMM_CFG commCfg - �������ò�������ϸ����HbiType.h��
			int doOffsetTemp - ��1:���ӳɹ���̼���������offsetģ��
							   1:���ӳɹ���̼�������offsetģ��
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetector(void *handle, COMM_CFG commCfg, int doOffsetTemp = 0);
// ��������ƽ��ӿ� 
/*********************************************************
* ��    ��: No003
* �� �� ��: HBI_ConnectDetectorUdp    - ���߱�׼UDP
            HBI_ConnectDetectorJumbo  - ���߱�׼UDP JUMBO
			HBI_ConnectDetectorWlan   - ���߱�׼UDP wireless
* ��������: �������ӣ�֧����̫��UDPЭ�飩
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			char *szDetectorIp - ƽ��IP��ַ,��192.168.10.40
			unsigned short usDetectorPort - ƽ��˿�,��32897(0x8081)
			char *szlocalIp - ��λ����ַ,��192.168.10.20
			unsigned short usLocalPort -��λ���˿�,��32896(0x8080)
			int doOffsetTemp - ��1:���ӳɹ���̼���������offsetģ��
							   1:���ӳɹ���̼�������pre-offsetģ�壬����offsetʹ��03������Ч
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorUdp(void *handle, char *szDetectorIp, unsigned short usDetectorPort, char *szlocalIp, unsigned short usLocalPort, int doOffsetTemp = 0);
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorJumbo(void *handle, char *szDetectorIp, unsigned short usDetectorPort, char *szlocalIp, unsigned short usLocalPort, int doOffsetTemp = 0);
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorWlan(void *handle, char *szDetectorIp, unsigned short usDetectorPort, char *szlocalIp, unsigned short usLocalPort, int doOffsetTemp = 0);
/*********************************************************
* ��    ��: No003
* �� �� ��: HBI_ConnectDetectorPcie
* ��������: �������ӣ�֧�ֹ��ͨѶЭ�飩
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int doOffsetTemp - ��1:���ӳɹ���̼���������offsetģ��
							   1:���ӳɹ���̼�������pre-offsetģ�壬����offsetʹ��03������Ч
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorPcie(void *handle, int doOffsetTemp = 0);
/******************************************************************************
* ��    ��: No003
* �� �� ��: HBI_ConnectDetectorEx
* ��������: ��������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			����ͨѶ���Ʋ���������hbi_init.ini��
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:hbi_fpd_init.ini���Ŀ¼��HbiType.dll��ͬĿ¼��
* ˵    ��:
* ƽ���ַ:FPD_IP=192.168.10.40
* ƽ��˿�:FPD_PORT=32897
* ���ص�ַ:LOCAL_IP=192.168.10.20
* ���ض˿�:LOCAL_PORT=32896
* ����ģʽ:TRIGGER_MODE=1           #0-Invalid Trigger;1-Software Trigger;2-Clear;3-Static:Hvg Trigger Mode;
									#4-Static:AED Trigger Mode;5-Dynamic:Hvg Sync Mode;
									#6-Dynamic:Fpd Sync Mode;7-Dynamic:Continue Mode;8-Static:SAECMode;
* ƫ�ý���ʹ��:OFFSET_ENABEL=3      #0-No Offset Correction;1-Software PreOffset Correction;2-Firmware PostOffset Correction;3-Firmware PreOffset Correction;
* �������ʹ��:GAIN_ENABLE  =2      #0-No Gain Correction;1-Software Gain Correction;2-Firmware Gain Correction;
* �������ʹ��:DEFECT_ENABLE=2      #0-No Defect Correction;1-Software Defect Correction;2-Firmware Defect Correction;
* Dummy����ʹ��:DUMMY_ENABLE=2      #0-No Dummy Correction;1-Software Dummy Correction;2-Firmware Dummy Correction;
* �����ɼ�ʱ��:LIVE_ACQ_TIME=1000   #1000-1000ms
* �����ʱ��:SELF_DUMPING_TIME=500  #500-500ms
* Prepare��ʱ:PREPARE_TIME=1500     #1500-1500ms
* �Ƿ����̼�Offsetģ��:DO_OFFSET=1  #1-���̼�Offsetģ�壬0-�����̼�Offsetģ��
******************************************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorEx(void *handle);
/*********************************************************
* ��    ��: No004
* �� �� ��: HBI_DisConnectDetector
* ��������: �Ͽ�����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		SOFTWARE_CALIBRATE_ENABLE inEnable - У��ʹ��״̬,��HbiType.h��FPD_SOFTWARE_CALIBRATE_ENABLE
		Out: ��
* �� �� ֵ��int
			0   - �ɹ�
			��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DisConnectDetector(void *handle);

/*********************************************************
* ��    ��: D005
* �� �� ����HBI_RegEventCallBackFun
* ��������: ע��ص�����
* ����˵����
		In: void *handle - ���(�޷���ָ��)
			USER_CALLBACK_HANDLE_ENVENT callbackfun - ע��ص�����
			void *pContext- ����ָ�룬һ����λ�����������ָ�봫��SDK���ص�������������λ�����Ա㾲̬��ȫ�ֺ������������������Ϊ��ָ�롣
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RegEventCallBackFun(void *handle, USER_CALLBACK_HANDLE_ENVENT handleEventfun, void *pContext);

/*********************************************************
* ��    ��: No006
* �� �� ��: HBI_ResetDetector
* ��������: ����̽����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ResetDetector(void *handle);

/*********************************************************
* ��    ��: No007
* �� �� ��: HBI_ResetFirmware
* ��������: ���ù̼���������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ResetFirmware(void *handle);

/*********************************************************
* ��    ��: No008
* �� �� ��: HBI_GetFPDSerialNumber
* ��������: ��ȡ��Ʒ���к�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		In/Out: char *szSn,����14λ
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetFPDSerialNumber(void *handle, char *szSn);

/*********************************************************
* ��    ��: No009
* �� �� ��: HBI_GetSDKVerion
* ��������: ��ȡSDK�汾��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out: char *szVer
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSDKVerion(void *handle, char *szVer);

/*********************************************************
* ��    ��: No010
* �� �� ��: HBI_GetFirmareVerion
* ��������: ��ȡ�̼��汾��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out: char *szVer
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetFirmareVerion(void *handle, char *szFirmwareVer);

/*********************************************************
* ��    ��: No011
* �� �� ��: HBI_GetError
* ��������: ��ȡ������Ϣ
* ����˵��:
	In:  CodeStringTable* inTable - ������Ϣ��Ϣ�б�
		 int count  - ��Ϣ�б����
		 int recode - ������
	Out:��
* �� �� ֵ��const char *
	��NULL - �ɹ���������Ϣ
	NULL   - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL const char * __stdcall HBI_GetError(const CodeStringTable* inTable, int count, int recode);

/*********************************************************
* ��    ��: No012
* �� �� ��: HBI_GetFpdCfgInfo
* ��������: ��ȡROM����
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out:RegCfgInfo* pRegCfg,��ϸ����HbiType.h����
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetFpdCfgInfo(void *handle, RegCfgInfo* pRegCfg);

/*********************************************************
* ��    ��: No013
* �� �� ��: HBI_GetImageProperty
* ��������: ��ȡͼ������
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out: IMAGE_PROPERTY *img_pro,��HbiType.h��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetImageProperty(void *handle, IMAGE_PROPERTY *img_pro);

/*********************************************************
* ��    ��: No014
* �� �� ��: HBI_SinglePrepare
* ��������: ��֡�ɼ�׼��ָ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
0   �ɹ�
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SinglePrepare(void *handle);

/*********************************************************
* ��    ��: No015
* �� �� ��: HBI_SingleAcquisition
* ��������: ��֡�ɼ�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			FPD_AQC_MODE _mode - �ɼ�ģʽ�Լ�����
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SingleAcquisition(void *handle, FPD_AQC_MODE _mode);

/*********************************************************
* ��    ��: No016
* �� �� ��: HBI_LiveAcquisition
* ��������: �����ɼ�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			FPD_AQC_MODE _mode - �ɼ�ģʽ�Լ�����
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_LiveAcquisition(void *handle, FPD_AQC_MODE _mode);

/*********************************************************
* ��    ��: No017
* �� �� ��: HBI_StopAcquisition
* ��������: ֹͣ�����ɼ�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��     ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_StopAcquisition(void *handle);

/*********************************************************
* ��    ��: No018
* �� �� ��: HBI_SetSinglePrepareTime
* ��������: ����������֡�ɼ���պͲɼ�֮���ʱ����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int *in_itime - ʱ�� [0~10000] ��λ:mm
				0-��ʾ������֡�ɼ���HBI_Prepare��HBI_SingleAcquisition��ɵ�֡�ɼ�
				��0-��ʾ������֡�ɼ���ֻ��HBI_Prepare���ɰ���Ԥ��ʱ����ɵ�֡�ɼ�
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSinglePrepareTime(void *handle, int in_itime);

/*********************************************************
* ��    ��: No019
* �� �� ��: HBI_GetSinglePrepareTime
* ��������: ��ȡ������֡�ɼ���պͲɼ�֮���ʱ����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_itime - ʱ�� [0~10000] ��λ:mm
				0-��ʾ������֡�ɼ���HBI_Prepare��HBI_SingleAcquisition��ɵ�֡�ɼ�
				��0-��ʾ������֡�ɼ���ֻ��HBI_Prepare���ɰ���Ԥ��ʱ����ɵ�֡�ɼ�
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSinglePrepareTime(void *handle, int *out_itime);

/*********************************************************
* ��    ��: No020
* �� �� ��: HBI_SetLiveAcquisitionTime(��̬ƽ��)
* ��������: ���òɼ�ʱ����(��������֡��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int time - ���ʱ��,��λ�Ǻ���ms
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetLiveAcquisitionTime(void *handle, int time);

/*********************************************************
* ��    ��: No021
* �� �� ��: HBI_GetLiveAcquisitionTime(��̬ƽ��)
* ��������: ��ȡ�ɼ�ʱ����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_time - ʱ��,��λ�Ǻ���ms
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetLiveAcquisitionTime(void *handle, int *out_time);

/*********************************************************
* ��    ��: No026
* �� �� ��: HBI_SetSelfDumpingTime
* ��������: ���òɼ�ʱ����(��̬ƽ��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int time - ���ʱ��,��λ�Ǻ���ms��>= 1000ms
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSelfDumpingTime(void *handle, int time);

/*********************************************************
* ��    ��: No027
* �� �� ��: HBI_GetSelfDumpingTime(��̬ƽ��)
* ��������: ��ȡ�ɼ�ʱ����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_time - ʱ��,��λ�Ǻ���ms
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSelfDumpingTime(void *handle, int *out_time);

/*********************************************************
* ��    ��: No022
* �� �� ��: HBI_TriggerAndCorrectApplay
* ��������: ���ô���ģʽ��ͼ��У��ʹ�ܣ�����վ���°汾
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int _triggerMode,1-������3-��ѹ������4-FreeAED��
			IMAGE_CORRECT_ENABLE* pCorrect,��HbiType.h��
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:�滻HBI_WorkStationInitDllCfg��HBI_QuckInitDllCfg�ӿ�
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_TriggerAndCorrectApplay(void *handle, int _triggerMode, IMAGE_CORRECT_ENABLE* pCorrect);

/*********************************************************
* ��    ��: No023
* �� �� ��: HBI_UpdateTriggerMode
* ��������: ���ô���ģʽ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int _triggerMode,1-������3-��ѹ������4-FreeAED��
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_UpdateTriggerMode(void *handle, int _triggerMode);

/*********************************************************
* ��    ��: No024
* �� �� ��: HBI_UpdateCorrectEnable
* ��������: ����ͼ��̼�У��ʹ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			IMAGE_CORRECT_ENABLE* pCorrect,��HbiType.h��
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_UpdateCorrectEnable(void *handle, IMAGE_CORRECT_ENABLE* pCorrect);

/*********************************************************
* ��    ��: No025
* �� �� ��: HBI_GetCorrectEnable
* ��������: ��ȡͼ��̼�У��ʹ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			IMAGE_CORRECT_ENABLE* pCorrect,��HbiType.h��
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetCorrectEnable(void *handle, IMAGE_CORRECT_ENABLE *pCorrect);

/*********************************************************
* ��    ��: No026
* �� �� ��: HBI_SetSoftwareCorrect
* ��������: ����У��ʹ�ܣ�������SDKУ�������������������ڹ̼�У����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			SOFTWARE_CALIBRATE_ENABLE inEnable - У��ʹ��״̬,��HbDllType.h��SOFTWARE_CALIBRATE_ENABLE struct
		Out: ��
* �� �� ֵ��int
		0   �ɹ�
		��0 ʧ�ܣ���HbDllError.h������
* ��    ע:�½ӿ�
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSoftwareCorrect(void *handle, SOFTWARE_CALIBRATE_ENABLE inEnable);

/*********************************************************
* ��    ��: No027
* �� �� ��: HBI_GetSoftwareCorrect
* ��������: ��ȡУ��ʹ�ܲ�����������SDKУ�������������������ڹ̼�У����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			SOFTWARE_CALIBRATE_ENABLE inEnable - У��ʹ��״̬,��HbDllType.h��
			SOFTWARE_CALIBRATE_ENABLE struct
		Out: ��
* �� �� ֵ��int
		0   �ɹ�
		��0 ʧ�ܣ���HbDllError.h������
* ��    ע:�½ӿ�
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSoftwareCorrect(void *handle, SOFTWARE_CALIBRATE_ENABLE *inEnable);

/*********************************************************
* ��    ��: No028
* �� �� ��: HBI_SetAcqSpanTm
* ��������: ����AED����ʱ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int time - ���ʱ��,��λ�Ǻ���ms��>= 500ms
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetAedIntegrateTm(void *handle, int time);

/*********************************************************
* ��    ��: No029
* �� �� ��: HBI_GetAedIntegrateTm
* ��������: ��ȡAED����ʱ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_time - ʱ��,��λ�Ǻ���ms
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetAedIntegrateTm(void *handle, int *out_time);

/*********************************************************
* ��    ��: No030
* �� �� ��: HBI_SetAedThreshold
* ��������: ����AED��ֵ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		int out_ivalue - ��ֵ [25,000~1,000,000]
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetAedThreshold(void *handle, int in_ivalue);

/*********************************************************
* ��    ��: No031
* �� �� ��: HBI_GetAedThreshold
* ��������: ��ȡAED��ֵ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_ivalue - ��ֵ [10,000~1,000,000]
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetAedThreshold(void *handle, int *out_ivalue);

/*********************************************************
* ��    ��: No032
* �� �� ��: HBI_SetSaturationValue
* ��������: ���ñ���ֵ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_ivalue - ����ֵ [0~65,535]
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSaturationValue(void *handle, int in_ivalue);

/*********************************************************
* ��    ��: No033
* �� �� ��: HBI_GetSaturationValue
* ��������: ��ȡ����ֵ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int *out_ivalue - ����ֵ [0~65,535]
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSaturationValue(void *handle, int *out_ivalue);

/*********************************************************
* ��    ��: No034
* �� �� ��: HBI_SetClippingValue
* ��������: ����ͼ�����ֵ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_ivalue - ����ֵ [0~65,535]
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetClippingValue(void *handle, int in_ivalue);

/*********************************************************
* ��    ��: No035
* �� �� ��: HBI_GetClippingValue
* ��������: ��ȡͼ�����ֵ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *out_ivalue - ����ֵ [0~65,535]
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetClippingValue(void *handle, int *out_ivalue);

/*********************************************************
* ��    ��: No036
* �� �� ��: HBI_SetPGALevel
* ��������: �������浲λ,�����ÿɱ�̻��ֵ��ݵ�λ,���������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int mode - ģʽ
			[n]-Invalid
			[1]-0.6pC
			[2]-1.2pC
			[3]-2.4pC
			[4]-3.6pC
			[5]-4.8pC
			[6]-7.2pC,Ĭ��7.2pC
			[7]-9.6pC
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetPGALevel(void *handle, int nGainLevel);

/*********************************************************
* ��    ��: No037
* �� �� ��: HBI_GetGainMode
* ��������: ��ȡ���浲λ,����ȡ�ɱ�̻��ֵ��ݵ�λ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		[n]-Invalid
		[1]-0.6pC
		[2]-1.2pC
		[3]-2.4pC
		[4]-3.6pC
		[5]-4.8pC
		[6]-7.2pC
		[7]-9.6pC
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetPGALevel(void *handle);

/*********************************************************
* ��    ��: No038
* �� �� ��: HBI_SetLPFLevel
* ��������: ����AEC�ɼ�ģʽ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int nLPFLevel - ��λ
			[n]-Invalid
			[0]-210khz,Ĭ��210khz
			[1]-105khz
			[2]-52khz
			[3]-26khz
			[4]-13khz
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetLPFLevel(void *handle, int nLPFLevel);

/*********************************************************
* ��    ��: No039
* �� �� ��: HBI_GetLPFLevel
* ��������: ��ȡ��ͨ�˲�����λ����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		[0]-210khz,Ĭ��210khz
		[1]-105khz
		[2]-52khz
		[3]-26khz
		[4]-13khz
		[n]-Invalid
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetLPFLevel(void *handle);

/*********************************************************
* ��    ��: No040
* �� �� ��: HBI_SetBinning
* ��������: ����ͼ��binning��ʽ
* ����˵��:
		In:
			void *handle - ���(�޷���ָ��)
			unsigned int nbin - 1:1x1,2:2x2,3:3x3(�ݲ�֧��),4:4x4
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetBinning(void *handle, unsigned int bin);

/*********************************************************
* ��    ��: No041
* �� �� ��: HBI_GetBinning
* ��������: ��ȡͼ��binning��ʽ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
unsigned int *nbin - 1:1x1,2:2x2,3:3x3(�ݲ�֧��),4:4x4
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetBinning(void *handle, unsigned int *bin);

/*********************************************************
* ��    ��: No042
* �� �� ��: HBI_SetPreviewMode
* ��������: ����PreviewԤ����ȡ��Ԥ��
* ��������: ����PreviewԤ����ȡ��Ԥ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int inTriggMode
				1-����
				3-��ѹ����
				4-FreeAED
				8-SAEC
				������֧�֡�
			int inPreviewMode
				0-normal image
				1-preview image
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetPreviewMode(void *handle, int inTriggMode, int inPreviewMode);

/*********************************************************
* ��    ��: No043
* �� �� ��: HBI_GetPreviewMode
* ��������: ����Preview
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:int *outMode - preview mode [0~2]
			0-normal image,1-preview image,2-preview image and normal image��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetPreviewMode(void *handle, int *outMode);

/*********************************************************
* ��    ��: No044
* �� �� ��: HBI_SAecModeApply
* ��������: ���û�ȡ��SAECģʽ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int inPreviewMode
				0-normal image
				1-preview image
			int inPerTime  - fpd pre ready delay time
			int inPostTime - fpd post ready delay time
		Out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:��Ϊ���������
			1�����ã�inPreviewMode=1(preview image)��inPerTime��inPostTime(�ͻ�ָ��)
			2��ȡ����inPreviewMode=0(normal image)��inPerTime��inPostTimeĬ�ϼ���
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SAecModeApply(void *handle, int inPreviewMode, int inPerTime = 0, int inPostTime = 0);

/*********************************************************
* ��    ��: No045
* �� �� ��: HBI_SAecAcq
* ��������: SAEC�ɼ���ͼָ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SAecAcq(void *handle);

/*********************************************************
* ��    ��: No046
* �� �� ��: HBI_RegProgressCallBack
* ��������: ע��ص�����
* ����˵��: ����̼�����������Ϣ
		In: void *handle - ���(�޷���ָ��)
			USER_CALLBACK_HANDLE_PROCESS handleStatusfun - ע��ص�����
			void* pObject - ����ָ�룬���Ϊ��
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RegProgressCallBack(void *handle, USER_CALLBACK_HANDLE_PROCESS handleStatusfun, void* pObject);

/*********************************************************
* ��    ��: No047
* �� �� ��: HBI_GenerateTemplate
* ��������: ��������ģ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
				EnumIMAGE_ACQ_CMD _mode - ����ģ������
				OFFSET_TEMPLATE_TYPE      �����ɼ�һ�鰵��ͼ - Firmware PreOffset Template
				GAIN_TEMPLATE_TYPE        �����ɼ�һ������ͼ - gain Template
				DEFECT_TEMPLATE_GROUP1,   �����ɼ�һ������ͼ - defect group1
				DEFECT_TEMPLATE_GROUP2,   �����ɼ�һ������ͼ - defect group2
				DEFECT_ACQ_AND_TEMPLATE,  �����ɼ�һ������ͼ - defect group3 and generate template
				SOFTWARE_OFFSET_TEMPLATE  �����ɼ�һ�鰵��ͼ - Software PreOffset Template
			int bprevew - �Ƿ�����previewģ�壬1-���ɣ�0-������
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateTemplate(void *handle, EnumIMAGE_ACQ_CMD _mode, int bprevew = 0);

/*********************************************************
* ��    ��: No048
* �� �� ��: HBI_DownloadTemplate
* ��������: ���ؽ���ģ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			DOWNLOAD_FILE *downloadfile - ����ģ���ļ�����ָ��
              emUPLOAD_FILE_TYPE emfiletype-ģ������(OFFSET_TMP-offsetģ��.GAIN_TMP-gainģ��,DEFECT_TMP-defectģ��)
	          int nBinningtype-ģ��binning���ͣ�1-binning1*1,2-binning2*2,3-binning3*3,4-binning4*4��
	          char filepath-ģ�����·��
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadTemplate(void *handle, DOWNLOAD_FILE *downloadfile);

/*********************************************************
* ��    ��: No049
* �� �� ��: HBI_DownloadTemplateEx
* ��������: ���ؽ���ģ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			DOWNLOAD_MODE *downloadmode - ����ģ���ļ�����ָ��
				DOWNLOAD_FILE *downloadfile - ����ģ���ļ�����ָ��
						emUPLOAD_FILE_TYPE emfiletype-ģ������(OFFSET_TMP-offsetģ��.GAIN_TMP-gainģ��,DEFECT_TMP-defectģ��)
						int nBinningtype-ģ��binning���ͣ�1-binning1*1,2-binning2*2,3-binning3*3,4-binning4*4��
						char filepath-ģ�����·��
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadTemplateEx(void *handle, DOWNLOAD_MODE *downloadmode);

/*********************************************************
* ��    ��: No070
* �� �� ��: HBI_DownloadTemplateByType
* ��������: ��������Ĭ�����ع̶�����ģ���ļ�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int infiletype - �����ļ�����0-gainģ�壬1-defectģ�壬2-offsetģ�壬����-��֧��
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadTemplateByType(void *handle, int infiletype);

/*********************************************************
* ��    ��: No050
* �� �� ��: HBI_StopDownloadTemplate
* ��������: ֹͣ���ؽ���ģ��
* ����˵��:
		In:  void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_StopDownloadTemplate(void *handle);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���¹̼�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* ��    ��: No051
* �� �� ��: HBI_UpgradeFirmware
* ��������: �����̼���Ϣ������Ƕ��ʽ���
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			char *binfile - bin�ļ�·��
			int filetype - 0:FPGA�����1:Embedded���
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_UpgradeFirmware(void *handle, char *binfile, int filetype=0);

/*********************************************************
* ��    ��: No052
* �� �� ��: HBI_StopUpdateFirmware
* ��������: ֹͣ���¹̼�HBI_StopDownloadTemplate
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		out:��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_StopUpdateFirmware(void *handle);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* ��    ��: No053
* �� �� ��: HBI_Dumping
* ��������: ���ָ��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_Dumping(void *handle);

/*********************************************************
* ��    ��: No054
* �� �� ��: HBI_GetSysParamCfg
* ��������: �ض�ϵͳRAM/ROM����,�첽�¼����ڲ����ڻص������з���
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	int cmd  - rom or ram
	int type - user or admin
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSysParamCfg(void *handle, int cmd, int type);

/*********************************************************
* ��    ��: No055
* �� �� ��: HBI_SetSysParamCfg
* ��������: ����ϵͳRAM/ROM����
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	int cmd -
	int type -
	RegCfgInfo* pRegCfg -
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSysParamCfg(void *handle, int cmd, int type, RegCfgInfo* pRegCfg);

/*********************************************************
* ��    ��: No056
* �� �� ��: HBI_SetGigabitEther
* ��������: ����������Ϣ����
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		EtherInfo* pEther,��HbiType.h��
	Out:��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetGigabitEther(void *handle, EtherInfo* pEther);

/*********************************************************
* ��    ��: No057
* �� �� ��: HBI_RetransMissPacket
* ��������: ���������ش�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RetransMissPacket(void *handle);

/*********************************************************
* ��    ��: No058
* �� �� ��: HBI_RetransMissFrame
* ��������: ��֡�ش�
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RetransMissFrame(void *handle);

/*********************************************************
* ��    ��: No059
* �� �� ��: HBI_IsConnect
* ��������: �ж�ƽ����Ϊ����״̬
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
* �� �� ֵ��int
		1 - ����
		0 - �Ͽ�
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_IsConnect(void *handle);

/*********************************************************
* ��    ��: No060
* �� �� ��: HBI_GetCurFPDStatus
* ��������: ��ȡƽ�嵱ǰ״̬
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		0 - idle status����ʾ����ִ�иò���
		1 - busy status����ʾ״̬��æ�У��ܾ�ִ�иò���
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetCurFPDStatus(void *handle);

/*********************************************************
* ��    ��: No061
* �� �� ��: HBI_SetCapacity
* ��������: ���û���������(��С)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			unsigned int nframesize - �ɴ洢��֡��,
			��������С����֡��С����֡����
		Out: ��
* �� �� ֵ��int
		0   �ɹ�
		��0 ʧ�ܣ���HbDllError.h������
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetCapacity(void *handle, unsigned int nframesize);

/*********************************************************
* ��    ��: No062
* �� �� ��: HBI_SetRawStyle
* ��������: �����Ƿ񱣴�ͼ���Լ�ͼ���ļ���ʽ
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			bool bsave - ���������ʾ,false:��ʾ�����棬true:���治��ʾ
			bool bsingleraw - �����ڵ����ļ������ļ�,false:1֡���ݱ���1���ļ���true:��֡���ݿɱ�����һ���ļ���
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetRawStyle(void *handle, bool bsave, bool bsingleraw = false);

/*********************************************************
* ��    ��: No063
* �� �� ��: HBI_SetAqcProperty
* ��������: ���òɼ�����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			FPD_AQC_MODE _mode - �ɼ�ģʽ�Լ�����
		Out: ��
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetAqcProperty(void *handle, FPD_AQC_MODE _mode);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����PCIE�ӿ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* ��    ��: No064
* �� �� ��: HBI_SetDebugMode
* ��������: �л�����ģʽ������ģʽ-���ڵ���PCIE�ӿ�
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		int mode - 0:����ģʽ��1-PCIE����ģʽ
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetDebugMode(void *handle, int mode);

/*********************************************************
* ��    ��: No065
* �� �� ��: HBI_PcieSendBuff
* ��������: ��PCIE��ַ�������ݣ�������PCIE����ģʽ����Ч
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		ePCIE_WR_TYPE etype - bar��ַ��ddr��ַ����
		long addr - ar��ַ��ddr��ַ
		unsigned char *szSndBuff - д�뻺����
		int nlen - ���������ݳ���
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PcieSendBuff(void *handle, ePCIE_WR_TYPE etype, long addr, unsigned char *szSndBuff, int nlen);

/*********************************************************
* ��    ��: No066
* �� �� ��: HBI_InitOffsetMode
* ��������: ��ʼ������ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		ePCIE_WR_TYPE etype - bar��ַ��ddr��ַ����
		long addr - ar��ַ��ddr��ַ
		unsigned char *szRcvbuff - ���ջ�����
		int nlen - ���������ݳ���
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PcieRecvBuff(void *handle, ePCIE_WR_TYPE _type, long addr, unsigned char *szRcvbuff, int nlen);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ֲ�����ģ�壬����ģ����ԣ�������ο���������ģ��ӿ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* ��    ��: No067
* �� �� ��: HBI_InitOffsetMode
* ��������: ��ʼ������ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		CALIBRATE_INPUT_PARAM calibrate_param,��HbiType.h��
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitOffsetMode(void *handle, CALIBRATE_INPUT_PARAM calibrate_param);

/*********************************************************
* ��    ��: No068
* �� �� ��: HBI_InsertOffsetMode
* ��������: ��offset����ģ���в�������
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		int group_id - ��ID
		char *filepath - �ļ�·��
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InsertOffsetMode(void *handle, int group_id, char *filepath);

/*********************************************************
* ��    ��: No069
* �� �� ��: HBI_ClearOffsetMode
* ��������: ���offset����ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ClearOffsetMode(void *handle);

/*********************************************************
* ��    ��: No070
* �� �� ��: HBI_GenerateOffsetTemp
* ��������: ����offsetģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		int raw_num - ����ͼ����
		int bprevew - �Ƿ�����previewģ�壬1-���ɣ�0-������
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateOffsetTemp(void *handle, int raw_num, int bprevew = 0);

/*********************************************************
* ��    ��: No071
* �� �� ��: HBI_InitGainMode
* ��������: ��ʼ��gain����ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		CALIBRATE_INPUT_PARAM calibrate_param - ��������
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitGainMode(void *handle, CALIBRATE_INPUT_PARAM calibrate_param);

/*********************************************************
* ��    ��: No072
* �� �� ��: HBI_InsertGainMode
* ��������: ��gain����ģ���в�������
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	int group_id - ��ID
	char *filepath - �ļ�·��
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InsertGainMode(void *handle, int group_id, char *filepath);

/*********************************************************
* ��    ��: No073
* �� �� ��: HBI_ClearGainMode
* ��������: ���gain����ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ClearGainMode(void *handle);

/*********************************************************
* ��    ��: No074
* �� �� ��: HBI_GenerateGainTemp
* ��������: ����gainģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		int group_sum - ����
		int per_group_num - ÿ�����ͼƬ����
		int bprevew       - �Ƿ�����previewģ�壬1-���ɣ�0-������
		Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateGainTemp(void *handle, int group_sum, int per_group_num, int bprevew = 0);

/*********************************************************
* ��    ��: No075
* �� �� ��: HBI_InitDefectMode
* ��������: ��ʼ��defect����ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		CALIBRATE_INPUT_PARAM calibrate_param - ��������
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitDefectMode(void *handle, CALIBRATE_INPUT_PARAM calibrate_param);

/*********************************************************
* ��    ��: No076
* �� �� ��: HBI_InsertDefectMode
* ��������: ��defect����ģ���в�������
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
		int group_id - ��ID
		char *filepath - �ļ�·��
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InsertDefectMode(void *handle, int group_id, char *filepath);

/*********************************************************
* ��    ��: No077
* �� �� ��: HBI_ClearDefectMode
* ��������: ���defect����ģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ClearDefectMode(void *handle);

/*********************************************************
* ��    ��: No078
* �� �� ��: HBI_GenerateDefectTemp
* ��������: ����defectģ��
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	int group_sum - ����
	int per_group_num - ÿ�����ͼƬ����
	int bprevew       - �Ƿ�����previewģ�壬1-���ɣ�0-������
	Out: ��
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateDefectTemp(void *handle, int group_sum, int per_group_num, int bprevew = 0);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�����Ŀ¼��ַ������δʵ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////*********************************************************
////* ��    ��: No079
////* �� �� ��: HBI_SetFileDirectory
////* ��������: �����ļ��洢·��
////* ����˵��:
////		In: void *handle - ���(�޷���ָ��)
////			HBI_FILE_TYPE filetype - �ļ����ͣ�ö����
////				0    IMAGE_FILE
////				1    TEMPLATE_FILE
////				char *dirpath - �ļ�·��
////		Out: ��
////* �� �� ֵ��int
////		0 - �ɹ�
////		1 - ʧ��
////* ��    ע:
////*********************************************************/
////HBI_FPD_DLL int __stdcall HBI_SetFileDirectory(void *handle, HBI_FILE_TYPE filetype, char *dirpath);

/*********************************************************
* ��    ��: No080
* �� �� ��: HBI_GetFileDirectory
* ��������: ��ȡ�ļ��洢·��
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			HBI_FILE_TYPE filetype - �ļ����ͣ�ö����
				0    IMAGE_FILE
				1    TEMPLATE_FILE
		Out: ��
* �� �� ֵ��int
		NULL  - ʧ��
		char* - ����·��
* ��    ע:
*********************************************************/
HBI_FPD_DLL char* __stdcall HBI_GetFileDirectory(void *handle, HBI_FILE_TYPE filetype);

/*********************************************************
* ��    ��: No081
* �� �� ��: HBI_GetTempFileFullDirectory
* ��������: ��ȡ��ǰģ���ļ�ȫĿ¼
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
		Out: ��
* �� �� ֵ��int
		NULL  - ʧ��
		char* - ����·��
* ��    ע:
*********************************************************/
HBI_FPD_DLL char* __stdcall HBI_GetTempFileFullDirectory(void *handle);

/*********************************************************
* ��    ��: No082
* �� �� ��: HBI_IsBusyNow
* ��������: �жϵ�ǰSDK�Ƿ��������У�������ǰ����
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			eventtype eventtype - ����ģ������
				1    �ֲ�����ģ�崦����
				2    ��������ģ�崦����
				3,   �ɼ�������
				4,   ���ò���������
		Out: ��
* �� �� ֵ��int
		0 - idle status����ʾ����ִ�иò���
		1 - busy status����ʾ״̬��æ�У��ܾ�ִ�иò���
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_IsBusyNow(void *handle, int eventtype);

/*********************************************************
* ��    ��: No083
* �� �� ��: HBI_SetImageROI
* ��������: set region of interest
* ����˵��:
		In: void *handle  - ���(�޷���ָ��)
		In: ImageROI *roi - The param of 'region of interest'
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetImageROI(void *handle, ImageROI *roi);

/*********************************************************
* ��    ��: No084
* �� �� ��: HBI_GetImageROI
* ��������: get region of interest
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
* �� �� ֵ��ImageROI*
		NULL   - ʧ��
		��NULL - �ɹ�,The param of 'region of interest'
* ��    ע:
*********************************************************/
HBI_FPD_DLL ImageROI* __stdcall HBI_GetImageROI(void *handle);

/*********************************************************
* ��    ��: No085
* �� �� ��: HBI_InitUserMode
* ��������: ��ʼ��user mode list��ע�������ļ�hbi_mode_config.ini��hbi_mode_config.json
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			FPD_USER_MODE mode - �û�Mode
		Out: ��
* �� �� ֵ��int
		0 - �ɹ�
		1 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitUserMode(void *handle);
/*********************************************************
* ��    ��: No086
* �� �� ��: HBI_AddUserMode
* ��������: ����û�Mode��user mode list
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			FPD_USER_MODE mode - �û�Mode
		Out: ��
* �� �� ֵ��int
		0 - �ɹ�
		1 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_AddUserMode(void *handle, FPD_USER_MODE mode);
// ɾ��һ��mode��user mode list
HBI_FPD_DLL int __stdcall HBI_DelUserMode(void *handle, FPD_USER_MODE mode);
// ���浱ǰuser mode list
HBI_FPD_DLL int __stdcall HBI_SaveUserMode(void *handle);
// ��ȡUser Mode�Ĵ�С
HBI_FPD_DLL unsigned int __stdcall HBI_GetUserModeSize(void *handle);
// ͨ��mode id��ȡUser Mode Id
HBI_FPD_DLL FPD_USER_MODE* __stdcall HBI_GetUserModeById(void *handle, unsigned int modeid);
// Ӧ�� User Mode ͨ�� Mode
HBI_FPD_DLL int  __stdcall HBI_EnableUserMode(void *handle, FPD_USER_MODE mode);
// ���User Mode�б�
HBI_FPD_DLL int  __stdcall HBI_ClearUpUserMode(void *handle);
// ��ȡ��ǰUser Mode��У���ļ�·��
HBI_FPD_DLL char* __stdcall HBI_GetCurrentCorrectFilePath(void *handle);
// �ж�mode���Ƿ����
HBI_FPD_DLL bool __stdcall HBI_IsExistMode(void *handle, FPD_USER_MODE mode);
//
HBI_FPD_DLL int __stdcall HBI_DetectorAuthor(void *handle, char *pcode);
//
/*********************************************************
* ��    ��: No099
* �� �� ��: HBI_DownloadImage
* ��������: ����ͼ��(����ƽ��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int beginnumber - ���ؿ�ʼͼ�����
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadImage(void *handle, int beginnumber = 1);

/*********************************************************
* ��    ��: No100
* �� �� ��: HBI_SetSleepState
* ��������: ����ƽ��Ϊ����״̬(����ƽ��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSleepState(void *handle);

/*********************************************************
* ��    ��: No101
* �� �� ��: HBI_WakeUpFpd
* ��������: ������״̬����ƽ��(����ƽ��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_WakeUpFpd(void *handle);

/*********************************************************
* ��    ��: No102
* �� �� ��: HBI_EnableEmmcStorage
* ��������: Emmc�洢ͼ��ʹ��(����ƽ��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int nenable - 1:��ͼ,����:����ͼ
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_EnableEmmcStorage(void *handle, int nenable = 0);

/*********************************************************
* ��    ��: No103
* �� �� ��: HBI_ReflashBatteryStatusInfo
* ��������: ˢ�µ����Ϣ(����ƽ��)
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע: �첽������ͨ���ص���������00
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ReflashBatteryStatusInfo(void *handle);

/*********************************************************
* ��    ��: No104
* �� �� ��: HBI_GetBatteryStatusInfo
* ��������: ��ȡ�����Ϣ(����ƽ��)
* ����˵��:
	In: void *handle - ���(�޷���ָ��)
	    BATTERY_STATUS_INFO *pBatteryStatus - ���״̬��Ϣ ��<HbiType.h>

    Out:BATTERY_STATUS_INFO *pBatteryStatus
* �� �� ֵ��int
	0   - �ɹ�
	��0 - ʧ��
* ��    ע:ͬ������������ͬ����ͨ����η�������λ��
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetBatteryStatusInfo(void *handle, BATTERY_STATUS_INFO *pBatteryStatus);
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* ��    ��: No105
* �� �� ��: HBI_TriggerBinningAcqTime
* ��������: ���ô���ģʽ��binning��ʽ�Լ�֡�ʣ��ɼ�ͼ��ʱ������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int triggerMode - ����ģʽ
				��̬ƽ�壨ÿ��1֡����1-������2-Clear,3-��ѹ������4-FreeAED
				��̬ƽ�壨ÿ��2֡���ϣ���05-Dynamic:Hvg Sync Mode,06-Dynamic:Fpd Sync Mode,7-Continue Mode
			unsigned char binning - 1:1x1,2:2x2,3:3x3,4:4x4��������֧��
			int time - ���ʱ��,��λ�Ǻ���ms,����0
			int nfeedback - 1�����óɹ����Զ������̼���������1���������óɹ��źţ����������źż��ص�������
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_TriggerBinningAcqTime(void *handle, int triggerMode, unsigned char binning, int acqtime, int nfeedback = 0);

/*********************************************************
* ��    ��: No106
* �� �� ��: HBI_PgaBinningAcqTime
* ��������: ����PGA��λ��binning��ʽ�Լ�֡�ʣ��ɼ�ͼ��ʱ������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int nPgaLevel - PGA ��λ��[n]-Invalid,[1]-0.6pC,[2]-1.2pC,[3]-2.4pC,[4]-3.6pC,[5]-4.8pC,[6]-7.2pC,Ĭ��7.2pC,[7]-9.6pC
			unsigned char binning - 1:1x1,2:2x2,3:3x3,4:4x4��������֧��
			int acqtime - ���ʱ��,��λ�Ǻ���ms,����0
			int nfeedback - 1�����óɹ����Զ������̼���������1���������óɹ��źţ����������źż��ص�������
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PgaBinningAcqTime(void *handle, int nPgaLevel, unsigned char binning, int acqtime, int nfeedback = 0);

/*********************************************************
* ��    ��: No107
* �� �� ��: HBI_TriggerPgaBinningAcqTime
* ��������: ���ô���ģʽ��PGA��λ��binning��ʽ�Լ�֡�ʣ��ɼ�ͼ��ʱ������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int triggerMode - ����ģʽ
				��̬ƽ�壨ÿ��1֡����1-������2-Clear,3-��ѹ������4-FreeAED
				��̬ƽ�壨ÿ��2֡���ϣ���05-Dynamic:Hvg Sync Mode,06-Dynamic:Fpd Sync Mode,7-Continue Mode
			int nPgaLevel - PGA ��λ��[n]-Invalid,[1]-0.6pC,[2]-1.2pC,[3]-2.4pC,[4]-3.6pC,[5]-4.8pC,[6]-7.2pC,Ĭ��7.2pC,[7]-9.6pC
			unsigned char binning - 1:1x1,2:2x2,3:3x3,4:4x4��������֧��
			int acqtime - ���ʱ��,��λ�Ǻ���ms,����0
			int nfeedback - 1�����óɹ����Զ������̼���������1���������óɹ��źţ����������źż��ص�������
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_TriggerPgaBinningAcqTime(void *handle, int triggerMode, int nPgaLevel, unsigned char binning, int acqtime, int nfeedback = 0);

/*********************************************************
* ��    ��: No108
* �� �� ��: HBI_PgaAcqTime
* ��������: ����PGA��λ����֡�ʣ��ɼ�ͼ��ʱ������
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int nPgaLevel - PGA ��λ��[n]-Invalid,[1]-0.6pC,[2]-1.2pC,[3]-2.4pC,[4]-3.6pC,[5]-4.8pC,[6]-7.2pC,Ĭ��7.2pC,[7]-9.6pC
			int acqtime - ���ʱ��,��λ�Ǻ���ms,����0
			int nfeedback - 1�����óɹ����Զ������̼���������1���������óɹ��źţ����������źż��ص�������
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PgaAcqTime(void *handle, int nPgaLevel, int acqtime, int nfeedback = 0);

/*********************************************************
* ��    ��: No109
* �� �� ��: HBI_SwitchNetTypeWlanMode
* ��������: �л�����2.4G/5G�����WLAN AP/Client Mode(����ƽ��)
* ����˵��:
		In: void *handle - ���(�޷���ָ��)
			int nNetType - �����������ͣ�1-2.4G,2-5G,����-��Ч
			int nWlanMode - WLANģʽ��1-AP Mode,2-Client Mode,����-��Ч
* �� �� ֵ��int
		0   - �ɹ�
		��0 - ʧ��
* ��    ע:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SwitchNetTypeWlanMode(void *handle, int nNetType, int nWlanMode);
/***************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////
// ������ ��ʱδ���������ṩ
////////////////////////////////////////////////////////////////////////////////////////
class HBI_FPD_DLL CHbiFpdDllClass
{
public:
	CHbiFpdDllClass();
	virtual ~CHbiFpdDllClass();

public:
	bool Init();
};
CHbiFpdDllClass *m_phbiimage = new CHbiFpdDllClass;
if (m_phbiimage != NULL)
{
	delete m_phbiimage;
	m_phbiimage = NULL;
}
if (m_phbiimage != NULL)
{
	m_phbiimage->Init();
}
***************************************************************************************/
#ifdef _cplusplus
}
#endif
#endif // __HBI_FPD_H_
