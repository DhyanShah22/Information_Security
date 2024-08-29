#include <iostream>
#include <vector>
#include <string>

using namespace std;

string encryptRailFence(const string &text, int rails) {
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

string decryptRailFence(const string &cipher, int rails) {
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
    int choice;
    string text;
    int rails;

    cout << "Enter 0 to Encrypt or 1 to Decrypt: ";
    cin >> choice;
    cin.ignore();  

    cout << "Enter the number of rails: ";
    cin >> rails;
    cin.ignore();  
    cout << "Enter the text: ";
    getline(cin, text);

    if (choice == 0) {
        string encrypted = encryptRailFence(text, rails);
        cout << "Encrypted Text: " << encrypted << endl;
    } else if (choice == 1) {
        string decrypted = decryptRailFence(text, rails);
        cout << "Decrypted Text: " << decrypted << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
