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
		* ��������: ��������
		* ����˵��:
				In: ImageDataCallback callback - �û�ͼ��ص�����
					const std::string& port - ���ڶ˿ں�,����"COM1"
									  
				Out: ��
		* �� �� ֵ��int
				0   - �ɹ�
				��0 - ʧ��
		* ��    ע:
		*/
		int Connect(ImageDataCallback callback, const std::string& port);
		
		
		/*
		* ��������: �Ͽ�����
		*/
		void Disconnect();


		/*
		* ��������: ̽������������
		* ����˵��:
				In: DetectorConfig& config 

				Out: ��
		* �� �� ֵ��int
				0   - �ɹ�
				��0 - ʧ��
		* ��    ע:
		*/
		int ApplyConfig(const DetectorConfig& config);

		/*
		* ��������: ��֡�ɼ�
		* ����˵��:
				In: int time - ���Ųɼ����ع�ʱ�䣬��λms

				Out: ��
		* �� �� ֵ��int
				0   - �ɹ�
				��0 - ʧ��
		* ��    ע:
		*/
		int SingleAcquisition(int time);

		/*
		* ��������: �����ɼ�
		* ����˵��:
				In: int time -�����ɼ���֡�ʵĵ�������λms
					4֡(250ms),2֡(500ms),1֡(1000ms)

				Out: ��
		* �� �� ֵ��int
				0   - �ɹ�
				��0 - ʧ��
		* ��    ע:
		*/
		int StartLiveAcquisition(int time);
		
		
		/*
		* ��������: ֹͣ�ɼ�
		* �� �� ֵ��int
				0   - �ɹ�
				��0 - ʧ��
		* ��    ע: ֻ�������ɼ���Ч
		*/
		int StopLiveAcquisition();

		/*
		* ��������: ���ù�Դ�ĵ�ѹ�͵���
		* ����˵����double kv, ��ѹֵ����λǧ��kV
					int current�� ����ֵ����λ΢��uA
		* �� �� ֵ��
					0   - �ɹ�
				��0 - ʧ��
		* ��    ע: 
		*/
		int SetKVoltageAndCurrent(double kv, int current );

		/*
		* ��������: ̽�����Ƿ�����
		* �� �� ֵ��bool
				true   -  ������
				false  -  δ����
		* ��    ע:
		*/
		inline bool IsConnected() { return connected_; }

		/*
		* ��������: ���Ź����
		* ��    ע: �û�����Ҫ����
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
