/*---------------------------------------------------------------------------
* Copyright (c) 2019 上海昊博影像科技有限公司
* All rights reserved.
*
* 文件名称: HbiType.h
* 文件标识:
* 摘    要: 平板探测器数据结构头文件
*
* 当前版本: 3.0
* 作    者: mhyang
* 完成日期: 2020/11/20
----------------------------------------------------------------------------*/
#ifndef __HBI_TYPE_H_
#define __HBI_TYPE_H_

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef NULL
#define NULL 0
#endif

// 平板可支持的最大个数,最大小于4
#define DETECTOR_MAX_NUMBER 2

// 平板状态
#define FPD_DISCONN_STATUS             0   // fpd disconnect status
#define FPD_PREPARE_STATUS             1   // fpd prepare status                               ////#define FPD_STATUS_BUSY             0X01  // fpd busy status
#define FPD_READY_STATUS               2   // fpd ready status                                 ////#define FPD_STATUS_READY            0X02  // fpd ready status
#define FPD_DOOFFSET_TEMPLATE          3   // firmware do offset template                      ////#define FPD_STATUS_AED              0X03  // AED mode,avild image data
#define FPD_EXPOSE_STATUS              4   // fpd busy/expose status                           ////#define FPD_STATUS_PREPARE          0X04  // Software mode,prepare command feedback command
#define FPD_CONTINUE_READY             5   // continue ready
#define FPD_DWONLOAD_GAIN              6   // download gain template success ack respond       ////#define FPD_UPLOAD_GAIN_ANSWER      0X06  // Upload gain template answer  
#define FPD_DWONLOAD_DEFECT            7   // download defect template success ack respond     ////#define FPD_UPLOAD_DEFECT_ANSWER    0X07  // Upload defect template answer
#define FPD_DWONLOAD_OFFSET            8   // download offset template success ack respond
#define FPD_UPDATE_FIRMARE             9   // update firmware
#define FPD_RETRANS_MISS               10  // Retransmission
#define FPD_STATUS_AED                 11  // AED mode,avild image data
#define FPD_STATUS_SLEEP               12  // Energy saving status
#define FPD_STATUS_WAKEUP              13  // Wake up
#define FPD_DOWNLOAD_NO_IMAGE          14  // Retransmission
#define FPD_DOWNLOAD_TAIL_IMAGE        15  // AED mode,avild image data
#define FPD_EMMC_MAX_NUMBER            16  // emmc save image:Maximum number of stored images
#define FPD_ENDTIME_WARNNING           17  // AED mode,avild image data
#define FPD_WLAN_BATTERY_STATUS        18  // WLAN Battery Status Message
#define FPD_CONN_SUCCESS               100 // fpd connect status

// data length
#define FPD_DATA_BITS                  16
#define PACKET_MAX_SIZE                1049
#define PCIE_PACKET_MAX_SIZE           1052
#define JUMBO_PACKET_MAX_SIZE          8218
#define IMG_PACKET_DATA_MAX_LEN        1024
#define JUMBO_IMG_PACKET_DATA_MAX_LEN  8192
#define CUSTOMEFFECTRECVDATASIZE       1034
#define LIVE_ACQ_MAX_FRAME_NUM         20
#define FLOAT_PACKET_DATA_MAX_LEN      2048
#define UNINT_PACKET_DATA_MAX_LEN      2048
#define USHORT_PACKET_DATA_MAX_LEN     4096
#define USHORT_PACKET_DATA_WIRELESS    512
#define FLOAT_PACKET_DATA_WIRELESS     256
#define PREVIEW_SPACE_NUMBER           4
#define QUEUE_MAX_SIZE                 8
#define MIN_VALUE                      1e-6
#define ISDOUBLE_ZERO(d) (std::abs(d) < MIN_VALUE)

// 自定义无线网卡类型
#ifndef MIB_IF_TYPE_ETHERNET_WIRELESS
#define MIB_IF_TYPE_ETHERNET_WIRELESS 71
#endif

#ifndef MAX_IP_LEN
#define MAX_IP_LEN 16
#endif

// Notice:PCIe Register Address
// Base Addr
#define PCIE_BAR_BASE_ADDR       0x30000
// BAR Addr
#define BAR_FIRWARE_VERSION_ADDR 0x0
#define BAR_FIRWARE_YEAR_ADDR    0x1
#define BAR_FIRWARE_MONTH_ADDR   0x2
#define BAR_FIRWARE_DAY_ADDR     0x3
#define BAR_EVENT_ADDR           0x4
#define BAR_IMAGE_WIDTH_ADDR     0x5
#define BAR_IMAGE_HEIGHT_ADDR    0x6
#define BAR_WRITE_ADDR           0x1000
#define BAR_READ_ADDR            0x2000
// DDR Addr
#define DDR_BASE_STEP            0x2000000
#define DDR_ROM0_ADDR            0x0

#if 0 //kangmuzhineng
#define DDR_ROM1_ADDR            0x2000000
#define DDR_ROM2_ADDR            0x4000000
#else // modified by mhyang 202010519 固件有改动
#define DDR_ROM1_ADDR            0x4000000
#define DDR_ROM2_ADDR            0x8000000
#endif

// defect坏点默认阈值
#define BADPOINT_MAX_THRESHOLD   10000

typedef enum
{
	PCIE_WR_BAR = 0,
	PCIE_WR_DDR
}ePCIE_WR_TYPE;

struct FpdPixelMatrixTable
{
	unsigned int fpd_num;
	unsigned int fpd_width;
	unsigned int fpd_height;
	unsigned int fpd_packet_size;
	unsigned int fpd_jumbo_size;
	unsigned int fpd_pitch;
};

// Notice:Fpd Pixel Matrix Table,size is 20.
// jumbo packet 8192kb,and normal 1024kb
static const FpdPixelMatrixTable HB_FPD_SIZE[] = {	
	{ 1, 3072, 3072, 18432, 2304, 140 },/*,"4343-140um" */
	{ 2, 2560, 3072, 15360, 1920, 140 },/*,"3543-140um" */
	{ 3, 1248, 1024, 2496,  312,  125 },/*,"1613-125um" */
	{ 4, 2048, 2048, 8192,  1024, 140 },/*,"3030-140um" */
	{ 5, 2816, 3584, 19712, 2464, 85  },/*,"2530-85um" */
	{ 6, 2048, 1792, 7168,  896 , 140 },/*,"3025-140um" */
	{ 7, 4288, 4288, 35912, 4489, 100 },/*,"4343-100um" */
	{ 8, 3072, 3840, 23040, 2880, 75  },/*,"2530-75um"*/
	{ 9, 1024, 1024, 2048,  256,  200 },/*,"2121-200um"*/
	{10, 2784, 2400, 13050, 1632, 50  },/*,"1412-50um 1631+25"*/
	{11, 1056, 1200, 2475,  310,  50  } /*,"0606-50um 309+375"*/
};
////struct FpdPixelTable
////{
////	unsigned int fpd_num;
////	unsigned int fpd_width;
////	unsigned int fpd_height;
////	unsigned int fpd_pitch;
////};
////static const FpdPixelTable HB_FPD_SIZE[] = {
////	{ 1, 3072, 3072, 140 },/*,"4343-140um" */
////	{ 2, 2560, 3072, 140 },/*,"3543-140um" */
////	{ 3, 1248, 1024, 125 },/*,"1613-125um" */
////	{ 4, 2048, 2048, 140 },/*,"3030-140um" */
////	{ 5, 2816, 3584, 85  },/*,"2530-85um" */
////	{ 6, 2048, 1792, 140 },/*,"3025-140um" */
////	{ 7, 4288, 4288, 100 },/*,"4343-100um" */
////	{ 8, 3072, 3840, 75  },/*,"2530-75um"*/
////	{ 9, 1024, 1024, 200 },/*,"2121-200um"*/
////	{10, 2784, 2400, 50  },/*,"1412-50um 1631+25"*/
////	{11, 1056, 1200, 50  } /*,"0606-50um 309+375"*/
////};
// Notice:
typedef struct HBI_HANDLE_ST 
{
	HBI_HANDLE_ST()
	{
		_handle = NULL;
		_nfpdid = 0;
	}
	void *_handle;              // 设备对应句柄
	int  _nfpdid;               // 设备ID
}HBI_HANDLE;

