#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;


int modExp(int base, int exp, int mod){
    int result = 1;
    base =  base % mod;
    while(exp > 0){
        if(exp % 2 == 1){
            result = (result * base) % mod;
        }
        exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
string encrypt(string plaintext, int e, int n) {
    string ciphertext = "";
    for (char c : plaintext) {
        int encryptedChar = modExp(c, e, n);
        ciphertext += to_string(encryptedChar) + " ";
    }
    return ciphertext;
}

string decrypt(string ciphertext, int d, int n) {
    string plaintext = "";
    stringstream ss(ciphertext);
    string temp;

    while (ss >> temp) {
        int encryptedChar = stoi(temp);
        plaintext += (char)modExp(encryptedChar, d, n);
    }
    return plaintext;
}

int modInverse(int e, int phi){
    e = e % phi;
    for(int d = 0; d < phi; d++){
        if((e * d) % phi == 1){
            return d;
        }
    }
}

int main() {
    int p = 61, q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17;
    int d = modInverse(e, phi);

    cout << "RSA Cipher" << endl;
    cout << "Choose operation (0: Encrypt, 1: Decrypt): ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        cout << "Enter text to encrypt: ";
        string plaintext;
        cin.ignore();
        getline(cin, plaintext);
        string ciphertext = encrypt(plaintext, e, n);
        cout << "Encrypted Text: " << ciphertext << endl;
    } else if (choice == 1) {
        cout << "Enter text to decrypt (space-separated integers): ";
        string ciphertext;
        cin.ignore();
        getline(cin, ciphertext);
        string plaintext = decrypt(ciphertext, d, n);
        cout << "Decrypted Text: " << plaintext << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
