

#include "opencv-test_fn.h"
#include "ContrastEnhancer.h"
#include "CodeTesterV1.h"
#include "Tests1.h"
#include "SimpleEncryptionAndDecryption.h"

int main()
{
	// Testing static-ness.
	TestStaticness();

	// runOpenCVRandomRects();

	ContrastEnhancer lprCE;

	std::string lprImagePath = "D:/Repositories/OpenCV_Rect_Project/OpenCV_rectangle_project/x64/Release/increase contrasts.png";

	/*lprCE.ImproveContrast(3.0, -300, lprImagePath);*/
	 
	CodeTesterV1 codeTester;

	// Code Testing:
	int arr[] = { 1, 4, 2, 10, 2, 3, 1, 0, 20 };
	int k = 4;
	int n = sizeof(arr) / sizeof(arr[0]);
	
	// Code Testing 1.1:
	bool boola = true;
	bool boolb = false;
	bool boolc = false;

	cout << "Result of bool is: " << (boola && ( boolb || boolc)) << endl;

	// cout << maxSum(arr, n, k);
	// cout << "[T] sizeof(arr) is: " << sizeof(arr) << ", sizeof(arr[0]) is: "<<  sizeof(arr[0]) <<endl;
	codeTester.maxSum(arr, n , k);

	// Testing loop backwards
	auto sizeOfList = 5;
	auto index = sizeOfList - 1;

	for (; index >= 0; index--)
	{
		if (index == 2)
			break;
	}
	cout << "the index is now: " << index << endl;

	// ----- Test 1 
	Shared::Test1_EncryptSomeTextAndPrint();

	Shared::Test1_EncryptSomeTextAndPrint_V2();

	Shared::Test1_EncryptImage1();

	Shared::Test2_BlurImage1();
	
	// Shared::Test1_DecryptSomeTextAndPrint();

	cout << "Size of int is: " << sizeof(int) << endl;

	// --- Editing video
	//auto vidPath  = std::string("X:/Projects/Aus/VatesEDG/AutoTesting/_WIP/SingleStream_UpdatedLPRInfo_CheckHigherPlateConfidence/bay2_output.mp4");
	//auto outputVidPath = std::string("X:/Projects/Aus/VatesEDG/AutoTesting/_WIP/SingleStream_UpdatedLPRInfo_CheckHigherPlateConfidence/bay2_output_blacked.mp4");

	//Shared::CaptureVideoAndAddBlackRectangle(vidPath, outputVidPath);

	// --- Editing Video ENd
	
	// --- Contrast enhancing
	//auto inputImPath = std::string("Y:/Projects/EDG/Manly_Vale/Low_Contrast_Plate/Recording_20220518_193640_3132.mp4");
	//auto outputImPath = std::string("D:/Task_Files/ContrastEnhancing/test5_enhanced.mp4");

	//// --- Contrast enhancing
	//lprCE.ApplyClaheToVideo(inputImPath, outputImPath, 70, 700, 4);

	//auto inputImPath1 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/LaneCove_back-20220429_100859_03.mp4_20221220_190914.489.bmp");
	// auto inputImPath1 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/LaneCove_back-20220429_100859_03.mp4_20221220_190914.489.bmp");
	auto inputImPath1 = std::string("D:/Software/PotPlayer/Capture/1_back-20220429_100859_03.mp4_20230113_170652.852.bmp");
	auto outputImPath1 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im1.png");

	// auto inputImPath2 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/LaneCove_back-20220511_100847_09.mp4_20221220_190807.307.bmp");
	auto inputImPath2 = std::string("D:/Software/PotPlayer/Capture/2_back-20220511_100847_09.mp4_20230113_170027.bmp");
	auto outputImPath2 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im2.png");

	//auto inputImPath3 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/ManlyVale_20220518_193640_409.mp4_20221220_181828.358.bmp");
	auto inputImPath3 = std::string("D:/Software/PotPlayer/Capture/3_PlateLowContrast_ManlyVale_20220518_193640_409.mp4_20230113_170450.494.bmp");
	auto outputImPath3 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im3.png");

	//auto inputImPath4 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/ManlyVale_Recording_20220429_020906_346.mp4_20221221_115820.bmp");
	auto inputImPath4 = std::string("D:/Software/PotPlayer/Capture/4_Recording_20220429_020906_346.mp4_20230113_170611.457.bmp");
	auto outputImPath4 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im4.png");

	//auto inputImPath5 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/ManlyVale_Recording_20220518_193640_3132.mp4_20221220_180334.947.bmp");
	auto inputImPath5 = std::string("D:/Software/PotPlayer/Capture/5_Recording_20220518_193640_3132.mp4_20230113_170214.360.bmp");
	auto outputImPath5 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im5.png");

	//auto inputImPath6 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/ManlyVale_Recording_20220518_193640_3146.mp4_20221220_181316.053.bmp");
	auto inputImPath6 = std::string("D:/Software/PotPlayer/Capture/6_Recording_20220518_193640_3146.mp4_20230113_170241.373.bmp");
	auto outputImPath6 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im6.png");

	//auto inputImPath7 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/ManlyVale_Recording_20220610_183254_123_1.mp4_20221220_181659.636.bmp");
	auto inputImPath7 = std::string("D:/Software/PotPlayer/Capture/7_Recording_20220610_183254_123_1.mp4_20230113_170321.388.bmp");
	auto outputImPath7 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im7.png");

	//auto inputImPath8 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/ManlyVale_Recording_20220610_183254_123_2.mp4_20221220_181742.952.bmp");
	auto inputImPath8 = std::string("D:/Software/PotPlayer/Capture/8_Recording_20220610_183254_123_2.mp4_20230113_170410.943.bmp");
	auto outputImPath8 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im8.png");

	//auto inputImPath9 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/RouseHills_1524_20221210151012_47_video_152.mp4_20221220_182057.bmp");
	auto inputImPath9 = std::string("D:/Software/PotPlayer/Capture/9_1524_20221210151012_47_video_152.mp4_20230113_170520.221.bmp");
	auto outputImPath9 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im9.png");

	//auto inputImPath10 = std::string("C:/Users/wtchin/OneDrive - Hendricks Corp. Pte. Ltd/lowContrastPlates/testing/RouseHills_1524_20221211183651_113.mp4_20221220_182131.bmp");
	auto inputImPath10 = std::string("D:/Software/PotPlayer/Capture/10_1524_20221211183651_113.mp4_20230113_170541.912.bmp");
	auto outputImPath10 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/im10.png");

	lprCE.ApplyClahe2FullImage(inputImPath1, outputImPath1, cv::Point(1148,359),cv::Point(1252,398));
	lprCE.ApplyClahe2FullImage(inputImPath2, outputImPath2, cv::Point(549,536),cv::Point(645,583));
	lprCE.ApplyClahe2FullImage(inputImPath3, outputImPath3, cv::Point(1112,456), cv::Point(1190,482));
	//lprCE.ApplyClahe2FullImage(inputImPath4, outputImPath4, cv::Point(, ), cv::Point(, ));
	//lprCE.ApplyClahe2FullImage(inputImPath5, outputImPath5, cv::Point(, ), cv::Point(, ));

	//lprCE.ApplyClahe2FullImage(inputImPath6, outputImPath6, cv::Point(, ), cv::Point(, ));
	//lprCE.ApplyClahe2FullImage(inputImPath7, outputImPath7, cv::Point(, ), cv::Point(, ));
	//lprCE.ApplyClahe2FullImage(inputImPath8, outputImPath8, cv::Point(, ), cv::Point(, ));
	//lprCE.ApplyClahe2FullImage(inputImPath9, outputImPath9, cv::Point(, ), cv::Point(, ));
	//lprCE.ApplyClahe2FullImage(inputImPath10, outputImPath10, cv::Point(,), cv::Point(, ));

	auto outputVid_1 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/vid1.mp4");
	auto outputVid_2 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/vid2.mp4");
	auto outputVid_3 = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/vid3.mp4");

	lprCE.CreateVideoFromImg(outputImPath1, outputVid_1, 10, 150);
	lprCE.CreateVideoFromImg(outputImPath2, outputVid_2, 10, 150);
	lprCE.CreateVideoFromImg(outputImPath3, outputVid_3, 10, 150);

	auto inputIm_GoodOne = std::string("D:/Software/PotPlayer/Capture/GoodOne.bmp");
	auto outputVid_GoodOne = std::string("D:/Task_Files/ContrastEnhancing/CLAHE/GoodOne.mp4");

	lprCE.CreateVideoFromImg(inputIm_GoodOne, outputVid_GoodOne, 10, 150);


	return 0;
}

void runOpenCVRandomRects()
{
	Mat image1 = imread("C:/Projects/opencv-test_files/Img1.png");
	Mat image2 = imread("C:/Projects/opencv-test_files/Img2.png");
	rect_node* list1 = NULL;
	bool fn1_success = fn1_random_rectangles(image1, list1);
	rect_node* data = nullptr;

	if (fn1_success)
	{
		data = fn2_rect_largest_area(image1, list1);
		if (data->rect.tl().x == 0 && data->rect.tl().y == 0 && data->rect.br().x == 0 && data->rect.br().y == 0)
		{
			cout << "No intersections found! " << endl;
		}
		else
		{
			fn3_draw_rectangle_s(image1, data);
		}
	}
	//resize(image1, image1, Size(1920,1080));
	imshow("Display Window", image1);
	waitKey(0);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
