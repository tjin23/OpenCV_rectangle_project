#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

namespace Shared
{
	class SimpleDataProtection
	{
	public:
		static void encryptText(std::string & text);

		static void encryptCharacter(char & character);

		static void decryptCharacter(char & character);

		static cv::Mat encryptImage(cv::Mat & img);

		static cv::Mat encryptImage2(cv::Mat& img);

		static cv::Mat encryptImage3(cv::Mat& img, cv::Mat& keyImage);

		static cv::Mat XORImages(cv::Mat& src1, cv::Mat& src2);

		static void decryptImage(cv::Mat& img);
	};

	void Test1_EncryptSomeTextAndPrint();

	void Test1_DecryptSomeTextAndPrint();

	void Test1_EncryptSomeTextAndPrint_V2();
	
	void Test1_EncryptImage1();

	void Test2_BlurImage1();

	void  Test3_GaussianBlurImage1();

	int CaptureVideoAndEdit(std::string & inputVideoPath, std::string& outputVideoPath);

	int SeparateChannelOfVideo(int argc, char* argv[]);
}
