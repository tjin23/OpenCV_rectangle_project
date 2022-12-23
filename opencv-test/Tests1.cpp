#include "Tests1.h"
#include <chrono>
#include <cstdio>
#include <fstream>
#include "SimpleEncryptionAndDecryption.h"


#define cvtCOLOR 0
#define outputString "output_xor_image.png"
#define keyString "output_key_image_for_xor.png"
#define decryptedString "output_decrypted_image.png"

namespace Shared
{
	void Test1_EncryptSomeTextAndPrint()
	{
		auto testStr = std::string("ABC123");
		SimpleDataProtection::encryptText(testStr);
		std::cout << "Test str is: " << testStr << std::endl;
	}

	void Test1_DecryptSomeTextAndPrint()
	{
		auto testStr = std::string("ABC123");
		SimpleDataProtection::encryptText(testStr);

		for (auto i = 0; i < testStr.size(); i++)
		{
			SimpleDataProtection::decryptCharacter(testStr[i]);
		}

		std::cout << "Test str after decrypt is: " << testStr << std::endl;
	}

	void Test1_EncryptSomeTextAndPrint_V2()
	{
		auto testStr = std::string("PQRS567");
		SimpleDataProtection::encryptText(testStr);
		std::cout << "Test str is: " << testStr << std::endl;
	}

	void  Test1_EncryptImage1()
	{
		cv::Mat dsa = cv::imread("D:/Task_Files/SimpleDataProtection/lp_images/testData/sampleLicenseImage.jpg");
		
		// SimpleDataProtection::decryptImage(dsa);

		// cv::Mat output_im = SimpleDataProtection::encryptImage(dsa);

		cv::Mat imageKey = cv::Mat(dsa.size(), CV_8UC3);

		cv::Mat output_im = SimpleDataProtection::encryptImage3(dsa, imageKey);

		std::string output = "D:/Task_Files/SimpleDataProtection/output/";

		auto keyOutput = output + keyString;

		cv::imwrite(keyOutput, imageKey);

		auto outputImPath = output + outputString;

		std::ifstream ifile;

		ifile.open(outputImPath);
		if (ifile) 
		{
			std::remove(outputImPath.c_str());
		}
		cv::imwrite(outputImPath, output_im);

		ifile.open(keyOutput);
		if (ifile)
		{
			std::remove(keyOutput.c_str());
		}
		cv::imwrite(keyOutput, imageKey);

		// decrypting...
		auto image_key = cv::imread(keyOutput);
		auto image_xor = cv::imread(outputImPath);
		auto decryptedImage = SimpleDataProtection::XORImages(image_xor, imageKey);

		ifile.open(output + decryptedString);
		if (ifile)
		{
			std::remove((output + decryptedString).c_str());
		}

		cv::imwrite(output + decryptedString, decryptedImage);
	}

	void  Test2_BlurImage1()
	{
		cv::Mat image = cv::imread("D:/Task_Files/SimpleDataProtection/peopleInVehicle/piv2.png");

		cv::blur(image, image, cv::Size(50, 50));


		std::string output = "D:/Task_Files/SimpleDataProtection/output/blurred.png";

		std::ifstream ifile;
		ifile.open(output);
		if (ifile)
		{
			std::remove((output).c_str());
		}

		cv::imwrite(output , image);
	}

	int CaptureVideoAndAddBlackRectangle(std::string & inputVideoPath, std::string & outputVideoPath)
	{
		using namespace cv;

		// Create a VideoCapture object and open the input file
		// If the input is the web camera, pass 0 instead of the video file name
		VideoCapture cap(inputVideoPath);

		// Check if camera opened successfully
		if (!cap.isOpened()) 
		{
			std::cout << "Error opening video stream or file" << std::endl;
			return -1;
		}

		int frameNum = 0;

		// Output Video:
		VideoWriter outputVideo;

		int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));

		Size sz = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
			(int)cap.get(CAP_PROP_FRAME_HEIGHT));

		outputVideo.open(outputVideoPath, ex, cap.get(CAP_PROP_FPS), sz, true);

		if (!outputVideo.isOpened())
		{
			std::cout << "Could not open the output video for write: " << outputVideoPath << std::endl;
			return -1;
		}

		// Output Video end

		while (1) 
		{
			Mat frame;
			// Capture frame-by-frame
			cap >> frame;

			// If the frame is empty, break immediately
			if (frame.empty())
				break;

			// Which frames to blacken
			if (frameNum >= 100 && frameNum <= 210)
			{
				rectangle(frame, Point(1349, 563), Point(1385, 595), Scalar(0, 0, 0), cv::FILLED);
			}

			outputVideo << frame;

			frameNum++;
		}

		// When everything done, release the video capture object
		cap.release();

		// Closes all the frames
		destroyAllWindows();

		return 0;
	}

	int SeparateChannelOfVideo(int argc, char* argv[])
	{
		using namespace cv;
		using namespace std;

		if (argc != 4)
		{
			cout << "Not enough parameters" << endl;
			return -1;
		}

		const string source = argv[1];           // the source file name
		const bool askOutputType = argv[3][0] == 'Y';  // If false it will use the inputs codec type
		VideoCapture inputVideo(source);              // Open input

		if (!inputVideo.isOpened())
		{
			cout << "Could not open the input video: " << source << endl;
			return -1;
		}

		string::size_type pAt = source.find_last_of('.');                  // Find extension point
		
		const string NAME = source.substr(0, pAt) + argv[2][0] + ".mp4";   // Form the new name with container
		
		int ex = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));     // Get Codec Type- Int form
		
																		// Transform from int to char via Bitwise operators
		char EXT[] = 
			{ (char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0 };
		
		
		Size S = Size((int)inputVideo.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
			(int)inputVideo.get(CAP_PROP_FRAME_HEIGHT));


		VideoWriter outputVideo;                                        // Open the output


		if (askOutputType)
		{
			outputVideo.open(NAME, ex = -1, inputVideo.get(CAP_PROP_FPS), S, true);
		}
		else
		{
			outputVideo.open(NAME, ex, inputVideo.get(CAP_PROP_FPS), S, true);
		}
			
		if (!outputVideo.isOpened())
		{
			cout << "Could not open the output video for write: " << source << endl;
			return -1;
		}

		cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
			<< " of nr#: " << inputVideo.get(CAP_PROP_FRAME_COUNT) << endl;

		cout << "Input codec type: " << EXT << endl;

		int channel = 2; // Select the channel to save

		switch (argv[2][0])
		{
			case 'R': channel = 2; break;
			case 'G': channel = 1; break;
			case 'B': channel = 0; break;
		}

		Mat src, res;

		vector<Mat> spl;

		for (;;) //Show the image captured in the window and repeat
		{

			inputVideo >> src;              // read

			if (src.empty()) break;         // check if at end

			split(src, spl);                // process - extract only the correct channel

			for (int i = 0; i < 3; ++i)
			{
				if (i != channel)
					spl[i] = Mat::zeros(S, spl[0].type());
			}

			merge(spl, res);
			//outputVideo.write(res); //save or
			outputVideo << res;
		}
		cout << "Finished writing" << endl;
		return 0;
	}

	//{
	//	cv::Mat image = cv::imread("D:/Task_Files/SimpleDataProtection/peopleInVehicle/piv.png");

	//	cv::blur(image, image, cv::Size(10, 10));


	//	std::string output = "D:/Task_Files/SimpleDataProtection/output/blurred.png";

	//	std::ifstream ifile;
	//	ifile.open(output);
	//	if (ifile)
	//	{
	//		std::remove((output).c_str());
	//	}

	//	cv::imwrite(output, image);
	//}
}