/*---------------------------------------------------------------------------
* Copyright (c) 2019 上海昊博影像科技有限公司
* All rights reserved.
*
* 文件名称: HbiFpd.h
* 文件标识:
* 摘    要: 平板探测器导出函数头文件
*
* 当前版本: 3.0
* 作    者: mhyang
* 完成日期: 2020/11/20
* 修改日期: 2021/11/05
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
extern “C”{
#endif

////////////////////////////////////////////////////////////////////////////////////////
// “双板”或“多板”解决方案接口 ADD BY MHYANG 20211009
////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* 编    号: No0001
* 函 数 名: HBI_InitDual
* 功能描述: 初始化动态库
* 参数说明: 参数为回参，即两个平板的句柄
			In/Out:void **handle1 - 平板A的实例无符号对象指针
			In/Out:void **handle1 - 平板B的实例无符号对象指针
* 返 回 值：
			0   - 成功
			非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitDual(void **handle1, void **handle2);

/*********************************************************
* 编    号: No0002
* 函 数 名: HBI_InitEx
* 功能描述: 初始化双板或多板动态库实例，参数为回参，即平板的句柄和ID
* 参数说明: 参数为回参，即平板的句柄和ID
			In/Out:HBI_HANDLE *pHandArr - 数组对象，见《HbiType.h》
			In:int nArrSize - 数组的个数，《= DETECTOR_MAX_NUMBER
* 返 回 值：
			0   - 成功
			非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitEx(HBI_HANDLE *pHandArr, int nArrSize);

/*********************************************************
* 编    号: No0003
* 函 数 名: HBI_DestroyEx
* 功能描述: 销毁所有DLL资源
* 参数说明: 无
* 返 回 值：
			无
* 备    注:
*********************************************************/
HBI_FPD_DLL void __stdcall HBI_DestroyEx();

/*********************************************************
* 编    号: No0004
* 函 数 名: HBI_GetDetectorHandle
* 功能描述: 依据平板id获取获取句柄
* 参数说明:
			In：int fpdid - 平板id，0 《 平板id 《 DETECTOR_MAX_NUMBER
* 返 回 值：
			void * - 无符号对象指针
* 备    注:
*********************************************************/
HBI_FPD_DLL void *__stdcall HBI_GetDetectorHandle(int fpdid = 0);

/*********************************************************
* 编    号: No0005
* 函 数 名: HBI_GetDetectorId
* 功能描述: 依据句柄获取获取平板id
* 参数说明:
			In：void *handle - 平板句柄
* 返 回 值：
			int - 平板id
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetDetectorId(void *handle);

/*********************************************************
* 编    号: No0006
* 函 数 名: HBI_ActivateDetector
* 功能描述: 激活平板，目前SDK支持双板同时上图，不需要切换
* 参数说明:
			In：void *handle - 平板句柄
* 返 回 值：
			0   - 成功，回调函数反馈固件参数
			非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ActivateDetector(void *handle);
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/*********************************************************
* 编    号: No001
* 函 数 名: HBI_Init
* 功能描述: 初始化动态库
* 参数说明:
* 返 回 值：void * - 无符号对象指针
			失败：NULL
			成功：非空
* 备    注:
*********************************************************/
HBI_FPD_DLL void* __stdcall HBI_Init(int fpdid=0);

/*********************************************************
* 编    号: No002
* 函 数 名: HBI_Destroy
* 功能描述: 释放动态库资源
* 参数说明:
		In: void *handle - 句柄
		Out: 无
* 返 回 值：void
* 备    注:
*********************************************************/
HBI_FPD_DLL void __stdcall HBI_Destroy(void *handle);

