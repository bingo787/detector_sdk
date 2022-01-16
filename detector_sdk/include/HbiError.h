/*---------------------------------------------------------------------------
* Copyright (c) 2019 上海昊博影像科技有限公司
* All rights reserved.
*
* 文件名称: HbiError.h
* 文件标识:
* 摘    要: 平板探测器错误信息头文件
*
* 当前版本: 3.0
* 作    者: mhyang
* 完成日期: 2020/11/20
----------------------------------------------------------------------------*/
#ifndef __HB_DLL_ERROR_H_
#define __HB_DLL_ERROR_H_

enum HBIRETCODE {
	HBI_SUCCSS                    = 0,
	HBI_ERR_ININT_FAILED          = 8000,
	HBI_ERR_OPEN_DETECTOR_FAILED  = 8001,
	HBI_ERR_INVALID_PARAMS        = 8002,
	HBI_ERR_CONNECT_FAILED        = 8003,
	HBI_ERR_MALLOC_FAILED         = 8004,
	HBI_ERR_RELIMGMEM_FAILED      = 8005,
	HBI_ERR_RETIMGMEM_FAILED      = 8006,
	HBI_ERR_NODEVICE              = 8007,
	HBI_ERR_NODEVICE_TRY_CONNECT  = 8008,
	HBI_ERR_DEVICE_BUSY           = 8009,
	HBI_ERR_SENDDATA_FAILED       = 8010,
	HBI_ERR_RECEIVE_DATA_FAILED   = 8011,
	HBI_ERR_COMMAND_DISMATCH      = 8012,
	HBI_ERR_NO_IMAGE_RAW          = 8013,
	HBI_ERR_PTHREAD_ACTIVE_FAILED = 8014,
	HBI_ERR_STOP_ACQUISITION      = 8015,
	HBI_ERR_INSERT_FAILED         = 8016,
	HBI_ERR_GET_CFG_FAILED        = 8017,
	HBI_NOT_SUPPORT               = 8018,
	HBI_REGISTER_CALLBACK_FAILED  = 8019,
	HBI_SEND_MESSAGE_FAILD        = 8020,
	HBI_ERR_WORKMODE              = 8021,
	HBI_FAILED                    = 8022,
	HBI_FILE_NOT_EXISTS           = 8023,
	HBI_COMM_TYPE_ERR             = 8024,
	HBI_TYPE_IS_NOT_EXISTS        = 8025,
	HBI_SAVE_FILE_FAILED          = 8026,
	HBI_INIT_PARAM_FAILED         = 8027,
	HBI_INIT_FILE_NOT_EXIST       = 8028,
	HBI_INVALID_FLAT_PANEL        = 8029,
	HBI_INVALID_DLL_HANDLE        = 8031,
	HBI_FPD_IS_DISCONNECT         = 8032,
	HBI_ERR_DETECTOR_NUMBER       = 8033,
	HBI_ERR_DATA_CHECK_FAILED     = 8034,
	HBI_ERR_CFG_ISEMPTY           = 8035,
	HBI_END                       = 8036
};

