#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Sender {
public:
    Sender(const string& plaintext, const string& key)
        : plaintext(plaintext), key(key) {
        min_letter = *min_element(plaintext.begin(), plaintext.end());
        
        extended_plaintext = plaintext;
        if (plaintext.size() % key.size() != 0) {
            extended_plaintext += string(key.size() - (plaintext.size() % key.size()), min_letter);
        }
    }

    string getMinLetter() const {
        return string(1, min_letter);
    }

    string getExtendedPlaintext() const {
        return extended_plaintext;
    }

    string encrypt() {
        string ciphertext;
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
    string plaintext;
    string key;
    string extended_plaintext;
    char min_letter;
};

class Receiver {
public:
    void displayCiphertext(const string& ciphertext) const {
        cout << "Ciphertext: " << ciphertext << endl;
    }
    
    void displayMinLetter(const string& min_letter) const {
        cout << "Minimum letter used as filler: " << min_letter << endl;
    }

    void displayExtendedPlaintext(const string& extended_plaintext) const {
        cout << "Revised plaintext after padding: " << extended_plaintext << endl;
    }
};

int main() {
    string plaintext, key;
    cout << "Enter plaintext (in capital letters only): ";
    cin >> plaintext;
    cout << "Enter key (in numbers only): ";
    cin >> key;

    Sender sender(plaintext, key);
    Receiver receiver;

    receiver.displayMinLetter(sender.getMinLetter());
    receiver.displayExtendedPlaintext(sender.getExtendedPlaintext());

    string ciphertext = sender.encrypt();
    receiver.displayCiphertext(ciphertext);

    return 0;
}