//Note:fpd communication Type
typedef enum
{
	UDP_COMM_TYPE = 0,
	UDP_JUMBO_COMM_TYPE,
	PCIE_COMM_TYPE,
	WALN_COMM_TYPE
}FPD_COMM_TYPE;

//Note:sofeware work mode invalid
typedef enum
{
	WORKMODE_PRODUCTION_MODE = 0x00, // 软件生产模式
	WORKMODE_DEBUG_MODE = 0x01,      // 软件调试模式
	WORKMODE_UNKNOWN
}eSOFTWARE_WORKMODE;

typedef enum
{
	IMAGE_FILE    = 0,
	TEMPLATE_FILE = 1,
	TEMPLATE_IMG  = 2
}HBI_FILE_TYPE;

typedef struct CommCfgSt
{
	CommCfgSt()
	{
		_type = FPD_COMM_TYPE::PCIE_COMM_TYPE;
		_remoteip[0] = '\0';
		_localip[0]  = '\0';
		_loacalPort = 32986;
		_remotePort = 32987;
	}

	FPD_COMM_TYPE _type;
	// 网口通讯需要设置,PCIe只要设置类型即可
	char _remoteip[MAX_IP_LEN];
	char _localip[MAX_IP_LEN];
	unsigned short _loacalPort;
	unsigned short _remotePort;
}COMM_CFG;

//
typedef struct HbiDllInstanceSt
{
	HbiDllInstanceSt()
	{
		m_fpdId   = 0;
		m_fpdHand = NULL;
		m_commCfg._type        = FPD_COMM_TYPE::PCIE_COMM_TYPE;
		m_commCfg._remoteip[0] = '\0';
		m_commCfg._localip[0]  = '\0';
		m_commCfg._loacalPort  = 32986;
		m_commCfg._remotePort  = 32987;
		m_bConnected = false;
	}
	//
	unsigned int m_fpdId;  // 平板id
	void *m_fpdHand;       // 平板实例句柄
	COMM_CFG m_commCfg;    // 平板通讯方式
	bool m_bConnected;     // 平板连接状态
}HBI_DLL_INSTANCE;

// Notice: Image Property
typedef struct ImageProperty
{
	ImageProperty()
	{
		nFpdNum      = 0;
		nwidth       = 0;
		nheight      = 0;
		datatype     = 0;
		ndatabit     = 0;
		nendian      = 0;
		packet_size  = 0;
		frame_size   = 0;
		tailPacketSize = 0;
		frame_number = 2;
	}
	unsigned int nFpdNum;				//fpd Number
	unsigned int nwidth;			    //image width
	unsigned int nheight;			    //image height
	unsigned int datatype;			    //data type：0-unsigned char,1-char,2-unsigned short,3-float,4-double
	unsigned int ndatabit;			    //data bit:0-16bit,1-14bit,2-12bit,3-8bit
	unsigned int nendian;			    //endian:0-little endian,1-biger endian
	unsigned int packet_size;           //fpd send the number of packet per frame
	unsigned int frame_size;            //data size per frame
	unsigned int tailPacketSize;        //Tail packet size
	unsigned int frame_number;          //The number of buffer capacity,Integer,[2~32],buff_szie=frame_size * ncapacity
	// preview
	unsigned int npreviewwidth;			//preview image width
	unsigned int npreviewheight;		//preview image height
}IMAGE_PROPERTY;

// Notice:Fpd Trigger Work Mode
typedef enum
{
	INVALID_TRIGGER_MODE         = 0x00,// 无效模式
	STATIC_SOFTWARE_TRIGGER_MODE = 0x01,// 静态采集-软触发模式
	STATIC_PREP_TRIGGER_MODE     = 0x02,// 静态采集-软触发模式
	STATIC_HVG_TRIGGER_MODE      = 0x03,// 静态采集-高压触发模式
	STATIC_AED_TRIGGER_MODE      = 0x04,// 静态采集-FreeAED触发模式
	DYNAMIC_HVG_TRIGGER_MODE     = 0x05,// 动态采集-高压同步模式
	DYNAMIC_FPD_TRIGGER_MODE     = 0x06,// 动态采集-FPD同步模式
	DYNAMIC_FPD_CONTINUE_MODE    = 0x07,// 动态采集-FPD Conitnue模式
	DYNAMIC_FPD_SAEC_MODE        = 0x08 // 08-Static:SAECMode;
}EnumTRIGGER_MODE;

// Notice:fpd software calibrate enable info.
typedef struct image_correct_enable_st
{
	image_correct_enable_st()
	{
		bFeedbackCfg = false;
		ucOffsetCorrection = 0;
		ucGainCorrection = 0;
		ucDefectCorrection = 0;
		ucDummyCorrection = 0;
	};
	bool bFeedbackCfg;                  //true-ECALLBACK_TYPE_ROM_UPLOAD Event,false-ECALLBACK_TYPE_SET_CFG_OK Event
	unsigned char ucOffsetCorrection;   //0-No Offset Correction;1-Software PreOffset Correction;2-Firmware PostOffset Correction;3-Firmware PreOffset Correction;
	unsigned char ucGainCorrection;	    //0-No Gain Correction;1-Software Gain Correction;2-Firmware Gain Correction;
	unsigned char ucDefectCorrection;   //0-No Defect Correction;1-Software Defect Correction;2-Firmware Defect Correction;
	unsigned char ucDummyCorrection;    //0-No Dummy Correction;1-Software Dummy Correction;2-Firmware Dummy Correction;
}IMAGE_CORRECT_ENABLE;

// Notice:fpd software calibrate enable info.
typedef struct software_calibrate_enable_st
{
	software_calibrate_enable_st()
	{
		enableOffsetCalib = false;
		enableGainCalib   = false;
		enableDefectCalib = false;
		enableDummyCalib  = false;
	};
	bool enableOffsetCalib;
	bool enableGainCalib;
	bool enableDefectCalib;
	bool enableDummyCalib;
}SOFTWARE_CALIBRATE_ENABLE;

// Notice: Live Acquisition'properties 
typedef enum
{
	PREOFFSET_IMAGE   = 0x01,       // preoffset template and image
	ONLY_IMAGE        = 0x02,       // only image
	ONLY_PREOFFSET    = 0x03,       // only preoffset template
	OVERLAY_16BIT_IMG = 0x04,       // overlap result is 16bit'image
	OVERLAY_32BIT_IMG = 0x05        // overlap result is 32bit'image
}EnumLIVE_ACQUISITION;

