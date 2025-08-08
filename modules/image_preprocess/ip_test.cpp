#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// config
#define IMAGE_SIZE 384
#define NUM_CHANNELS 3
#define rescale_factor 0.00392156862745098

// Note: change to double
// float => double & CV_32FC3 => CV_64FC3 & Vec3f => Vec3d

void normalize(float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], std::vector<cv::Mat> channels) {
    // 假設 image 是 CV_32FC3 格式，且值域為 [0, 1]
    const float mean[NUM_CHANNELS] = {0.5, 0.5, 0.5};
    const float std[NUM_CHANNELS]  = {0.5, 0.5, 0.5};

    for (int c = 0; c < NUM_CHANNELS; ++c) {
        for (int i = 0; i < IMAGE_SIZE; ++i) {
            for (int j = 0; j < IMAGE_SIZE; ++j) {
                float pixel = channels[c].at<float>(i, j);
                out[c][i][j] = (pixel - mean[c]) / std[c];
            }
        }
    }
}

void preprocess(float out[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const cv::Mat& image_bgr) {
    // 1. 將 BGR 轉為 RGB
    cv::Mat image_rgb;
    cv::cvtColor(image_bgr, image_rgb, cv::COLOR_BGR2RGB);
    std::cout << "Before preprocess shape: (" << image_rgb.cols << ", " << image_rgb.rows << ", " << image_rgb.channels();
    std::cout << "), first pixel value: " << image_rgb.at<cv::Vec3b>(0, 0) << std::endl;

    // 2. 調整大小為 384x384
    cv::Mat resized;
    cv::resize(image_rgb, resized, cv::Size(IMAGE_SIZE, IMAGE_SIZE), 0 , 0, cv::INTER_AREA);
    std::cout << "Resized shape: (" << resized.cols << ", " << resized.rows << ", " << resized.channels();
    std::cout << "), first pixel value: " << resized.at<cv::Vec3b>(0, 0) << std::endl;

    // 3. 調整至 [0, 1] 範圍
    cv::Mat rescaled;
    resized.convertTo(rescaled, CV_32FC3, 1.0 / 255.0);
    std::cout << "Rescaled shape: (" << rescaled.cols << ", " << rescaled.rows << ", " << rescaled.channels();
    std::cout << "), first pixel value: [" << rescaled.at<cv::Vec3f>(0, 0)[0] << ", " << rescaled.at<cv::Vec3f>(0, 0)[1] << ", " << rescaled.at<cv::Vec3f>(0, 0)[2] << "]" << std::endl;

    // 4. 拆分通道（R, G, B)
    std::vector<cv::Mat> channels(3);
    cv::split(rescaled, channels);
    std::cout << "split shape: (" << 3 << ", " << channels[0].cols << ", " << channels[0].rows;
    std::cout << "), first pixel of each channel: " << channels[0].at<float>(0, 0) << ", " << channels[1].at<float>(0, 0) << ", " << channels[2].at<float>(0, 0) << std::endl;

    // 5. 正規化   
    normalize(out, channels);
    std::cout << "normalize shape: (" << NUM_CHANNELS << ", " << IMAGE_SIZE << ", " << IMAGE_SIZE;
    std::cout << "), first pixel of each channel: " << out[0][0][0] << ", " << out[1][0][0] << ", " << out[2][0][0] << std::endl;
}

int main() {
    std::string image_path = "test.jpg";

    // load image in BGR & HWC format => [Height(=image.rows), Width(=image.cols), Channels]
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Failed to load image from file: " << image_path << "\n";
        return 1;
    }

    // preprocess the image
    float preprocessed_img[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE];
    preprocess(preprocessed_img, img);
    std::cout << "After preprocess shape: (3, 384, 384)";
    std::cout << ", first pixel value: " << preprocessed_img[0][0][0] << ", " << preprocessed_img[1][0][0] << ", " << preprocessed_img[2][0][0] << std::endl;
    
    // Save the preprocessed image to a binary file
    std::string filename = "preprocessed_implementation_cpp.bin";
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Cannot open file for writing: " << filename << std::endl;
        return 0;
    }
    ofs.write(reinterpret_cast<const char*>(preprocessed_img), sizeof(float) * NUM_CHANNELS * IMAGE_SIZE * IMAGE_SIZE);
    ofs.close();

    return 0;
}