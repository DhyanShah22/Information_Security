#include <iostream>
#include <string>
#include <cctype> 
using namespace std;

const int CHAR_SET_SIZE = 95; 
string generateKey(const string& text, string key) {
    int textLen = text.length();
    int keyLen = key.length();

    if (keyLen >= textLen) return key;

    for (int i = keyLen; i < textLen; ++i) {
        int r = textLen - i; 
        char newKeyChar = (key[i % keyLen] + 3 + r) % CHAR_SET_SIZE;
        key += newKeyChar;
    }
    return key;
}

string encrypt(const string& plaintext, const string& key) {
    string ciphertext = "";
    string fullKey = generateKey(plaintext, key); 

    for (size_t i = 0; i < plaintext.length(); ++i) {
        if (isprint(plaintext[i])) { 
            int ptChar = plaintext[i] - ' ';
            int keyChar = fullKey[i] - ' ';
            char encryptedChar = ((ptChar + keyChar) % CHAR_SET_SIZE) + ' ';
            ciphertext += encryptedChar;
        } else {
            ciphertext += plaintext[i]; 
        }
    }
    return ciphertext;
}


string decrypt(const string& ciphertext, const string& key) {
    string plaintext = "";
    string fullKey = generateKey(ciphertext, key); 
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        if (isprint(ciphertext[i])) { 
            int ctChar = ciphertext[i] - ' ';
            int keyChar = fullKey[i] - ' ';
            char decryptedChar = ((ctChar - keyChar + CHAR_SET_SIZE) % CHAR_SET_SIZE) + ' ';
            plaintext += decryptedChar;
        } else {
            plaintext += ciphertext[i]; 
        }
    }
    return plaintext;
}

int main() {
    int choice;
    string text, key;

    cout << "Modified Vigenère Cipher Program\n";
    cout << "Enter 0 for Encryption or 1 for Decryption: ";
    cin >> choice;
    cin.ignore(); 

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the key (alphanumeric and symbols allowed): ";
    getline(cin, key);

    if (choice == 0) {
        cout << "Encrypted Text: " << encrypt(text, key) << endl;
    } else if (choice == 1) {
        cout << "Decrypted Text: " << decrypt(text, key) << endl;
    } else {
        cout << "Invalid choice. Please enter 0 for Encryption or 1 for Decryption.\n";
    }

    return 0;
}