// Notice: acq command:static and dynamic
typedef enum
{
	SINGLE_ACQ_DEFAULT_TYPE = 0x00, // 默认单帧采集
	LIVE_ACQ_DEFAULT_TYPE,          // 默认连续采集
	// 分布生成矫正模板，用于验证模板
	LIVE_ACQ_OFFSET_IMAGE,          // 创建Offset模板-连续采集暗场图
	SINGLE_ACQ_GAIN_IMAGE,          // 创建Gain模板-单帧采集亮场图	
	LIVE_ACQ_GAIN_IMAGE,            // 创建Gain模板-连续采集亮场图
	SINGLE_ACQ_DEFECT_IMAGE,        // 创建Defect模板-单帧采集亮场图
	LIVE_ACQ_DEFECT_IMAGE,          // 创建Defect模板-连续采集亮场图
	// 快速生成矫正模板，用于系统集成
	OFFSET_TEMPLATE_TYPE,           // 快速生成模板采集类型,连续采集一组暗场图并生成offset模板，固件生成模板
	GAIN_TEMPLATE_TYPE,             // 快速生成模板采集类型,连续采集一组亮场图并生成gain模板
	DEFECT_TEMPLATE_GROUP1,         // 快速生成模板采集类型,连续采集一组亮场图 - defect group1
	DEFECT_TEMPLATE_GROUP2,         // 快速生成模板采集类型,连续采集一组亮场图 - defect group2
	DEFECT_TEMPLATE_GROUP3,         // 快速生成模板采集类型,连续采集一组亮场图 - defect group3 and generate template
	SOFTWARE_OFFSET_TEMPLATE        // 快速生成模板采集类型,连续采集一组暗场图 - SDK生成offset模板
}EnumIMAGE_ACQ_CMD;

// Notice:fpd aqc mode
typedef struct fpd_aqc_mode_st
{
	fpd_aqc_mode_st()
	{
		eAqccmd    = SINGLE_ACQ_DEFAULT_TYPE;// default single shot type
		eLivetype  = ONLY_IMAGE;             // only image
		ngroupno   = 0;
		nAcqnumber = 0;
		ndiscard   = 0;
		nframeid   = 0;
	};
	EnumIMAGE_ACQ_CMD eAqccmd;      // 采集命令
	EnumLIVE_ACQUISITION eLivetype; // 只限于连续采集(LIVE_ACQ_DEFAULT_TYPE)详细任务, 1-固件做offset模板并上图；2-只上图；3-固件做只做offset模板。
	int  ngroupno;                  // 组号
	int  nAcqnumber;                // 实际采集帧数
	int  ndiscard;                  // 忽略的帧数
	int  nframeid;                  // 计数器
}FPD_AQC_MODE;

// Notice: upload template file
// template file type
typedef enum 
{
	OFFSET_TMP = 0x00,
	GAIN_TMP   = 0x01,
	DEFECT_TMP = 0x02
}emUPLOAD_FILE_TYPE;

// template file attributes
typedef struct hbi_file_attr_st
{
	hbi_file_attr_st()
	{
		emfiletype   = GAIN_TMP;
		nBinningtype = -1;
		filepath[0]  = '\0';
	};
	emUPLOAD_FILE_TYPE emfiletype;
	int nBinningtype;
	char filepath[MAX_PATH];
}DOWNLOAD_FILE;

// template file linked list
typedef struct download_mode_st
{
	download_mode_st()
	{
		pFileAttr = NULL;
		next = NULL;
	}
	DOWNLOAD_FILE *pFileAttr;
	struct download_mode_st* next;
}DOWNLOAD_MODE;
// upload process status
typedef enum {
	UPLOAD_FILE_START = 0x00,
	UPLOAD_FILE_DURING = 0x01,
	UPLOAD_FILE_STOP
}emUPLOAD_FILE_STATUS;

// Notice: After Each Member Variables, show Variables enum , 
// before '-' is variables' value, after '-' is the meaning of the value;
// each value departed by ';' symbol
enum eRequestCommType
{
	EDL_COMMON_TYPE_INVALVE               = 0x00,
	EDL_COMMON_TYPE_GLOBAL_RESET          = 0x01,
	EDL_COMMON_TYPE_PREPARE               = 0x02,
	EDL_COMMON_TYPE_SINGLE_SHORT          = 0x03,
	EDL_COMMON_TYPE_LIVE_ACQ              = 0x04,
	EDL_COMMON_TYPE_STOP_ACQ              = 0x05,
	EDL_COMMON_TYPE_PACKET_MISS           = 0x06,
	EDL_COMMON_TYPE_FRAME_MISS            = 0x07,
	EDL_COMMON_TYPE_DUMMPING              = 0x08,
	EDL_COMMON_TYPE_FPD_STATUS            = 0x09,
	EDL_COMMON_TYPE_END_RESPONSE          = 0x0A, // End response packet
	EDL_COMMON_TYPE_CONNECT_FPD           = 0x0B, // connect fpd
	EDL_COMMON_TYPE_DOWNLOAD_IMAGE        = 0x0C, // wireless download image
	EDL_COMMON_TYPE_SLEEP_STATE           = 0x0D, // wireless set sleep state
	EDL_COMMON_TYPE_WAKE_UP               = 0x0E, // wireless wake up
	EDL_COMMON_TYPE_DISCONNECT_FPD        = 0x0F, // disconnect fpd
	EDL_COMMON_TYPE_SET_RAM_PARAM_CFG     = 0x10,
	EDL_COMMON_TYPE_GET_RAM_PARAM_CFG     = 0x11,
	EDL_COMMON_TYPE_SET_ROM_PARAM_CFG     = 0x12,
	EDL_COMMON_TYPE_GET_ROM_PARAM_CFG     = 0x13,
	EDL_COMMON_TYPE_SET_FACTORY_PARAM_CFG = 0x14,
	EDL_COMMON_TYPE_GET_FACTORY_PARAM_CFG = 0x15,
	EDL_COMMON_TYPE_RESET_FIRM_PARAM_CFG  = 0x16,
	EDL_COMMON_UPLOAD_OFFSET_TEMPLATE     = 0x2E, //add by MH.YANG 30/12
	EDL_COMMON_UPLOAD_GAIN_TEMPLATE       = 0x2F,// Upload gain template
	EDL_COMMON_UPLOAD_DEFECT_TEMPLATE     = 0x30,// Upload defect template
	EDL_COMMON_DEFECT_AUTHOR              = 0x31,//
	EDL_COMMON_ERASE_FIRMWARE             = 0x4F,// Erase old firmware package request
	EDL_COMMON_UPDATE_FIRMWARE            = 0x50,// Update new firmware package request
	EDL_COMMON_UPDATE_EMBEDDED_INIT       = 0xFC,// Update embedded software
	EDL_COMMON_UPDATE_EMBEDDED_SOFTWARE   = 0xFD,// Update embedded software
	EDL_COMMON_TYPE_SWITCH_WALN_MODE      = 0xFE,// Switch wlan ap/client Mode and 2.4G/5G net Type
	EDL_COMMON_TYPE_SET_AQC_MODE          = 0xFF
};

