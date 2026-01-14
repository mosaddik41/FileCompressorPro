#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstring>

#include "../include/FileManager.h"
#include "../include/LZWDictionary.h"
#include "../include/BitBuffer.h"
#include "../include/BitReader.h"
#include "../include/LZWDecompressor.h"
#include "../include/ProjectDocumentation.h"
#include "../include/ProgressBar.h" 
#include "../include/Logger.h"
#include "../include/AnalysisEngine.h"
#include "../include/DictMonitor.h"
#include "../include/SecurityManager.h"


const std::string APP_VERSION = "3.0.0-ENTERPRISE";
const std::string BUILD_DATE = "2026-01-14";
const std::string DEVELOPER_INFO = "SPL1 Project - Secure LZW Engine";


void printApplicationHeader() {
    std::cout << "\n========================================================" << std::endl;
    std::cout << "      LZW SECURE PROFESSIONAL COMPRESSION SYSTEM        " << std::endl;
    std::cout << "          DESIGNED FOR SPL1  PROJECT - V" << APP_VERSION << "          "  << std::endl;
    std::cout << "========================================================" << std::endl;
}


void showSystemInfo() {
    std::cout << "\n[SYSTEM CONFIGURATION]" << std::endl;
    std::cout << "Architecture: Fixed-Width 12-Bit LZW Encoding" << std::endl;
    std::cout << "Max Dictionary Entries: 4096" << std::endl;
    std::cout << "Security Mode: Session-Locked XOR Cipher" << std::endl;
    std::cout << "Header Protocol: LZWv3 (Magic + Hash + Payload)" << std::endl;
    std::cout << "Build Target: x64 Windows/Linux (MinGW)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}


void displayHexView(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "[!] Target file not found for Hex Analysis." << std::endl;
        return;
    }
    unsigned char buffer[16];
    std::cout << "\n--- HEXADECIMAL STREAM ANALYSIS (BINARY VIEW) ---\n";
    for(int row = 0; row < 12 && file.read((char*)buffer, 16); row++) {
        std::cout << std::setw(4) << std::setfill('0') << std::hex << row * 16 << ": ";
        for(int i=0; i<16; i++) {
            std::cout << std::setw(2) << (int)buffer[i] << " ";
        }
        std::cout << std::dec << std::setfill(' ') << " | ";
        for(int i=0; i<16; i++) {
            if(buffer[i] >= 32 && buffer[i] <= 126) std::cout << (char)buffer[i];
            else std::cout << ".";
        }
        std::cout << "\n";
    }
}

