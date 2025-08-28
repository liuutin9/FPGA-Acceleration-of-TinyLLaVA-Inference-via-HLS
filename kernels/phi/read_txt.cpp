#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int readTxtFile(const char *filename, string &content) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }
    content.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return 0;
}

int main() {
    string content;
    if (readTxtFile("input_string.txt", content) == 0) {
        cout << "File content:\n" << content << endl;
    }
    return 0;
}