// Notice: After Each Member Variables, show Variables enum , 
// before '-' is variables' value, after '-' is the meaning of the value;
// each value departed by ';' symbol
enum eCallbackEventCommType
{
	ECALLBACK_TYPE_INVALVE             = 0X00,
	ECALLBACK_TYPE_COMM_RIGHT          = 0X01,
	ECALLBACK_TYPE_COMM_WRONG          = 0X02,
	ECALLBACK_TYPE_DUMMPLING           = 0X03,
	ECALLBACK_TYPE_ACQ_END             = 0X04,
	ECALLBACK_TYPE_UPDATE_FIRMWARE     = 0X06, // Update old firmware package answer 
	ECALLBACK_TYPE_ERASE_FIRMWARE      = 0X07, // Update new firmware package answer
	ECALLBACK_TYPE_FPD_STATUS          = 0X09, // Status package
	ECALLBACK_TYPE_ROM_UPLOAD          = 0X10,
	ECALLBACK_TYPE_RAM_UPLOAD          = 0X11,
	ECALLBACK_TYPE_FACTORY_UPLOAD      = 0X12,
	ECALLBACK_TYPE_WLAN_BATTERY        = 0X13,
	ECALLBACK_TYPE_SINGLE_IMAGE        = 0X51,
	ECALLBACK_TYPE_MULTIPLE_IMAGE      = 0X52,
	ECALLBACK_TYPE_PREVIEW_IMAGE       = 0X53,
	ECALLBACK_TYPE_PACKET_MISS         = 0X5B,
	ECALLBACK_TYPE_OFFSET_TMP          = 0X5C,
	ECALLBACK_OVERLAY_NUMBER           = 0X5D,
	ECALLBACK_OVERLAY_16BIT_IMAGE      = 0X5E,
	ECALLBACK_OVERLAY_32BIT_IMAGE      = 0X5F,
	ECALLBACK_TYPE_SENDTO_WIZARD       = 0XA0,
	ECALLBACK_TYPE_PACKET_MISS_MSG     = 0XA4,
	ECALLBACK_TYPE_THREAD_EVENT        = 0XA5,
	ECALLBACK_TYPE_ACQ_DISCARDDED      = 0XA6,
	ECALLBACK_TYPE_OFFSET_ERR_MSG      = 0XA7,
	ECALLBACK_TYPE_GAIN_ERR_MSG        = 0XA8,
	ECALLBACK_TYPE_DEFECT_ERR_MSG      = 0XA9,
	ECALLBACK_TYPE_NET_ERR_MSG         = 0XAA,
	ECALLBACK_TYPE_SET_CFG_OK          = 0XAB, // 设置参数成功
	ECALLBACK_TYPE_SAVE_SUCCESS        = 0XAC, // 保存图像成功
	ECALLBACK_TYPE_GENERATE_TEMPLATE   = 0XAD, // 生成模板
	ECALLBACK_TYPE_FILE_NOTEXIST       = 0XAE, // 文件不存在
	ECALLBACK_TYPE_WORK_STATUS         = 0XAF  // 工作状态(生产模式或测试模式)
};

enum eCallbackUpdateFirmwareStatus
{
	ECALLBACK_UPDATE_STATUS_START     = 0XB0, // Start status or Erase Firmaware
	ECALLBACK_UPDATE_STATUS_PROGRESS  = 0XB1, // progress
	ECALLBACK_UPDATE_STATUS_RESULT    = 0XB2  // the Processing Result
};

enum eCallbackTemplateStatus
{
	ECALLBACK_TEMPLATE_BEGIN          = 0X00,
	ECALLBACK_TEMPLATE_INVALVE_PARAM  = 0X01,
	ECALLBACK_TEMPLATE_MALLOC_FAILED  = 0X02,
	ECALLBACK_TEMPLATE_SEND_FAILED    = 0X03,
	ECALLBACK_TEMPLATE_STATUS_ABORMAL = 0X04,
	ECALLBACK_TEMPLATE_FRAME_NUM      = 0X05,
	ECALLBACK_TEMPLATE_TIMEOUT        = 0X06,
	ECALLBACK_TEMPLATE_MEAN           = 0X07,
	ECALLBACK_TEMPLATE_GENERATE       = 0X08,
	ECALLBACK_TEMPLATE_RESULT         = 0X09
};

// Notice:Image data type
typedef enum eHbiDataType
{
	EHBI_8UC1  = 0X01, // 1 - 8bits
	EHBI_16UC1 = 0X02, // 2 - 16bits
	EHBI_32FC1 = 0X04  // 4 - 32bits
}emHBI_DATA_TYPE;

// Notice:Image data object
// image buff size(8bits)  = uwidth * uheight;
// image buff size(16bits) = uwidth * uheight * 2;
// image buff size(32bits) = uwidth * uheight * 4;
typedef struct IMAGE_DATA_ST
{
	IMAGE_DATA_ST()
	{
		uwidth    = 3072;
		uheight   = 3072;
		ndatabits = emHBI_DATA_TYPE::EHBI_16UC1;
		uframeid  = 0;
		databuff  = NULL;
		datalen   = 0;
	}
	unsigned int uwidth;	   // image width
	unsigned int uheight;	   // image height
	emHBI_DATA_TYPE ndatabits; // data bit:1-8bit,2-16bit,4-32bit,其他默认-16bit
	unsigned int uframeid;     // frame id
	void * databuff;           // buffer address
	unsigned int datalen;      // buffer size
}ImageData;

// Notice: call back function
// @USER_CALLBACK_HANDLE_ENVENT
// @byteEventid:enum eEventCallbackCommType
// @ufpdId:平板设备ID
// @PVEventParam1:fpd config or image data buffer addr
// @nEventParam2:参数2，例如data size或状态
// @nEventParam3:参数3，例如帧率 frame rate或状态等
// @nEventParam4:参数4，例如pcie事件id或预留扩展
typedef int(*USER_CALLBACK_HANDLE_ENVENT)(void *pContext, int ufpdId, unsigned char byteEventId, void *PVEventParam1, int nEventParam2, int nEventParam3, int nEventParam4);
////typedef int(*USER_CALLBACK_HANDLE_ENVENT)(void *pContext, unsigned char byteEventid, void *buff, int len, int nframeid, int neventid, int nfps);

// Notice: call back function
// @USER_CALLBACK_HANDLE_PROCESS
// @cmd:enum eAnswerCallbackCommType
// @buff
// @len
typedef int(*USER_CALLBACK_HANDLE_PROCESS)(unsigned char cmd, int retcode, void *inContext);

// Notice: calibrate template raw file call back info
typedef struct callback_raw_info_st
{
	callback_raw_info_st()
	{
		szRawName[0] = '\0';
		dMean = 0.0;
	};
	char   szRawName[MAX_PATH];	// 返回数据文件名称
	double dMean;               // 灰度均值
}ECALLBACK_RAW_INFO;

// Notice:generate calibrate template input param
typedef struct calibrate_input_param_st {
	calibrate_input_param_st()
	{
		image_w       = 0;
		image_h       = 0;
		roi_x         = 0;
		roi_y         = 0;
		roi_w         = 0;
		roi_h         = 0;
		group_sum     = 0;
		per_group_num = 0;
	}
	int image_w;       // image width
	int image_h;       // image height
	int roi_x;         // ROI left
	int roi_y;         // ROI top
	int roi_w;         // ROI width
	int roi_h;         // ROI height
	int group_sum;     // group sum
	int per_group_num; // num per group
}CALIBRATE_INPUT_PARAM;

