#include <iostream>
#include <string>
#include <string.h>
#include <random>
#include <fstream>
using namespace std;

const char* readFile(const char* fpath, streampos& size) {
    ifstream file(fpath, ios::binary | ios::ate);
    if (!file.is_open()) { cout << "NO FILE" << endl; system("pause"); exit(1); }
    size = file.tellg();
    char* buffer = new char[size];
    file.seekg(0, ios::beg);
    file.read(buffer, size);
    file.close();
    return buffer;
}

int main(int argc, char const** argv) {
    // Prep
    string seed;
    streampos size;
    const char* plaintext = readFile(argv[1], size);
    cout << "Key: ";
    getline(cin, seed);
    
    // Output
    string path = argv[1];
    string ext = path.substr(path.find_last_of(".") + 1);
    ofstream outputFile("crypted." + ext, ios::binary);

    // Encrypt
    seed_seq ss(seed.begin(), seed.end());
    mt19937 gen(ss);
    uniform_int_distribution<> dis(-128, 127);
    for (int i=0; i<size; ++i) outputFile.put(plaintext[i] ^ static_cast<char>(dis(gen)));

    // Cleanup
    outputFile.close();
    return 0;
}
