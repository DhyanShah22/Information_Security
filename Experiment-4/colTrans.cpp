#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string encrypt(const std::string &text, const std::string &key) {
    int numRows = text.size() / key.size();
    if (text.size() % key.size() != 0) {
        numRows++; 
    }

    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(key.size(), 'X'));
    int index = 0;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < key.size(); c++) {
            if (index < text.size()) {
                matrix[r][c] = text[index++];
            }
        }
    }

    std::vector<int> colOrder(key.size());
    for (int i = 0; i < key.size(); i++) {
        colOrder[i] = i;
    }

    std::sort(colOrder.begin(), colOrder.end(), [&](int a, int b) {
        return key[a] < key[b];
    });

    std::string cipherText;
    for (int col : colOrder) {
        for (int row = 0; row < numRows; row++) {
            cipherText += matrix[row][col];
        }
    }

    return cipherText;
}

std::string decrypt(const std::string &cipherText, const std::string &key) {
    int numRows = cipherText.size() / key.size();
    if (cipherText.size() % key.size() != 0) {
        numRows++;
    }

    std::vector<int> colOrder(key.size());
    for (int i = 0; i < key.size(); i++) {
        colOrder[i] = i;
    }

    std::sort(colOrder.begin(), colOrder.end(), [&](int a, int b) {
        return key[a] < key[b];
    });

    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(key.size()));

    int index = 0;
    for (int col : colOrder) {
        for (int row = 0; row < numRows; row++) {
            if (index < cipherText.size()) {
                matrix[row][col] = cipherText[index++];
            }
        }
    }

    std::string plainText;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < key.size(); c++) {
            plainText += matrix[r][c];
        }
    }

    plainText.erase(std::find(plainText.begin(), plainText.end(), 'X'), plainText.end());
    return plainText;
}

int main() {
    std::string text, key;
    int choice;

    std::cout << "Enter 0 for Encrypt and 1 for Decrypt: ";
    std::cin >> choice;
    std::cin.ignore(); 

    if (choice == 0) {
        std::cout << "Enter the text to encrypt: ";
        std::getline(std::cin, text);
        std::cout << "Enter the key (a word): ";
        std::getline(std::cin, key);

        std::string encryptedText = encrypt(text, key);
        std::cout << "Encrypted Text: " << encryptedText << std::endl;
    } else if (choice == 1) {
        std::cout << "Enter the text to decrypt: ";
        std::getline(std::cin, text);
        std::cout << "Enter the key (a word): ";
        std::getline(std::cin, key);

        std::string decryptedText = decrypt(text, key);
        std::cout << "Decrypted Text: " << decryptedText << std::endl;
    } else {
        std::cout << "Invalid choice! Please enter 0 or 1." << std::endl;
    }

    return 0;
}
