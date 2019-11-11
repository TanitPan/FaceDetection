//#include "opencv2/opencv.hpp"
//#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
#include <iostream>




void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale)
{
	vector<Rect> faces;
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{

		Rect r = faces[i];
		Scalar color = Scalar(255, 0, 0);
		rectangle(img, cv::Point(cvRound(r.x * scale), cvRound(r.y * scale)), cv::Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), color, 3, 8, 0);
	}
	imshow("Face Detector Module", img);
	cout << faces.size() << endl;

}

int main()
{
	CascadeClassifier cascade;
	Mat frame = imread("combo08.jpg");
	double scale = 1;
	//cascade.load("..\..\haarcascade_frontalcatface.xml");
	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");


	//imshow("Face Detection", frame);
	if (frame.empty())
	{
		cout << "failed to open or find lena.jpg" << endl;
		return -1;
	}
	else
		cout << "lena.jpg loaded ok" << endl;

	detectAndDraw(frame, cascade, scale);
	waitKey(0);
	return 0;
}