/*********************************************************
* 编    号: No003
* 函 数 名: HBI_ConnectDetector
* 功能描述: 建立连接
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			COMM_CFG commCfg - 连接配置参数，详细见《HbiType.h》
			int doOffsetTemp - 非1:连接成功后固件不重新做offset模板
							   1:连接成功后固件重新做offset模板
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetector(void *handle, COMM_CFG commCfg, int doOffsetTemp = 0);
// 新增连接平板接口 
/*********************************************************
* 编    号: No003
* 函 数 名: HBI_ConnectDetectorUdp    - 有线标准UDP
            HBI_ConnectDetectorJumbo  - 有线标准UDP JUMBO
			HBI_ConnectDetectorWlan   - 有线标准UDP wireless
* 功能描述: 建立连接（支持以太网UDP协议）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			char *szDetectorIp - 平板IP地址,如192.168.10.40
			unsigned short usDetectorPort - 平板端口,如32897(0x8081)
			char *szlocalIp - 上位机地址,如192.168.10.20
			unsigned short usLocalPort -上位机端口,如32896(0x8080)
			int doOffsetTemp - 非1:连接成功后固件不重新做offset模板
							   1:连接成功后固件重新做pre-offset模板，矫正offset使能03即可生效
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorUdp(void *handle, char *szDetectorIp, unsigned short usDetectorPort, char *szlocalIp, unsigned short usLocalPort, int doOffsetTemp = 0);
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorJumbo(void *handle, char *szDetectorIp, unsigned short usDetectorPort, char *szlocalIp, unsigned short usLocalPort, int doOffsetTemp = 0);
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorWlan(void *handle, char *szDetectorIp, unsigned short usDetectorPort, char *szlocalIp, unsigned short usLocalPort, int doOffsetTemp = 0);
/*********************************************************
* 编    号: No003
* 函 数 名: HBI_ConnectDetectorPcie
* 功能描述: 建立连接（支持光口通讯协议）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int doOffsetTemp - 非1:连接成功后固件不重新做offset模板
							   1:连接成功后固件重新做pre-offset模板，矫正offset使能03即可生效
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorPcie(void *handle, int doOffsetTemp = 0);
/******************************************************************************
* 编    号: No003
* 函 数 名: HBI_ConnectDetectorEx
* 功能描述: 建立连接
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			基本通讯控制参数，见《hbi_init.ini》
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:hbi_fpd_init.ini存放目录与HbiType.dll是同目录。
* 说    明:
* 平板地址:FPD_IP=192.168.10.40
* 平板端口:FPD_PORT=32897
* 本地地址:LOCAL_IP=192.168.10.20
* 本地端口:LOCAL_PORT=32896
* 触发模式:TRIGGER_MODE=1           #0-Invalid Trigger;1-Software Trigger;2-Clear;3-Static:Hvg Trigger Mode;
									#4-Static:AED Trigger Mode;5-Dynamic:Hvg Sync Mode;
									#6-Dynamic:Fpd Sync Mode;7-Dynamic:Continue Mode;8-Static:SAECMode;
* 偏置矫正使能:OFFSET_ENABEL=3      #0-No Offset Correction;1-Software PreOffset Correction;2-Firmware PostOffset Correction;3-Firmware PreOffset Correction;
* 增益矫正使能:GAIN_ENABLE  =2      #0-No Gain Correction;1-Software Gain Correction;2-Firmware Gain Correction;
* 坏点矫正使能:DEFECT_ENABLE=2      #0-No Defect Correction;1-Software Defect Correction;2-Firmware Defect Correction;
* Dummy矫正使能:DUMMY_ENABLE=2      #0-No Dummy Correction;1-Software Dummy Correction;2-Firmware Dummy Correction;
* 连续采集时间:LIVE_ACQ_TIME=1000   #1000-1000ms
* 自清空时间:SELF_DUMPING_TIME=500  #500-500ms
* Prepare延时:PREPARE_TIME=1500     #1500-1500ms
* 是否做固件Offset模板:DO_OFFSET=1  #1-做固件Offset模板，0-不做固件Offset模板
******************************************************************************/
HBI_FPD_DLL int __stdcall HBI_ConnectDetectorEx(void *handle);
/*********************************************************
* 编    号: No004
* 函 数 名: HBI_DisConnectDetector
* 功能描述: 断开连接
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		SOFTWARE_CALIBRATE_ENABLE inEnable - 校正使能状态,见HbiType.h中FPD_SOFTWARE_CALIBRATE_ENABLE
		Out: 无
* 返 回 值：int
			0   - 成功
			非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DisConnectDetector(void *handle);

/*********************************************************
* 编    号: D005
* 函 数 名：HBI_RegEventCallBackFun
* 功能描述: 注册回调函数
* 参数说明：
		In: void *handle - 句柄(无符号指针)
			USER_CALLBACK_HANDLE_ENVENT callbackfun - 注册回调函数
			void *pContext- 对象指针，一般上位机软件将对象指针传入SDK，回调函数反馈给上位机，以便静态或全局函数访问其他对象，亦可为空指针。
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RegEventCallBackFun(void *handle, USER_CALLBACK_HANDLE_ENVENT handleEventfun, void *pContext);

/*********************************************************
* 编    号: No006
* 函 数 名: HBI_ResetDetector
* 功能描述: 重置探测器
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ResetDetector(void *handle);

/*********************************************************
* 编    号: No007
* 函 数 名: HBI_ResetFirmware
* 功能描述: 重置固件出厂设置
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ResetFirmware(void *handle);

/*********************************************************
* 编    号: No008
* 函 数 名: HBI_GetFPDSerialNumber
* 功能描述: 获取产品序列号
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		In/Out: char *szSn,长度14位
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetFPDSerialNumber(void *handle, char *szSn);

/*********************************************************
* 编    号: No009
* 函 数 名: HBI_GetSDKVerion
* 功能描述: 获取SDK版本号
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out: char *szVer
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSDKVerion(void *handle, char *szVer);

/*********************************************************
* 编    号: No010
* 函 数 名: HBI_GetFirmareVerion
* 功能描述: 获取固件版本号
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out: char *szVer
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetFirmareVerion(void *handle, char *szFirmwareVer);

/*********************************************************
* 编    号: No011
* 函 数 名: HBI_GetError
* 功能描述: 获取错误信息
* 参数说明:
	In:  CodeStringTable* inTable - 错误信息信息列表
		 int count  - 信息列表个数
		 int recode - 错误码
	Out:无
* 返 回 值：const char *
	非NULL - 成功，错误信息
	NULL   - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL const char * __stdcall HBI_GetError(const CodeStringTable* inTable, int count, int recode);

/*********************************************************
* 编    号: No012
* 函 数 名: HBI_GetFpdCfgInfo
* 功能描述: 获取ROM参数
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out:RegCfgInfo* pRegCfg,详细见《HbiType.h》。
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetFpdCfgInfo(void *handle, RegCfgInfo* pRegCfg);

/*********************************************************
* 编    号: No013
* 函 数 名: HBI_GetImageProperty
* 功能描述: 获取图像属性
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out: IMAGE_PROPERTY *img_pro,见HbiType.h。
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetImageProperty(void *handle, IMAGE_PROPERTY *img_pro);

/*********************************************************
* 编    号: No014
* 函 数 名: HBI_SinglePrepare
* 功能描述: 单帧采集准备指令
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
0   成功
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SinglePrepare(void *handle);

/*********************************************************
* 编    号: No015
* 函 数 名: HBI_SingleAcquisition
* 功能描述: 单帧采集
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			FPD_AQC_MODE _mode - 采集模式以及参数
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SingleAcquisition(void *handle, FPD_AQC_MODE _mode);

/*********************************************************
* 编    号: No016
* 函 数 名: HBI_LiveAcquisition
* 功能描述: 连续采集
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			FPD_AQC_MODE _mode - 采集模式以及参数
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_LiveAcquisition(void *handle, FPD_AQC_MODE _mode);

/*********************************************************
* 编    号: No017
* 函 数 名: HBI_StopAcquisition
* 功能描述: 停止连续采集
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备     注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_StopAcquisition(void *handle);

/*********************************************************
* 编    号: No018
* 函 数 名: HBI_SetSinglePrepareTime
* 功能描述: 设置软触发单帧采集清空和采集之间的时间间隔
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int *in_itime - 时间 [0~10000] 单位:mm
				0-表示软触发单帧采集先HBI_Prepare后HBI_SingleAcquisition完成单帧采集
				非0-表示软触发单帧采集，只需HBI_Prepare即可按照预定时间完成单帧采集
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSinglePrepareTime(void *handle, int in_itime);

/*********************************************************
* 编    号: No019
* 函 数 名: HBI_GetSinglePrepareTime
* 功能描述: 获取软触发单帧采集清空和采集之间的时间间隔
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_itime - 时间 [0~10000] 单位:mm
				0-表示软触发单帧采集先HBI_Prepare后HBI_SingleAcquisition完成单帧采集
				非0-表示软触发单帧采集，只需HBI_Prepare即可按照预定时间完成单帧采集
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSinglePrepareTime(void *handle, int *out_itime);

/*********************************************************
* 编    号: No020
* 函 数 名: HBI_SetLiveAcquisitionTime(静态平板)
* 功能描述: 设置采集时间间隔(即可设置帧率)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int time - 间隔时间,单位是毫秒ms
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetLiveAcquisitionTime(void *handle, int time);

/*********************************************************
* 编    号: No021
* 函 数 名: HBI_GetLiveAcquisitionTime(静态平板)
* 功能描述: 获取采集时间间隔
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_time - 时间,单位是毫秒ms
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetLiveAcquisitionTime(void *handle, int *out_time);

/*********************************************************
* 编    号: No026
* 函 数 名: HBI_SetSelfDumpingTime
* 功能描述: 设置采集时间间隔(动态平板)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int time - 间隔时间,单位是毫秒ms，>= 1000ms
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSelfDumpingTime(void *handle, int time);

/*********************************************************
* 编    号: No027
* 函 数 名: HBI_GetSelfDumpingTime(动态平板)
* 功能描述: 获取采集时间间隔
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_time - 时间,单位是毫秒ms
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSelfDumpingTime(void *handle, int *out_time);

/*********************************************************
* 编    号: No022
* 函 数 名: HBI_TriggerAndCorrectApplay
* 功能描述: 设置触发模式和图像校正使能（工作站）新版本
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int _triggerMode,1-软触发，3-高压触发，4-FreeAED。
			IMAGE_CORRECT_ENABLE* pCorrect,见HbiType.h。
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:替换HBI_WorkStationInitDllCfg和HBI_QuckInitDllCfg接口
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_TriggerAndCorrectApplay(void *handle, int _triggerMode, IMAGE_CORRECT_ENABLE* pCorrect);

/*********************************************************
* 编    号: No023
* 函 数 名: HBI_UpdateTriggerMode
* 功能描述: 设置触发模式
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int _triggerMode,1-软触发，3-高压触发，4-FreeAED。
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_UpdateTriggerMode(void *handle, int _triggerMode);

/*********************************************************
* 编    号: No024
* 函 数 名: HBI_UpdateCorrectEnable
* 功能描述: 更新图像固件校正使能
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			IMAGE_CORRECT_ENABLE* pCorrect,见HbiType.h。
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_UpdateCorrectEnable(void *handle, IMAGE_CORRECT_ENABLE* pCorrect);

/*********************************************************
* 编    号: No025
* 函 数 名: HBI_GetCorrectEnable
* 功能描述: 获取图像固件校正使能
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			IMAGE_CORRECT_ENABLE* pCorrect,见HbiType.h。
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetCorrectEnable(void *handle, IMAGE_CORRECT_ENABLE *pCorrect);

/*********************************************************
* 编    号: No026
* 函 数 名: HBI_SetSoftwareCorrect
* 功能描述: 设置校正使能，仅限于SDK校正，即软件矫正（相对于固件校正）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			SOFTWARE_CALIBRATE_ENABLE inEnable - 校正使能状态,见HbDllType.h中SOFTWARE_CALIBRATE_ENABLE struct
		Out: 无
* 返 回 值：int
		0   成功
		非0 失败，见HbDllError.h错误码
* 备    注:新接口
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSoftwareCorrect(void *handle, SOFTWARE_CALIBRATE_ENABLE inEnable);

/*********************************************************
* 编    号: No027
* 函 数 名: HBI_GetSoftwareCorrect
* 功能描述: 获取校正使能参数，仅限于SDK校正，即软件矫正（相对于固件校正）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			SOFTWARE_CALIBRATE_ENABLE inEnable - 校正使能状态,见HbDllType.h中
			SOFTWARE_CALIBRATE_ENABLE struct
		Out: 无
* 返 回 值：int
		0   成功
		非0 失败，见HbDllError.h错误码
* 备    注:新接口
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSoftwareCorrect(void *handle, SOFTWARE_CALIBRATE_ENABLE *inEnable);

/*********************************************************
* 编    号: No028
* 函 数 名: HBI_SetAcqSpanTm
* 功能描述: 设置AED积分时间
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int time - 间隔时间,单位是毫秒ms，>= 500ms
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetAedIntegrateTm(void *handle, int time);

/*********************************************************
* 编    号: No029
* 函 数 名: HBI_GetAedIntegrateTm
* 功能描述: 获取AED积分时间
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_time - 时间,单位是毫秒ms
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetAedIntegrateTm(void *handle, int *out_time);

/*********************************************************
* 编    号: No030
* 函 数 名: HBI_SetAedThreshold
* 功能描述: 设置AED阈值
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		int out_ivalue - 阈值 [25,000~1,000,000]
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetAedThreshold(void *handle, int in_ivalue);

/*********************************************************
* 编    号: No031
* 函 数 名: HBI_GetAedThreshold
* 功能描述: 获取AED阈值
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_ivalue - 阈值 [10,000~1,000,000]
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetAedThreshold(void *handle, int *out_ivalue);

/*********************************************************
* 编    号: No032
* 函 数 名: HBI_SetSaturationValue
* 功能描述: 设置饱和值
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_ivalue - 饱和值 [0~65,535]
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSaturationValue(void *handle, int in_ivalue);

/*********************************************************
* 编    号: No033
* 函 数 名: HBI_GetSaturationValue
* 功能描述: 获取饱和值
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int *out_ivalue - 饱和值 [0~65,535]
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSaturationValue(void *handle, int *out_ivalue);

/*********************************************************
* 编    号: No034
* 函 数 名: HBI_SetClippingValue
* 功能描述: 设置图像剪裁值
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_ivalue - 剪裁值 [0~65,535]
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetClippingValue(void *handle, int in_ivalue);

/*********************************************************
* 编    号: No035
* 函 数 名: HBI_GetClippingValue
* 功能描述: 获取图像剪裁值
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *out_ivalue - 剪裁值 [0~65,535]
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetClippingValue(void *handle, int *out_ivalue);

/*********************************************************
* 编    号: No036
* 函 数 名: HBI_SetPGALevel
* 功能描述: 设置增益挡位,即设置可编程积分电容档位,提高灵敏度
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int mode - 模式
			[n]-Invalid
			[1]-0.6pC
			[2]-1.2pC
			[3]-2.4pC
			[4]-3.6pC
			[5]-4.8pC
			[6]-7.2pC,默认7.2pC
			[7]-9.6pC
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetPGALevel(void *handle, int nGainLevel);

/*********************************************************
* 编    号: No037
* 函 数 名: HBI_GetGainMode
* 功能描述: 获取增益挡位,即获取可编程积分电容档位
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		[n]-Invalid
		[1]-0.6pC
		[2]-1.2pC
		[3]-2.4pC
		[4]-3.6pC
		[5]-4.8pC
		[6]-7.2pC
		[7]-9.6pC
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetPGALevel(void *handle);

/*********************************************************
* 编    号: No038
* 函 数 名: HBI_SetLPFLevel
* 功能描述: 设置AEC采集模式
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int nLPFLevel - 档位
			[n]-Invalid
			[0]-210khz,默认210khz
			[1]-105khz
			[2]-52khz
			[3]-26khz
			[4]-13khz
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetLPFLevel(void *handle, int nLPFLevel);

/*********************************************************
* 编    号: No039
* 函 数 名: HBI_GetLPFLevel
* 功能描述: 获取低通滤波器档位参数
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		[0]-210khz,默认210khz
		[1]-105khz
		[2]-52khz
		[3]-26khz
		[4]-13khz
		[n]-Invalid
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetLPFLevel(void *handle);

/*********************************************************
* 编    号: No040
* 函 数 名: HBI_SetBinning
* 功能描述: 设置图像binning方式
* 参数说明:
		In:
			void *handle - 句柄(无符号指针)
			unsigned int nbin - 1:1x1,2:2x2,3:3x3(暂不支持),4:4x4
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetBinning(void *handle, unsigned int bin);

/*********************************************************
* 编    号: No041
* 函 数 名: HBI_GetBinning
* 功能描述: 获取图像binning方式
* 参数说明:
		In: void *handle - 句柄(无符号指针)
unsigned int *nbin - 1:1x1,2:2x2,3:3x3(暂不支持),4:4x4
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetBinning(void *handle, unsigned int *bin);

/*********************************************************
* 编    号: No042
* 函 数 名: HBI_SetPreviewMode
* 功能描述: 设置Preview预览或取消预览
* 功能描述: 设置Preview预览或取消预览
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int inTriggMode
				1-软触发
				3-高压触发
				4-FreeAED
				8-SAEC
				其他不支持。
			int inPreviewMode
				0-normal image
				1-preview image
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetPreviewMode(void *handle, int inTriggMode, int inPreviewMode);

/*********************************************************
* 编    号: No043
* 函 数 名: HBI_GetPreviewMode
* 功能描述: 设置Preview
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:int *outMode - preview mode [0~2]
			0-normal image,1-preview image,2-preview image and normal image。
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetPreviewMode(void *handle, int *outMode);

/*********************************************************
* 编    号: No044
* 函 数 名: HBI_SAecModeApply
* 功能描述: 设置或取消SAEC模式
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int inPreviewMode
				0-normal image
				1-preview image
			int inPerTime  - fpd pre ready delay time
			int inPostTime - fpd post ready delay time
		Out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:分为两种情况：
			1》启用：inPreviewMode=1(preview image)，inPerTime和inPostTime(客户指定)
			2》取消：inPreviewMode=0(normal image)，inPerTime和inPostTime默认即可
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SAecModeApply(void *handle, int inPreviewMode, int inPerTime = 0, int inPostTime = 0);

/*********************************************************
* 编    号: No045
* 函 数 名: HBI_SAecAcq
* 功能描述: SAEC采集上图指令
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SAecAcq(void *handle);

/*********************************************************
* 编    号: No046
* 函 数 名: HBI_RegProgressCallBack
* 功能描述: 注册回调函数
* 参数说明: 处理固件升级反馈信息
		In: void *handle - 句柄(无符号指针)
			USER_CALLBACK_HANDLE_PROCESS handleStatusfun - 注册回调函数
			void* pObject - 对象指针，亦可为空
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RegProgressCallBack(void *handle, USER_CALLBACK_HANDLE_PROCESS handleStatusfun, void* pObject);

/*********************************************************
* 编    号: No047
* 函 数 名: HBI_GenerateTemplate
* 功能描述: 快速生成模板
* 参数说明:
		In: void *handle - 句柄(无符号指针)
				EnumIMAGE_ACQ_CMD _mode - 生成模板类型
				OFFSET_TEMPLATE_TYPE      连续采集一组暗场图 - Firmware PreOffset Template
				GAIN_TEMPLATE_TYPE        连续采集一组亮场图 - gain Template
				DEFECT_TEMPLATE_GROUP1,   连续采集一组亮场图 - defect group1
				DEFECT_TEMPLATE_GROUP2,   连续采集一组亮场图 - defect group2
				DEFECT_ACQ_AND_TEMPLATE,  连续采集一组亮场图 - defect group3 and generate template
				SOFTWARE_OFFSET_TEMPLATE  连续采集一组暗场图 - Software PreOffset Template
			int bprevew - 是否生成preview模板，1-生成，0-不生成
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateTemplate(void *handle, EnumIMAGE_ACQ_CMD _mode, int bprevew = 0);

/*********************************************************
* 编    号: No048
* 函 数 名: HBI_DownloadTemplate
* 功能描述: 下载矫正模板
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			DOWNLOAD_FILE *downloadfile - 下载模板文件对象指针
              emUPLOAD_FILE_TYPE emfiletype-模板类型(OFFSET_TMP-offset模板.GAIN_TMP-gain模板,DEFECT_TMP-defect模板)
	          int nBinningtype-模板binning类型（1-binning1*1,2-binning2*2,3-binning3*3,4-binning4*4）
	          char filepath-模板绝对路径
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadTemplate(void *handle, DOWNLOAD_FILE *downloadfile);

/*********************************************************
* 编    号: No049
* 函 数 名: HBI_DownloadTemplateEx
* 功能描述: 下载矫正模板
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			DOWNLOAD_MODE *downloadmode - 下载模板文件链表指针
				DOWNLOAD_FILE *downloadfile - 下载模板文件对象指针
						emUPLOAD_FILE_TYPE emfiletype-模板类型(OFFSET_TMP-offset模板.GAIN_TMP-gain模板,DEFECT_TMP-defect模板)
						int nBinningtype-模板binning类型（1-binning1*1,2-binning2*2,3-binning3*3,4-binning4*4）
						char filepath-模板绝对路径
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadTemplateEx(void *handle, DOWNLOAD_MODE *downloadmode);

/*********************************************************
* 编    号: No070
* 函 数 名: HBI_DownloadTemplateByType
* 功能描述: 按照类型默认下载固定矫正模板文件
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int infiletype - 下载文件类型0-gain模板，1-defect模板，2-offset模板，其他-不支持
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadTemplateByType(void *handle, int infiletype);

/*********************************************************
* 编    号: No050
* 函 数 名: HBI_StopDownloadTemplate
* 功能描述: 停止下载矫正模板
* 参数说明:
		In:  void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_StopDownloadTemplate(void *handle);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新固件
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* 编    号: No051
* 函 数 名: HBI_UpgradeFirmware
* 功能描述: 升级固件信息或无线嵌入式软件
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			char *binfile - bin文件路径
			int filetype - 0:FPGA软件，1:Embedded软件
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_UpgradeFirmware(void *handle, char *binfile, int filetype=0);

/*********************************************************
* 编    号: No052
* 函 数 名: HBI_StopUpdateFirmware
* 功能描述: 停止更新固件HBI_StopDownloadTemplate
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		out:无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_StopUpdateFirmware(void *handle);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* 编    号: No053
* 函 数 名: HBI_Dumping
* 功能描述: 清空指令
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_Dumping(void *handle);

/*********************************************************
* 编    号: No054
* 函 数 名: HBI_GetSysParamCfg
* 功能描述: 回读系统RAM/ROM参数,异步事件，在参数在回调函数中反馈
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	int cmd  - rom or ram
	int type - user or admin
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetSysParamCfg(void *handle, int cmd, int type);

/*********************************************************
* 编    号: No055
* 函 数 名: HBI_SetSysParamCfg
* 功能描述: 配置系统RAM/ROM参数
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	int cmd -
	int type -
	RegCfgInfo* pRegCfg -
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSysParamCfg(void *handle, int cmd, int type, RegCfgInfo* pRegCfg);

/*********************************************************
* 编    号: No056
* 函 数 名: HBI_SetGigabitEther
* 功能描述: 设置网络信息参数
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		EtherInfo* pEther,见HbiType.h。
	Out:无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetGigabitEther(void *handle, EtherInfo* pEther);

/*********************************************************
* 编    号: No057
* 函 数 名: HBI_RetransMissPacket
* 功能描述: 单包丢包重传
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RetransMissPacket(void *handle);

/*********************************************************
* 编    号: No058
* 函 数 名: HBI_RetransMissFrame
* 功能描述: 整帧重传
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_RetransMissFrame(void *handle);

/*********************************************************
* 编    号: No059
* 函 数 名: HBI_IsConnect
* 功能描述: 判断平板是为连接状态
* 参数说明:
		In: void *handle - 句柄(无符号指针)
* 返 回 值：int
		1 - 连接
		0 - 断开
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_IsConnect(void *handle);

/*********************************************************
* 编    号: No060
* 函 数 名: HBI_GetCurFPDStatus
* 功能描述: 获取平板当前状态
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		0 - idle status，表示可以执行该操作
		1 - busy status，表示状态繁忙中，拒绝执行该操作
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetCurFPDStatus(void *handle);

/*********************************************************
* 编    号: No061
* 函 数 名: HBI_SetCapacity
* 功能描述: 设置缓冲区容量(大小)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			unsigned int nframesize - 可存储的帧数,
			缓冲区大小等于帧大小乘以帧数。
		Out: 无
* 返 回 值：int
		0   成功
		非0 失败，见HbDllError.h错误码
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetCapacity(void *handle, unsigned int nframesize);

/*********************************************************
* 编    号: No062
* 函 数 名: HBI_SetRawStyle
* 功能描述: 设置是否保存图像以及图像文件形式
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			bool bsave - 保存拟或显示,false:显示不保存，true:保存不显示
			bool bsingleraw - 报存在单个文件或多个文件,false:1帧数据保存1个文件，true:多帧数据可保存在一个文件中
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetRawStyle(void *handle, bool bsave, bool bsingleraw = false);

/*********************************************************
* 编    号: No063
* 函 数 名: HBI_SetAqcProperty
* 功能描述: 设置采集属性
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			FPD_AQC_MODE _mode - 采集模式以及参数
		Out: 无
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetAqcProperty(void *handle, FPD_AQC_MODE _mode);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 调试PCIE接口
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* 编    号: No064
* 函 数 名: HBI_SetDebugMode
* 功能描述: 切换调试模式和生产模式-用于调试PCIE接口
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		int mode - 0:生产模式，1-PCIE调试模式
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetDebugMode(void *handle, int mode);

/*********************************************************
* 编    号: No065
* 函 数 名: HBI_PcieSendBuff
* 功能描述: 向PCIE地址发送数据，仅限于PCIE调试模式下有效
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		ePCIE_WR_TYPE etype - bar地址或ddr地址类型
		long addr - ar地址或ddr地址
		unsigned char *szSndBuff - 写入缓冲区
		int nlen - 缓冲区数据长度
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PcieSendBuff(void *handle, ePCIE_WR_TYPE etype, long addr, unsigned char *szSndBuff, int nlen);

/*********************************************************
* 编    号: No066
* 函 数 名: HBI_InitOffsetMode
* 功能描述: 初始化暗场模板
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		ePCIE_WR_TYPE etype - bar地址或ddr地址类型
		long addr - ar地址或ddr地址
		unsigned char *szRcvbuff - 接收缓冲区
		int nlen - 缓冲区数据长度
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PcieRecvBuff(void *handle, ePCIE_WR_TYPE _type, long addr, unsigned char *szRcvbuff, int nlen);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 分布生成模板，用于模板测试，集成请参考快速生成模板接口
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* 编    号: No067
* 函 数 名: HBI_InitOffsetMode
* 功能描述: 初始化暗场模板
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		CALIBRATE_INPUT_PARAM calibrate_param,见HbiType.h。
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitOffsetMode(void *handle, CALIBRATE_INPUT_PARAM calibrate_param);

/*********************************************************
* 编    号: No068
* 函 数 名: HBI_InsertOffsetMode
* 功能描述: 向offset矫正模型中插入数据
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		int group_id - 组ID
		char *filepath - 文件路径
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InsertOffsetMode(void *handle, int group_id, char *filepath);

/*********************************************************
* 编    号: No069
* 函 数 名: HBI_ClearOffsetMode
* 功能描述: 清空offset矫正模型
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ClearOffsetMode(void *handle);

/*********************************************************
* 编    号: No070
* 函 数 名: HBI_GenerateOffsetTemp
* 功能描述: 生成offset模板
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		int raw_num - 暗场图个数
		int bprevew - 是否生成preview模板，1-生成，0-不生成
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateOffsetTemp(void *handle, int raw_num, int bprevew = 0);

/*********************************************************
* 编    号: No071
* 函 数 名: HBI_InitGainMode
* 功能描述: 初始化gain矫正模型
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		CALIBRATE_INPUT_PARAM calibrate_param - 矫正参数
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitGainMode(void *handle, CALIBRATE_INPUT_PARAM calibrate_param);

/*********************************************************
* 编    号: No072
* 函 数 名: HBI_InsertGainMode
* 功能描述: 向gain矫正模型中插入数据
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	int group_id - 组ID
	char *filepath - 文件路径
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InsertGainMode(void *handle, int group_id, char *filepath);

/*********************************************************
* 编    号: No073
* 函 数 名: HBI_ClearGainMode
* 功能描述: 清空gain矫正模型
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ClearGainMode(void *handle);

/*********************************************************
* 编    号: No074
* 函 数 名: HBI_GenerateGainTemp
* 功能描述: 生成gain模板
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		int group_sum - 组数
		int per_group_num - 每组包含图片个数
		int bprevew       - 是否生成preview模板，1-生成，0-不生成
		Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateGainTemp(void *handle, int group_sum, int per_group_num, int bprevew = 0);

/*********************************************************
* 编    号: No075
* 函 数 名: HBI_InitDefectMode
* 功能描述: 初始化defect矫正模型
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		CALIBRATE_INPUT_PARAM calibrate_param - 矫正参数
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitDefectMode(void *handle, CALIBRATE_INPUT_PARAM calibrate_param);

/*********************************************************
* 编    号: No076
* 函 数 名: HBI_InsertDefectMode
* 功能描述: 向defect矫正模型中插入数据
* 参数说明:
	In: void *handle - 句柄(无符号指针)
		int group_id - 组ID
		char *filepath - 文件路径
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InsertDefectMode(void *handle, int group_id, char *filepath);

/*********************************************************
* 编    号: No077
* 函 数 名: HBI_ClearDefectMode
* 功能描述: 清空defect矫正模型
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ClearDefectMode(void *handle);

/*********************************************************
* 编    号: No078
* 函 数 名: HBI_GenerateDefectTemp
* 功能描述: 生成defect模板
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	int group_sum - 组数
	int per_group_num - 每组包含图片个数
	int bprevew       - 是否生成preview模板，1-生成，0-不生成
	Out: 无
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GenerateDefectTemp(void *handle, int group_sum, int per_group_num, int bprevew = 0);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文件工作目录地址管理，暂未实现
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////*********************************************************
////* 编    号: No079
////* 函 数 名: HBI_SetFileDirectory
////* 功能描述: 设置文件存储路径
////* 参数说明:
////		In: void *handle - 句柄(无符号指针)
////			HBI_FILE_TYPE filetype - 文件类型，枚举类
////				0    IMAGE_FILE
////				1    TEMPLATE_FILE
////				char *dirpath - 文件路径
////		Out: 无
////* 返 回 值：int
////		0 - 成功
////		1 - 失败
////* 备    注:
////*********************************************************/
////HBI_FPD_DLL int __stdcall HBI_SetFileDirectory(void *handle, HBI_FILE_TYPE filetype, char *dirpath);

