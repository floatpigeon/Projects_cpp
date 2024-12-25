#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "color_previewer.hpp"

int main() {
    cv::Scalar lower(60, 64, 128);
    cv::Scalar upper(60, 192, 255);
    ColorPreviewer::generate_color_range_image(lower, upper);

    return 0;
}
