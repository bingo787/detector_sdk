#include "detector.h"

#include <iostream>
#include <string>
#include <cstring>

#include "include/HbiFpd.h"
#include "include/HbiType.h"
#include "include/HbiError.h"


const char STX = 0x02;
const char CR = 0x0D;
const char SP = 0x20;
const char StartTag = STX;
const char EndTag = CR;

const int MAX_KV = 300;
const int MAX_CURRENT = 900;
const int MAX_BUFFER_SIZE = 256;


#define PRINT_FUNC_NAME  do{ if(verbose){printf("%s\n",__FUNCTION__);}}while(0)

#define CHECK_IS_CONNECTED  do\
{\
if(!connected_){\
printf("Detector not connected\n");\
return rayon::ErrorCode::E_FAILED;\
}\
}while(0)



int rayon::handleEventfun(void *content,
	int nDevId,
	unsigned char byteEventId,
	void *pvParam,
	int nlength,
	int param3,
	int param4) {
	int ret = 1;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	IMAGE_DATA_ST *image_data = nullptr;
	RegCfgInfo *pRegCfg = nullptr;
	rayon::Detector *detector = (rayon::Detector *) content;

	if (detector != nullptr) {
		pRegCfg = &(detector->reg_config_);
	}
	if ((byteEventId == ECALLBACK_TYPE_ROM_UPLOAD) || (byteEventId == ECALLBACK_TYPE_RAM_UPLOAD) ||
		(byteEventId == ECALLBACK_TYPE_FACTORY_UPLOAD)) {
		if (pvParam == nullptr || nlength == 0) {
			printf("注册回调函数参数异常!\n");
			return ret;
		}
		// 防止参数冲突
		if (0 != nDevId) {
			printf("warning:%s: ,nDevId=%d,eventid=0x%02x,nParam2=%d\n", __FUNCTION__, nDevId, byteEventId, nlength);
			return ret;
		}
	}
	else if ((byteEventId == ECALLBACK_TYPE_SINGLE_IMAGE) || (byteEventId == ECALLBACK_TYPE_MULTIPLE_IMAGE) ||
		(byteEventId == ECALLBACK_TYPE_PREVIEW_IMAGE) || (byteEventId == ECALLBACK_TYPE_OFFSET_TMP) ||
		(byteEventId == ECALLBACK_OVERLAY_16BIT_IMAGE) || (byteEventId == ECALLBACK_OVERLAY_32BIT_IMAGE)) {
		if (pvParam == nullptr || nlength == 0) {
			printf("注册回调函数参数异常!\n");
			return ret;
		}
		// 防止参数冲突
		if (0 != nDevId) {
			printf("warning:%s: ,nDevId=%d,eventid=0x%02x,nParam2=%d\n", __FUNCTION__, nDevId, byteEventId, nlength);
			return ret;
		}
		//
		image_data = reinterpret_cast<IMAGE_DATA_ST *>(pvParam);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	int status = -1;
	int j = 0;
	ret = 1;
	bool b = false;

	switch (byteEventId) {
	case ECALLBACK_TYPE_FPD_STATUS: // 平板状态：连接/断开/ready/busy
	{
		printf("ECALLBACK_TYPE_FPD_STATUS,recode=%d\n", nlength);
		if (nlength <= 0 && nlength >= -11) {
			if (nlength == 0)
				printf("ECALLBACK_TYPE_FPD_STATUS,Err:网络未连接!\n");
			else if (nlength == -1)
				printf("ECALLBACK_TYPE_FPD_STATUS,Err:参数异常!\n");
			else if (nlength == -2)
				printf("ECALLBACK_TYPE_FPD_STATUS,Err:准备就绪的描述符数返回失败!\n");
			else if (nlength == -3)
				printf("ECALLBACK_TYPE_FPD_STATUS,Err:接收超时!\n");
			else if (nlength == -4)
				printf("ECALLBACK_TYPE_FPD_STATUS,Err:接收失败!\n");
			else if (nlength == -5)
				printf("ECALLBACK_TYPE_FPD_STATUS,Err:端口不可读!\n");
			else if (nlength == -6)
				printf("ECALLBACK_TYPE_FPD_STATUS,network card unusual!\n");
			else if (nlength == -7)
				printf("ECALLBACK_TYPE_FPD_STATUS,network card ok!\n");
			else if (nlength == -8)
				printf("ECALLBACK_TYPE_FPD_STATUS:update Firmware end!\n");
			else if (nlength == -9)
				printf("ECALLBACK_TYPE_FPD_STATUS:光纤已断开!!\n");
			else if (nlength == -10)
				printf("ECALLBACK_TYPE_FPD_STATUS:read ddr failed,try restarting the PCIe driver!\n");
			else /*if (nlength == -11)*/
				printf("ECALLBACK_TYPE_FPD_STATUS:ECALLBACK_TYPE_FPD_STATUS:is not jumb!\n");
			status = (int)FPD_DISCONN_STATUS;
		}
		else if (nlength == FPD_CONN_SUCCESS) { // connect
			printf("ECALLBACK_TYPE_FPD_STATUS,开始监听!\n");
			status = (int)FPD_CONN_SUCCESS;
		}
		else if (nlength == FPD_PREPARE_STATUS) { // ready
			printf("ECALLBACK_TYPE_FPD_STATUS,ready!\n");
			status = (int)FPD_PREPARE_STATUS;
		}
		else if (nlength == FPD_READY_STATUS) { // busy
			printf("ECALLBACK_TYPE_FPD_STATUS,busy!\n");
			status = (int)FPD_READY_STATUS;
		}
		else if (nlength == FPD_DOOFFSET_TEMPLATE) { // prepare
			printf("ECALLBACK_TYPE_FPD_STATUS,prepare!\n");
			status = (int)FPD_DOOFFSET_TEMPLATE;
		}
		else if (nlength == FPD_EXPOSE_STATUS) { // busy expose
			printf("ECALLBACK_TYPE_FPD_STATUS:Exposing!\n");
			status = FPD_EXPOSE_STATUS;
		}
		else if (nlength == FPD_CONTINUE_READY) { // continue ready
			printf("ECALLBACK_TYPE_FPD_STATUS:Continue ready!\n");
			status = FPD_CONTINUE_READY;
		}
		else if (nlength == FPD_DWONLOAD_GAIN) { // download gain template
			printf("ECALLBACK_TYPE_FPD_STATUS:Download gain template ack!\n");
			status = FPD_DWONLOAD_GAIN;
		}
		else if (nlength == FPD_DWONLOAD_DEFECT) { // download defect template
			printf("ECALLBACK_TYPE_FPD_STATUS:Download defect template ack!\n");
			status = FPD_DWONLOAD_DEFECT;
		}
		else if (nlength == FPD_DWONLOAD_OFFSET) { // download offset template
			printf("ECALLBACK_TYPE_FPD_STATUS:Download offset template ack!\n");
			status = FPD_DWONLOAD_OFFSET;
		}
		else if (nlength == FPD_UPDATE_FIRMARE) { // update firmware
			printf("ECALLBACK_TYPE_FPD_STATUS:Update firmware!\n");
			status = FPD_UPDATE_FIRMARE;
		}
		else if (nlength == FPD_RETRANS_MISS) { // update firmware
			printf("ECALLBACK_TYPE_FPD_STATUS:Retransmission!\n");
			status = FPD_RETRANS_MISS;
		}
		else
			printf("ECALLBACK_TYPE_FPD_STATUS,Err:Other error=%d\n", nlength);
	}
	break;
	case ECALLBACK_TYPE_SET_CFG_OK: {
		printf("ECALLBACK_TYPE_SET_CFG_OK:Reedback set rom param succuss!\n");
	}

									break;
	case ECALLBACK_TYPE_ROM_UPLOAD:/* 更新配置 */
	{
		printf("ECALLBACK_TYPE_ROM_UPLOAD:\n");

		if (pRegCfg != nullptr) {
			memset(pRegCfg, 0x00, sizeof(RegCfgInfo));
			memcpy(pRegCfg, (unsigned char *)pvParam, sizeof(RegCfgInfo));

			printf("\tSerial Number:%s\n", pRegCfg->m_SysBaseInfo.m_cSnNumber);

			// 高低位需要转换
			unsigned short usValue = ((pRegCfg->m_EtherInfo.m_sDestUDPPort & 0xff) << 8)
				| ((pRegCfg->m_EtherInfo.m_sDestUDPPort >> 8) & 0xff);
			printf("\tSourceIP:%d.%d.%d.%d:%u\n",
				pRegCfg->m_EtherInfo.m_byDestIP[0],
				pRegCfg->m_EtherInfo.m_byDestIP[1],
				pRegCfg->m_EtherInfo.m_byDestIP[2],
				pRegCfg->m_EtherInfo.m_byDestIP[3],
				usValue);

			usValue = ((pRegCfg->m_EtherInfo.m_sSourceUDPPort & 0xff) << 8)
				| ((pRegCfg->m_EtherInfo.m_sSourceUDPPort >> 8) & 0xff);
			printf("\tDestIP:%d.%d.%d.%d:%u\n",
				pRegCfg->m_EtherInfo.m_bySourceIP[0],
				pRegCfg->m_EtherInfo.m_bySourceIP[1],
				pRegCfg->m_EtherInfo.m_bySourceIP[2],
				pRegCfg->m_EtherInfo.m_bySourceIP[3],
				usValue);

			//
			if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x01)
				printf("\tPanelSize:0x%02x,fpd type:4343-140um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x02)
				printf("\tPanelSize:0x%02x,fpd type:3543-140um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x03)
				printf("\tPanelSize:0x%02x,fpd type:1613-125um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x04)
				printf("\tPanelSize:0x%02x,fpd type:3030-140um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x05)
				printf("\tPanelSize:0x%02x,fpd type:2530-85um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x06)
				printf("\tPanelSize:0x%02x,fpd type:3025-140um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x07)
				printf("\tPanelSize:0x%02x,fpd type:4343-100um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x08)
				printf("\tPanelSize:0x%02x,fpd type:2530-75um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x09)
				printf("\tPanelSize:0x%02x,fpd type:2121-200um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x0a)
				printf("\tPanelSize:0x%02x,fpd type:1412-50um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else if (pRegCfg->m_SysBaseInfo.m_byPanelSize == 0x0b)
				printf("\tPanelSize:0x%02x,fpd type:0606-50um\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);
			else
				printf("\tPanelSize:0x%02x,invalid fpd type\n", pRegCfg->m_SysBaseInfo.m_byPanelSize);

			printf("\twidth=%d,hight=%d\n",
				pRegCfg->m_SysBaseInfo.m_sImageWidth,
				pRegCfg->m_SysBaseInfo.m_sImageHeight);
			printf("\tdatatype is unsigned char.\n");
			printf("\tdatabit is 16bits.\n");
			printf("\tdata is little endian.\n");

			if (pRegCfg->m_SysBaseInfo.m_byPanelSize >= 0x01 && pRegCfg->m_SysBaseInfo.m_byPanelSize <= 0x0b) {
				/*
				* workmode
				* 01-Software Trigger;02-Clear;03-Static:Hvg Trigger Mode;04-Static:AED Trigger Mode;
				* 05-Dynamic:Hvg Sync Mode;06-Dynamic:Fpd Sync Mode;07-Dynamic:Fpd Continue;08-Static:SAECMode;
				*/
				if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x01)
					printf("\tstatic software trigger.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x03)
					printf("\tstatic hvg trigger.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x04)
					printf("\tFree AED trigger mode.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x05)
					printf("\tDynamic:Hvg Sync mode.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x06)
					printf("\tDynamic:Fpd Sync mode.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x07)
					printf("\tDynamic:Fpd Continue mode.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else if (pRegCfg->m_SysCfgInfo.m_byTriggerMode == 0x08)
					printf("\tStatic:SAEC mode.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);
				else
					printf("\tother trigger mode.[0x%02x]\n", pRegCfg->m_SysCfgInfo.m_byTriggerMode);

				printf("\tPre Acquisition Delay Time.%u\n", pRegCfg->m_SysCfgInfo.m_unPreAcquisitionDelayTime);

			}
		}
	}

	break;
	case ECALLBACK_TYPE_SINGLE_IMAGE:   // 单帧采集上图
	{
		printf("ECALLBACK_TYPE_SINGLE_IMAGE\n");
		//关掉光源
		detector->TurnOffXray();
		detector->image_data_callback_(0, *image_data);
	}break;

	case ECALLBACK_TYPE_MULTIPLE_IMAGE: // 连续采集上图
	{
		printf("ECALLBACK_TYPE_MULTIPLE_IMAGE\n");
		detector->image_data_callback_(0, *image_data);
	}

	break;
	case ECALLBACK_TYPE_GENERATE_TEMPLATE: {
		if (nlength == ECALLBACK_TEMPLATE_BEGIN) {
			printf("ECALLBACK_TEMPLATE_BEGIN\n");
		}
		else if (nlength == ECALLBACK_TEMPLATE_INVALVE_PARAM) {
			printf("ECALLBACK_TEMPLATE_INVALVE_PARAM:%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_MALLOC_FAILED) {
			printf("ECALLBACK_TEMPLATE_MALLOC_FAILED:%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_SEND_FAILED) {
			printf("ECALLBACK_TEMPLATE_SEND_FAILED:%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_STATUS_ABORMAL) {
			printf("ECALLBACK_TEMPLATE_STATUS_ABORMAL:%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_FRAME_NUM) {
			printf("ECALLBACK_TEMPLATE_FRAME_NUM:%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_TIMEOUT) {
			printf("ECALLBACK_TEMPLATE_TIMEOUT:%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_MEAN) {
			ECALLBACK_RAW_INFO *ptr = (ECALLBACK_RAW_INFO *)pvParam;
			if (ptr != NULL) {
				printf("ECALLBACK_TEMPLATE_MEAN:%s,dMean=%0.2f\n", ptr->szRawName, ptr->dMean);
			}
		}
		else if (nlength == ECALLBACK_TEMPLATE_GENERATE) {
			if (param3 == OFFSET_TMP)
				printf("ECALLBACK_TEMPLATE_GENERATE:OFFSET_TMP\n");
			else if (param3 == GAIN_TMP)
				printf("ECALLBACK_TEMPLATE_GENERATE:GAIN_TMP\n");
			else if (param3 == DEFECT_TMP)
				printf("ECALLBACK_TEMPLATE_GENERATE:DEFECT_TMP,bad point=%d\n", nlength);
			else
				printf("ECALLBACK_TEMPLATE_GENERATE:nid=%d\n", param3);
		}
		else if (nlength == ECALLBACK_TEMPLATE_RESULT) {
			printf("ECALLBACK_TEMPLATE_RESULT:%d\n", param3);
		}
		else {// other
			printf("other:len=%d,nid=%d\n", nlength, param3);
		}
	}
										   break;
	case ECALLBACK_OVERLAY_16BIT_IMAGE:break;
	case ECALLBACK_OVERLAY_32BIT_IMAGE: {
		printf("pImgPage->UpdateOverlay32BitImage failed,frame_%d,eventid=%d",
			image_data->uframeid,
			param4);
	}

										break;
	case ECALLBACK_TYPE_THREAD_EVENT: {
		if (nlength == 100)
			printf("ECALLBACK_TYPE_THREAD_EVENT,start recv data!\n");
		else if (nlength == 101)
			printf("ECALLBACK_TYPE_THREAD_EVENT,end recv data!\n");
		else if (nlength == 104)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Packet Retransmission:start recv data!\n");
		else if (nlength == 105)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Frame Retransmission:start recv data!\n");
		else if (nlength == 106)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Frame loss retransmission over,end recv data!\n");
		else if (nlength == 107)
			printf("ECALLBACK_TYPE_THREAD_EVENT,image buff is null:end recv data!\n");
		else if (nlength == 108)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Generate Offset Template:start thread!\n");
		else if (nlength == 109)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Generate Offset Template:end thread!\n");
		else if (nlength == 110)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Generate Gain Template:start thread!\n");
		else if (nlength == 111)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Generate Gain Template:end thread!\n");
		else if (nlength == 112)
			printf("ECALLBACK_TYPE_THREAD_EVENT,offset calibrate:success!\n");
		else if (nlength == 113)
			printf("ECALLBACK_TYPE_THREAD_EVENT,offset calibrate:failed!\n");
		else if (nlength == 114)
			printf("ECALLBACK_TYPE_THREAD_EVENT,gain calibrate:success!\n");
		else if (nlength == 115)
			printf("ECALLBACK_TYPE_THREAD_EVENT,gain calibrate:failed!\n");
		else if (nlength == 116)
			printf("ECALLBACK_TYPE_THREAD_EVENT,defect calibrate:success!\n");
		else if (nlength == 117)
			printf("ECALLBACK_TYPE_THREAD_EVENT,defect calibrate:failed!\n");
		else if (nlength == 118)
			printf("ECALLBACK_TYPE_THREAD_EVENT,InitGainTemplate:failed!\n");
		else if (nlength == 119)
			printf("ECALLBACK_TYPE_THREAD_EVENT,firmare offset calibrate:success!\n");
		else if (nlength == 120)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Generate Defect Template:start thread!\n");
		else if (nlength == 121)
			printf("ECALLBACK_TYPE_THREAD_EVENT,Generate Defect Template:end thread!\n");
		else
			printf("ECALLBACK_TYPE_THREAD_EVENT,Err:未知错误[%d]\n", nlength);
	}
									  break;
	case ECALLBACK_TYPE_FILE_NOTEXIST: {
		if (pvParam != nullptr)
			printf("err:%s not exist!\n", (char *)pvParam);
	}

									   break;
	default: {
		printf("ECALLBACK_TYPE_INVALVE,command=%02x\n", byteEventId);
	}
			 break;
	}

	return ret;
}


void rayon::Detector::CheckWatchDog() {
	PRINT_FUNC_NAME;
	static int tag = 1;
	//检查是否需要喂狗
	if (!need_feeding_dog_)
	{
		need_feeding_dog_ = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(350));
		// 接收串口数据, 暂时不做解析处理
		char buff[MAX_BUFFER_SIZE] = { 0 };
		memset(buff, 0, MAX_BUFFER_SIZE);
		auto count = serial_port_.receive(buff, MAX_BUFFER_SIZE);
		std::string message(buff, count);
		if (verbose) {
			printf("serial port recieve :%s", message.c_str());
		}
		return;
	}

	//获取高压状态
	GetHVStatus();

	tag++;
	tag = tag % 2;

	if (tag == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		SendCommand("MON");
	}
	else if (tag == 1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		SendCommand("FLT");
	}



}


int rayon::Detector::Connect(ImageDataCallback callback, const std::string & port)
{
	PRINT_FUNC_NAME;
	if (callback == nullptr) {
		return ErrorCode::E_INVALID_PARAMS;
	}

	// 探测器平板句柄初始化
	handle_ = HBI_Init();
	if (handle_ == nullptr) {
		return ErrorCode::E_FPD_ERROR;
	}

	// 注册回调函数
	image_data_callback_ = callback;
	auto ret = HBI_RegEventCallBackFun(handle_, handleEventfun, this);
	if (ret != 0) {
		printf("HBI_RegEventCallBackFun return error %d\n", ret);
		return ErrorCode::E_FPD_ERROR;
	}

	// 连接平板探测器
	int do_pre_offset = 0;
	std::string local_ip = "192.168.10.20";
	std::string detector_ip = "192.168.10.40";
	ret = HBI_ConnectDetectorJumbo(handle_,
		const_cast<char*>(detector_ip.c_str()), 0x8081,
		const_cast<char*>(local_ip.c_str()), 0x8080, do_pre_offset);
	if (ret != 0) {
		printf("HBI_ConnectDetectorJumbo return error %d\n", ret);
		return ErrorCode::E_FPD_ERROR;
	}

	// 打开串口
	auto ret2 = serial_port_.open(port.c_str(), 9600, 0, 8, 1, 0);
	if (!ret2) {
		printf("Open serial port %s, failed, please check port name(COM1 or COM2 ??)\n",port.c_str());
		
		HBI_DisConnectDetector(handle_);
		HBI_Destroy(handle_);

		return ErrorCode::E_SERIAL_PORT_ERROR;
	}

	// 初始化串口光源控制
	SendCommand("FREV");
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	SendCommand("MON");

	connected_ = true;

	// 启动后台线程接收串口消息，以及检查看门狗
	receive_serial_msg_task_ = std::thread([this]() {
		while (IsConnected())
		{
			CheckWatchDog();
		}
	});


	return 0;
}
void rayon::Detector::Disconnect()
{
	PRINT_FUNC_NAME;
	HBI_Destroy(handle_);
	TurnOffXray();

	connected_ = false;
	receive_serial_msg_task_.join();
	serial_port_.close();
}

int rayon::Detector::ApplyConfig(const DetectorConfig & config)
{
	PRINT_FUNC_NAME;
	IMAGE_CORRECT_ENABLE correct;
	correct.ucDefectCorrection = 1;
	correct.ucGainCorrection = 1;
	correct.ucOffsetCorrection = 1;
	correct.bFeedbackCfg = true;
	int trigger = 7;
	if (config.work_mode == WorkMode::E_STATIC) {
		trigger = 1;
	}

	int ret = HBI_TriggerAndCorrectApplay(handle_, trigger, &correct);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	return ret != 0 ? ErrorCode::E_FAILED : ErrorCode::E_SUCCESS;
}


int rayon::Detector::SingleAcquisition(int expose_time) {

	PRINT_FUNC_NAME;
	CHECK_IS_CONNECTED;
	int ret = -1;
	TurnOnXray();
	if (expose_time > 0) {
		HBI_SetSinglePrepareTime(handle_, expose_time);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		ret = HBI_SinglePrepare(handle_);
	}
	else {
		FPD_AQC_MODE st_mode;
		st_mode.eAqccmd = SINGLE_ACQ_DEFAULT_TYPE;
		st_mode.eLivetype = ONLY_IMAGE;     // 1-固件做offset模板并上图；2-只上图；3-固件做只做offset模板。
		st_mode.ndiscard = 0;     // 这里默认位0，不抛弃前几帧图像
		st_mode.nframeid = 0;     // 这里默认位0
		ret = HBI_SingleAcquisition(handle_, st_mode);
	}
	return ret != 0 ? ErrorCode::E_FAILED : ErrorCode::E_SUCCESS;
}
int rayon::Detector::StartLiveAcquisition(int expose_time) {
	PRINT_FUNC_NAME;
	CHECK_IS_CONNECTED;
	if (expose_time < 1000) {
		expose_time = 1000;
	}
	auto ret = HBI_SetSelfDumpingTime(handle_, expose_time);
	if (ret != 0) {
		return ErrorCode::E_FPD_ERROR;
	}

	TurnOnXray();

	FPD_AQC_MODE st_mode;
	st_mode.eAqccmd = LIVE_ACQ_DEFAULT_TYPE;
	st_mode.eLivetype = ONLY_IMAGE;     // 1-固件做offset模板并上图；2-只上图；3-固件做只做offset模板。
	st_mode.ndiscard = 0;     // 这里默认位0，不抛弃前几帧图像
	st_mode.nframeid = 0;     // 这里默认位0
	st_mode.ngroupno = 0;
	ret = HBI_LiveAcquisition(handle_, st_mode);
	return ret != 0 ? ErrorCode::E_FAILED : ErrorCode::E_SUCCESS;
}
int rayon::Detector::StopLiveAcquisition() {
	PRINT_FUNC_NAME;
	CHECK_IS_CONNECTED;
	auto ret = HBI_StopAcquisition(handle_);
	TurnOffXray();
	return ret != 0 ? ErrorCode::E_FAILED : ErrorCode::E_SUCCESS;
}
int rayon::Detector::SetKVoltageAndCurrent(double kv, int current)
{
	PRINT_FUNC_NAME;
	CHECK_IS_CONNECTED;
	SetKVoltage(kv);
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	SetCurrent(current);
	return 0;
}
int rayon::Detector::SetKVoltage(double kv) {
	PRINT_FUNC_NAME;
	if (kv > MAX_KV) {
		return ErrorCode::E_INVALID_PARAMS;
	}

	std::string message;
	message.append("VP");
	auto value_str = std::to_string((int)(kv * 10));
	auto value_str_len = value_str.size();
	value_str.insert(0, 4 - value_str_len, '0');
	message.append(value_str);
	SendCommand(message);

	return 0;
}
int rayon::Detector::SetCurrent(int current) {
	PRINT_FUNC_NAME;
	if (current > MAX_CURRENT) {
		return ErrorCode::E_INVALID_PARAMS;
	}
	std::string message;
	message.append("CP");
	auto value_str = std::to_string(current);
	auto value_str_len = value_str.size();
	value_str.insert(0, 4 - value_str_len, '0');
	message.append(value_str);
	return SendCommand(message);

}
void rayon::Detector::GetHVStatus()
{
	PRINT_FUNC_NAME;
	SendCommand("STAT");
}
int rayon::Detector::TurnOnXray() {
	PRINT_FUNC_NAME;
	return SendCommand("ENBL1");
}
int rayon::Detector::TurnOffXray() {
	PRINT_FUNC_NAME;
	return SendCommand("ENBL0");
}
int rayon::Detector::SendCommand(const std::string &cmd) {

	std::string message;
	message.push_back(StartTag);
	message.append(cmd);
	message.push_back(EndTag);
	if (verbose)
	{
		printf("send command %s\n", message.c_str());
	}

	auto ret = serial_port_.send(message.data(), message.size());
	
	return 0;
}

