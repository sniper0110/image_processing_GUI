#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "functions.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "histogram1d.h"
#include "linefinder.h"
#include "harrisdetector.h"
#include <opencv2/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include "videoprocessor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    void on_loadVideoButton_clicked();

    void on_saltPepperButton_clicked();

    void on_colorSpaceButton_clicked();

    void on_saveImage_clicked();

    void on_logoButton_clicked();

    void on_computeHistButton_clicked();

    void on_equalizeHistButton_clicked();

    void on_dilateButton_clicked();

    void on_openButton_clicked();

    void on_erodeButton_clicked();

    void on_closeButton_clicked();

    void on_moveInToOutButton_clicked();

    void on_loadImageButton_clicked();

    void on_blurButton_clicked();

    void on_sobelButton_clicked();

    void on_lablacianButton_clicked();

    void on_sharpenButton_clicked();

    void on_cannyButton_clicked();

    void on_houghLineButton_clicked();

    void on_houghCircleButton_clicked();

    void on_contoursButton_clicked();

    void on_bounBoxButton_clicked();

    void on_harrisButton_clicked();

    void on_fastButton_clicked();

    //void on_surfButton_clicked();

    //void on_siftButton_clicked();

    void on_saltPepperButton_2_clicked();

    void on_logoButton_2_clicked();

    void on_colorSpaceButton_2_clicked();

    void on_equalizeHistButton_2_clicked();

    void on_blurButton_2_clicked();

    void on_cannyButton_2_clicked();

    void on_sobelButton_2_clicked();

    void on_lablacianButton_2_clicked();

    void on_sharpenButton_2_clicked();

    void on_dilateButton_2_clicked();

    void on_erodeButton_2_clicked();

    void on_openButton_2_clicked();

    void on_closeButton_2_clicked();

    void on_houghCircleButton_2_clicked();

    void on_harrisButton_2_clicked();

    void on_fastButton_2_clicked();

private:
    Ui::MainWindow *ui;
    //input_Form *m_input_ui; //creating an input form inside the main window
    //Output_Form *m_output_ui; //creating an output form inside the main window
    cv::Mat inputImage;
    cv::Mat outputImage;
    QString file;
    VideoProcessor video;
    VideoProcessor *vvideo;
    VideoProcessor outVideo;

};


#endif // MAINWINDOW_H
