
#pragma once
#include <cstdio>
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

class ColorPreviewer {
public:
    static void color_picker_HLS() {
        int v0, v1, v2;
        std::cin >> v0 >> v1 >> v2;

        cv::Scalar HLS(v0, v1, v2);
        cv::Mat hlsImage(1, 1, CV_8UC3, HLS);
        cv::Mat BGR_image_;
        cv::cvtColor(hlsImage, BGR_image_, cv::COLOR_HLS2BGR);
        cv::Mat displayImage(300, 300, CV_8UC3, BGR_image_.at<cv::Vec3b>(0, 0));
        cv::imshow("window", displayImage);

        cv::waitKey(0);
    }

    static void color_picker_BGR() {
        int v0, v1, v2;
        std::cin >> v0 >> v1 >> v2;

        cv::Scalar BGR(v0, v1, v2);
        cv::Mat displayImage(300, 300, CV_8UC3, BGR);
        cv::imshow("window", displayImage);

        cv::waitKey(0);
    }
    static void BGR_to_HLS() {
        int v0, v1, v2;
        std::cin >> v0 >> v1 >> v2;

        cv::Scalar BGR(v0, v1, v2);
        cv::Mat bgrImage(1, 1, CV_8UC3, BGR);
        cv::Mat displayImage(256, 256, CV_8UC3, BGR);

        cv::Mat hlsImage;
        cv::cvtColor(bgrImage, hlsImage, cv::COLOR_BGR2HLS);

        std::vector<cv::Mat> hlsChannels;
        cv::split(hlsImage, hlsChannels);

        std::cout << "H :" << hlsChannels[0] << std::endl;
        std::cout << "L :" << hlsChannels[1] << std::endl;
        std::cout << "S :" << hlsChannels[2] << std::endl;

        cv::imshow("Original Image", displayImage);
        cv::waitKey(0);
    }

    static void generate_color_range_image(cv::Scalar lowerlimit, cv::Scalar upperlimit) {
        int rows = abs(upperlimit[1] - lowerlimit[1]);
        int cols = abs(upperlimit[2] - lowerlimit[2]);

        int v0 = lowerlimit[0];

        int row_begin = lowerlimit[1];
        int col_begin = lowerlimit[2];
        cv::Mat image(rows, cols, CV_8UC3);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                double v1 = row_begin + i;
                double v2 = col_begin + j;
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(v0, v1, v2);
            }
        }

        cv::cvtColor(image, image, cv::COLOR_HLS2BGR);
        cv::Mat displayImage;
        cv::resize(image, displayImage, cv::Size(), 2.0, 2.0, cv::INTER_LINEAR);

        cv::imshow("Image", displayImage);
        std::cout << ".." << std::endl;
        cv::waitKey(0);
    }
};