/*********************************************************
* 编    号: No080
* 函 数 名: HBI_GetFileDirectory
* 功能描述: 获取文件存储路径
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			HBI_FILE_TYPE filetype - 文件类型，枚举类
				0    IMAGE_FILE
				1    TEMPLATE_FILE
		Out: 无
* 返 回 值：int
		NULL  - 失败
		char* - 返回路径
* 备    注:
*********************************************************/
HBI_FPD_DLL char* __stdcall HBI_GetFileDirectory(void *handle, HBI_FILE_TYPE filetype);

/*********************************************************
* 编    号: No081
* 函 数 名: HBI_GetTempFileFullDirectory
* 功能描述: 获取当前模板文件全目录
* 参数说明:
		In: void *handle - 句柄(无符号指针)
		Out: 无
* 返 回 值：int
		NULL  - 失败
		char* - 返回路径
* 备    注:
*********************************************************/
HBI_FPD_DLL char* __stdcall HBI_GetTempFileFullDirectory(void *handle);

/*********************************************************
* 编    号: No082
* 函 数 名: HBI_IsBusyNow
* 功能描述: 判断当前SDK是否正处理中，不允许当前操作
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			eventtype eventtype - 生成模板类型
				1    分布生成模板处理中
				2    快速生成模板处理中
				3,   采集过程中
				4,   设置参数过程中
		Out: 无
* 返 回 值：int
		0 - idle status，表示可以执行该操作
		1 - busy status，表示状态繁忙中，拒绝执行该操作
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_IsBusyNow(void *handle, int eventtype);

/*********************************************************
* 编    号: No083
* 函 数 名: HBI_SetImageROI
* 功能描述: set region of interest
* 参数说明:
		In: void *handle  - 句柄(无符号指针)
		In: ImageROI *roi - The param of 'region of interest'
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetImageROI(void *handle, ImageROI *roi);

/*********************************************************
* 编    号: No084
* 函 数 名: HBI_GetImageROI
* 功能描述: get region of interest
* 参数说明:
		In: void *handle - 句柄(无符号指针)
* 返 回 值：ImageROI*
		NULL   - 失败
		非NULL - 成功,The param of 'region of interest'
* 备    注:
*********************************************************/
HBI_FPD_DLL ImageROI* __stdcall HBI_GetImageROI(void *handle);

