#include <iostream>
#include <cmath>
#include <vector>

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

class Receiver {
public:
    long long privateKey, publicKey;
    Receiver(long long privKey, long long p, long long g) {
        privateKey = privKey;
        publicKey = mod_exp(g, privateKey, p);
        cout << "Receiver (User B) private key: " << privateKey << endl;
        cout << "Receiver (User B) public key: " << publicKey << endl;
    }
    long long compute_shared_key(long long senderPublicKey, long long p) {
        cout << "Receiver (User B) computing shared key with User A's public key: " << senderPublicKey << endl;
        return mod_exp(senderPublicKey, privateKey, p);
    }
};

class Sender {
public:
    long long privateKey, publicKey;
    Sender(long long privKey, long long p, long long g) {
        privateKey = privKey;
        publicKey = mod_exp(g, privateKey, p);
        cout << "Public Key (USER A): "<< publicKey <<endl;
        cout << "Private Key (USER B): "<< privateKey<<endl;
    }

    long long compute_shared_key(long long receiverPublicKey, long long p){
        cout<<"Public key recieved from USER B: " << receiverPublicKey;
        return mod_exp(receiverPublicKey, privateKey, p);
    }
};

int main() {
    long long p, g, privateA, privateB, sharedKeyA, sharedKeyB;

    cout << "Enter a large prime number (p): ";
    cin >> p;

    cout << "Enter a primitive root modulo " << p << " (g): ";
    cin >> g;

    cout << "User A, enter your private key: ";
    cin >> privateA;
    cout << "User B, enter your private key: ";
    cin >> privateB;

    Sender userA(privateA, p, g);
    Receiver userB(privateB, p, g);

    cout << "\nPublic keys exchanged:" << endl;
    cout << "User A sends public key: " << userA.publicKey << endl;
    cout << "User B sends public key: " << userB.publicKey << endl;

    sharedKeyA = userA.compute_shared_key(userB.publicKey, p);
    sharedKeyB = userB.compute_shared_key(userA.publicKey, p);

    cout << "\nShared key calculated by User A: " << sharedKeyA << endl;
    cout << "Shared key calculated by User B: " << sharedKeyB << endl;

    if (sharedKeyA == sharedKeyB) {
        cout << "\nShared secret key (User A and User B): " << sharedKeyA << endl;
        cout << "Both users have successfully computed the same shared secret key!" << endl;
    } else {
        cout << "\nError: Shared keys do not match!" << endl;
    }

    return 0;
}
