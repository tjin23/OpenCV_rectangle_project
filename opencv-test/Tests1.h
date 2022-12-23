#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

namespace Shared
{
	void Test1_EncryptSomeTextAndPrint();

	void Test1_DecryptSomeTextAndPrint();

	void Test1_EncryptSomeTextAndPrint_V2();
	
	void Test1_EncryptImage1();

	void Test2_BlurImage1();

	void  Test3_GaussianBlurImage1();

	int CaptureVideoAndAddBlackRectangle(std::string & inputVideoPath, std::string& outputVideoPath);

	int SeparateChannelOfVideo(int argc, char* argv[]);
}
