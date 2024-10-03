#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to calculate the GCD of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int a, int b, int c, int d) {
    return (a * d - b * c) % 26;
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int mod) {
    for (int x = 1; x < mod; x++) {
        if ((a * x) % mod == 1) {
            return x;
        }
    }
    return -1; // If no modular inverse exists
}

// Function to check if the key matrix is invertible
bool isInvertible(int det) {
    return gcd(det, 26) == 1; // Check if GCD is 1
}

// Function to encrypt the text using the key
string encrypt(string text, vector<vector<int>>& keyMatrix) {
    string encrypted = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        int a = text[i] - 'A';   // First letter
        int b = text[i + 1] - 'A'; // Second letter

        // Perform encryption
        int c = (keyMatrix[0][0] * a + keyMatrix[0][1] * b) % 26;
        int d = (keyMatrix[1][0] * a + keyMatrix[1][1] * b) % 26;

        encrypted += (c + 'A');
        encrypted += (d + 'A');
    }
    return encrypted;
}

// Function to decrypt the text using the key
string decrypt(string text, vector<vector<int>>& keyMatrix) {
    string decrypted = "";

    // Calculate the determinant and its modular inverse
    int det = determinant(keyMatrix[0][0], keyMatrix[0][1], keyMatrix[1][0], keyMatrix[1][1]);
    int invDet = modInverse(det, 26);

    // Calculate the adjugate matrix
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
        int a = text[i] - 'A';   // First letter
        int b = text[i + 1] - 'A'; // Second letter

        // Perform decryption
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

    // Ensure text is uppercase and has an even length
    if (text.length() % 2 != 0) {
        text += 'X'; // Padding with 'X' if length is odd
    }

    // Create the key matrix
    vector<vector<int>> keyMatrix(2, vector<int>(2));
    keyMatrix[0][0] = key[0] - 'A';
    keyMatrix[0][1] = key[1] - 'A';
    keyMatrix[1][0] = key[2] - 'A';
    keyMatrix[1][1] = key[3] - 'A';

    // Calculate determinant
    int det = determinant(keyMatrix[0][0], keyMatrix[0][1], keyMatrix[1][0], keyMatrix[1][1]);
    cout << "Determinant: " << det << endl; // Debugging line

    // Check for invertibility
    if (choice == 0 && !isInvertible(det)) {
        cout << "Error: The key matrix is not invertible under mod 26. Please enter a valid key." << endl;
        return 0;
    }

    // Perform encryption or decryption based on user choice
    if (choice == 0) {
        string encryptedText = encrypt(text, keyMatrix);
        cout << "Encrypted text: " << encryptedText << endl;
    } else {
        // For decryption, first check if the key matrix is valid
        if (!isInvertible(det)) {
            cout << "Error: The key matrix is not invertible under mod 26. Please enter a valid key." << endl;
            return 0;
        }
        string decryptedText = decrypt(text, keyMatrix);
        cout << "Decrypted text: " << decryptedText << endl;
    }

    return 0;
}
