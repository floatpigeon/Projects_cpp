#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "color_previewer.hpp"

int main() {
    cv::Scalar lowerlimit, upperlimit;

    lowerlimit = cv::Scalar(50, 64, 128);
    upperlimit = cv::Scalar(50, 192, 255);
    ColorPreviewer::generate_color_range_image("50H", lowerlimit, upperlimit);

    lowerlimit = cv::Scalar(60, 64, 128);
    upperlimit = cv::Scalar(60, 192, 255);
    ColorPreviewer::generate_color_range_image("60H", lowerlimit, upperlimit);

    lowerlimit = cv::Scalar(70, 64, 128);
    upperlimit = cv::Scalar(70, 192, 255);
    ColorPreviewer::generate_color_range_image("70H", lowerlimit, upperlimit);

    cv::waitKey(0);
    return 0;
}