// Notice:PPD zoom param 
typedef struct fpd_zoom_rect_st
{
	unsigned int left; // zoom begin 
	unsigned int top;
	unsigned int width;
	unsigned int height;
}FPD_ZOOM_RECT;

// Notice:PPD work mode 
typedef struct fpd_user_mode_st {
	fpd_user_mode_st()
	{
		mode_binning      = 1;
		mode_pga_level    = 6;
		mode_acqtime      = 1000;
		mode_preparetime  = 0;
		mode_kv           = 0;
		mode_zoom         = {0, 0, 0, 0};
	}
	unsigned char mode_binning;     // binning tyep
	unsigned char mode_pga_level;   // pga level
	unsigned int  mode_acqtime;     // Image acquisition time,unit:ms(1000ms:1 frame,500ms:2 frame,250ms:4 frame,125ms:8 frame,...,33ms:30 frame)
	unsigned int  mode_preparetime; // [0]发送prepare命令+single shot采集1帧；[>0]发送prepare命令采集1帧。
	unsigned int  mode_kv;          // acquisition voltage
	FPD_ZOOM_RECT mode_zoom;        // zoom rect
}FPD_USER_MODE;

// Notice:PPD mode list
typedef struct correct_template_mode_st {
	correct_template_mode_st()
	{
		fpd_size          = 0;
		binning           = 0;
		pga_level         = 0;
		acquire_fps       = 1;
		zoom_rect.left    = 0;
		zoom_rect.top     = 0;
		zoom_rect.width   = 0;
		zoom_rect.height  = 0;
		trigger_mode      = 1;
		correct_offset    = 0;
		correct_gain      = 0;
		correct_defect    = 0;
		correct_dummy     = 0;	
	}
	unsigned char fpd_size;          // fpd type
	unsigned char binning;           // binning type
	unsigned char pga_level;         // pga level
	unsigned char  acquire_fps;       // image acquire frame rate(1 frame:1000ms,2 frame:500ms,4 frame:250ms,8 frame:125ms,...,30 frame:33ms)
	FPD_ZOOM_RECT zoom_rect;         // zoom rect
	unsigned char trigger_mode;      // trigger mode,reference EnumTRIGGER_MODE
	unsigned char correct_offset;    // 00-"Do nothing";01-"prepare Offset Correction";  02-"post Offset Correction";03-Firware offset Correction;
	unsigned char correct_gain;      // 00-"Do nothing";01-"Software Gain Correction";   02-"Firware Gain Correction"
	unsigned char correct_defect;    // 00-"Do nothing";01-"Software Defect Correction"; 02-"Firware Defect Correction"
	unsigned char correct_dummy;     // 00-"Do nothing";01-"Software Defect Correction"; 02-"Firware Defect Correction"
	unsigned int  correct_dose_kv;   // dose:kv
	unsigned int  correct_dose_ma;   // dose:ma
}CORRECT_TEMPLATE_MODE;

// Notice: After Each Member Variables, show Variables enum , 
// before '-' is variables' value, after '-' is the meaning of the value;
// each value departed by ';' symbol
#pragma pack(1)

// Notice:wireless battery info
typedef struct battery_status_info_st
{
	battery_status_info_st()
	{
		usTemperature = 0;
		usHumidity = 0;
		uzStatusCmd = 0x12;
		uzPercentage = 0;
		uzBatteryStatus = 0;
		usRemainingTime = 0;
		uzIsWlan24G5G = 0;
		uzIsApClientMode = 0;
	}
	unsigned short usTemperature;       // Detector Temperature
	unsigned short usHumidity;          // Detector Humidity
	unsigned char uzStatusCmd;          // Battery Status command,default:0x12
	unsigned char uzPercentage;         // Battery Percentage,0~100
	unsigned char uzBatteryStatus;      // Battery Status,01-Battery charging,02-Battery powered,03-Power supply,04-Charging complete.
	unsigned short usRemainingTime;     // Remaining Charging Time,unit:minute
	unsigned char uzIsWlan24G5G;        // WLAN:1-2.4G,2-5G,others-Invalid
	unsigned char uzIsApClientMode;     // WLAN:AP Mode or Client Mode,1-AP Mode,2-Client Mode,others-Invalid
}BATTERY_STATUS_INFO;

// Notice:Region of interest in images：9
typedef struct ImageRoi_st
{
	ImageRoi_st()
	{
		m_byRoiEnable = 0;
		m_sRoiLeft    = 0;
		m_sRoiTop     = 0;
		m_sRoiWidth   = 0;
		m_sRoiHeight  = 0;
	}
	unsigned char  m_byRoiEnable;      //01 ROI enbale or disable,1-enbale,非1-disable
	unsigned short m_sRoiLeft;         //02 ROI rect left
	unsigned short m_sRoiTop;          //02 ROI rect top
	unsigned short m_sRoiWidth;        //02 ROI rect Width
	unsigned short m_sRoiHeight;       //02 ROI rect Height
}ImageROI;

