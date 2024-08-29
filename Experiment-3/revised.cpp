#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string substitute(const string &text, const string &chart) {
    string substituted;
    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            substituted += chart[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            substituted += chart[c - 'a'];
        } else {
            substituted += c; 
        }
    }
    return substituted;
}

string circularShift(const string &text, int k, bool right) {
    int n = text.size();
    k = k % n;
    if (right) {
        return text.substr(n - k) + text.substr(0, n - k);
    } else {
        return text.substr(k) + text.substr(0, k);
    }
}

string railFenceEncrypt(const string &text, int rails) {
    if (rails == 1) return text;

    vector<string> rail(rails);
    int direction = 1, row = 0;

    for (char c : text) {
        rail[row] += c;
        row += direction;
        if (row == 0 || row == rails - 1) direction *= -1;
    }

    string ciphertext;
    for (const string &line : rail) {
        ciphertext += line;
    }

    return ciphertext;
}

string railFenceDecrypt(const string &cipher, int rails) {
    if (rails == 1) return cipher;

    vector<string> rail(rails, string(cipher.length(), '\0'));
    int direction = 1, row = 0, index = 0;

    for (int i = 0; i < cipher.length(); ++i) {
        rail[row][i] = '*';
        row += direction;
        if (row == 0 || row == rails - 1) direction *= -1;
    }

    for (int r = 0; r < rails; ++r) {
        for (int c = 0; c < rail[r].length(); ++c) {
            if (rail[r][c] == '*' && index < cipher.length()) {
                rail[r][c] = cipher[index++];
            }
        }
    }

    string plaintext;
    row = 0;
    direction = 1;
    for (int i = 0; i < cipher.length(); ++i) {
        plaintext += rail[row][i];
        row += direction;
        if (row == 0 || row == rails - 1) direction *= -1;
    }

    return plaintext;
}

int main() {
    int choice, rails, key;
    string text, chart = "XABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

    cout << "Enter 0 to Encrypt or 1 to Decrypt: ";
    cin >> choice;
    cin.ignore(); 

    cout << "Enter the number of rails: ";
    cin >> rails;
    cin.ignore(); 

    cout << "Enter the key value: ";
    cin >> key;
    cin.ignore();
    cout << "Enter the text: ";
    getline(cin, text);

    if (choice == 0) {
        string substituted = substitute(text, chart);
        bool rightShift = key % 2 != 0; // Right shift if key is odd
        string shifted = circularShift(substituted, key, rightShift);
        string encrypted = railFenceEncrypt(shifted, rails);
        cout << "Encrypted Text: " << encrypted << endl;
    } else if (choice == 1) {
        string decryptedRailFence = railFenceDecrypt(text, rails);
        bool rightShift = key % 2 != 0; 
        string shifted = circularShift(decryptedRailFence, key, !rightShift); 
        string substituted = substitute(shifted, chart);
        cout << "Decrypted Text: " << substituted << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
