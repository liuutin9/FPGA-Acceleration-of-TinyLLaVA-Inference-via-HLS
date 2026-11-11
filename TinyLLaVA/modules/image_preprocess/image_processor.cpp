#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "image_processor.hpp"

void normalize(float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const std::vector<cv::Mat>& channels) {
    // channels[c] 是 CV_32FC1，值域為 [0, 1]
    for (int c = 0; c < NUM_CHANNELS; ++c) {
        for (int i = 0; i < IMAGE_SIZE; ++i) {
            for (int j = 0; j < IMAGE_SIZE; ++j) {
                float pixel = channels[c].at<float>(i, j);
                out[c][i][j] = (pixel - IMAGE_MEAN[c]) / IMAGE_STD[c];
            }
        }
    }
}

void preprocess(float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const cv::Mat& image_bgr) {
    // 1. 將 BGR 轉為 RGB
    cv::Mat image_rgb;
    cv::cvtColor(image_bgr, image_rgb, cv::COLOR_BGR2RGB);

    // 2. 調整大小為 384x384
    //    INTER_AREA: same choice as ip_test.cpp, which was compared against SiglipImageProcessor.
    //    PIL's bicubic resize cannot be reproduced exactly with OpenCV, so a small difference remains
    //    (preprocessed_implementation_cpp.bin vs _py.bin: mean |diff| ~0.011).
    cv::Mat resized;
    cv::resize(image_rgb, resized, cv::Size(IMAGE_SIZE, IMAGE_SIZE), 0, 0, cv::INTER_AREA);

    // 3. 轉為 float 並調整至 [0, 1]
    cv::Mat rescaled;
    resized.convertTo(rescaled, CV_32FC3, 1.0 / 255.0);

    // 4. 拆分通道（R, G, B）
    std::vector<cv::Mat> channels(NUM_CHANNELS);
    cv::split(rescaled, channels);

    // 5. 正規化，輸出 CHW
    normalize(output, channels);
}

#ifdef IMAGE_PROCESSOR_MAIN
// Standalone test: g++ -DIMAGE_PROCESSOR_MAIN image_processor.cpp ...
int main() {
    std::string image_path = "test.jpg";

    // load image in BGR & HWC format => [Height, Width, Channels]
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Failed to load image from file: " << image_path << "\n";
        return 1;
    }
    std::cout << "rows: " << img.rows << std::endl;
    std::cout << "cols: " << img.cols << std::endl;
    std::cout << "channels: " << img.channels() << std::endl;

    static float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE];
    preprocess(output, img);
    std::cout << "first pixel: " << output[0][0][0] << ", " << output[1][0][0] << ", " << output[2][0][0] << std::endl;
    return 0;
}
#endif
