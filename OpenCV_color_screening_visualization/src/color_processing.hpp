
#pragma once

#include <opencv2/opencv.hpp>

class ImageProcess {
public:
    static void HLS_color_filter(cv::Mat& input_image, cv::Mat& output_image) {
        cv::Mat process_image;
        cv::cvtColor(input_image, process_image, cv::COLOR_BGR2HLS);

        cv::Mat ColorMask;
        cv::Scalar lowerlimit(40, 96, 128);
        cv::Scalar upperlimit(80, 160, 255);
        cv::inRange(process_image, lowerlimit, upperlimit, ColorMask);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::morphologyEx(ColorMask, process_image, cv::MORPH_OPEN, kernel);

        output_image = ColorMask;
    }
};