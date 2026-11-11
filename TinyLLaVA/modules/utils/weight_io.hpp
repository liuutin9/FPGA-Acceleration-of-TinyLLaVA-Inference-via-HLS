// fp16 weight-file helpers shared by the CPU modules (connector, phi-2).
// Weight files are raw little-endian fp16, one file per HF tensor, named after the tensor,
// e.g. "language_model.model.layers.0.self_attn.q_proj.weight.bin".
#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace weight_io {

inline float fp16_to_fp32(uint16_t h) {
    const uint32_t sign = (h & 0x8000u) << 16;
    const uint32_t exp  = (h >> 10) & 0x1F;
    const uint32_t frac = h & 0x03FF;
    if (exp == 0) {
        const float v = std::ldexp(static_cast<float>(frac), -24);  // zero / subnormal
        return sign ? -v : v;
    }
    uint32_t bits;
    if (exp == 0x1F) {
        bits = sign | 0x7F800000u | (frac << 13);                   // inf / nan
    } else {
        bits = sign | ((exp + 112) << 23) | (frac << 13);           // normal
    }
    float f;
    std::memcpy(&f, &bits, sizeof(f));
    return f;
}

// 65536-entry lookup table, built once.
inline const float* fp16_table() {
    static std::vector<float> table = [] {
        std::vector<float> t(65536);
        for (uint32_t i = 0; i < 65536; ++i) t[i] = fp16_to_fp32(static_cast<uint16_t>(i));
        return t;
    }();
    return table.data();
}

inline std::string join(std::string dir, const std::string& name) {
    if (!dir.empty() && dir.back() != '/') dir += '/';
    return dir + name;
}

// Reads exactly `count` fp16 values; fails if the file is missing or has a different size.
inline bool read_fp16(const std::string& path, std::vector<uint16_t>& out, size_t count) {
    std::ifstream fin(path, std::ios::binary | std::ios::ate);
    if (!fin) {
        std::cerr << "Error: cannot open file " << path << std::endl;
        return false;
    }
    const size_t file_size = static_cast<size_t>(fin.tellg());
    if (file_size != count * sizeof(uint16_t)) {
        std::cerr << "Error: file size mismatch for " << path << " (expected " << count * sizeof(uint16_t)
                  << " bytes, got " << file_size << " bytes)" << std::endl;
        return false;
    }
    fin.seekg(0);
    out.resize(count);
    fin.read(reinterpret_cast<char*>(out.data()), file_size);
    return static_cast<bool>(fin);
}

inline bool read_fp16_as_f32(const std::string& path, std::vector<float>& out, size_t count) {
    std::vector<uint16_t> raw;
    if (!read_fp16(path, raw, count)) return false;
    const float* lut = fp16_table();
    out.resize(count);
    for (size_t i = 0; i < count; ++i) out[i] = lut[raw[i]];
    return true;
}

}  // namespace weight_io
