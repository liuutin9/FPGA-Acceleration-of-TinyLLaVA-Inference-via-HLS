#include <CL/cl2.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define HIDDEN_SIZE 2560
#define NUM_BLOCKS 8
#define BLOCK_SIZE (HIDDEN_SIZE / NUM_BLOCKS)

static std::vector<char> load_binary_file(const std::string &xclbin_path) {
    std::ifstream stream(xclbin_path, std::ios::binary | std::ios::ate);
    if (!stream.is_open()) throw std::runtime_error("Failed to open xclbin file");
    size_t size = stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    stream.read(buffer.data(), size);
    return buffer;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <xclbin>\n";
        return 1;
    }

    std::string xclbin = argv[1];

    // ------------------------------
    // 1. 找 FPGA 裝置
    // ------------------------------
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    auto platform = platforms.front();

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
    auto device = devices.front();

    cl::Context context(device);
    cl::CommandQueue queue(context, device, CL_QUEUE_PROFILING_ENABLE);

    // ------------------------------
    // 2. 讀入 bitstream (xclbin)
    // ------------------------------
    auto binary = load_binary_file(xclbin);
    cl::Program::Binaries bins{{binary.data(), binary.size()}};
    cl::Program program(context, {device}, bins);
    cl::Kernel kernel(program, "kernel_phi_linear");

    // ------------------------------
    // 3. 建立資料
    // ------------------------------
    std::vector<float> in(HIDDEN_SIZE);
    std::vector<float> out(HIDDEN_SIZE, 0.0f);
    std::vector<float> bias(HIDDEN_SIZE);
    std::vector<float> weight(HIDDEN_SIZE * HIDDEN_SIZE);

    // 初始化隨機資料
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        in[i] = 1.0f; // 簡單一點
        bias[i] = 0.0f;
    }
    for (int i = 0; i < HIDDEN_SIZE * HIDDEN_SIZE; i++) {
        weight[i] = 1.0f; // 全部 1.0
    }

    // ------------------------------
    // 4. 建立 Buffer
    // ------------------------------
    cl::Buffer buf_in(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
                      sizeof(float) * HIDDEN_SIZE, in.data());
    cl::Buffer buf_out(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
                       sizeof(float) * HIDDEN_SIZE, out.data());
    cl::Buffer buf_weight(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
                          sizeof(float) * HIDDEN_SIZE * HIDDEN_SIZE, weight.data());
    cl::Buffer buf_bias(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
                        sizeof(float) * HIDDEN_SIZE, bias.data());

    // ------------------------------
    // 5. 設定 Kernel 參數
    // ------------------------------
    kernel.setArg(0, buf_out);
    kernel.setArg(1, buf_in);
    kernel.setArg(2, buf_weight);
    kernel.setArg(3, buf_bias);

    // ------------------------------
    // 6. 將資料送到 FPGA
    // ------------------------------
    queue.enqueueMigrateMemObjects({buf_in, buf_weight, buf_bias}, 0);

    // ------------------------------
    // 7. 執行 kernel
    // ------------------------------
    queue.enqueueTask(kernel);

    // ------------------------------
    // 8. 把結果搬回 host
    // ------------------------------
    queue.enqueueMigrateMemObjects({buf_out}, CL_MIGRATE_MEM_OBJECT_HOST);
    queue.finish();

    // ------------------------------
    // 9. 簡單檢查結果
    // ------------------------------
    std::cout << "Result sample: ";
    for (int i = 0; i < 10; i++) {
        std::cout << out[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
