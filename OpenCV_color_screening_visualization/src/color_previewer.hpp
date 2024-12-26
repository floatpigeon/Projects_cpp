
#pragma once

#include <opencv2/core/cvdef.h>
#include <cstdio>
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

class ColorPreviewer {
public:
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

    static cv::Mat generate_LS_range_image(std::string windowname, cv::Scalar lowerlimit, cv::Scalar upperlimit) {
        int rows = abs(upperlimit[1] - lowerlimit[1]);
        int cols = abs(upperlimit[2] - lowerlimit[2]);

        cv::Mat image(rows, cols, CV_8UC3);
        int v0 = lowerlimit[0];
        for (int i = 0; i < rows; i++) {
            int v1 = lowerlimit[1] + i;
            for (int j = 0; j < cols; j++) {
                int v2                    = lowerlimit[2] + j;
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(v0, v1, v2);
            }
        }

        cv::cvtColor(image, image, cv::COLOR_HLS2BGR);
        cv::Mat displayImage;
        cv::resize(image, displayImage, cv::Size(), 3.0, 3.0, cv::INTER_LINEAR);

        cv::imshow(windowname, displayImage);
        return displayImage;
    }

    static cv::Mat generate_gradient_image(
        std::string windowname, cv::Scalar lowerlimit, cv::Scalar upperlimit, int mode) {
        int rows, cols;
        cv::Mat image;
        int v0, v1, v2;

        if ((upperlimit[mode] - lowerlimit[mode]) != 0) {
            std::cout << windowname + "_ColorPreviewer::generate_gradient_image : Variable No be controlled!"
                      << std::endl;
            return image;
        }

        switch (mode) {
            case 0:
                rows = abs(upperlimit[1] - lowerlimit[1]);
                cols = abs(upperlimit[2] - lowerlimit[2]);
                v0   = lowerlimit[0];

                image = cv::Mat(rows, cols, CV_8UC3);
                for (int i = 0; i < rows; i++) {
                    v1 = lowerlimit[1] + i;
                    for (int j = 0; j < cols; j++) {
                        v2                        = lowerlimit[2] + j;
                        image.at<cv::Vec3b>(i, j) = cv::Vec3b(v0, v1, v2);
                    }
                }
                break;
            case 1:
                rows = abs(upperlimit[0] - lowerlimit[0]);
                cols = abs(upperlimit[2] - lowerlimit[2]);
                v1   = lowerlimit[1];

                image = cv::Mat(rows, cols, CV_8UC3);
                for (int i = 0; i < rows; i++) {
                    v0 = lowerlimit[0] + i;
                    for (int j = 0; j < cols; j++) {
                        v2                        = lowerlimit[2] + j;
                        image.at<cv::Vec3b>(i, j) = cv::Vec3b(v0, v1, v2);
                    }
                }
                break;
            case 2:
                rows = abs(upperlimit[0] - lowerlimit[0]);
                cols = abs(upperlimit[1] - lowerlimit[1]);
                v2   = lowerlimit[2];

                image = cv::Mat(rows, cols, CV_8UC3);
                for (int i = 0; i < rows; i++) {
                    int v0 = lowerlimit[0] + i;
                    for (int j = 0; j < cols; j++) {
                        int v1                    = lowerlimit[1] + j;
                        image.at<cv::Vec3b>(i, j) = cv::Vec3b(v0, v1, v2);
                    }
                }
                break;
            default: break;
        }

        cv::cvtColor(image, image, cv::COLOR_HLS2BGR);
        cv::Mat displayImage;
        cv::resize(image, displayImage, cv::Size(), 3.0, 3.0, cv::INTER_LINEAR);

        cv::imshow(windowname, displayImage);

        return displayImage;
    }
};
