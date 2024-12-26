
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
        ColorPreviewer::generate_LS_range_image("50H", lowerlimit, upperlimit);

        lowerlimit = cv::Scalar(60, 64, 128);
        upperlimit = cv::Scalar(60, 192, 255);
        ColorPreviewer::generate_LS_range_image("60H", lowerlimit, upperlimit);

        lowerlimit = cv::Scalar(70, 64, 128);
        upperlimit = cv::Scalar(70, 192, 255);
        ColorPreviewer::generate_LS_range_image("70H", lowerlimit, upperlimit);

        cv::waitKey(0);
    }

    static void HLS_color_filter_test() {
        cv::Scalar lowerlimit(0, 0, 255);
        cv::Scalar upperlimit(180, 255, 255);
        cv::Mat test_image = ColorPreviewer::generate_gradient_image("TEST", lowerlimit, upperlimit, 2);

        if (test_image.empty()) return;

        cv::Mat processed_image;
        ImageProcess::HLS_color_filter(test_image, processed_image);
        // cv::imshow("Processed_Image", processed_image);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(processed_image, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            // 颜色为随机颜色
            cv::Scalar color = cv::Scalar(255, 0, 0);
            cv::drawContours(test_image, contours, static_cast<int>(i), color, 1, cv::LINE_8, hierarchy, 0);
        }

        cv::imshow("display", test_image);

        cv::waitKey(0);
    }

    static void generate_gradient_image_test() {
        cv::Scalar lowerlimit, upperlimit;

        lowerlimit = cv::Scalar(60, 64, 128);
        upperlimit = cv::Scalar(60, 192, 255);
        ColorPreviewer::generate_gradient_image("LS", lowerlimit, upperlimit, 0);

        lowerlimit = cv::Scalar(50, 128, 128);
        upperlimit = cv::Scalar(70, 128, 255);
        ColorPreviewer::generate_gradient_image("HS", lowerlimit, upperlimit, 1);

        lowerlimit = cv::Scalar(50, 96, 196);
        upperlimit = cv::Scalar(70, 160, 196);
        ColorPreviewer::generate_gradient_image("HL", lowerlimit, upperlimit, 2);

        cv::waitKey(0);
    }
};
