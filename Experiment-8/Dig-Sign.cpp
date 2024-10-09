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

void GenerateRSAKeys(RSA::PrivateKey& privateKey, RSA::PublicKey& publicKey) {
    AutoSeededRandomPool rng;

    // Generate a private key
    privateKey.GenerateRandomWithKeySize(rng, 2048);

    // Directly assign the public key from the private key's parameters
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

std::string SignMessage(const RSA::PrivateKey& privateKey, const std::string& message) {
    AutoSeededRandomPool rng;
    std::string signature;
    std::string hash = HashMessage(message); // Hash the message first

    // Create a PK_Signer from the private key
    RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

    // Sign the hash
    StringSource(hash, true,
        new SignerFilter(rng, signer,
            new StringSink(signature)
        )
    );

    return signature;
}

bool VerifySignature(const RSA::PublicKey& publicKey, const std::string& message, const std::string& signature) {
    AutoSeededRandomPool rng;
    bool result = false;

    // Hash the original message
    std::string hash = HashMessage(message);
    
    // Create a PK_Verifier from the public key
    RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

    // Verify the signature against the hash
    try {
        StringSource(signature + hash, true,
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


int main() {
    RSA::PrivateKey privateKey;
    RSA::PublicKey publicKey;

    GenerateRSAKeys(privateKey, publicKey);

    std::string message;
    std::cout << "Enter the message to be signed: ";
    std::getline(std::cin, message);

    std::string signature = SignMessage(privateKey, message);
    std::cout << "Signature (Hex): ";
    StringSource(signature, true, new HexEncoder(new FileSink(std::cout)));
    std::cout << std::endl;

    std::cout << "Do you want to verify the signature? (1 for Yes, 0 for No): ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::string verifyMessage;
        std::cout << "Enter the original message to verify: ";
        std::cin.ignore(); // Clear the input buffer
        std::getline(std::cin, verifyMessage);

        if (VerifySignature(publicKey, verifyMessage, signature)) {
            std::cout << "Signature is valid. The message is authentic and untampered." << std::endl;
        } else {
            std::cout << "Signature verification failed. The message may have been altered." << std::endl;
        }
    }

    return 0;
}