/*********************************************************
* 编    号: No085
* 函 数 名: HBI_InitUserMode
* 功能描述: 初始化user mode list，注意配置文件hbi_mode_config.ini或hbi_mode_config.json
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			FPD_USER_MODE mode - 用户Mode
		Out: 无
* 返 回 值：int
		0 - 成功
		1 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_InitUserMode(void *handle);
/*********************************************************
* 编    号: No086
* 函 数 名: HBI_AddUserMode
* 功能描述: 添加用户Mode到user mode list
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			FPD_USER_MODE mode - 用户Mode
		Out: 无
* 返 回 值：int
		0 - 成功
		1 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_AddUserMode(void *handle, FPD_USER_MODE mode);
// 删除一个mode从user mode list
HBI_FPD_DLL int __stdcall HBI_DelUserMode(void *handle, FPD_USER_MODE mode);
// 保存当前user mode list
HBI_FPD_DLL int __stdcall HBI_SaveUserMode(void *handle);
// 获取User Mode的大小
HBI_FPD_DLL unsigned int __stdcall HBI_GetUserModeSize(void *handle);
// 通过mode id获取User Mode Id
HBI_FPD_DLL FPD_USER_MODE* __stdcall HBI_GetUserModeById(void *handle, unsigned int modeid);
// 应用 User Mode 通过 Mode
HBI_FPD_DLL int  __stdcall HBI_EnableUserMode(void *handle, FPD_USER_MODE mode);
// 清空User Mode列表
HBI_FPD_DLL int  __stdcall HBI_ClearUpUserMode(void *handle);
// 获取当前User Mode的校正文件路径
HBI_FPD_DLL char* __stdcall HBI_GetCurrentCorrectFilePath(void *handle);
// 判断mode的是否存在
HBI_FPD_DLL bool __stdcall HBI_IsExistMode(void *handle, FPD_USER_MODE mode);
//
HBI_FPD_DLL int __stdcall HBI_DetectorAuthor(void *handle, char *pcode);
//
/*********************************************************
* 编    号: No099
* 函 数 名: HBI_DownloadImage
* 功能描述: 下载图像(无线平板)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int beginnumber - 下载开始图像序号
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_DownloadImage(void *handle, int beginnumber = 1);

/*********************************************************
* 编    号: No100
* 函 数 名: HBI_SetSleepState
* 功能描述: 设置平板为休眠状态(无线平板)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SetSleepState(void *handle);

/*********************************************************
* 编    号: No101
* 函 数 名: HBI_WakeUpFpd
* 功能描述: 从休眠状态唤醒平板(无线平板)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_WakeUpFpd(void *handle);

/*********************************************************
* 编    号: No102
* 函 数 名: HBI_EnableEmmcStorage
* 功能描述: Emmc存储图像使能(无线平板)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int nenable - 1:存图,其他:不存图
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_EnableEmmcStorage(void *handle, int nenable = 0);

/*********************************************************
* 编    号: No103
* 函 数 名: HBI_ReflashBatteryStatusInfo
* 功能描述: 刷新电池信息(无线平板)
* 参数说明:
	In: void *handle - 句柄(无符号指针)
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注: 异步函数，通过回调函数反馈00
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_ReflashBatteryStatusInfo(void *handle);

/*********************************************************
* 编    号: No104
* 函 数 名: HBI_GetBatteryStatusInfo
* 功能描述: 获取电池信息(无线平板)
* 参数说明:
	In: void *handle - 句柄(无符号指针)
	    BATTERY_STATUS_INFO *pBatteryStatus - 电池状态信息 见<HbiType.h>

    Out:BATTERY_STATUS_INFO *pBatteryStatus
* 返 回 值：int
	0   - 成功
	非0 - 失败
* 备    注:同步函数，参数同步后通过入参反馈给上位机
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_GetBatteryStatusInfo(void *handle, BATTERY_STATUS_INFO *pBatteryStatus);
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************
* 编    号: No105
* 函 数 名: HBI_TriggerBinningAcqTime
* 功能描述: 设置触发模式、binning方式以及帧率（采集图像时间间隔）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int triggerMode - 触发模式
				静态平板（每秒1帧）：1-软触发，2-Clear,3-高压触发，4-FreeAED
				动态平板（每秒2帧以上）：05-Dynamic:Hvg Sync Mode,06-Dynamic:Fpd Sync Mode,7-Continue Mode
			unsigned char binning - 1:1x1,2:2x2,3:3x3,4:4x4，其他不支持
			int time - 间隔时间,单位是毫秒ms,大于0
			int nfeedback - 1：设置成功后自动反馈固件参数，非1：反馈设置成功信号（见参数和信号见回调函数）
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_TriggerBinningAcqTime(void *handle, int triggerMode, unsigned char binning, int acqtime, int nfeedback = 0);

/*********************************************************
* 编    号: No106
* 函 数 名: HBI_PgaBinningAcqTime
* 功能描述: 设置PGA档位、binning方式以及帧率（采集图像时间间隔）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int nPgaLevel - PGA 档位，[n]-Invalid,[1]-0.6pC,[2]-1.2pC,[3]-2.4pC,[4]-3.6pC,[5]-4.8pC,[6]-7.2pC,默认7.2pC,[7]-9.6pC
			unsigned char binning - 1:1x1,2:2x2,3:3x3,4:4x4，其他不支持
			int acqtime - 间隔时间,单位是毫秒ms,大于0
			int nfeedback - 1：设置成功后自动反馈固件参数，非1：反馈设置成功信号（见参数和信号见回调函数）
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PgaBinningAcqTime(void *handle, int nPgaLevel, unsigned char binning, int acqtime, int nfeedback = 0);

/*********************************************************
* 编    号: No107
* 函 数 名: HBI_TriggerPgaBinningAcqTime
* 功能描述: 设置触发模式、PGA档位、binning方式以及帧率（采集图像时间间隔）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int triggerMode - 触发模式
				静态平板（每秒1帧）：1-软触发，2-Clear,3-高压触发，4-FreeAED
				动态平板（每秒2帧以上）：05-Dynamic:Hvg Sync Mode,06-Dynamic:Fpd Sync Mode,7-Continue Mode
			int nPgaLevel - PGA 档位，[n]-Invalid,[1]-0.6pC,[2]-1.2pC,[3]-2.4pC,[4]-3.6pC,[5]-4.8pC,[6]-7.2pC,默认7.2pC,[7]-9.6pC
			unsigned char binning - 1:1x1,2:2x2,3:3x3,4:4x4，其他不支持
			int acqtime - 间隔时间,单位是毫秒ms,大于0
			int nfeedback - 1：设置成功后自动反馈固件参数，非1：反馈设置成功信号（见参数和信号见回调函数）
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_TriggerPgaBinningAcqTime(void *handle, int triggerMode, int nPgaLevel, unsigned char binning, int acqtime, int nfeedback = 0);

/*********************************************************
* 编    号: No108
* 函 数 名: HBI_PgaAcqTime
* 功能描述: 设置PGA档位、及帧率（采集图像时间间隔）
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int nPgaLevel - PGA 档位，[n]-Invalid,[1]-0.6pC,[2]-1.2pC,[3]-2.4pC,[4]-3.6pC,[5]-4.8pC,[6]-7.2pC,默认7.2pC,[7]-9.6pC
			int acqtime - 间隔时间,单位是毫秒ms,大于0
			int nfeedback - 1：设置成功后自动反馈固件参数，非1：反馈设置成功信号（见参数和信号见回调函数）
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_PgaAcqTime(void *handle, int nPgaLevel, int acqtime, int nfeedback = 0);

/*********************************************************
* 编    号: No109
* 函 数 名: HBI_SwitchNetTypeWlanMode
* 功能描述: 切换无线2.4G/5G网络和WLAN AP/Client Mode(无线平板)
* 参数说明:
		In: void *handle - 句柄(无符号指针)
			int nNetType - 无线网络类型，1-2.4G,2-5G,其他-无效
			int nWlanMode - WLAN模式，1-AP Mode,2-Client Mode,其他-无效
* 返 回 值：int
		0   - 成功
		非0 - 失败
* 备    注:
*********************************************************/
HBI_FPD_DLL int __stdcall HBI_SwitchNetTypeWlanMode(void *handle, int nNetType, int nWlanMode);
/***************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////
// 导出类 暂时未开发，不提供
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
