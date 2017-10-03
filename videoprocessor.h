#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class VideoProcessor {
private:
// the OpenCV video capture object
cv::VideoCapture capture;
// the callback function to be called
// for the processing of each frame
void (*process)(cv::Mat&, cv::Mat&);
// a bool to determine if the
// process callback will be called
bool callIt;
// Input display window name
std::string windowNameInput;
// Output display window name
std::string windowNameOutput;
// delay between each frame processing
int delay;
// number of processed frames
long fnumber;
// stop at this frame number
long frameToStop;
// to stop the processing
bool stop;
// vector of image filename to be used as input
std::vector<std::string> images;
// image vector iterator
std::vector<std::string>::const_iterator itImg;

// frame rate
double rate;

public:
VideoProcessor() : callIt(true), delay(0),
fnumber(0), stop(false), frameToStop(-1) {}
// get frame rate
double getFrameRate(){
    return capture.get(CV_CAP_PROP_FPS);
}

// set the callback function that
// will be called for each frame
void setFrameProcessor(
void (*frameProcessingCallback)(cv::Mat&, cv::Mat&)) {
process= frameProcessingCallback;
}

// set the name of the video file
bool setInput(std::string filename) {
fnumber= 0;
// In case a resource was already
// associated with the VideoCapture instance
capture.release();
images.clear();
// Open the video file
return capture.open(filename);
}

// to display the processed frames
void displayInput(std::string wn) {
windowNameInput= wn;
cv::namedWindow(windowNameInput);
}
// to display the processed frames
void displayOutput(std::string wn) {
windowNameOutput= wn;
cv::namedWindow(windowNameOutput);
}

// do not display the processed frames
void dontDisplay() {
cv::destroyWindow(windowNameInput);
cv::destroyWindow(windowNameOutput);
windowNameInput.clear();
windowNameOutput.clear();
}

// to grab (and process) the frames of the sequence
void run() {
// current frame
cv::Mat frame;
// output frame
cv::Mat output;
// if no capture device has been set
if (!isOpened())
return;
stop= false;
while (!isStopped()) {
// read next frame if any
if (!readNextFrame(frame))
break;
// display input frame
if (windowNameInput.length()!=0)
cv::imshow(windowNameInput,frame);
// calling the process function
if (callIt) {
// process the frame
process(frame, output);
// increment frame number
fnumber++;
} else {
output= frame;
}
// display output frame
if (windowNameOutput.length()!=0)
cv::imshow(windowNameOutput,output);
// introduce a delay
if (delay>=0 && cv::waitKey(delay)>=0)
    stopIt();
    // check if we should stop
    if (frameToStop>=0 &&
    getFrameNumber()==frameToStop)
    stopIt();
    }
    }

// Stop the processing
void stopIt() {
stop= false;
}
// Is the process stopped?
bool isStopped() {
return stop;
}
// Is a capture device opened?
bool isOpened() {
capture.isOpened();
}
// set a delay between each frame
// 0 means wait at each frame
// negative means no delay
void setDelay(int d) {
delay= d;
}

// to get the next frame
// could be: video file or camera
bool readNextFrame(cv::Mat& frame) {
return capture.read(frame);
}

// process callback to be called
void callProcess() {
callIt= true;
}

// do not call process callback
void dontCallProcess() {
callIt= false;
}

void stopAtFrameNo(long frame) {
frameToStop= frame;
}
// return the frame number of the next frame
long getFrameNumber() {
// get info of from the capture device
long fnumber= static_cast<long>(
capture.get(CV_CAP_PROP_POS_FRAMES));
return fnumber;
}

// set the vector of input images
bool setInput(const std::vector<std::string>& imgs) {
fnumber= 0;
// In case a resource was already
// associated with the VideoCapture instance
capture.release();
// the input will be this vector of images
images= imgs;
itImg= images.begin();
return true;
}



};






#endif // VIDEOPROCESSOR_H
