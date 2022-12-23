#include "SimpleEncryptionAndDecryption.h"

namespace Shared
{
	void SimpleDataProtection::encryptText(std::string& text)
	{
		for (auto i = 0; i < text.size(); i++)
		{
			encryptCharacter(text[i]);
		}
	}

	void SimpleDataProtection::encryptCharacter(char& character)
	{
		// Capital letters A to O
		if (character >= 65 && character <= 79)
		{
			character -= 10;
		}
		// Capital letters P to Z
		else if (character >= 80 && character <= 90)
		{
			character += 11;
		}
		// Digits 0 to 9
		else if (character >= 48 && character <= 57)
		{
			character -= 15;
		}
	}

	void SimpleDataProtection::decryptCharacter(char& character)
	{
		// Capital letters A to O
		if (character >= 55 && character <= 69)
		{
			character += 10;
		}
		// Capital letters P to Z
		else if (character >= 91 && character <= 101)
		{
			character -= 11;
		}
		// Digits 0 to 9
		else if (character >= 33 && character <= 42)
		{
			character += 15;
		}
	}

	cv::Mat SimpleDataProtection::encryptImage(cv::Mat& img)
	{
		// cv::Mat fullImageHSV;
		cv::Mat sampleImage;
		//cvtColor(img, sampleImage, CV_BGR2HSV);
		cvtColor(img, sampleImage, CV_BGR2YUV);
		return sampleImage;
	}

	cv::Mat SimpleDataProtection::encryptImage2(cv::Mat& img)
	{
		cv::Mat outputImage;

		const auto scalarKey = cv::Scalar(127, 169, 185);

		cv::Mat imageKey = cv::Mat(img.size(), CV_8UC3, scalarKey);

		cv::bitwise_xor(img, imageKey, outputImage);

		return outputImage;
	}

	cv::Mat SimpleDataProtection::encryptImage3(cv::Mat& img, cv::Mat& keyImage)
	{
		// const auto scalarKey = cv::Scalar(127, 169, 185);

		randu(keyImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));


		return XORImages(keyImage, img);
	}

	cv::Mat SimpleDataProtection::XORImages(cv::Mat& src1, cv::Mat& src2)
	{
		cv::Mat outputImage;

		cv::bitwise_xor(src1, src2, outputImage);

		return outputImage;
	}

	void SimpleDataProtection::decryptImage(cv::Mat& img)
	{
		// cv::Mat fullImageHSV;
		cvtColor(img, img, CV_HSV2BGR);
	}
}