// System Manufacture Information：100
typedef struct SysBaseInfo_st 
{
	// Register_1 // Register_1~Register_100
	unsigned char   	m_byProductType;      				//01	//01-Flat Panel Detector;  02-Linear Array Detector
	// Register_2
	unsigned char    	m_byXRaySensorType;   				//01	//01-Amorphous Silicon; 02-CMOS; 03-IGZO; 04-LTPS; 05-Amorphous Selenium
	// Register_3
	unsigned char    	m_byPanelSize;        				//01	//01-1717 inch Panel Size; 02-1417; 03-1414; 04-1212; 
	                                                                //05-1012; 06-0912; 07-0910; 08-0909; 09-0506; 10-0505; 11-0503
	// Register_4
	unsigned char   	m_byPixelPitch;						//01	//01-27 um; 02-50; 03-75; 04-85; 05-100; 06-127; 07-140; 08-150; 09-180; 10-200 11-205; 12-400; 13-1000
	// Register_5
	unsigned char       m_byPixelMatrix;     				//01	//01-"3072 x 3072"; 02-"2536 x 3528"; 03-"2800 x 2304"; 04-"2304 x 2304"; 05-"2048 x 2048"; 06-"1536 x 1536"; 
	                                                                //07-"1024 x 1536"; 08-"1024 x 1024"; 09-"1024 x 0768"; 10-"1024 x 0512"; 11-"0768 x 0768"; 
	                                                                //12-"0512 x 0512"; 13-"0512 x 0256"; 14-"0256 x 0256"
	// Register_6
	unsigned char       m_byScintillatorType;				//01	//01-DRZ Standard; 02-DRZ High; 03-DRZ Plus; 04-PI-200; 05-Structured GOS; 06-CSI Evaporation; 07-CSI Attach;
	// Register_7
	unsigned char       m_byScanLineFanoutMode;				//01	//01-Single Side Single Gate; 02-Dual Side Single Gate; 03-Single Side Dual Gate; 04-Dual Side Dual Gate;
	// Register_8
	unsigned char       m_byReadoutLineFanoutMode;  		//01	//01-Single Side Single Read; 02-Dual Side Single Read; 03-Single Side Dual Read; 04-Dual Side Dual Read;
	// Register_9
	unsigned char       m_byFPDMode;						//01	//01-Static; 02-Dynamic;
	// Register_10
	unsigned char       m_byFPDStyle;						//01	//01-Fixed; 02-Wireless; 03-Portable;
	// Register_11
	unsigned char       m_byApplicationMode;        		//01	//01-Medical; 02-Industry;
	// Register_12
	unsigned char       m_byGateChannel;					//01	//01-"600 Channel"; 02-"512 Channel"; 03-"384 Channel"; 04-"256 Channel"; 05-"128 Channel"; 06-"064 Channel"
	// Register_13
	unsigned char		m_byGateType;						//01	//01-"HX8677"; 02-"HX8698D"; 03-"NT39565D"
	// Register_14
	unsigned char		m_byAFEChannel;						//01	//01-"64 Channel"; 02-"128 Channel"; 03-"256 Channel"; 04-"512 Channel";
	// Register_15
	unsigned char		m_byAFEType;						//01	//01-"AFE0064"; 02-"TI COF 2256"; 03-"AD8488"; 04-"ADI COF 2256";
	// Register_16~Register_17
	unsigned short		m_sGateNumber;						//02	//Gate Number
	// Register_18~Register_19
	unsigned short		m_sAFENumber;						//02	//AFE Number	
	// Register_20~Register_21
	unsigned short		m_sImageWidth;						//02	//Image Width // modified by mhyang 20191220
	// Register_22~Register_23
	unsigned short		m_sImageHeight;						//02	//Image Height
	// Register_24~Register_37
	unsigned char		m_cSnNumber[14];				    //15	//sn number   // modified by mhyang 20200401
	// Register_38~Register_46.
	ImageROI            m_stRoi;                            //09    //Region Of Interest;
	// Register_47~Register_53
	unsigned char       m_byAuthorizationEndTime1;          //01	//Authorization End Time1 // modified by mhyang 20211118
	unsigned char       m_byAuthorizationEndTime2;          //01	//Authorization End Time2
	unsigned char       m_byAuthorizationEndTime3;          //01	//Authorization End Time3
	unsigned char       m_byAuthorizationEndTime4;          //01	//Authorization End Time4
	unsigned char       m_byAuthorizationEndTime5;          //01	//Authorization End Time5
	unsigned char       m_byAuthorizationEndTime6;          //01	//Authorization End Time6
	unsigned char       m_byAuthorizationStatus;            //01	//Authorization Status
	// Register_54~Register_59
	unsigned char       m_byRtcTime1;						//01	//RTC Time1 // modified by mhyang 20211119
	unsigned char       m_byRtcTime2;						//01	//RTC Time2
	unsigned char       m_byRtcTime3;						//01	//RTC Time3
	unsigned char       m_byRtcTime4;						//01	//RTC Time4
	unsigned char       m_byRtcTime5;						//01	//RTC Time5
	unsigned char       m_byRtcTime6;						//01	//RTC Time6
	// Register_60~Register_100.
	unsigned char		m_abySysBaseInfoReserved[41];	    //41//////Registers 60To100(include) Are Reserved;
}SysBaseInfo;

// System Manufacture Information：50
typedef struct SysManuInfo_st 
{
	// Register_1~Register_4                                //04 Register_151~Register_178
	unsigned char       m_byHead[4];
	// Register_5~Register_16
	unsigned char       m_byFPDSerialNumber[12];   			//12	//FPD SN Byte 01-12;
	// Register_17~Register_18
	unsigned short      m_sYear;							//02	//Year
	// Register_19~Register_20
	unsigned short      m_sMouth;							//02	//Month
	// Register_21~Register_22
	unsigned char       m_byEmbeddedSoftwareVersion1;		//01	//Embedded Software Version
	unsigned char       m_byEmbeddedSoftwareVersion2;		//01	//Embedded Software Version
	// Register_23~Register_26
	unsigned char       m_byEmbeddedSoftwareBuildingTime1;	//01	//Embedded Software Building Time
	unsigned char       m_byEmbeddedSoftwareBuildingTime2;	//01	//Embedded Software Building Time
	unsigned char       m_byEmbeddedSoftwareBuildingTime3;	//01	//Embedded Software Building Time
	unsigned char       m_byEmbeddedSoftwareStatus;		    //01	//Embedded Software Status 0-release,1-rc,2-beta
	// Register_27~Register_28
	unsigned short      m_sMasterFPGAFirmwareVersion;		//02	//Master FPGA Firmware Version
	// Register_29~Register_31
	unsigned char       m_byMasterFPGAFirmwareBuildingTime1;//01	//Master FPGA Firmware Building Time1
	unsigned char       m_byMasterFPGAFirmwareBuildingTime2;//01	//Master FPGA Firmware Building Time2
	unsigned char       m_byMasterFPGAFirmwareBuildingTime3;//01	//Master FPGA Firmware Building Time3
	// Register_32~Register_34
	unsigned char       m_byMasterFPGAFirmwareStatus1;		//01	//Master FPGA Firmware Status1
	unsigned char       m_byMasterFPGAFirmwareStatus2;		//01	//Master FPGA Firmware Status2
	unsigned char       m_byMasterFPGAFirmwareStatus3;      //01	//Master FPGA Firmware Status3
	// Register_35~Register_36
	unsigned char		m_byMCUFirmwareVersion1;			//01	//MCU Firmware Version1
	unsigned char		m_byMCUFirmwareVersion2;			//01	//MCU Firmware Version2
	// Register_37~Register_40
	unsigned char		m_byMCUFirmwareBuildingTime1;		//01	//MCU Firmware Building Time1
	unsigned char		m_byMCUFirmwareBuildingTime2;		//01	//MCU Firmware Building Time2
	unsigned char       m_byMCUFirmwareBuildingTime3;		//01	//MCU Firmware Building Time3
	unsigned char       m_byMCUFirmwareStatus;				//01	//MCU Firmware Status
	// Register_41~Register_44
	unsigned char		m_szBatterySN[4];		            //04	//Battery Serial number
	// Register_45~Register_50
	unsigned char		m_abySysManuInfoReserved[6];        //6     //Reserved Size
}SysManuInfo;

// System Status Information：28
typedef struct SysStatusInfo_st 
{
	// Register_1~Register_4 // Register_151~Register_178
	unsigned char		m_byHead[4];
	// Register_5~Register_8
	unsigned int		m_unTemperature;					//04	//Temperature
	// Register_9~Register_12
	unsigned int 		m_unHumidity;						//04	//Humidity
	// Register_13~Register_16
	unsigned int 		m_unDose;							//04	//Dose
	// Register_17~Register_28
	unsigned char		m_abySysStatusInfoReserved[12];
}SysStatusInfo;

// Gigabit Ethernet Information：40
typedef struct EtherInfo_st 
{
	// Register_1~Register_4 // Register_179~Register_218
	unsigned char       m_byHead[4];
	// Register_5~Register_10
	unsigned char       m_bySourceMAC[6];                   //06	//Source MAC
	// Register_11~Register_14
	unsigned char       m_bySourceIP[4];                    //04	//Source IP
	// Register_15~Register_16
	unsigned short		m_sSourceUDPPort;					//02	//Source UDP Port
	// Register_17~Register_22
	unsigned char       m_byDestMAC[6];                     //06	//Dest MAC
	// Register_23~Register_26
	unsigned char       m_byDestIP[4];                      //04	//Dest IP
	// Register_27~Register_28
	unsigned short		m_sDestUDPPort;						//02	//Dest UDP Port	
	// Register_29
	unsigned char       m_byIs5GMode;                       //01	//1-2.4G模式,2-5G模式
	// Register_30
	unsigned char       m_byIsAPMode;                       //01	//1-AP模式,2-Client模式
	// Register_31~Register_40
	unsigned char		m_abyEtherInfoReserved[10];         //10	//Reserved Size
}EtherInfo;

