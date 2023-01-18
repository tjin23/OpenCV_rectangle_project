#include "ContrastEnhancer.h"
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

void ContrastEnhancer::ImproveContrast(const double & alpha, const int & beta, const std::string & imagePath)
{
    // CommandLineParser parser(argc, argv, "{@input | lena.jpg | input image}");
    Mat image = imread(imagePath);
    if (image.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        return;
    }
    Mat new_image = Mat::zeros(image.size(), image.type());
    // double alpha = 1.0; /*< Simple contrast control */
    // int beta = 0;       /*< Simple brightness control */
    //cout << " Basic Linear Transforms " << endl;
    //cout << "-------------------------" << endl;
    //cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    //cout << "* Enter the beta value [0-100]: ";    cin >> beta;
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) 
            {
                new_image.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }
    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
}

void ContrastEnhancer::ApplyClahe(const std::string& imagePath, const std::string& outputImagePath)
{
    Mat inputIm = imread(imagePath, IMREAD_GRAYSCALE); //input image

    Ptr<CLAHE> clahe = createCLAHE();
    // clahe->setClipLimit(20);
	clahe->setTilesGridSize(cv::Size(12, 12));

    Mat dstIm;
    clahe->apply(inputIm, dstIm);
    
    std::ifstream ifile;

    ifile.open(outputImagePath);
    if (ifile)
    {
        std::remove(outputImagePath.c_str());
    }
    cv::imwrite(outputImagePath, dstIm);
}

void ContrastEnhancer::ApplyClahe2FullImage(const std::string& imagePath, const std::string& outputImagePath, cv::Point tl, cv::Point br)
{
	Mat inputIm = imread(imagePath, IMREAD_GRAYSCALE); //input image

	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(100);
	// clahe->setTilesGridSize(cv::Size(40, 40));

	Mat dstIm;
	// clahe->apply(inputIm, dstIm);
	
	// START
	// cv::cvtColor(inputFrame, inputFrame, CV_BGR2GRAY);

	// Default
	//cv::Point outputTL(720, 327);
	//cv::Point outputBR(1383, 720);

	//cv::Point outputTL(1050, 468);
	//cv::Point outputBR(outputTL.x + 94, outputTL.y + 36);

	auto claheFrame = inputIm.clone()(Rect(tl, br));

	clahe->apply(claheFrame, claheFrame);


	// Region to replace
	// Mat claheSubMat = claheFrame(Rect(outputTL, outputBR));

	auto submat = inputIm(Rect(tl, br));

	claheFrame.copyTo(submat);

	inputIm.copyTo(dstIm);
	// END

	std::ifstream ifile;

	ifile.open(outputImagePath);

	if (ifile)
	{
		std::remove(outputImagePath.c_str());
	}

	cv::imwrite(outputImagePath, dstIm);
}

void ContrastEnhancer::CreateVideoFromImg(
	std::string& inputImPath, std::string& outputVideoPath, int FPS, int numberOfFrames)
{
	using namespace cv;

	// Output Video:
	VideoWriter outputVideo;

	Mat inputIm = imread(inputImPath, IMREAD_GRAYSCALE);

	Size sz = inputIm.size();

	outputVideo.open(outputVideoPath, VideoWriter::fourcc('M', 'P', '4', 'G'), FPS, sz, false);

	if (!outputVideo.isOpened())
	{
		std::cout << "Could not open the output video for write: " << outputVideoPath << std::endl;
		return;
	}

	auto currFrame = 1;
	while (currFrame <= numberOfFrames)
	{
		outputVideo << inputIm;
		currFrame++;
	}

	std::cout << "Done!" << std::endl;

	// Closes all the frames
	destroyAllWindows();
}

