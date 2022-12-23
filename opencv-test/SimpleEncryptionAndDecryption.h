#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

namespace Shared
{
	class SimpleDataProtection
	{
	public:
		static void encryptText(std::string& text);

		static void encryptCharacter(char& character);

		static void decryptCharacter(char& character);

		static cv::Mat encryptImage(cv::Mat& img);

		static cv::Mat encryptImage2(cv::Mat& img);

		static cv::Mat encryptImage3(cv::Mat& img, cv::Mat& keyImage);

		static cv::Mat XORImages(cv::Mat& src1, cv::Mat& src2);

		static void decryptImage(cv::Mat& img);
	};
}