// High Voltage Generator Interface Trigger Mode Information：21
typedef union signal_value
{
	struct
	{
		unsigned int  b0 : 1;
		unsigned int  b1 : 1;
		unsigned int  b2 : 1;
		unsigned int  b3 : 1;
		unsigned int  b4 : 1;
		unsigned int  b5 : 3;
	}BITE_VALUE;
	unsigned char unValue;
}UNION_SIGNAL_VALUE;

typedef struct HiVolTriggerModeInfo_st
{
	// Register_1~Register_4  //Register_219~Register_239
	unsigned char		m_byHead[4];                //04	
	// Register_5 HVG_Trig Mode(03)			        
	unsigned char		m_byPolarityParam;          //01	bit4:NON,bit3:i_HVG_Request,bit2:i_HVG_Sync_In,bit1:o_FPD_Ready,bit0:o_FPD_Sync_Out
	unsigned char		m_byHVGRequestParam03;      //01	bit4:NON,bit3:i_HVG_Request,bit2:i_HVG_Sync_In,bit1:0,bit0:0
	unsigned char		m_byFPDReadyParam03;        //01	bit4:NON,bit3:0,bit2:0,bit1:o_FPD_Ready,bit0:o_FPD_Sync_Out
	// Register_8 HVG_SYNC Mode(05)			        
	unsigned char		m_byHVGRequestParam05;      //01	bit4:NON,bit3:i_HVG_Request,bit2:i_HVG_Sync_In,bit1:0,bit0:0
	unsigned char		m_byFPDReadyParam05;        //01	bit4:NON,bit3:0,bit2:0,bit1:o_FPD_Ready,bit0:o_FPD_Sync_Out
	// Register_10 FPD_SYNC Mode(06)		        
	unsigned char		m_byHVGRequestParam06;      //01	bit4:NON,bit3:i_HVG_Request,bit2:i_HVG_Sync_In,bit1:0,bit0:0
	unsigned char		m_byFPDReadyParam06;        //01	bit4:NON,bit3:0,bit2:0,bit1:o_FPD_Ready,bit0:o_FPD_Sync_Out
	// Register_12 FPD_SYNC Mode(08)		        
	unsigned char		m_byHVGRequestParam08;      //01	bit4:NON,bit3:i_HVG_Request,bit2:i_HVG_Sync_In,bit1:0,bit0:0
	unsigned char		m_byFPDReadyParam08;        //01	bit4:NON,bit3:0,bit2:0,bit1:o_FPD_Ready,bit0:o_FPD_Sync_Out
	unsigned char		m_byHVGExplore08;           //01	bit4:NON,bit3:i_HVG_Request,bit2:i_HVG_Sync_In,bit1:0,bit0:0
	// Register_15~Register_21
	unsigned char		m_byHiVolTriggerReserved[7];//07	
}HiVolTriggerModeInfo;

// System Configuration Information：128
typedef struct SysCfgInfo_st 
{
	// Register_1~Register_4  //Register_240~Register_367	
	unsigned char       m_byHead[4];
	// Register_5
	unsigned char       m_byTriggerMode;					//01	// 01-"Static: Software Mode" 02-"Static: Prep Mode"; 03-"Static Hvg Trigger Mode"; 
														    		// 04-Static AED Trigger Mode, 05-Dynamic Hvg In Mode,06-Dynamic Fpd Out Mode.
	// Register_6										    
	unsigned char 	    m_byPreviewModeTransmission;		//01	//00-"Just transmmit full resolution image matrix"; 01-"Just transmmit the preview image"; 
	                                                                //02-"Transmmit the preview image and full resolution image"
	// Register_7										    
	unsigned char 	    m_byPositiveVsNegativeIntegrate;	//01	//01-"Electron"; 02-"Hole" //04-"Static: Inner Trigger Mode"; 05-"Dynamic: Sync In Mode"; 06-"Dynamic: Sync Out Mode"
														    
	// Register_8										    
	unsigned char 	    m_byBinning;						//01	//01-"1x1"; 02-"2x2 Binning"; 03-"3x3 Binning"; 04-"4x4 Binning";
														    
	// Register_9										    
	unsigned char       m_byIntegratorCapacitorSelection;	//01	//01-"Integrator Capacitor PGA0"; 02-"Integrator Capacitor PGA1"; 03-"PGA2";......;08-"Integrator Capacitor PGA7"

	// Register_10
	unsigned char       m_byAmplifierGainSelection;			//01	//01-"Amplifier Gain AMP0"; 02-"Amplifier Gain AMP1"; 03-"Amplifier Gain AMP2"; 04-"Amplifier Gain AMP3";
	                                                                //05-"Amplifier Gain AMP4"; 06-"Amplifier Gain AMP5"; 07-"Amplifier Gain AMP6"; 08-"Amplifier Gain AMP7";
	// Register_11
	unsigned char		m_bySelfDumpingEnable;				//01	//01-"Enable Dumping Process"; 02-"Disable Dumping Process";
	// Register12
	unsigned char		m_bySelfDumpingProcessing;			//01	//01-"Clear Process for Dumping"; 02-"Acquisition Process for Dumping";

	// add 20190705
	unsigned char       m_byClearFrameNumber;               //01	//01-"Clear Frame"; 02-"Clear Frame";03-"Clear Frame";04-"Clear Frame";

	// Register_13
	unsigned char		m_byPDZ;							//01	//01-"Disable PDZ"; 02-"Enable PDZ"
	// Register_14
	unsigned char		m_byNAPZ;							//01	//01-"Disable NAPZ"; 02-"Enable NAPZ"

	// Register15
	unsigned char		m_byInnerTriggerSensorSelection;	//01	//00-"No Selection"; 01-"I Sensor Selection"; 02-"II Sensor Selection"; 
	                                                                //03-"III Sensor Selection"; 04-"IV Sensor Selection"; 05-"V Sensor Selection"                                                                
	// Register_16~Register_17
	unsigned short		m_sZoomBeginRowNumber;				//02	//Zoom Begin Row Number
	// Register_18~Register_19
	unsigned short		m_sZoomEndRowNumber;				//02	//Zoom End Row Number
	// Register_20~Register_21
	unsigned short		m_sZoomBeginColumnNumber;			//02	//Zoom Begin Column Number
	// Register_22~Register_23
	unsigned short		m_sZoomEndColumnNumber;				//02	//Zoom End Column Number

	// Register24~Register27
	unsigned int 		m_unSelfDumpingSpanTime;			//04	//unit: ms
	// Register28~Register31
	unsigned int 		m_unContinuousAcquisitionSpanTime;	//04	//unit: ms
	// Register32~Register35
	unsigned int 		m_unPreDumpingDelayTime;			//04	//unit: ms
	// Register36~Register39
	unsigned int 		m_unPreAcquisitionDelayTime;		//04	//unit: ms
	// Register40~Register43
	unsigned int 		m_unPostDumpingDelayTime;			//04	//unit: ms
	// Register44~Register47
	unsigned int 		m_unPostAcquisitionDelayTime;		//04	//unit: ms
	// Register48~Register51
	unsigned int 		m_unSyncInExposureWindowTime;		//04	//unit: ms
	// Register52~Register55
	unsigned int 		m_unSyncOutExposureWindowTime;		//04	//unit: ms
	// Register56~Register59
	unsigned int 		m_unTFTOffToIntegrateOffTimeSpan;	//04	//unit: ms
	// Register_60~Register_63
	unsigned int 		m_unIntegrateTime;					//04	//unit: ms
	// Register_64~Register_67
	unsigned int 		m_unPreFrameDelay;					//04	//unit: ms
	// Register_68~Register_71
	unsigned int 		m_unPostFrameDelay;					//04	//unit: ms
	// Register_72~Register_75
	unsigned int 		m_unSaturation;					    //04	//unit: ms
	// Register_76~Register_79
	unsigned int 		m_unClipping;					    //04	//unit: ms
	// Register_80~Register_81
	unsigned short		m_sHvgRdyMode;				        //02	//0-"Edge Trigger"; 非0-"[1~255]:Config Delay,unit:n*128 ms"
	// Register_82~Register_83
	unsigned short		m_sSaecPreRdyTm;				    //02	//SAEC pre ready time
	// Register_84~Register_85
	unsigned short		m_sSaecPostRdyTm;				    //02	//SAEC post ready time
	// Register_86
	unsigned char       m_byDefectThreshold;                //01	//Defect correction:Calculating the threshold of bad points
	// Register_87~Register_90
	unsigned int 		m_unSleepTime;                      //04	//energy conservation settings: 睡眠（Sleep,unit:minute）
	// Register_91~Register_94
	unsigned int 		m_unMaxBadPointtNumber;             //04	//defect template:Support the maximum threshold of bad points
	// Register_95~Register_120
	unsigned char		m_abySysCfgInfoReserved[26];        //26
	// Register_121~Register_122
	unsigned short		m_sGainb;					        //02	//offset
	// Register_123~Register_126
	unsigned int 		m_unVoltage;					    //04	//unit: kv
	// Register_127
	unsigned char       m_byExTriggerAcqType;               //01    //Reference EnumIMAGE_ACQ_CMD type
}SysCfgInfo;

