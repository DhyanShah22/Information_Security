#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Encryptor {
public:
    Encryptor(const string& plaintext) : plaintext(plaintext) {}

    void encrypt() {
        string ciphertext;
        vector<string> words = splitPlaintext(plaintext);

        cout << "Plaintext: " << plaintext << endl;

        for (int i = 0; i < words.size(); ++i) {
            cout << "Word " << i + 1 << ": ";
            for (int j = 0; j < words[i].size(); ++j) {
                int shift = (i + 1) + j; 
                char cipher_char = shiftLetter(words[i][j], shift);
                cout << shift << " ";
                ciphertext += cipher_char;
            }
            ciphertext += " ";  
            cout << endl;
        }

        cout << "Ciphertext: " << ciphertext << endl;
    }

private:
    string plaintext;

    vector<string> splitPlaintext(const string& text) {
        vector<string> words;
        string word;
        istringstream stream(text);

        while (stream >> word) {
            words.push_back(word);
        }

        return words;
    }

    char shiftLetter(char letter, int shift) {
        return ((letter - 'A' + shift) % 26) + 'A';
    }
};

int main() {
    string plaintext;
    cout << "Enter plaintext (in capital letters only, up to nine words): ";
    getline(cin, plaintext);

    Encryptor encryptor(plaintext);
    encryptor.encrypt();

    return 0;
}
