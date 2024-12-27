
#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include "color_previewer.hpp"
#include "color_processing.hpp"
#include "image_processing.hpp"

class Examples {
public:
    static void darts_target_finder_test() {
        cv::Scalar lowerlimit(0, 0, 255);
        cv::Scalar upperlimit(180, 255, 255);
        cv::Mat test_image = ColorPreviewer::generate_gradient_image("TEST", lowerlimit, upperlimit, 2);

        cv::Mat process_image = test_image;
        ImageProcess::darts_target_finder(test_image, process_image);
        cv::imshow("draw", process_image);
        cv::waitKey(0);
    }

    static void hybrid_image_processing_test() {
        cv::Scalar lowerlimit(0, 0, 255);
        cv::Scalar upperlimit(180, 255, 255);
        cv::Mat test_image = ColorPreviewer::generate_gradient_image("TEST", lowerlimit, upperlimit, 2);

        cv::Mat processed_image;
        ColorProcess::hybrid_image_processing(test_image, processed_image);
        ImageProcess::draw_range(processed_image, test_image);

        cv::imshow("processed", processed_image);
        cv::waitKey(0);
    }

    static void bright_filter_test() {
        cv::Scalar lowerlimit(0, 0, 255);
        cv::Scalar upperlimit(180, 255, 255);
        cv::Mat test_image = ColorPreviewer::generate_gradient_image("TEST", lowerlimit, upperlimit, 2);

        cv::Mat processed_image;
        ColorProcess::bright_filter(test_image, processed_image);

        cv::imshow("processed", processed_image);
        cv::waitKey(0);
    }

    static void Green_LS_of_H_preview() {
        cv::Scalar lowerlimit, upperlimit;

        lowerlimit = cv::Scalar(50, 64, 128);
        upperlimit = cv::Scalar(50, 192, 255);
        ColorPreviewer::generate_gradient_image("50H", lowerlimit, upperlimit, 0);

        lowerlimit = cv::Scalar(60, 64, 128);
        upperlimit = cv::Scalar(60, 192, 255);
        ColorPreviewer::generate_gradient_image("60H", lowerlimit, upperlimit, 0);

        lowerlimit = cv::Scalar(70, 64, 128);
        upperlimit = cv::Scalar(70, 192, 255);
        ColorPreviewer::generate_gradient_image("70H", lowerlimit, upperlimit, 0);

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
