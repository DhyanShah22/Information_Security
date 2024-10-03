#include <iostream>
#include <string>
#include <cctype> 
using namespace std;

string encrypt(const string& plaintext, const string& key) {
    string ciphertext = "";
    int keyLength = key.length();

    for (size_t i = 0; i < plaintext.length(); ++i) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLength]) - 'A';
            char encryptedChar = ((plaintext[i] - offset + keyChar) % 26) + offset;
            ciphertext += encryptedChar;
        } else {
            ciphertext += plaintext[i];
        }
    }
    return ciphertext;
}

string decrypt(const string& ciphertext, const string& key) {
    string plaintext = "";
    int keyLength = key.length();

    for (size_t i = 0; i < ciphertext.length(); ++i) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLength]) - 'A';
            char decryptedChar = ((ciphertext[i] - offset - keyChar + 26) % 26) + offset;
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

    cout << "Vigenère Cipher Program\n";
    cout << "Enter 0 for Encryption or 1 for Decryption: ";
    cin >> choice;
    cin.ignore();
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the key (alphabetic characters only): ";
    getline(cin, key);

    for (char c : key) {
        if (!isalpha(c)) {
            cout << "Invalid key. The key must contain only alphabetic characters.\n";
            return 1;
        }
    }

    if (choice == 0) {
        cout << "Encrypted Text: " << encrypt(text, key) << endl;
    } else if (choice == 1) {
        cout << "Decrypted Text: " << decrypt(text, key) << endl;
    } else {
        cout << "Invalid choice. Please enter 0 for Encryption or 1 for Decryption.\n";
    }

    return 0;
}
