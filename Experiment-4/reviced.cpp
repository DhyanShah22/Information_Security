#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Caesar Cipher encryption
std::string caesarEncrypt(const std::string &text, int shift) {
    std::string result = text;
    for (char &c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }
    return result;
}

// Caesar Cipher decryption
std::string caesarDecrypt(const std::string &text, int shift) {
    return caesarEncrypt(text, 26 - shift);  // Reverse shift for decryption
}

// Columnar Transposition Cipher encryption
std::string columnarEncrypt(const std::string &text, const std::string &key) {
    int numRows = (text.size() + key.size() - 1) / key.size(); // Calculate the number of rows needed
    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(key.size(), 'X')); // Create matrix filled with 'X'
    
    // Fill the matrix row-wise
    int index = 0;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < key.size(); c++) {
            if (index < text.size()) {
                matrix[r][c] = text[index++];
            }
        }
    }

    // Determine the order of the columns based on the key
    std::vector<int> colOrder(key.size());
    for (int i = 0; i < key.size(); i++) {
        colOrder[i] = i;
    }

    std::sort(colOrder.begin(), colOrder.end(), [&](int a, int b) {
        return key[a] < key[b];
    });

    // Read columns in order to form the encrypted text
    std::string cipherText;
    for (int col : colOrder) {
        for (int row = 0; row < numRows; row++) {
            cipherText += matrix[row][col];
        }
    }

    return cipherText;
}

// Columnar Transposition Cipher decryption
std::string columnarDecrypt(const std::string &cipherText, const std::string &key, int originalLength) {
    int numRows = (originalLength + key.size() - 1) / key.size(); // Calculate number of rows
    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(key.size()));

    // Determine the order of columns based on the key
    std::vector<int> colOrder(key.size());
    for (int i = 0; i < key.size(); i++) {
        colOrder[i] = i;
    }

    std::sort(colOrder.begin(), colOrder.end(), [&](int a, int b) {
        return key[a] < key[b];
    });

    // Fill the matrix column-wise using the ciphertext
    int index = 0;
    for (int col : colOrder) {
        for (int row = 0; row < numRows; row++) {
            if (index < cipherText.size()) {
                matrix[row][col] = cipherText[index++];
            }
        }
    }

    // Read the plaintext row-wise
    std::string plainText;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < key.size(); c++) {
            plainText += matrix[r][c];
        }
    }

    // Remove padding 'X' characters added during encryption
    while (plainText.size() > originalLength) {
        plainText.pop_back();
    }

    return plainText;
}

// Combined encryption function
std::string combinedEncrypt(const std::string &text, const std::string &key, int shift) {
    std::string caesarEncrypted = caesarEncrypt(text, shift);
    return columnarEncrypt(caesarEncrypted, key);
}

// Combined decryption function
std::string combinedDecrypt(const std::string &cipherText, const std::string &key, int shift, int originalLength) {
    std::string columnarDecrypted = columnarDecrypt(cipherText, key, originalLength);
    return caesarDecrypt(columnarDecrypted, shift);
}

int main() {
    std::string text, key;
    int choice, shift;

    std::cout << "Enter 0 for Encrypt and 1 for Decrypt: ";
    std::cin >> choice;
    std::cin.ignore(); 

    if (choice == 0) {
        std::cout << "Enter the text to encrypt: ";
        std::getline(std::cin, text);
        std::cout << "Enter the key (a word): ";
        std::getline(std::cin, key);
        std::cout << "Enter the shift for Caesar Cipher (1-25): ";
        std::cin >> shift;

        std::string encryptedText = combinedEncrypt(text, key, shift);
        std::cout << "Encrypted Text: " << encryptedText << std::endl;
    } else if (choice == 1) {
        std::cout << "Enter the text to decrypt: ";
        std::getline(std::cin, text);
        std::cout << "Enter the key (a word): ";
        std::getline(std::cin, key);
        std::cout << "Enter the shift for Caesar Cipher (1-25): ";
        std::cin >> shift;

        int originalLength;
        std::cout << "Enter the original length of the text: ";
        std::cin >> originalLength; // Store original length to handle padding removal
        
        std::string decryptedText = combinedDecrypt(text, key, shift, originalLength);
        std::cout << "Decrypted Text: " << decryptedText << std::endl;
    } else {
        std::cout << "Invalid choice! Please enter 0 or 1." << std::endl;
    }

    return 0;
}
