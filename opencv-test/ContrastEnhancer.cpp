#include "ContrastEnhancer.h"

using std::cin;
using std::cout;
using std::endl;

void LPRContrastEnhancer::ImproveContrast(const double & alpha, const int & beta, const std::string & imagePath)
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