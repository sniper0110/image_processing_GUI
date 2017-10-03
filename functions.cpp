#include "functions.h"


void salt(cv::Mat &image, int n) {
    for (int k=0; k<n; k++) {
    // rand() is the MFC random number generator
    // try qrand() with Qt
    int i= rand()%image.cols;
    int j= rand()%image.rows;
    if (image.channels() == 1) { // gray-level image
         image.at<uchar>(j,i)= 255;
    }
    else if (image.channels() == 3) { // color image

    image.at<cv::Vec3b>(j,i)[0]= 255;
    image.at<cv::Vec3b>(j,i)[1]= 255;
    image.at<cv::Vec3b>(j,i)[2]= 255;
    }
  }
}

void saltVid(cv::Mat &image1, cv::Mat &image2){
    int n=1000;
    image2 = image1;
    salt(image2, n);
}

void logoVid(cv::Mat &image1, cv::Mat &image2){
    //outputImage = inputImage;
    image2 = image1;
    cv::Mat logo = cv::imread("logo.jpeg");
    // to contain resized image
    cv::resize(logo,logo,
    cv::Size(logo.cols/3,logo.rows/3)); // 1/3 resizing
    // define image ROI
    cv::Mat imageROI;
    imageROI= image2(cv::Rect(image2.cols-10-logo.cols,10,logo.cols,logo.rows));
    // add logo to image
    cv::addWeighted(imageROI,1.0,logo,1,0.,imageROI);

}

void HLSVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::cvtColor(image2, image2, CV_BGR2HLS);
}

void equalHistVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::cvtColor(image2, image2, CV_BGR2GRAY);
    cv::equalizeHist(image2, image2);
}

void blurVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::blur(image2,image2,cv::Size(5,5));
}

void sobelVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::Sobel(image2,image2, CV_8U,1,0,3,0.4,128); // X direction
    cv::Sobel(image2,image2, CV_8U,0,1,3,0.4,128); // THEN Y direction
}

void laplaceVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::Laplacian(image2, image2, CV_32F, 3);
}

void sharpenVid(cv::Mat &image, cv::Mat &result){
    result.create(image.size(), image.type());
    for (int j= 1; j<image.rows-1; j++) { // for all rows
        // (except first and last)
      const uchar* previous=image.ptr<const uchar>(j-1); // previous row
      const uchar* current=image.ptr<const uchar>(j);
      // current row
      const uchar* next=image.ptr<const uchar>(j+1); // next row
      uchar* output= result.ptr<uchar>(j); // output row
      for (int i=1; i<image.cols-1; i++) {
         *output++= cv::saturate_cast<uchar>(
         5*current[i]-current[i-1]
         -current[i+1]-previous[i]-next[i]);
      }
    }
    // Set the unprocess pixels to 0
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}

void dilateVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::dilate(image2,image2,cv::Mat());
}

void erodeVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::erode(image2,image2,cv::Mat());
}

void openVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::Mat element5(5,5,CV_8U,cv::Scalar(1));
    cv::morphologyEx(image2,image2,cv::MORPH_OPEN,element5);
}

void closeVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::Mat element5(5,5,CV_8U,cv::Scalar(1));
    cv::morphologyEx(image2,image2,cv::MORPH_CLOSE,element5);
}

void houghCircleVid(cv::Mat &image1, cv::Mat &image2){
    image2=image1;
    cv::cvtColor(image2, image2, CV_BGR2GRAY);
    cv::GaussianBlur(image2,image2,cv::Size(5,5),1.5);
    std::vector<cv::Vec3f> circles;

    cv::HoughCircles(image2, circles, CV_HOUGH_GRADIENT,
    2,
    // accumulator resolution (size of the image / 2)
    50, // minimum distance between two circles
    200, // Canny high threshold
    100, // minimum number of votes
    5, 100); // min and max radius
    std::vector<cv::Vec3f>::
    const_iterator itc= circles.begin();
    while (itc!=circles.end()) {
    cv::circle(image2,
    cv::Point((*itc)[0], (*itc)[1]), // circle centre
    (*itc)[2],
    // circle radius
    cv::Scalar(0), // color
    2);
    // thickness
    ++itc;
    }
}

void fastVid(cv::Mat &image1, cv::Mat &image2){
    image2 = image1;
    cv::cvtColor(image2, image2, CV_BGR2GRAY);
    // vector of keypoints
    std::vector<cv::KeyPoint> keypoints;
    // Construction of the Fast feature detector object
     cv::Ptr<cv::FastFeatureDetector> fast = cv::FastFeatureDetector::create(40); // threshold for detection
    //fast.setThreshold(40);
    // feature point detection
    fast->detect(image2,keypoints);
    cv::drawKeypoints(image2,
    // original image
    keypoints,
    // vector of keypoints
    image2,
    // the output image
    cv::Scalar(255,255,255), // keypoint color
    cv::DrawMatchesFlags::DRAW_OVER_OUTIMG); //drawing flag
}

void harrisVid(cv::Mat &image1, cv::Mat &image2){

    image2=image1;
    cv::cvtColor(image2, image2, CV_BGR2GRAY);

    // Detect Harris Corners
    cv::Mat cornerStrength;
    cv::cornerHarris(image2, cornerStrength,
        3,      // neighborhood size
        3,      // aperture size
        0.01    // Harris parameter
        );
    // threshold the corner strengths
    cv::Mat harrisCorners;
    double threshold = 0.0001;
    cv::threshold(cornerStrength, harrisCorners, threshold, 255, cv::THRESH_BINARY_INV);
    image2=harrisCorners;
}

void sharpen(const cv::Mat &image, cv::Mat &result) {
    // allocate if necessary
    result.create(image.size(), image.type());
    for (int j= 1; j<image.rows-1; j++) { // for all rows
        // (except first and last)
      const uchar* previous=image.ptr<const uchar>(j-1); // previous row
      const uchar* current=image.ptr<const uchar>(j);
      // current row
      const uchar* next=image.ptr<const uchar>(j+1); // next row
      uchar* output= result.ptr<uchar>(j); // output row
      for (int i=1; i<image.cols-1; i++) {
         *output++= cv::saturate_cast<uchar>(
         5*current[i]-current[i-1]
         -current[i+1]-previous[i]-next[i]);
      }
    }
    // Set the unprocess pixels to 0
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}


void canny(cv::Mat& img, cv::Mat& out) {
// Convert to gray
if (img.channels()==3)
cv::cvtColor(img,out,CV_BGR2GRAY);
// Compute Canny edges
cv::Canny(out,out,100,200);
// Invert the image
cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
}

void saltAndPepper(cv::Mat& img, cv::Mat& out){


}

void nothing(cv::Mat& img, cv::Mat& out) {
// Convert to gray
if (img.channels()==3)
cv::cvtColor(img,out,CV_BGR2GRAY);
// Compute Canny edges
//cv::Canny(out,out,100,200);
// Invert the image
//cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
}
