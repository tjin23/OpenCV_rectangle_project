#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

class LPRContrastEnhancer
{
public :
    void ImproveContrast(const double& alpha, const int& beta, const std::string& imagePath);
};