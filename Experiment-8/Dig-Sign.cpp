#include <iostream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

class Sender {
public:
    RSA::PrivateKey privateKey;
    RSA::PublicKey publicKey;

    Sender() {
        GenerateRSAKeys();
    }

    void GenerateRSAKeys() {
        AutoSeededRandomPool rng;
        privateKey.GenerateRandomWithKeySize(rng, 2048);
        publicKey = RSA::PublicKey(privateKey);  
    }

    std::string HashMessage(const std::string &message) {
        SHA1 hash;
        std::string digest;

        StringSource(message, true,
            new HashFilter(hash,
                new StringSink(digest)
            )
        );

        return digest;
    }

    std::string SignMessage(const std::string& message) {
        AutoSeededRandomPool rng;
        std::string signature;
        std::string hash = HashMessage(message); // Hash the message first

        RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

        StringSource(hash, true,
            new SignerFilter(rng, signer,
                new StringSink(signature)
            )
        );

        return signature;
    }

    std::string SendMessage(const std::string& message) {
        std::string signature = SignMessage(message);

        std::string encodedSignature;
        StringSource(signature, true, new HexEncoder(new StringSink(encodedSignature)));

        std::cout << "Generated Signature (Hex): " << encodedSignature << std::endl;

        std::string concatenated = message + ":" + encodedSignature;
        std::cout << "Concatenated Message (Plaintext + Signature): " << concatenated << std::endl;

        return concatenated;  
    }
};

class Receiver {
public:
    bool VerifySignature(const RSA::PublicKey& publicKey, const std::string& message, const std::string& signature) {
        AutoSeededRandomPool rng;
        bool result = false;

        std::string hash = HashMessage(message);

        std::string decodedSignature;
        StringSource(signature, true, new HexDecoder(new StringSink(decodedSignature)));

        RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

        try {
            StringSource(decodedSignature + hash, true,
                new SignatureVerificationFilter(verifier,
                    new ArraySink((byte*)&result, sizeof(result))
                )
            );
        }
        catch (const Exception& e) {
            std::cerr << "Verification error: " << e.what() << std::endl;
            return false;
        }

        return result;
    }

    std::string HashMessage(const std::string &message) {
        SHA1 hash;
        std::string digest;

        StringSource(message, true,
            new HashFilter(hash,
                new StringSink(digest)
            )
        );

        return digest;
    }

    void ReceiveMessage(const std::string& receivedMessage, const RSA::PublicKey& publicKey, bool tampered = false) {
        std::size_t delimiterPos = receivedMessage.find(':');
        if (delimiterPos == std::string::npos) {
            std::cerr << "Error: Could not find signature in the received message." << std::endl;
            return;
        }

        std::string message = receivedMessage.substr(0, delimiterPos);
        std::string encodedSignature = receivedMessage.substr(delimiterPos + 1);

        std::cout << "Received Plaintext: " << message << std::endl;
        std::cout << "Received Signature (Hex): " << encodedSignature << std::endl;

        if (tampered) {
            message[0] = 'f'; 
            message += " (modified)"; 
            std::cout << "Received Plaintext(Tampered): " << message << std::endl;
            std::cout << "Message has been tampered with." << std::endl;
        }

        if (VerifySignature(publicKey, message, encodedSignature)) {
            std::cout << "Signature is valid. The message is authentic and untampered." << std::endl;
        } else {
            std::cout << "Signature verification failed. The message may have been altered." << std::endl;
        }
    }
};

int main() {
    Sender sender;  
    Receiver receiver;  

    std::string message;
    std::cout << "Enter the message to be sent: ";
    std::getline(std::cin, message);

    std::string concatenatedMessage = sender.SendMessage(message);

    receiver.ReceiveMessage(concatenatedMessage, sender.publicKey); 

    std::cout << "\n--- Simulating Tampering ---\n" << std::endl;
    receiver.ReceiveMessage(concatenatedMessage, sender.publicKey, true); 
    return 0;
}