int main() {
    int userCommand = 0;
    Logger systemLogger("session_history.log"); 
    DictMonitor monitor;

    printApplicationHeader();


    std::string sessionPassword;
    std::cout << "\n[SECURITY] INITIALIZE SESSION" << std::endl;
    std::cout << "Please set a Master Password for this session: ";
    std::cin >> sessionPassword;
    
    SecurityManager sessionSecurity(sessionPassword);
    uint32_t sessionHash = sessionSecurity.getPasswordHash();
    
    std::cout << "[SUCCESS] Session Authenticated. Hash ID: " << std::hex << sessionHash << std::dec << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    while (true) {
        std::cout << "\n--- SYSTEM CONTROL PANEL ---" << std::endl;
        std::cout << " 1. [SECURE COMPRESS]   Process 'sample.txt'" << std::endl;
        std::cout << " 2. [SECURE DECOMPRESS] Process 'compressed.bin'" << std::endl;
        std::cout << " 3. [DIAGNOSTICS]       Algorithm Parameters" << std::endl;
        std::cout << " 4. [MANUAL]            Technical Documentation" << std::endl;
        std::cout << " 5. [HEX VIEW]          Raw Binary Inspection" << std::endl;
        std::cout << " 6. [LOGS]              Session History" << std::endl;
        std::cout << " 7. [QUIT]              Exit System" << std::endl;
        std::cout << "\nAction Choice (1-7): ";

        if (!(std::cin >> userCommand)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (userCommand == 7) break;

        switch(userCommand) {
            case 1: {
                FileManager fm("sample.txt", "compressed.bin");
                if (!fm.fileExists()) {
                    std::cout << "[ERROR] Source file 'sample.txt' missing." << std::endl;
                    continue;
                }

                std::vector<char> sourceData = fm.readFile();
                std::cout << "\n[STAGE 1] Running Pre-Compression Analysis..." << std::endl;
                double entropy = AnalysisEngine::calculateEntropy(sourceData);
                std::cout << " > Input Entropy: " << std::fixed << std::setprecision(2) << entropy << " bits/byte" << std::endl;
                std::cout << " > Predicted Yield: " << AnalysisEngine::getEfficiencyRecommendation(entropy) << std::endl;

                LZWDictionary lzwDict;
                BitBuffer bitStream;
                std::string currentChain = "";
                ProgressBar pg(sourceData.size());
                
                std::cout << "[STAGE 2] Executing LZW Dictionary Build..." << std::endl;
                for (size_t i = 0; i < sourceData.size(); ++i) {
                    char byte = sourceData[i];
                    std::string combined = currentChain + byte;
                    if (lzwDict.contains(combined)) {
                        currentChain = combined;
                    } else {
                        bitStream.write12Bits(lzwDict.getCode(currentChain));
                        lzwDict.add(combined);
                        currentChain = std::string(1, byte);
                    }
                    if (i % 50 == 0) pg.update(i);
                }
                if (!currentChain.empty()) bitStream.write12Bits(lzwDict.getCode(currentChain));
                bitStream.flush();
                pg.finish();

                std::vector<uint8_t> packedData = bitStream.getPackedData();
                sessionSecurity.encrypt(packedData); 

                std::vector<char> finalArchive;
                finalArchive.push_back('L'); finalArchive.push_back('Z'); 
                finalArchive.push_back('W'); finalArchive.push_back('!');
                
                char* hashPtr = reinterpret_cast<char*>(&sessionHash);
                for(int i=0; i<4; i++) finalArchive.push_back(hashPtr[i]);

                for(uint8_t b : packedData) finalArchive.push_back(static_cast<char>(b));

                fm.writeFile(finalArchive);
                double ratio = (static_cast<double>(finalArchive.size()) / sourceData.size()) * 100.0;
                
                std::cout << "[SUCCESS] Archive secured. Compression Ratio: " << ratio << "%" << std::endl;
                systemLogger.logCompressionEvent(sourceData.size(), finalArchive.size(), ratio);
                break;
            }

            case 2: { 
                FileManager fm("compressed.bin", "restored.txt");
                std::vector<char> binData = fm.readFile();
                if (binData.size() < 8) {
                    std::cout << "[ERROR] Archive corrupted or incomplete." << std::endl;
                    continue;
                }

                if (binData[0]!='L' || binData[1]!='Z' || binData[2]!='W' || binData[3]!='!') {
                    std::cout << "[ERROR] Invalid archive signature." << std::endl;
                    continue;
                }

                uint32_t storedHash;
                std::memcpy(&storedHash, &binData[4], 4);
                
                if (storedHash != sessionHash) {
                    std::cout << "[AUTH FAILED] Access Denied: Session password does not match file." << std::endl;
                    continue;
                }

                std::vector<uint8_t> payload(binData.begin() + 8, binData.end());
                sessionSecurity.decrypt(payload);

                std::cout << "[STAGE 1] Reconstructing String Table..." << std::endl;
                LZWDecompressor decompressor;
                std::vector<char> restoredData = decompressor.decompress(payload);
                
                fm.writeFile(restoredData);
                std::cout << "[STAGE 2] Checking Integrity..." << std::endl;
                if (fm.verifyIntegrity("sample.txt", "restored.txt")) {
                    std::cout << " >> [MATCH] Data restoration 100% verified." << std::endl;
                } else {
                    std::cout << " >> [MISMATCH] Warning: Original and restored files differ." << std::endl;
                }
                break;
            }

            case 3: showSystemInfo(); break;
            case 4: std::cout << TECHNICAL_MANUAL << std::endl; break;
            case 5: displayHexView("compressed.bin"); break;
            case 6: systemLogger.showRecentHistory(); break;
            default: std::cout << "Invalid Command." << std::endl;
        }
    }

    std::cout << "\n[INFO] Flushed memory. Closing SPL1 Secure LZW System..." << std::endl;
    return 0;
}