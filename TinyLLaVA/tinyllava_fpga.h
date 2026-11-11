// Entry points of the two FPGA hosts, used by tinyllava_fpga.cpp.
// Both hosts are compiled with -DTINYLLAVA_LIB so their standalone main() is dropped.
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace siglip_host {
// 26 SigLIP encoder layers + Connector on the FPGA.
//   embeddings     : 729 * 1152 floats (patch embedding + position embedding)
//   image_features : 728 * 2560 floats out (token 0 dropped, projected to Phi-2 space)
int run_siglip_connector(const char* platform_vendor, const char* device_name, const char* xclbin,
                         const float* embeddings, float* image_features, const std::string& weight_dir);
}  // namespace siglip_host

namespace phi_host {
// Phi-2 on the FPGA, token by token. Every IMAGE_TOKEN_INDEX (-200) in input_ids is
// replaced by num_image_tokens rows of image_features.
int phi_generate(const char* platform_vendor, const char* device_name, const char* xclbin,
                 const std::vector<int32_t>& input_ids, const float* image_features, int num_image_tokens,
                 int max_new_tokens, std::vector<int32_t>& output_ids, const std::string& weight_dir);
}  // namespace phi_host
