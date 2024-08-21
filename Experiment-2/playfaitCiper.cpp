#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

string formatText(const string &text) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            result += tolower(c);
        }
    }
    return result;
}

vector<vector<char>> generateKeyTable(const string &key) {
    vector<vector<char>> table(5, vector<char>(5, ' '));
    string formattedKey = formatText(key);
    string usedChars;

    for (char c : formattedKey) {
        if (usedChars.find(c) == string::npos && c != 'j') {
            usedChars += c;
        }
    }

    if (usedChars.find('i') == string::npos && usedChars.find('j') == string::npos) {
        usedChars += 'i';
    } else if (usedChars.find('i') != string::npos && usedChars.find('j') == string::npos) {
        usedChars += 'j';
    }

    for (char c = 'a'; c <= 'z'; ++c) {
        if (c != 'j' && usedChars.find(c) == string::npos) {
            usedChars += c;
        }
    }

    int index = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            table[i][j] = usedChars[index++];
        }
    }
    return table;
}

pair<int, int> findPosition(const vector<vector<char>> &table, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (table[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

string preprocessText(const string &text) {
    string result;
    string formattedText = formatText(text);

    for (size_t i = 0; i < formattedText.length(); ++i) {
        result += formattedText[i];
        if (i + 1 < formattedText.length() && formattedText[i] == formattedText[i + 1]) {
            result += 'x';
        }
    }
    if (result.length() % 2 != 0) {
        result += 'x';
    }
    return result;
}

string encryptPair(char a, char b, const vector<vector<char>> &table) {
    auto [row1, col1] = findPosition(table, a);
    auto [row2, col2] = findPosition(table, b);

    if (row1 == row2) {
        return {table[row1][(col1 + 1) % 5], table[row2][(col2 + 1) % 5]};
    } else if (col1 == col2) {
        return {table[(row1 + 1) % 5][col1], table[(row2 + 1) % 5][col2]};
    } else {
        return {table[row1][col2], table[row2][col1]};
    }
}

string decryptPair(char a, char b, const vector<vector<char>> &table) {
    auto [row1, col1] = findPosition(table, a);
    auto [row2, col2] = findPosition(table, b);

    if (row1 == row2) {
        return {table[row1][(col1 + 4) % 5], table[row2][(col2 + 4) % 5]};
    } else if (col1 == col2) {
        return {table[(row1 + 4) % 5][col1], table[(row2 + 4) % 5][col2]};
    } else {
        return {table[row1][col2], table[row2][col1]};
    }
}

string playfairCipher(const string &text, const string &key, bool encrypt = true) {
    auto table = generateKeyTable(key);
    string processedText = preprocessText(text);
    string result;

    for (size_t i = 0; i < processedText.length(); i += 2) {
        if (encrypt) {
            result += encryptPair(processedText[i], processedText[i + 1], table);
        } else {
            result += decryptPair(processedText[i], processedText[i + 1], table);
        }
    }
    return result;
}

int main() {
    string key;
    string plaintext;
    int option;

    cout << "Enter the key: ";
    getline(cin, key);

    cout << "Enter 1 for encryption or 0 for decryption: ";
    cin >> option;
    cin.ignore(); // To ignore the newline character after the integer input

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    string result;
    if (option == 1) {
        result = playfairCipher(plaintext, key);
        cout << "Encrypted: " << result << endl;
    } else if (option == 0) {
        result = playfairCipher(plaintext, key, false);
        cout << "Decrypted: " << result << endl;
    } else {
        cout << "Invalid option" << endl;
    }

    return 0;
}
