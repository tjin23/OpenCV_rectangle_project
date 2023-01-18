#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

class ContrastEnhancer
{
public :
    void ImproveContrast(const double& alpha, const int& beta, const std::string& imagePath);

    void ApplyClahe(const std::string& imagePath, const std::string& outputImagePath);

    void ApplyClahe2FullImage(const std::string& imagePath, const std::string& outputImagePath, cv::Point tl, cv::Point br);

    int ApplyClaheToVideo(std::string& inputVideoPath, std::string& outputVideoPath, 
        const int& claheFrameStart, const int& claheFrameEnd, 
        const int& clipLimit);

    int ApplyClaheToVideo_3Channels(std::string& inputVideoPath, std::string& outputVideoPath,
        const int& claheFrameStart, const int& claheFrameEnd,
        const int& clipLimit);

    void CreateVideoFromImg(
        std::string& inputImPath, std::string& outputVideoPath, int FPS, int numberOfFrames);
};