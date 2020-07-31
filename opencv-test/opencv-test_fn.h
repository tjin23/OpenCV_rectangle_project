#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace cv;
using namespace std;


struct rect_node
{
	Rect rect;
	rect_node* next;
	rect_node(Point tl, Point br) : rect(Rect(tl,br)), next(nullptr) {}
};

/*
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

bool fn1_random_rectangles(Mat image, rect_node * &list1)
{
	cv::Size sz = image.size();
	int imageWidth = sz.width;
	int imageHeight = sz.height;
	srand((unsigned)time(0));
	int n = 0, start_values = 0, rect_x, rect_y;

	cout << "Enter 'N', the number of random rectangles to be generated." << endl;
	cin >> n;

	if (n < 0)
	{
		cout << "Entered negative value. Program exiting.";
		return false;
	}
	cout << "N = " << n << " chosen. " << endl;

	// Random starting values : 
	rect_node* tail = nullptr;
	for (int i = 0; i < n; i++)
	{
		int sp_x = rand() % imageWidth;
		int sp_y = rand() % imageHeight;

		int ep_x = sp_x + rand() % (imageWidth - sp_x);
		int ep_y = sp_y + rand() % (imageHeight - sp_y);

		Point start_point;
		start_point.x = (unsigned)sp_x;
		start_point.y = (unsigned)sp_y;

		Point end_point;
		end_point.x = (unsigned)ep_x;
		end_point.y = (unsigned)ep_y;

		rect_node * new_node = new rect_node(start_point, end_point);
		if (i == 0)
		{
			list1 = new_node; //head = new_node;
			tail = new_node;
			//delete new_node; // dont simply delete nodes. We need to use these nodes!
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
			//delete new_node; // dont simply delete nodes. We need to use these nodes!
		}
	}
	return true;
}

rect_node* fn2_rect_largest_area(Mat image,rect_node * &list1)
{
	rect_node* tail = nullptr;
	tail = list1;
	// placehold for error handling.
	Point placehold;
	placehold.x = 0;
	placehold.y = 0;
	rect_node* placeholder = new rect_node(placehold, placehold);
	//rect_node* placeholder = rect_node(placehold, placehold);
	if (list1 == nullptr)
	{
		cout << "Failed! List is invalid! " << endl;
		return placeholder;
	}
	int ix = 0;
	int max_area = 0;

	// assuming threshold is not required. Since img1 and img2 are black and white
	Mat greyscale;
	cvtColor(image, greyscale, cv::COLOR_BGR2GRAY);
	Mat dst;
	double threshold_level = 250;
	double maxval = 255;
	// T
	threshold(greyscale, dst, threshold_level, maxval, THRESH_BINARY_INV);

	vector<vector <Point>> contours;
	findContours(dst, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	// Find the top left and bottom right points in black rectangle.
	Point black_rect_tl;
	Point black_rect_br;

	Size sz = image.size();
	//starting values at extremes. 
	black_rect_tl.x = sz.width;
	black_rect_tl.y = sz.height;
	black_rect_br.x = 0;
	black_rect_br.y = 0;

	for(int i = 0; i < contours[0].size();i++)
	{
		// Find the top left corner and bottom right corner.
		cout<<"point : "<< i <<  endl;
		cout<<contours[0][i]<<endl;
		//find top left corner
		if (contours[0][i].x < black_rect_tl.x)
		{
			black_rect_tl.x = contours[0][i].x;
		}
		if (contours[0][i].y < black_rect_tl.y)
		{
			black_rect_tl.y = contours[0][i].y;
		}
		// find bottom right corner
		if (contours[0][i].x > black_rect_br.x)
		{
			black_rect_br.x = contours[0][i].x;
		}
		if (contours[0][i].y > black_rect_br.y)
		{
			black_rect_br.y = contours[0][i].y;
		}
	}
	cout << "Black rect top left : " << black_rect_tl.x << "," << black_rect_tl.y << endl;
	cout << "Black rect bot right: " << black_rect_br.x << "," << black_rect_br.y << endl;

	//rect_node* node = new rect_node(placehold, placehold);
	rect_node* tail2 = placeholder;
	while (tail != nullptr)
	{
		//cout << "current rectangle id :" << ix++ << endl;
		//uncomment below rectangle() to print all random rectangles in blue.
		//rectangle(image, tail->rect, Scalar(255, 0, 0));
		int dx = min(tail->rect.br().x, black_rect_br.x) - max(tail->rect.tl().x, black_rect_tl.x);
		int dy = min(tail->rect.br().y, black_rect_br.y) - max(tail->rect.tl().y, black_rect_tl.y);
		// no intersection means dx or dy negative.
		
		if (dy >= 0 && dx >= 0)
		{
			if (dx * dy > max_area)
			{
				// delete all subsequent nodes where same area was stored.
				if (placeholder->next != nullptr)
				{
					rect_node* current = placeholder->next;
					rect_node* next = nullptr;
					while (current != nullptr)
					{
						cout << "Deleting..." << endl;
						next = current->next;
						delete current;
						current = next;
					}
				}
				max_area = dx * dy;
				placeholder->rect = Rect(tail->rect.tl(),tail->rect.br());
				tail2 = placeholder;
			}
			else if(dx * dy == max_area && max_area != 0)
			{
				cout << "same max area detected. Area is : " << dx * dy << endl;
				rect_node* new_ret_node = new rect_node(tail->rect.tl(),tail->rect.br());
				tail2->next = new_ret_node;
				tail2 = new_ret_node;
			}
		}
		tail = tail->next;
	}
	return placeholder;
}

void fn3_draw_rectangle_s(Mat image, rect_node*& list1)
{
	//cout << "enter fn 3! " << endl;
	rect_node* current = list1;
	while (current != nullptr)
	{
		cout << "Printing rectangle.. " << endl;
		rectangle(image, current->rect, Scalar(0, 0, 255));
		current = current->next;
	}
}
