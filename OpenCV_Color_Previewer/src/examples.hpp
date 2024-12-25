
#pragma once

#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include "color_previewer.hpp"
#include "color_processing.hpp"

class Examples {
public:
    static void Green_LS_of_H() {
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
    }

    static void color_filter_HLS_test() {
        cv::Scalar lowerlimit(60, 0, 0);
        cv::Scalar upperlimit(60, 255, 255);
        cv::Mat test_image =
            ColorPreviewer::generate_color_range_image("Test_Image", lowerlimit, upperlimit);

        cv::Mat processed_image;
        ImageProcess::color_filter_HLS(test_image, processed_image);
        cv::imshow("Processed_Image", processed_image);

        cv::waitKey(0);
    }
};