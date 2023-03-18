
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Code for turning a string into an integer
unsigned long hash_str(const std::string& str) {
    unsigned long hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char) str[i];
    return hash;
}

int main(int argc, char const *argv[]) {
	
	// Open file
	if (argc != 2) exit(1);
	string filePath = argv[1];
	string fileExtension = filePath.substr(filePath.find_last_of(".") + 1);
	ifstream inputFile(filePath, ios::binary);
	
	// Encrypt or Decrypt
	short encrypting;
	cout << "Encrypt or Decrypt (1 or 0): ";
	cin >> encrypting;
	if (encrypting != 1 && encrypting != 0) exit(1);
	ofstream outputFile((encrypting ? "encrypted." : "decrypted.") + fileExtension, ios::binary);

	// Encryption key
	string key;
	cout << "Encryption key: ";
	cin >> key;

	// Seed the encryption
	srand(hash_str(key));
	for (int i=0; i<10; ++i) srand(rand());

	// Encrypt data
	short dir = encrypting * 2 - 1;
	char c;
	while (inputFile.get(c)) {
		unsigned char byte = static_cast<unsigned char>(c);
		byte = ((byte + rand() * dir) % 256 + 256) % 256;
		outputFile.put(byte);
	}

	// Wrapping up
	inputFile.close();
	outputFile.close();
	system("pause");
	return 0;
}
