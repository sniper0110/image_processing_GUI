#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vvideo = new VideoProcessor();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete vvideo;
}

void MainWindow::on_loadImageButton_clicked()
{

    //if(cvGetWindowHandle("Input window")){
        cvDestroyWindow("Input window");
    //}
    QString filen = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if(!filen.isEmpty()){
    //inputImage = tmp;
    inputImage = cv::imread(filen.toStdString());
    cv::namedWindow("Input window");
    cv::imshow("Input window", inputImage);
    }

}

void MainWindow::on_loadVideoButton_clicked()
{
    QString filen = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.mp4 *.avi)"));
    // Open video file
    std::string s = filen.toUtf8().constData();

    video.setInput(s); //"SampleVideo.mp4"
    // Declare a window to display the video
    video.displayInput("Input video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(nothing);
    // Start the process
    video.run();

}



void MainWindow::on_saltPepperButton_clicked()
{
    outputImage = inputImage;
    salt(outputImage, 2000);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}



void MainWindow::on_colorSpaceButton_clicked()
{
    outputImage = inputImage;
   cv::cvtColor(outputImage, outputImage, CV_BGR2HLS);
   cv::namedWindow("Output window");
   cv::imshow("Output window", outputImage);
}

void MainWindow::on_saveImage_clicked()
{
    cv::imwrite("output.png", outputImage);
}

void MainWindow::on_logoButton_clicked()
{
    outputImage = inputImage;
    cv::Mat logo = cv::imread("logo.jpeg");
    // to contain resized image
    cv::resize(logo,logo,
    cv::Size(logo.cols/3,logo.rows/3)); // 1/3 resizing
    // define image ROI
    cv::Mat imageROI;
    imageROI= outputImage(cv::Rect(outputImage.cols-10-logo.cols,10,logo.cols,logo.rows));
    // add logo to image
    cv::addWeighted(imageROI,1.0,logo,1,0.,imageROI);

    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);

}

void MainWindow::on_computeHistButton_clicked()
{
    cv::Mat test;
    cv::cvtColor(inputImage, test, CV_BGR2GRAY);
    // The histogram object
    Histogram1D h;
    //cv::calcHist(outputImage, 1);
    // Compute the histogram
    cv::MatND histo= h.getHistogram(test);
    cv::namedWindow("Output window");
    cv::imshow("Output window", h.getHistogram(test));
}


void MainWindow::on_equalizeHistButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    cv::equalizeHist(outputImage, outputImage);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_dilateButton_clicked()
{
    cv::dilate(inputImage,outputImage,cv::Mat());
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_erodeButton_clicked()
{
    cv::erode(inputImage, outputImage, cv::Mat());
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_openButton_clicked()
{
    cv::Mat element5(5,5,CV_8U,cv::Scalar(1));
    cv::morphologyEx(inputImage,outputImage,cv::MORPH_OPEN,element5);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_closeButton_clicked()
{
    cv::Mat element5(5,5,CV_8U,cv::Scalar(1));
    cv::morphologyEx(inputImage,outputImage,cv::MORPH_CLOSE,element5);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_moveInToOutButton_clicked()
{
    inputImage = outputImage;
}



void MainWindow::on_blurButton_clicked()
{
    cv::blur(inputImage,outputImage,cv::Size(5,5));
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_sobelButton_clicked()
{
    cv::Sobel(inputImage,outputImage, CV_8U,1,0,3,0.4,128); // X direction
    cv::Sobel(outputImage, outputImage, CV_8U,0,1,3,0.4,128); // THEN Y direction
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_lablacianButton_clicked()
{
    cv::Laplacian(inputImage, outputImage, CV_32F, 3);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_sharpenButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    sharpen(outputImage, outputImage);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}


void MainWindow::on_cannyButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    cv::Canny(outputImage, outputImage, 100, 200);
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

void MainWindow::on_houghLineButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    cv::Mat contours;
    // Create LineFinder instance
    LineFinder finder;
    // Set probabilistic Hough parameters
    finder.setLineLengthAndGap(100,20);
    finder.setMinVote(80);
    // Detect lines and draw them
    finder.findLines(contours); //std::vector<cv::Vec4i> lines= finder.findLines(contours);
    finder.drawDetectedLines(outputImage);
    cv::namedWindow("Output window");
    cv::imshow("Output window",outputImage);
}

void MainWindow::on_houghCircleButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    cv::GaussianBlur(outputImage,outputImage,cv::Size(5,5),1.5);
    std::vector<cv::Vec3f> circles;

    cv::HoughCircles(outputImage, circles, CV_HOUGH_GRADIENT,
    2,
    // accumulator resolution (size of the image / 2)
    50, // minimum distance between two circles
    200, // Canny high threshold
    100, // minimum number of votes
    5, 100); // min and max radius
    std::vector<cv::Vec3f>::
    const_iterator itc= circles.begin();
    while (itc!=circles.end()) {
    cv::circle(outputImage,
    cv::Point((*itc)[0], (*itc)[1]), // circle centre
    (*itc)[2],
    // circle radius
    cv::Scalar(0), // color
    2);
    // thickness
    ++itc;
    }

    cv::namedWindow("Output window");
    cv::imshow("Output window",outputImage);
}

void MainWindow::on_contoursButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(outputImage,
    contours, // a vector of contours
    CV_RETR_EXTERNAL, // retrieve the external contours
    CV_CHAIN_APPROX_NONE); // all pixels of each contours
    // Draw black contours on a white image
    cv::Mat result(outputImage.size(),CV_8U,cv::Scalar(255));
    result = outputImage;
    cv::drawContours(result,contours,
    -1, // draw all contours
    cv::Scalar(0), // in black
    2); // with a thickness of 2
    cv::namedWindow("Output window");
    cv::imshow("Output window",result);
}


void MainWindow::on_bounBoxButton_clicked()
{

}

void MainWindow::on_harrisButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
//    // Create Harris detector instance
//    HarrisDetector harris;
//    // Compute Harris values
//    harris.detect(outputImage);
//    // Detect Harris corners
//    std::vector<cv::Point> pts;
//    harris.getCorners(pts,0.01);
//    // Draw Harris corners
//    harris.drawOnImage(outputImage,pts);
//    cv::namedWindow("Output window");
//    cv::imshow("Output window",outputImage);

    // Detect Harris Corners
    cv::Mat cornerStrength;
    cv::cornerHarris(outputImage, cornerStrength,
        3,      // neighborhood size
        3,      // aperture size
        0.01    // Harris parameter
        );
    // threshold the corner strengths
    cv::Mat harrisCorners;
    double threshold = 0.0001;
    cv::threshold(cornerStrength, harrisCorners, threshold, 255, cv::THRESH_BINARY_INV);

    //cv::imshow("Original Image", image);
    cv::namedWindow("Output window");
    cv::imshow("Output window", harrisCorners);
}

void MainWindow::on_fastButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    // vector of keypoints
    std::vector<cv::KeyPoint> keypoints;
    // Construction of the Fast feature detector object
     cv::Ptr<cv::FastFeatureDetector> fast = cv::FastFeatureDetector::create(40); // threshold for detection
    //fast.setThreshold(40);
    // feature point detection
    fast->detect(outputImage,keypoints);
    cv::drawKeypoints(outputImage,
    // original image
    keypoints,
    // vector of keypoints
    outputImage,
    // the output image
    cv::Scalar(255,255,255), // keypoint color
    cv::DrawMatchesFlags::DRAW_OVER_OUTIMG); //drawing flag
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);
}

