#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Histogram1D {
private:
   int histSize[1]; // number of bins
   float hranges[2]; // min and max pixel value
   const float* ranges[1];
   int channels[1]; // only 1 channel used here

public:
   Histogram1D() {
   // Prepare arguments for 1D histogram
   histSize[0]= 256;
   hranges[0]= 0.0;
   hranges[1]= 255.0;
   ranges[0]= hranges;
   channels[0]= 0; // by default, we look at channel 0
   }
   // Computes the 1D histogram.
   cv::MatND getHistogram(const cv::Mat &image) {
   cv::MatND hist;
   // Compute histogram
   cv::calcHist(&image,
   1,
   // histogram from 1 image only
   channels, // the channel used
   cv::Mat(), // no mask is used
   hist,
   // the resulting histogram
   1,
   // it is a 1D histogram
   histSize, // number of bins
   ranges
   // pixel value range
   );
   return hist;
   }
};


#endif // HISTOGRAM1D_H
