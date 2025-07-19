#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>

const float IMAGE_MEAN[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};
const float IMAGE_STD[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};

void normalize(float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], auto channels) ;

void preprocess(float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const cv::Mat& image_bgr) ;

