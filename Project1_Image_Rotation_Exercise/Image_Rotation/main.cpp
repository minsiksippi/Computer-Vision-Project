#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat problem_a_rotate_forward(cv::Mat img, double angle) {
	cv::Mat output;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////

	float newAngle = 90.0 + angle;
	float absAngle = abs(angle);
	double cosA = cos(newAngle * CV_PI / 180.0);
	double sinA = sin(newAngle * CV_PI / 180.0);

	int len, outRow, outCol;
	int CenterRow, CenterCol;
	int Center_outputRow, Center_outputCol;
	int outHeight = img.rows - 1;

	CenterRow = (int)img.rows / 2;
	CenterCol = (int)img.cols / 2;

	outRow = (int)(img.rows * cos(absAngle * CV_PI / 180) + img.cols * sin(absAngle * CV_PI / 180));
	outCol = (int)(img.rows * sin(absAngle * CV_PI / 180) + img.cols * cos(absAngle * CV_PI / 180));
	outRow = abs(outRow);
	outCol = abs(outCol);

	if (outRow >= outCol) len = outRow;
	else len = outCol;

	output.create(outRow, outCol, img.type());
	output.setTo(0);

	Center_outputRow = (int)(output.rows / 2);
	Center_outputCol = (int)(output.cols / 2);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int newX = (int)((j - CenterCol) * cosA + (outHeight - i - CenterRow) * -sinA);
			int newY = (int)((j - CenterCol) * sinA + (outHeight - i - CenterRow) * cosA);
			newX = newX + Center_outputRow;
			newY = newY + Center_outputCol;

			if (newY < 0 || newY >= len || newX < 0 || newX >= len) continue;
			else
			{
				if (img.channels() == 1)
				{
					output.at<uchar>(newX, newY) = img.at<uchar>(i, j);
				}
				else if (img.channels() == 3)
				{
					output.at<cv::Vec3b>(newX, newY)[0] = img.at<cv::Vec3b>(i, j)[0];
					output.at<cv::Vec3b>(newX, newY)[1] = img.at<cv::Vec3b>(i, j)[1];
					output.at<cv::Vec3b>(newX, newY)[2] = img.at<cv::Vec3b>(i, j)[2];
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("a_output", output); 
	cv::waitKey(0);
	return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle) {
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////

	float newAngle = 90.0 - angle;
	float absAngle = abs(angle);
	double cosA = cos(newAngle * CV_PI / 180.0);
	double sinA = sin(newAngle * CV_PI / 180.0);

	int outRow, outCol, outHeight;
	int CenterCol, CenterRow;
	int Center_outputRow, Center_outputCol;
	
	outRow = (int)(img.rows * cos(absAngle * CV_PI / 180) + img.cols * sin(absAngle * CV_PI / 180));
	outCol = (int)(img.rows * sin(absAngle * CV_PI / 180) + img.cols * cos(absAngle * CV_PI / 180));

	CenterRow = (int)img.rows / 2;
	CenterCol = (int)img.cols / 2;

	output.create(outRow, outCol, img.type());
	output.setTo(0);

	outHeight = output.rows - 1;

	Center_outputRow = (int)(output.rows / 2);
	Center_outputCol = (int)(output.cols / 2);

	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			int newX = (int)((j - Center_outputCol) * cosA + ((outHeight - i) - Center_outputRow) * -sinA);
			int newY = (int)((j - Center_outputCol) * sinA + ((outHeight - i) - Center_outputRow) * cosA);

			newX = (newX + CenterRow);
			newY = (newY + CenterCol);

			if (newY < 0 || newY >= img.cols || newX < 0 || newX >= img.rows) continue;
			else
			{
				if (img.channels() == 1)
				{
					output.at<uchar>(i, j) = img.at<uchar>(newX, newY);
				}
				else if (img.channels() == 3)
				{
					output.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(newX, newY)[0];
					output.at<cv::Vec3b>(i, j)[1] = img.at<cv::Vec3b>(newX, newY)[1];
					output.at<cv::Vec3b>(i, j)[2] = img.at<cv::Vec3b>(newX, newY)[2];
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("b_output", output); 
	cv::waitKey(0);
	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle) {
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	cv::Mat BImage;

	float newAngle = 90.0 - angle;

	double cosA = cos(newAngle * CV_PI / 180.0);
	double sinA = sin(newAngle * CV_PI / 180.0);
	double firstI, firstJ, secondI, secondJ;
	double ps1, ps2, ps3, ps4;

	int outRow, outCol, outHeight;
	int CenterCol, CenterRow;
	int Center_outputRow, Center_outputCol;

	CenterRow = (int)img.rows / 2;
	CenterCol = (int)img.cols / 2;

	float absAngle = abs(angle);
	outRow = (int)(img.rows * cos(absAngle * CV_PI / 180) + img.cols * sin(absAngle * CV_PI / 180));
	outCol = (int)(img.rows * sin(absAngle * CV_PI / 180) + img.cols * cos(absAngle * CV_PI / 180));


	BImage.create(outRow, outCol, img.type());
	BImage.setTo(0);
	output.create(outRow, outCol, img.type());
	output.setTo(0);

	outHeight = BImage.rows - 1;
	
	Center_outputRow = (int)(BImage.rows / 2);
	Center_outputCol = (int)(BImage.cols / 2);

	for (int i = 0;i < BImage.rows; i++)
	{
		for (int j = 0; j < BImage.cols; j++)
		{
			int newX = (int)((j - Center_outputCol) * cosA + ((outHeight - i) - Center_outputRow) * -sinA);
			int newY = (int)((j - Center_outputCol) * sinA + ((outHeight - i) - Center_outputRow) * cosA);

			newX = (newX + CenterRow);
			newY = (newY + CenterCol);

			if (newY < 0 || newY >= img.cols || newX < 0 || newX >= img.rows) continue;
			else
			{
				if (img.channels() == 1)
				{
					BImage.at<uchar>(i, j) = img.at<uchar>(newX, newY);
				}
				else if (img.channels() == 3)
				{
					BImage.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(newX, newY)[0];
					BImage.at<cv::Vec3b>(i, j)[1] = img.at<cv::Vec3b>(newX, newY)[1];
					BImage.at<cv::Vec3b>(i, j)[2] = img.at<cv::Vec3b>(newX, newY)[2];
				}
			}
		}
	}

	output = BImage.clone();
	for (int i = 0; i < output.rows - 1; i++)
	{
		for (int j = 0; j < output.cols - 1; j++)
		{
			firstI = (double)i / ((double)output.cols);
			secondI = 1.0 - firstI;
			firstJ = (double)j / ((double)output.rows);
			secondJ = 1.0 - firstJ;
			
			ps1 = secondJ * secondI;
			ps2 = firstJ * secondI;
			ps3 = secondJ * firstI;
			ps4 = firstJ * firstI;

			if (BImage.channels() == 1)
			{
				uchar P1 = BImage.at<uchar>(i, j);
				uchar P2 = BImage.at<uchar>(i, j + 1);
				uchar P3 = BImage.at<uchar>(i + 1, j);
				uchar P4 = BImage.at<uchar>(i + 1, j + 1);
				output.at<uchar>(i, j) = ps1 * P1 + ps2 * P2 + ps3 * P3 + ps4 * P4;
			}
			else if (BImage.channels() == 3)
			{
				cv::Vec3b P1 = BImage.at<cv::Vec3b>(i, j);
				cv::Vec3b P2 = BImage.at<cv::Vec3b>(i, j + 1);
				cv::Vec3b P3 = BImage.at<cv::Vec3b>(i + 1, j);
				cv::Vec3b P4 = BImage.at<cv::Vec3b>(i + 1, j + 1);
				output.at<cv::Vec3b>(i, j) = ps1 * P1 + ps2 * P2 + ps3 * P3 + ps4 * P4;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("c_output", output); 
	cv::waitKey(0);

	return output;
}

cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y) {
	/*
	img : input image
	num : number for brightness (increase or decrease)
	x : x coordinate of image (for square part)
	y : y coordinate of image (for square part)

	*/
	cv::Mat output = img.clone();
	int size = 100;
	int height = (y + 100 > img.cols) ? img.cols : y + 100;
	int width = (x + 100 > img.rows) ? img.rows : x + 100;

	for (int i = x; i < width; i++)
	{
		for (int j = y; j < height; j++)
		{
			for (int c = 0; c < img.channels(); c++)
			{
				int t = img.at<cv::Vec3b>(i, j)[c] + num;
				output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
			}
		}

	}
	cv::imshow("output1", img);
	cv::imshow("output2", output);
	cv::waitKey(0);
	return output;
}

int main(void) {

	double angle = 45.0f;

	cv::Mat input = cv::imread("lena.jpg");
	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
	//Example how to access pixel value, change params if you want
	//Example_change_brightness(input, 100, 50, 125);
}
