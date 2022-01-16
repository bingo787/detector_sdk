// DetectorDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include <string>
#include "Detector.h"

#include "WinSerialPort.h"


void MyHandleFunc(int error_code, IMAGE_DATA_ST data)
{
	// 用户回调函数，此处可以拿到照片数据
	// cv::Mat img = cv::Mat(height, width, MatType.CV_16UC1, data);
	std::cout << "frame id : " <<  data.uframeid << std::endl;
	std::cout << "image bits,width,height : " << data.ndatabits << ","<<  data.uwidth << "," << data.uheight << std::endl;

}	
int main(int argc, char** argv)
{
	std::cout << "Hello Detector " << std::endl;

	std::string port = "COM1";
	if (argc > 1)
	{
		port = argv[1];
	}
	rayon::Detector detector;
	auto ret = detector.Connect(MyHandleFunc, port);

	if (ret != 0 )
	{
		std::cout << "detector connect failed" << std::endl;
		exit(-1);
	}
	rayon::DetectorConfig config;
	config.work_mode = rayon::WorkMode::E_STATIC;
	detector.ApplyConfig(config);
	detector.SetKVoltageAndCurrent(40,400);
	
	std::cout << "\n 1：单张采集， 2：连续采集， 3：停止连续采集，4：断开连接" << std::endl;
    std::string input;

	while (true)
	{
		std::cin >> input;
		switch (std::stoi(input))
		{
		case 1: {
			ret = detector.SingleAcquisition(1000);
			if (ret!=0)
			{
				std::cout << "detector.SingleAcquisition failed\n";
			}
		}break;
		case 2: {
			rayon::DetectorConfig config;
			config.work_mode = rayon::WorkMode::E_DYNAMIC;
			detector.ApplyConfig(config);
			ret =  detector.StartLiveAcquisition(250);
			if (ret != 0)
			{
				std::cout << "detector.StartLiveAcquisition failed\n";
			}
		}break;

		case 3: {
			ret = detector.StopLiveAcquisition();
			if (ret != 0)
			{
				std::cout << "detector.StopLiveAcquisition() failed\n";
			}
		}break;
		case 4: {
			detector.Disconnect();
			exit(0);
		}break;
		default:
			break;
		}
	}

	return 0;
}
