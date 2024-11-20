#include <iostream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

class Sender {
public:
    RSA::PrivateKey privatekey;
    RSA::PublicKey publicKey;
    
    Sender() {
        AutoSeededRandomPool rng;
        privatekey.GenerateRandomWithKeySize(rng, 2048);
        publicKey = RSA::PublicKey(privatekey);
    }

    string signMessage(const string& message) {
        AutoSeededRandomPool rng;
        string signature;
        RSASSA_PKCS1v15_SHA_Signer signer(privatekey);

        StringSource(message, true, new SignerFilter(rng, signer, new StringSink(signature)));
        string encodedString;
        StringSource(signature, true, new HexEncoder(new StringSink(encodedString)));
        return encodedString;
    }

    string sendMessage(const string& message){
        string signature = signMessage(message);
        cout << "Generated Signature (Hex): " << signature << endl;
        return message + ":" + signature;
    }
};

class Receiver {
public:
    bool verifyMessage(RSA::PublicKey& publicKey, const string& message, const string& encodedSignature){
        string decodedSignature;
        StringSource(encodedSignature, true, new HexDecoder(new StringSink(decodedSignature)));
        RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
        try {
            StringSource(decodedSignature + message, true, new SignatureVerificationFilter(verifier));
            return true;
        }catch(...){
            return false;
        }
    }

    void receiveMessage(const string&receivedMessage, RSA::PublicKey& publicKey, bool tampered = false){
        size_t delimeterPos = receivedMessage.find(':');
        if(delimeterPos == string::npos){
            cerr << "Error: Invalid message format." << endl;
        }

        string message = receivedMessage.substr(0, delimeterPos);
        string signature = receivedMessage.substr(delimeterPos + 1);

        if(verifyMessage(publicKey, message, signature)){
            cout << "Message verified successfully. It is authentic and untampered." << endl;
        }
        else{
            cout << "Message verification failed. It may have been tampered with." << endl;
        }
    }
};

int main() {
    Sender sender;
    Receiver receiver;

    cout << "Enter message: ";
    string message;
    getline(cin, message);

    string transmittedMessage = sender.sendMessage(message);

    cout << "\n--- Receiving Message ---\n";
    receiver.receiveMessage(transmittedMessage, sender.publicKey);

    cout << "\n--- Simulating Tampering ---\n";
    receiver.receiveMessage(transmittedMessage, sender.publicKey, true);

    return 0;
}
