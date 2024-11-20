#include <iostream>
#include <string>

using namespace std;

string encryptAlternatingShift(const string& plaintext) {
    string ciphertext;
    int shift = 2;
    int direction = 1;

    for (size_t i = 0; i < plaintext.size(); ++i) {
        char charToEncrypt = plaintext[i];
        if (isalpha(charToEncrypt)) {
            char base = isupper(charToEncrypt) ? 'A' : 'a';
            char newChar = (charToEncrypt - base + direction * shift) % 26 + base;
            ciphertext += newChar;
            direction *= -1;
            shift += 1;
        } else {
            ciphertext += charToEncrypt;
        }
    }

    return ciphertext;
}

int main() {
    string plaintext = "SECRET";
    string ciphertext = encryptAlternatingShift(plaintext);
    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    return 0;
}
