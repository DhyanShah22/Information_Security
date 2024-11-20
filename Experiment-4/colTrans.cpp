#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

string encrypt(const string &text, const string &key){
    int numRows = (text.size() + key.size() - 1) / key.size();
    vector<vector<char>> matrix(numRows, vector<char>(key.size(), 'X'));
    int index = 0;
    for(int r = 0; r <numRows; r++){
        for(int c = 0; c < key.size(); c++){
            if(index < text.size()) matrix[r][c] = text[index++];
        }
    }

    vector<int>colOrder(key.size());
    iota(colOrder.begin(), colOrder.end(), 0);
    sort(colOrder.begin(), colOrder.end(), [&](int a, int b) { return key[a] < key[b];});

    string ciphertext;
    for(int col : colOrder){
        for(int row = 0; row < numRows; row++){
            ciphertext += matrix[row][col];
        }
    }
    return ciphertext;
}
string decrypt(const string &cipherText, const string &key) {
    int numRows = (cipherText.size() + key.size() - 1) / key.size();
    vector<int> colOrder(key.size());
    iota(colOrder.begin(), colOrder.end(), 0);
    sort(colOrder.begin(), colOrder.end(), [&](int a, int b) { return key[a] < key[b]; });

    vector<vector<char>> matrix(numRows, vector<char>(key.size()));
    int index = 0;
    for (int col : colOrder)
        for (int row = 0; row < numRows; row++)
            if (index < cipherText.size()) matrix[row][col] = cipherText[index++];

    string plainText;
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < key.size(); c++)
            plainText += matrix[r][c];

    plainText.erase(find(plainText.begin(), plainText.end(), 'X'), plainText.end());
    return plainText;
}

int main() {
    string text, key;
    int choice;

    cout << "Enter 0 for Encrypt and 1 for Decrypt: ";
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Enter the text to encrypt: ";
        getline(cin, text);
        cout << "Enter the key: ";
        getline(cin, key);
        cout << "Encrypted Text: " << encrypt(text, key) << endl;
    } else if (choice == 1) {
        cout << "Enter the text to decrypt: ";
        getline(cin, text);
        cout << "Enter the key: ";
        getline(cin, key);
        cout << "Decrypted Text: " << decrypt(text, key) << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
