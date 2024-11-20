#include<iostream>
#include<string>
#include<cctype>

using namespace std;

string encrypt(const string &text, const string &key){
    string ciphertext;
    int keyLength = key.length();
    for(size_t i = 0; i < text.size(); i++){
        if(isalpha(text[i])){
            char offset = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLength]) - 'A';
            char encryptedChar = ((text[i] - offset + keyChar) % 26) + offset;
            ciphertext += encryptedChar;
        }
        else{
            ciphertext += text[i];
        }
    }
    return ciphertext;
}

string decrypt(const string &text, const string &key){
    string plaintext;
    int keyLength = key.length();
    for(size_t i = 0; i < text.size(); i++){
        if(isalpha(text[i])){
            char offset = isupper(text[i]) ? 'A' : 'a';
            char keyChar = toupper(key[i % keyLength]) - 'A';
            char decryptedChar = ((text[i] - offset - keyChar + 26) % 26 ) + offset;
            plaintext += decryptedChar;
        }
        else{
            plaintext += text[i];
        }
    }
    return plaintext;
}


int main(){
    int choice;
    string text, key;

    cout<<"Enter 0 for encryption and 1 for decryption"<<endl;
    cin>>choice;
    cin.ignore();

    cout<<"Enter the text: "<<endl;
    getline(cin, text);

    cout<<"Enter the key: "<<endl;
    getline(cin, key);

    if(choice == 0){
        cout<< "Encrypted text is: " << encrypt(text, key) << endl;
    }
    else if(choice == 1){
        cout<< "Decrypted text is: " << decrypt(text, key) << endl;
    }
    else{
        cout<<"Invalid choice"<<endl;
    }
    return 0;
}