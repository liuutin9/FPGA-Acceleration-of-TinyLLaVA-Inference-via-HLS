#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <image_processor.hpp>
const int IMAGE_SIZE = 384;
const int NUM_CHANNELS = 3;

const float IMAGE_MEAN[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};
const float IMAGE_STD[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};

// void normalize(
//     float image[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], 
//     float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE].
// ){
//     for(int c = 0; c < NUM_CHANNELS; c++){
//         for(int i = 0; i < NUM_CHANNELS; i++){
//             for(int j = 0; j < NUM_CHANNELS; j++){
//                 out[c][i][j] = (image[c][i][j] - IMAGE_MEAN[c]) / IMAGE_STD[c];
//              }
//         }
//     }
// }

void normalize(float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], auto channels) {
    // 假設 image 是 CV_32FC3 格式，且值域為 [0, 1]
    const float mean[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};
    const float std[NUM_CHANNELS]  = {0.5f, 0.5f, 0.5f};

    for (int c = 0; c < NUM_CHANNELS; ++c) {
        for (int i = 0; i < IMAGE_SIZE; ++i) {
            for (int j = 0; j < IMAGE_SIZE; ++j) {
                float pixel = channels[c].at<float>(i, j);
                out[c][i][j] = (pixel - mean[c]) / std[c];
            }
        }
    }
}

void preprocess(float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const cv::Mat& image_bgr) {
    // 1. 將 BGR 轉為 RGB
    cv::Mat image_rgb;
    cv::cvtColor(image_bgr, image_rgb, cv::COLOR_BGR2RGB);

    // 2. 調整大小為 384x384
    cv::Mat resized;
    cv::resize(image_rgb, resized, cv::Size(384, 384));
    // std::cout << "rows: " << resized.rows << std::endl;
    // std::cout << "cols: " << resized.cols << std::endl;
    // std::cout << "channels: " << resized.channels() << std::endl; 
    // std::cout << "total pixel: " << resized.total() << std::endl;

    // 3. 轉為 float 並正規化到 [0, 1]
    cv::Mat rescaled;
    resized.convertTo(rescaled, CV_32FC3, 1.0 / 255.0);

    // 4. 拆分通道（R, G, B)
    std::vector<cv::Mat> channels(3);
    cv::split(rescaled, channels); // channels[i] => cv::Mat (H, W)
    // std::cout << "channels size: " << channels[0].size() << std::endl;

    //float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE] = {0};    
    normalize(output, channels); // float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]

    // // 5. 將每個通道展平成一維並依序合併成 CHW 向量
    // std::vector<float> chw;
    // for (const auto& channel : channels) {
    //     std::copy(
    //         channel.ptr<float>(0),                   // 起始指標
    //         channel.ptr<float>(0) + channel.total(), // 終止指標
    //         std::back_inserter(chw)                  // 插入 vector 尾巴
    //     );
    // }
    
    // return chw;
}

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
    std::cout << "total pixel: " << img.total() << std::endl;

    // show the image (for test)
    // cv::imshow("Loaded Image", img);
    // cv::waitKey(0);

    // preprocess the image
    float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE];
    preprocess(output, img);
    //std::cout << "Preprocessed image size: " << preprocessed_img.size() << "\n";

    return 0;
}