#include <iostream>
#include <vector>
#include <string>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int determinant(int a, int b, int c, int d) {
    return (a * d - b * c) % 26;
}

int modInverse(int a, int mod) {
    for (int x = 1; x < mod; x++) {
        if ((a * x) % mod == 1) {
            return x;
        }
    }
    return -1; 
}

bool isInvertible(int det) {
    return gcd(det, 26) == 1; 
}

string encrypt(string text, vector<vector<int>>& keyMatrix) {
    string encrypted = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        int a = text[i] - 'A';   
        int b = text[i + 1] - 'A'; 

        // Perform encryption
        int c = (keyMatrix[0][0] * a + keyMatrix[0][1] * b) % 26;
        int d = (keyMatrix[1][0] * a + keyMatrix[1][1] * b) % 26;

        encrypted += (c + 'A');
        encrypted += (d + 'A');
    }
    return encrypted;
}

string decrypt(string text, vector<vector<int>>& keyMatrix) {
    string decrypted = "";

    int det = determinant(keyMatrix[0][0], keyMatrix[0][1], keyMatrix[1][0], keyMatrix[1][1]);
    int invDet = modInverse(det, 26);

    vector<vector<int>> adjMatrix(2, vector<int>(2));
    adjMatrix[0][0] = keyMatrix[1][1] * invDet % 26;
    adjMatrix[0][1] = -keyMatrix[0][1] * invDet % 26;
    adjMatrix[1][0] = -keyMatrix[1][0] * invDet % 26;
    adjMatrix[1][1] = keyMatrix[0][0] * invDet % 26;

    // Make sure all values are positive
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (adjMatrix[i][j] < 0) {
                adjMatrix[i][j] += 26;
            }
        }
    }

    for (size_t i = 0; i < text.length(); i += 2) {
        int a = text[i] - 'A';   
        int b = text[i + 1] - 'A'; 

        int c = (adjMatrix[0][0] * a + adjMatrix[0][1] * b) % 26;
        int d = (adjMatrix[1][0] * a + adjMatrix[1][1] * b) % 26;

        decrypted += (c + 'A');
        decrypted += (d + 'A');
    }
    return decrypted;
}

int main() {
    int choice;
    string text, key;

    cout << "Enter 0 for Encryption or 1 for Decryption: ";
    cin >> choice;

    cout << "Enter the text (uppercase letters only, no spaces): ";
    cin >> text;

    cout << "Enter 4 letters for the key (will form a 2x2 matrix): ";
    cin >> key;

    if (text.length() % 2 != 0) {
        text += 'X'; 
    }

    vector<vector<int>> keyMatrix(2, vector<int>(2));
    keyMatrix[0][0] = key[0] - 'A';
    keyMatrix[0][1] = key[1] - 'A';
    keyMatrix[1][0] = key[2] - 'A';
    keyMatrix[1][1] = key[3] - 'A';

    int det = determinant(keyMatrix[0][0], keyMatrix[0][1], keyMatrix[1][0], keyMatrix[1][1]);
    cout << "Determinant: " << det << endl; 

    if (choice == 0 && !isInvertible(det)) {
        cout << "Error: The key matrix is not invertible under mod 26. Please enter a valid key." << endl;
        return 0;
    }

    if (choice == 0) {
        string encryptedText = encrypt(text, keyMatrix);
        cout << "Encrypted text: " << encryptedText << endl;
    } else {
        if (!isInvertible(det)) {
            cout << "Error: The key matrix is not invertible under mod 26. Please enter a valid key." << endl;
            return 0;
        }
        string decryptedText = decrypt(text, keyMatrix);
        cout << "Decrypted text: " << decryptedText << endl;
    }

    return 0;
}
