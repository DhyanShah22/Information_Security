#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string substituteEncrypt(const string& text, const unordered_map<char, char>& subMap) {
    string cipherText;
    for (char ch : text) {
        if (subMap.find(toupper(ch)) != subMap.end()) {
            cipherText += subMap.at(toupper(ch));
        } else {
            cipherText += ch; 
        }
    }
    return cipherText;
}

string substituteDecrypt(const string& text, const unordered_map<char, char>& revSubMap) {
    string plainText;
    for (char ch : text) {
        if (revSubMap.find(toupper(ch)) != revSubMap.end()) {
            plainText += revSubMap.at(toupper(ch));
        } else {
            plainText += ch; 
        }
    }
    return plainText;
}

int main() {
    string text;
    int choice;

    unordered_map<char, char> subMap = {
        {'A', 'M'}, {'B', 'N'}, {'C', 'O'}, {'D', 'P'}, {'E', 'Q'}, {'F', 'R'},
        {'G', 'S'}, {'H', 'T'}, {'I', 'U'}, {'J', 'V'}, {'K', 'W'}, {'L', 'X'},
        {'M', 'Y'}, {'N', 'Z'}, {'O', 'A'}, {'P', 'B'}, {'Q', 'C'}, {'R', 'D'},
        {'S', 'E'}, {'T', 'F'}, {'U', 'G'}, {'V', 'H'}, {'W', 'I'}, {'X', 'J'},
        {'Y', 'K'}, {'Z', 'L'}
    };

    unordered_map<char, char> revSubMap;
    for (const auto& pair : subMap) {
        revSubMap[pair.second] = pair.first;
    }

    cout << "Choose an option (1 for encrypt, 2 for decrypt): ";
    cin >> choice;
    cin.ignore(); 

    cout << "Enter the message: ";
    getline(cin, text);

    if (choice == 1) {
        string encryptedText = substituteEncrypt(text, subMap);
        cout << "Encrypted Message: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = substituteDecrypt(text, revSubMap);
        cout << "Decrypted Message: " << decryptedText << endl;
    } else {
        cout << "Invalid choice" << endl;
    }

    return 0;
}