// Image Calibration Configuration：20
typedef struct ImgCaliCfg_st 
{
	// Register_1~Register_4 //Register_368~Register_387
	unsigned char		m_byHead[4];                        //04    //head 
	// Register_5
	unsigned char		m_byOffsetCorrection;				//01	//00-"Do nothing";01-"Software Offset Correction"; 02-"Hardware Offset Correction";
	// Register_6
	unsigned char		m_byGainCorrection;					//01	//00-"Do nothing";01-"Software Gain Correction";   02-"Hardware Gain Correction"
	// Register_7
	unsigned char		m_byDefectCorrection;				//01	//00-"Do nothing";01-"Software Defect Correction"; 02-"Software Defect Correction"
	// Register_8
	unsigned char		m_byDummyCorrection;				//01	//00-"Do nothing";01-"Software Dummy Correction";  02-"Software Dummy Correction"
	// Register_9~Register_20
	unsigned char		m_abyImgCaliCfgReserved[12];		//12//////Registers 114(include) Are Reserved;
}ImgCaliCfg;

// Voltage Adjust Configuration：48
typedef struct VolAdjustCfg_st 
{
	// Register_1~Register_4 //Register_388~Register_435
	unsigned char		m_byHead[4];
	// Register_5~Register_8
	unsigned int 		m_unVCOM;							//04	//VCOM
	// Register_9~Register_12
	unsigned int 		m_unVGG;							//04	//VGG
	// Register_13~Register_16
	unsigned int 		m_unVEE;							//04	//VEE
	// Register_17~Register_20
	unsigned int 		m_unVbias;							//04	//Vbias	
	// Register_21~Register_36
	unsigned int 		m_unComp[4];						//04	//Comp1	// Register114
	// Register_37~Register_48
	unsigned char		m_abyVolAdjustCfgReserved[12];		//12//////Registers 114(include) Are Reserved;
}VolAdjustCfg;

// TI COF Parameter Configuration：84
typedef struct TICOFCfg_st 
{
	// Register_1~Register_4  //Register_436~Register_519
	unsigned char		m_byHead[4];
	// Register_5~Register_64
	unsigned short		m_sTICOFRegister[30];
	// Register_65~Register_84
	unsigned char		m_abyTICOFCfgReserved[20];
}TICOFCfg;

//CMOS Parameter Configuration：116
typedef struct CMOSCfg_st 
{
	// Register_1~Register_4 //Register_520~Register_635
	unsigned char		m_byHead[4];
	// Register_5~Register_68
	unsigned short		m_sCMOSRegister[32];
	// Register_69~Register_116
	unsigned char		m_abyCMOSCfgReserved[48];
}CMOSCfg;

// ADI COF Parameter Configuration：389
typedef struct ADICOFCfg_st 
{
	// Register_1~Register_4 //Register_636~Register_1024
	unsigned char		m_byHead[4];
	// Register_5~Register_19
	unsigned short		m_sADICOFRegister[15];
	// Register_20~Register_375
	unsigned char		m_abyADICOFCfgReserved[355];
}ADICOFCfg;

// 1024 byte regedit
typedef struct RegCfgInfo_s
{
	// System base Information：100,Register_1~Register_100
	SysBaseInfo m_SysBaseInfo;
	// System Manufacture Information：50,Register_101~Register_150
	SysManuInfo m_SysManuInfo;
	// System Status Information：28,Register_151~Register_178
	SysStatusInfo m_SysStatusInfo;
	// Gigabit Ethernet Information：40,Register_179~Register_218
	EtherInfo m_EtherInfo;
	// High Voltage Generator Interface Trigger Mode Information：21,Register_219~Register_239
	HiVolTriggerModeInfo m_HiVolTriggerModeInfo;
	// System Configuration Information：127,Register_240~Register_366
	SysCfgInfo m_SysCfgInfo;
	// Image Calibration Configuration：20,Register_367~Register_386
	ImgCaliCfg m_ImgCaliCfg;
	// Voltage Adjust Configuration：48,Register_387~Register_434
	VolAdjustCfg m_VolAdjustCfg;
	// TI COF Parameter Configuration：84,Register_435~Register_518
	TICOFCfg m_TICOFCfg;
	// CMOS Parameter Configuration：116,Register_519~Register_634
	CMOSCfg m_CMOSCfg;
	// ADI COF Parameter Configuration：390,Register_635~Register_1024
	ADICOFCfg m_ADICOFCfg;
	///////////////////////
}RegCfgInfo;
#pragma pack()
/////////////////////////////////////////////////////////////////////////////
extern char g_szDllPath1[MAX_PATH];                         // 全局变量-当前sdk所在目录
extern HBI_DLL_INSTANCE g_hbiInstance[DETECTOR_MAX_NUMBER]; // 全局变量-sdk实例
////////////////////////////////////////////////////////////////////////////
#endif // __HBI_TYPE_H_
