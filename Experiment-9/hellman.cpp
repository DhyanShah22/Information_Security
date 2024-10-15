#include <iostream>
#include <cmath>

using namespace std;

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        exp = exp >> 1;   
        base = (base * base) % mod;  
    }
    return result;
}

int main() {
    long long p, g, privateA, privateB, publicA, publicB, sharedKeyA, sharedKeyB;

    cout << "Enter a large prime number (p): ";
    cin >> p;
    cout << "Enter a primitive root modulo " << p << " (g): ";
    cin >> g;

    cout << "User A, enter your private key: ";
    cin >> privateA;
    cout << "User B, enter your private key: ";
    cin >> privateB;

    publicA = mod_exp(g, privateA, p);
    publicB = mod_exp(g, privateB, p);

    cout << "\nPublic key of User A: " << publicA;
    cout << "\nPublic key of User B: " << publicB << endl;

    sharedKeyA = mod_exp(publicB, privateA, p);
    sharedKeyB = mod_exp(publicA, privateB, p);

    if (sharedKeyA == sharedKeyB) {
        cout << "\nShared secret key (User A and User B): " << sharedKeyA << endl;
    } else {
        cout << "\nError: Shared keys do not match!" << endl;
    }

    return 0;
}