/*void MainWindow::on_surfButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    // vector of keypoints
    std::vector<cv::KeyPoint> keypoints;
    // Construct the SURF feature detector object
    cv::SurfFeatureDetector surf(
    2500.); // threshold
    // Detect the SURF features
    surf.detect(outputImage,keypoints);
    // Draw the keypoints with scale and orientation information
    cv::drawKeypoints(outputImage,
    // original image
    keypoints,
    // vector of keypoints
    outputImage,
    // the resulting image
    cv::Scalar(255,255,255),
    // color of the points
    cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS); //flag
    cv::namedWindow("Output window");
    cv::imshow("Output window", outputImage);

}*/

/*void MainWindow::on_siftButton_clicked()
{
    cv::cvtColor(inputImage, outputImage, CV_BGR2GRAY);
    // vector of keypoints
    std::vector<cv::KeyPoint> keypoints;
    // Construct the SURF feature detector object

    cv::SiftFeatureDetector sift(
    0.03, // feature threshold
    10.); // threshold to reduce
    // sensitivity to lines
    // Detect the SURF features
    sift.detect(image,keypoints);
}*/

void MainWindow::on_saltPepperButton_2_clicked()
{
    //video.setInput(s); //"SampleVideo.mp4"
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(saltVid);
    // Start the process
    video.run();

}



void MainWindow::on_logoButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(logoVid);
    // Start the process
    video.run();
}

void MainWindow::on_colorSpaceButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(HLSVid);
    // Start the process
    video.run();
}

void MainWindow::on_equalizeHistButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(equalHistVid);
    // Start the process
    video.run();
}

void MainWindow::on_blurButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(blurVid);
    // Start the process
    video.run();
}

void MainWindow::on_cannyButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(canny);
    // Start the process
    video.run();
}

void MainWindow::on_sobelButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(sobelVid);
    // Start the process
    video.run();
}

void MainWindow::on_lablacianButton_2_clicked()
{
    // Declare a window to display the video
    video.displayOutput("Output video");
    // Play the video at the original frame rate
    video.setDelay(1000./video.getFrameRate());
    // Set the frame processor callback function
    video.setFrameProcessor(laplaceVid);
    // Start the process
    video.run();
}

void MainWindow::on_sharpenButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(sharpenVid);
    // Start the process
    vvideo->run();
}

void MainWindow::on_dilateButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(dilateVid);
    // Start the process
    vvideo->run();
}


void MainWindow::on_erodeButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(erodeVid);
    // Start the process
    vvideo->run();
}

void MainWindow::on_openButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(openVid);
    // Start the process
    vvideo->run();
}

void MainWindow::on_closeButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(closeVid);
    // Start the process
    vvideo->run();
}

void MainWindow::on_houghCircleButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(houghCircleVid);
    // Start the process
    vvideo->run();
}

void MainWindow::on_harrisButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(harrisVid);
    // Start the process
    vvideo->run();
}

void MainWindow::on_fastButton_2_clicked()
{
    // Declare a window to display the video
    vvideo->displayOutput("Output video");
    // Play the video at the original frame rate
    vvideo->setDelay(1000./vvideo->getFrameRate());
    // Set the frame processor callback function
    vvideo->setFrameProcessor(fastVid);
    // Start the process
    vvideo->run();
}
