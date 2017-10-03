#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>


void salt(cv::Mat &image, int n);
void sharpen(const cv::Mat &image, cv::Mat &result);
void canny(cv::Mat& img, cv::Mat& out);
void nothing(cv::Mat& img, cv::Mat& out);
void saltVid(cv::Mat &image1, cv::Mat &image2);
void logoVid(cv::Mat &image1, cv::Mat &image2);
void HLSVid(cv::Mat &image1, cv::Mat &image2);
void equalHistVid(cv::Mat &image1, cv::Mat &image2);
void blurVid(cv::Mat &image1, cv::Mat &image2);
void sobelVid(cv::Mat &image1, cv::Mat &image2);
void laplaceVid(cv::Mat &image1, cv::Mat &image2);
void sharpenVid(cv::Mat &image, cv::Mat &result);
void dilateVid(cv::Mat &image1, cv::Mat &image2);
void erodeVid(cv::Mat &image1, cv::Mat &image2);
void openVid(cv::Mat &image1, cv::Mat &image2);
void closeVid(cv::Mat &image1, cv::Mat &image2);
void houghCircleVid(cv::Mat &image1, cv::Mat &image2);
void fastVid(cv::Mat &image1, cv::Mat &image2);
void harrisVid(cv::Mat &image1, cv::Mat &image2);


#endif // FUNCTIONS_H
