#include<iostream>
#include<string>
#include<vector>

using namespace std;

string encryptRailFence(const string& text, int rails){
    if(rails<=1) return text;

    vector<string>rail(rails);
    int row = 0, direction = 1;

    for(char c: text){
        rail[row] += c;
        row += direction;
        if(row == 0 || row == rails - 1) direction = -direction;
    }

    string ciphertext;
    for(const auto& line :rail){
        ciphertext += line;
    }
    return ciphertext;
}

string decryptRailFence(const string &cipher, int rails){
    if(rails<=1) return cipher;

    vector<string>rail(rails, string(cipher.size(), '\0'));
    int row = 0, direction = 1, index = 0;

    for(size_t i = 0; i < cipher.size(); ++i){
        rail[row][i] = '*';
        row += direction;
        if(row == 0 || row == rails - 1) direction = -direction;
    }


    for(auto& line : rail){
        for(auto& c: line){
            if(c == '*') c = cipher[index++];
        }
    }

    string plaintext;
    row = 0, direction = 1;
    for(size_t i = 0; i < cipher.size(); ++i){
        plaintext += rail[row][i];
        row += direction;
        if(row == 0 || row == rails - 1) direction = -direction;
    }
    return plaintext;
}

int main(){
    int choice, rails;
    string text;

    cout<< "Enter 1 for encryption and 2 for decryption" <<endl;
    cin >> choice;
    cin.ignore();

    cout<<"Enter no. of rails" <<endl;
    cin >> rails;
    cin.ignore();

    cout << "Enter the text: "<<endl;
    getline(cin, text);

    if(choice == 1){
        cout << "Encrypted text: " << encryptRailFence(text, rails) << endl;
    }
    else if(choice == 2){
        cout<< "Decrypted text: " << decryptRailFence(text, rails) <<endl;
    }
    else{
        cout<<"Invalid choice!"<<endl;
    }

    return 0;
}