#include <iostream>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <algorithm>


using namespace std;

class PlayfairCipher {
private:
    vector<vector<char>> matrix;
    string key;

    void createMatrix() {
        unordered_set<char> used;
        int k = 0;
        matrix.resize(7, vector<char>(4));

        for (char ch : key) {
            ch = tolower(ch);
            if (used.find(ch) == used.end() && ch != 'j') {
                matrix[k / 4][k % 4] = ch;
                used.insert(ch);
                k++;
            }
        }

        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (used.find(ch) == used.end() && ch != 'j') {
                matrix[k / 4][k % 4] = ch;
                used.insert(ch);
                k++;
            }
        }

        // Add numbers to fill the 7x4 matrix
        for (char ch = '0'; ch <= '9'; ++ch) {
            if (k >= 28) break;
            matrix[k / 4][k % 4] = ch;
            k++;
        }
    }

    pair<int, int> findPosition(char ch) {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (matrix[i][j] == ch) {
                    return {i, j};
                }
            }
        }
        return {-1, -1}; // Should never reach here
    }

    string processDigraph(char a, char b, bool encrypt) {
        pair<int, int> pos1 = findPosition(a);
        pair<int, int> pos2 = findPosition(b);
        char finalA, finalB;

        // Same row
        if (pos1.first == pos2.first) {
            if (encrypt) {
                finalA = matrix[pos1.first][(pos1.second + 1) % 4];
                finalB = matrix[pos2.first][(pos2.second + 1) % 4];
            } else {
                finalA = matrix[pos1.first][(pos1.second + 3) % 4];
                finalB = matrix[pos2.first][(pos2.second + 3) % 4];
            }
        }
        // Same column
        else if (pos1.second == pos2.second) {
            if (encrypt) {
                finalA = matrix[(pos1.first + 1) % 7][pos1.second];
                finalB = matrix[(pos2.first + 1) % 7][pos2.second];
            } else {
                finalA = matrix[(pos1.first + 6) % 7][pos1.second];
                finalB = matrix[(pos2.first + 6) % 7][pos2.second];
            }
        }
        // Rectangle swap
        else {
            finalA = matrix[pos1.first][pos2.second];
            finalB = matrix[pos2.first][pos1.second];
        }

        return string(1, finalA) + string(1, finalB);
    }

public:
    PlayfairCipher(string key) : key(move(key)) {
        createMatrix();
    }

    string encrypt(string text) {
        string result;
        text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
        text.erase(remove_if(text.begin(), text.end(), ::isdigit), text.end());

        // Process digraphs
        for (size_t i = 0; i < text.length(); i += 2) {
            if (i + 1 == text.length() || text[i] == text[i + 1]) {
                text.insert(i + 1, "x");
            }
            result += processDigraph(tolower(text[i]), tolower(text[i + 1]), true);
        }

        return result;
    }

    string decrypt(string text) {
        string result;

        for (size_t i = 0; i < text.length(); i += 2) {
            result += processDigraph(tolower(text[i]), tolower(text[i + 1]), false);
        }

        return result;
    }

    void printMatrix() {
        for (const auto &row : matrix) {
            for (char ch : row) {
                cout << ch << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    string key, text;

    cout << "Enter key: ";
    getline(cin, key);
    PlayfairCipher cipher(key);

    cout << "Generated 7x4 matrix:" << endl;
    cipher.printMatrix();

    cout << "Enter text to encrypt: ";
    getline(cin, text);
    string encrypted = cipher.encrypt(text);
    cout << "Encrypted text: " << encrypted << endl;

    string decrypted = cipher.decrypt(encrypted);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
