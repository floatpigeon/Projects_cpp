
#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

class ColorProcess {
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

    static void bright_filter(cv::Mat& input_image, cv::Mat& output_image) {
        cv::Mat process_image;
        cv::cvtColor(input_image, process_image, cv::COLOR_BGR2GRAY);

        cv::Mat BrightMask;
        cv::threshold(process_image, BrightMask, 200, 255, cv::THRESH_BINARY);

        static cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::morphologyEx(BrightMask, BrightMask, cv::MORPH_OPEN, kernel);
        output_image = BrightMask;
    }

    static void hybrid_image_processing(cv::Mat& input_image, cv::Mat& output_image) {
        cv::Mat HSV_image;
        cv::cvtColor(input_image, HSV_image, cv::COLOR_BGR2HLS);
        cv::Mat GreenMask;

        static cv::Scalar lowerlimit(45, 96, 128);
        static cv::Scalar upperlimit(75, 192, 255);
        cv::inRange(HSV_image, lowerlimit, upperlimit, GreenMask);

        static cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::morphologyEx(GreenMask, GreenMask, cv::MORPH_OPEN, kernel);

        output_image = GreenMask;

        // cv::Mat BrightMask;
        // cv::cvtColor(input_image, BrightMask, cv::COLOR_BGR2GRAY);
        // cv::threshold(BrightMask, BrightMask, 100, 200, cv::THRESH_BINARY);

        // cv::bitwise_and(GreenMask, BrightMask, output_image);
    }
};