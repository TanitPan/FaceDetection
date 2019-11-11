//#include "opencv2/opencv.hpp"
////#include "opencv2/objdetect.hpp"
////#include "opencv2/highgui.hpp"
////#include "opencv2/imgproc.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//
//void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale)
//{
//	vector<Rect> faces;
//	Mat gray;
//	cvtColor(img, gray, COLOR_BGR2GRAY);
//	cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//	for (size_t i = 0; i < faces.size(); i++)
//	{
//
//		Rect r = faces[i];
//		Scalar color = Scalar(255, 0, 0);
//		rectangle(img, cv::Point(cvRound(r.x * scale), cvRound(r.y * scale)), cv::Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), color, 3, 8, 0);
//	}
//	imshow("Face Detector Module", img);
//	cout << faces.size() << endl;
//
//}
//
//int main()
//{
//	CascadeClassifier cascade;
//	Mat frame = imread("combo08.jpg");
//	double scale = 1;
//	//cascade.load("..\..\haarcascade_frontalcatface.xml");
//	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");
//
//
//	//imshow("Face Detection", frame);
//	if (frame.empty())
//	{
//		cout << "failed to open or find lena.jpg" << endl;
//		return -1;
//	}
//	else
//		cout << "lena.jpg loaded ok" << endl;
//
//	detectAndDraw(frame, cascade, scale);
//	waitKey(0);
//	return 0;
//}

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void detectAndDraw(Mat& img, Mat& filter, CascadeClassifier& cascade, double scale)
{
	vector<Rect> faces;
	Mat gray,newFil;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Scalar color = Scalar(0, 0, 255);
		rectangle(img, cv::Point(cvRound(r.x * scale), cvRound(r.y * scale)), cv::Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), color, 3, 8, 0);
		resize(filter, newFil, Size(r.width, r.height), 0, 0, INTER_LINEAR);
		//filter.copyTo(img(Rect(r.x*scale, r.y*scale, filter.cols, filter.rows)));
		newFil.copyTo(img(Rect(r.x * scale, r.y * scale, newFil.cols, newFil.rows)));
		
	}
	imshow("Face Detector Module", img);
	cout << faces.size() << endl;

}


int main(int argc, char** argv)
{
	Mat filter;
	//Mat frame;
	//frame = imread("combo08.jpg");
	CascadeClassifier cascade;
	double scale = 1;
	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");
	//VideoCapture cap("C:/Users/TANIT/source/repos/ConsoleApplication2/ConsoleApplication2/Wildlife.mp4");
	filter = imread("C:/Users/TANIT/source/repos/ConsoleApplication2/ConsoleApplication2/test04.jpg");
	VideoCapture cap(0);
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the web camera" << endl;
		cin.get();
		return -1;
	}
	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
	cout << "Resolution of video: " << dWidth << "x" << dHeight << endl;


	//cap.set(CAP_PROP_POS_MSEC, 300);
	//double fps = cap.get(CAP_PROP_FPS);
	//cout << "Frames per second(FPS): " << fps << endl;

	String windowName = "My Camera Feed";
	//namedWindow(windowName, WINDOW_NORMAL);
	//namedWindow(windowName);

	while (true)
	{
		Mat frame;
		bool bSuccess = cap.read(frame);

		if (bSuccess == false)
		{
			cout << "End of video reached" << endl;
			break;
		}

		//imshow(windowName, frame);
		detectAndDraw(frame, filter, cascade, scale);
		if (waitKey(10) == 27)
		{
			cout << "Esc key pressed. Stopping the video" << endl;
			break;
		}
		
	
	}
	//detectAndDraw(frame, filter, cascade, scale);
	//waitKey(0);
	cout << "Program completed successfully" << endl;
	return 0;
}