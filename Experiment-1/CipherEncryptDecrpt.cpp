#include<iostream>
#include<string>
#include<cctype>

using namespace std;

int LetterToNumber (char letter){
    return toupper(letter) - 'A';
}

char NumberToLetter(int number) {
    return 'A' + number;
}

string encrypt(const string& message, int key){
    string cipherText;
    for(char ch: message){
        if(isalpha(ch)){
            int num = LetterToNumber(ch);
            num = (num + key) % 26; 
            cipherText += NumberToLetter(num);
        } else {
            cipherText += ch; 
        }
    }
    return cipherText;
}

string decrypt(const string& message, int key){
    string plainText;
    for (char ch : message) {
        if (isalpha(ch)) {
            int num = LetterToNumber(ch);
            num = (num - key + 26) % 26; 
            plainText += NumberToLetter(num);
        } else {
            plainText += ch; 
        }
    }
    return plainText;
}

int main() {
    string message;
    int key;
    int choice;

    cout << "Choose an option (1 for encrypt, 2 for decrypt): ";
    cin >> choice;
    cin.ignore(); 

    cout << "Enter the message: ";
    getline(cin, message);

    cout << "Enter the key (integer): ";
    cin >> key;

    if (choice == 1) {
        string encryptedMessage = encrypt(message, key);
        cout << "Encrypted Message: " << encryptedMessage <<endl;
    } else if (choice == 2) {
        string decryptedMessage = decrypt(message, key);
        cout << "Decrypted Message: " << decryptedMessage << endl;
    } else {
        cout << "Invalid choice" << endl;
    }

    return 0;
}