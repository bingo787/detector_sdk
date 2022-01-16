#pragma once

#include <string>
#include <thread>

#include "include/HbiType.h"
#include "WinSerialPort.h"

namespace rayon {

	enum ErrorCode {
		E_SUCCESS = 0,
		E_FAILED,
		E_INVALID_PARAMS,
		E_FPD_ERROR,
		E_SERIAL_PORT_ERROR
	};


	typedef void(*ImageDataCallback)(int error_code, IMAGE_DATA_ST data);

	enum WorkMode {
		E_STATIC,
		E_DYNAMIC
	};
	struct DetectorConfig {
		WorkMode work_mode;
	};

	class Detector {
	public:
		Detector() = default;
		~Detector() = default;

		/*
		* 功能描述: 建立连接
		* 参数说明:
				In: ImageDataCallback callback - 用户图像回调函数
					const std::string& port - 串口端口号,比如"COM1"
									  
				Out: 无
		* 返 回 值：int
				0   - 成功
				非0 - 失败
		* 备    注:
		*/
		int Connect(ImageDataCallback callback, const std::string& port);
		
		
		/*
		* 功能描述: 断开连接
		*/
		void Disconnect();


		/*
		* 功能描述: 探测器参数配置
		* 参数说明:
				In: DetectorConfig& config 

				Out: 无
		* 返 回 值：int
				0   - 成功
				非0 - 失败
		* 备    注:
		*/
		int ApplyConfig(const DetectorConfig& config);

		/*
		* 功能描述: 单帧采集
		* 参数说明:
				In: int time - 单张采集的曝光时间，单位ms

				Out: 无
		* 返 回 值：int
				0   - 成功
				非0 - 失败
		* 备    注:
		*/
		int SingleAcquisition(int time);

		/*
		* 功能描述: 连续采集
		* 参数说明:
				In: int time -连续采集的帧率的倒数，单位ms
					4帧(250ms),2帧(500ms),1帧(1000ms)

				Out: 无
		* 返 回 值：int
				0   - 成功
				非0 - 失败
		* 备    注:
		*/
		int StartLiveAcquisition(int time);
		
		
		/*
		* 功能描述: 停止采集
		* 返 回 值：int
				0   - 成功
				非0 - 失败
		* 备    注: 只对连续采集生效
		*/
		int StopLiveAcquisition();

		/*
		* 功能描述: 设置光源的电压和电流
		* 参数说明：double kv, 电压值，单位千伏kV
					int current， 电流值，单位微安uA
		* 返 回 值：
					0   - 成功
				非0 - 失败
		* 备    注: 
		*/
		int SetKVoltageAndCurrent(double kv, int current );

		/*
		* 功能描述: 探测器是否连接
		* 返 回 值：bool
				true   -  已连接
				false  -  未连接
		* 备    注:
		*/
		inline bool IsConnected() { return connected_; }

		/*
		* 功能描述: 看门狗检查
		* 备    注: 用户不需要调用
		*/
		void CheckWatchDog();

		bool verbose = false;

	private:
		friend int handleEventfun(void *content,
			int nDevId,
			unsigned char byteEventId,
			void *pvParam,
			int nlength,
			int param3,
			int param4);

		int SendCommand(const std::string& cmd);
		int TurnOnXray();
		int TurnOffXray();
		int SetKVoltage(double vol);
		int SetCurrent(int current);
		void GetHVStatus();
		void *handle_{};
		bool connected_ =false;
		bool need_feeding_dog_ = false;
		RegCfgInfo reg_config_;
		ImageDataCallback image_data_callback_{};
		WinSerialPort serial_port_{};
		std::thread receive_serial_msg_task_;
	};

}
