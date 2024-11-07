#include <iostream>
#include <string>
#include <algorithm>

class Sender {
public:
    Sender(const std::string& plaintext, const std::string& key)
        : plaintext(plaintext), key(key) {
        min_letter = *std::min_element(plaintext.begin(), plaintext.end());
        
        extended_plaintext = plaintext;
        if (plaintext.size() % key.size() != 0) {
            extended_plaintext += std::string(key.size() - (plaintext.size() % key.size()), min_letter);
        }
    }

    std::string getMinLetter() const {
        return std::string(1, min_letter);
    }

    std::string getExtendedPlaintext() const {
        return extended_plaintext;
    }

    std::string encrypt() {
        std::string ciphertext;
        int k = key.size();
        
        for (int i = 0; i < extended_plaintext.size(); ++i) {
            char plain_char = extended_plaintext[i];
            int shift = key[i % k] - '0';
            char cipher_char = ((plain_char - 'A' + shift) % 26) + 'A';
            ciphertext += cipher_char;
        }
        
        return ciphertext;
    }

private:
    std::string plaintext;
    std::string key;
    std::string extended_plaintext;
    char min_letter;
};

class Receiver {
public:
    void displayCiphertext(const std::string& ciphertext) const {
        std::cout << "Ciphertext: " << ciphertext << std::endl;
    }
    
    void displayMinLetter(const std::string& min_letter) const {
        std::cout << "Minimum letter used as filler: " << min_letter << std::endl;
    }

    void displayExtendedPlaintext(const std::string& extended_plaintext) const {
        std::cout << "Revised plaintext after padding: " << extended_plaintext << std::endl;
    }
};

int main() {
    std::string plaintext, key;
    std::cout << "Enter plaintext (in capital letters only): ";
    std::cin >> plaintext;
    std::cout << "Enter key (in numbers only): ";
    std::cin >> key;

    Sender sender(plaintext, key);
    Receiver receiver;

    receiver.displayMinLetter(sender.getMinLetter());
    receiver.displayExtendedPlaintext(sender.getExtendedPlaintext());

    std::string ciphertext = sender.encrypt();
    receiver.displayCiphertext(ciphertext);

    return 0;
}