struct CodeStringTable
{
	int		     num;
	int        HBIRETCODE;
	const char *errString;
};
static const CodeStringTable CrErrStrList[] = {
	{ 0,  HBI_SUCCSS, "Success" },
	{ 1,  HBI_ERR_ININT_FAILED, "Init dll failed" },
	{ 2,  HBI_ERR_OPEN_DETECTOR_FAILED, "Open device driver failed" },
	{ 3,  HBI_ERR_INVALID_PARAMS, "Parameter error" },
	{ 4,  HBI_ERR_CONNECT_FAILED, "Connect failed" },
	{ 5,  HBI_ERR_MALLOC_FAILED, "Malloc memory failed" },
	{ 6,  HBI_ERR_RELIMGMEM_FAILED, "Releaseimagemem fail" },
	{ 7,  HBI_ERR_RETIMGMEM_FAILED, "ReturnImageMem fail" },
	{ 8,  HBI_ERR_NODEVICE, "No Init DLL Instance" },
	{ 9,  HBI_ERR_NODEVICE_TRY_CONNECT, "Disconnect status" },
	{ 10, HBI_ERR_DEVICE_BUSY, "Fpd is busy" },
	{ 11, HBI_ERR_SENDDATA_FAILED, "SendData failed" },
	{ 12, HBI_ERR_RECEIVE_DATA_FAILED, "Receive Data failed" },
	{ 13, HBI_ERR_COMMAND_DISMATCH, "Command dismatch" },
	{ 14, HBI_ERR_NO_IMAGE_RAW, "No Image raw" },
	{ 15, HBI_ERR_PTHREAD_ACTIVE_FAILED, "Pthread active failed" },
	{ 16, HBI_ERR_STOP_ACQUISITION, "Pthread stop data acquisition failed" },
	{ 17, HBI_ERR_INSERT_FAILED, "insert calibrate mode failed" },
	{ 18, HBI_ERR_GET_CFG_FAILED, "get Fpd config failed" },
	{ 19, HBI_NOT_SUPPORT, "not surport yet" },
	{ 20, HBI_REGISTER_CALLBACK_FAILED, "failed to register callback function" },
	{ 21, HBI_SEND_MESSAGE_FAILD, "send message failed" },
	{ 22, HBI_ERR_WORKMODE, "switch work mode failed" },
	{ 23, HBI_FAILED, "operation failed" },
	{ 24, HBI_FILE_NOT_EXISTS, "file does not exist" },
	{ 25, HBI_COMM_TYPE_ERR, "communication is not exist"},
	{ 26, HBI_TYPE_IS_NOT_EXISTS, "this type is not exists"},
	{ 27, HBI_SAVE_FILE_FAILED, "save file failed"},
	{ 28, HBI_INIT_PARAM_FAILED, "Init dll param failed"},
	{ 29, HBI_INIT_FILE_NOT_EXIST, "Init dll config file is not exist"},
	{ 30, HBI_INVALID_FLAT_PANEL, "Invalid flat panel detector"},
	{ 31, HBI_INVALID_DLL_HANDLE, "Invalid dll instance handle"},
	{ 32, HBI_FPD_IS_DISCONNECT, "Fpd is disconnect"},
	{ 33, HBI_ERR_DETECTOR_NUMBER, "Detector number error"},
	{ 34, HBI_ERR_DATA_CHECK_FAILED, "Data Check failed"},
    { 35, HBI_ERR_CFG_ISEMPTY, "The configuration variable is empty"},
    { 36, HBI_END, "Exit monitoring"}
};
///*********************************************
//* 描  述：通过返回码获取当前错误信息
//* 函  数：GetHbiErrorString
//* 参  数：CodeStringTable* inTable 返回码表
//*         int count                返回码个数
//*         int recode               返回码
//* 返回值：
//*         const char * 返回字符串
//* 备  注: BY MH.YANG 2019/12/09
//*********************************************/
//const char *GetHbiErrorString(CodeStringTable* inTable, int count, int recode)
//{
//	const char *retString = "Unknown";
//	for(int i = 0; i < count; i++) {
//		if(inTable[i].HBIRETCODE == recode) {
//			retString = inTable[i].errString;
//			break;
//		}
//	}
//	return retString;
//}
//int main()
//{
//		static const CodeStringTable CrErrStrList[] = {
//			{ 0,  HBI_SUCCSS, "Success" },
//			{ 1,  HBI_ERR_OPEN_DETECTOR_FAILED, "Open device driver failed" },
//			{ 2,  HBI_ERR_INVALID_PARAMS, "Parameter error" },
//			{ 3,  HBI_ERR_CONNECT_FAILED, "Connect failed" },
//			{ 4,  HBI_ERR_MALLOC_FAILED, "Malloc memory failed" },
//			{ 5,  HBI_ERR_RELIMGMEM_FAILED, "Releaseimagemem fail" },
//			{ 6,  HBI_ERR_RETIMGMEM_FAILED, "ReturnImageMem fail" },
//			{ 7,  HBI_ERR_NODEVICE, "No Device" },
//			{ 8,  HBI_ERR_NODEVICE_TRY_CONNECT, "No Device,Try again" },
//			{ 9,  HBI_ERR_DEVICE_BUSY, "Device busy" },
//			{ 10, HBI_ERR_SENDDATA_FAILED, "SendData failed" },
//			{ 11, HBI_ERR_RECEIVE_DATA_FAILED, "Receive Data failed" },
//			{ 12, HBI_ERR_COMMAND_DISMATCH, "Command dismatch" },
//			{ 13, HBI_ERR_NO_IMAGE_RAW, "No Image raw" },
//			{ 14, HBI_ERR_PTHREAD_ACTIVE_FAILED, "Pthread active failed" },
//			{ 15, HBI_ERR_STOP_ACQUISITION, "Pthread stop data acquisition failed" },
//			{ 16, HBI_ERR_INSERT_FAILED, "insert calibrate mode failed" },
//			{ 17, HBI_ERR_GET_CFG_FAILED, "get device config failed" },
//			{ 16, HBI_NOT_SUPPORT, "not surport yet" },
//		};
//	int nCode = 8001;
//	const char *tmpString = GetErrString(CodeStringTable, sizeof(CrErrStrList)/sizeof(CodeStringTable), uValue);
//	printf("nCode=%d,tmpString=%s\n", nCode, tmpString);
//	return 0;
//}
#endif // __HB_DLL_ERROR_H_
