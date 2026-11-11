#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>

// Same values as Siglip_config.hpp; defined here too so this header can be included on its own.
#ifndef NUM_CHANNELS
#define NUM_CHANNELS 3
#endif
#ifndef IMAGE_SIZE
#define IMAGE_SIZE 384
#endif

const float IMAGE_MEAN[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};
const float IMAGE_STD[NUM_CHANNELS] = {0.5f, 0.5f, 0.5f};

// channels: R, G, B planes (CV_32FC1, values in [0, 1]) -> out = (x - mean) / std, CHW
void normalize(float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const std::vector<cv::Mat>& channels);

// SiglipImageProcessor: BGR->RGB, resize 384x384, x/255, normalize, HWC->CHW
void preprocess(float output[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], const cv::Mat& image_bgr);
