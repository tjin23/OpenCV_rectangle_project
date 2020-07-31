

#include "opencv-test_fn.h"

int main()
{
	Mat image1 = imread("C:/Projects/opencv-test_files/Img1.png");
	Mat image2 = imread("C:/Projects/opencv-test_files/Img2.png");
	rect_node* list1 = NULL;
	bool fn1_success = fn1_random_rectangles(image1, list1);
	rect_node* data = nullptr;

	if (fn1_success)
	{	
		data =  fn2_rect_largest_area(image1, list1);
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
	return 0;
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
