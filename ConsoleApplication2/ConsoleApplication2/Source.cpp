#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Function to detect and draw at faces area
void detectAndDraw(Mat& img, Mat& filter, CascadeClassifier& cascade, double scale)
{
	vector<Rect> faces;	// Vector for storing detected faces 
	Mat gray, newFil;
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
	imshow("Face Detector Module", img); // Display image on the chosen window
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
	filter = imread("C:/Users/TANIT/source/repos/Face detection 01/ConsoleApplication2/ConsoleApplication2/TestSample/test04.jpg");

	// Uncomment this to detect faces from saved video
	//VideoCapture cap("C:/Users/TANIT/source/repos/ConsoleApplication2/ConsoleApplication2/Wildlife.mp4");

	VideoCapture cap(0); // Open the default webcam.

	// Check for failure
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the webcam" << endl;
		cin.get(); // Wait for key press
		return -1;
	}
	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
	cout << "Resolution of video: " << dWidth << "x" << dHeight << endl;

	int frame_width = static_cast<int>(dWidth);
	int frame_height = static_cast<int>(dHeight);

	Size frame_size(frame_width, frame_height);
	int frame_per_second = 10;

	// Create and initialize VideoWriter obj
	VideoWriter oVid("D:/VideoFile/recording01.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), frame_per_second, frame_size, true);

	// Check for failure in initializing VideoWriter obj
	if (oVid.isOpened() == false)
	{
		cout << "Fail to save the video to file" << endl;
		cin.get();
		return -1;
	}

	//cap.set(CAP_PROP_POS_MSEC, 300);
	//double fps = cap.get(CAP_PROP_FPS);
	//cout << "Frames per second(FPS): " << fps << endl;

	String windowName = "My Camera Feed";
	//namedWindow(windowName, WINDOW_NORMAL);
	//namedWindow(windowName);

	while (true)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // Read new frame from video recording

		// Breaking the while loop if the frame can no longer be captured
		if (bSuccess == false)
		{
			cout << "Webcam is disconnected" << endl;
			break;
		}

		oVid.write(frame);
		//imshow(windowName, frame);
		detectAndDraw(frame, filter, cascade, scale); // Function to detect faces and draw at that location


		// If 'Esc' is pressed within 10ms, break the loop.
		if (waitKey(10) == 27)
		{
			cout << "Esc key pressed. Stopping the recording" << endl;
			break;
		}
		
	
	}
	oVid.release();
	//detectAndDraw(frame, filter, cascade, scale);
	//waitKey(0);
	cout << "Program completed successfully" << endl;
	return 0;
}