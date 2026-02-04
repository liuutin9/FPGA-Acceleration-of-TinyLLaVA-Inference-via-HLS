#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/tokenizers_c.h"
#include "../include/tokenizers_cpp.h"

int main(int argc, char* argv[]) {

    // 設定tokenizer，需要讀取 tokenizer.json
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path/to/tokenizer.json>\n";
        return 1;
    }

    std::string tokenizer_json_path = argv[1];

    std::ifstream ifs(tokenizer_json_path);
    if (!ifs) {
        std::cerr << "Cannot open tokenizer file: " << tokenizer_json_path << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string json_content = buffer.str();

    // 解析過 tokenizer.json 後，創立 tokenizer object
    auto tokenizer = tokenizers::Tokenizer::FromBlobJSON(json_content);

    if (!tokenizer) {
        std::cerr << "Failed to load tokenizer from JSON\n";
        return -1;
    }
    
    // 測試數據
    std::vector<std::string> test_sentences = {
        "Hello, world!",
        "The quick brown fox jumps over the lazy dog.",
        "I love programming in C++ and Python.",
        "Let's test some emojis! ?????",
        "1234567890 - numbers and symbols #@$%^&*",
        "Newlines:\nThis is line one.\nThis is line two.",
        "Mixed English words only.",
        "Special chars: !@#$%^&*()_+-=[]{}|;:',.<>/?~",
        "Whitespace        test             with multiple spaces.",
        "Tabs\tand\nnewlines",
    };

    
    // tokenizer->Encode() : 將 string 編碼成 token ids (std::vector<int>)
    // tokenizer->Decode() : 將 token ids (std::vector<int>) 解碼成 string
    for (const auto& sentence : test_sentences) {
        auto encoding = tokenizer->Encode(sentence);
        std::cout << "Original: " << sentence << std::endl;
        std::cout << "Tokens: [";
        bool head = true;
        for (auto id : encoding) {
            if (!head) std::cout << ", ";
            head = false;
            std::cout << id;
        }
        std::cout << ']' << std::endl;
        std::cout << "Decoded: " << tokenizer->Decode(encoding) << std::endl << std::endl;
    }


    return 0;
}