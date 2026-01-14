#ifndef SECURITY_MANAGER_H
#define SECURITY_MANAGER_H

#include <string>
#include <vector>
#include <cstdint>

class SecurityManager {
private:
    std::string secretKey;
    
    std::vector<uint8_t> generateKeyStream(size_t length);

public:
    SecurityManager(const std::string& password);
    
    void encrypt(std::vector<uint8_t>& data);
    
    void decrypt(std::vector<uint8_t>& data);

    uint32_t getPasswordHash();
};

#endif