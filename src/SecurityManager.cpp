#include "../include/SecurityManager.h"
#include <iostream>

SecurityManager::SecurityManager(const std::string& password) : secretKey(password) {}

std::vector<uint8_t> SecurityManager::generateKeyStream(size_t length) {
    std::vector<uint8_t> keyStream;
    if (secretKey.empty()) return keyStream;


    for (size_t i = 0; i < length; ++i) {

        uint8_t keyByte = secretKey[i % secretKey.length()];
        keyStream.push_back(keyByte ^ (i % 255));
    }
    return keyStream;
}

void SecurityManager::encrypt(std::vector<uint8_t>& data) {
    std::vector<uint8_t> keyStream = generateKeyStream(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = data[i] ^ keyStream[i]; 
    }
    std::cout << "[SECURITY] Data encryption layer applied successfully." << std::endl;
}

void SecurityManager::decrypt(std::vector<uint8_t>& data) {

    encrypt(data); 
    std::cout << "[SECURITY] Data decryption layer processed." << std::endl;
}

uint32_t SecurityManager::getPasswordHash() {
    uint32_t hash = 5381;
    for (char c : secretKey) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}