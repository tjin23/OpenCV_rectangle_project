

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
	auto vidPath  = std::string("X:/Projects/Aus/VatesEDG/AutoTesting/_WIP/SingleStream_UpdatedLPRInfo_CheckHigherPlateConfidence/bay2_output.mp4");
	
	auto outputVidPath = std::string("X:/Projects/Aus/VatesEDG/AutoTesting/_WIP/SingleStream_UpdatedLPRInfo_CheckHigherPlateConfidence/bay2_output_blacked.mp4");

	Shared::CaptureVideoAndAddBlackRectangle(vidPath, outputVidPath);

	// --- Editing Video ENd
	
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