int ContrastEnhancer::ApplyClaheToVideo(std::string& inputVideoPath, 
	std::string& outputVideoPath,
	const int & claheFrameStart, 
	const int & claheFrameEnd, 
	const int & clipLimit)
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

	// Output Video:
	VideoWriter outputVideo;

	int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));

	Size sz = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	outputVideo.open(outputVideoPath, ex, cap.get(CAP_PROP_FPS), sz, false);

	if (!outputVideo.isOpened())
	{
		std::cout << "Could not open the output video for write: " << outputVideoPath << std::endl;
		return -1;
	}
	// Output Video end

	Ptr<CLAHE> clahe = createCLAHE();
	// clahe->setClipLimit(clipLimit);
	clahe->setTilesGridSize(cv::Size(40, 40));
	
	int frameNum = 0;

	while (1)
	{
		Mat inputFrame;

		// Capture frame-by-frame
		cap >> inputFrame;

		// If the frame is empty, break immediately
		if (inputFrame.empty())
			break;

		// std::cout << "Frame type is " << inputFrame.type() << std::endl;

		cv::cvtColor(inputFrame, inputFrame, CV_BGR2GRAY);

		auto claheFrame = inputFrame.clone();

		// Which frames to enhance contrast
		if (frameNum >= claheFrameStart && frameNum <= claheFrameEnd)
		{
			clahe->apply(claheFrame, claheFrame);

			// Default
			//cv::Point outputTL(720, 327);
			//cv::Point outputBR(1383, 720);

			cv::Point outputTL(1050,468);
			cv::Point outputBR(outputTL.x+94, outputTL.y+36);
			

			// Region to replace
			Mat claheSubMat = claheFrame(Rect(outputTL, outputBR));

			auto submat = inputFrame(Rect(outputTL, outputBR));

			claheSubMat.copyTo(submat);
		}

		outputVideo << inputFrame;

		// std::cout << "Frame size is " << inputFrame.size().width << "," << inputFrame.size().height <<  std::endl;
		// std::cout << "Frame number is " << frameNum <<  std::endl;

		frameNum++;
	}

	// When everything done, release the video capture object
	cap.release();

	std::cout << "Done!" <<  std::endl;

	// Closes all the frames
	destroyAllWindows();

	return 0;
}

int ContrastEnhancer::ApplyClaheToVideo_3Channels(std::string& inputVideoPath, std::string& outputVideoPath,
	const int& claheFrameStart, const int& claheFrameEnd,
	const int& clipLimit)
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



	// Output Video:
	VideoWriter outputVideo;

	int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));

	Size sz = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	outputVideo.open(outputVideoPath, ex, cap.get(CAP_PROP_FPS), sz, false);

	if (!outputVideo.isOpened())
	{
		std::cout << "Could not open the output video for write: " << outputVideoPath << std::endl;
		return -1;
	}
	// Output Video end

	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(clipLimit);

	int frameNum = 0;

	while (1)
	{
		Mat inputFrame;

		// Capture frame-by-frame
		cap >> inputFrame;

		// If the frame is empty, break immediately
		if (inputFrame.empty())
			break;

		// std::cout << "Frame type is " << inputFrame.type() << std::endl;

		cv::cvtColor(inputFrame, inputFrame, CV_BGR2GRAY);

		auto claheFrame = inputFrame.clone();

		// Which frames to enhance contrast
		if (frameNum >= claheFrameStart && frameNum <= claheFrameEnd)
		{
			clahe->apply(claheFrame, claheFrame);

			// Default
			//cv::Point outputTL(720, 327);
			//cv::Point outputBR(1383, 720);

			cv::Point outputTL(1050, 468);
			cv::Point outputBR(outputTL.x + 94, outputTL.y + 36);


			// Region to replace
			Mat claheSubMat = claheFrame(Rect(outputTL, outputBR));

			auto submat = inputFrame(Rect(outputTL, outputBR));

			claheSubMat.copyTo(submat);
		}

		outputVideo << inputFrame;

		// std::cout << "Frame size is " << inputFrame.size().width << "," << inputFrame.size().height <<  std::endl;
		// std::cout << "Frame number is " << frameNum <<  std::endl;

		frameNum++;
	}

	//while (1)
	//{
	//	Mat inputFrame;

	//	// Capture frame-by-frame
	//	cap >> inputFrame;

	//	// If the frame is empty, break immediately
	//	if (inputFrame.empty())
	//		break;

	//	// std::cout << "Frame type is " << inputFrame.type() << std::endl;

	//	cv::cvtColor(inputFrame, inputFrame, CV_BGR2Lab);

	//	// cv::Mat lab_planes;
	//	OutputArrayOfArrays lab_planes;
	//	cv::split(inputFrame, lab_planes);

	//	auto claheFrame = inputFrame.clone();

	//	// Which frames to enhance contrast
	//	if (frameNum >= claheFrameStart && frameNum <= claheFrameEnd)
	//	{
	//		clahe->apply(claheFrame, claheFrame);

	//		// Default
	//		//cv::Point outputTL(720, 327);
	//		//cv::Point outputBR(1383, 720);

	//		cv::Point outputTL(1050, 468);
	//		cv::Point outputBR(outputTL.x + 94, outputTL.y + 36);


	//		// Region to replace
	//		Mat claheSubMat = claheFrame(Rect(outputTL, outputBR));

	//		auto submat = inputFrame(Rect(outputTL, outputBR));

	//		claheSubMat.copyTo(submat);
	//	}

	//	outputVideo << inputFrame;

	//	// std::cout << "Frame size is " << inputFrame.size().width << "," << inputFrame.size().height <<  std::endl;
	//	// std::cout << "Frame number is " << frameNum <<  std::endl;

	//	frameNum++;
	//}

	// When everything done, release the video capture object
	cap.release();

	std::cout << "Done!" << std::endl;

	// Closes all the frames
	destroyAllWindows();

	return 0;
}