//
//  mcFile.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcFile_hpp
#define mcFile_hpp

#include <iostream>
#include <unordered_map>

struct mcData;

const std::string DATA_FILE_NAME = "data.bin";

class mcFile {
private:
    void read(const std::string& inLine, mcData& data);
    
public:
    // saving and loading file
    std::unordered_map<std::string, float> dataHash;
    void save(const char* filename, mcData& data);
    const bool load(const char* filename, mcData& data);
    
    
    
};

#endif /* mcFile_hpp */
