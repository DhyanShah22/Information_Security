#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Encryptor {
public:
    Encryptor(const std::string& plaintext) : plaintext(plaintext) {}

    void encrypt() {
        std::string ciphertext;
        std::vector<std::string> words = splitPlaintext(plaintext);

        std::cout << "Plaintext: " << plaintext << std::endl;

        for (int i = 0; i < words.size(); ++i) {
            std::cout << "Word " << i + 1 << ": ";
            for (int j = 0; j < words[i].size(); ++j) {
                int shift = (i + 1) + j;  // i+1 (1-based word index) + j (0-based letter index)
                char cipher_char = shiftLetter(words[i][j], shift);
                std::cout << shift << " ";
                ciphertext += cipher_char;
            }
            ciphertext += " ";  // Add space between words in ciphertext
            std::cout << std::endl;
        }

        std::cout << "Ciphertext: " << ciphertext << std::endl;
    }

private:
    std::string plaintext;

    // Helper function to split plaintext into words
    std::vector<std::string> splitPlaintext(const std::string& text) {
        std::vector<std::string> words;
        std::string word;
        std::istringstream stream(text);

        while (stream >> word) {
            words.push_back(word);
        }

        return words;
    }

    // Helper function to shift a character by 'shift' positions in the alphabet
    char shiftLetter(char letter, int shift) {
        return ((letter - 'A' + shift) % 26) + 'A';
    }
};

int main() {
    std::string plaintext;
    std::cout << "Enter plaintext (in capital letters only, up to nine words): ";
    std::getline(std::cin, plaintext);

    Encryptor encryptor(plaintext);
    encryptor.encrypt();

    return 0;
}
