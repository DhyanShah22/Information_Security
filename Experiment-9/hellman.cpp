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

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long find_primitive_root(long long p) {
    vector<long long> factors;
    long long phi = p - 1;
    long long n = phi;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        factors.push_back(n);

    for (long long res = 2; res <= p; res++) {
        bool is_primitive = true;
        for (long long factor : factors) {
            if (mod_exp(res, phi / factor, p) == 1) {
                is_primitive = false;
                break;
            }
        }
        if (is_primitive)
            return res;
    }
    return -1; 
}

class Sender {
public:
    long long privateKey, publicKey;
    Sender(long long privKey, long long p, long long g) {
        privateKey = privKey;
        publicKey = mod_exp(g, privateKey, p);
        cout << "Sender (User A) private key: " << privateKey << endl;
        cout << "Sender (User A) public key: " << publicKey << endl;
    }
    long long compute_shared_key(long long receiverPublicKey, long long p) {
        cout << "Sender (User A) computing shared key with User B's public key: " << receiverPublicKey << endl;
        return mod_exp(receiverPublicKey, privateKey, p);
    }
};

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

int main() {
    long long p, g, privateA, privateB, sharedKeyA, sharedKeyB;

    cout << "Enter a large prime number (p): ";
    cin >> p;

    g = find_primitive_root(p);
    if (g == -1) {
        cout << "No primitive root found for the given prime." << endl;
        return -1;
    }

    cout << "The primitive root modulo " << p << " is: " << g << endl;

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
