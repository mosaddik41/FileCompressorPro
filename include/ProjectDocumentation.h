#ifndef PROJECT_DOCUMENTATION_H
#define PROJECT_DOCUMENTATION_H

#include <string>


const std::string TECHNICAL_MANUAL = 
"====================================================================\n"
"                  LZW COMPRESSOR: TECHNICAL MANUAL                  \n"
"====================================================================\n\n"
"1. INTRODUCTION TO LZW\n"
"   The Lempel-Ziv-Welch (LZW) algorithm is a lossless data compression\n"
"   technique. It is a dictionary-based substitution coder. Unlike \n"
"   Huffman coding, it does not require a statistical model of the data\n"
"   before starting, making it a 'one-pass' algorithm.\n\n"
"2. THE COMPRESSION PROCESS\n"
"   - The encoder maintains a dictionary of strings.\n"
"   - It reads symbols and finds the longest string in the dictionary\n"
"     that matches the current input.\n"
"   - It outputs the index (code) of that string and adds a new string\n"
"     (the match plus the next symbol) to the dictionary.\n\n"
"3. THE DECOMPRESSION PROCESS\n"
"   - The decoder reconstructs the dictionary dynamically.\n"
"   - It reads codes and translates them back into strings.\n"
"   - It adds new sequences to its dictionary by looking at the \n"
"     previous sequence and the first character of the current one.\n\n"
"4. BIT-PACKING LOGIC (12-BIT SPECIFICATION)\n"
"   Since 12 bits do not align with 8-bit byte boundaries, this \n"
"   software implements a custom BitBuffer. \n"
"   - Code 1 (12 bits) + Code 2 (12 bits) = 24 bits total.\n"
"   - 24 bits / 8 bits = 3 full bytes exactly.\n"
"   - This allows for a 33% increase in dictionary capacity compared\n"
"     to standard 8-bit encoding while maintaining high efficiency.\n\n"
"5. PERFORMANCE EXPECTATIONS\n"
"   - Text Files: High compression (approx 40-60% savings).\n"
"   - Binary/Images: Variable compression depending on pattern density.\n"
"   - Encrypted/Random: Low or zero compression (overhead may increase size).\n\n"
"6. SYSTEM REQUIREMENTS & COMPILATION\n"
"   - Compiler: GCC/G++ with C++17 support.\n"
"   - Memory: Minimum 1MB available RAM for dictionary allocation.\n"
"   - Disk: Permission to read/write in the project root directory.\n"
"====================================================================\n";

#endif 