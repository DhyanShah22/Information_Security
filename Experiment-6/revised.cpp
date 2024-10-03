#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

pair<map<char, int>, map<int, char>> Mapping() {
    map<char, int> letter_num;
    map<int, char> num_letter;

    for (char c = 'A'; c <= 'Z'; ++c) {
        letter_num[c] = c - 'A';
        num_letter[c - 'A'] = c;
    }

    return {letter_num, num_letter};
}

vector<int> multiplication_matrix(const vector<vector<int>>& key_matrix, const vector<int>& input_vector) {
    int size = key_matrix.size();
    vector<int> result(size, 0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < input_vector.size(); ++j) {
            result[i] += key_matrix[i][j] * input_vector[j];
        }
        result[i] = (result[i] % 26 + 26) % 26;
    }
    return result;
}

vector<vector<int>> convert_key_to_numbers(const vector<vector<char>>& key_matrix, const map<char, int>& letter_num) {
    int rows = key_matrix.size();
    int cols = key_matrix[0].size();
    vector<vector<int>> numeric_key_matrix(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            numeric_key_matrix[i][j] = letter_num.at(key_matrix[i][j]);
        }
    }
    return numeric_key_matrix;
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    throw runtime_error("No modular inverse found.");
}

int determinant(const vector<vector<int>>& matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

vector<vector<int>> inverse_matrix(const vector<vector<int>>& matrix) {
    int det = determinant(matrix);
    int mod = 26;
    if (det == 0) {
        throw runtime_error("Matrix is not invertible.");
    }
    int inv_det = mod_inverse(det, mod);

    return {
        {(matrix[1][1] * inv_det) % mod, (-matrix[0][1] * inv_det + mod) % mod},
        {(-matrix[1][0] * inv_det + mod) % mod, (matrix[0][0] * inv_det) % mod}
    };
}

string hill_cipher_encrypt(const string& plain_text, const vector<vector<char>>& key_matrix) {
    auto [letter_num, num_letter] = Mapping();
    vector<vector<int>> numeric_key_matrix = convert_key_to_numbers(key_matrix, letter_num);

    vector<int> input_vector(plain_text.size());
    for (size_t i = 0; i < plain_text.size(); ++i) {
        input_vector[i] = letter_num.at(plain_text[i]);
    }

    while (input_vector.size() % numeric_key_matrix.size() != 0) {
        input_vector.push_back(letter_num.at('X'));
    }

    string encrypted_text;
    for (size_t i = 0; i < input_vector.size(); i += numeric_key_matrix.size()) {
        vector<int> sub_vector(input_vector.begin() + i, input_vector.begin() + i + numeric_key_matrix.size());
        vector<int> encrypted_vector = multiplication_matrix(numeric_key_matrix, sub_vector);

        for (int val : encrypted_vector) {
            encrypted_text += num_letter[(val % 26 + 26) % 26];
        }
    }

    return encrypted_text;
}

string hill_cipher_decrypt(const string& encrypted_text, const vector<vector<char>>& key_matrix) {
    auto [letter_num, num_letter] = Mapping();
    vector<vector<int>> numeric_key_matrix = convert_key_to_numbers(key_matrix, letter_num);

    vector<vector<int>> inverse_key_matrix = inverse_matrix(numeric_key_matrix);

    vector<int> input_vector(encrypted_text.size());
    for (size_t i = 0; i < encrypted_text.size(); ++i) {
        input_vector[i] = letter_num.at(encrypted_text[i]);
    }

    string decrypted_text;
    for (size_t i = 0; i < input_vector.size(); i += inverse_key_matrix.size()) {
        vector<int> sub_vector(input_vector.begin() + i, input_vector.begin() + i + inverse_key_matrix.size());
        vector<int> decrypted_vector = multiplication_matrix(inverse_key_matrix, sub_vector);

        for (int val : decrypted_vector) {
            decrypted_text += num_letter[(val % 26 + 26) % 26];
        }
    }

    return decrypted_text;
}

vector<vector<char>> read_key_matrix(int size) {
    vector<vector<char>> key_matrix(size, vector<char>(size));
    cout << "Enter the " << size << "x" << size << " key matrix (row-wise, letters only):\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> key_matrix[i][j];
        }
    }
    return key_matrix;
}

bool is_invertible(const vector<vector<int>>& matrix) {
    int det = determinant(matrix);
    try {
        int inv = mod_inverse(det, 26);
        return true;
    } catch (const runtime_error& e) {
        return false;
    }
}

int main() {
    int choice;
    cout << "Enter 0 for Encryption or 1 for Decryption: ";
    cin >> choice;

    string text;
    if (choice == 0) {
        cout << "Enter the plain text (uppercase letters only): ";
        cin >> text;
        transform(text.begin(), text.end(), text.begin(), ::toupper);
    } else if (choice == 1) {
        cout << "Enter the encrypted text (uppercase letters only): ";
        cin >> text;
        transform(text.begin(), text.end(), text.begin(), ::toupper);
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    int size;
    cout << "Enter the size of the key matrix (e.g., 2 for a 2x2 matrix): ";
    cin >> size;

    vector<vector<char>> key_matrix = read_key_matrix(size);

    vector<vector<int>> numeric_key_matrix = convert_key_to_numbers(key_matrix, Mapping().first);
    if (!is_invertible(numeric_key_matrix)) {
        cout << "Error: The key matrix is not invertible. Please enter a valid matrix." << endl;
        return 1;
    }

    if (choice == 0) {
        string encrypted_text = hill_cipher_encrypt(text, key_matrix);
        cout << "Encrypted Text: " << encrypted_text << endl;
    } else {
        string decrypted_text = hill_cipher_decrypt(text, key_matrix);
        cout << "Decrypted Text: " << decrypted_text << endl;
    }

    return 0;
}
